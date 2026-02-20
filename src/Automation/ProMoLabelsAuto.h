/* ==========================================================================

	Copyright © 2026 Technical University of Denmark

	Author :		Giovanni Meroni

   ========================================================================*/
#ifndef _PROMOLABELSAUTO_H_
#define _PROMOLABELSAUTO_H_

// ProMoLabelsAuto.h : header file
//



/////////////////////////////////////////////////////////////////////////////
// CProMoLabelsAuto command target
#include "ProMoElementChildAuto.h"

class AFX_EXT_CLASS CProMoLabelsAuto : public CProMoElementChildAuto
{
	DECLARE_DYNCREATE(CProMoLabelsAuto)

	CProMoLabelsAuto();           // protected constructor used by dynamic creation

// Attributes
public:

// Operations
public:
protected:
	virtual void GetLabels(CObArray& labels);

// Overrides
public:
	virtual void SetDiagramAutoObject(CProMoDiagramAutoAbs* pAppAuto);
	virtual void SetElementAutoObject(CProMoElementAuto* pElementAuto);
	virtual CProMoElementAuto* GetElementAutoObject() const;

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CProMoLabelsAuto)
	//}}AFX_VIRTUAL

// Implementation
protected:
	virtual ~CProMoLabelsAuto();

	// Generated message map functions
	//{{AFX_MSG(CProMoLabelsAuto)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
	// Generated OLE dispatch map functions
	//{{AFX_DISPATCH(CProMoLabelsAuto)
	afx_msg VARIANT GetIDs();
	afx_msg void SetIDs(const VARIANT FAR& newValue);
	afx_msg LPDISPATCH Add();
	afx_msg long Count();
	afx_msg BOOL Remove(const VARIANT FAR& Item);
	afx_msg LPDISPATCH GetItem(const VARIANT FAR& Item);
	afx_msg void SetItem(const VARIANT FAR& Item, LPDISPATCH newValue);
	//}}AFX_DISPATCH
	DECLARE_DISPATCH_MAP()
	DECLARE_INTERFACE_MAP()
};

#endif //_PROMOLABELSAUTO_H_
/////////////////////////////////////////////////////////////////////////////
