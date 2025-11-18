/* ==========================================================================

	Copyright © 2025 Technical University of Denmark

	CProMoEdgeView

	Author :		Giovanni Meroni

	Purpose :		"CProMoEdgeView" extends "CDiagramLine" to represent
					all line/edge objects that can be drawn and managed by
					"CProMoEditor". This class contains visual properties
					that lines/edges have. Structural properties are
					defined by the associated model class.

	Description :	With respect to "CDiagramLine", "CProMoEdgeView"
					contains a reference to the "CProMoEdgeModel" object
					representing the model for that edge.
					It is also assumed that an edge view has exactly 1 model.

	Usage :			Views that represent an edge in a graph should be
					derived from this class.

   ========================================================================*/
#include "stdafx.h"
#include "ProMoEdgeView.h"
#include "ProMoEdgeModel.h"
#include "ProMoBlockView.h"
#include "ProMoNameFactory.h"
#include <math.h>
#include "../DiagramEditor/Tokenizer.h"
#include "../FileUtils/FileParser.h"
#include "ProMoLabel.h"


CProMoEdgeView::CProMoEdgeView()
/* ============================================================
	Function :		CProMoEdgeView::CProMoEdgeView
	Description :	Constructor
	Access :		Public

	Return :		void
	Parameters :	none

	Usage :

   ============================================================*/
{
	SetZoom(1.0);
	
	SetMinimumSize(CSize(-1, -1));
	SetType(_T("promo_edge_view"));

	SetName(CProMoNameFactory::GetID());

	m_lockFlags = 0;

	m_bkColor = CLR_NONE;
	m_bkMode = TRANSPARENT;

	m_lineColor = RGB(0, 0, 0);
	m_lineWidth = 1;
	m_lineStyle = PS_SOLID;
	
	m_source = NULL;
	m_dest = NULL;
	m_edgeModel = NULL;
	m_propagating = FALSE;
	m_visible = TRUE;
	SetModel(new CProMoEdgeModel());
}

CProMoEdgeView::~CProMoEdgeView()
/* ============================================================
	Function :		CProMoEdgeView::~CProMoEdgeView
	Description :	Destructor
	Access :		Public

	Return :		void
	Parameters :	none

	Usage :

   ============================================================*/
{
	if (m_source) {
		CProMoEdgeView* oldSourceEdge = m_source;
		oldSourceEdge->SetBottom(GetBottom());
		oldSourceEdge->SetRight(GetRight());
		if (m_dest) {
			oldSourceEdge->SetDestinationEdge(m_dest);
		}
		else {
			oldSourceEdge->m_dest = NULL;
		}
	}
	
	if (m_dest) {
		CProMoEdgeView* oldDestEdge = m_dest;
		oldDestEdge->SetTop(GetTop());
		oldDestEdge->SetLeft(GetLeft());
		if (m_source) {
			oldDestEdge->SetSourceEdge(m_source);
		}
		else {
			oldDestEdge->m_source = NULL;
		}
	}

	SetModel(NULL);

}

CDiagramEntity* CProMoEdgeView::Clone()
/* ============================================================
	Function :		CProMoEdgeView::Clone
	Description :	Clone this object to a new object.

	Return :		CDiagramEntity*	-	The new object.
	Parameters :	none

	Usage :			Call to create a clone of the object. The
					caller will have to delete the object.

   ============================================================*/

{

	CProMoEdgeView* obj = new CProMoEdgeView;
	obj->Copy(this);
	obj->SetName(CProMoNameFactory::GetID());
	return obj;
}

void CProMoEdgeView::Copy(CDiagramEntity* obj)
/* ============================================================
	Function :		CProMoEdgeView::Copy
	Description :	Copy the information in "obj" to this object.
	Access :		Public

	Return :		void
	Parameters :	CDiagramEntity* obj	-	The object to copy
												from.

	Usage :			Copies basic information. from "obj" to this.
					"GetType" can be used to check for the correct
					object type in overridden versions.
   ============================================================*/
{
	CDiagramEntity::Copy(obj);
	CProMoEdgeView* objView = dynamic_cast<CProMoEdgeView*>(obj);
	if (objView) {
		m_bkColor = objView->m_bkColor;
		m_bkMode = objView->m_bkMode;
		m_lineColor = objView->m_lineColor;
		m_lineWidth = objView->m_lineWidth;
		m_lineStyle = objView->m_lineStyle;

		if (GetModel()) {
			GetModel()->Copy(objView->GetModel());
		}
	}
}

void CProMoEdgeView::DrawLine(CDC* dc, CRect rect)
/* ============================================================
	Function :		CProMoEdgeView::DrawLine
	Description :	Draws the line of the edge.

	Return :		void
	Parameters :	CDC* dc		-	The CDC to draw to.
					CRect rect	-	The real rectangle of the
									object.

   ============================================================*/
{
	CPen pen;
	pen.CreatePen(m_lineStyle, m_lineWidth, m_lineColor);
	CPen* pOldPen = dc->SelectObject(&pen);

	COLORREF pOldBkColor = dc->SetBkColor(m_bkColor);
	int pOldBkMode = dc->SetBkMode(m_bkMode);

	dc->MoveTo(rect.TopLeft());
	dc->LineTo(rect.BottomRight());

	//draw the tip only if it is the last segment
	if (m_dest == NULL) {
		DrawHead(dc, rect, 10 * GetZoom());
	}

	//draw the tail only if it is the last segment
	if (m_source == NULL) {
		DrawTail(dc, rect, 10 * GetZoom());
	}

	dc->SetBkMode(pOldBkMode);
	dc->SelectObject(pOldPen);
	dc->SetBkColor(pOldBkColor);

}

void CProMoEdgeView::DrawHead(CDC* dc, CRect rect, double size)
/* ============================================================
	Function :		CProMoEdgeView::DrawHead
	Description :	Draws the head of the edge.
	Access :		Protected

	Return :		void
	Parameters :	CDC* dc		-	The CDC to draw to.
					CRect rect	-	The real rectangle of the 
									object.
					double size	-	The size of the head

	Usage :			The function should clean up all selected
					objects. Note that the CDC is a memory CDC,
					so creating a memory CDC in this function
					will probably not speed up the function.
					Override this function to change the shape
					being drawn.

   ============================================================*/
{

	CPen pen;
	pen.CreatePen(m_lineStyle, m_lineWidth, m_lineColor);
	CPen* pOldPen = dc->SelectObject(&pen);

	CBrush brush;
	brush.CreateSolidBrush(m_lineColor);
	CBrush* pOldBrush = dc->SelectObject(&brush);

	COLORREF pOldBkColor = dc->SetBkColor(m_bkColor);
	int pOldBkMode = dc->SetBkMode(m_bkMode);

	const double dx = static_cast<double>(rect.BottomRight().x) - static_cast<double>(rect.TopLeft().x);
	const double dy = static_cast<double>(rect.BottomRight().y) - static_cast<double>(rect.TopLeft().y);
	const double length = sqrt(dx * dx + dy * dy);
	if (size < 1 || length < size) return;

	// ux,uy is a unit vector parallel to the line.
	const double ux = dx / length;
	const double uy = dy / length;

	// vx,vy is a unit vector perpendicular to ux,uy
	const double vx = -uy;
	const double vy = ux;

	const double half_width = 0.5 * size;

	
	CPoint arrow[3];
	arrow[0] = rect.BottomRight();
	arrow[1] = CPoint (round(rect.BottomRight().x - size * ux + half_width * vx),
			 round(rect.BottomRight().y - size * uy + half_width * vy) );
	arrow[2] = CPoint ( round(rect.BottomRight().x - size * ux - half_width * vx),
			 round(rect.BottomRight().y - size * uy - half_width * vy) );
	dc->Polygon(arrow, 3);
	
	dc->SetBkMode(pOldBkMode);
	dc->SetBkColor(pOldBkColor);
	dc->SelectObject(pOldBrush);
	dc->SelectObject(pOldPen);

}

