#ifndef _PROCESSEDITOR_H_
#define _PROCESSEDITOR_H_

#include "../DiagramEditor/DiagramEditor.h"
#include "ProcessEntityBlock.h"
#include "ProcessLineEdge.h"

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
	virtual void	Load(const CStringArray& stra);



private:
	virtual void DrawObjectsR(CProcessEntityBlock* block, CDC* dc, double zoom) const;
	// Private helpers
	virtual void ResetTarget();
	virtual void SetTarget(CProcessEntityBlock* obj, BOOL select);
	CProcessEntityBlock* GetTargetBlock(CPoint point);
	CProcessEntityBlock* GetConnectedBlock(CProcessLineEdge* line, BOOL backwards, BOOL ifSelected);
	virtual void DeselectChildBlocks(CProcessEntityBlock* block);
	virtual void SelectChildBlocks(CProcessEntityBlock* block);
	virtual void PrepareForAlignment();
	virtual void AutoResizeAll();
};

#endif //_PROCESSEDITOR_H_
