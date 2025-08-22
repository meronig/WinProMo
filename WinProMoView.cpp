/* ==========================================================================

	Copyright © 2025 Technical University of Denmark

	CWinProMoView

	Author :		Giovanni Meroni

	Purpose :		"CWinProMoView" is used as part of the MFC document/view
					architecture to represent documents. It contains a
					reference to "CProMoEditor", which handles the display 
					and model editing operations.

	Description :	"CWinProMoView" is derived from "CView".

	Usage :			Classes should be derived from "CWinProMoView". For
					derived classes to properly work, IMPLEMENT_DYNCREATE
					and DECLARE_DYNCREATE macros must be present. If an
					editor different than "CProMoEditor" is needed,	
					"CreateEditor" should be overridden.

   ========================================================================*/
#include "stdafx.h"
#include "WinProMoDoc.h"
#include "WinProMoView.h"
#include "GridSizeDialog.h"
#include "CanvasSizeDialog.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CWinProMoView

IMPLEMENT_DYNCREATE(CWinProMoView, CView)

BEGIN_MESSAGE_MAP(CWinProMoView, CView)
	//{{AFX_MSG_MAP(CWinProMoView)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
	ON_WM_SIZE()
	ON_WM_ERASEBKGND()
	ON_COMMAND(ID_EDIT_COPY, OnEditCopy)
	ON_UPDATE_COMMAND_UI(ID_EDIT_COPY, OnUpdateEditCopy)
	ON_COMMAND(ID_EDIT_CUT, OnEditCut)
	ON_UPDATE_COMMAND_UI(ID_EDIT_CUT, OnUpdateEditCut)
	ON_COMMAND(ID_EDIT_PASTE, OnEditPaste)
	ON_UPDATE_COMMAND_UI(ID_EDIT_PASTE, OnUpdateEditPaste)
	ON_COMMAND(ID_EDIT_UNDO, OnEditUndo)
	ON_UPDATE_COMMAND_UI(ID_EDIT_UNDO, OnUpdateEditUndo)
	ON_COMMAND(ID_ARRANGE_SNAPTOGRID, OnButtonSnap)
	ON_UPDATE_COMMAND_UI(ID_ARRANGE_SNAPTOGRID, OnUpdateButtonSnap)
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CWinProMoView::OnFilePrintPreview)
	ON_COMMAND(ID_EDIT_DELETE, CWinProMoView::OnEditDelete)
	ON_UPDATE_COMMAND_UI(ID_EDIT_DELETE, CWinProMoView::OnUpdateEditDelete)
	ON_COMMAND(ID_ARRANGE_GROUP, CWinProMoView::OnArrangeGroup)
	ON_UPDATE_COMMAND_UI(ID_ARRANGE_GROUP, CWinProMoView::OnUpdateArrangeGroup)
	ON_COMMAND(ID_ARRANGE_UNGROUP, CWinProMoView::OnArrangeUngroup)
	ON_UPDATE_COMMAND_UI(ID_ARRANGE_UNGROUP, CWinProMoView::OnUpdateArrangeUngroup)
	ON_COMMAND(ID_VIEW_GRID, CWinProMoView::OnViewGrid)
	ON_UPDATE_COMMAND_UI(ID_VIEW_GRID, CWinProMoView::OnUpdateViewGrid)
	ON_COMMAND(ID_ALIGN_BOTTOM, CWinProMoView::OnAlignBottom)
	ON_UPDATE_COMMAND_UI(ID_ALIGN_BOTTOM, CWinProMoView::OnUpdateAlignBottom)
	ON_UPDATE_COMMAND_UI(ID_ALIGN_CENTER, CWinProMoView::OnUpdateAlignCenter)
	ON_COMMAND(ID_ALIGN_CENTER, CWinProMoView::OnAlignCenter)
	ON_COMMAND(ID_ALIGN_LEFT, CWinProMoView::OnAlignLeft)
	ON_UPDATE_COMMAND_UI(ID_ALIGN_LEFT, CWinProMoView::OnUpdateAlignLeft)
	ON_COMMAND(ID_ALIGN_MIDDLE, CWinProMoView::OnAlignMiddle)
	ON_UPDATE_COMMAND_UI(ID_ALIGN_MIDDLE, CWinProMoView::OnUpdateAlignMiddle)
	ON_COMMAND(ID_ALIGN_RIGHT, CWinProMoView::OnAlignRight)
	ON_UPDATE_COMMAND_UI(ID_ALIGN_RIGHT, CWinProMoView::OnUpdateAlignRight)
	ON_COMMAND(ID_ALIGN_TOP, CWinProMoView::OnAlignTop)
	ON_UPDATE_COMMAND_UI(ID_ALIGN_TOP, CWinProMoView::OnUpdateAlignTop)
	ON_COMMAND(ID_EDIT_GRIDSIZE, CWinProMoView::OnEditGridsize)
	ON_COMMAND(ID_EDIT_CANVASSIZE, CWinProMoView::OnEditCanvassize)
	ON_COMMAND(ID_VIEW_PAGEBREAKS, &CWinProMoView::OnViewPagebreaks)
	ON_UPDATE_COMMAND_UI(ID_VIEW_PAGEBREAKS, &CWinProMoView::OnUpdateViewPagebreaks)
	ON_COMMAND(ID_ZOOM_100, &CWinProMoView::OnZoom100)
	ON_COMMAND(ID_ZOOM_200, &CWinProMoView::OnZoom200)
	ON_COMMAND(ID_ZOOM_50, &CWinProMoView::OnZoom50)
	ON_COMMAND(ID_ZOOM_150, &CWinProMoView::OnZoom150)
	ON_COMMAND(ID_ZOOM_400, &CWinProMoView::OnZoom400)
	ON_COMMAND(ID_ZOOM_75, &CWinProMoView::OnZoom75)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CWinProMoView construction/destruction

