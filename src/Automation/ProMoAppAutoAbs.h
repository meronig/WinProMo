/* ==========================================================================

	Copyright © 2026 Technical University of Denmark

	Author :		Giovanni Meroni

   ========================================================================*/
   // ProMoAppAutoAbs.h : header file
   //

   /////////////////////////////////////////////////////////////////////////////
   // CProMoAppAutoAbs command target
#ifndef _PROMOAPPAUTOABS_H_
#define _PROMOAPPAUTOABS_H_

class CProMoDiagramsAutoAbs;

class CProMoDiagramAutoAbs;

class AFX_EXT_CLASS CProMoAppAutoAbs : public CCmdTarget
{
	DECLARE_DYNAMIC(CProMoAppAutoAbs)

	CProMoAppAutoAbs();           // protected constructor used by dynamic creation

	// Attributes

	// Operations
public:
	virtual CProMoDiagramsAutoAbs* GetDiagramsAutoObject();
	virtual void ReleaseDiagramsAutoObject();
	virtual BOOL CanCreateDiagram(const CString& diagramType);
	
protected:
	virtual CProMoDiagramsAutoAbs* CreateDiagramsAutoObject() = 0;
	virtual CProMoDiagramAutoAbs* GetActiveDiagram() = 0;
	virtual void GetRegisteredDiagrams(CStringArray& diagramTypes) = 0;
	virtual void ForceQuit() = 0;

	// Overrides
		// ClassWizard generated virtual function overrides
		//{{AFX_VIRTUAL(CProMoAppAutoAbs)
public:
	virtual void OnFinalRelease();
	//}}AFX_VIRTUAL

// Implementation
protected:
	virtual ~CProMoAppAutoAbs();

	// Generated message map functions
	//{{AFX_MSG(CProMoAppAutoAbs)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
	DECLARE_OLECREATE(CProMoAppAutoAbs)

	// Generated OLE dispatch map functions
	//{{AFX_DISPATCH(CProMoAppAutoAbs)
	afx_msg LPDISPATCH GetDiagrams();
	afx_msg void SetDiagrams(LPDISPATCH newValue);
	afx_msg VARIANT GetCreatableDiagramTypes();
	afx_msg void SetCreatableDiagramTypes(const VARIANT FAR& newValue);
	afx_msg LPDISPATCH ActiveDiagram();
	afx_msg void Quit(BOOL saveChanges);
	//}}AFX_DISPATCH
	DECLARE_DISPATCH_MAP()
	DECLARE_INTERFACE_MAP()
	
private:
	CProMoDiagramsAutoAbs* m_pDiagrams;

};

#endif //_PROMOAPPAUTOABS_H_
/////////////////////////////////////////////////////////////////////////////
