#include "ProcessLineEdgeView.h"
#include "ProcessLineEdgeModel.h"
#include "ProcessEntityBlockView.h"
#include "LinkFactory.h"
#include "../stdafx.h"

CProcessLineEdgeView::CProcessLineEdgeView()
/* ============================================================
	Function :		CProcessLineEdge::CProcessLineEdge
	Description :	Constructor
	Access :		Public

	Return :		void
	Parameters :	none

	Usage :

   ============================================================*/
{

	SetMinimumSize(CSize(-1, -1));
	SetType(_T("process_edge_view"));
	SetTitle(_T(""));

	SetPropertyDialog(&m_dlg, CPropertyDialog::IDD);

	SetName(CLinkFactory::GetID());

	m_source = NULL;
	m_dest = NULL;
	m_edgemodel = NULL;
	setModel(new CProcessLineEdgeModel());
}

CProcessLineEdgeView::~CProcessLineEdgeView()
/* ============================================================
	Function :		CProcessLineEdge::~CProcessLineEdge
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

	setModel(NULL);

}

CDiagramEntity* CProcessLineEdgeView::Clone()
/* ============================================================
	Function :		CProcessLineEdge::Clone
	Description :	Clone this object to a new object.

	Return :		CDiagramEntity*	-	The new object.
	Parameters :	none

	Usage :			Call to create a clone of the object. The
					caller will have to delete the object.

   ============================================================*/

{

	CProcessLineEdgeView* obj = new CProcessLineEdgeView;
	obj->Copy(this);
	obj->m_source = NULL;
	obj->m_dest = NULL;
	//obj->setModel(this->getModel());
	obj->setModel(new CProcessLineEdgeModel());
	return obj;
}

void CProcessLineEdgeView::DrawArrowHead(CDC* dc, POINT p0, POINT p1, int head_length, int head_width) {
	
	const float dx = static_cast<float>(p1.x - p0.x);
	const float dy = static_cast<float>(p1.y - p0.y);
	const auto length = sqrt(dx * dx + dy * dy);
	if (head_length < 1 || length < head_length) return;

	// ux,uy is a unit vector parallel to the line.
	const auto ux = dx / length;
	const auto uy = dy / length;

	// vx,vy is a unit vector perpendicular to ux,uy
	const auto vx = -uy;
	const auto vy = ux;

	const auto half_width = 0.5f * head_width;

	const POINT arrow[3] =
	{ p1,
	  POINT{ round(p1.x - head_length * ux + half_width * vx),
			 round(p1.y - head_length * uy + half_width * vy) },
	  POINT{ round(p1.x - head_length * ux - half_width * vx),
			 round(p1.y - head_length * uy - half_width * vy) }
	};
	dc->Polygon(arrow, 3);
}

