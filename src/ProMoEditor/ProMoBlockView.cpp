/* ==========================================================================

	Copyright © 2025 Technical University of Denmark

	CProMoBlockView

	Author :		Giovanni Meroni

	Purpose :		"CProMoBlockView" extends "CDiagramEntity" to represent 
					all block/node objects that can be drawn and managed by 
					"CProMoEditor". This class contains visual properties 
					that blocks/nodes have. Structural properties are 
					defined by the associated model class.

	Description :	With respect to "CDiagramEntity", "CProMoBlockView" 
					contains a reference to the "CProMoBlockModel" object 
					representing the model for that block.
					It is also assumed that a block view has exactly 1 model.

	Usage :			Views that represent a node in a graph should be
					derived from this class.

   ========================================================================*/
#include "stdafx.h"
#include <afxtempl.h>
#include "ProMoBlockView.h"
#include "ProMoNameFactory.h"
#include "../DiagramEditor/Tokenizer.h"
#include "ProMoEdgeView.h"
#include "ProMoEdgeModel.h"
#include "../resource.h"
#include "../FileUtils/FileParser.h"
#include "../GeometryUtils/GeometryHelper.h"
#include "../GeometryUtils/IntersectionHelper.h"
#include "ProMoLabel.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

CProMoBlockView::CProMoBlockView()
/* ============================================================
	Function :		CProMoBlockView::CProMoBlockView
	Description :	constructor

	Return :		void
	Parameters :	none

	Usage :

   ============================================================*/
{
	m_blockModel = NULL;
	m_lockProportions = FALSE;
	m_shape = SHAPE_CUSTOM;

	m_lockFlags = 0;

	m_bkColor = CLR_NONE;
	m_bkMode = TRANSPARENT;

	m_lineColor = RGB(0, 0, 0);
	m_lineWidth = 1;
	m_lineStyle = PS_SOLID;

	m_fillColor = RGB(255, 255, 255);
	m_fillPattern = FALSE;
	m_fillStyle = HS_CROSS;

	SetConstraints(CSize(128, 32), CSize(-1, -1));
	m_titleRect = CDoubleRect(0,0,0,0);
	SetType(_T("promo_block_view"));

	SetZoom(1.0);

	CString title;
	SetModel(new CProMoBlockModel());
	m_targetAttachment = DEHT_NONE;
	m_visible = TRUE;

	SetName(CProMoNameFactory::GetID());

	//test: a triangle
	//m_vertices.Add(new CDoublePoint(0.5, 0));
	//m_vertices.Add(new CDoublePoint(1, 1));
	//m_vertices.Add(new CDoublePoint(0, 1));
	//m_perimeter = SHAPE_POLYGON;
}

CProMoBlockView::~CProMoBlockView()
/* ============================================================
	Function :		CProMoBlockView::~CProMoBlockView
	Description :	destructor

	Return :		void
	Parameters :	none

	Usage :

   ============================================================*/
{

	SetModel(NULL);
	ClearVertices();
}

void CProMoBlockView::Draw(CDC* dc, CRect rect)
/* ============================================================
	Function :		CProMoBlockView::Draw
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
		DrawShape(dc, rect);
		Highlight(dc, rect);
	}
}

void CProMoBlockView::DrawShape(CDC* dc, CRect& rect)
/* ============================================================
	Function :		CProMoBlockView::DrawShape
	Description :	Draws the shape of the block.

	Return :		void
	Parameters :	CDC* dc		-	The CDC to draw to.
					CRect rect	-	The real rectangle of the
									object.

   ============================================================*/
{
	
	CSize sz = GetMarkerSize();
	CPoint pt;
	pt.x = round((double)sz.cx * GetZoom());
	pt.y = round((double)sz.cy * GetZoom());

	CPen pen;
	pen.CreatePen(m_lineStyle, m_lineWidth, m_lineColor);
	CPen* pOldPen = dc->SelectObject(&pen);

	CBrush brush;
	if (m_fillPattern) {
		brush.CreateHatchBrush(m_fillStyle, m_fillColor);
	} else {
		brush.CreateSolidBrush(m_fillColor);
	}
	CBrush* pOldBrush = dc->SelectObject(&brush);

	COLORREF pOldBkColor = dc->SetBkColor(m_bkColor);
	int pOldBkMode = dc->SetBkMode(m_bkMode);

	switch (GetShape()) {
	case SHAPE_ELLIPSE:
		dc->Ellipse(rect);
		break;
	case SHAPE_POLYGON:
		if (m_vertices.GetSize() > 2) {
			CArray<POINT, POINT&> scaledPoints;
			scaledPoints.SetSize(m_vertices.GetSize());

			for (int i = 0; i < m_vertices.GetSize(); ++i)
			{
				CDoublePoint* v = (CDoublePoint*)m_vertices[i];
				CDoublePoint scaled = CGeometryHelper::ScaleToRect(*v, rect);

				scaledPoints[i].x = (LONG)scaled.x;
				scaledPoints[i].y = (LONG)scaled.y;
			}

			dc->Polygon(scaledPoints.GetData(), static_cast<int>(scaledPoints.GetSize()));
			break;
		}
	case SHAPE_RECTANGLE:
		dc->Rectangle(rect);
		break;
	default:
		dc->RoundRect(rect, pt);
	}

	dc->SetBkMode(pOldBkMode);
	dc->SetBkColor(pOldBkColor);
	dc->SelectObject(pOldBrush);
	dc->SelectObject(pOldPen);
	
}

int CProMoBlockView::GetHitCode(CPoint point) const
/* ============================================================
	Function :		CProMoBlockView::GetHitCode
	Description :	Returns the hit point constant for "point".
	Access :		Public

	Return :		int				-	The hit point,
										"DEHT_NONE" if none.
	Parameters :	CPoint point	-	The point to check

	Usage :			Call to see in what part of the object point
					lies. The hit point can be one of the following:
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
						"DEHT_TOP" Top-side
						"DEHT_BOTTOM" Bottom-side
						"DEHT_LEFT" :Left-side
						"DEHT_RIGHT" Right-side

   ============================================================*/
{
	return CDiagramEntity::GetHitCode(point);
}

int CProMoBlockView::GetHitCode(const CPoint& point, const CRect& rect) const
/* ============================================================
	Function :		CProMoBlockView::GetHitCode
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
						"DEHT_TOPMIDDLE" Middle top-side
						"DEHT_TOPRIGHT" Top-right corner
						"DEHT_BOTTOMLEFT" Bottom-left corner
						"DEHT_BOTTOMMIDDLE" Middle bottom-side
						"DEHT_BOTTOMRIGHT" Bottom-right corner
						"DEHT_LEFTMIDDLE" Middle left-side
						"DEHT_RIGHTMIDDLE" Middle right-side
						"DEHT_TOP" Top-side
						"DEHT_BOTTOM" Bottom-side
						"DEHT_LEFT" :Left-side
						"DEHT_RIGHT" Right-side

   ============================================================*/
{
	int result = CDiagramEntity::GetHitCode(point, rect);
	// the result is a specific selection marker
	if (result != DEHT_NONE && result != DEHT_BODY)
		return result;

	CRect rectTest;

	rectTest = GetSelectionMarkerRect(DEHT_TOP, rect);
	if (rectTest.PtInRect(point))
		result = DEHT_TOP;

	rectTest = GetSelectionMarkerRect(DEHT_BOTTOM, rect);
	if (rectTest.PtInRect(point))
		result = DEHT_BOTTOM;

	rectTest = GetSelectionMarkerRect(DEHT_LEFT, rect);
	if (rectTest.PtInRect(point))
		result = DEHT_LEFT;

	rectTest = GetSelectionMarkerRect(DEHT_RIGHT, rect);
	if (rectTest.PtInRect(point))
		result = DEHT_RIGHT;

	return result;
}

CRect CProMoBlockView::GetSelectionMarkerRect(UINT marker, CRect rect) const
/* ============================================================
	Function :		CProMoBlockView::GetSelectionMarkerRect
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
						"DEHT_TOP" Top-side
						"DEHT_BOTTOM" Bottom-side
						"DEHT_LEFT" :Left-side
						"DEHT_RIGHT" Right-side

   ============================================================*/
{
	CRect rectMarker;
	int horz = GetMarkerSize().cx / 2;
	int vert = GetMarkerSize().cy / 2;

	switch (marker)
	{
	case DEHT_TOP:
		rectMarker.SetRect(rect.left - horz,
			rect.top - vert,
			rect.right + horz,
			rect.top + vert);
		break;
	case DEHT_BOTTOM:
		rectMarker.SetRect(rect.left - horz,
			rect.bottom - vert,
			rect.right + horz,
			rect.bottom + vert);
		break;
	case DEHT_LEFT:
		rectMarker.SetRect(rect.left - horz,
			rect.top - vert,
			rect.left + horz,
			rect.bottom + vert);
		break;
	case DEHT_RIGHT:
		rectMarker.SetRect(rect.right - horz,
			rect.top - vert,
			rect.right + horz,
			rect.bottom + vert);
		break;
	default:
		rectMarker = CDiagramEntity::GetSelectionMarkerRect(marker, rect);
	}
	return rectMarker;
}