CWinProMoView::CWinProMoView()
{
	m_screenResolutionX = 0;
	m_screenResolutionY = 0;
	m_nHorzPages = 0;
	m_nVertPages = 0;
	m_editor = NULL;
}

CProMoEditor* CWinProMoView::GetEditor()
{
	return m_editor;
}

void CWinProMoView::SetPageSize()
{
	CDC dc;
	if (!GetPrinterDC(dc))
	{
		AfxMessageBox(_T("No printer available."));
		return;
	}

	m_editor->SetPageLayout(&dc);
	
	dc.DeleteDC();
}

CWinProMoView::~CWinProMoView()
{
	delete m_editor;
}

BOOL CWinProMoView::PreCreateWindow(CREATESTRUCT& cs)
{
	return CView::PreCreateWindow(cs);
}

void CWinProMoView::OnInitialUpdate()
{
	CView::OnInitialUpdate();

	CreateEditor();

	if (!m_editor->m_hWnd)
	{
		// Creating the editor window
		CWinProMoDoc* pDoc = GetDocument();

		CRect rect;
		GetClientRect(rect);
		m_editor->Create(WS_CHILD | WS_VISIBLE, rect, this, pDoc->GetData());

		// We get the screen resolution, which we will use 
		// for scaling to printer. See also OnDraw.
		CClientDC dc(this);
		m_screenResolutionX = dc.GetDeviceCaps(LOGPIXELSX);
		m_screenResolutionY = dc.GetDeviceCaps(LOGPIXELSY);

		SetPageSize();

		m_editor->SetModified(FALSE);

	}
	else
		m_editor->Clear();
}

/////////////////////////////////////////////////////////////////////////////
// CWinProMoView drawing

void CWinProMoView::OnDraw(CDC* pDC)
{

}

/////////////////////////////////////////////////////////////////////////////
// CWinProMoView printing

