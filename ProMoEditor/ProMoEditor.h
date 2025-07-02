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

protected:
	virtual void DrawObjectsR(CProMoBlockView* block, CDC* dc, double zoom) const;
	// Private helpers
	virtual void ResetTarget();
	virtual void SetTarget(CProMoBlockView* obj, BOOL select);
	CProMoBlockView* GetTargetBlock(CPoint point);
	CProMoBlockView* GetConnectedBlock(CProMoEdgeView* line, BOOL backwards);
	virtual void DeselectChildBlocks(CProMoBlockView* block);
	virtual void SelectChildBlocks(CProMoBlockView* block);
	virtual void PrepareForAlignment();
	virtual void AutoResizeAll();
	virtual void NotifySelectionChanged();

// Overrides:
public:
	// Command handlers
	virtual void	Cut();
	virtual void	LeftAlignSelected();
	virtual void	RightAlignSelected();
	virtual void	TopAlignSelected();
	virtual void	BottomAlignSelected();
	virtual void	SelectAll();
	virtual void	UnselectAll();
	virtual void	Select(CDiagramEntity* obj, BOOL select);

protected:
	virtual void DrawGrid(CDC* dc, CRect rect, double zoom) const;
	virtual void DrawObjects(CDC* dc, double zoom) const;
	virtual void SaveObjects(CStringArray& stra);

	// Message handlers
	virtual afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	virtual afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	virtual afx_msg void OnLButtonUp(UINT nFlags, CPoint point);


};

#endif //_PROMOEDITOR_H_
