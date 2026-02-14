/* ==========================================================================

	Copyright © 2026 Technical University of Denmark

	Author :		Giovanni Meroni

   ========================================================================*/
#ifndef _PROMOEDGECHILDAUTO_H_
#define _PROMOEDGECHILDAUTO_H_

// ProMoEdgeChildAuto.h : header file
//



/////////////////////////////////////////////////////////////////////////////
// CProMoEdgeChildAuto command target
#include "ProMoElementChildAuto.h"
#include "../ProMoEditor/ProMoEdgeModel.h"

class AFX_EXT_CLASS CProMoEdgeChildAuto : public CProMoElementChildAuto
{
	DECLARE_DYNCREATE(CProMoEdgeChildAuto)

	CProMoEdgeChildAuto();           // protected constructor used by dynamic creation

// Attributes
public:

// Operations
public:
	virtual CProMoEdgeModel* GetEdgeModel();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CProMoEdgeChildAuto)
	//}}AFX_VIRTUAL

// Implementation
protected:
	virtual ~CProMoEdgeChildAuto();

	// Generated message map functions
	//{{AFX_MSG(CProMoEdgeChildAuto)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
	// Generated OLE dispatch map functions
	//{{AFX_DISPATCH(CProMoEdgeChildAuto)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_DISPATCH
	DECLARE_DISPATCH_MAP()
	DECLARE_INTERFACE_MAP()
};

#endif //_PROMOEDGECHILDAUTO_H_
/////////////////////////////////////////////////////////////////////////////
