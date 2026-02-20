/* ==========================================================================

	Copyright © 2026 Technical University of Denmark

	Author :		Giovanni Meroni

   ========================================================================*/
#ifndef _PROMOEDGESEGMENTAUTO_H_
#define _PROMOEDGESEGMENTAUTO_H_

// ProMoEdgeSegmentAuto.h : header file
//



/////////////////////////////////////////////////////////////////////////////
// CProMoEdgeSegmentAuto command target
#include "ProMoEdgeChildAuto.h"

class AFX_EXT_CLASS CProMoEdgeSegmentAuto : public CProMoEdgeChildAuto
{
	DECLARE_DYNCREATE(CProMoEdgeSegmentAuto)

	CProMoEdgeSegmentAuto();           // protected constructor used by dynamic creation

// Attributes
public:

// Operations
public:
protected:
	virtual CProMoEdgeView* GetSegment();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CProMoEdgeSegmentAuto)
	//}}AFX_VIRTUAL

// Implementation
protected:
	virtual ~CProMoEdgeSegmentAuto();

	// Generated message map functions
	//{{AFX_MSG(CProMoEdgeSegmentAuto)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
	// Generated OLE dispatch map functions
	//{{AFX_DISPATCH(CProMoEdgeSegmentAuto)
	afx_msg double GetTop();
	afx_msg void SetTop(double newValue);
	afx_msg double GetLeft();
	afx_msg void SetLeft(double newValue);
	afx_msg double GetBottom();
	afx_msg void SetBottom(double newValue);
	afx_msg double GetRight();
	afx_msg void SetRight(double newValue);
	afx_msg double GetWidth();
	afx_msg void SetWidth(double newValue);
	afx_msg double GetHeight();
	afx_msg void SetHeight(double newValue);
	afx_msg LPDISPATCH Split();
	afx_msg LPDISPATCH Prev();
	afx_msg LPDISPATCH Next();
	afx_msg void Remove();
	//}}AFX_DISPATCH
	DECLARE_DISPATCH_MAP()
	DECLARE_INTERFACE_MAP()
};

#endif //_PROMOEDGESEGMENTAUTO_H_
/////////////////////////////////////////////////////////////////////////////
