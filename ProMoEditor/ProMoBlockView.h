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
		
	// Model-view links
	virtual CProMoBlockModel* GetModel() const;
	virtual void SetModel(CProMoBlockModel*);

	// Block-specific methods
	virtual void AutoResize();
		
	virtual void Highlight(CDC* dc, CRect rect);
	virtual BOOL IsTarget();
	virtual void SetTarget(BOOL isTarget);
		
	
protected:
	BOOL m_target;
	CProMoBlockModel* m_blockmodel;

	virtual void RecomputeIntersectionLinks();
	virtual CPoint GetIntersection(CPoint innerPoint, CPoint outerPoint);

private:
	CPropertyDialog	m_dlg;
	BOOL			m_moved;
		
// Overrides
public:
	virtual void SetRect(double left, double top, double right, double bottom);
	static	CDiagramEntity* CreateFromString(const CString& str);
	
	virtual void Draw(CDC* dc, CRect rect);

protected:
	virtual CString				GetDefaultGetString() const;
	virtual BOOL				GetDefaultFromString(CString& str);


};
#endif //_PROMOBLOCKVIEW_H_