void CProMoEdgeView::DrawTail(CDC* dc, CRect rect, double size)
/* ============================================================
	Function :		CProMoEdgeView::DrawTail
	Description :	Draws the tail of the edge.
	Access :		Protected

	Return :		void
	Parameters :	CDC* dc		-	The CDC to draw to.
					CRect rect	-	The real rectangle of the
									object.
					double size	-	The size of the tail

	Usage :			The function should clean up all selected
					objects. Note that the CDC is a memory CDC,
					so creating a memory CDC in this function
					will probably not speed up the function.
					Override this function to change the shape
					being drawn.

   ============================================================*/
{
	
	CPen pen;
	pen.CreatePen(m_lineStyle, m_lineWidth, m_lineColor);
	CPen* pOldPen = dc->SelectObject(&pen);

	CBrush brush;
	brush.CreateSolidBrush(m_lineColor);
	CBrush* pOldBrush = dc->SelectObject(&brush);

	COLORREF pOldBkColor = dc->SetBkColor(m_bkColor);
	int pOldBkMode = dc->SetBkMode(m_bkMode);

	// 1. Define the start and end points
	int x1 = rect.TopLeft().x;
	int y1 = rect.TopLeft().y;
	int x2 = rect.BottomRight().x;
	int y2 = rect.BottomRight().y;

	// 2. Calculate the circle radius
	double radius = size / 2;

	// 3. Find the center of the circle: it's the midpoint of (x1, y1) and the second intersection point (x3, y3)
	int dx = x2 - x1;
	int dy = y2 - y1;
	double lineLength = sqrt((double)dx * dx + (double)dy * dy);

	// 4. Parametric form of the line
	// Find t such that the distance from (x1, y1) to (x3, y3) equals the diameter of the circle
	// We need t such that |t| = diameter / lineLength (scaled so that we can reach the exact distance)

	double t = static_cast<double>(size) / lineLength;

	// 5. Find the second intersection point (x3, y3) by moving from (x1, y1) along the line in both directions
	int x3 = static_cast<int>(x1 + t * dx);
	int y3 = static_cast<int>(y1 + t * dy);

	// 6. Calculate the center of the circle: midpoint of (x1, y1) and (x3, y3)
	int centerX = (x1 + x3) / 2;
	int centerY = (y1 + y3) / 2;

	// 7. Calculate the bounding rectangle for the circle centered at (centerX, centerY)
	CDoubleRect circleRect;
	circleRect.left = centerX - radius;
	circleRect.top = centerY - radius;
	circleRect.right = centerX + radius;
	circleRect.bottom = centerY + radius;

	// 8. Draw the circle
	dc->Ellipse(circleRect.ToCRect());

	dc->SetBkMode(pOldBkMode);
	dc->SetBkColor(pOldBkColor);
	dc->SelectObject(pOldBrush);
	dc->SelectObject(pOldPen);
	
}

void CProMoEdgeView::KeepElementsConnected(double left, double top, double right, double bottom)
/* ============================================================
	Function :		CProMoEdgeView::KeepElementsConnected
	Description :	Repositions labels and keeps edges 
					connected.
	Access :		Protected

	Return :		void
	Parameters :	double left		-	Left edge
					double top		-	Top edge
					double right	-	Right edge
					double bottom	-	Bottom edge

	Usage :			Call *before* the object is moved or
					resized to to reposition labels and
					keep edges connected.

   ============================================================*/
{
	if (m_edgeModel) {
		//keep connected edges connected
		if (GetLeft() != left) {
			if (m_source && !m_propagating) {
				CScopedUpdate guard(m_propagating);
				if (!m_source->IsSelected()) {
					m_source->SetRight(left);
				}
			}
		}
		if (GetRight() != right) {
			if (m_dest && !m_propagating) {
				CScopedUpdate guard(m_propagating);
				if (!m_dest->IsSelected()) {
					m_dest->SetLeft(right);
				}
			}
		}
		if (GetTop() != top) {
			if (m_source && !m_propagating) {
				CScopedUpdate guard(m_propagating);
				if (!m_source->IsSelected()) {
					m_source->SetBottom(top);
				}
			}
		}
		if (GetBottom() != bottom) {
			if (m_dest && !m_propagating) {
				CScopedUpdate guard(m_propagating);
				if (!m_dest->IsSelected()) {
					m_dest->SetTop(bottom);
				}
			}
		}
	
		for (int i = 0; i < m_edgeModel->GetLabels()->GetSize(); i++) {
			CProMoLabel* label = dynamic_cast<CProMoLabel*>(m_edgeModel->GetLabels()->GetAt(i));
			if (label) {
				//reposition labels that are not selected (otherwise they will be moved twice)
				if (!label->IsSelected()) {
					label->Reposition();
				}
			}
		}
	}

}

void CProMoEdgeView::Reposition()
/* ============================================================
	Function :		CProMoEdgeView::Reposition
	Description :	Recomputes the intersection with connected
					blocks and keeps linked edges visually 
					connected.
	Access :		Protected

	Return :		void
	Parameters :	none

   ============================================================*/

{
	if (m_edgeModel) {
		if (m_source) {
			SetTop(m_source->GetBottom());
			SetLeft(m_source->GetRight());
		}
		else {
			if (IsFirstSegment() && m_edgeModel->GetSource()) {
				CProMoBlockModel* sourceBlockModel = m_edgeModel->GetSource();
				if (sourceBlockModel) {
					CProMoBlockView* sourceBlockView = sourceBlockModel->GetMainView();
					if (sourceBlockView) {
						CPoint pt = sourceBlockView->GetIntersection(GetRect().TopLeft(), GetRect().BottomRight());
						// No intersection exists, set to block center and compute again
						if (pt.x < 0) {
							pt = sourceBlockView->GetIntersection(CPoint(sourceBlockView->GetRect().BottomRight() - sourceBlockView->GetRect().TopLeft()), GetRect().BottomRight());
						}
						if (pt.x >= 0) {
							SetTop(pt.y);
							SetLeft(pt.x);
						}
					}
				}
			}
		}

		if (m_dest) {
			SetBottom(m_dest->GetTop());
			SetRight(m_dest->GetLeft());
		}
		else {
			if (IsLastSegment() && m_edgeModel->GetDestination()) {
				CProMoBlockModel* destBlockModel = m_edgeModel->GetDestination();
				if (destBlockModel) {
					CProMoBlockView* destBlockView = destBlockModel->GetMainView();
					if (destBlockView) {
						CPoint pt = destBlockView->GetIntersection(GetRect().BottomRight(), GetRect().TopLeft());
						// No intersection exists, set to block center and compute again
						if (pt.x < 0) {
							pt = destBlockView->GetIntersection(GetRect().TopLeft(), CPoint(destBlockView->GetRect().BottomRight() - destBlockView->GetRect().TopLeft()));
						}
						if (pt.x >= 0) {
							SetBottom(pt.y);
							SetRight(pt.x);
						}
					}
				}
			}
		}
	}
}

void CProMoEdgeView::Draw(CDC* dc, CRect rect)
/* ============================================================
	Function :		CProMoEdgeView::Draw
	Description :	Draws the object.

	Return :		void
	Parameters :	CDC* dc		-	The CDC to draw to.
					CRect rect	-	The real rectangle of the
									object.

	Usage :			The function should clean up all selected
					objects. Note that the CDC is a memory CDC,
					so creating a memory CDC in this function
					will probably not speed up the function.

   ============================================================*/
{
	if (m_visible) {
		DrawLine(dc, rect);
	}
}

int CProMoEdgeView::GetHitCode(const CPoint& point, const CRect& rect) const
/* ============================================================
	Function :		CProMoEdgeView::GetHitCode
	Description :	Returns the hit point constant for "point"
					assuming the object rectangle "rect".
	Access :		Public

	Return :		int				-	The hit point,
										"DEHT_NONE" if none.
	Parameters :	CPoint point	-	The point to check
					CRect rect		-	The rect to check

	Usage :			Call to see in what part of the object point
					lies. The hit point can be one of the following:
						"DEHT_NONE" No hit-point
						"DEHT_BODY" Inside object body
						"DEHT_TOPLEFT" Top-left corner
						"DEHT_BOTTOMRIGHT" Bottom-right corner
						"DEHT_CENTER" Center of the object body 
							(i.e., in the middle of the line)

   ============================================================*/
{
	CRect rectTest = GetSelectionMarkerRect(DEHT_CENTER, rect);
	if (rectTest.PtInRect(point)) {
		return DEHT_CENTER;
	}
	return CDiagramLine::GetHitCode(point, rect);
}

HCURSOR CProMoEdgeView::GetCursor(int hit) const
/* ============================================================
	Function :		CProMoEdgeView::GetCursor
	Description :	Returns the cursor for a specific hit
					point.
	Access :		Public

	Return :		HCURSOR	-	The cursor to display, or "NULL"
								if default.
	Parameters :	int hit	-	The hit point constant ("DEHT_",
								defined in DiagramEntity.h) to
								show a cursor for.

	Usage :			Shows the cursor for a subset of the hit
					points. Will also show cursors different
					from the standard ones.
					"hit" can be one of the following:
						"DEHT_NONE" No hit-point
						"DEHT_BODY" Inside object body
						"DEHT_TOPLEFT" Top-left corner
						"DEHT_TOPMIDDLE" Middle top-side
						"DEHT_TOPRIGHT" Top-right corner
						"DEHT_BOTTOMLEFT" Bottom-left corner
						"DEHT_BOTTOMMIDDLE" Middle bottom-side
						"DEHT_BOTTOMRIGHT" Bottom-right corner
						"DEHT_LEFTMIDDLE" Middle left-side
						"DEHT_RIGHTMIDDLE" Middle right-side
						"DEHT_CENTER" Center of the object body 
							(i.e., in the middle of the line)

   ============================================================*/
{
	if (hit == DEHT_CENTER) {
		return LoadCursor(NULL, IDC_SIZEALL);
	}
	return CDiagramLine::GetCursor(hit);
}


CDiagramEntity* CProMoEdgeView::CreateFromString(const CString& str)
/* ============================================================
	Function :		CProMoEdgeView::CreateFromString
	Description :	Static factory function that creates and
					returns an instance of this class if str
					is a valid representation.

	Return :		CDiagramEntity*		-	The object, or NULL
											if str is not a
											representation of
											this type.
	Parameters :	const CString& str	-	The string to create
											from.

	Usage :			Can be used as a factory for text file loads.
					Each object type should have its own
					version - the default one is a model
					implementation.

   ============================================================*/
{

	CProMoEdgeView* obj = new CProMoEdgeView;
	if (!obj->FromString(str))
	{
		delete obj;
		obj = NULL;
	}

	return obj;

}


