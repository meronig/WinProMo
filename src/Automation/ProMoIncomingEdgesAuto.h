/* ==========================================================================

	Copyright © 2026 Technical University of Denmark

	Author :		Giovanni Meroni

   ========================================================================*/
#ifndef _PROMOINCOMINGEDGESAUTO_H_
#define _PROMOINCOMINGEDGESAUTO_H_

// ProMoIncomingEdgesAuto.h : header file
//



/////////////////////////////////////////////////////////////////////////////
// CProMoIncomingEdgesAuto command target
#include "ProMoBlockChildAuto.h"

class AFX_EXT_CLASS CProMoIncomingEdgesAuto : public CProMoBlockChildAuto
{
	DECLARE_DYNCREATE(CProMoIncomingEdgesAuto)

	CProMoIncomingEdgesAuto();           // protected constructor used by dynamic creation

// Attributes
public:

// Operations
public:

// Overrides
public:
	virtual void SetElementAutoObject(CProMoElementAuto* pElementAuto);
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CProMoIncomingEdgesAuto)
	//}}AFX_VIRTUAL

// Implementation
protected:
	virtual ~CProMoIncomingEdgesAuto();

	// Generated message map functions
	//{{AFX_MSG(CProMoIncomingEdgesAuto)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
	// Generated OLE dispatch map functions
	//{{AFX_DISPATCH(CProMoIncomingEdgesAuto)
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

#endif //_PROMOINCOMINGEDGESAUTO_H_
/////////////////////////////////////////////////////////////////////////////
