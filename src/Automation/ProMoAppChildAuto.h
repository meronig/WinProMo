/* ==========================================================================

	Copyright © 2026 Technical University of Denmark

	Author :		Giovanni Meroni

   ========================================================================*/
#ifndef _PROMOAPPCHILDAUTO_H_
#define _PROMOAPPCHILDAUTO_H_

#include "ProMoAutomationHost.h"
#include "ProMoAppAutoAbs.h"

class AFX_EXT_CLASS CProMoAppChildAuto :
    public CCmdTarget
{
	DECLARE_DYNCREATE(CProMoAppChildAuto)

	CProMoAppChildAuto();

public:

	virtual void Initialize(IProMoAutomationHost* obj);
	void Detach();
	BOOL IsAlive() const;

	virtual CProMoAppAutoAbs* GetAppAutoObject() const;
	virtual void SetAppAutoObject(CProMoAppAutoAbs* pAppAuto);

	virtual void ThrowIfNoAppAutoObject() const;
	virtual void ThrowIfDetached() const;


	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CProMoAppChildAuto)
public:
	virtual void OnFinalRelease();
	//}}AFX_VIRTUAL

	// Generated message map functions
	//{{AFX_MSG(CProMoAppChildAuto)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
public:
	// Generated OLE dispatch map functions
	//{{AFX_DISPATCH(CProMoAppChildAuto)
	afx_msg LPDISPATCH Application();
	//}}AFX_DISPATCH
	DECLARE_DISPATCH_MAP()
	DECLARE_INTERFACE_MAP()

// Implementation
protected:
	virtual ~CProMoAppChildAuto();

	virtual void DetachInternalObject();

	IProMoAutomationHost* m_pInternalObject;
	CProMoAppAutoAbs* m_pAppAuto;

};

#endif // _PROMOAPPCHILDAUTO_H_