CDiagramEntity* CProMoEdgeView::CreateFromString(const CString& str, CProMoModel* model)
/* ============================================================
	Function :		CProMoEdgeView::CreateFromString
	Description :	Static factory function that creates and
					returns an instance of this class if str
					is a valid representation.

	Return :		CDiagramEntity*		-	The object, or NULL
											if str is not a
											representation of
											this type.
	Parameters :	const CString& str	-	The string to create
											from.
					CProMoModel* model	-	A model to be
											associated to the
											object being created.

	Usage :			Can be used as a factory for text file loads.
					Each object type should have its own
					version - the default one is a model
					implementation.

   ============================================================*/
{

	CProMoEdgeView* obj = new CProMoEdgeView;
	if (!obj->FromString(str))
	{
		delete obj;
		obj = NULL;
	}
	else {
		CProMoEdgeModel* blockModel = dynamic_cast<CProMoEdgeModel*>(model);

		if (blockModel) {
			obj->SetModel(blockModel);
		}
	}

	return obj;

}

void CProMoEdgeView::SetSource(CDiagramEntity *source)
/* ============================================================
	Function :		CProMoEdgeView::SetSource
	Description :	Makes the object being passed as input
					parameter the source of this edge, while
					keeping the model relations consistent.
	Access :		Public

	Return :		void
	Parameters :	CDiagramEntity* source	-	the object that
												should be the
												source

   ============================================================*/
{
	CProMoBlockView* blockView = dynamic_cast<CProMoBlockView*>(source);
	CProMoEdgeView* edgeView = dynamic_cast<CProMoEdgeView*>(source);

	// If the new source is a block, set it.
	SetSourceBlock(blockView);
	// If the new source is an edge, set it. Otherwise, set it to NULL;
	SetSourceEdge(edgeView);
	
	Reposition();

}

void CProMoEdgeView::SetDestination(CDiagramEntity *destination)
/* ============================================================
	Function :		CProMoEdgeView::SetDestination
	Description :	Makes the object being passed as input
					parameter the destination of this edge, 
					while keeping the model relations 
					consistent.
	Access :		Public

	Return :		void
	Parameters :	CDiagramEntity* destination	-	the object
													that should
													be the
													destination

   ============================================================*/
{
	CProMoEdgeView* edgeView = dynamic_cast<CProMoEdgeView*>(destination);
	CProMoBlockView* blockView = dynamic_cast<CProMoBlockView*>(destination);
	
	// If the new destination is a block, set it.
	SetDestinationBlock(blockView);
	// If the new destination is an edge, set it. Otherwise, set it to NULL;
	SetDestinationEdge(edgeView);

	Reposition();

}

CDiagramEntity* CProMoEdgeView::GetSource() const
/* ============================================================
	Function :		CProMoEdgeView::GetSource
	Description :	Returns a pointer to the source object
	Access :		Public

	Return :		CDiagramEntity*	-	A pointer to the source
										object
	Parameters :	none

   ============================================================*/
{
	if (m_source) {
		return m_source;
	}
	if (m_edgeModel) {
		if (IsFirstSegment()) {
			if (m_edgeModel->GetSource()) {
				return m_edgeModel->GetSource()->GetMainView();
			}
		}
	}
	return NULL;
}

CDiagramEntity* CProMoEdgeView::GetDestination() const
/* ============================================================
	Function :		CProMoEdgeView::GetDestination
	Description :	Returns a pointer to the destination object
	Access :		Public

	Return :		CDiagramEntity*	-	A pointer to the
										destination object
	Parameters :	none

   ============================================================*/
{
	if (m_dest) {
		return m_dest;
	}
	if (m_edgeModel) {
		if (IsLastSegment()) {
			if (m_edgeModel->GetDestination()) {
				return m_edgeModel->GetDestination()->GetMainView();
			}
		}
	}
	return NULL;
}

BOOL CProMoEdgeView::IsFirstSegment() const
/* ============================================================
	Function :		CProMoEdgeView::IsFirstSegment
	Description :	Returns TRUE if this is the first segment
					composing the edge.

	Return :		BOOL	-	TRUE if this is the first 
								segment composing the edge
	Parameters :	none

   ============================================================*/
{
	if (m_source){
		return FALSE;
	}
	return TRUE;
}

BOOL CProMoEdgeView::IsLastSegment() const
/* ============================================================
	Function :		CProMoEdgeView::IsLastSegment
	Description :	Returns TRUE if this is the last segment
					composing the edge.

	Return :		BOOL	-	TRUE if this is the last
								segment composing the edge
	Parameters :	none

   ============================================================*/
{
	if (m_dest) {
		return FALSE;
	}
	return TRUE;
}

void CProMoEdgeView::SetRect(CRect rect)
/* ============================================================
	Function :		CProMoEdgeView::SetRect
	Description :	Sets the object rectangle, normalized.
	Access :		Public

	Return :		void
	Parameters :	CRect rect	-	The rectangle to set.

	Usage :			Call to place the object.

   ============================================================*/
{

	CDiagramLine::SetRect(rect);

}

void CProMoEdgeView::SetRect(double left, double top, double right, double bottom)
/* ============================================================
	Function :		CProMoEdgeView::SetRect
	Description :	Sets the object rectangle.
	Access :		Public

	Return :		void
	Parameters :	double left		-	Left edge
					double top		-	Top edge
					double right	-	Right edge
					double bottom	-	Bottom edge

	Usage :			Call to place the object.

   ============================================================*/
{

	CDiagramEntity::SetRect(left, top, right, bottom);

}

void CProMoEdgeView::SetLeft(double left)
/* ============================================================
	Function :		CProMoEdgeView::SetLeft
	Description :	Sets the left edge of the object rectangle
	Access :		Public

	Return :		void
	Parameters :	double left	-	New left position

	Usage :			Call to set the left edge of the object.
					The object coordinates are expressed as
					double values to allow unlimited zoom.

   ============================================================*/
{
	KeepElementsConnected(left, GetTop(), GetRight(), GetBottom());
	CDiagramLine::SetLeft(left);
}

void CProMoEdgeView::SetRight(double right)
/* ============================================================
	Function :		CProMoEdgeView::SetRight
	Description :	Sets the right edge of the object
					rectangle
	Access :		Public

	Return :		void
	Parameters :	double right	-	New right position

	Usage :			Call to set the right edge of the object.
					The object coordinates are expressed as
					double values to allow unlimited zoom.

   ============================================================*/
{
	KeepElementsConnected(GetLeft(), GetTop(), right, GetBottom());
	CDiagramLine::SetRight(right);

}

void CProMoEdgeView::SetTop(double top)
/* ============================================================
	Function :		CProMoEdgeView::SetTop
	Description :	Sets the top edge of the object rectangle
	Access :		Public

	Return :		void
	Parameters :	double top	-	New top position

	Usage :			Call to set the top edge of the object.
					The object coordinates are expressed as
					double values to allow unlimited zoom.

   ============================================================*/
{
	KeepElementsConnected(GetLeft(), top, GetRight(), GetBottom());
	CDiagramLine::SetTop(top);
	
}

void CProMoEdgeView::SetBottom(double bottom)
/* ============================================================
	Function :		CProMoEdgeView::SetBottom
	Description :	Sets the bottom edge of the object
					rectangle
	Access :		Public

	Return :		void
	Parameters :	double bottom	-	New bottom position

	Usage :			Call to set the bottom edge of the object.
					The object coordinates are expressed as
					double values to allow unlimited zoom.

   ============================================================*/
{
	KeepElementsConnected(GetLeft(), GetTop(), GetRight(), bottom);
	CDiagramLine::SetBottom(bottom);
	
}


CProMoEdgeView* CProMoEdgeView::Split()
/* ============================================================
	Function :		CProMoEdgeView::Split
	Description :	Splits this edge view into two connected 
					edge views, both sharing the same model.
					This edge view will be the first view. The
					second view will be returned.

	Return :		CProMoEdgeView*	-	The second edge view.
	Parameters :	none

	Usage :			Call to split this edge view. The caller 
					needs to manage the edge view being 
					returned.

   ============================================================*/

{
	if (m_edgeModel) {
		CDiagramEntity* newEntity = Clone();

		CProMoEdgeView* newEdge = dynamic_cast<CProMoEdgeView*>(newEntity);

		if (newEdge) {
			//compute the length and position of the new edge
			CRect newEdgeRect(GetRect());
			newEdgeRect.top = newEdgeRect.bottom - (newEdgeRect.Height() / 2);;
			newEdgeRect.left = newEdgeRect.right - (newEdgeRect.Width() / 2);;
			newEdge->Select(FALSE);
			CProMoBlockModel* sourceBlockModel = m_edgeModel->GetSource();
			CProMoBlockModel* destBlockModel = m_edgeModel->GetDestination();
			//update edge links
			newEdge->SetDestinationEdge(dynamic_cast<CProMoEdgeView*>(GetDestination()));
			newEdge->SetSourceEdge(this);
			if (destBlockModel) {
				newEdge->SetDestinationBlock(destBlockModel->GetMainView());
			}
			if (sourceBlockModel) {
				newEdge->SetSourceBlock(sourceBlockModel->GetMainView());
			}
			newEdge->SetRect(newEdgeRect);
			//clear duplicated properties
			newEdge->SetTitle(_T(""));
			return newEdge;
		}
	}
	return NULL;
	
}

