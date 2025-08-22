/* ==========================================================================

	Copyright © 2025 Technical University of Denmark

	Author :		Giovanni Meroni

   ========================================================================*/
// WinProMoView.h : interface of the CWinProMoView class
//
/////////////////////////////////////////////////////////////////////////////
#ifndef _WINPROMOVIEW_H_
#define _WINPROMOVIEW_H_

#include "stdafx.h"
#include "./ProMoEditor/ProMoEditor.h"
#include "WinProMoDoc.h"

class WINPROMO_API CWinProMoView : public CView
{
public: // create from serialization only
	DECLARE_DYNCREATE(CWinProMoView)

// Attributes
public:
	CWinProMoDoc* GetDocument();

// Operations
public:
	CWinProMoView();
	CProMoEditor* GetEditor();
	void SetPageSize();
	virtual BOOL GetPrinterDC(CDC& dc);

protected:
	virtual void CreateEditor();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CWinProMoView)
public:
	virtual void OnDraw(CDC* pDC);
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	virtual void OnInitialUpdate();
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnPrint(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnFilePrintPreview();
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CWinProMoView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif


// Generated message map functions
protected:
	//{{AFX_MSG(CWinProMoView)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnEditCopy();
	afx_msg void OnUpdateEditCopy(CCmdUI* pCmdUI);
	afx_msg void OnEditCut();
	afx_msg void OnUpdateEditCut(CCmdUI* pCmdUI);
	afx_msg void OnEditPaste();
	afx_msg void OnUpdateEditPaste(CCmdUI* pCmdUI);
	afx_msg void OnEditUndo();
	afx_msg void OnUpdateEditUndo(CCmdUI* pCmdUI);
	afx_msg void OnButtonSnap();
	afx_msg void OnUpdateButtonSnap(CCmdUI* pCmdUI);
	afx_msg void OnEditDelete();
	afx_msg void OnUpdateEditDelete(CCmdUI* pCmdUI);
	//}}AFX_MSG
	//Commands
	DECLARE_MESSAGE_MAP()

protected:
	// Private data
	CProMoEditor*	m_editor;
	int				m_screenResolutionX;
	int				m_screenResolutionY;
	int				m_nHorzPages;
	int				m_nVertPages;
public:
	afx_msg void OnArrangeGroup();
	afx_msg void OnUpdateArrangeGroup(CCmdUI* pCmdUI);
	afx_msg void OnArrangeUngroup();
	afx_msg void OnUpdateArrangeUngroup(CCmdUI* pCmdUI);
	afx_msg void OnViewGrid();
	afx_msg void OnUpdateViewGrid(CCmdUI* pCmdUI);
	afx_msg void OnAlignBottom();
	afx_msg void OnUpdateAlignBottom(CCmdUI* pCmdUI);
	afx_msg void OnUpdateAlignCenter(CCmdUI* pCmdUI);
	afx_msg void OnAlignCenter();
	afx_msg void OnAlignLeft();
	afx_msg void OnUpdateAlignLeft(CCmdUI* pCmdUI);
	afx_msg void OnAlignMiddle();
	afx_msg void OnUpdateAlignMiddle(CCmdUI* pCmdUI);
	afx_msg void OnAlignRight();
	afx_msg void OnUpdateAlignRight(CCmdUI* pCmdUI);
	afx_msg void OnAlignTop();
	afx_msg void OnUpdateAlignTop(CCmdUI* pCmdUI);
	afx_msg void OnEditGridsize();
	afx_msg void OnEditCanvassize();
	afx_msg void OnViewPagebreaks();
	afx_msg void OnUpdateViewPagebreaks(CCmdUI* pCmdUI);
	afx_msg void OnZoom100();
	afx_msg void OnZoom200();
	afx_msg void OnZoom50();
	afx_msg void OnZoom150();
	afx_msg void OnZoom400();
	afx_msg void OnZoom75();
};

#ifndef _DEBUG  // debug version in WinProMoView.cpp
inline CWinProMoDoc* CWinProMoView::GetDocument()
   { return (CWinProMoDoc*)m_pDocument; }
#endif

#endif //_WINPROMOVIEW_H_
/////////////////////////////////////////////////////////////////////////////
