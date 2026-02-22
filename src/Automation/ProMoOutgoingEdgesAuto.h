/* ==========================================================================

	Copyright © 2026 Technical University of Denmark

	Author :		Giovanni Meroni

   ========================================================================*/
#ifndef _PROMOOUTGOINGEDGESAUTO_H_
#define _PROMOOUTGOINGEDGESAUTO_H_

// ProMoOutgoingEdgesAuto.h : header file
//



/////////////////////////////////////////////////////////////////////////////
// CProMoOutgoingEdgesAuto command target
#include "ProMoBlockChildAuto.h"

class AFX_EXT_CLASS CProMoOutgoingEdgesAuto : public CProMoBlockChildAuto
{
	DECLARE_DYNCREATE(CProMoOutgoingEdgesAuto)

	CProMoOutgoingEdgesAuto();           // protected constructor used by dynamic creation

// Attributes
public:

// Operations
public:

// Overrides
public:
	virtual void SetElementAutoObject(CProMoElementAuto* pElementAuto);
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CProMoOutgoingEdgesAuto)
	//}}AFX_VIRTUAL

// Implementation
protected:
	virtual ~CProMoOutgoingEdgesAuto();

	// Generated message map functions
	//{{AFX_MSG(CProMoOutgoingEdgesAuto)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
	// Generated OLE dispatch map functions
	//{{AFX_DISPATCH(CProMoOutgoingEdgesAuto)
	afx_msg VARIANT GetIDs();
	afx_msg void SetIDs(const VARIANT FAR& newValue);
	afx_msg short Count();
	afx_msg BOOL Add(LPDISPATCH Item);
	afx_msg BOOL Remove(const VARIANT FAR& Item);
	afx_msg LPDISPATCH GetItem(const VARIANT FAR& Item);
	afx_msg void SetItem(const VARIANT FAR& Item, LPDISPATCH newValue);
	//}}AFX_DISPATCH
	DECLARE_DISPATCH_MAP()
	DECLARE_INTERFACE_MAP()
};

#endif //_PROMOOUTGOINGEDGESAUTO_H_
/////////////////////////////////////////////////////////////////////////////