void CProMoEdgeView::AutoResize()
/* ============================================================
	Function :		CProMoEdgeView::AutoResize
	Description :	Automatically resizes edges. Not implemented
					for this class.
	Access :		Public

	Return :		void
	Parameters :	none

   ============================================================*/
{

}

CProMoEdgeModel* CProMoEdgeView::GetEdgeModel() const
/* ============================================================
	Function :		CProMoEdgeView::GetEdgeModel
	Description :	Returns a pointer to the model of this
					edge
	Access :		Public

	Return :		CProMoEdgeModel*		-	A pointer to the
												model
	Parameters :	none

   ============================================================*/
{
	return m_edgeModel;
}

CProMoModel* CProMoEdgeView::GetModel() const
/* ============================================================
	Function :		CProMoEdgeView::GetModel
	Description :	Returns a pointer to the model of this
					edge
	Access :		Public

	Return :		CProMoModel*		-	A pointer to the
											model
	Parameters :	none

   ============================================================*/
{
	return m_edgeModel;
}

void CProMoEdgeView::SetModel(CProMoModel* model)
/* ============================================================
	Function :		CProMoEdgeView::SetModel
	Description :	Makes the object being passed as input
					parameter the model for this edge
	Access :		Protected

	Return :		void
	Parameters :	CProMoModel* model		-	the object that
												should be the
												model

   ============================================================*/
{
	CProMoEdgeModel* edgeModel = dynamic_cast<CProMoEdgeModel*>(model);
	if (m_edgeModel != edgeModel) {
		CProMoEdgeModel* oldModel = m_edgeModel;
		m_edgeModel = edgeModel;
		
		//link this class to the new model
		if (edgeModel) {
			edgeModel->LinkView(this);
			if (m_source) {
				m_source->SetModel(edgeModel);
			}
			if (m_dest) {
				m_dest->SetModel(edgeModel);
			}
		}
		//unlink this class from the old model
		if (oldModel) {
			oldModel->UnlinkView(this);
			//if the old model has no views, delete it
			if (oldModel->GetViews()->GetSize() == 0) {
				delete oldModel;
			}
		}
	}
}

void CProMoEdgeView::SetSourceEdge(CProMoEdgeView* source)
/* ============================================================
	Function :		CProMoEdgeView::SetSourceEdge
	Description :	Makes the object being passed as input
					parameter the source of this edge, while
					keeping the model relations consistent.
	Access :		Protected

	Return :		void
	Parameters :	CProMoEdgeView* source	-	the object that
												should be the
												source

   ============================================================*/
{
	if (m_edgeModel) {
		//save the old source edge view
		CProMoEdgeView* oldSourceView = m_source;

		// the source edge view has changed

		if (source != oldSourceView) {

			if (source) {
				m_source = source;
				source->SetDestinationEdge(this);

				CProMoBlockModel* oldSourceModel = ((CProMoEdgeModel*)source->GetModel())->GetSource();
				source->SetModel(GetModel());
				((CProMoEdgeModel*)source->GetModel())->SetSource(oldSourceModel);
			}

			else {
				m_source = NULL;

				CProMoBlockModel* oldDestModel = m_edgeModel->GetDestination();
				m_edgeModel->SetDestination(NULL);
				SetModel(dynamic_cast<CProMoEdgeModel*>(GetModel()->Clone()));
				m_edgeModel->SetDestination(oldDestModel);
			}

			if (oldSourceView) {
				oldSourceView->m_dest = NULL;
			}
		}
	}
}

void CProMoEdgeView::SetSourceBlock(CProMoBlockView* source)
/* ============================================================
	Function :		CProMoEdgeView::SetSourceBlock
	Description :	Makes the object being passed as input
					parameter the source of this edge, while
					keeping the model relations consistent.
	Access :		Protected

	Return :		void
	Parameters :	CProMoBlockView* source	-	the object that
												should be the
												source

   ============================================================*/
{
	if (m_edgeModel) {
		if (source) {
			//connect the elements at the model level
			m_edgeModel->SetSource((CProMoBlockModel*)(source->GetModel()));
		}
		else {
			m_edgeModel->SetSource(NULL);
		}
	}
}

void CProMoEdgeView::SetDestinationEdge(CProMoEdgeView* destination)
/* ============================================================
	Function :		CProMoEdgeView::SetDestinationEdge
	Description :	Makes the object being passed as input
					parameter the destination of this edge,
					while keeping the model relations
					consistent.
	Access :		Protected

	Return :		void
	Parameters :	CProMoEdgeView* destination	-	the object
													that should
													be the
													destination

   ============================================================*/
{
	if (m_edgeModel) {
		//save the old source edge view
		CProMoEdgeView* oldDestView = m_dest;

		if (oldDestView != destination) {
			if (destination) {
				m_dest = destination;
				destination->SetSourceEdge(this);

				CProMoBlockModel* oldDestModel = ((CProMoEdgeModel*)destination->GetModel())->GetDestination();
				destination->SetModel(GetModel());
				((CProMoEdgeModel*)destination->GetModel())->SetDestination(oldDestModel);

			}

			else {
				m_dest = NULL;

				CProMoBlockModel* oldSourceModel = m_edgeModel->GetSource();
				m_edgeModel->SetSource(NULL);
				SetModel(dynamic_cast<CProMoEdgeModel*>(GetModel()->Clone()));
				m_edgeModel->SetSource(oldSourceModel);
			}

			// the source edge view has changed
			if (oldDestView) {
				oldDestView->m_source = NULL;
			}
		}
	}
}

void CProMoEdgeView::SetDestinationBlock(CProMoBlockView* destination)
/* ============================================================
	Function :		CProMoEdgeView::SetDestinationBlock
	Description :	Makes the object being passed as input
					parameter the destination of this edge,
					while keeping the model relations
					consistent.
	Access :		Protected

	Return :		void
	Parameters :	CProMoBlockView* destination	-	the object
													that should
													be the
													destination

   ============================================================*/
{
	if (m_edgeModel) {
		if (destination) {
			//connect the elements at the model level
			m_edgeModel->SetDestination((CProMoBlockModel*)(destination->GetModel()));

		}
		else {
			m_edgeModel->SetDestination(NULL);
		}
	}

}

CString CProMoEdgeView::GetHeaderFromString(CString& str)
/* ============================================================
	Function :		CProMoEdgeView::GetHeaderFromString
	Description :	Gets the header from "str".
	Access :		Protected

	Return :		CString			-	The type of "str".
	Parameters :	CString& str	-	"CString" to get type from.

	Usage :			Call as a part of loading the object. "str"
					will have the type removed after the call.

   ============================================================*/
{
	CString header;

	CFileParser::GetHeaderFromString(str, header);

	return header;
}


CString CProMoEdgeView::GetDefaultGetString() const
{
	/* ============================================================
	Function :		CProMoEdgeView::GetDefaultString
	Description :	Gets the default properties of the object
					as a string.
	Access :		Protected

	Return :		CString	-	Resulting string
	Parameters :	none

	Usage :			Call as a part of the saving of objects
					to disk.

   ============================================================*/

	ASSERT_VALID(this->GetModel());

	CString str;

	CString model = GetModel()->GetName();
	CFileParser::EncodeString(model);
	
	CString title = GetTitle();
	CFileParser::EncodeString(title);
	
	CString name = GetName();
	CFileParser::EncodeString(name);
	
	CString sourceString = _T("");

	if (m_source) {
		sourceString = m_source->GetName();
		CFileParser::EncodeString(sourceString);
	}

	CString destString = _T("");

	if (m_dest) {
		destString = m_dest->GetName();
		CFileParser::EncodeString(destString);
	}

	str.Format(_T("%s:%s,%f,%f,%f,%f,%s,%i,%s,%s,%s,%i,%i,%i,%i,%i,%i"), 
		(LPCTSTR)GetType(), (LPCTSTR)name, GetLeft(), GetTop(), GetRight(), GetBottom(), (LPCTSTR)title, GetGroup(), (LPCTSTR)model, (LPCTSTR)sourceString, (LPCTSTR)destString, m_lockFlags,
		m_bkColor, m_bkMode, m_lineColor, m_lineWidth, m_lineStyle);

	return str;

}