BOOL CWinProMoView::OnPreparePrinting(CPrintInfo* pInfo)
{	
	CDC dc;
	if (!GetPrinterDC(dc))
	{
		AfxMessageBox(_T("No printer available."));
		return FALSE;
	}

	if (m_editor)
	{
		// Virtual size in logical units
		CSize virtSize = m_editor->GetVirtualSize();

		if (pInfo) {

			// Scale with printer resolution / screen resolution
			double wzoom = (double)dc.GetDeviceCaps(LOGPIXELSX) / m_screenResolutionX;
			double hzoom = (double)dc.GetDeviceCaps(LOGPIXELSY) / m_screenResolutionY;
			int virtWidth = (int)round(virtSize.cx * wzoom);
			int virtHeight = (int)round(virtSize.cy * hzoom);

			CSize paperSize;
			paperSize.cx = dc.GetDeviceCaps(HORZRES);
			paperSize.cy = dc.GetDeviceCaps(VERTRES);

			m_nHorzPages = (virtWidth + paperSize.cx - 1) / paperSize.cx;
			m_nVertPages = (virtHeight + paperSize.cy - 1) / paperSize.cy;

			int totalPages = m_nHorzPages * m_nVertPages;

			pInfo->SetMaxPage(totalPages);
			pInfo->m_nCurPage = 1; // start at first page
		}
	}

	dc.DeleteDC();

	// default preparation
	return DoPreparePrinting(pInfo);
}

void CWinProMoView::OnPrint(CDC* pDC, CPrintInfo* pInfo)
{
	if (!m_editor)
		return;

	double zoom = (double)pDC->GetDeviceCaps(LOGPIXELSX) / m_screenResolutionX;

	// total rect = entire diagram in printer coords
	CRect totalRect(0, 0,
		(int)(m_editor->GetVirtualSize().cx * zoom),
		(int)(m_editor->GetVirtualSize().cy * zoom));

	// Determine current page index
	int pageIndex = pInfo->m_nCurPage - 1; // 0-based
	int pageX = pageIndex % m_nHorzPages;
	int pageY = pageIndex / m_nHorzPages;

	int pageWidth = pDC->GetDeviceCaps(HORZRES);
	int pageHeight = pDC->GetDeviceCaps(VERTRES);

	int offsetX = pageX * pageWidth;
	int offsetY = pageY * pageHeight;

	// Clip to page area
	CRect clipRect(0, 0, pageWidth, pageHeight);
	pDC->SaveDC();  // save state so we can restore later
	pDC->IntersectClipRect(&clipRect);

	// Shift origin so that Print() draws the right slice
	pDC->SetWindowOrg(offsetX, offsetY);

	COLORREF col = m_editor->GetBackgroundColor();
	m_editor->SetRedraw(FALSE);
	m_editor->SetBackgroundColor(RGB(255, 255, 255));
	m_editor->Print(pDC, totalRect, zoom);
	m_editor->SetBackgroundColor(col);
	m_editor->SetRedraw(TRUE);

	pDC->RestoreDC(-1); // restore to original

}


void CWinProMoView::OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo)
{
	

}

void CWinProMoView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

void CWinProMoView::OnFilePrintPreview()
{
	CDC dc;
	if (!GetPrinterDC(dc))
	{
		AfxMessageBox(_T("No printer available."));
		return; 
	}
	CView::OnFilePrintPreview();
}

/////////////////////////////////////////////////////////////////////////////
// CWinProMoView diagnostics

#ifdef _DEBUG
void CWinProMoView::AssertValid() const
{
	CView::AssertValid();
}

void CWinProMoView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

void CWinProMoView::CreateEditor()
{
	if (!m_editor) {
		m_editor = new CProMoEditor;
	}
}

