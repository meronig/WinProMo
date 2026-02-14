/* ==========================================================================

	Copyright © 2026 Technical University of Denmark

	Author :		Giovanni Meroni

   ========================================================================*/
#ifndef _PROMODIAGRAMCHILDAUTO_H_
#define _PROMODIAGRAMCHILDAUTO_H_

#include "ProMoAutomationHost.h"
#include "ProMoAppChildAuto.h"
#include "ProMoDiagramAutoAbs.h"

class AFX_EXT_CLASS CProMoDiagramChildAuto :
	public CProMoAppChildAuto
{
	DECLARE_DYNCREATE(CProMoDiagramChildAuto)

	CProMoDiagramChildAuto();

	// Attributes
public:

	// Operations
public:

	virtual CProMoEntityContainer* GetContainer();
	
	virtual CProMoDiagramAutoAbs* GetDiagramAutoObject() const;
	virtual void SetDiagramAutoObject(CProMoDiagramAutoAbs* pAppAuto);
	
	virtual void ThrowIfNoDiagramAutoObject() const;
	
	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CProMoDiagramChildAuto)
public:
	virtual void OnFinalRelease();
	//}}AFX_VIRTUAL

	// Implementation
protected:
	virtual ~CProMoDiagramChildAuto();

	// Generated message map functions
	//{{AFX_MSG(CProMoDiagramChildAuto)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
	// Generated OLE dispatch map functions
	//{{AFX_DISPATCH(CProMoDiagramChildAuto)
	afx_msg LPDISPATCH Diagram();
	//}}AFX_DISPATCH
	DECLARE_DISPATCH_MAP()
	DECLARE_INTERFACE_MAP()

	CProMoDiagramAutoAbs* m_pDiagramAuto;

};

#endif // _PROMODIAGRAMCHILDAUTO_H_