BOOL CProMoEdgeView::GetDefaultFromString(CString& str)
/* ============================================================
	Function :		CProMoEdgeView::GetDefaultFromString
	Description :	Gets the default properties from "str"
	Access :		Protected

	Return :		BOOL			-	"TRUE" if the default
										properties could be loaded ok.
	Parameters :	CString& str	-	"CString" to get the
										default properties from.

	Usage :			Call as a part of loading the object from
					disk. The default object properties will
					be stripped from "str" and the object
					properties set from the data.

   ============================================================*/
{
	BOOL result = FALSE;
	
	CTokenizer* tok = CFileParser::Tokenize(str);
	if (tok) {

		int size = tok->GetSize();

		if (size >= 10)
		{
			CString name;
			double left;
			double top;
			double right;
			double bottom;
			CString title;
			int group;
			CString model;
			CString source;
			CString dest;

			int count = 0;

			tok->GetAt(count++, name);
			tok->GetAt(count++, left);
			tok->GetAt(count++, top);
			tok->GetAt(count++, right);
			tok->GetAt(count++, bottom);
			tok->GetAt(count++, title);
			tok->GetAt(count++, group);
			tok->GetAt(count++, model);
			tok->GetAt(count++, source);
			tok->GetAt(count++, dest);

			CDiagramEntity::SetRect(left, top, right, bottom);

			CFileParser::DecodeString(title);
			CFileParser::DecodeString(name);

			SetTitle(title);
			SetName(name);
			SetGroup(group);
			
			// missing style attributes should not prevent the block from loading
			if (size >= 16) {
				int lockFlags;
				COLORREF bkColor;
				int bkMode;
				COLORREF lineColor;
				int lineWidth;
				int lineStyle;
				
				tok->GetAt(count++, lockFlags);
				tok->GetAt(count++, bkColor);
				tok->GetAt(count++, bkMode);
				tok->GetAt(count++, lineColor);
				tok->GetAt(count++, lineWidth);
				tok->GetAt(count++, lineStyle);
				
				m_bkColor = bkColor;
				m_bkMode = bkMode;
				m_lineColor = lineColor;
				m_lineWidth = lineWidth;
				m_lineStyle = lineStyle;
				m_lockFlags = lockFlags;
			}

			result = TRUE;
		}
		delete tok;
	}

	return result;

}


void CProMoEdgeView::DrawSelectionMarkers(CDC* dc, CRect rect) const
/* ============================================================
	Function :		CProMoEdgeView::DrawSelectionMarkers
	Description :	Draws selection markers for this object.
	Access :		Public

	Return :		void
	Parameters :	CDC* dc		-	"CDC" to draw to.
					CRect rect	-	True object rectangle.

	Usage :			Draws a subset of the standard selection
					markers. Overridden to also draw the center
					marker, that can be used to split the edge
					into two connected segments.

   ============================================================*/
{
	CRect rectSelect;

	dc->SelectStockObject(BLACK_BRUSH);
	rectSelect = GetSelectionMarkerRect(DEHT_CENTER, rect);
	dc->Rectangle(rectSelect);

	CDiagramLine::DrawSelectionMarkers(dc, rect);
}

void CProMoEdgeView::ShowPopup(CPoint point, CWnd* parent)
/* ============================================================
	Function :		CProMoEdgeView::ShowPopup
	Description :	Shows the popup menu for the object.
	Access :		Public

	Return :		void
	Parameters :	CPoint point	-	The point to track.
					CWnd* parent	-	The parent "CWnd" of the
										menu (should be the
										"CDiagramEditor")

   ============================================================*/
{

	CMenu menu;
	if (menu.CreatePopupMenu())
	{

		menu.AppendMenu(MF_STRING, ID_EDIT_CUT, _T("Cut"));
		menu.AppendMenu(MF_STRING, ID_EDIT_COPY, _T("Copy"));
		menu.TrackPopupMenu(TPM_LEFTALIGN | TPM_RIGHTBUTTON, point.x, point.y, parent);

	}

}

CRect CProMoEdgeView::GetSelectionMarkerRect(UINT marker, CRect rect) const
/* ============================================================
	Function :		CProMoEdgeView::GetSelectionMarkerRect
	Description :	Gets the selection marker rectangle for
					marker, given the true object rectangle
					"rect".
	Access :		Protected


	Return :		CRect		-	The marker rectangle
	Parameters :	UINT marker	-	The marker type ("DEHT_"-
									constants defined in
									DiargramEntity.h)
					CRect rect	-	The object rectangle

	Usage :			"marker" can be one of the following:
						"DEHT_NONE" No hit-point
						"DEHT_BODY" Inside object body
						"DEHT_TOPLEFT" Top-left corner
						"DEHT_TOPMIDDLE" Middle top-side
						"DEHT_TOPRIGHT" Top-right corner
						"DEHT_BOTTOMLEFT" Bottom-left corner
						"DEHT_BOTTOMMIDDLE" Middle bottom-side
						"DEHT_BOTTOMRIGHT" Bottom-right corner
						"DEHT_LEFTMIDDLE" Middle left-side
						"DEHT_RIGHTMIDDLE" Middle right-side
						"DEHT_CENTER" Center of the object body 
							(i.e., in the middle of the line)

   ============================================================*/
{
	CRect rectMarker;
	int horz = GetMarkerSize().cx / 2;
	int vert = GetMarkerSize().cy / 2;

	if (marker == DEHT_CENTER) {

		rectMarker.SetRect(rect.left + (rect.Width() / 2) - horz,
			rect.top + (rect.Height() / 2) - vert,
			rect.left + (rect.Width() / 2) + horz,
			rect.top + (rect.Height() / 2) + vert);
		return rectMarker;

	}
	return CDiagramLine::GetSelectionMarkerRect(marker, rect);
}


CString CProMoEdgeView::GetSourceFromString(const CString& str)
/* ============================================================
	Function :		CProMoEdgeView::GetSourceFromString
	Description :	Static factory function that 
					parses a formatted string and extracts the
					name of the source object
	Access :		Public

	Return :		CString			-	The name of the source
										object
	Parameters :	CString& str	-	The string to be parsed

   ============================================================*/
{
	CTokenizer* tok = CFileParser::Tokenize(str);
	CString sourceName;
	if (tok) {
		tok->GetAt(8, sourceName);
		delete tok;
	}
	return sourceName;
}

CString CProMoEdgeView::GetDestinationFromString(const CString& str)
/* ============================================================
	Function :		CProMoEdgeView::GetDestinationFromString
	Description :	Static factory function that 
					parses a formatted string and extracts the
					name of the destination object
	Access :		Public

	Return :		CString			-	The name of the 
										destination object
	Parameters :	CString& str	-	The string to be parsed

   ============================================================*/
{
	CTokenizer* tok = CFileParser::Tokenize(str);
	CString destName;
	if (tok) {
		tok->GetAt(9, destName);
		delete tok;
	}
	return destName;
}

CString CProMoEdgeView::GetModelFromString(const CString& str)
/* ============================================================
	Function :		CProMoEdgeView::GetModelFromString
	Description :	Static factory function that 
					parses a formatted string and extracts the
					name of the associated model object
	Access :		Public

	Return :		CString			-	The name of the model
	Parameters :	CString& str	-	The string to be parsed

   ============================================================*/
{
	CTokenizer* tok = CFileParser::Tokenize(str);
	CString modelName;
	if (tok) {
		tok->GetAt(7, modelName);
		delete tok;
	}
	return modelName;
}

CString CProMoEdgeView::GetNameFromString(const CString& str)
/* ============================================================
	Function :		CProMoEdgeView::GetNameFromString
	Description :	Static factory function that 
					parses a formatted string and extracts the
					name of the object
	Access :		Public

	Return :		CString			-	The name of the object
	Parameters :	CString& str	-	The string to be parsed

   ============================================================*/
{
	CTokenizer* tok = CFileParser::Tokenize(str);
	CString name;
	if (tok) {
		tok->GetAt(0, name);
		delete tok;
	}
	return name;
}

void CProMoEdgeView::LinkLabel(CProMoLabel* label)
/* ============================================================
	Function :		CProMoEdgeView::LinkView
	Description :	Links a new label to this object.
	Access :		Protected

	Return :		void
	Parameters :	CProMoLabel* label - the label to link

   ============================================================*/
{
	if (label && m_edgeModel) {
		m_edgeModel->LinkLabel(label);
	}
}

void CProMoEdgeView::OnLabelChanged(CProMoLabel* label)
/* ============================================================
	Function :		CProMoEdgeView::OnLabelChanged
	Description :	Notification that a label has changed.
	Access :		Public

	Return :		void
	Parameters :	CProMoLabel* label	-	Label that changed.

	Usage :			Can be called by a label to notify the
					view that it changed, and to trigger UI
					updates. Currently not used.

   ============================================================*/
{
	
}

BOOL CProMoEdgeView::IsLocked(const unsigned int& flag) const
/* ============================================================
	Function :		CProMoEdgeView::IsLocked
	Description :	Returns if the specified property (or
					combination of properties) is locked

	Access :		Public

	Return :		BOOL				-	"TRUE" if the
											property specified
											is locked
	Parameters :	unsigned int& flag	-	The property (or
											combination) to
											check

   ============================================================*/
{
	return (m_lockFlags & flag) != 0;
}

unsigned int CProMoEdgeView::GetLock() const
/* ============================================================
	Function :		CProMoEdgeView::IsLocked
	Description :	Returns the specified property (or
					combination of properties)

	Access :		Public

	Return :		unsigned int& flag	-	The property (or
											combination) being
											locked
	Parameters :	none

   ============================================================*/
{
	return m_lockFlags;
}

void CProMoEdgeView::SetLock(const unsigned int& flag)
/* ============================================================
	Function :		CProMoEdgeView::SetLock
	Description :	Locks the specified property (or combination
					of properties)

	Access :		Public

	Return :		void
	Parameters :	unsigned int& flag	-	The property (or
											combination) to
											lock

   ============================================================*/
{
	m_lockFlags = flag;
}

