/* ==========================================================================

	Copyright © 2026 Technical University of Denmark

	Author :		Giovanni Meroni

   ========================================================================*/
#ifndef _PROMOPROPERTYAUTO_H_
#define _PROMOPROPERTYAUTO_H_

// ProMoPropertyAuto.h : header file
//



/////////////////////////////////////////////////////////////////////////////
// CProMoPropertyAuto command target
#include "ProMoElementChildAuto.h"

class AFX_EXT_CLASS CProMoPropertyAuto : public CProMoElementChildAuto
{
	DECLARE_DYNCREATE(CProMoPropertyAuto)

	CProMoPropertyAuto();           // protected constructor used by dynamic creation

// Attributes
public:
	virtual CProMoProperty* GetProperty();
// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CProMoPropertyAuto)
	//}}AFX_VIRTUAL

// Implementation
protected:
	virtual ~CProMoPropertyAuto();

	// Generated message map functions
	//{{AFX_MSG(CProMoPropertyAuto)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
	// Generated OLE dispatch map functions
	//{{AFX_DISPATCH(CProMoPropertyAuto)
	afx_msg BSTR GetName();
	afx_msg void SetName(LPCTSTR lpszNewValue);
	afx_msg short GetType();
	afx_msg void SetType(short nNewValue);
	afx_msg VARIANT GetValue();
	afx_msg void SetValue(const VARIANT FAR& newValue);
	afx_msg VARIANT GetChildNames();
	afx_msg void SetChildNames(const VARIANT FAR& newValue);
	afx_msg BOOL IsReadOnly();
	afx_msg LPDISPATCH Label();
	afx_msg BOOL IsComposite();
	afx_msg BOOL IsMultivalue();
	afx_msg BOOL Add();
	afx_msg BOOL Remove();
	afx_msg short Count();
	afx_msg LPDISPATCH GetItem(const VARIANT FAR& Item);
	afx_msg void SetItem(const VARIANT FAR& Item, LPDISPATCH newValue);
	//}}AFX_DISPATCH
	DECLARE_DISPATCH_MAP()
	DECLARE_INTERFACE_MAP()
};

#endif //_PROMOPROPERTYAUTO_H_
/////////////////////////////////////////////////////////////////////////////
