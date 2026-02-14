/* ==========================================================================

	Copyright © 2026 Technical University of Denmark

	Author :		Giovanni Meroni

   ========================================================================*/
#ifndef _PROMOBLOCKCHILDAUTO_H_
#define _PROMOBLOCKCHILDAUTO_H_

// ProMoBlockChildAuto.h : header file
//



/////////////////////////////////////////////////////////////////////////////
// CProMoBlockChildAuto command target
#include "ProMoElementChildAuto.h"

class AFX_EXT_CLASS CProMoBlockChildAuto : public CProMoElementChildAuto
{
	DECLARE_DYNCREATE(CProMoBlockChildAuto)

	CProMoBlockChildAuto();           // protected constructor used by dynamic creation

// Attributes
public:

// Operations
public:
	CProMoBlockModel* GetBlockModel();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CProMoBlockChildAuto)
	//}}AFX_VIRTUAL

// Implementation
protected:
	virtual ~CProMoBlockChildAuto();

	// Generated message map functions
	//{{AFX_MSG(CProMoBlockChildAuto)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
	// Generated OLE dispatch map functions
	//{{AFX_DISPATCH(CProMoBlockChildAuto)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_DISPATCH
	DECLARE_DISPATCH_MAP()
	DECLARE_INTERFACE_MAP()
};

#endif	//_PROMOBLOCKCHILDAUTO_H_
/////////////////////////////////////////////////////////////////////////////
