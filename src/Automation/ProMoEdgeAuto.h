/* ==========================================================================

	Copyright © 2026 Technical University of Denmark

	Author :		Giovanni Meroni

   ========================================================================*/
#ifndef _PROMOEDGEAUTO_H_
#define _PROMOEDGEAUTO_H_

// ProMoEdgeAuto.h : header file
//



/////////////////////////////////////////////////////////////////////////////
// CProMoEdgeAuto command target
#include "ProMoElementAuto.h"

class AFX_EXT_CLASS CProMoEdgeSegmentsAuto;

class AFX_EXT_CLASS CProMoEdgeAuto : public CProMoElementAuto
{
	DECLARE_DYNCREATE(CProMoEdgeAuto)

	CProMoEdgeAuto();           // protected constructor used by dynamic creation

// Attributes
public:

// Operations
public:
	virtual CProMoEdgeModel* GetEdgeModel();

	virtual CProMoEdgeSegmentsAuto* GetSegmentsAutoObject();
	virtual void ReleaseSegmentsAutoObject();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CProMoEdgeAuto)
public:
	virtual void OnFinalRelease();
	//}}AFX_VIRTUAL

// Implementation
protected:
	virtual ~CProMoEdgeAuto();

	// Generated message map functions
	//{{AFX_MSG(CProMoEdgeAuto)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
	// Generated OLE dispatch map functions
	//{{AFX_DISPATCH(CProMoEdgeAuto)
	afx_msg LPDISPATCH GetSource();
	afx_msg void SetSource(LPDISPATCH newValue);
	afx_msg LPDISPATCH GetDestination();
	afx_msg void SetDestination(LPDISPATCH newValue);
	afx_msg LPDISPATCH GetSegments();
	afx_msg void SetSegments(LPDISPATCH newValue);
	//}}AFX_DISPATCH
	DECLARE_DISPATCH_MAP()
	DECLARE_INTERFACE_MAP()

	CProMoEdgeSegmentsAuto* m_pSegments;
};

#endif //_PROMOEDGEAUTO_H_
/////////////////////////////////////////////////////////////////////////////