BOOL CWinProMoView::GetPrinterDC(CDC& dc)
{
	// First try via application (respects user’s print setup)
	AfxGetApp()->CreatePrinterDC(dc);
	if (dc.GetSafeHdc())
		return TRUE;

	// Fallback: try defaults via CPrintDialog
	CPrintDialog dlg(FALSE);
	if (dlg.GetDefaults())
	{
		HDC hPrinterDC = dlg.GetPrinterDC();
		if (hPrinterDC)
		{
			dc.Attach(hPrinterDC);
			return TRUE;
		}
	}

	// Nothing available
	return FALSE;
}

void CWinProMoView::OnSize(UINT nType, int cx, int cy)
{
	CView::OnSize(nType, cx, cy);

	if (m_editor) {
		if (m_editor->m_hWnd)
			m_editor->MoveWindow(0, 0, cx, cy);
	}
}

BOOL CWinProMoView::OnEraseBkgnd(CDC* pDC)
{
	return TRUE;
}

void CWinProMoView::OnButtonSnap()
{
	if (m_editor) {
		BOOL snap = !m_editor->GetSnapToGrid();
		m_editor->SetSnapToGrid(snap);
	}
}

// Edit menu
void CWinProMoView::OnEditCopy()
{
	if (m_editor) {
		m_editor->Copy();
	}

}

void CWinProMoView::OnEditCut()
{

	if (m_editor) {
		m_editor->Cut();
	}

}

void CWinProMoView::OnEditPaste()
{

	if (m_editor) {
		m_editor->Paste();
	}

}

void CWinProMoView::OnEditUndo()
{

	if (m_editor) {
		m_editor->Undo();
	}

}

void CWinProMoView::OnUpdateEditUndo(CCmdUI* pCmdUI)
{

	if (m_editor) {
		m_editor->UpdateUndo(pCmdUI);
	}

}

void CWinProMoView::OnUpdateEditCopy(CCmdUI* pCmdUI)
{

	if (m_editor) {
		m_editor->UpdateCopy(pCmdUI);
	}

}

void CWinProMoView::OnUpdateEditCut(CCmdUI* pCmdUI)
{

	if (m_editor) {
		m_editor->UpdateCut(pCmdUI);
	}

}

void CWinProMoView::OnUpdateEditPaste(CCmdUI* pCmdUI)
{

	if (m_editor) {
		m_editor->UpdatePaste(pCmdUI);
	}

}

void CWinProMoView::OnUpdateButtonSnap(CCmdUI* pCmdUI)
{

	if (m_editor) {
		pCmdUI->SetCheck(m_editor->GetSnapToGrid());
		pCmdUI->Enable(m_editor->IsGridVisible());
	}

}