void CProcessLineEdgeView::DrawArrowTail(CDC* dc, POINT p0, POINT p1, int circleDiameter)
{
	// 1. Define the start and end points
	int x1 = p0.x;
	int y1 = p0.y;
	int x2 = p1.x;
	int y2 = p1.y;

	// 2. Calculate the circle radius
	int radius = circleDiameter / 2;

	// 3. Find the center of the circle: it's the midpoint of (x1, y1) and the second intersection point (x3, y3)
	int dx = x2 - x1;
	int dy = y2 - y1;
	float lineLength = sqrt(dx * dx + dy * dy);

	// 4. Parametric form of the line
	// Find t such that the distance from (x1, y1) to (x3, y3) equals the diameter of the circle
	// We need t such that |t| = diameter / lineLength (scaled so that we can reach the exact distance)

	float t = static_cast<float>(circleDiameter) / lineLength;

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

void CProcessLineEdgeView::Reposition()
{
	//new
	if (m_source != NULL) {
		CProcessEntityBlockView* obj = dynamic_cast<CProcessEntityBlockView*>(m_source);
		if (obj) {
			CPoint pt = obj->getIntersection(GetRect().TopLeft(), GetRect().BottomRight());
			if (pt.x >= 0) {
				SetTop(pt.y);
				SetLeft(pt.x);
			}
		}
		CProcessLineEdgeView* edge = dynamic_cast<CProcessLineEdgeView*>(m_source);
		if (edge) {
			SetTop(edge->GetBottom());
			SetLeft(edge->GetRight());
		}
	}
	if (m_dest != NULL) {
		CProcessEntityBlockView* obj = dynamic_cast<CProcessEntityBlockView*>(m_dest);
		if (obj) {
			CPoint pt = obj->getIntersection(GetRect().BottomRight(), GetRect().TopLeft());
			if (pt.x >= 0) {
				SetBottom(pt.y);
				SetRight(pt.x);
			}
		}
		CProcessLineEdgeView* edge = dynamic_cast<CProcessLineEdgeView*>(m_dest);
		if (edge) {
			SetBottom(edge->GetTop());
			SetRight(edge->GetLeft());
		}
	}
}

void CProcessLineEdgeView::Draw(CDC* dc, CRect rect)
/* ============================================================
	Function :		CProcessLineEdge::Draw
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

	//draw the arrow tip only if it is the last segment
	if (m_dest == NULL) {
		DrawArrowHead(dc, rect.TopLeft(), rect.BottomRight(), 10, 10);
	}

	if (m_source == NULL) {
		DrawArrowTail(dc, rect.TopLeft(), rect.BottomRight(), 10);
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

int CProcessLineEdgeView::GetHitCode(const CPoint& point, const CRect& rect) const
{
	CRect rectTest = GetSelectionMarkerRect(DEHT_CENTER, rect);
	if (rectTest.PtInRect(point)) {
		return DEHT_CENTER;
	}
	return CDiagramLine::GetHitCode(point, rect);
}

HCURSOR CProcessLineEdgeView::GetCursor(int hit) const
{
	if (hit == DEHT_CENTER) {
		return LoadCursor(NULL, IDC_SIZEALL);
	}
	return CDiagramLine::GetCursor(hit);
}


CDiagramEntity* CProcessLineEdgeView::CreateFromString(const CString& str)
/* ============================================================
	Function :		CProcessLineEdge::CreateFromString
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

	CProcessLineEdgeView* obj = new CProcessLineEdgeView;
	if (!obj->FromString(str))
	{
		delete obj;
		obj = NULL;
	}

	return obj;

}

void CProcessLineEdgeView::SetSource(CDiagramEntity *source)
{
	//save the old source edge view
	CProcessLineEdgeView* oldSourceView = m_source;

	CProcessEntityBlockView* blockView = dynamic_cast<CProcessEntityBlockView*>(source);
	//new source is a block view
	if (blockView) {
		//connect the elements at the model level
		getModel()->SetSource(blockView->getModel());
		//disconnect the edges at the view level
		m_source = NULL;
	}
	
	//new source is an edge view
	CProcessLineEdgeView* edgeView = dynamic_cast<CProcessLineEdgeView*>(source);

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

void CProcessLineEdgeView::SetDestination(CDiagramEntity *destination)
{
	//save the old source edge view
	CProcessLineEdgeView* oldDestView = m_dest;

	CProcessEntityBlockView* blockView = dynamic_cast<CProcessEntityBlockView*>(destination);
	//new source is a block view
	if (blockView) {
		//connect the elements at the model level
		getModel()->SetDestination(blockView->getModel());
		//disconnect the edges at the view level
		m_dest = NULL;
	}

	//new source is an edge view
	CProcessLineEdgeView* edgeView = dynamic_cast<CProcessLineEdgeView*>(destination);

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

CDiagramEntity* CProcessLineEdgeView::GetSource() const
{
	return m_source;
}

CDiagramEntity* CProcessLineEdgeView::GetDestination() const
{
	return m_dest;
}

CProcessLineEdgeModel* CProcessLineEdgeView::getModel() const
{
	return m_edgemodel;
}

void CProcessLineEdgeView::setModel(CProcessLineEdgeModel* model)
{
	if (m_edgemodel != model) {
		CProcessLineEdgeModel* oldModel = m_edgemodel;
		m_edgemodel = model;
		
		//link this class to the new model
		if (model) {
			model->linkView(this);
		}
		//unlink this class from the old model
		if (oldModel) {
			oldModel->unlinkView(this);
			//if the old model has no views, delete it
			if (oldModel->getViews()->GetSize() == 0) {
				delete oldModel;
			}
		}
	}
}

CString CProcessLineEdgeView::GetDefaultGetString() const
{
	/* ============================================================
	Function :		CProcessLineEdge::GetDefaultString
	Description :	Gets the default properties of the object
					as a string.
	Access :		Protected

	Return :		CString	-	Resulting string
	Parameters :	none

	Usage :			Call as a part of the saving of objects
					to disk.

   ============================================================*/
   //ASSERT_VALID(false);

	ASSERT_VALID(this->getModel());

	CString str;

	CString model = getModel()->GetName();
	model.Replace(_T(":"), _T("\\colon"));
	model.Replace(_T(";"), _T("\\semicolon"));
	model.Replace(_T(","), _T("\\comma"));
	model.Replace(_T("\r\n"), _T("\\newline"));

	CString title = GetTitle();
	title.Replace(_T(":"), _T("\\colon"));
	title.Replace(_T(";"), _T("\\semicolon"));
	title.Replace(_T(","), _T("\\comma"));
	title.Replace(_T("\r\n"), _T("\\newline"));

	CString name = GetName();
	name.Replace(_T(":"), _T("\\colon"));
	name.Replace(_T(";"), _T("\\semicolon"));
	name.Replace(_T(","), _T("\\comma"));
	name.Replace(_T("\r\n"), _T("\\newline"));

	CString sourceString = _T("");

	CDiagramEntity* source = GetSource();

	if (source) {
		sourceString = source->GetName();
		sourceString.Replace(_T(":"), _T("\\colon"));
		sourceString.Replace(_T(";"), _T("\\semicolon"));
		sourceString.Replace(_T(","), _T("\\comma"));
		sourceString.Replace(_T("\r\n"), _T("\\newline"));
	}

	CString destString = _T("");

	CDiagramEntity* dest = GetDestination();

	if (dest) {
		destString = dest->GetName();
		destString.Replace(_T(":"), _T("\\colon"));
		destString.Replace(_T(";"), _T("\\semicolon"));
		destString.Replace(_T(","), _T("\\comma"));
		destString.Replace(_T("\r\n"), _T("\\newline"));
	}

	str.Format(_T("%s:%f,%f,%f,%f,%s,%s,%i,%s,%s,%s"), GetType(), GetLeft(), GetTop(), GetRight(), GetBottom(), title, name, GetGroup(), model, sourceString, destString);

	return str;

}

void CProcessLineEdgeView::DrawSelectionMarkers(CDC* dc, CRect rect) const
{
	CRect rectSelect;

	dc->SelectStockObject(BLACK_BRUSH);
	rectSelect = GetSelectionMarkerRect(DEHT_CENTER, rect);
	dc->Rectangle(rectSelect);

	CDiagramLine::DrawSelectionMarkers(dc, rect);
}

CRect CProcessLineEdgeView::GetSelectionMarkerRect(UINT marker, CRect rect) const
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