void CProMoBlockView::Highlight(CDC* dc, CRect rect)
/* ============================================================
	Function :		CProMoBlockView::Highlight
	Description :	Highlights the object by making its border
					thicker and red.

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
	if (IsTarget()) {
		CPen p;
		p.CreatePen(PS_SOLID, 3, RGB(255, 0, 0));
		CPen* pOldPen = dc->SelectObject(&p);
		CGdiObject* pOldBrush = dc->SelectStockObject(NULL_BRUSH);

		CRect highlightRect;

		switch (m_targetAttachment) {
			case DEHT_BODY:
				highlightRect = rect;
				break;
			case DEHT_TOP:
				highlightRect = GetSelectionMarkerRect(DEHT_TOP, rect);
				break;
			case DEHT_BOTTOM:
				highlightRect = GetSelectionMarkerRect(DEHT_BOTTOM, rect);
				break;
			case DEHT_LEFT:
				highlightRect = GetSelectionMarkerRect(DEHT_LEFT, rect);
				break;
			case DEHT_RIGHT:
				highlightRect = GetSelectionMarkerRect(DEHT_RIGHT, rect);
				break;
		}
		dc->Rectangle(highlightRect);

		dc->SelectObject(pOldBrush);
		dc->SelectObject(pOldPen);
	}
}

BOOL CProMoBlockView::IsTarget() const
/* ============================================================
	Function :		CProMoBlockView::IsTarget
	Description :	Returns if the block is the target of the
					current drawing operation (e.g., when 
					dragging another object over it)
	Access :		Public

	Return :		BOOL	-	"TRUE" if the block is the 
								target
	Parameters :	none

   ============================================================*/
{
	return (m_targetAttachment!=DEHT_NONE);
}

unsigned int CProMoBlockView::GetTargetAttachment() const
/* ============================================================
	Function :		CProMoBlockView::IsTarget
	Description :	Returns the type of attachment for the
					current drawing operation (e.g., when 
					dragging another object over it)
	Access :		Public

	Return :		unsigned int	-	The type of attachment
										for the dragged block
	Parameters :	none

   ============================================================*/
{
	return m_targetAttachment;
}

void CProMoBlockView::SetTarget(unsigned int attachment)
/* ============================================================
	Function :		CProMoBlockView::SetTarget
	Description :	Makes the current block a target for the
					current drawing operation (e.g., when 
					dragging another object over it)
	Access :		Public

	Return :		void
	Parameters :	unsigned int attachment	-	The type of
												attachment for
												the dragged block

   ============================================================*/
{
	m_targetAttachment = attachment;
}

void CProMoBlockView::SetLockedProportions(BOOL hasLockedProportions)
/* ============================================================
	Function :		CProMoBlockView::SetLockedProportions
	Description :	Sets the proportions of the block as locked
	Access :		Public

	Return :		void
	Parameters :	BOOL hasLockedProportions	-	"TRUE" if the
													proportions
													should be
													locked

   ============================================================*/
{
	m_lockProportions = hasLockedProportions;
}

BOOL CProMoBlockView::HasLockedProportions() const
/* ============================================================
	Function :		CProMoBlockView::HasLockedProportions
	Description :	Returns if the proportions of the block are
					locked
	Access :		Public

	Return :		BOOL	-	"TRUE" if the proportions are
								locked
	Parameters :	none

   ============================================================*/
{
	return m_lockProportions;
}

void CProMoBlockView::ShowPopup(CPoint point, CWnd* parent)
/* ============================================================
	Function :		CProMoBlockView::ShowPopup
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

CPoint CProMoBlockView::GetIntersection(CPoint innerPoint, CPoint outerPoint)
/* ============================================================
	Function :		CProMoBlockView::GetIntersection
	Description :	Determines the point on the border of the 
					block that intersects with a (virtual) 
					line. Can be used to know where to trim a 
					connected edge.
					Override this method if a custom shape is
					being drawn, in order to compute the 
					point accordingly.
	Access :		Public

	Return :		CPoint				-	"CPoint" that lies
											on the border of
											the block
	Parameters :	CPoint innerPoint	-	"CPoint" that lies 
											inside the (shape
											of) the block
					CPoint outerPoint	-	"CPoint" that lies 
											outside the (shape 
											of) the block

   ============================================================*/
{
	CDoublePoint result;
	if (GetShape() == SHAPE_ELLIPSE) {
		result = CIntersectionHelper::SegmentIntersectsEllipse(innerPoint, outerPoint, GetRect());
	} else if (GetShape() == SHAPE_POLYGON) {
		result = CIntersectionHelper::SegmentIntersectsPolygon(innerPoint, outerPoint, GetRect(), m_vertices);
	} else {
		result = CIntersectionHelper::SegmentIntersectsRect(innerPoint, outerPoint, GetRect());
	}
		
	return result.ToCPoint();
}

void CProMoBlockView::SetLeft(double left)
/* ============================================================
	Function :		CProMoBlockView::SetLeft
	Description :	Sets the left edge of the object rectangle
	Access :		Public

	Return :		void
	Parameters :	double left	-	New left position

	Usage :			Call to set the left edge of the object.
					The object coordinates are expressed as
					double values to allow unlimited zoom.
					Overridden to reposition child blocks and 
					connected edges.

   ============================================================*/
{

	KeepElementsConnected(left, GetTop(), GetRight(), GetBottom()); 
	CDiagramEntity::SetLeft(left);
	Reposition();

}

void CProMoBlockView::SetRight(double right)
/* ============================================================
	Function :		CProMoBlockView::SetRight
	Description :	Sets the right edge of the object
					rectangle
	Access :		Public

	Return :		void
	Parameters :	double right	-	New right position

	Usage :			Call to set the right edge of the object.
					The object coordinates are expressed as
					double values to allow unlimited zoom.
					Overridden to reposition child blocks and 
					connected edges.

   ============================================================*/
{

	KeepElementsConnected(GetLeft(), GetTop(), right, GetBottom());
	CDiagramEntity::SetRight(right);
	Reposition();
}

void CProMoBlockView::SetTop(double top)
/* ============================================================
	Function :		CProMoBlockView::SetTop
	Description :	Sets the top edge of the object rectangle
	Access :		Public

	Return :		void
	Parameters :	double top	-	New top position

	Usage :			Call to set the top edge of the object.
					The object coordinates are expressed as
					double values to allow unlimited zoom.
					Overridden to reposition child blocks and 
					connected edges.

   ============================================================*/
{
	KeepElementsConnected(GetLeft(), top, GetRight(), GetBottom());
	CDiagramEntity::SetTop(top);
	Reposition();

}

void CProMoBlockView::SetBottom(double bottom)
/* ============================================================
	Function :		CProMoBlockView::SetBottom
	Description :	Sets the bottom edge of the object
					rectangle
	Access :		Public

	Return :		void
	Parameters :	double bottom	-	New bottom position

	Usage :			Call to set the bottom edge of the object.
					The object coordinates are expressed as
					double values to allow unlimited zoom.
					Overridden to reposition child blocks and 
					connected edges.

   ============================================================*/
{

	KeepElementsConnected(GetLeft(), GetTop(), GetRight(), bottom);
	CDiagramEntity::SetBottom(bottom);
	Reposition();
}

void CProMoBlockView::SetTitle(CString title)
/* ============================================================
	Function :		CProMoBlockView::SetTitle
	Description :	Sets the Title property
	Access :		Public

	Return :		void
	Parameters :	CString title	-	The new title

	Usage :			Call to set the title of the object.
					Overridden to resize the block to fit the 
					title if fitTitle is "TRUE"

   ============================================================*/
{
	CDiagramEntity::SetTitle(title);

	CDiagramEntity::SetRect(GetRect());

}


