// ProMoElementsAuto.h : header file
//



/////////////////////////////////////////////////////////////////////////////
// CProMoElementsAuto command target
#ifndef _PROMOELEMENTSAUTO_H_
#define _PROMOELEMENTSAUTO_H_

#include "ProMoDiagramChildAuto.h"
#include "..\ProMoEditor\ProMoEntityContainer.h"
#include "ProMoElementAuto.h"

class AFX_EXT_CLASS CProMoElementsAuto : public CProMoDiagramChildAuto
{
	DECLARE_DYNCREATE(CProMoElementsAuto)

	CProMoElementsAuto();           // protected constructor used by dynamic creation

// Attributes
public:

// Operations
public:
protected:
	virtual CProMoElementAuto* GetElementAutoObject(CProMoModel* pModel);
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CProMoElementsAuto)
	//}}AFX_VIRTUAL

// Implementation
protected:
	virtual ~CProMoElementsAuto();

	// Generated message map functions
	//{{AFX_MSG(CProMoElementsAuto)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
	// Generated OLE dispatch map functions
	//{{AFX_DISPATCH(CProMoElementsAuto)
	afx_msg VARIANT GetIDs();
	afx_msg void SetIDs(const VARIANT FAR& newValue);
	afx_msg short Count();
	afx_msg LPDISPATCH Add(const VARIANT FAR& elementType);
	afx_msg BOOL Remove(const VARIANT FAR& Item);
	afx_msg LPDISPATCH GetItem(const VARIANT FAR& Item);
	afx_msg void SetItem(const VARIANT FAR& Item, LPDISPATCH newValue);
	//}}AFX_DISPATCH
	DECLARE_DISPATCH_MAP()
	DECLARE_INTERFACE_MAP()
};

#endif //_PROMOELEMENTSAUTO_H_
/////////////////////////////////////////////////////////////////////////////
