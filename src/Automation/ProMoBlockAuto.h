/* ==========================================================================

	Copyright © 2026 Technical University of Denmark

	Author :		Giovanni Meroni

   ========================================================================*/
#ifndef _PROMOBLOCKAUTO_H_
#define _PROMOBLOCKAUTO_H_

// ProMoBlockAuto.h : header file
//


/////////////////////////////////////////////////////////////////////////////
// CProMoBlockAuto command target

#include "ProMoElementAuto.h"

class AFX_EXT_CLASS CProMoSubBlocksAuto;

class AFX_EXT_CLASS CProMoBoundaryBlocksAuto;

class AFX_EXT_CLASS CProMoIncomingEdgesAuto;
	
class AFX_EXT_CLASS CProMoOutgoingEdgesAuto;

class AFX_EXT_CLASS CProMoBlockAuto : public CProMoElementAuto
{
	DECLARE_DYNCREATE(CProMoBlockAuto)

	CProMoBlockAuto();           // protected constructor used by dynamic creation

// Attributes
public:

// Operations
public:
	virtual CProMoBlockModel* GetBlockModel();
	virtual CProMoBlockView* GetMainBlockView();

	virtual CProMoSubBlocksAuto* GetSubBlocksAutoObject();
	virtual void ReleaseSubBlocksAutoObject();

	virtual CProMoBoundaryBlocksAuto* GetBoundaryBlocksAutoObject();
	virtual void ReleaseBoundaryBlocksAutoObject();
	
	virtual CProMoIncomingEdgesAuto* GetIncomingEdgesAutoObject();
	virtual void ReleaseIncomingEdgesAutoObject();
	
	virtual CProMoOutgoingEdgesAuto* GetOutgoingEdgesAutoObject();
	virtual void ReleaseOutgoingEdgesAutoObject();

	static CProMoBlockAuto* FromIDispatch(LPDISPATCH obj);
	static CProMoBlockModel* GetModelFromIDispatch(LPDISPATCH obj);

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CProMoBlockAuto)
public:
	virtual void OnFinalRelease();
	//}}AFX_VIRTUAL

// Implementation
protected:
	virtual ~CProMoBlockAuto();

	// Generated message map functions
	//{{AFX_MSG(CProMoBlockAuto)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
	// Generated OLE dispatch map functions
	//{{AFX_DISPATCH(CProMoBlockAuto)
	afx_msg OLE_COLOR GetFillColor();
	afx_msg void SetFillColor(OLE_COLOR nNewValue);
	afx_msg BOOL GetFillPattern();
	afx_msg void SetFillPattern(BOOL bNewValue);
	afx_msg short GetFillStyle();
	afx_msg void SetFillStyle(short nNewValue);
	afx_msg LPDISPATCH GetParent();
	afx_msg void SetParent(LPDISPATCH newValue);
	afx_msg LPDISPATCH GetSubBlocks();
	afx_msg void SetSubBlocks(LPDISPATCH newValue);
	afx_msg LPDISPATCH GetBoundaryBlocks();
	afx_msg void SetBoundaryBlocks(LPDISPATCH newValue);
	afx_msg short GetBoundaryAttachment();
	afx_msg void SetBoundaryAttachment(short nNewValue);
	afx_msg LPDISPATCH GetOutgoingEdges();
	afx_msg void SetOutgoingEdges(LPDISPATCH newValue);
	afx_msg LPDISPATCH GetIncomingEdges();
	afx_msg void SetIncomingEdges(LPDISPATCH newValue);
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
	afx_msg BOOL IsBoundaryBlock();
	afx_msg BOOL IsSubBlock();
	//}}AFX_DISPATCH
	DECLARE_DISPATCH_MAP()
	DECLARE_INTERFACE_MAP()

	CProMoSubBlocksAuto* m_pSubBlocks;
	CProMoBoundaryBlocksAuto* m_pBoundaryBlocks;
	CProMoIncomingEdgesAuto* m_pIncomingEdges;
	CProMoOutgoingEdgesAuto* m_pOutgoingEdges;
};

#endif //_PROMOBLOCKAUTO_H_
/////////////////////////////////////////////////////////////////////////////
