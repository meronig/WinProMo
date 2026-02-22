/* ==========================================================================

	Copyright © 2026 Technical University of Denmark

	Author :		Giovanni Meroni

   ========================================================================*/
#ifndef _PROMOLABELAUTO_H_
#define _PROMOLABELAUTO_H_

// ProMoLabelAuto.h : header file
//



/////////////////////////////////////////////////////////////////////////////
// CProMoLabelAuto command target

#include "ProMoElementChildAuto.h"

class AFX_EXT_CLASS CProMoLabelAuto : public CProMoElementChildAuto
{
	DECLARE_DYNCREATE(CProMoLabelAuto)

	CProMoLabelAuto();           // protected constructor used by dynamic creation

// Attributes
public:

// Operations
public:
	virtual CProMoLabel* GetLabel();

// Overrides
public:
	virtual CProMoElementAuto* GetElementAutoObject() const;
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CProMoLabelAuto)
	//}}AFX_VIRTUAL

// Implementation
protected:
	virtual ~CProMoLabelAuto();

	// Generated message map functions
	//{{AFX_MSG(CProMoLabelAuto)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
	// Generated OLE dispatch map functions
	//{{AFX_DISPATCH(CProMoLabelAuto)
	afx_msg double GetTop();
	afx_msg void SetTop(double newValue);
	afx_msg double GetBottom();
	afx_msg void SetBottom(double newValue);
	afx_msg double GetLeft();
	afx_msg void SetLeft(double newValue);
	afx_msg double GetRight();
	afx_msg void SetRight(double newValue);
	afx_msg double GetWidth();
	afx_msg void SetWidth(double newValue);
	afx_msg double GetHeight();
	afx_msg void SetHeight(double newValue);
	afx_msg BSTR GetFontName();
	afx_msg void SetFontName(LPCTSTR lpszNewValue);
	afx_msg short GetFontSize();
	afx_msg void SetFontSize(short nNewValue);
	afx_msg short GetFontWeight();
	afx_msg void SetFontWeight(short nNewValue);
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
	afx_msg short GetBkMode();
	afx_msg void SetBkMode(short nNewValue);
	afx_msg short GetTextHorizontalAlignment();
	afx_msg void SetTextHorizontalAlignment(short nNewValue);
	afx_msg short GetTextVerticalAlignment();
	afx_msg void SetTextVerticalAlignment(short nNewValue);
	afx_msg LPDISPATCH GetProperty();
	afx_msg void SetProperty(LPDISPATCH newValue);
	afx_msg BSTR GetID();
	afx_msg void SetID(LPCTSTR lpszNewValue);
	afx_msg BOOL GetTextMultiLine();
	afx_msg void SetTextMultiLine(BOOL bNewValue);
	afx_msg void Cut();
	afx_msg void Copy();
	afx_msg void Delete();
	afx_msg LPDISPATCH Duplicate();
	//}}AFX_DISPATCH
	DECLARE_DISPATCH_MAP()
	DECLARE_INTERFACE_MAP()
};

#endif //_PROMOLABELAUTO_H_
/////////////////////////////////////////////////////////////////////////////
