/* ==========================================================================

	Copyright © 2025 Technical University of Denmark

	Author :		Giovanni Meroni

   ========================================================================*/
#ifndef _PROMOBLOCKVIEW_H_
#define _PROMOBLOCKVIEW_H_

#include "../DiagramEditor/DiagramEntity.h"
#include "ProMoBlockModel.h"
#include "../GeometryUtils/DoublePoint.h"
#include "../GeometryUtils/DoubleRect.h"

#define SHAPE_CUSTOM 0
#define SHAPE_RECTANGLE 1
#define SHAPE_ELLIPSE 2
#define SHAPE_POLYGON 3

class AFX_EXT_CLASS CProMoBlockView : public CDiagramEntity
{

public:
	// Creation/initialization
	CProMoBlockView();
	virtual ~CProMoBlockView();

	virtual CDiagramEntity* Clone();
	virtual void	Copy(CDiagramEntity* obj);

	static	CDiagramEntity* CreateFromString(const CString& str, CProMoModel* model);

	static CString GetModelFromString(const CString& str);
	static CString GetNameFromString(const CString& str);
		
	// Model-view links
	virtual CProMoBlockModel* GetModel() const;
	
	// Block-specific methods
	virtual void AutoResize();
		
	virtual BOOL IsTarget();
	virtual void SetTarget(BOOL isTarget);
	
	virtual void SetLockedProportions(BOOL hasLockedProportions);
	virtual BOOL HasLockedProportions();

	// Parent-child block links
	virtual void SetParentBlock(CProMoBlockView* parent);
	virtual CProMoBlockView* GetParentBlock() const;
	virtual void UnlinkAllSubBlocks();

	virtual CPoint GetIntersection(CPoint innerPoint, CPoint outerPoint);

	virtual void LinkLabel(CProMoLabel* label);
	virtual void OnLabelChanged(CProMoLabel* label);
	
protected:
	BOOL m_target;
	CProMoBlockModel* m_blockmodel;

	virtual void RecomputeIntersectionLinks();
	virtual void KeepElementsConnected(double left, double top, double right, double bottom);
	virtual CPoint MapPointToNewRect(CPoint oldPoint, double left, double top, double right, double bottom);
	
	virtual void SetModel(CProMoBlockModel* model);

	virtual void SetShape(const int& type);
	virtual int GetShape() const;

	virtual BOOL AddVertex(const CDoublePoint &point);
	virtual CObArray* GetVertices();
	virtual void ClearVertices();

	virtual void DrawShape(CDC* dc, CRect& rect);
	virtual void Highlight(CDC* dc, CRect rect);
	
	virtual BOOL IsFitCompatible(UINT shapeAnchor, UINT labelAnchor);
	virtual void AdjustToLabel(CProMoLabel* label);
	virtual void RepositionLabels();


private:
	BOOL			m_moved;
	BOOL			m_lockProportions;
	CDoubleRect		m_titleRect;
	int				m_shape;
	CObArray		m_vertices;
	
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
	virtual CString				GetHeaderFromString(CString& str);
	virtual BOOL				GetDefaultFromString(CString& str);


};
#endif //_PROMOBLOCKVIEW_H_

