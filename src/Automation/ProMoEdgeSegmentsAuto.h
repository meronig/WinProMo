/* ==========================================================================

	Copyright © 2026 Technical University of Denmark

	Author :		Giovanni Meroni

   ========================================================================*/
#ifndef _PROMOEDGESEGMENTSAUTO_H_
#define _PROMOEDGESEGMENTSAUTO_H_

// ProMoEdgeSegmentsAuto.h : header file
//



/////////////////////////////////////////////////////////////////////////////
// CProMoEdgeSegmentsAuto command target
#include "ProMoEdgeChildAuto.h"

class AFX_EXT_CLASS CProMoEdgeSegmentsAuto : public CProMoEdgeChildAuto
{
	DECLARE_DYNCREATE(CProMoEdgeSegmentsAuto)

	CProMoEdgeSegmentsAuto();           // protected constructor used by dynamic creation

// Attributes
public:

// Operations
public:

// Overrides
public:
	virtual void SetElementAutoObject(CProMoElementAuto* pElementAuto);
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CProMoEdgeSegmentsAuto)
	//}}AFX_VIRTUAL

// Implementation
protected:
	virtual ~CProMoEdgeSegmentsAuto();

	// Generated message map functions
	//{{AFX_MSG(CProMoEdgeSegmentsAuto)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
	// Generated OLE dispatch map functions
	//{{AFX_DISPATCH(CProMoEdgeSegmentsAuto)
	afx_msg short Count();
	afx_msg LPDISPATCH GetItem(short Item);
	afx_msg void SetItem(short Item, LPDISPATCH newValue);
	//}}AFX_DISPATCH
	DECLARE_DISPATCH_MAP()
	DECLARE_INTERFACE_MAP()
};

#endif //_PROMOEDGESEGMENTSAUTO_H_
/////////////////////////////////////////////////////////////////////////////
