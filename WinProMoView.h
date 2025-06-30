// WinProMoView.h : interface of the CWinProMoView class
//
/////////////////////////////////////////////////////////////////////////////
#ifndef _WINPROMOVIEW_H_
#define _WINPROMOVIEW_H_

#include "stdafx.h"
#include "./ProMoEditor/ProMoEditor.h"
#include "WinProMoDoc.h"

class AFX_EXT_CLASS CWinProMoView : public CView
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

protected:
	virtual void CreateEditor();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CWinProMoView)
public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	virtual void OnInitialUpdate();
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);
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
	//}}AFX_MSG
	//Commands
	DECLARE_MESSAGE_MAP()

protected:
	// Private data
	CProMoEditor*	m_editor;
	int				m_screenResolutionX;

};

#ifndef _DEBUG  // debug version in WinProMoView.cpp
inline CWinProMoDoc* CWinProMoView::GetDocument()
   { return (CWinProMoDoc*)m_pDocument; }
#endif

#endif //_WINPROMOVIEW_H_
/////////////////////////////////////////////////////////////////////////////
