/* ==========================================================================

	Copyright © 2026 Technical University of Denmark

	Author :		Giovanni Meroni

   ========================================================================*/
#ifndef _PROMOPROPERTIESAUTO_H_
#define _PROMOPROPERTIESAUTO_H_

// ProMoPropertiesAuto.h : header file
//



/////////////////////////////////////////////////////////////////////////////
// CProMoPropertiesAuto command target
#include "ProMoElementChildAuto.h"

class AFX_EXT_CLASS CProMoPropertiesAuto : public CProMoElementChildAuto
{
	DECLARE_DYNCREATE(CProMoPropertiesAuto)

	CProMoPropertiesAuto();           // protected constructor used by dynamic creation

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
public:
	virtual void SetElementAutoObject(CProMoElementAuto* pElementAuto);
	//{{AFX_VIRTUAL(CProMoPropertiesAuto)
	//}}AFX_VIRTUAL

// Implementation
protected:
	virtual ~CProMoPropertiesAuto();

	// Generated message map functions
	//{{AFX_MSG(CProMoPropertiesAuto)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
	// Generated OLE dispatch map functions
	//{{AFX_DISPATCH(CProMoPropertiesAuto)
	afx_msg VARIANT GetNames();
	afx_msg void SetNames(const VARIANT FAR& newValue);
	afx_msg long Count();
	afx_msg LPDISPATCH GetItem(const VARIANT FAR& Item);
	afx_msg void SetItem(const VARIANT FAR& Item, LPDISPATCH newValue);
	//}}AFX_DISPATCH
	DECLARE_DISPATCH_MAP()
	DECLARE_INTERFACE_MAP()
};

#endif //_PROMOPROPERTIESAUTO_H_
/////////////////////////////////////////////////////////////////////////////
