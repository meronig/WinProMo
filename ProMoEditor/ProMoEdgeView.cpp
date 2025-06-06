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
	setModel(new CProMoEdgeModel());
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

	setModel(NULL);

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
	obj->m_source = NULL;
	obj->m_dest = NULL;
	obj->SetName(CProMoNameFactory::GetID());
	obj->setModel(new CProMoEdgeModel());
	return obj;
}

void CProMoEdgeView::DrawArrowHead(CDC* dc, POINT p0, POINT p1, int head_length, int head_width) {
	
	
	const double dx = static_cast<double>(p1.x) - static_cast<double>(p0.x);
	const double dy = static_cast<double>(p1.y) - static_cast<double>(p0.y);
	const double length = sqrt(dx * dx + dy * dy);
	if (head_length < 1 || length < head_length) return;

	// ux,uy is a unit vector parallel to the line.
	const double ux = dx / length;
	const double uy = dy / length;

	// vx,vy is a unit vector perpendicular to ux,uy
	const double vx = -uy;
	const double vy = ux;

	const double half_width = 0.5 * head_width;

	
	CPoint arrow[3];
	arrow[0] = p1;
	arrow[1] = CPoint (round(p1.x - head_length * ux + half_width * vx),
			 round(p1.y - head_length * uy + half_width * vy) );
	arrow[2] = CPoint ( round(p1.x - head_length * ux - half_width * vx),
			 round(p1.y - head_length * uy - half_width * vy) );
	dc->Polygon(arrow, 3);
	
}

void CProMoEdgeView::DrawArrowTail(CDC* dc, POINT p0, POINT p1, int circleDiameter)
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
	double lineLength = sqrt((double)dx * dx + (double)dy * dy);

	// 4. Parametric form of the line
	// Find t such that the distance from (x1, y1) to (x3, y3) equals the diameter of the circle
	// We need t such that |t| = diameter / lineLength (scaled so that we can reach the exact distance)

	double t = static_cast<double>(circleDiameter) / lineLength;

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
{
	if (m_source != NULL) {
		CProMoBlockView* obj = dynamic_cast<CProMoBlockView*>(m_source);
		if (obj) {
			CPoint pt = obj->getIntersection(GetRect().TopLeft(), GetRect().BottomRight());
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
			CPoint pt = obj->getIntersection(GetRect().BottomRight(), GetRect().TopLeft());
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

int CProMoEdgeView::GetHitCode(const CPoint& point, const CRect& rect) const
{
	CRect rectTest = GetSelectionMarkerRect(DEHT_CENTER, rect);
	if (rectTest.PtInRect(point)) {
		return DEHT_CENTER;
	}
	return CDiagramLine::GetHitCode(point, rect);
}

HCURSOR CProMoEdgeView::GetCursor(int hit) const
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
{
	//save the old source edge view
	CProMoEdgeView* oldSourceView = m_source;

	CProMoBlockView* blockView = dynamic_cast<CProMoBlockView*>(source);
	//new source is a block view
	if (blockView) {
		//connect the elements at the model level
		getModel()->SetSource(blockView->getModel());
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
{
	//save the old source edge view
	CProMoEdgeView* oldDestView = m_dest;

	CProMoBlockView* blockView = dynamic_cast<CProMoBlockView*>(destination);
	//new source is a block view
	if (blockView) {
		//connect the elements at the model level
		getModel()->SetDestination(blockView->getModel());
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
{
	return m_source;
}

CDiagramEntity* CProMoEdgeView::GetDestination() const
{
	return m_dest;
}

CProMoEdgeModel* CProMoEdgeView::getModel() const
{
	return m_edgemodel;
}

void CProMoEdgeView::setModel(CProMoEdgeModel* model)
{
	if (m_edgemodel != model) {
		CProMoEdgeModel* oldModel = m_edgemodel;
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

	ASSERT_VALID(this->getModel());

	CString str;

	CString model = getModel()->GetName();
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
{
	CRect rectSelect;

	dc->SelectStockObject(BLACK_BRUSH);
	rectSelect = GetSelectionMarkerRect(DEHT_CENTER, rect);
	dc->Rectangle(rectSelect);

	CDiagramLine::DrawSelectionMarkers(dc, rect);
}

CRect CProMoEdgeView::GetSelectionMarkerRect(UINT marker, CRect rect) const
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
