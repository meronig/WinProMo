/* ==========================================================================

	Copyright © 2025 Technical University of Denmark

	Author :		Giovanni Meroni

   ========================================================================*/
#ifndef _PROMOBLOCKVIEW_H_
#define _PROMOBLOCKVIEW_H_

#include "../DiagramEditor/DiagramEntity.h"
#include "ProMoBlockModel.h"
class AFX_EXT_CLASS CProMoBlockView : public CDiagramEntity
{

public:
	// Creation/initialization
	CProMoBlockView();
	virtual ~CProMoBlockView();

	virtual CDiagramEntity* Clone();
	virtual void	Copy(CDiagramEntity* obj);

	static	CDiagramEntity* CreateFromString(const CString& str, CProMoModel* model);
		
	// Model-view links
	virtual CProMoBlockModel* GetModel() const;
	
	// Block-specific methods
	virtual void AutoResize();
		
	virtual void Highlight(CDC* dc, CRect rect);
	virtual BOOL IsTarget();
	virtual void SetTarget(BOOL isTarget);
	
	virtual void SetLockedProportions(BOOL hasLockedProportions);
	virtual BOOL HasLockedProportions();

	virtual void SetFitTitle(BOOL hasFitTitle);
	virtual BOOL HasFitTitle();

	// Parent-child block links
	virtual void SetParentBlock(CProMoBlockView* parent);
	virtual void UnlinkAllSubBlocks();

	virtual CPoint GetIntersection(CPoint innerPoint, CPoint outerPoint);

protected:
	BOOL m_target;
	CProMoBlockModel* m_blockmodel;

	virtual void RecomputeIntersectionLinks();
	virtual void KeepElementsConnected(double left, double top, double right, double bottom);
	virtual CPoint MapPointToNewRect(CPoint oldPoint, double left, double top, double right, double bottom);
	virtual CRect ComputeTextRect(const CString &text, const CFont &font);

	virtual void SetModel(CProMoBlockModel*);


private:
	BOOL			m_moved;
	BOOL			m_lockProportions;
	BOOL			m_fitTitle;
	CRect			m_titleRect;
		
// Overrides
public:
	virtual void	SetLeft(double left);
	virtual void	SetRight(double right);
	virtual void	SetTop(double top);
	virtual void	SetBottom(double bottom);
	virtual void	SetTitle(CString title);

	
	virtual void	SetRect(CRect rect);
	virtual void SetRect(double left, double top, double right, double bottom);
	static	CDiagramEntity* CreateFromString(const CString& str);
	
	virtual void Draw(CDC* dc, CRect rect);

	virtual void	ShowPopup(CPoint point, CWnd* parent);

protected:
	virtual CString				GetDefaultGetString() const;
	virtual BOOL				GetDefaultFromString(CString& str);


};
#endif //_PROMOBLOCKVIEW_H_

