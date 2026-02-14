/* ==========================================================================

	Copyright © 2026 Technical University of Denmark

	Author :		Giovanni Meroni

   ========================================================================*/
#ifndef _PROMOELEMENTCHILDAUTO_H_
#define _PROMOELEMENTCHILDAUTO_H_

// ProMoElementChildAuto.h : header file
//



/////////////////////////////////////////////////////////////////////////////
// CProMoElementChildAuto command target
#include "ProMoDiagramChildAuto.h"
#include "ProMoElementAuto.h"


class AFX_EXT_CLASS CProMoElementChildAuto : public CProMoDiagramChildAuto
{
	DECLARE_DYNCREATE(CProMoElementChildAuto)

	CProMoElementChildAuto();           // protected constructor used by dynamic creation

// Attributes
public:

// Operations
public:
	virtual CProMoModel* GetModel();

	virtual CProMoElementAuto* GetElementAutoObject() const;
	virtual void SetElementAutoObject(CProMoElementAuto* pElementAuto);

	virtual void ThrowIfNoElementAutoObject() const;


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CProMoElementChildAuto)
public:
	virtual void OnFinalRelease();
	//}}AFX_VIRTUAL

// Implementation
protected:
	virtual ~CProMoElementChildAuto();

	// Generated message map functions
	//{{AFX_MSG(CProMoElementChildAuto)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
	// Generated OLE dispatch map functions
	//{{AFX_DISPATCH(CProMoElementChildAuto)
	afx_msg LPDISPATCH Element();
	//}}AFX_DISPATCH
	DECLARE_DISPATCH_MAP()
	DECLARE_INTERFACE_MAP()

	CProMoElementAuto* m_pElementAuto;


};

#endif	//_PROMOELEMENTCHILDAUTO_H_
/////////////////////////////////////////////////////////////////////////////
