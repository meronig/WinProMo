/* ==========================================================================

	Copyright © 2025 Technical University of Denmark

	Author :		Giovanni Meroni

   ========================================================================*/
#ifndef _PROMOEDITOR_H_
#define _PROMOEDITOR_H_

#include "../DiagramEditor/DiagramEditor.h"
#include "ProMoBlockView.h"
#include "ProMoEdgeView.h"
#include "ProMoControlFactory.h"

#define WM_SELECTION_CHANGED (WM_APP + 100)

class AFX_EXT_CLASS CProMoEditor : public CDiagramEditor
{
public:
	// Construction/initialization/destruction
	CProMoEditor();
	virtual ~CProMoEditor();

public:
	virtual void	Load(const CStringArray& stra, CProMoControlFactory* fact);
	virtual void NotifySelectionChanged();
	void UpdateDelete(CCmdUI* pCmdUI) const;

	virtual void	MiddleAlignSelected();
	virtual void	CenterAlignSelected();

protected:
	virtual void DrawObjectsR(CProMoBlockView* block, CDC* dc, double zoom) const;
	// Private helpers
	virtual void ResetTarget();
	virtual void SetTarget(CProMoBlockView* obj, BOOL select);
	virtual CProMoBlockView* GetTargetBlock(CPoint point);
	virtual CProMoBlockView* GetConnectedBlock(CProMoEdgeView* line, BOOL backwards);
	virtual void DeselectChildBlocks(CProMoBlockView* block);
	virtual void SelectChildBlocks(CProMoBlockView* block);
	virtual void PrepareForAlignment();
	virtual void AutoResizeAll();
	virtual CObArray* GetProperties(CDiagramEntity* element);
	virtual void DrawPageBreaks(CDC* dc, CRect rect, double zoom) const;

// Overrides:
public:
	// Visuals
	virtual void	Draw(CDC* dc, CRect rect) const;

	// Command handlers
	virtual void	Cut();
	virtual void	Paste();
	virtual void	Undo();
	virtual void	Redo();
	virtual void	SelectAll();
	virtual void	UnselectAll();
	virtual void	DeleteAllSelected();
	virtual void	LeftAlignSelected();
	virtual void	RightAlignSelected();
	virtual void	TopAlignSelected();
	virtual void	BottomAlignSelected();
	
	// Property Accessors
	virtual void	ShowPageBreaks(BOOL isVisible);
	virtual BOOL	IsPageBreaksVisible();
	virtual void	SetPageLayout(CDC* dc);
		
protected:
	virtual void DrawGrid(CDC* dc, CRect rect, double zoom) const;
	virtual void DrawObjects(CDC* dc, double zoom) const;
	virtual void SaveObjects(CStringArray& stra);

	// Message handlers
	virtual afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	virtual afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	virtual afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	virtual afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);

protected:
	BOOL m_pageBreaksVisible;
	int m_printResolutionX;
	int m_printResolutionY;
	CSize m_paperSize;
	CSize m_printableArea;
};

#endif //_PROMOEDITOR_H_
