/* ==========================================================================

	Copyright © 2025 Technical University of Denmark

	Author :		Giovanni Meroni

   ========================================================================*/
#ifndef _PROMOBLOCKVIEW_H_
#define _PROMOBLOCKVIEW_H_

#include "../DiagramEditor/DiagramEntity.h"
#include "PropertyDialog.h"
#include "ProMoBlockModel.h"
class AFX_EXT_CLASS CProMoBlockView : public CDiagramEntity
{

public:
	friend class CProMoEdgeView;
	// Creation/initialization
	CProMoBlockView();
	virtual ~CProMoBlockView();

	virtual CDiagramEntity* Clone();
	virtual void	Copy(CDiagramEntity* obj);

		
	// Model-view links
	virtual CProMoBlockModel* GetModel() const;
	virtual void SetModel(CProMoBlockModel*);

	// Block-specific methods
	virtual void AutoResize();
		
	virtual void Highlight(CDC* dc, CRect rect);
	virtual BOOL IsTarget();
	virtual void SetTarget(BOOL isTarget);
	
	virtual void SetLockedProportions(BOOL hasLockedProportions);
	virtual BOOL HasLockedProportions();

	
protected:
	BOOL m_target;
	CProMoBlockModel* m_blockmodel;

	virtual void RecomputeIntersectionLinks();
	virtual CPoint GetIntersection(CPoint innerPoint, CPoint outerPoint);
	virtual void KeepElementsConnected(double left, double top, double right, double bottom);
	virtual CPoint MapPointToNewRect(CPoint oldPoint, double left, double top, double right, double bottom);
	virtual CRect ComputeTextRect(const CString &text, const CFont &font);

private:
	CPropertyDialog	m_dlg;
	BOOL			m_moved;
	BOOL			m_lockProportions;
		
// Overrides
public:
	virtual void	SetLeft(double left);
	virtual void	SetRight(double right);
	virtual void	SetTop(double top);
	virtual void	SetBottom(double bottom);

	
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