CString CProMoEdgeView::GetFontName() const
/* ============================================================
	Function :		CProMoEdgeView::GetFontName()
	Description :	Returns the name of the font used to
					display the labels
	Access :		Public

	Return :		CString		-	The name of the font used
									to display the label
	Parameters :	none

   ============================================================*/
{
	CString fontName;
	BOOL hasValue = FALSE;

	if (m_edgeModel) {
		CObArray* labels = m_edgeModel->GetLabels();
		if (labels) {
			for (int i = 0; i < labels->GetSize(); i++) {
				CProMoLabel* label = dynamic_cast<CProMoLabel*>(labels->GetAt(i));
				if (!label || label->IsLocked(LOCK_FONTNAME)) {
					continue;
				}
				CString currValue = label->GetFontName();
				if (!hasValue) {
					fontName = currValue;
					hasValue = TRUE;
				}
				else if (fontName != currValue) {
					return CString();
				}
			}
		}
	}
	return fontName;
}

unsigned int CProMoEdgeView::GetFontSize() const
/* ============================================================
	Function :		CProMoEdgeView::GetFontSize()
	Description :	Returns the size of the font used to
					display the labels
	Access :		Public

	Return :		unsigned int	-	The size of the font used
										to display the label
	Parameters :	none

   ============================================================*/
{
	unsigned int fontSize = 0;
	BOOL hasValue = FALSE;

	if (m_edgeModel) {
		CObArray* labels = m_edgeModel->GetLabels();
		if (labels) {
			for (int i = 0; i < labels->GetSize(); i++) {
				CProMoLabel* label = dynamic_cast<CProMoLabel*>(labels->GetAt(i));
				if (!label || label->IsLocked(LOCK_FONTSIZE)) {
					continue;
				}
				unsigned int currValue = label->GetFontSize();
				if (!hasValue) {
					fontSize = currValue;
					hasValue = TRUE;
				}
				else if (fontSize != currValue) {
					return 0;
				}
			}
		}
	}
	return fontSize;
}

unsigned int CProMoEdgeView::GetFontWeight() const
/* ============================================================
	Function :		CProMoEdgeView::GetFontWeight()
	Description :	Returns the weight of the font used to
					display the labels
	Access :		Public

	Return :		unsigned int	-	The weight of the font used
										to display the label
	Parameters :	none

   ============================================================*/
{
	unsigned int fontWeight = 0;
	BOOL hasValue = FALSE;

	if (m_edgeModel) {
		CObArray* labels = m_edgeModel->GetLabels();
		if (labels) {
			for (int i = 0; i < labels->GetSize(); i++) {
				CProMoLabel* label = dynamic_cast<CProMoLabel*>(labels->GetAt(i));
				if (!label || label->IsLocked(LOCK_FONTWEIGHT)) {
					continue;
				}
				unsigned int currValue = label->GetFontWeight();
				if (!hasValue) {
					fontWeight = currValue;
					hasValue = TRUE;
				}
				else if (fontWeight != currValue) {
					return 0;
				}
			}
		}
	}
	return fontWeight;
}

BOOL CProMoEdgeView::IsFontItalic() const
/* ============================================================
	Function :		CProMoEdgeView::IsFontItalic()
	Description :	Returns if the font used to display the
					labels are in italic
	Access :		Public

	Return :		BOOL		-	"TRUE" if the font used
									to display the label is in
									italic
	Parameters :	none

   ============================================================*/
{
	BOOL italic = FALSE;
	BOOL hasValue = FALSE;

	if (m_edgeModel) {
		CObArray* labels = m_edgeModel->GetLabels();
		if (labels) {
			for (int i = 0; i < labels->GetSize(); i++) {
				CProMoLabel* label = dynamic_cast<CProMoLabel*>(labels->GetAt(i));
				if (!label || label->IsLocked(LOCK_FONTITALIC))
					continue;

				BOOL currValue = label->IsFontItalic();
				if (!hasValue) {
					italic = currValue;
					hasValue = TRUE;
				}
				else if (italic != currValue) {
					// mixed state, return sentinel
					return FALSE;
				}
			}
		}
	}
	return italic;
}

BOOL CProMoEdgeView::IsFontUnderline() const
/* ============================================================
	Function :		CProMoEdgeView::IsFontUnderline()
	Description :	Returns if the font used to display the
					labels are underlined
	Access :		Public

	Return :		BOOL		-	"TRUE" if the font used
									to display the label is
									underlined
	Parameters :	none

   ============================================================*/
{
	BOOL underline = FALSE;
	BOOL hasValue = FALSE;

	if (m_edgeModel) {
		CObArray* labels = m_edgeModel->GetLabels();
		if (labels) {
			for (int i = 0; i < labels->GetSize(); i++) {
				CProMoLabel* label = dynamic_cast<CProMoLabel*>(labels->GetAt(i));
				if (!label || label->IsLocked(LOCK_FONTUNDERLINE))
					continue;

				BOOL currValue = label->IsFontUnderline();
				if (!hasValue) {
					underline = currValue;
					hasValue = TRUE;
				}
				else if (underline != currValue) {
					// mixed state, return sentinel
					return FALSE;
				}
			}
		}
	}
	return underline;
}

BOOL CProMoEdgeView::IsFontStrikeOut() const
/* ============================================================
	Function :		CProMoEdgeView::IsFontStrikeOut()
	Description :	Returns if the font used to display the
					labels are stroken out
	Access :		Public

	Return :		BOOL		-	"TRUE" if the font used
									to display the label is
									stroken out
	Parameters :	none

   ============================================================*/
{
	BOOL strikeOut = FALSE;
	BOOL hasValue = FALSE;

	if (m_edgeModel) {
		CObArray* labels = m_edgeModel->GetLabels();
		if (labels) {
			for (int i = 0; i < labels->GetSize(); i++) {
				CProMoLabel* label = dynamic_cast<CProMoLabel*>(labels->GetAt(i));
				if (!label || label->IsLocked(LOCK_FONTSTRIKEOUT))
					continue;

				BOOL currValue = label->IsFontStrikeOut();
				if (!hasValue) {
					strikeOut = currValue;
					hasValue = TRUE;
				}
				else if (strikeOut != currValue) {
					// mixed state, return sentinel
					return FALSE;
				}
			}
		}
	}
	return strikeOut;
}

COLORREF CProMoEdgeView::GetTextColor() const
/* ============================================================
	Function :		CProMoEdgeView::GetTextColor()
	Description :	Returns the color of the text in the labels
	Access :		Public

	Return :		COLORREF	-	The color of the text in
									the label
	Parameters :	none

   ============================================================*/
{
	COLORREF textColor = RGB(0, 0, 0);
	BOOL hasValue = FALSE;

	if (m_edgeModel) {
		CObArray* labels = m_edgeModel->GetLabels();
		if (labels) {
			for (int i = 0; i < labels->GetSize(); i++) {
				CProMoLabel* label = dynamic_cast<CProMoLabel*>(labels->GetAt(i));
				if (!label || label->IsLocked(LOCK_TEXTCOLOR)) {
					continue;
				}
				COLORREF currValue = label->GetTextColor();
				if (!hasValue) {
					textColor = currValue;
					hasValue = TRUE;
				}
				else if (textColor != currValue) {
					return RGB(0, 0, 0);
				}
			}
		}
	}
	return textColor;
}

COLORREF CProMoEdgeView::GetBkColor() const
/* ============================================================
	Function :		CProMoEdgeView::GetBkColor()
	Description :	Returns the background color of the block
	Access :		Public

	Return :		COLORREF	-	The background color of the
									block
	Parameters :	none

   ============================================================*/
{
	return m_bkColor;
}

unsigned int CProMoEdgeView::GetTextHorizontalAlignment() const
/* ============================================================
	Function :		CProMoEdgeView::GetTextHorizontalAlignment()
	Description :	Returns the horizontal alignment of the text
					in the labels
	Access :		Public

	Return :		unsigned int	-	The alignment of the
										text in the labels
	Parameters :	none

   ============================================================*/
{
	unsigned int alignment = 0;
	BOOL hasValue = FALSE;

	if (m_edgeModel) {
		CObArray* labels = m_edgeModel->GetLabels();
		if (labels) {
			for (int i = 0; i < labels->GetSize(); i++) {
				CProMoLabel* label = dynamic_cast<CProMoLabel*>(labels->GetAt(i));
				if (!label || label->IsLocked(LOCK_ALIGNMENT)) {
					continue;
				}
				unsigned int currValue = label->GetTextHorizontalAlignment();
				if (!hasValue) {
					alignment = currValue;
					hasValue = TRUE;
				}
				else if (alignment != currValue) {
					return 0;
				}
			}
		}
	}
	return alignment;
}

unsigned int CProMoEdgeView::GetTextVerticalAlignment() const
/* ============================================================
	Function :		CProMoEdgeView::GetTextVerticalAlignment()
	Description :	Returns the vertical alignment of the text
					in the labels
	Access :		Public

	Return :		unsigned int	-	The alignment of the
										text in the labels
	Parameters :	none

   ============================================================*/
{
	unsigned int alignment = 0;
	BOOL hasValue = FALSE;

	if (m_edgeModel) {
		CObArray* labels = m_edgeModel->GetLabels();
		if (labels) {
			for (int i = 0; i < labels->GetSize(); i++) {
				CProMoLabel* label = dynamic_cast<CProMoLabel*>(labels->GetAt(i));
				if (!label || label->IsLocked(LOCK_ALIGNMENT)) {
					continue;
				}
				unsigned int currValue = label->GetTextVerticalAlignment();
				if (!hasValue) {
					alignment = currValue;
					hasValue = TRUE;
				}
				else if (alignment != currValue) {
					return 0;
				}
			}
		}
	}
	return alignment;
}

