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
	ON_COMMAND(ID_EDIT_REDO, &CWinProMoView::OnEditRedo)
	ON_UPDATE_COMMAND_UI(ID_EDIT_REDO, &CWinProMoView::OnUpdateEditRedo)
	ON_COMMAND(ID_FORMAT_FONT, &CWinProMoView::OnFormatFont)
	ON_UPDATE_COMMAND_UI(ID_FORMAT_FONT, &CWinProMoView::OnUpdateFormatFont)
	ON_COMMAND(ID_ALIGNMENT_BOTTOM, &CWinProMoView::OnAlignmentBottom)
	ON_COMMAND(ID_ALIGNMENT_CENTER, &CWinProMoView::OnAlignmentCenter)
	ON_COMMAND(ID_ALIGNMENT_LEFT, &CWinProMoView::OnAlignmentLeft)
	ON_COMMAND(ID_ALIGNMENT_MIDDLE, &CWinProMoView::OnAlignmentMiddle)
	ON_COMMAND(ID_ALIGNMENT_MULTILINE, &CWinProMoView::OnAlignmentMultiline)
	ON_COMMAND(ID_ALIGNMENT_RIGHT, &CWinProMoView::OnAlignmentRight)
	ON_COMMAND(ID_ALIGNMENT_TOP, &CWinProMoView::OnAlignmentTop)
	ON_UPDATE_COMMAND_UI(ID_ALIGNMENT_BOTTOM, &CWinProMoView::OnUpdateAlignmentBottom)
	ON_UPDATE_COMMAND_UI(ID_ALIGNMENT_CENTER, &CWinProMoView::OnUpdateAlignmentCenter)
	ON_UPDATE_COMMAND_UI(ID_ALIGNMENT_LEFT, &CWinProMoView::OnUpdateAlignmentLeft)
	ON_UPDATE_COMMAND_UI(ID_ALIGNMENT_MIDDLE, &CWinProMoView::OnUpdateAlignmentMiddle)
	ON_UPDATE_COMMAND_UI(ID_ALIGNMENT_MULTILINE, &CWinProMoView::OnUpdateAlignmentMultiline)
	ON_UPDATE_COMMAND_UI(ID_ALIGNMENT_RIGHT, &CWinProMoView::OnUpdateAlignmentRight)
	ON_UPDATE_COMMAND_UI(ID_ALIGNMENT_TOP, &CWinProMoView::OnUpdateAlignmentTop)
	ON_COMMAND(ID_BACKGROUND_COLOR, &CWinProMoView::OnBackgroundColor)
	ON_UPDATE_COMMAND_UI(ID_BACKGROUND_COLOR, &CWinProMoView::OnUpdateBackgroundColor)
	ON_COMMAND(ID_BACKGROUND_TRANSPARENT, &CWinProMoView::OnBackgroundTransparent)
	ON_UPDATE_COMMAND_UI(ID_BACKGROUND_TRANSPARENT, &CWinProMoView::OnUpdateBackgroundTransparent)
	ON_COMMAND(ID_FILL_COLOR, &CWinProMoView::OnFillColor)
	ON_UPDATE_COMMAND_UI(ID_FILL_COLOR, &CWinProMoView::OnUpdateFillColor)
	ON_COMMAND(ID_PATTERN_CROSSHATCH, &CWinProMoView::OnPatternCrosshatch)
	ON_UPDATE_COMMAND_UI(ID_PATTERN_CROSSHATCH, &CWinProMoView::OnUpdatePatternCrosshatch)
	ON_COMMAND(ID_PATTERN_DIAGONALCROSSHATCH, &CWinProMoView::OnPatternDiagonalcrosshatch)
	ON_UPDATE_COMMAND_UI(ID_PATTERN_DIAGONALCROSSHATCH, &CWinProMoView::OnUpdatePatternDiagonalcrosshatch)
	ON_COMMAND(ID_PATTERN_DIAGONALLEFT, &CWinProMoView::OnPatternDiagonalleft)
	ON_UPDATE_COMMAND_UI(ID_PATTERN_DIAGONALLEFT, &CWinProMoView::OnUpdatePatternDiagonalleft)
	ON_COMMAND(ID_PATTERN_DIAGONALRIGHT, &CWinProMoView::OnPatternDiagonalright)
	ON_UPDATE_COMMAND_UI(ID_PATTERN_DIAGONALRIGHT, &CWinProMoView::OnUpdatePatternDiagonalright)
	ON_COMMAND(ID_PATTERN_HORIZONTAL, &CWinProMoView::OnPatternHorizontal)
	ON_UPDATE_COMMAND_UI(ID_PATTERN_HORIZONTAL, &CWinProMoView::OnUpdatePatternHorizontal)
	ON_COMMAND(ID_PATTERN_SOLID, &CWinProMoView::OnPatternSolid)
	ON_UPDATE_COMMAND_UI(ID_PATTERN_SOLID, &CWinProMoView::OnUpdatePatternSolid)
	ON_COMMAND(ID_PATTERN_VERTICAL, &CWinProMoView::OnPatternVertical)
	ON_UPDATE_COMMAND_UI(ID_PATTERN_VERTICAL, &CWinProMoView::OnUpdatePatternVertical)
	ON_COMMAND(ID_LINE_COLOR, &CWinProMoView::OnLineColor)
	ON_UPDATE_COMMAND_UI(ID_LINE_COLOR, &CWinProMoView::OnUpdateLineColor)
	ON_COMMAND(ID_STYLE_SOLID, &CWinProMoView::OnStyleSolid)
	ON_UPDATE_COMMAND_UI(ID_STYLE_SOLID, &CWinProMoView::OnUpdateStyleSolid)
	ON_COMMAND(ID_STYLE_DOTTED, &CWinProMoView::OnStyleDotted)
	ON_UPDATE_COMMAND_UI(ID_STYLE_DOTTED, &CWinProMoView::OnUpdateStyleDotted)
	ON_COMMAND(ID_STYLE_DASHED, &CWinProMoView::OnStyleDashed)
	ON_UPDATE_COMMAND_UI(ID_STYLE_DASHED, &CWinProMoView::OnUpdateStyleDashed)
	ON_COMMAND(ID_STYLE_DOTDASHDOTTED, &CWinProMoView::OnStyleDotdashdotted)
	ON_UPDATE_COMMAND_UI(ID_STYLE_DOTDASHDOTTED, &CWinProMoView::OnUpdateStyleDotdashdotted)
	ON_COMMAND(ID_STYLE_DASHDOTTED, &CWinProMoView::OnStyleDashdotted)
	ON_UPDATE_COMMAND_UI(ID_STYLE_DASHDOTTED, &CWinProMoView::OnUpdateStyleDashdotted)
	ON_COMMAND(ID_WIDTH_1PT, &CWinProMoView::OnWidth1pt)
	ON_UPDATE_COMMAND_UI(ID_WIDTH_1PT, &CWinProMoView::OnUpdateWidth1pt)
	ON_COMMAND(ID_WIDTH_2PT, &CWinProMoView::OnWidth2pt)
	ON_UPDATE_COMMAND_UI(ID_WIDTH_2PT, &CWinProMoView::OnUpdateWidth2pt)
	ON_COMMAND(ID_WIDTH_4PT, &CWinProMoView::OnWidth4pt)
	ON_UPDATE_COMMAND_UI(ID_WIDTH_4PT, &CWinProMoView::OnUpdateWidth4pt)
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


