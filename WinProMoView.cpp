/* ==========================================================================
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
	ON_COMMAND(ID_VIEW_SNAPTOGRID, OnButtonSnap)
	ON_UPDATE_COMMAND_UI(ID_VIEW_SNAPTOGRID, OnUpdateButtonSnap)
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CView::OnFilePrintPreview)
	ON_COMMAND(ID_EDIT_DELETE, &CWinProMoView::OnEditDelete)
	ON_UPDATE_COMMAND_UI(ID_EDIT_DELETE, &CWinProMoView::OnUpdateEditDelete)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CWinProMoView construction/destruction

CWinProMoView::CWinProMoView()
{
	m_screenResolutionX = 0;
	m_screenResolutionY = 0;
	m_editor = NULL;
}

CProMoEditor* CWinProMoView::GetEditor()
{
	return m_editor;
}

void CWinProMoView::SetPageSize()
{
	CPrintDialog dlg(FALSE);
	if (dlg.GetDefaults())
	{
		CDC dc;
		dc.Attach(dlg.GetPrinterDC());

		if (m_editor) {
			m_editor->SetPageLayout(&dc);
		}

		dc.Detach();
		
	}
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
	CWinProMoDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	if (m_editor) {
		if (pDC->IsPrinting())
		{

			COLORREF col = m_editor->GetBackgroundColor();
			// Print zoom is the difference between screen- 
			// and printer resolution.
			double zoom = pDC->GetDeviceCaps(LOGPIXELSX);
			zoom = zoom / m_screenResolutionX;

			CRect rect(0, 0,
				(int)((double)m_editor->GetVirtualSize().cx * zoom),
				(int)((double)m_editor->GetVirtualSize().cy * zoom));
			m_editor->SetRedraw(FALSE);
			m_editor->SetBackgroundColor(RGB(255, 255, 255));
			m_editor->Print(pDC, rect, zoom);
			m_editor->SetBackgroundColor(col);
			m_editor->SetRedraw(TRUE);

		}

	}
}

/////////////////////////////////////////////////////////////////////////////
// CWinProMoView printing

BOOL CWinProMoView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CWinProMoView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CWinProMoView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
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
		m_editor->ShowGrid(snap);
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