BOOL CProMoEdgeView::HasTextAlignmentFlag(unsigned int flag) const
/* ============================================================
	Function :		CProMoEdgeView::HasTextAlignmentFlag()
	Description :	Returns if the labels have the specified
					alignment flag
	Access :		Public

	Return :		BOOL			-	"TRUE" if the labels
										have the specified
										alignment flag
	Parameters :	unsigned int	-	The alignment of the
										text in the labels

   ============================================================*/
{
	BOOL hasFlag = FALSE;
	BOOL hasValue = FALSE;

	if (m_edgeModel) {
		CObArray* labels = m_edgeModel->GetLabels();
		if (labels) {
			for (int i = 0; i < labels->GetSize(); i++) {
				CProMoLabel* label = dynamic_cast<CProMoLabel*>(labels->GetAt(i));
				if (!label || label->IsLocked(LOCK_ALIGNMENT))
					continue;

				BOOL currValue = label->HasTextAlignmentFlag(flag);
				if (!hasValue) {
					hasFlag = currValue;
					hasValue = TRUE;
				}
				else if (hasFlag != currValue) {
					// mixed state, return sentinel
					return FALSE;
				}
			}
		}
	}
	return hasFlag;
}

unsigned int CProMoEdgeView::GetTextAlignment() const
/* ============================================================
	Function :		CProMoEdgeView::GetTextAlignment()
	Description :	Returns the alignment of the text in the
					labels
	Access :		Public

	Return :		unsigned int	-	The alignment of the
										text in the labels
	Parameters :	none

   ============================================================*/
{
	unsigned int alignment = 0;
	BOOL hasValue = FALSE;

	if (m_edgeModel) {
		CObArray* labels = m_edgeModel->GetLabels();
		if (labels) {
			for (int i = 0; i < labels->GetSize(); i++) {
				CProMoLabel* label = dynamic_cast<CProMoLabel*>(labels->GetAt(i));
				if (!label || label->IsLocked(LOCK_ALIGNMENT)) {
					continue;
				}
				unsigned int currValue = label->GetTextAlignment();
				if (!hasValue) {
					alignment = currValue;
					hasValue = TRUE;
				}
				else if (alignment != currValue) {
					return 0;
				}
			}
		}
	}
	return alignment;
}

BOOL CProMoEdgeView::IsVisible() const
/* ============================================================
	Function :		CProMoEdgeView::IsVisible()
	Description :	Returns if the edge is visible
	Access :		Public

	Return :		BOOL		-	"TRUE" if the block is
									visible
	Parameters :	none

   ============================================================*/
{
	return m_visible;
}

unsigned int CProMoEdgeView::GetBkMode() const
/* ============================================================
	Function :		CProMoEdgeView::GetBkMode()
	Description :	Returns the background style of the edge
	Access :		Public

	Return :		unsigned int	-	The background style of
										the edge
	Parameters :	none

   ============================================================*/
{
	return m_bkMode;
}

COLORREF CProMoEdgeView::GetLineColor() const
/* ============================================================
	Function :		CProMoEdgeView::GetLineColor()
	Description :	Returns the line color of the edge
	Access :		Public

	Return :		COLORREF	-	The line color of the
									edge
	Parameters :	none

   ============================================================*/
{
	return m_lineColor;
}

unsigned int CProMoEdgeView::GetLineWidth() const
/* ============================================================
	Function :		CProMoEdgeView::GetLineWidth()
	Description :	Returns the line width of the edge
	Access :		Public

	Return :		unsigned int	-	The line width of the
										edge
	Parameters :	none

   ============================================================*/
{
	return m_lineWidth;
}

unsigned int CProMoEdgeView::GetLineStyle() const
/* ============================================================
	Function :		CProMoEdgeView::GetLineStyle()
	Description :	Returns the line style of the edge
	Access :		Public

	Return :		unsigned int	-	The line style of the
										edge
	Parameters :	none

   ============================================================*/
{
	return m_lineStyle;
}

// Setters
BOOL CProMoEdgeView::SetFontName(const CString& name)
/* ============================================================
	Function :		CProMoEdgeView::SetFontName()
	Description :	Sets the name of the font used to display
					the labels
	Access :		Public

	Return :		BOOL					-	"TRUE" if the
												operation
												succeeded
	Parameters :	CString& name		-	The name of
												the font

   ============================================================*/
{
	BOOL result = TRUE;
	if (IsLocked(LOCK_FONTNAME))
		return FALSE;

	if (m_edgeModel) {
		CObArray* labels = m_edgeModel->GetLabels();
		if (labels) {
			for (int i = 0; i < labels->GetSize(); i++) {
				CProMoLabel* label = dynamic_cast<CProMoLabel*>(labels->GetAt(i));
				if (!label || label->IsLocked(LOCK_FONTNAME)) {
					continue;
				}
				result &= label->SetFontName(name);
			}
		}
	}
	return result;
}

BOOL CProMoEdgeView::SetFontSize(const unsigned int& size)
/* ============================================================
	Function :		CProMoEdgeView::SetFontSize()
	Description :	Sets the size of the font used to display
					the labels
	Access :		Public

	Return :		BOOL					-	"TRUE" if the
												operation
												succeeded
	Parameters :	unsigned int& size		-	The size of
												the font

   ============================================================*/
{
	BOOL result = TRUE;
	if (IsLocked(LOCK_FONTSIZE))
		return FALSE;
	if (size == 0)
		return FALSE;
	if (m_edgeModel) {
		CObArray* labels = m_edgeModel->GetLabels();
		if (labels) {
			for (int i = 0; i < labels->GetSize(); i++) {
				CProMoLabel* label = dynamic_cast<CProMoLabel*>(labels->GetAt(i));
				if (!label || label->IsLocked(LOCK_FONTSIZE)) {
					continue;
				}
				result &= label->SetFontSize(size);
			}
		}
	}
	return result;
}

BOOL CProMoEdgeView::SetFontWeight(const unsigned int& weight)
/* ============================================================
	Function :		CProMoEdgeView::SetFontWeight()
	Description :	Sets the weight of the font used to display
					the labels
	Access :		Public

	Return :		BOOL					-	"TRUE" if the
												operation
												succeeded
	Parameters :	unsigned int& weight		-	The weight of
												the font

   ============================================================*/
{
	BOOL result = TRUE;
	if (IsLocked(LOCK_FONTWEIGHT))
		return FALSE;
	if (weight == 0)
		return FALSE;
	if (m_edgeModel) {
		CObArray* labels = m_edgeModel->GetLabels();
		if (labels) {
			for (int i = 0; i < labels->GetSize(); i++) {
				CProMoLabel* label = dynamic_cast<CProMoLabel*>(labels->GetAt(i));
				if (!label || label->IsLocked(LOCK_FONTWEIGHT)) {
					continue;
				}
				result &= label->SetFontWeight(weight);
			}
		}
	}
	return result;
}

BOOL CProMoEdgeView::SetFontItalic(const BOOL& italic)
/* ============================================================
	Function :		CProMoEdgeView::SetFontItalic()
	Description :	Sets the font used to display the labels as
					italic
	Access :		Public

	Return :		BOOL					-	"TRUE" if the
												operation
												succeeded
	Parameters :	BOOL& italic				-	"TRUE" if the
												font should be
												in italic

   ============================================================*/
{
	BOOL result = TRUE;
	if (IsLocked(LOCK_FONTITALIC))
		return FALSE;
	if (m_edgeModel) {
		CObArray* labels = m_edgeModel->GetLabels();
		if (labels) {
			for (int i = 0; i < labels->GetSize(); i++) {
				CProMoLabel* label = dynamic_cast<CProMoLabel*>(labels->GetAt(i));
				if (!label || label->IsLocked(LOCK_FONTITALIC)) {
					continue;
				}
				result &= label->SetFontItalic(italic);
			}
		}
	}
	return result;
}

BOOL CProMoEdgeView::SetFontUnderline(const BOOL& underline)
/* ============================================================
	Function :		CProMoEdgeView::SetFontUnderline()
	Description :	Sets the font used to display the labels as
					underlined
	Access :		Public

	Return :		BOOL					-	"TRUE" if the
												operation
												succeeded
	Parameters :	BOOL& underline			-	"TRUE" if the
												font should be
												underlined

   ============================================================*/
{
	BOOL result = TRUE;
	if (IsLocked(LOCK_FONTUNDERLINE))
		return FALSE;
	if (m_edgeModel) {
		CObArray* labels = m_edgeModel->GetLabels();
		if (labels) {
			for (int i = 0; i < labels->GetSize(); i++) {
				CProMoLabel* label = dynamic_cast<CProMoLabel*>(labels->GetAt(i));
				if (!label || label->IsLocked(LOCK_FONTUNDERLINE)) {
					continue;
				}
				result &= label->SetFontUnderline(underline);
			}
		}
	}
	return result;
}