void CProMoBlockView::KeepElementsConnected(double left, double top, double right, double bottom)
/* ============================================================
	Function :		CProMoBlockView::KeepElementsConnected
	Description :	Repositions child blocks and 
					connected edges.
	Access :		Protected

	Return :		void
	Parameters :	double left		-	Left edge
					double top		-	Top edge
					double right	-	Right edge
					double bottom	-	Bottom edge

	Usage :			Call *before* the object is moved or
					resized to to reposition child blocks and 
					connected edges.

   ============================================================*/
{
	if (m_blockModel) {

		//note: reposition links
		int i = 0;
		CObArray edges;
		m_blockModel->GetIncomingEdges(edges);

		for (i = 0; i < edges.GetSize(); i++) {
			CProMoEdgeModel* edgeModel = dynamic_cast<CProMoEdgeModel*>(edges.GetAt(i));
			if (edgeModel) {
				CProMoEdgeView* edgeView = edgeModel->GetLastSegment();

				//destination: bottomright
				if (!edgeView->IsSelected()) {
					CPoint newPoint = MapPointToNewRect(edgeView->GetRect().BottomRight(), left, top, right, bottom);

					edgeView->SetBottom(newPoint.y);
					edgeView->SetRight(newPoint.x);

				}
			}

		}

		edges.RemoveAll();
		m_blockModel->GetOutgoingEdges(edges);

		for (i = 0; i < edges.GetSize(); i++) {
			CProMoEdgeModel* edgeModel = dynamic_cast<CProMoEdgeModel*>(edges.GetAt(i));
			if (edgeModel) {
				CProMoEdgeView* edgeView = edgeModel->GetFirstSegment();
				//destination: topleft
				if (!edgeView->IsSelected()) {
					CPoint newPoint = MapPointToNewRect(edgeView->GetRect().TopLeft(), left, top, right, bottom);

					edgeView->SetTop(newPoint.y);
					edgeView->SetLeft(newPoint.x);
				}
			}

		}

		double deltaY = GetTop() - top;
		double deltaX = GetLeft() - left;

		// SubBlocks

		if (deltaX != 0 || deltaY != 0) {
			CObArray childBlocks;
			m_blockModel->GetSubBlocks(childBlocks);

			for (i = 0; i < childBlocks.GetSize(); i++) {
				CProMoBlockModel* childModel = dynamic_cast<CProMoBlockModel*>(childBlocks.GetAt(i));
				if (childModel) {
					CProMoBlockView* childView = childModel->GetMainView();
					if (childView) {
						//move child nodes that are not selected (otherwise they will be moved twice)
						if (!childView->IsSelected()) {
							childView->SetRect(childView->GetLeft() - deltaX, childView->GetTop() - deltaY, childView->GetRight() - deltaX, childView->GetBottom() - deltaY);
						}
					}
				}
			}


			//TODO: generalize to all possible boundary positions
			CObArray boundaryBlocks;
			m_blockModel->GetBoundaryBlocks(boundaryBlocks, DEHT_BODY);

			for (i = 0; i < boundaryBlocks.GetSize(); i++) {
				CProMoBlockModel* childModel = dynamic_cast<CProMoBlockModel*>(boundaryBlocks.GetAt(i));
				if (childModel) {
					CProMoBlockView* childView = childModel->GetMainView();
					if (childView) {
						//move child nodes that are not selected (otherwise they will be moved twice)
						if (!childView->IsSelected()) {
							childView->SetRect(childView->GetLeft() - deltaX, childView->GetTop() - deltaY, childView->GetRight() - deltaX, childView->GetBottom() - deltaY);
						}
					}
				}
			}

		}

	}

}

CPoint CProMoBlockView::MapPointToNewRect(CPoint oldPoint, double left, double top, double right, double bottom)
/* ============================================================
	Function :		CProMoBlockView::MapPointToNewRect
	Description :	Determines where a point on the border of
					the block should be moved when the block
					is moved/resized.
					Override this method if the shape being
					drawn is changed, in order to compute the
					point accordingly.
	Access :		Protected

	Return :		CPoint				-	"CPoint" that will
											lie on the border 
											when the block is
											moved/resized
	Parameters :	CPoint oldPoint		-	"CPoint" that lies
											on the border of
											the block
					double left			-	New left edge
					double top			-	New top edge
					double right		-	New right edge
					double bottom		-	New bottom edge

	Usage :			Call when the block is resized or moved, to
					adjust connected edges accordingly.

   ============================================================*/
{
	double width = GetRight() - GetLeft();
	double height = GetBottom() - GetTop();

	if (width == 0 || height == 0) return CPoint(-1, -1); // avoid divide by zero

	double xRel = (oldPoint.x - GetLeft()) / width;
	double yRel = (oldPoint.y - GetTop()) / height;

	// Clamp to [0, 1] to avoid floating point overshoots
	xRel = max(0.0, min(1.0, xRel));
	yRel = max(0.0, min(1.0, yRel));

	int newX = static_cast<int>(round(left + xRel * (right - left)));
	int newY = static_cast<int>(round(top + yRel * (bottom - top)));

	return CPoint(newX, newY);
}

void CProMoBlockView::RecomputeIntersectionLinks()
	/* ============================================================
		Function :		CProMoBlockView::RecomputeIntersectionLinks
		Description :	Recomputes the position of the edges
						connected to this block, such that they are
						attached to the border of the block.
		Access :		Protected

		Return :		void
		Parameters :	none

	   ============================================================*/
{
	if (m_blockModel) {
		//recompute intersection for edges
		int i = 0;
		
		CObArray edges;
		m_blockModel->GetIncomingEdges(edges);

		for (i = 0; i < edges.GetSize(); i++) {
			CProMoEdgeModel* edgeModel = dynamic_cast<CProMoEdgeModel*>(edges.GetAt(i));
			if (edgeModel) {
				CProMoEdgeView* edgeView = edgeModel->GetLastSegment();
				//destination: bottomright
				CPoint pt = GetIntersection(edgeView->GetRect().BottomRight(), edgeView->GetRect().TopLeft());
				if (pt.x >= 0) {
					edgeView->SetBottom(pt.y);
					edgeView->SetRight(pt.x);
				}
			}

		}

		edges.RemoveAll();
		m_blockModel->GetOutgoingEdges(edges);

		for (i = 0; i < edges.GetSize(); i++) {
			CProMoEdgeModel* edgeModel = dynamic_cast<CProMoEdgeModel*>(edges.GetAt(i));
			if (edgeModel) {
				CProMoEdgeView* edgeView = edgeModel->GetFirstSegment();
				//destination: topleft
				CPoint pt = GetIntersection(edgeView->GetRect().TopLeft(), edgeView->GetRect().BottomRight());
				if (pt.x >= 0) {
					edgeView->SetTop(pt.y);
					edgeView->SetLeft(pt.x);
				}
			}
		}

		//recompute intersection for sub-blocks
		CObArray childBlocks;
		m_blockModel->GetSubBlocks(childBlocks);
		
		for (i = 0; i < childBlocks.GetSize(); i++) {
			CProMoBlockModel* childModel = dynamic_cast<CProMoBlockModel*>(childBlocks.GetAt(i));
			if (childModel) {
				CProMoBlockView* childView = childModel->GetMainView();
				if (childView) {
					childView->RecomputeIntersectionLinks();
				}
			}
		}
	}
}

CProMoBlockModel* CProMoBlockView::GetBlockModel() const
/* ============================================================
	Function :		CProMoBlockView::GetBlockModel
	Description :	Returns a pointer to the model of this
					block
	Access :		Public

	Return :		CProMoBlockModel*	-	A pointer to the
											model
	Parameters :	none

   ============================================================*/
{
	return m_blockModel;
}

void CProMoBlockView::LinkSubBlock(CProMoBlockView* block)
/* ============================================================
	Function :		CProMoBlockView::LinkSubBlock
	Description :	Makes the block being passed as input
					parameter a subblock of this block. A 
					subblock is a block that is contained by
					this block.
	Access :		Public

	Return :		void
	Parameters :	CProMoBlockModel* block	-	the block that
												should be
												a subblock

   ============================================================*/
{
	if (m_blockModel) {
		m_blockModel->LinkChildBlock(block->m_blockModel, DEHT_BODY);
	}
}

void CProMoBlockView::UnlinkSubBlock(CProMoBlockView* block)
/* ============================================================
	Function :		CProMoBlockModel::UnlinkSubBlock
	Description :	Removes the block being passed as input
					parameter from the subblocks of this block
	Access :		Public

	Return :		void
	Parameters :	CProMoBlockModel* block	-	the block that
												should be
												removed

   ============================================================*/
{
	if (m_blockModel) {
		m_blockModel->UnlinkChildBlock(block->m_blockModel);
	}
}