CWinProMoDoc* CWinProMoView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CWinProMoDoc)));
	return (CWinProMoDoc*)m_pDocument;
}

#endif //_DEBUG

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


void CWinProMoView::OnEditRedo()
{
	if (m_editor) {
		m_editor->Redo();
	}
}


void CWinProMoView::OnUpdateEditRedo(CCmdUI* pCmdUI)
{
	if (m_editor) {
		m_editor->UpdateRedo(pCmdUI);
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
		pCmdUI->Enable(m_editor->IsAnyObjectSelected());
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
	if (m_editor) {
		m_editor->UpdateGroup(pCmdUI);
	}
}


void CWinProMoView::OnAlignCenter()
{
	if (m_editor) {
		m_editor->CenterAlignSelected();
	}
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
	if (m_editor) {
		m_editor->MiddleAlignSelected();
	}
}


void CWinProMoView::OnUpdateAlignMiddle(CCmdUI* pCmdUI)
{
	if (m_editor) {
		m_editor->UpdateGroup(pCmdUI);
	}
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

void CWinProMoView::OnFormatFont()
{
	if (m_editor) {
		CClientDC dc(this);
		LOGFONT lf = { 0 };  // zero-initialize

		lf.lfHeight = -MulDiv(m_editor->GetFontSize(), GetDeviceCaps(dc, LOGPIXELSY), 72);

		// Weight
		lf.lfWeight = m_editor->GetFontWeight();

		// Style flags
		lf.lfItalic = m_editor->IsFontItalic();
		lf.lfUnderline = m_editor->IsFontUnderline();
		lf.lfStrikeOut = m_editor->IsFontStrikeOut();

		// Charset (use DEFAULT_CHARSET unless you need otherwise)
		lf.lfCharSet = DEFAULT_CHARSET;

		// Font face name
#if _MSC_VER >= 1500
		_tcsncpy_s(lf.lfFaceName, LF_FACESIZE, m_editor->GetFontName(), _TRUNCATE);
#else
		_tcsncpy(lf.lfFaceName, m_editor->GetFontName(), LF_FACESIZE - 1);
		lf.lfFaceName[LF_FACESIZE - 1] = _T('\0');
#endif

		CFontDialog dlg(&lf, CF_EFFECTS | CF_SCREENFONTS, NULL, AfxGetMainWnd());
		dlg.m_cf.rgbColors = m_editor->GetTextColor();

		if (dlg.DoModal() == IDOK)
		{
			m_editor->SetFontName(dlg.GetFaceName());
			m_editor->SetFontSize(dlg.GetSize()/10);
			m_editor->SetFontWeight(dlg.GetWeight());
			m_editor->SetFontItalic(dlg.IsItalic());
			m_editor->SetFontUnderline(dlg.IsUnderline());
			m_editor->SetFontStrikeOut(dlg.IsStrikeOut());
			m_editor->SetTextColor(dlg.GetColor());
		}
	}
}

void CWinProMoView::OnUpdateFormatFont(CCmdUI* pCmdUI)
{
	if (m_editor) {
		pCmdUI->Enable(m_editor->IsAnyObjectSelected());
	}
}

void CWinProMoView::OnAlignmentBottom()
{
	if (m_editor) {
		m_editor->SetTextVerticalAlignment(DT_BOTTOM);	
	}
}

void CWinProMoView::OnAlignmentCenter()
{
	if (m_editor) {
		m_editor->SetTextHorizontalAlignment(DT_CENTER);
	}
}

void CWinProMoView::OnAlignmentLeft()
{
	if (m_editor) {
		m_editor->SetTextHorizontalAlignment(DT_LEFT);
	}
}

void CWinProMoView::OnAlignmentMiddle()
{
	if (m_editor) {
		m_editor->SetTextVerticalAlignment(DT_VCENTER);
	}
}

void CWinProMoView::OnAlignmentMultiline()
{
	if (m_editor) {
		if (m_editor->HasTextAlignmentFlag(DT_WORDBREAK)) {
			m_editor->SetTextAlignmentFlag(DT_SINGLELINE, TRUE);
		}
		else {
			m_editor->SetTextAlignmentFlag(DT_WORDBREAK, TRUE);
		}
	}
}

void CWinProMoView::OnAlignmentRight()
{
	if (m_editor) {
		m_editor->SetTextHorizontalAlignment(DT_RIGHT);
	}
}

void CWinProMoView::OnAlignmentTop()
{
	if (m_editor) {
		m_editor->SetTextVerticalAlignment(DT_TOP);
	}
}

void CWinProMoView::OnUpdateAlignmentBottom(CCmdUI* pCmdUI)
{
	if (m_editor) {
		pCmdUI->Enable(m_editor->IsAnyObjectSelected() && !m_editor->IsLocked(LOCK_ALIGNMENT));
		pCmdUI->SetCheck(m_editor->GetTextVerticalAlignment() == DT_BOTTOM);
	}
}

void CWinProMoView::OnUpdateAlignmentCenter(CCmdUI* pCmdUI)
{
	if (m_editor) {
		pCmdUI->Enable(m_editor->IsAnyObjectSelected() && !m_editor->IsLocked(LOCK_ALIGNMENT));
		pCmdUI->SetCheck(m_editor->GetTextHorizontalAlignment() == DT_CENTER);
	}
}

void CWinProMoView::OnUpdateAlignmentLeft(CCmdUI* pCmdUI)
{
	if (m_editor) {
		pCmdUI->Enable(m_editor->IsAnyObjectSelected() && !m_editor->IsLocked(LOCK_ALIGNMENT));
		pCmdUI->SetCheck(m_editor->GetTextHorizontalAlignment() == DT_LEFT);
	}
}

void CWinProMoView::OnUpdateAlignmentMiddle(CCmdUI* pCmdUI)
{
	if (m_editor) {
		pCmdUI->Enable(m_editor->IsAnyObjectSelected() && !m_editor->IsLocked(LOCK_ALIGNMENT));
		pCmdUI->SetCheck(m_editor->GetTextVerticalAlignment() == DT_VCENTER);
	}
}

void CWinProMoView::OnUpdateAlignmentMultiline(CCmdUI* pCmdUI)
{
	if (m_editor) {
		pCmdUI->Enable(m_editor->IsAnyObjectSelected() && !m_editor->IsLocked(LOCK_ALIGNMENT));
		pCmdUI->SetCheck(m_editor->HasTextAlignmentFlag(DT_WORDBREAK));
	}
}

void CWinProMoView::OnUpdateAlignmentRight(CCmdUI* pCmdUI)
{
	if (m_editor) {
		pCmdUI->Enable(m_editor->IsAnyObjectSelected() && !m_editor->IsLocked(LOCK_ALIGNMENT));
		pCmdUI->SetCheck(m_editor->GetTextHorizontalAlignment() == DT_RIGHT);
	}
}

void CWinProMoView::OnUpdateAlignmentTop(CCmdUI* pCmdUI)
{
	if (m_editor) {
		pCmdUI->Enable(m_editor->IsAnyObjectSelected() && !m_editor->IsLocked(LOCK_ALIGNMENT));
		pCmdUI->SetCheck(m_editor->GetTextVerticalAlignment() == DT_TOP);
	}
}

void CWinProMoView::OnBackgroundColor()
{
	if (m_editor) {
		CColorDialog dlg (m_editor->GetBkColor(), CC_FULLOPEN | CC_RGBINIT, AfxGetMainWnd());
		if (dlg.DoModal() == IDOK)
		{
			m_editor->SetBkColor(dlg.GetColor());
		}
	}
}

void CWinProMoView::OnUpdateBackgroundColor(CCmdUI* pCmdUI)
{
	if (m_editor) {
		pCmdUI->Enable(m_editor->IsAnyObjectSelected() && !m_editor->IsLocked(LOCK_BKCOLOR));
	}
}

void CWinProMoView::OnBackgroundTransparent()
{
	if (m_editor) {
		if (m_editor->GetBkMode() == TRANSPARENT)
			m_editor->SetBkMode(OPAQUE);
		else
			m_editor->SetBkMode(TRANSPARENT);
	}
}

void CWinProMoView::OnUpdateBackgroundTransparent(CCmdUI* pCmdUI)
{
	if (m_editor) {
		pCmdUI->Enable(m_editor->IsAnyObjectSelected() && !m_editor->IsLocked(LOCK_BKMODE));
		pCmdUI->SetCheck(m_editor->GetBkMode() == TRANSPARENT);
	}
}

void CWinProMoView::OnFillColor()
{
	if (m_editor) {
		CColorDialog dlg(m_editor->GetFillColor(), CC_FULLOPEN | CC_RGBINIT, AfxGetMainWnd());
		if (dlg.DoModal() == IDOK)
		{
			m_editor->SetFillColor(dlg.GetColor());
		}
	}
}

void CWinProMoView::OnUpdateFillColor(CCmdUI* pCmdUI)
{
	if (m_editor) {
		if (m_editor->IsAnyBlockSelected()) {
			pCmdUI->Enable(!m_editor->IsLocked(LOCK_FILLCOLOR));
		}
		else {
			pCmdUI->Enable(FALSE);
		}
	}
}

void CWinProMoView::OnPatternCrosshatch()
{
	if (m_editor) {
		m_editor->SetFillPattern(TRUE);
		m_editor->SetFillStyle(HS_CROSS);
	}
}

void CWinProMoView::OnUpdatePatternCrosshatch(CCmdUI* pCmdUI)
{
	if (m_editor) {
		if (m_editor->IsAnyBlockSelected()) {
			pCmdUI->Enable(!m_editor->IsLocked(LOCK_FILLSTYLE));
			pCmdUI->SetCheck((m_editor->GetFillStyle() == HS_CROSS) && m_editor->IsFillPattern());
		}
		else {
			pCmdUI->Enable(FALSE);
			pCmdUI->SetCheck(FALSE);
		}
	}
}

void CWinProMoView::OnPatternDiagonalcrosshatch()
{
	if (m_editor) {
		m_editor->SetFillPattern(TRUE);
		m_editor->SetFillStyle(HS_DIAGCROSS);
	}
}

void CWinProMoView::OnUpdatePatternDiagonalcrosshatch(CCmdUI* pCmdUI)
{
	if (m_editor) {
		if (m_editor->IsAnyBlockSelected()) {
			pCmdUI->Enable(!m_editor->IsLocked(LOCK_FILLSTYLE));
			pCmdUI->SetCheck((m_editor->GetFillStyle() == HS_DIAGCROSS) && m_editor->IsFillPattern());
		}
		else {
			pCmdUI->Enable(FALSE);
			pCmdUI->SetCheck(FALSE);
		}
	}
}

void CWinProMoView::OnPatternDiagonalleft()
{
	if (m_editor) {
		m_editor->SetFillPattern(TRUE);
		m_editor->SetFillStyle(HS_BDIAGONAL);
	}
}

void CWinProMoView::OnUpdatePatternDiagonalleft(CCmdUI* pCmdUI)
{
	if (m_editor) {
		if (m_editor->IsAnyBlockSelected()) {
			pCmdUI->Enable(!m_editor->IsLocked(LOCK_FILLSTYLE));
			pCmdUI->SetCheck((m_editor->GetFillStyle() == HS_BDIAGONAL) && m_editor->IsFillPattern());
		}
		else {
			pCmdUI->Enable(FALSE);
			pCmdUI->SetCheck(FALSE);
		}
	}
}

void CWinProMoView::OnPatternDiagonalright()
{
	if (m_editor) {
		m_editor->SetFillPattern(TRUE);
		m_editor->SetFillStyle(HS_FDIAGONAL);
	}
}

void CWinProMoView::OnUpdatePatternDiagonalright(CCmdUI* pCmdUI)
{
	if (m_editor) {
		if (m_editor->IsAnyBlockSelected()) {
			pCmdUI->Enable(!m_editor->IsLocked(LOCK_FILLSTYLE));
			pCmdUI->SetCheck((m_editor->GetFillStyle() == HS_FDIAGONAL) && m_editor->IsFillPattern());
		}
		else {
			pCmdUI->Enable(FALSE);
			pCmdUI->SetCheck(FALSE);
		}
	}
}

void CWinProMoView::OnPatternHorizontal()
{
	if (m_editor) {
		m_editor->SetFillPattern(TRUE);
		m_editor->SetFillStyle(HS_HORIZONTAL);
	}
}

void CWinProMoView::OnUpdatePatternHorizontal(CCmdUI* pCmdUI)
{
	if (m_editor) {
		if (m_editor->IsAnyBlockSelected()) {
			pCmdUI->Enable(!m_editor->IsLocked(LOCK_FILLSTYLE));
			pCmdUI->SetCheck((m_editor->GetFillStyle() == HS_HORIZONTAL) && m_editor->IsFillPattern());
		}
		else {
			pCmdUI->Enable(FALSE);
			pCmdUI->SetCheck(FALSE);
		}
	}
}

void CWinProMoView::OnPatternSolid()
{
	if (m_editor) {
		m_editor->SetFillPattern(FALSE);
	}
}

void CWinProMoView::OnUpdatePatternSolid(CCmdUI* pCmdUI)
{
	if (m_editor) {
		if (m_editor->IsAnyBlockSelected()) {
			pCmdUI->Enable(!m_editor->IsLocked(LOCK_FILLSTYLE));
			pCmdUI->SetCheck(!m_editor->IsFillPattern());
		}
		else {
			pCmdUI->Enable(FALSE);
			pCmdUI->SetCheck(FALSE);
		}
	}
}

void CWinProMoView::OnPatternVertical()
{
	if (m_editor) {
		m_editor->SetFillPattern(TRUE);
		m_editor->SetFillStyle(HS_VERTICAL);
	}
}

void CWinProMoView::OnUpdatePatternVertical(CCmdUI* pCmdUI)
{
	if (m_editor) {
		if (m_editor->IsAnyBlockSelected()) {
			pCmdUI->Enable(!m_editor->IsLocked(LOCK_FILLSTYLE));
			pCmdUI->SetCheck((m_editor->GetFillStyle() == HS_VERTICAL) && m_editor->IsFillPattern());
		}
		else {
			pCmdUI->Enable(FALSE);
			pCmdUI->SetCheck(FALSE);
		}
	}
}

void CWinProMoView::OnLineColor()
{
	if (m_editor) {
		CColorDialog dlg(m_editor->GetLineColor(), CC_FULLOPEN | CC_RGBINIT, AfxGetMainWnd());
		if (dlg.DoModal() == IDOK)
		{
			m_editor->SetLineColor(dlg.GetColor());
		}
	}
}

void CWinProMoView::OnUpdateLineColor(CCmdUI* pCmdUI)
{
	if (m_editor) {
		if (m_editor->IsAnyEdgeSelected() || m_editor->IsAnyBlockSelected()) {
			pCmdUI->Enable(!m_editor->IsLocked(LOCK_LINECOLOR));
		}
		else {
			pCmdUI->Enable(FALSE);
		}
	}
}

void CWinProMoView::OnStyleSolid()
{
	if (m_editor) {
		m_editor->SetLineStyle(PS_SOLID);
	}
}

void CWinProMoView::OnUpdateStyleSolid(CCmdUI* pCmdUI)
{
	if (m_editor) {
		if (m_editor->IsAnyEdgeSelected() || m_editor->IsAnyBlockSelected()) {
			pCmdUI->Enable(!m_editor->IsLocked(LOCK_LINESTYLE) && m_editor->GetLineWidth() == 1);
			pCmdUI->SetCheck((m_editor->GetLineStyle() == PS_SOLID) || m_editor->GetLineWidth() != 1);
		}
		else {
			pCmdUI->Enable(FALSE);
			pCmdUI->SetCheck(FALSE);
		}
	}
}

void CWinProMoView::OnStyleDotted()
{
	if (m_editor) {
		m_editor->SetLineStyle(PS_DOT);
	}
}

void CWinProMoView::OnUpdateStyleDotted(CCmdUI* pCmdUI)
{
	if (m_editor) {
		if (m_editor->IsAnyEdgeSelected() || m_editor->IsAnyBlockSelected()) {
			pCmdUI->Enable(!m_editor->IsLocked(LOCK_LINESTYLE) && m_editor->GetLineWidth() == 1);
			pCmdUI->SetCheck((m_editor->GetLineStyle() == PS_DOT) && m_editor->GetLineWidth() == 1);
		}
		else {
			pCmdUI->Enable(FALSE);
			pCmdUI->SetCheck(FALSE);
		}
	}
}

void CWinProMoView::OnStyleDashed()
{
	if (m_editor) {
		m_editor->SetLineStyle(PS_DASH);
	}
}

void CWinProMoView::OnUpdateStyleDashed(CCmdUI* pCmdUI)
{
	if (m_editor) {
		if (m_editor->IsAnyEdgeSelected() || m_editor->IsAnyBlockSelected()) {
			pCmdUI->Enable(!m_editor->IsLocked(LOCK_LINESTYLE) && m_editor->GetLineWidth() == 1);
			pCmdUI->SetCheck((m_editor->GetLineStyle() == PS_DASH) && m_editor->GetLineWidth() == 1);
		}
		else {
			pCmdUI->Enable(FALSE);
			pCmdUI->SetCheck(FALSE);
		}
	}
}

void CWinProMoView::OnStyleDotdashdotted()
{
	if (m_editor) {
		m_editor->SetLineStyle(PS_DASHDOTDOT);
	}
}

void CWinProMoView::OnUpdateStyleDotdashdotted(CCmdUI* pCmdUI)
{
	if (m_editor) {
		if (m_editor->IsAnyEdgeSelected() || m_editor->IsAnyBlockSelected()) {
			pCmdUI->Enable(!m_editor->IsLocked(LOCK_LINESTYLE) && m_editor->GetLineWidth() == 1);
			pCmdUI->SetCheck((m_editor->GetLineStyle() == PS_DASHDOTDOT) && m_editor->GetLineWidth() == 1);
		}
		else {
			pCmdUI->Enable(FALSE);
			pCmdUI->SetCheck(FALSE);
		}
	}
}

void CWinProMoView::OnStyleDashdotted()
{
	if (m_editor) {
		m_editor->SetLineStyle(PS_DASHDOT);
	}
}

void CWinProMoView::OnUpdateStyleDashdotted(CCmdUI* pCmdUI)
{
	if (m_editor) {
		if (m_editor->IsAnyEdgeSelected() || m_editor->IsAnyBlockSelected()) {
			pCmdUI->Enable(!m_editor->IsLocked(LOCK_LINESTYLE) && m_editor->GetLineWidth() == 1);
			pCmdUI->SetCheck((m_editor->GetLineStyle() == PS_DASHDOT) && m_editor->GetLineWidth() == 1);
		}
		else {
			pCmdUI->Enable(FALSE);
			pCmdUI->SetCheck(FALSE);
		}
	}
}

void CWinProMoView::OnWidth1pt()
{
	if (m_editor) {
		m_editor->SetLineWidth(1);
	}
}

void CWinProMoView::OnUpdateWidth1pt(CCmdUI* pCmdUI)
{
	if (m_editor) {
		if (m_editor->IsAnyEdgeSelected() || m_editor->IsAnyBlockSelected()) {
			pCmdUI->Enable(!m_editor->IsLocked(LOCK_LINEWIDTH));
			pCmdUI->SetCheck(m_editor->GetLineWidth() == 1);
		}
		else {
			pCmdUI->Enable(FALSE);
			pCmdUI->SetCheck(FALSE);
		}
	}
}

void CWinProMoView::OnWidth2pt()
{
	if (m_editor) {
		m_editor->SetLineWidth(2);
	}
}

void CWinProMoView::OnUpdateWidth2pt(CCmdUI* pCmdUI)
{
	if (m_editor) {
		if (m_editor->IsAnyEdgeSelected() || m_editor->IsAnyBlockSelected()) {
			pCmdUI->Enable(!m_editor->IsLocked(LOCK_LINEWIDTH));
			pCmdUI->SetCheck(m_editor->GetLineWidth() == 2);
		}
		else {
			pCmdUI->Enable(FALSE);
		}
	}
}

void CWinProMoView::OnWidth4pt()
{
	if (m_editor) {
		m_editor->SetLineWidth(4);
	}
}

void CWinProMoView::OnUpdateWidth4pt(CCmdUI* pCmdUI)
{
	if (m_editor) {
		if (m_editor->IsAnyEdgeSelected() || m_editor->IsAnyBlockSelected()) {
			pCmdUI->Enable(!m_editor->IsLocked(LOCK_LINEWIDTH));
			pCmdUI->SetCheck(m_editor->GetLineWidth() == 4);
		}
		else {
			pCmdUI->Enable(FALSE);
		}
	}
}
