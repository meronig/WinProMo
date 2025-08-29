/* ==========================================================================

	Copyright © 2025 Technical University of Denmark

	Author :		Giovanni Meroni

   ========================================================================*/
#if !defined(_AFX_PROPERTYDIALOG_H_)
#define _AFX_PROPERTYDIALOG_H_

#include "../DiagramEditor/DiagramPropertyDlg.h"
#include "../resource.h"

/////////////////////////////////////////////////////////////////////////////
// CPropertyDialog dialog

class AFX_EXT_CLASS CPropertyDialog : public CDiagramPropertyDlg
{

// Construction
public:
	CPropertyDialog(CWnd* pParent = NULL);   // standard constructor
	~CPropertyDialog();

	virtual void SetValues();

// Dialog Data
	//{{AFX_DATA(CPropertyDialog)
	enum { IDD = IDD_DIALOG_PROPERTY };
	CString	m_text;
	//}}AFX_DATA

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CPropertyDialog)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CPropertyDialog)
	virtual void OnOK();
	virtual void OnCancel();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

public:
	afx_msg void OnEnChangeEditText();
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(_AFX_PROPERTYDIALOG_H_)
