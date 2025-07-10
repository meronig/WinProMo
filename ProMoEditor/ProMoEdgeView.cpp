/* ==========================================================================
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
#include "../DiagramEditor/Tokenizer.h"
#include <math.h>

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

	SetMinimumSize(CSize(-1, -1));
	SetType(_T("promo_edge_view"));
	SetTitle(_T(""));

	SetPropertyDialog(&m_dlg, CPropertyDialog::IDD);

	SetName(CProMoNameFactory::GetID());

	m_source = NULL;
	m_dest = NULL;
	m_edgemodel = NULL;
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
		m_source->SetBottom(GetBottom());
		m_source->SetRight(GetRight());
		m_source->SetDestination(GetDestination());
	}
	
	if (m_dest) {
		m_dest->SetTop(GetTop());
		m_dest->SetLeft(GetLeft());
		m_dest->SetSource(GetSource());
	}
	
	SetSource(NULL);
	SetDestination(NULL);

	if (m_dlg.m_hWnd)
		m_dlg.DestroyWindow();

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
	if (GetModel()) {
		GetModel()->Copy(objView->GetModel());
	}
}

void CProMoEdgeView::DrawHead(CDC* dc, CRect rect, int size) 
/* ============================================================
	Function :		CProMoEdgeView::DrawHead
	Description :	Draws the head of the edge.
	Access :		Protected

	Return :		void
	Parameters :	CDC* dc		-	The CDC to draw to.
					CRect rect	-	The real rectangle of the 
									object.
					int size	-	The size of the head

	Usage :			The function should clean up all selected
					objects. Note that the CDC is a memory CDC,
					so creating a memory CDC in this function
					will probably not speed up the function.
					Override this function to change the shape
					being drawn.

   ============================================================*/
{

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
	
}

