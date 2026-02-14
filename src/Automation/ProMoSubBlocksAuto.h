/* ==========================================================================

	Copyright © 2026 Technical University of Denmark

	Author :		Giovanni Meroni

   ========================================================================*/
#ifndef _PROMOSUBBLOCKSAUTO_H_
#define _PROMOSUBBLOCKSAUTO_H_

// ProMoSubBlocksAuto.h : header file
//



/////////////////////////////////////////////////////////////////////////////
// CProMoSubBlocksAuto command target
#include "ProMoBlockChildAuto.h"

class AFX_EXT_CLASS CProMoSubBlocksAuto : public CProMoBlockChildAuto
{
	DECLARE_DYNCREATE(CProMoSubBlocksAuto)

	CProMoSubBlocksAuto();           // protected constructor used by dynamic creation

// Attributes
public:

// Operations
public:

// Overrides
public:
	virtual void SetElementAutoObject(CProMoElementAuto* pElementAuto);
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CProMoSubBlocksAuto)
	//}}AFX_VIRTUAL

// Implementation
protected:
	virtual ~CProMoSubBlocksAuto();

	// Generated message map functions
	//{{AFX_MSG(CProMoSubBlocksAuto)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
	// Generated OLE dispatch map functions
	//{{AFX_DISPATCH(CProMoSubBlocksAuto)
	afx_msg VARIANT GetIDs();
	afx_msg void SetIDs(const VARIANT FAR& newValue);
	afx_msg long Count();
	afx_msg BOOL Add(LPDISPATCH Item);
	afx_msg BOOL Remove(const VARIANT FAR& Item);
	afx_msg LPDISPATCH GetItem(const VARIANT FAR& Item);
	afx_msg void SetItem(const VARIANT FAR& Item, LPDISPATCH newValue);
	//}}AFX_DISPATCH
	DECLARE_DISPATCH_MAP()
	DECLARE_INTERFACE_MAP()
};

#endif //_PROMOSUBBLOCKSAUTO_H_
/////////////////////////////////////////////////////////////////////////////
