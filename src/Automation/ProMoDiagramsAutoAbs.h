/* ==========================================================================

	Copyright © 2026 Technical University of Denmark

	Author :		Giovanni Meroni

========================================================================*/
// ProMoDiagramsAutoAbs.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CProMoDiagramsAutoAbs command target
#ifndef _PROMODIAGRAMSAUTOABS_H_
#define _PROMODIAGRAMSAUTOABS_H_

#include "ProMoDiagramAutoAbs.h"
#include "ProMoAutomationHost.h"
#include "ProMoAppAutoAbs.h"


class AFX_EXT_CLASS CProMoDiagramsAutoAbs : public CProMoAppChildAuto
{
	DECLARE_DYNAMIC(CProMoDiagramsAutoAbs)

	CProMoDiagramsAutoAbs();           // protected constructor used by dynamic creation

	// Attributes
private:
	// Operations

protected:
	
	virtual int GetOpenDiagramsCount() = 0;
	virtual CProMoDiagramAutoAbs* GetDiagramAutoObject(int index) = 0;
	virtual CProMoDiagramAutoAbs* GetDiagramAutoObject(const CString& name) = 0;
	virtual CProMoDiagramAutoAbs* AddNewDiagram(const CString& type) = 0;
	virtual CProMoDiagramAutoAbs* OpenDiagram(const CString& fileName) = 0;
	virtual void GetOpenDiagrams(CStringArray& diagramList) = 0;

	// Overrides
public:
	virtual void SetAppAutoObject(CProMoAppAutoAbs* pAppAuto);

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CProMoDiagramsAutoAbs)
	//}}AFX_VIRTUAL

// Implementation
protected:
	virtual ~CProMoDiagramsAutoAbs();

	// Generated message map functions
	//{{AFX_MSG(CProMoDiagramsAutoAbs)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
	// Generated OLE dispatch map functions
	//{{AFX_DISPATCH(CProMoDiagramsAutoAbs)
	afx_msg VARIANT GetIDs();
	afx_msg void SetIDs(const VARIANT FAR& newValue);
	afx_msg LPDISPATCH Add(const VARIANT FAR& documentType);
	afx_msg LPDISPATCH Open(const VARIANT FAR& fileName);
	afx_msg short Count();
	afx_msg void Save(BOOL noPrompt);
	afx_msg void Close(BOOL saveChanges);
	afx_msg LPDISPATCH GetItem(const VARIANT FAR& Item);
	afx_msg void SetItem(const VARIANT FAR& Item, LPDISPATCH newValue);
	//}}AFX_DISPATCH
	DECLARE_DISPATCH_MAP()
	DECLARE_INTERFACE_MAP()
};

#endif //_PROMODIAGRAMSAUTOABS_H_
/////////////////////////////////////////////////////////////////////////////