BOOL CProMoEdgeView::SetFontStrikeOut(const BOOL& strikeOut)
/* ============================================================
	Function :		CProMoEdgeView::SetFontStrikeOut()
	Description :	Sets the font used to display the labels as
					stroken out
	Access :		Public

	Return :		BOOL					-	"TRUE" if the
												operation
												succeeded
	Parameters :	BOOL& strikeOut			-	"TRUE" if the
												font should be
												stroken out

   ============================================================*/
{
	BOOL result = TRUE;
	if (IsLocked(LOCK_FONTSTRIKEOUT))
		return FALSE;
	if (m_edgeModel) {
		CObArray* labels = m_edgeModel->GetLabels();
		if (labels) {
			for (int i = 0; i < labels->GetSize(); i++) {
				CProMoLabel* label = dynamic_cast<CProMoLabel*>(labels->GetAt(i));
				if (!label || label->IsLocked(LOCK_FONTSTRIKEOUT)) {
					continue;
				}
				result &= label->SetFontStrikeOut(strikeOut);
			}
		}
	}
	return result;
}

BOOL CProMoEdgeView::SetTextColor(const COLORREF& color)
/* ============================================================
	Function :		CProMoEdgeView::SetTextColor()
	Description :	Sets the color of the text in the labels
	Access :		Public

	Return :		BOOL					-	"TRUE" if the
												operation
												succeeded
	Parameters :	COLORREF& color			-	The color of
												the text in
												the label

   ============================================================*/
{
	BOOL result = TRUE;
	if (IsLocked(LOCK_TEXTCOLOR))
		return FALSE;
	if (m_edgeModel) {
		CObArray* labels = m_edgeModel->GetLabels();
		if (labels) {
			for (int i = 0; i < labels->GetSize(); i++) {
				CProMoLabel* label = dynamic_cast<CProMoLabel*>(labels->GetAt(i));
				if (!label || label->IsLocked(LOCK_TEXTCOLOR)) {
					continue;
				}
				result &= label->SetTextColor(color);
			}
		}
	}
	return result;
}

BOOL CProMoEdgeView::SetBkColor(const COLORREF& color)
/* ============================================================
	Function :		CProMoEdgeView::SetBkColor()
	Description :	Sets the background color of the block
	Access :		Public

	Return :		BOOL					-	"TRUE" if the
												operation
												succeeded
	Parameters :	COLORREF& color			-	The background
												color of the
												block

   ============================================================*/
{
	if (IsLocked(LOCK_BKCOLOR))
		return FALSE;
	m_bkColor = color;
	return TRUE;
}

BOOL CProMoEdgeView::SetTextAlignmentFlag(const unsigned int& flag, const BOOL& enabled)
/* ============================================================
	Function :		CProMoEdgeView::SetTextAlignmentFlag()
	Description :	Sets the alignment flag of the text in the labels
	Access :		Public

	Return :		BOOL				-	"TRUE" if the
											operation
											succeeded
	Parameters :	unsigned int& flag	-	The alignment flag
											of the text in
											the labels
					BOOL& enabled		-	"TRUE" to enable

   ============================================================*/
{
	BOOL result = TRUE;
	if (IsLocked(LOCK_ALIGNMENT))
		return FALSE;

	if (m_edgeModel) {
		CObArray* labels = m_edgeModel->GetLabels();
		if (labels) {
			for (int i = 0; i < labels->GetSize(); i++) {
				CProMoLabel* label = dynamic_cast<CProMoLabel*>(labels->GetAt(i));
				if (!label || label->IsLocked(LOCK_ALIGNMENT)) {
					continue;
				}
				result &= label->SetTextAlignmentFlag(flag, enabled);
			}
		}
	}
	return result;
}


BOOL CProMoEdgeView::SetTextHorizontalAlignment(const unsigned int& alignment)
/* ============================================================
	Function :		CProMoEdgeView::SetTextHorizontalAlignment()
	Description :	Sets the horizontal alignment of the text
					in the labels
	Access :		Public

	Return :		BOOL					-	"TRUE" if the
												operation
												succeeded
	Parameters :	unsigned int& alignment	-	The alignment of
												the text in
												the labels

   ============================================================*/
{
	BOOL result = TRUE;
	if (IsLocked(LOCK_ALIGNMENT))
		return FALSE;

	if (m_edgeModel) {
		CObArray* labels = m_edgeModel->GetLabels();
		if (labels) {
			for (int i = 0; i < labels->GetSize(); i++) {
				CProMoLabel* label = dynamic_cast<CProMoLabel*>(labels->GetAt(i));
				if (!label || label->IsLocked(LOCK_ALIGNMENT)) {
					continue;
				}
				result &= label->SetTextHorizontalAlignment(alignment);
			}
		}
	}
	return result;
}

BOOL CProMoEdgeView::SetTextVerticalAlignment(const unsigned int& alignment)
/* ============================================================
	Function :		CProMoEdgeView::SetTextVerticalAlignment()
	Description :	Sets the vertical alignment of the text
					in the labels
	Access :		Public

	Return :		BOOL					-	"TRUE" if the
												operation
												succeeded
	Parameters :	unsigned int& alignment	-	The alignment of
												the text in
												the labels

   ============================================================*/
{
	BOOL result = TRUE;
	if (IsLocked(LOCK_ALIGNMENT))
		return FALSE;

	if (m_edgeModel) {
		CObArray* labels = m_edgeModel->GetLabels();
		if (labels) {
			for (int i = 0; i < labels->GetSize(); i++) {
				CProMoLabel* label = dynamic_cast<CProMoLabel*>(labels->GetAt(i));
				if (!label || label->IsLocked(LOCK_ALIGNMENT)) {
					continue;
				}
				result &= label->SetTextVerticalAlignment(alignment);
			}
		}
	}
	return result;
}

BOOL CProMoEdgeView::SetTextAlignment(const unsigned int& alignment)
/* ============================================================
	Function :		CProMoEdgeView::SetTextAlignment()
	Description :	Sets the alignment of the text in the labels
	Access :		Public

	Return :		BOOL					-	"TRUE" if the
												operation
												succeeded
	Parameters :	unsigned int& alignment	-	The alignment of
												the text in
												the labels

   ============================================================*/
{
	BOOL result = TRUE;
	if (IsLocked(LOCK_ALIGNMENT))
		return FALSE;

	if (m_edgeModel) {
		CObArray* labels = m_edgeModel->GetLabels();
		if (labels) {
			for (int i = 0; i < labels->GetSize(); i++) {
				CProMoLabel* label = dynamic_cast<CProMoLabel*>(labels->GetAt(i));
				if (!label || label->IsLocked(LOCK_ALIGNMENT)) {
					continue;
				}
				result &= label->SetTextAlignment(alignment);
			}
		}
	}
	return result;
}

BOOL CProMoEdgeView::SetVisible(const BOOL& visible)
/* ============================================================
	Function :		CProMoEdgeView::SetVisible()
	Description :	Sets whether the block should be visible
	Access :		Public

	Return :		BOOL					-	"TRUE" if the
												operation
												succeeded
	Parameters :	BOOL& underline			-	"TRUE" if the
												block should be
												visible
	Usage:			The function should be used to hide blocks
					that are not relevant. Note that an
					invisible block can still be selected and
					moved by the user. To prevent that, invoke
					SetLock with PROMO_LOCK_SELECTION

   ============================================================*/
{
	m_visible = visible;
	return TRUE;
}

BOOL CProMoEdgeView::SetBkMode(const unsigned int& mode)
/* ============================================================
	Function :		CProMoEdgeView::SetBkMode()
	Description :	Sets the background style of the edge
	Access :		Public

	Return :		BOOL				-	"TRUE" if the operation
											succeeded
	Parameters :	unsigned int& model	-	The background style of
											the edge

   ============================================================*/
{
	if (IsLocked(LOCK_BKMODE))
		return FALSE;
	m_bkMode = mode;
	return TRUE;
}

BOOL CProMoEdgeView::SetLineColor(const COLORREF& color)
/* ============================================================
	Function :		CProMoEdgeView::SetLineColor()
	Description :	Sets the line color of the edge
	Access :		Public

	Return :		BOOL					-	"TRUE" if the
												operation
												succeeded
	Parameters :	COLORREF& color			-	The line color
												of the edge

   ============================================================*/
{
	if (IsLocked(LOCK_LINECOLOR))
		return FALSE;
	m_lineColor = color;
	return TRUE;
}

BOOL CProMoEdgeView::SetLineWidth(const unsigned int& width)
/* ============================================================
	Function :		CProMoEdgeView::SetLineWidth()
	Description :	Sets the line width of the edge
	Access :		Public

	Return :		BOOL					-	"TRUE" if the
												operation
												succeeded
	Parameters :	unsigned int& width		-	The line width
												of the block

   ============================================================*/
{
	if (IsLocked(LOCK_LINEWIDTH))
		return FALSE;
	m_lineWidth = width;
	return TRUE;
}

BOOL CProMoEdgeView::SetLineStyle(const unsigned int& style)
/* ============================================================
	Function :		CProMoEdgeView::SetLineStyle()
	Description :	Sets the line style of the edge
	Access :		Public

	Return :		BOOL					-	"TRUE" if the
												operation
												succeeded
	Parameters :	unsigned int& style		-	The line style
												of the edge

	Usage:			If the line width is greater than 1, the
					line style is ignored and the line is drawn
					as solid. Otherwise, the line style is used.
					The style should be one of the
					PS_* constants defined in Wingdi.h

   ============================================================*/
{
	if (IsLocked(LOCK_LINESTYLE))
		return FALSE;
	m_lineStyle = style;
	return TRUE;
}