CWinProMoDoc* CWinProMoView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CWinProMoDoc)));
	return (CWinProMoDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CWinProMoView message handlers

void CWinProMoView::OnEditDelete()
{
	if (m_editor) {
		m_editor->DeleteAllSelected();
	}
}

void CWinProMoView::OnUpdateEditDelete(CCmdUI* pCmdUI)
{
	if (m_editor) {
		m_editor->UpdateDelete(pCmdUI);
	}
}


void CWinProMoView::OnArrangeGroup()
{
	if (m_editor) {
		m_editor->Group();
	}
}


void CWinProMoView::OnUpdateArrangeGroup(CCmdUI* pCmdUI)
{
	if (m_editor) {
		m_editor->UpdateGroup(pCmdUI);
	}
}


void CWinProMoView::OnArrangeUngroup()
{
	if (m_editor) {
		m_editor->Ungroup();
	}
}


void CWinProMoView::OnUpdateArrangeUngroup(CCmdUI* pCmdUI)
{
	if (m_editor) {
		m_editor->UpdateUngroup(pCmdUI);
	}
}


void CWinProMoView::OnViewGrid()
{
	if (m_editor) {
		BOOL grid = !m_editor->IsGridVisible();
		m_editor->ShowGrid(grid);
	}
}


void CWinProMoView::OnUpdateViewGrid(CCmdUI* pCmdUI)
{
	if (m_editor) {
		pCmdUI->SetCheck(m_editor->IsGridVisible());
		pCmdUI->Enable(!m_editor->GetSnapToGrid());
	}
}


void CWinProMoView::OnAlignBottom()
{
	if (m_editor) {
		m_editor->BottomAlignSelected();
	}
}


void CWinProMoView::OnUpdateAlignBottom(CCmdUI* pCmdUI)
{
	if (m_editor) {
		m_editor->UpdateGroup(pCmdUI);
	}
}


void CWinProMoView::OnUpdateAlignCenter(CCmdUI* pCmdUI)
{
	// TODO: Add your command handler code here
}


void CWinProMoView::OnAlignCenter()
{
	// TODO: Add your command handler code here
}


void CWinProMoView::OnAlignLeft()
{
	m_editor->LeftAlignSelected();
}


void CWinProMoView::OnUpdateAlignLeft(CCmdUI* pCmdUI)
{
	if (m_editor) {
		m_editor->UpdateGroup(pCmdUI);
	}
}


void CWinProMoView::OnAlignMiddle()
{
	// TODO: Add your command handler code here
}


void CWinProMoView::OnUpdateAlignMiddle(CCmdUI* pCmdUI)
{
	// TODO: Add your command handler code here
}


void CWinProMoView::OnAlignRight()
{
	m_editor->RightAlignSelected();
}


void CWinProMoView::OnUpdateAlignRight(CCmdUI* pCmdUI)
{
	if (m_editor) {
		m_editor->UpdateGroup(pCmdUI);
	}
}


void CWinProMoView::OnAlignTop()
{
	m_editor->TopAlignSelected();
}


void CWinProMoView::OnUpdateAlignTop(CCmdUI* pCmdUI)
{
	if (m_editor) {
		m_editor->UpdateGroup(pCmdUI);
	}
}


void CWinProMoView::OnEditGridsize()
{
	if (m_editor) {
		CGridSizeDialog	dlg;

		dlg.m_width = m_editor->GetGridSize().cx;
		dlg.m_height = m_editor->GetGridSize().cy;
		if (dlg.DoModal() == IDOK)
			m_editor->SetGridSize(CSize(dlg.m_width, dlg.m_height));
	}
}


void CWinProMoView::OnEditCanvassize()
{
	if (m_editor) {
		CCanvasSizeDialog	dlg;

		dlg.m_width = m_editor->GetVirtualSize().cx;
		dlg.m_height = m_editor->GetVirtualSize().cy;
		if (dlg.DoModal() == IDOK)
			m_editor->SetVirtualSize(CSize(dlg.m_width, dlg.m_height));
	}
}


void CWinProMoView::OnViewPagebreaks()
{
	if (m_editor) {
		BOOL breaks = !m_editor->IsPageBreaksVisible();
		m_editor->ShowPageBreaks(breaks);
	}
}


void CWinProMoView::OnUpdateViewPagebreaks(CCmdUI* pCmdUI)
{
	if (m_editor) {
		pCmdUI->SetCheck(m_editor->IsPageBreaksVisible());
	}
}


void CWinProMoView::OnZoom100()
{
	if (m_editor) {
		m_editor->SetZoom(1.0);
	}
}


void CWinProMoView::OnZoom200()
{
	if (m_editor) {
		m_editor->SetZoom(2.0);
	}
}


void CWinProMoView::OnZoom50()
{
	if (m_editor) {
		m_editor->SetZoom(0.5);
	}
}


void CWinProMoView::OnZoom150()
{
	if (m_editor) {
		m_editor->SetZoom(1.5);
	}
}


void CWinProMoView::OnZoom400()
{
	if (m_editor) {
		m_editor->SetZoom(4.0);
	}
}


void CWinProMoView::OnZoom75()
{
	if (m_editor) {
		m_editor->SetZoom(0.75);
	}
}
