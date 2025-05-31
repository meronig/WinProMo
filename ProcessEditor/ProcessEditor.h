#ifndef _PROCESSEDITOR_H_
#define _PROCESSEDITOR_H_

#include "../DiagramEditor/DiagramEditor.h"
#include "ProcessEntityBlockView.h"
#include "ProcessLineEdgeView.h"
#include "ProcessControlFactory.h"


class CProcessEditor : public CDiagramEditor
{
public:
	// Construction/initialization/destruction
	CProcessEditor();
	virtual ~CProcessEditor();

protected:
	// Overrides:
	virtual void DrawGrid(CDC* dc, CRect rect, double zoom) const;
	virtual void DrawObjects(CDC* dc, double zoom) const;
	virtual void SaveObjects(CStringArray& stra);

	// Message handlers
	virtual afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	virtual afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	virtual afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	virtual afx_msg void OnLButtonUp(UINT nFlags, CPoint point);

public:
	// Command handlers
	CDiagramEntity* GetNamedObject(const CString& name) const;

	virtual void	Cut();
	virtual void	LeftAlignSelected();
	virtual void	RightAlignSelected();
	virtual void	TopAlignSelected();
	virtual void	BottomAlignSelected();
	virtual void	Load(const CStringArray& stra, CProcessControlFactory& fact);



private:
	virtual void DrawObjectsR(CProcessEntityBlockView* block, CDC* dc, double zoom) const;
	// Private helpers
	virtual void ResetTarget();
	virtual void SetTarget(CProcessEntityBlockView* obj, BOOL select);
	CProcessEntityBlockView* GetTargetBlock(CPoint point);
	CProcessEntityBlockView* GetConnectedBlock(CProcessLineEdgeView* line, BOOL backwards, BOOL ifSelected);
	virtual void DeselectChildBlocks(CProcessEntityBlockView* block);
	virtual void SelectChildBlocks(CProcessEntityBlockView* block);
	virtual void PrepareForAlignment();
	virtual void AutoResizeAll();

	CProcessModel* GetNamedModel(const CObArray& array, const CString& name) const;
	void DeleteModel(CObArray& array, const CString& name);
};

#endif //_PROCESSEDITOR_H_