void CProMoBlockView::UnlinkFromParent()
/* ============================================================
	Function :		CProMoBlockView::UnlinkFromParent

	Description :	Makes this block no longer linked to another
					block, neither as subblock nor as boundary
					block.
	Access :		Public

	Return :		void
	Parameters :	none

   ============================================================*/
{
	if (m_blockModel) {
		if (m_blockModel) {
			m_blockModel->SetParentBlock(NULL, DEHT_NONE);
		}
	}
}

void CProMoBlockView::UnlinkAllSubBlocks()
/* ============================================================
	Function :		CProMoBlockView::UnlinkAllSubBlocks
	Description :	Removes all the subblocks of this block
	Access :		Public

	Return :		void
	Parameters :	none

   ============================================================*/
{
	if (m_blockModel) {
		CObArray subblocks;
		m_blockModel->GetSubBlocks(subblocks);
		for (int i = 0; i < subblocks.GetSize(); i++) {
			m_blockModel->UnlinkChildBlock(dynamic_cast<CProMoBlockModel*>(subblocks.GetAt(i)));
		}
	}
}

void CProMoBlockView::LinkBoundaryBlock(CProMoBlockView* block, unsigned int attachment)
/* ============================================================
	Function :		CProMoBlockView::LinkBoundaryBlock
	Description :	Makes the block being passed as input
					parameter a boundary block of this block. A
					boundary block is a block that lies on the
					boundary of this block.
	Access :		Public

	Return :		void
	Parameters :	CProMoBlockModel* block	-	the block that
												should be
												a boundary block

   ============================================================*/
{
	if (m_blockModel && block) {
		m_blockModel->LinkChildBlock(block->GetBlockModel(), attachment);
		Reposition();
	}
}

void CProMoBlockView::UnlinkBoundaryBlock(CProMoBlockView* block)
/* ============================================================
	Function :		CProMoBlockModel::UnlinkBoundaryBlock
	Description :	Removes the block being passed as input
					parameter from the boundary blocks of this
					block
	Access :		Public

	Return :		void
	Parameters :	CProMoBlockModel* block	-	the block that
												should be
												removed

   ============================================================*/
{
	if (m_blockModel) {
		m_blockModel->UnlinkChildBlock(block->GetBlockModel());
	}
}

void CProMoBlockView::UnlinkAllBoundaryBlocks()
/* ============================================================
	Function :		CProMoBlockView::UnlinkAllSubBlocks
	Description :	Removes all the boundary blocks of this block
	Access :		Public

	Return :		void
	Parameters :	none

   ============================================================*/
{
	if (m_blockModel) {
		CObArray blocks;
		m_blockModel->GetBoundaryBlocks(blocks, DEHT_BODY);
		for (int i = 0; i < blocks.GetSize(); i++) {
			m_blockModel->UnlinkChildBlock(dynamic_cast<CProMoBlockModel*>(blocks.GetAt(i)));
		}
	}
}

CProMoModel* CProMoBlockView::GetModel() const
/* ============================================================
	Function :		CProMoBlockView::GetModel
	Description :	Returns a pointer to the model of this 
					block
	Access :		Public

	Return :		CProMoModel*	-	A pointer to the 
										model
	Parameters :	none

   ============================================================*/
{
	return m_blockModel;
}

void CProMoBlockView::SetModel(CProMoModel* model)
/* ============================================================
	Function :		CProMoBlockView::SetModel
	Description :	Makes the object being passed as input
					parameter the model for this block
	Access :		Protected

	Return :		void
	Parameters :	CProMoModel* block	-	the object that
											should be the
											model

   ============================================================*/
{
	CProMoBlockModel* blockModel = dynamic_cast<CProMoBlockModel*>(model);
	if (m_blockModel != blockModel) {
		CProMoBlockModel* oldModel = m_blockModel;
		m_blockModel = blockModel;

		//link this class to the new model
		if (blockModel) {
			blockModel->LinkView(this);
		}
		//unlink this class from the old model
		if (oldModel) {
			oldModel->UnlinkView(this);
			//if the old model has no views, delete it
			CObArray views;
			oldModel->GetViews(views);
			if (views.GetSize() == 0) {
				delete oldModel;
			}
		}
	}
}

void CProMoBlockView::SetShape(const int& type)
/* ============================================================
	Function :		CProMoBlockView::SetShape
	Description :	Sets the shape of the block

	Return :		void
	Parameters :	int& type	-	the shape of the block
									
	Usage :			Virtual. Can be overridden in a derived
					class to support additional shapes. 
					"type" can be one of the following:
						"PERIMETER_RECTANGLE" A rectangle
						"PERIMETER_ELLIPSE" An ellipse
						"PERIMETER_POLYGON" A n-sided
							polygon
					The shape will always be inscribed by the 
					CRect object obtained by invoking GetRect()
						
   ============================================================*/
{
	m_shape = type;
}

int CProMoBlockView::GetShape() const
/* ============================================================
	Function :		CProMoBlockView::GetShape
	Description :	Returns the shape of the block

	Return :		int& type	-	the shape of the block
	Parameters :	none

	Usage :			Virtual. Can be overridden in a derived
					class to support additional shapes.
					"type" can be one of the following:
						"PERIMETER_RECTANGLE" A rectangle
						"PERIMETER_ELLIPSE" An ellipse
						"PERIMETER_POLYGON" A n-sided
							polygon
					The shape will always be inscribed by the
					CRect object obtained by invoking GetRect()

   ============================================================*/
{
	return m_shape;
}

BOOL CProMoBlockView::AddVertex(const CDoublePoint& point)
/* ============================================================
	Function :		CProMoBlockView::AddVertex
	Description :	Adds a new vertex to the polygon 
					representing the shape of the block.
					The operation succeeds only if the shape of
					the block is SHAPE_POLYGON.
	Access :		Protected

	Return :		BOOL				-	"TRUE" if the vertex
											was added.
	Parameters :	CDoublePoint& point	-	Vertex to be added

   ============================================================*/
{
	if (0 <= point.x && point.x <= 1 && 0 <= point.y && point.y <= 1 && m_shape == SHAPE_POLYGON) {
		CDoublePoint* vertex = new CDoublePoint(point);
		m_vertices.Add(vertex);
		return TRUE;
	}
	return FALSE;
}

void CProMoBlockView::GetVertices(CObArray& vertices) const
/* ============================================================
	Function :		CProMoBlockView::GetVertices
	Description :	Returns the vertices of the polygon
					representing the shape of the block.
	Access :		Protected

	Return :		void
	Parameters :	CObArray			-	Array containing
											pointers to the
											vertices.

   ============================================================*/
{
	if (m_shape == SHAPE_POLYGON) {
		vertices.Append(m_vertices);
	}
}

void CProMoBlockView::ClearVertices()
/* ============================================================
	Function :		CProMoBlockView::ClearVertices
	Description :	Removes all the vertices of the polygon
					representing the shape of the block.
	Access :		Protected

	Return :		none
	Parameters :	none

   ============================================================*/
{
	for (INT_PTR i = m_vertices.GetSize() - 1; i >= 0; i--) {
		delete m_vertices.GetAt(i);
	}
	m_vertices.RemoveAll();
}

void CProMoBlockView::AutoResize()
/* ============================================================
	Function :		CProMoBlockView::AutoResize
	Description :	Automatically resizes block to prevent
					child blocks from protruding.
	Access :		Public

	Return :		void
	Parameters :	none

   ============================================================*/
{
	if (m_blockModel) {
		CObArray childBlocks;
		m_blockModel->GetSubBlocks(childBlocks);

		for (int i = 0; i < childBlocks.GetSize(); i++) {
			CProMoBlockModel* childModel = dynamic_cast<CProMoBlockModel*>(childBlocks.GetAt(i));
			if (childModel) {
				CProMoBlockView* childView = childModel->GetMainView();
				if (childView) {
					BOOL isSelected = childView->IsSelected();
					childView->Select(TRUE);
					if (childView->GetBottom() > this->GetBottom()) {
						this->SetRect(GetLeft(), GetTop(), GetRight(), childView->GetBottom() + 5);
					}
					if (childView->GetRight() > this->GetRight()) {
						this->SetRect(GetLeft(), GetTop(), childView->GetRight() + 5, GetBottom());
					}
					if (childView->GetTop() < this->GetTop()) {
						this->SetRect(GetLeft(), childView->GetTop() - 5, GetRight(), GetBottom());
					}
					if (childView->GetLeft() < this->GetLeft()) {
						this->SetRect(childView->GetLeft() - 5, GetTop(), GetRight(), GetBottom());
					}
					childView->Select(isSelected);
				}
			}
		}

		if (m_blockModel->GetParentBlock() != NULL) {
			if (m_blockModel->GetParentBlock()->GetMainView() != NULL) {
				m_blockModel->GetParentBlock()->GetMainView()->AutoResize();
			}
		}
		else {
			this->RecomputeIntersectionLinks();
		}
	}
}