void CProMoEdgeView::DrawTail(CDC* dc, CRect rect, int size)
/* ============================================================
	Function :		CProMoEdgeView::DrawTail
	Description :	Draws the tail of the edge.
	Access :		Protected

	Return :		void
	Parameters :	CDC* dc		-	The CDC to draw to.
					CRect rect	-	The real rectangle of the
									object.
					int size	-	The size of the tail

	Usage :			The function should clean up all selected
					objects. Note that the CDC is a memory CDC,
					so creating a memory CDC in this function
					will probably not speed up the function.
					Override this function to change the shape
					being drawn.

   ============================================================*/
{
	// 1. Define the start and end points
	int x1 = rect.TopLeft().x;
	int y1 = rect.TopLeft().y;
	int x2 = rect.BottomRight().x;
	int y2 = rect.BottomRight().y;

	// 2. Calculate the circle radius
	int radius = size / 2;

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
	CRect circleRect;
	circleRect.left = centerX - radius;
	circleRect.top = centerY - radius;
	circleRect.right = centerX + radius;
	circleRect.bottom = centerY + radius;

	// 8. Draw the circle
	dc->Ellipse(circleRect);
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
	if (m_source != NULL) {
		CProMoBlockView* obj = dynamic_cast<CProMoBlockView*>(m_source);
		if (obj) {
			CPoint pt = obj->GetIntersection(GetRect().TopLeft(), GetRect().BottomRight());
			if (pt.x >= 0) {
				SetTop(pt.y);
				SetLeft(pt.x);
			}
		}
		CProMoEdgeView* edge = dynamic_cast<CProMoEdgeView*>(m_source);
		if (edge) {
			SetTop(edge->GetBottom());
			SetLeft(edge->GetRight());
		}
	}
	if (m_dest != NULL) {
		CProMoBlockView* obj = dynamic_cast<CProMoBlockView*>(m_dest);
		if (obj) {
			CPoint pt = obj->GetIntersection(GetRect().BottomRight(), GetRect().TopLeft());
			if (pt.x >= 0) {
				SetBottom(pt.y);
				SetRight(pt.x);
			}
		}
		CProMoEdgeView* edge = dynamic_cast<CProMoEdgeView*>(m_dest);
		if (edge) {
			SetBottom(edge->GetTop());
			SetRight(edge->GetLeft());
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

	dc->SelectStockObject(BLACK_PEN);

	dc->MoveTo(rect.TopLeft());
	dc->LineTo(rect.BottomRight());

	//draw the tip only if it is the last segment
	if (m_dest == NULL) {
		DrawHead(dc, rect, 10);
	}

	//draw the tail only if it is the last segment
	if (m_source == NULL) {
		DrawTail(dc, rect, 10);
	}
		
	
	CString str = GetTitle();
	if (str.GetLength())
	{
		CFont font;
		font.CreateFont(-round(12.0 * GetZoom()), 0, 0, 0, FW_NORMAL, 0, 0, 0, 0, 0, 0, 0, 0, _T("Courier New"));
		dc->SelectObject(&font);
		int mode = dc->SetBkMode(TRANSPARENT);

		CRect rectTemp(rect);
		rectTemp.NormalizeRect();
		int cy = round(14.0 * GetZoom());
		int cut = round((double)GetMarkerSize().cx * GetZoom() / 2);
		CRect r(rect.right - cut, rect.top, rect.right - (rectTemp.Width() + cut), rect.bottom);
		if (rect.top == rect.bottom)
		{
			CRect r(rect.left, rect.top - (cy + cut), rect.right, rect.bottom);
			r.NormalizeRect();
			dc->DrawText(str, r, DT_NOPREFIX | DT_SINGLELINE | DT_VCENTER | DT_CENTER);
		}
		else
		{
			CRect r(rect.right - cut, rect.top, rect.right - (cy * str.GetLength() + cut), rect.bottom);
			r.NormalizeRect();
			dc->DrawText(str, r, DT_NOPREFIX | DT_SINGLELINE | DT_VCENTER | DT_RIGHT);
		}

		dc->SelectStockObject(DEFAULT_GUI_FONT);
		dc->SetBkMode(mode);

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

void CProMoEdgeView::SetSource(CDiagramEntity *source)
/* ============================================================
	Function :		CProMoEdgeView::SetSource
	Description :	Makes the object being passed as input
					parameter the source of this edge.
	Access :		Public

	Return :		void
	Parameters :	CDiagramEntity* source	-	the object that
												should be the
												source

   ============================================================*/
{
	//save the old source edge view
	CProMoEdgeView* oldSourceView = m_source;

	CProMoBlockView* blockView = dynamic_cast<CProMoBlockView*>(source);
	//new source is a block view
	if (blockView) {
		//connect the elements at the model level
		GetModel()->SetSource(blockView->GetModel());
		//disconnect the edges at the view level
		m_source = NULL;
	}
	
	//new source is an edge view
	CProMoEdgeView* edgeView = dynamic_cast<CProMoEdgeView*>(source);

	// the source edge view has changed
	if (source != oldSourceView) {

		if (edgeView) {
			//just connect the two views
			m_source = edgeView;
			edgeView->SetDestination(this);
		}

		else {
			m_source = NULL;
		}
		
		if (m_source != oldSourceView) {
			//set the destination to null
			if (oldSourceView) {
				oldSourceView->m_dest = NULL;
			}
		}
		
	}
	

	Reposition();

}

void CProMoEdgeView::SetDestination(CDiagramEntity *destination)
/* ============================================================
	Function :		CProMoEdgeView::SetDestination
	Description :	Makes the object being passed as input
					parameter the destination of this edge
	Access :		Public

	Return :		void
	Parameters :	CDiagramEntity* destination	-	the object
													that should
													be the
													destination

   ============================================================*/
{
	//save the old source edge view
	CProMoEdgeView* oldDestView = m_dest;

	CProMoBlockView* blockView = dynamic_cast<CProMoBlockView*>(destination);
	//new source is a block view
	if (blockView) {
		//connect the elements at the model level
		GetModel()->SetDestination(blockView->GetModel());
		//disconnect the edges at the view level
		m_dest = NULL;
	}

	//new source is an edge view
	CProMoEdgeView* edgeView = dynamic_cast<CProMoEdgeView*>(destination);

	if (oldDestView != destination) {

		if (edgeView) {
			//just connect the two views
			m_dest = edgeView;
			edgeView->SetSource(this);
		}

		else {
			m_dest = NULL;
		}

		// the source edge view has changed
		if (m_dest != oldDestView) {
			//set the destination to null
			if (oldDestView) {
				oldDestView->m_source = NULL;
			}
		}
	}

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
	return m_source;
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
	return m_dest;
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
	if (GetSource()){
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
	if (GetSource()) {
		return FALSE;
	}
	return TRUE;
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
	CDiagramEntity* newEntity = Clone();
	
	CProMoEdgeView* newEdge = dynamic_cast<CProMoEdgeView*>(newEntity);

	if (newEdge) {
		//compute the length and position of both edges
		CRect edgeRect = GetRect();
		CRect newEdgeRect(edgeRect);
		edgeRect.bottom = edgeRect.top + (edgeRect.Height() / 2);
		edgeRect.right = edgeRect.left + (edgeRect.Width() / 2);
		SetRect(edgeRect);
		newEdgeRect.top = newEdgeRect.bottom - (newEdgeRect.Height() / 2);;
		newEdgeRect.left = newEdgeRect.right - (newEdgeRect.Width() / 2);;
		newEdge->SetRect(newEdgeRect);
		newEdge->Select(FALSE);
		//update edge links
		newEdge->SetDestination(GetDestination());
		newEdge->SetSource(this);
		newEdge->SetModel(GetModel());
		//clear duplicated properties
		newEdge->SetTitle(_T(""));
		return newEdge;
	}
	return NULL;
	
}

CProMoEdgeModel* CProMoEdgeView::GetModel() const
/* ============================================================
	Function :		CProMoEdgeView::GetModel
	Description :	Returns a pointer to the model of this
					edge
	Access :		Public

	Return :		CProMoEdgeModel*	-	A pointer to the
											model
	Parameters :	none

   ============================================================*/
{
	return m_edgemodel;
}

void CProMoEdgeView::SetModel(CProMoEdgeModel* model)
/* ============================================================
	Function :		CProMoEdgeView::SetModel
	Description :	Makes the object being passed as input
					parameter the model for this edge
	Access :		Public

	Return :		void
	Parameters :	CProMoEdgeModel* block	-	the object that
												should be the
												model

   ============================================================*/
{
	if (m_edgemodel != model) {
		CProMoEdgeModel* oldModel = m_edgemodel;
		m_edgemodel = model;
		
		//link this class to the new model
		if (model) {
			model->LinkView(this);
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
	CStringReplace(model, _T(":"), _T("\\colon"));
	CStringReplace(model, _T(";"), _T("\\semicolon"));
	CStringReplace(model, _T(","), _T("\\comma"));
	CStringReplace(model, _T("\r\n"), _T("\\newline"));

	CString title = GetTitle();
	CStringReplace(title, _T(":"), _T("\\colon"));
	CStringReplace(title, _T(";"), _T("\\semicolon"));
	CStringReplace(title, _T(","), _T("\\comma"));
	CStringReplace(title, _T("\r\n"), _T("\\newline"));

	CString name = GetName();
	CStringReplace(name, _T(":"), _T("\\colon"));
	CStringReplace(name, _T(";"), _T("\\semicolon"));
	CStringReplace(name, _T(","), _T("\\comma"));
	CStringReplace(name, _T("\r\n"), _T("\\newline"));

	CString sourceString = _T("");

	CDiagramEntity* source = GetSource();

	if (source) {
		sourceString = source->GetName();
		CStringReplace(sourceString, _T(":"), _T("\\colon"));
		CStringReplace(sourceString, _T(";"), _T("\\semicolon"));
		CStringReplace(sourceString, _T(","), _T("\\comma"));
		CStringReplace(sourceString, _T("\r\n"), _T("\\newline"));
	}

	CString destString = _T("");

	CDiagramEntity* dest = GetDestination();

	if (dest) {
		destString = dest->GetName();
		CStringReplace(destString, _T(":"), _T("\\colon"));
		CStringReplace(destString, _T(";"), _T("\\semicolon"));
		CStringReplace(destString, _T(","), _T("\\comma"));
		CStringReplace(destString, _T("\r\n"), _T("\\newline"));
	}

	str.Format(_T("%s:%s,%f,%f,%f,%f,%s,%i,%s,%s,%s"), (LPCTSTR)GetType(), (LPCTSTR)name, GetLeft(), GetTop(), GetRight(), GetBottom(), (LPCTSTR)title, GetGroup(), (LPCTSTR)model, (LPCTSTR)sourceString, (LPCTSTR)destString);

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
	CString data(str);
	if (data[data.GetLength() - 1] == _TCHAR(';'))
		data = data.Left(data.GetLength() - 1); // Strip the ';'

	CTokenizer tok(data);
	int size = tok.GetSize();
	if (size >= 7)
	{
		CString name;
		double left;
		double top;
		double right;
		double bottom;
		CString title;
		int group;
		int count = 0;

		tok.GetAt(count++, name);
		tok.GetAt(count++, left);
		tok.GetAt(count++, top);
		tok.GetAt(count++, right);
		tok.GetAt(count++, bottom);
		tok.GetAt(count++, title);
		tok.GetAt(count++, group);

		CDiagramEntity::SetRect(left, top, right, bottom);

		CStringReplace(title, _T("\\colon"), _T(":"));
		CStringReplace(title, _T("\\semicolon"), _T(";"));
		CStringReplace(title, _T("\\comma"), _T(","));
		CStringReplace(title, _T("\\newline"), _T("\r\n"));

		CStringReplace(name, _T("\\colon"), _T(":"));
		CStringReplace(name, _T("\\semicolon"), _T(";"));
		CStringReplace(name, _T("\\comma"), _T(","));
		CStringReplace(name, _T("\\newline"), _T("\r\n"));

		SetTitle(title);
		SetName(name);
		SetGroup(group);

		// Rebuild rest of string
		str = _T("");
		for (int t = count; t < size; t++)
		{
			tok.GetAt(t, data);

			str += data;
			if (t < size - 1)
				str += _T(",");
		}

		result = TRUE;
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
