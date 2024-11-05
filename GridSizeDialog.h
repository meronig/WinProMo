#if !defined(AFX_GRIDSIZEDIALOG_H__5BA59EE8_C3CA_4FA1_AE65_53EAB2552C63__INCLUDED_)
#define AFX_GRIDSIZEDIALOG_H__5BA59EE8_C3CA_4FA1_AE65_53EAB2552C63__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// GridSizeDialog.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CGridSizeDialog dialog

class CGridSizeDialog : public CDialog
{
// Construction
public:
	CGridSizeDialog(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CGridSizeDialog)
	enum { IDD = IDD_DIALOG_GRID_SIZE };
	int		m_height;
	int		m_width;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CGridSizeDialog)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CGridSizeDialog)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_GRIDSIZEDIALOG_H__5BA59EE8_C3CA_4FA1_AE65_53EAB2552C63__INCLUDED_)
