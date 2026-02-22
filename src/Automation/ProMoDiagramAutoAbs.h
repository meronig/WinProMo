/* ==========================================================================

	Copyright © 2026 Technical University of Denmark

	Author :		Giovanni Meroni

   ========================================================================*/
// ProMoDiagramAutoAbs.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CProMoDiagramAuto command target
#ifndef _PROMODIAGRAMAUTOABS_H_
#define _PROMODIAGRAMAUTOABS_H_

#include "ProMoAppChildAuto.h"
#include "../ProMoEditor/ProMoEntityContainer.h"
#include "ProMoAppAutoAbs.h"

class AFX_EXT_CLASS CProMoLabelsAuto;

class AFX_EXT_CLASS CProMoDiagramAutoAbs : public CProMoAppChildAuto
{
	DECLARE_DYNAMIC(CProMoDiagramAutoAbs)

	CProMoDiagramAutoAbs();           // protected constructor used by dynamic creation

	// Attributes
private:

	// Operations
public:
	virtual CProMoEntityContainer* GetContainer() = 0;
	
	virtual void RefreshWindow() = 0;
	
	virtual CProMoLabelsAuto* GetLabelsAutoObject();
	virtual void ReleaseLabelsAutoObject();

	virtual void NotifyChange();
	
protected:
	
	virtual void SaveDiagramAs(CString fileName) = 0;
	virtual void SaveDiagram() = 0;
	virtual void CloseDiagram() = 0;
	

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CProMoDiagramAutoAbs)
public:
	virtual void OnFinalRelease();
	//}}AFX_VIRTUAL


// Implementation
protected:
	virtual ~CProMoDiagramAutoAbs();
	
	// Generated message map functions
	//{{AFX_MSG(CProMoDiagramAutoAbs)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
	// Generated OLE dispatch map functions
	//{{AFX_DISPATCH(CProMoDiagramAutoAbs)
public:
	afx_msg LPDISPATCH GetElements();
	afx_msg void SetElements(LPDISPATCH newValue);
	afx_msg long GetWidth();
	afx_msg void SetWidth(long nNewValue);
	afx_msg long GetHeight();
	afx_msg void SetHeight(long nNewValue);
	afx_msg LPDISPATCH GetLabels();
	afx_msg void SetLabels(LPDISPATCH newValue);
	afx_msg VARIANT GetCreatableElementTypes();
	afx_msg void SetCreatableElementTypes(const VARIANT FAR& newValue);
	afx_msg void SaveAs(const VARIANT FAR& fileName);
	afx_msg void Activate();
	afx_msg void Close(BOOL saveChanges);
	afx_msg void Redo(short times);
	afx_msg void Save(BOOL noPrompt);
	afx_msg void Undo(short times);
	afx_msg BSTR Path();
	afx_msg BSTR Type();
	//}}AFX_DISPATCH
	DECLARE_DISPATCH_MAP()
	DECLARE_INTERFACE_MAP()

	CProMoLabelsAuto* m_pLabels;
};

#endif //_PROMODIAGRAMAUTOABS_H_
/////////////////////////////////////////////////////////////////////////////
