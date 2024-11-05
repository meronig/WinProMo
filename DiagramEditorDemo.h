// DiagramEditorDemo.h : main header file for the DIAGRAMEDITORDEMO application
//

#if !defined(AFX_DIAGRAMEDITORDEMO_H__B51B11E1_660E_4012_8888_AD056B3E630F__INCLUDED_)
#define AFX_DIAGRAMEDITORDEMO_H__B51B11E1_660E_4012_8888_AD056B3E630F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols


/////////////////////////////////////////////////////////////////////////////
// CDiagramEditorDemoApp:
// See DiagramEditorDemo.cpp for the implementation of this class
//

class CDiagramEditorDemoApp : public CWinApp
{
public:
	CDiagramEditorDemoApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDiagramEditorDemoApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CDiagramEditorDemoApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DIAGRAMEDITORDEMO_H__B51B11E1_660E_4012_8888_AD056B3E630F__INCLUDED_)
