// ProMoElementAuto.h : header file
//



/////////////////////////////////////////////////////////////////////////////
// CProMoElementAuto command target
#ifndef _PROMOELEMENTAUTO_H_
#define _PROMOELEMENTAUTO_H_

#include "ProMoDiagramChildAuto.h"
#include "../ProMoEditor/ProMoEdgeView.h"

class AFX_EXT_CLASS CProMoPropertiesAuto;
class AFX_EXT_CLASS CProMoLabelsAuto;

class AFX_EXT_CLASS CProMoElementAuto : public CProMoDiagramChildAuto
{
	DECLARE_DYNCREATE(CProMoElementAuto)

	CProMoElementAuto();           // protected constructor used by dynamic creation

// Attributes
public:

// Operations
public:
	virtual CProMoModel* GetModel();

	virtual void GetViews(CObArray& viewList);
	virtual IProMoView* GetMainView();

	virtual CProMoLabelsAuto* GetLabelsAutoObject();
	virtual void ReleaseLabelsAutoObject();

	virtual CProMoPropertiesAuto* GetPropertiesAutoObject();
	virtual void ReleasePropertiesAutoObject();

protected:
	
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CProMoElementAuto)
public:
	virtual void OnFinalRelease();
	//}}AFX_VIRTUAL

// Implementation
protected:
	virtual ~CProMoElementAuto();

	// Generated message map functions
	//{{AFX_MSG(CProMoElementAuto)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
	// Generated OLE dispatch map functions
	//{{AFX_DISPATCH(CProMoElementAuto)
	afx_msg BOOL GetLockAspectRatio();
	afx_msg void SetLockAspectRatio(BOOL bNewValue);
	afx_msg OLE_COLOR GetLineColor();
	afx_msg void SetLineColor(OLE_COLOR nNewValue);
	afx_msg long GetLineWidth();
	afx_msg void SetLineWidth(long nNewValue);
	afx_msg long GetLineStyle();
	afx_msg void SetLineStyle(long nNewValue);
	afx_msg BSTR GetFontName();
	afx_msg void SetFontName(LPCTSTR lpszNewValue);
	afx_msg long GetFontSize();
	afx_msg void SetFontSize(long nNewValue);
	afx_msg long GetFontWeight();
	afx_msg void SetFontWeight(long nNewValue);
	afx_msg BOOL GetFontItalic();
	afx_msg void SetFontItalic(BOOL bNewValue);
	afx_msg BOOL GetFontUnderline();
	afx_msg void SetFontUnderline(BOOL bNewValue);
	afx_msg BOOL GetFontStrikeOut();
	afx_msg void SetFontStrikeOut(BOOL bNewValue);
	afx_msg OLE_COLOR GetTextColor();
	afx_msg void SetTextColor(OLE_COLOR nNewValue);
	afx_msg OLE_COLOR GetBkColor();
	afx_msg void SetBkColor(OLE_COLOR nNewValue);
	afx_msg long GetBkMode();
	afx_msg void SetBkMode(long nNewValue);
	afx_msg long GetTextAlignment();
	afx_msg void SetTextAlignment(long nNewValue);
	afx_msg long GetTextHorizontalAlignment();
	afx_msg void SetTextHorizontalAlignment(long nNewValue);
	afx_msg long GetTextVerticalAlignment();
	afx_msg void SetTextVerticalAlignment(long nNewValue);
	afx_msg BSTR GetName();
	afx_msg void SetName(LPCTSTR lpszNewValue);
	afx_msg LPDISPATCH GetLabels();
	afx_msg void SetLabels(LPDISPATCH newValue);
	afx_msg LPDISPATCH GetProperties();
	afx_msg void SetProperties(LPDISPATCH newValue);
	afx_msg BSTR GetType();
	afx_msg void SetType(LPCTSTR lpszNewValue);
	afx_msg void Copy();
	afx_msg void Cut();
	afx_msg void Delete();
	afx_msg LPDISPATCH Duplicate();
	//}}AFX_DISPATCH
	DECLARE_DISPATCH_MAP()
	DECLARE_INTERFACE_MAP()

	CProMoPropertiesAuto* m_pProperties;
	CProMoLabelsAuto* m_pLabels;
};

#endif // _PROMOELEMENTAUTO_H_
/////////////////////////////////////////////////////////////////////////////