CString CProMoBlockView::GetDefaultGetString() const
{
	/* ============================================================
	Function :		CProMoBlockView::GetDefaultString
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
	
	str.Format(_T("%s:%s,%f,%f,%f,%f,%s,%i,%s,%i,%i,%i,%i,%i,%i,%i,%i,%i"), 
		(LPCTSTR)GetType(), (LPCTSTR)name, GetLeft(), GetTop(), GetRight(), GetBottom(), (LPCTSTR)title, GetGroup(), (LPCTSTR)model, m_lockFlags,
		m_bkColor, m_bkMode, m_lineColor, m_lineWidth, m_lineStyle, m_fillColor, m_fillPattern, m_fillStyle);
	
	return str;

}

CString CProMoBlockView::GetHeaderFromString(CString& str)
/* ============================================================
	Function :		CProMoBlockView::GetHeaderFromString
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


BOOL CProMoBlockView::GetDefaultFromString(CString& str)
/* ============================================================
	Function :		CProMoBlockView::GetDefaultFromString
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
		if (size >= 8)
		{
			CString name;
			double left;
			double top;
			double right;
			double bottom;
			CString title;
			int group;
			CString model;

			int count = 0;

			tok->GetAt(count++, name);
			tok->GetAt(count++, left);
			tok->GetAt(count++, top);
			tok->GetAt(count++, right);
			tok->GetAt(count++, bottom);
			tok->GetAt(count++, title);
			tok->GetAt(count++, group);
			tok->GetAt(count++, model);

			SetRect(left, top, right, bottom);

			CFileParser::DecodeString(title);
			CFileParser::DecodeString(name);

			SetTitle(title);
			SetName(name);
			SetGroup(group);

			// missing style attributes should not prevent the block from loading
			if (size >= 17) {
				int lockFlags;
				COLORREF bkColor;
				int bkMode;
				COLORREF lineColor;
				int lineWidth;
				int lineStyle;
				COLORREF fillColor;
				BOOL fillPattern;
				int fillStyle;

				tok->GetAt(count++, lockFlags);
				tok->GetAt(count++, bkColor);
				tok->GetAt(count++, bkMode);
				tok->GetAt(count++, lineColor);
				tok->GetAt(count++, lineWidth);
				tok->GetAt(count++, lineStyle);
				tok->GetAt(count++, fillColor);
				tok->GetAt(count++, fillPattern);
				tok->GetAt(count++, fillStyle);

				m_bkColor = bkColor;
				m_bkMode = bkMode;
				m_lineColor = lineColor;
				m_lineWidth = lineWidth;
				m_lineStyle = lineStyle;
				m_fillColor = fillColor;
				m_fillPattern = fillPattern;
				m_fillStyle = fillStyle;
				m_lockFlags = lockFlags;
			}

			result = TRUE;
		}
		delete tok;
	}

	return result;

}

CDiagramEntity* CProMoBlockView::Clone()
/* ============================================================
	Function :		CProMoBlockView::Clone
	Description :	Clone this object to a new object.

	Return :		CDiagramEntity*	-	The new object.
	Parameters :	none

	Usage :			Call to create a clone of the object. The
					caller will have to delete the object.

   ============================================================*/
{

	//Hierarchy is not copied: if multiple blocks are selected, they become root nodes
	CProMoBlockView* obj = new CProMoBlockView;
	obj->Copy(this);
	obj->SetName(CProMoNameFactory::GetID());
	return obj;

}

void CProMoBlockView::Copy(CDiagramEntity* obj)
/* ============================================================
	Function :		CProMoBlockView::Copy
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
	CProMoBlockView* objView = dynamic_cast<CProMoBlockView*>(obj);
	if (objView) {
		m_bkColor = objView->m_bkColor;
		m_bkMode = objView->m_bkMode;
		m_lineColor = objView->m_lineColor;
		m_lineWidth = objView->m_lineWidth;
		m_lineStyle = objView->m_lineStyle;
		m_fillColor = objView->m_fillColor;
		m_fillStyle = objView->m_fillStyle;
		m_fillPattern = objView->m_fillPattern;

		if (GetModel()) {
			GetModel()->Copy(objView->GetModel());
		}
		SetLockedProportions(objView->HasLockedProportions());
	}
}

void CProMoBlockView::SetRect(CRect rect)
/* ============================================================
	Function :		CProMoBlockView::SetRect
	Description :	Sets the object rectangle, normalized.
	Access :		Public

	Return :		void
	Parameters :	CRect rect	-	The rectangle to set.

	Usage :			Call to place the object.
					Overridden to avoid name hiding for SetRect
					overloaded methods in derived classes.
					DO NOT DELETE.

   ============================================================*/
{
	
	CDiagramEntity::SetRect(rect);
}

void CProMoBlockView::SetRect(double left, double top, double right, double bottom)
/* ============================================================
	Function :		CProMoBlockView::SetRect
	Description :	Sets the object rectangle.
	Access :		Public

	Return :		void
	Parameters :	double left		-	Left edge
					double top		-	Top edge
					double right	-	Right edge
					double bottom	-	Bottom edge

	Usage :			Call to place the object.
					Overridden to resize the block to fit the 
					title if fitTitle is "TRUE"

   ============================================================*/
{
	
	if (!m_titleRect.IsRectNull()) {

		if (m_titleRect.Width() > right - left) {
			if (GetLeft() - left != 0) {
				left = (right - m_titleRect.Width());
			}
			else {
				right = (left + m_titleRect.Width());
			}
		}

		if (m_titleRect.Height() > bottom - top) {
			if (GetTop() - top != 0) {
				top = (bottom - m_titleRect.Height());
			}
			else {
				bottom = (top + m_titleRect.Height());
			}
		}
	}

	CDiagramEntity::SetRect(left, top, right, bottom);

}

CDiagramEntity* CProMoBlockView::CreateFromString(const CString& str)
/* ============================================================
	Function :		CProMoBlockView::CreateFromString
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

	CProMoBlockView* obj = new CProMoBlockView;
	if (!obj->FromString(str))
	{
		delete obj;
		obj = NULL;
	}

	return obj;

}

CDiagramEntity* CProMoBlockView::CreateFromString(const CString& str, CProMoModel* model)
/* ============================================================
	Function :		CProMoBlockView::CreateFromString
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

	CProMoBlockView* obj = new CProMoBlockView;
	if (!obj->FromString(str))
	{
		delete obj;
		obj = NULL;
	}
	else {
		CProMoBlockModel* blockModel = dynamic_cast<CProMoBlockModel*>(model);

		if (blockModel) {
			obj->SetModel(blockModel);
		}
	}

	return obj;

}

CString CProMoBlockView::GetModelFromString(const CString& str)
/* ============================================================
	Function :		CProMoBlockView::GetModelFromString
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

CString CProMoBlockView::GetNameFromString(const CString& str)
/* ============================================================
	Function :		CProMoBlockView::GetNameFromString
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

void CProMoBlockView::LinkLabel(CProMoLabel* label)
/* ============================================================
	Function :		CProMoBlockView::LinkView
	Description :	Links a new label to this object.
	Access :		Protected

	Return :		void
	Parameters :	CProMoLabel* label - the label to link

   ============================================================*/
{
	if (label && m_blockModel) {
		m_blockModel->LinkLabel(label);
	}
}

void CProMoBlockView::OnLabelChanged(CProMoLabel* label)
/* ============================================================
	Function :		CProMoBlockView::OnLabelChanged
	Description :	Notification that a label has changed.
	Access :		Public

	Return :		void
	Parameters :	CProMoLabel* label	-	Label that changed.

	Usage :			Can be called by a label to notify the
					view that it changed, and to trigger UI
					updates.

   ============================================================*/
{
	if (label) {
		AdjustToLabel(label);
	}
}

BOOL CProMoBlockView::IsFitCompatible(UINT shapeAnchor, UINT labelAnchor) const
/* ============================================================
	Function :		CProMoBlockView::IsFitCompatible
	Description :	Checks if the anchoring point of the view
					and label allow the label to fit the block
	Access :		Protected

	Return :		BOOL				-	"TRUE" if the view
											can fit the label
	Parameters :	UINT shapeAnchor	-	The anchoring point
											of the view.
					UINT labelAnchor	-	The anchoring point
											of the label.

   ============================================================*/
{
	return (shapeAnchor == labelAnchor) ||
		(shapeAnchor == DEHT_CENTER && labelAnchor == DEHT_CENTER);
}

void CProMoBlockView::AdjustToLabel(CProMoLabel* label)
/* ============================================================
	Function :		CProMoBlockView::AdjustToLabel
	Description :	Recomputes the bounding rect such that
					labels fit the view rectangle (if applicable), 
					and the	view cannot be shrunk.
	Access :		Protected

	Return :		void
	Parameters :	CProMoLabel* label	-	Label that changed.

   ============================================================*/
{
	CDoubleRect rect(GetLeft(), GetTop(), GetRight(), GetBottom());

	//TODO: also exclude labels whose offset is not 0
	
	if (label && label->HasFitView() && IsFitCompatible(label->GetViewAnchorPoint(), label->GetLabelAnchorPoint())) {

		CDoubleRect labelRect;

		CObArray labels;
		GetModel()->GetLabels(labels);

		for (int i = 0; i < labels.GetSize(); i++) {
			CProMoLabel* otherLabel = (CProMoLabel*)labels.GetAt(i);
			if (!otherLabel || !otherLabel->HasFitView() || !IsFitCompatible(otherLabel->GetViewAnchorPoint(), otherLabel->GetLabelAnchorPoint()))
				continue;
			labelRect.UnionRect(labelRect, otherLabel->GetRect());
		}

		// Get current rect
		double curW = rect.Width();
		double curH = rect.Height();
		double reqW = labelRect.Width();
		double reqH = labelRect.Height();

		const double EPS = 1e-6;

		// If proportions are locked, scale uniformly to satisfy both dims
		if (m_lockProportions && curW > EPS && curH > EPS) {
			double scaleW = reqW / curW;
			double scaleH = reqH / curH;
			double scale = max(scaleW, scaleH);
			reqW = curW * scale;
			reqH = curH * scale;
		}
		
		// Adjust based on anchor combination
		CDoubleRect newRect = rect; // copy

		double dw = reqW - curW;
		double dh = reqH - curH;

		switch (label->GetViewAnchorPoint())
		{
		case DEHT_TOPLEFT:
			newRect.right = newRect.left + reqW;
			newRect.bottom = newRect.top + reqH;
			break;

		case DEHT_TOPMIDDLE:
			newRect.left -= dw / 2.0;
			newRect.right += dw / 2.0;
			newRect.bottom = newRect.top + reqH;
			break;

		case DEHT_TOPRIGHT:
			newRect.left = newRect.right - reqW;
			newRect.bottom = newRect.top + reqH;
			break;

		case DEHT_BOTTOMLEFT:
			newRect.right = newRect.left + reqW;
			newRect.top = newRect.bottom - reqH;
			break;

		case DEHT_BOTTOMMIDDLE:
			newRect.left -= dw / 2.0;
			newRect.right += dw / 2.0;
			newRect.top = newRect.bottom - reqH;
			break;

		case DEHT_BOTTOMRIGHT:
			newRect.left = newRect.right - reqW;
			newRect.top = newRect.bottom - reqH;
			break;

		case DEHT_LEFTMIDDLE:
			newRect.right = newRect.left + reqW;
			newRect.top -= dh / 2.0;
			newRect.bottom += dh / 2.0;
			break;

		case DEHT_CENTER:
			newRect.left -= dw / 2.0;
			newRect.top -= dh / 2.0;
			newRect.right += dw / 2.0;
			newRect.bottom += dh / 2.0;
			break;

		case DEHT_RIGHTMIDDLE:
			newRect.left = newRect.right - reqW;
			newRect.top -= dh / 2.0;
			newRect.bottom += dh / 2.0;
			break;

		default:
			// unsupported anchor for fitting
			return;
		}

		m_titleRect = newRect;

		BOOL needUpdate = newRect.Width() > curW + EPS || newRect.Height() > curH + EPS;
		
		if (needUpdate) {
			if (rect.left > newRect.left)
				rect.left = newRect.left;
			if (rect.right < newRect.right)
				rect.right = newRect.right;
			if (rect.top > newRect.top)
				rect.top = newRect.top;
			if (rect.bottom < newRect.bottom)
				rect.bottom = newRect.bottom;
		}
	}
	
	SetRect(rect.left, rect.top, rect.right, rect.bottom);
}

void CProMoBlockView::Reposition()
/* ============================================================
	Function :		CProMoBlockView::Reposition
	Description :	Repositions all the labels attached to the
					block, such that the anchoring is preserved.
	Access :		Public

	Return :		void
	Parameters :	CProMoLabel* label - the label to link

   ============================================================*/
{
	CObArray labels;
	m_blockModel->GetLabels(labels);
	int i = 0;

	for (i = 0; i < labels.GetSize(); i++) {
		CProMoLabel* label = dynamic_cast<CProMoLabel*>(labels.GetAt(i));
		if (label) {
			//reposition labels
			if (!label->IsSelected()) {
				label->Reposition();
			}
		}
	}

	CObArray blocks;
	m_blockModel->GetBoundaryBlocks(blocks, DEHT_BODY);

	for (i = 0; i < blocks.GetSize(); i++) {
		CProMoBlockModel* block = dynamic_cast<CProMoBlockModel*>(blocks.GetAt(i));
		if (block) {
			CProMoBlockView* view = block->GetMainView();
			if (view) {
				CDoubleRect blockRect = view->GetRect();
				double blockHeight = blockRect.Height();
				double blockWidth = blockRect.Width();
				switch (block->m_attachmentType) {
				case DEHT_TOP:
					blockRect.top = GetTop() - (blockHeight / 2);
					blockRect.bottom = GetTop() + (blockHeight / 2);
					break;
				case DEHT_BOTTOM:
					blockRect.top = GetBottom() - (blockHeight / 2);
					blockRect.bottom = GetBottom() + (blockHeight / 2);
					break;
				case DEHT_LEFT:
					blockRect.left = GetLeft() - (blockWidth / 2);
					blockRect.right = GetLeft() + (blockWidth / 2);
					break;
				case DEHT_RIGHT:
					blockRect.left = GetRight() - (blockWidth / 2);
					blockRect.right = GetRight() + (blockWidth / 2);
					break;
				}
				view->SetRect(blockRect.ToCRect());
			}
		}
	}


}

BOOL CProMoBlockView::IsLocked(const unsigned int& flag) const
/* ============================================================
	Function :		CProMoBlockView::IsLocked
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

unsigned int CProMoBlockView::GetLock() const
/* ============================================================
	Function :		CProMoBlockView::IsLocked
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

void CProMoBlockView::SetLock(const unsigned int& flag)
/* ============================================================
	Function :		CProMoBlockView::SetLock
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

CString CProMoBlockView::GetFontName() const
/* ============================================================
	Function :		CProMoBlockView::GetFontName()
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

	if (m_blockModel) {
		CObArray labels;
		m_blockModel->GetLabels(labels);

		for (int i = 0; i < labels.GetSize(); i++) {
			CProMoLabel* label = dynamic_cast<CProMoLabel*>(labels.GetAt(i));

			if (!label || label->IsLocked(LOCK_FONTNAME)) {
				continue;
			}
			CString currValue = label->GetFontName();
			if (!hasValue) {
				fontName = currValue;
				hasValue = TRUE;
			}
			else if (fontName != currValue ) {
				return CString();
			}
		}
	}
	return fontName;
}

unsigned int CProMoBlockView::GetFontSize() const
/* ============================================================
	Function :		CProMoBlockView::GetFontSize()
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
	
	if (m_blockModel) {
		CObArray labels;
		m_blockModel->GetLabels(labels);

		for (int i = 0; i < labels.GetSize(); i++) {
			CProMoLabel* label = dynamic_cast<CProMoLabel*>(labels.GetAt(i));
			
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
	return fontSize;
}

unsigned int CProMoBlockView::GetFontWeight() const
/* ============================================================
	Function :		CProMoBlockView::GetFontWeight()
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

	if (m_blockModel) {
		CObArray labels;
		m_blockModel->GetLabels(labels);

		for (int i = 0; i < labels.GetSize(); i++) {
			CProMoLabel* label = dynamic_cast<CProMoLabel*>(labels.GetAt(i));
			
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
	return fontWeight;
}

BOOL CProMoBlockView::IsFontItalic() const
/* ============================================================
	Function :		CProMoBlockView::IsFontItalic()
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

	if (m_blockModel) {
		CObArray labels;
		m_blockModel->GetLabels(labels);

		for (int i = 0; i < labels.GetSize(); i++) {
			CProMoLabel* label = dynamic_cast<CProMoLabel*>(labels.GetAt(i));
			
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
	return italic;
}

BOOL CProMoBlockView::IsFontUnderline() const
/* ============================================================
	Function :		CProMoBlockView::IsFontUnderline()
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

	if (m_blockModel) {
		CObArray labels;
		m_blockModel->GetLabels(labels);

		for (int i = 0; i < labels.GetSize(); i++) {
			CProMoLabel* label = dynamic_cast<CProMoLabel*>(labels.GetAt(i));
			
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
	return underline;
}

BOOL CProMoBlockView::IsFontStrikeOut() const
/* ============================================================
	Function :		CProMoBlockView::IsFontStrikeOut()
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

	if (m_blockModel) {
		CObArray labels;
		m_blockModel->GetLabels(labels);

		for (int i = 0; i < labels.GetSize(); i++) {
			CProMoLabel* label = dynamic_cast<CProMoLabel*>(labels.GetAt(i));
			
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
	return strikeOut;
}

COLORREF CProMoBlockView::GetTextColor() const
/* ============================================================
	Function :		CProMoBlockView::GetTextColor()
	Description :	Returns the color of the text in the labels
	Access :		Public

	Return :		COLORREF	-	The color of the text in
									the label
	Parameters :	none

   ============================================================*/
{
	COLORREF textColor = RGB(0, 0, 0);
	BOOL hasValue = FALSE;

	if (m_blockModel) {
		CObArray labels;
		m_blockModel->GetLabels(labels);

		for (int i = 0; i < labels.GetSize(); i++) {
			CProMoLabel* label = dynamic_cast<CProMoLabel*>(labels.GetAt(i));
			
		if (!label || label->IsLocked(LOCK_TEXTCOLOR)) {
				continue;
			}
			COLORREF currValue = label->GetTextColor();
			if (!hasValue) {
				textColor = currValue;
				hasValue = TRUE;
			}
			else if (textColor != currValue) {
				return RGB(0,0,0);
			}
		}
	}
	return textColor;
}

COLORREF CProMoBlockView::GetBkColor() const
/* ============================================================
	Function :		CProMoBlockView::GetBkColor()
	Description :	Returns the background color of the block
	Access :		Public

	Return :		COLORREF	-	The background color of the
									block
	Parameters :	none

   ============================================================*/
{
	return m_bkColor;
}

unsigned int CProMoBlockView::GetTextHorizontalAlignment() const
/* ============================================================
	Function :		CProMoBlockView::GetTextHorizontalAlignment()
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

	if (m_blockModel) {
		CObArray labels;
		m_blockModel->GetLabels(labels);

		for (int i = 0; i < labels.GetSize(); i++) {
			CProMoLabel* label = dynamic_cast<CProMoLabel*>(labels.GetAt(i));
			
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
	return alignment;
}

unsigned int CProMoBlockView::GetTextVerticalAlignment() const
/* ============================================================
	Function :		CProMoBlockView::GetTextVerticalAlignment()
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

	if (m_blockModel) {
		CObArray labels;
		m_blockModel->GetLabels(labels);

		for (int i = 0; i < labels.GetSize(); i++) {
			CProMoLabel* label = dynamic_cast<CProMoLabel*>(labels.GetAt(i));
			
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
	return alignment;
}

BOOL CProMoBlockView::HasTextAlignmentFlag(unsigned int flag) const
/* ============================================================
	Function :		CProMoBlockView::HasTextAlignmentFlag()
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

	if (m_blockModel) {
		CObArray labels;
		m_blockModel->GetLabels(labels);

		for (int i = 0; i < labels.GetSize(); i++) {
			CProMoLabel* label = dynamic_cast<CProMoLabel*>(labels.GetAt(i));
			
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
	return hasFlag;
}

unsigned int CProMoBlockView::GetTextAlignment() const
/* ============================================================
	Function :		CProMoBlockView::GetTextAlignment()
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

	if (m_blockModel) {
		CObArray labels;
		m_blockModel->GetLabels(labels);

		for (int i = 0; i < labels.GetSize(); i++) {
			CProMoLabel* label = dynamic_cast<CProMoLabel*>(labels.GetAt(i));
			
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
	return alignment;
}

BOOL CProMoBlockView::IsVisible() const
/* ============================================================
	Function :		CProMoBlockView::IsVisible()
	Description :	Returns if the block is visible
	Access :		Public

	Return :		BOOL		-	"TRUE" if the block is
									visible
	Parameters :	none

   ============================================================*/
{
	return m_visible;
}

unsigned int CProMoBlockView::GetBkMode() const
/* ============================================================
	Function :		CProMoBlockView::GetBkMode()
	Description :	Returns the background style of the block
	Access :		Public

	Return :		unsigned int	-	The background style of
										the block
	Parameters :	none

   ============================================================*/
{
	return m_bkMode;
}

COLORREF CProMoBlockView::GetLineColor() const
/* ============================================================
	Function :		CProMoBlockView::GetLineColor()
	Description :	Returns the line color of the block
	Access :		Public

	Return :		COLORREF	-	The line color of the
									block
	Parameters :	none

   ============================================================*/
{
	return m_lineColor;
}

unsigned int CProMoBlockView::GetLineWidth() const
/* ============================================================
	Function :		CProMoBlockView::GetLineWidth()
	Description :	Returns the line width of the block
	Access :		Public

	Return :		unsigned int	-	The line width of the
										block
	Parameters :	none

   ============================================================*/
{
	return m_lineWidth;
}

unsigned int CProMoBlockView::GetLineStyle() const
/* ============================================================
	Function :		CProMoBlockView::GetLineStyle()
	Description :	Returns the line style of the block
	Access :		Public

	Return :		unsigned int	-	The line style of the
										block
	Parameters :	none

   ============================================================*/
{
	return m_lineStyle;
}

COLORREF CProMoBlockView::GetFillColor() const
/* ============================================================
	Function :		CProMoBlockView::GetFillColor()
	Description :	Returns the fill color of the block
	Access :		Public

	Return :		COLORREF	-	The fill color of the
									block
	Parameters :	none

   ============================================================*/
{
	return m_fillColor;
}

BOOL CProMoBlockView::IsFillPattern() const
/* ============================================================
	Function :		CProMoBlockView::IsFillPattern()
	Description :	Returns if the block should be filled with
					a pattern
	Access :		Public

	Return :		BOOL		-	"TRUE" if the block should
									be filled with a pattern
	Parameters :	none

   ============================================================*/
{
	return m_fillPattern;
}

unsigned int CProMoBlockView::GetFillStyle() const
/* ============================================================
	Function :		CProMoBlockView::GetFillStyle()
	Description :	Returns the fill style of the block
	Access :		Public

	Return :		unsigned int	-	The fill style of the
										block
	Parameters :	none

   ============================================================*/
{
	return m_fillStyle;
}

// Setters
BOOL CProMoBlockView::SetFontName(const CString& name)
/* ============================================================
	Function :		CProMoBlockView::SetFontName()
	Description :	Sets the name of the font used to display
					the labels
	Access :		Public

	Return :		BOOL					-	"TRUE" if the
												operation
												succeeded
	Parameters :	CString& name			-	The name of
												the font

   ============================================================*/
{
	BOOL result = TRUE;
	if (IsLocked(LOCK_FONTNAME))
		return FALSE;

	if (m_blockModel) {
		CObArray labels;
		m_blockModel->GetLabels(labels);

		for (int i = 0; i < labels.GetSize(); i++) {
			CProMoLabel* label = dynamic_cast<CProMoLabel*>(labels.GetAt(i));
			if (!label || label->IsLocked(LOCK_FONTNAME)) {
				continue;
			}
			result &= label->SetFontName(name);
		}
	}
	return result;
}

BOOL CProMoBlockView::SetFontSize(const unsigned int& size)
/* ============================================================
	Function :		CProMoBlockView::SetFontSize()
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
	if (m_blockModel) {
		CObArray labels;
		m_blockModel->GetLabels(labels);

		for (int i = 0; i < labels.GetSize(); i++) {
			CProMoLabel* label = dynamic_cast<CProMoLabel*>(labels.GetAt(i));
			if (!label || label->IsLocked(LOCK_FONTSIZE)) {
				continue;
			}
			result &= label->SetFontSize(size);
		}
	}
	return result;
}

BOOL CProMoBlockView::SetFontWeight(const unsigned int& weight)
/* ============================================================
	Function :		CProMoBlockView::SetFontWeight()
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
	if (m_blockModel) {
		CObArray labels;
		m_blockModel->GetLabels(labels);

		for (int i = 0; i < labels.GetSize(); i++) {
			CProMoLabel* label = dynamic_cast<CProMoLabel*>(labels.GetAt(i));
		if (!label || label->IsLocked(LOCK_FONTWEIGHT)) {
				continue;
			}
			result &= label->SetFontWeight(weight);
		}
	}
	return result;
}

BOOL CProMoBlockView::SetFontItalic(const BOOL& italic)
/* ============================================================
	Function :		CProMoBlockView::SetFontItalic()
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
	if (m_blockModel) {
		CObArray labels;
		m_blockModel->GetLabels(labels);

		for (int i = 0; i < labels.GetSize(); i++) {
			CProMoLabel* label = dynamic_cast<CProMoLabel*>(labels.GetAt(i));
			if (!label || label->IsLocked(LOCK_FONTITALIC)) {
				continue;
			}
			result &= label->SetFontItalic(italic);
		}
	}
	return result;
}

BOOL CProMoBlockView::SetFontUnderline(const BOOL& underline)
/* ============================================================
	Function :		CProMoBlockView::SetFontUnderline()
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
	if (m_blockModel) {
		CObArray labels;
		m_blockModel->GetLabels(labels);

		for (int i = 0; i < labels.GetSize(); i++) {
			CProMoLabel* label = dynamic_cast<CProMoLabel*>(labels.GetAt(i));
			if (!label || label->IsLocked(LOCK_FONTUNDERLINE)) {
				continue;
			}
			result &= label->SetFontUnderline(underline);
		}
	}
	return result;
}

BOOL CProMoBlockView::SetFontStrikeOut(const BOOL& strikeOut)
/* ============================================================
	Function :		CProMoBlockView::SetFontStrikeOut()
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
	if (m_blockModel) {
		CObArray labels;
		m_blockModel->GetLabels(labels);

		for (int i = 0; i < labels.GetSize(); i++) {
			CProMoLabel* label = dynamic_cast<CProMoLabel*>(labels.GetAt(i));
			if (!label || label->IsLocked(LOCK_FONTSTRIKEOUT)) {
				continue;
			}
			result &= label->SetFontStrikeOut(strikeOut);
		}
	}
	return result;
}

BOOL CProMoBlockView::SetTextColor(const COLORREF& color)
/* ============================================================
	Function :		CProMoBlockView::SetTextColor()
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
	if (m_blockModel) {
		CObArray labels;
		m_blockModel->GetLabels(labels);

		for (int i = 0; i < labels.GetSize(); i++) {
			CProMoLabel* label = dynamic_cast<CProMoLabel*>(labels.GetAt(i));
			if (!label || label->IsLocked(LOCK_TEXTCOLOR)) {
				continue;
			}
			result &= label->SetTextColor(color);
		}
	}
	return result;
}

BOOL CProMoBlockView::SetBkColor(const COLORREF& color)
/* ============================================================
	Function :		CProMoBlockView::SetBkColor()
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

BOOL CProMoBlockView::SetTextAlignmentFlag(const unsigned int& flag, const BOOL& enabled)
/* ============================================================
	Function :		CProMoBlockView::SetTextAlignmentFlag()
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

	if (m_blockModel) {
		CObArray labels;
		m_blockModel->GetLabels(labels);

		for (int i = 0; i < labels.GetSize(); i++) {
			CProMoLabel* label = dynamic_cast<CProMoLabel*>(labels.GetAt(i));
		if (!label || label->IsLocked(LOCK_ALIGNMENT)) {
				continue;
			}
			result &= label->SetTextAlignmentFlag(flag, enabled);
		}
	}
	return result;
}

BOOL CProMoBlockView::SetTextHorizontalAlignment(const unsigned int& alignment)
/* ============================================================
	Function :		CProMoBlockView::SetTextHorizontalAlignment()
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

	if (m_blockModel) {
		CObArray labels;
		m_blockModel->GetLabels(labels);

		for (int i = 0; i < labels.GetSize(); i++) {
			CProMoLabel* label = dynamic_cast<CProMoLabel*>(labels.GetAt(i));
			if (!label || label->IsLocked(LOCK_ALIGNMENT)) {
				continue;
			}
			result &= label->SetTextHorizontalAlignment(alignment);
		}
	}
	return result;
}

BOOL CProMoBlockView::SetTextVerticalAlignment(const unsigned int& alignment)
/* ============================================================
	Function :		CProMoBlockView::SetTextVerticalAlignment()
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

	if (m_blockModel) {
		CObArray labels;
		m_blockModel->GetLabels(labels);

		for (int i = 0; i < labels.GetSize(); i++) {
			CProMoLabel* label = dynamic_cast<CProMoLabel*>(labels.GetAt(i));
		if (!label || label->IsLocked(LOCK_ALIGNMENT)) {
				continue;
			}
			result &= label->SetTextVerticalAlignment(alignment);
		}
	}
	return result;
}

BOOL CProMoBlockView::SetTextAlignment(const unsigned int& alignment)
/* ============================================================
	Function :		CProMoBlockView::SetTextAlignment()
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
	
	if (m_blockModel) {
		CObArray labels;
		m_blockModel->GetLabels(labels);

		for (int i = 0; i < labels.GetSize(); i++) {
			CProMoLabel* label = dynamic_cast<CProMoLabel*>(labels.GetAt(i));
			if (!label || label->IsLocked(LOCK_ALIGNMENT)) {
				continue;
			}
			result &= label->SetTextAlignment(alignment);
		}
	}
	return result;
}

BOOL CProMoBlockView::SetVisible(const BOOL& visible)
/* ============================================================
	Function :		CProMoBlockView::SetVisible()
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

BOOL CProMoBlockView::SetBkMode(const unsigned int& mode)
/* ============================================================
	Function :		CProMoBlockView::SetBkMode()
	Description :	Sets the background style of the block
	Access :		Public

	Return :		BOOL				-	"TRUE" if the operation
											succeeded
	Parameters :	unsigned int& model	-	The background style of
											the block

   ============================================================*/
{
	if (IsLocked(LOCK_BKMODE))
		return FALSE;
	m_bkMode = mode;
	return TRUE;
}

BOOL CProMoBlockView::SetLineColor(const COLORREF& color)
/* ============================================================
	Function :		CProMoBlockView::SetLineColor()
	Description :	Sets the line color of the block
	Access :		Public

	Return :		BOOL					-	"TRUE" if the
												operation
												succeeded
	Parameters :	COLORREF& color			-	The line color
												of the block

   ============================================================*/
{
	if (IsLocked(LOCK_LINECOLOR))
		return FALSE;
	m_lineColor = color;
	return TRUE;
}

BOOL CProMoBlockView::SetLineWidth(const unsigned int& width)
/* ============================================================
	Function :		CProMoBlockView::SetLineWidth()
	Description :	Sets the line width of the block
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

BOOL CProMoBlockView::SetLineStyle(const unsigned int& style)
/* ============================================================
	Function :		CProMoBlockView::SetLineStyle()
	Description :	Sets the line style of the block
	Access :		Public

	Return :		BOOL					-	"TRUE" if the
												operation
												succeeded
	Parameters :	unsigned int& style		-	The line style
												of the block

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

BOOL CProMoBlockView::SetFillColor(const COLORREF& color)
/* ============================================================
	Function :		CProMoBlockView::SetFillColor()
	Description :	Sets the fill color of the block
	Access :		Public

	Return :		BOOL					-	"TRUE" if the
												operation
												succeeded
	Parameters :	COLORREF& color			-	The fill color
												of the block

   ============================================================*/
{
	if (IsLocked(LOCK_FILLCOLOR))
		return FALSE;
	m_fillColor = color;
	return TRUE;
}

BOOL CProMoBlockView::SetFillPattern(const BOOL& pattern)
/* ============================================================
	Function :		CProMoBlockView::SetFillPattern()
	Description :	Sets whether the fill style of the block is
					patterned
	Access :		Public

	Return :		BOOL					-	"TRUE" if the
												operation
												succeeded
	Parameters :	BOOL& pattern			-	"TRUE" if the
												fill style 
												should be
												a pattern

   ============================================================*/
{
	if (IsLocked(LOCK_FILLSTYLE))
		return FALSE;
	m_fillPattern = pattern;
	return TRUE;
}

BOOL CProMoBlockView::SetFillStyle(const unsigned int& style)
/* ============================================================
	Function :		CProMoBlockView::SetFillStyle()
	Description :	Sets the fill style of the block
	Access :		Public

	Return :		BOOL					-	"TRUE" if the
												operation
												succeeded
	Parameters :	unsigned int& style		-	The fill style
												of the block

   ============================================================*/
{
	if (IsLocked(LOCK_FILLSTYLE))
		return FALSE;
	m_fillStyle = style;
	return TRUE;
}

