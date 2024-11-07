#include "ProcessLineEdge.h"
#include "LinkFactory.h"
#include "../stdafx.h"

CProcessLineEdge::CProcessLineEdge()
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
	SetType(_T("process_edge"));
	SetTitle(_T(""));

	SetPropertyDialog(&m_dlg, CPropertyDialog::IDD);

	SetName(CLinkFactory::GetID());

	m_source = NULL;
	m_dest = NULL;
}

CProcessLineEdge::~CProcessLineEdge()
/* ============================================================
	Function :		CProcessLineEdge::~CProcessLineEdge
	Description :	Destructor
	Access :		Public

	Return :		void
	Parameters :	none

	Usage :

   ============================================================*/
{
	CProcessLineEdge* edge = dynamic_cast<CProcessLineEdge*>(m_source);
	if (edge) {
		edge->SetBottom(GetBottom());
		edge->SetRight(GetRight());
		edge->SetDestination(GetDestination());
	}
	
	
	edge = dynamic_cast<CProcessLineEdge*>(m_dest);
	if (edge) {
		edge->SetTop(GetTop());
		edge->SetLeft(GetLeft());
		edge->SetSource(GetSource());
	}
	
	
	SetSource(NULL);
	SetDestination(NULL);

	if (m_dlg.m_hWnd)
		m_dlg.DestroyWindow();

}

CDiagramEntity* CProcessLineEdge::Clone()
/* ============================================================
	Function :		CProcessLineEdge::Clone
	Description :	Clone this object to a new object.

	Return :		CDiagramEntity*	-	The new object.
	Parameters :	none

	Usage :			Call to create a clone of the object. The
					caller will have to delete the object.

   ============================================================*/

{

	CProcessLineEdge* obj = new CProcessLineEdge;
	obj->Copy(this);
	obj->m_source = NULL;
	obj->m_dest = NULL;
	return obj;
}

void DrawArrow(CDC* dc, POINT p0, POINT p1, int head_length, int head_width) {
	
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

void CProcessLineEdge::Draw(CDC* dc, CRect rect)
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
	CProcessLineEdge* dest = dynamic_cast<CProcessLineEdge*>(m_dest);
	if (!dest) {
		DrawArrow(dc, rect.TopLeft(), rect.BottomRight(), 10, 10);
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

int CProcessLineEdge::GetHitCode(const CPoint& point, const CRect& rect) const
{
	CRect rectTest = GetSelectionMarkerRect(DEHT_CENTER, rect);
	if (rectTest.PtInRect(point)) {
		return DEHT_CENTER;
	}
	return CDiagramLine::GetHitCode(point, rect);
}

HCURSOR CProcessLineEdge::GetCursor(int hit) const
{
	if (hit == DEHT_CENTER) {
		return LoadCursor(NULL, IDC_SIZEALL);
	}
	return CDiagramLine::GetCursor(hit);
}

bool CProcessLineEdge::canConnectSource(CDiagramEntity* source)
{
	CProcessEntityBlock* obj = dynamic_cast<CProcessEntityBlock*>(source);
	if (obj) {
		return true;
	}
	return false;
}

bool CProcessLineEdge::canConnectDestination(CDiagramEntity* destination)
{
	CProcessEntityBlock* obj = dynamic_cast<CProcessEntityBlock*>(destination);
	if (obj) {
		return true;
	}
	return false;
}


CDiagramEntity* CProcessLineEdge::CreateFromString(const CString& str)
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

	CProcessLineEdge* obj = new CProcessLineEdge;
	if (!obj->FromString(str))
	{
		delete obj;
		obj = NULL;
	}

	return obj;

}

void CProcessLineEdge::SetSource(CDiagramEntity *source)
{

	if (m_source != source) {

		//set the new source	
		CDiagramEntity* oldSource = m_source;
		m_source = source;

		if (oldSource) {
			//if a previous source block exists, remove the reference from the old source block
			CProcessEntityBlock* obj = dynamic_cast<CProcessEntityBlock*>(oldSource);
			if (obj) {
				for (int i = 0; i < obj->m_outgoingEdges.GetSize(); i++) {
					if (obj->m_outgoingEdges.GetAt(i) == this) {
						obj->m_outgoingEdges.RemoveAt(i);
					}
				}
			}
			//if a previous source edge exists, remove the reference from the old source edge
			CProcessLineEdge* edge = dynamic_cast<CProcessLineEdge*>(oldSource);
			if (edge) {
				//edge->SetDestination(NULL);
				edge->m_dest = NULL;
			}
		}

		if (source) {
			//if the new source block exists, add a reference to the new source block
			CProcessEntityBlock* obj = dynamic_cast<CProcessEntityBlock*>(source);
			if (obj) {
				obj->m_outgoingEdges.Add(this);
			}
			//if the new source edge exists, add a reference to the new source edge
			CProcessLineEdge* edge = dynamic_cast<CProcessLineEdge*>(m_source);
			if (edge) {
				edge->SetDestination(this);
				//edge->m_dest = this;
			}
		}
	}
	//new
	if (m_source != NULL) {
		CProcessEntityBlock* obj = dynamic_cast<CProcessEntityBlock*>(m_source);
		if (obj) {
			CPoint pt = obj->getIntersection(GetRect().TopLeft(), GetRect().BottomRight());
			if (pt.x >= 0) {
				SetTop(pt.y);
				SetLeft(pt.x);
			}
		}
		CProcessLineEdge* edge = dynamic_cast<CProcessLineEdge*>(m_source);
		if (edge) {
			SetTop(edge->GetBottom());
			SetLeft(edge->GetRight());
		}
	}
	if (m_dest != NULL) {
		CProcessEntityBlock* obj = dynamic_cast<CProcessEntityBlock*>(m_dest);
		if (obj) {
			CPoint pt = obj->getIntersection(GetRect().BottomRight(), GetRect().TopLeft());
			if (pt.x >= 0) {
				SetBottom(pt.y);
				SetRight(pt.x);
			}
		}
		CProcessLineEdge* edge = dynamic_cast<CProcessLineEdge*>(m_dest);
		if (edge) {
			SetBottom(edge->GetTop());
			SetRight(edge->GetLeft());
		}
	}
}

void CProcessLineEdge::SetDestination(CDiagramEntity *destination)
{
	if (m_dest != destination) {

		//set the new destination	
		CDiagramEntity *oldDest = m_dest;
		m_dest = destination;

		if (oldDest) {
			//if a previous destination block exists, remove the reference from the old destination block
			CProcessEntityBlock* obj = dynamic_cast<CProcessEntityBlock*>(oldDest);
			if (obj) {
				for (int i = 0; i < obj->m_incomingEdges.GetSize(); i++) {
					if (obj->m_incomingEdges.GetAt(i) == this) {
						obj->m_incomingEdges.RemoveAt(i);
					}
				}
			}
			//if a previous destination edge exists, remove the reference from the old destination edge
			CProcessLineEdge* edge = dynamic_cast<CProcessLineEdge*>(oldDest);
			if (edge) {
				edge->m_source = NULL;
				//edge->SetSource(NULL);
			}
		}

		
		if (destination) {
			//if the new destination block exists, add a reference to the new destination block
			CProcessEntityBlock* obj = dynamic_cast<CProcessEntityBlock*>(destination);
			if (obj) {
				obj->m_incomingEdges.Add(this);
			}
			//if a previous destination edge exists, remove the reference from the old destination edge
			CProcessLineEdge* edge = dynamic_cast<CProcessLineEdge*>(m_dest);
			if (edge) {
				//edge->m_source = this;
				edge->SetSource(this);
			}
		}
	}
	//new
	if (m_source != NULL) {
		CProcessEntityBlock* obj = dynamic_cast<CProcessEntityBlock*>(m_source);
		if (obj) {
			CPoint pt = obj->getIntersection(GetRect().TopLeft(), GetRect().BottomRight());
			if (pt.x >= 0) {
				SetTop(pt.y);
				SetLeft(pt.x);
			}
		}
		CProcessLineEdge* edge = dynamic_cast<CProcessLineEdge*>(m_source);
		if (edge) {
			SetTop(edge->GetBottom());
			SetLeft(edge->GetRight());
		}
	}
	if (m_dest != NULL) {
		CProcessEntityBlock* obj = dynamic_cast<CProcessEntityBlock*>(m_dest);
		if (obj) {
			CPoint pt = obj->getIntersection(GetRect().BottomRight(), GetRect().TopLeft());
			if (pt.x >= 0) {
				SetBottom(pt.y);
				SetRight(pt.x);
			}
		}
		CProcessLineEdge* edge = dynamic_cast<CProcessLineEdge*>(m_dest);
		if (edge) {
			SetBottom(edge->GetTop());
			SetRight(edge->GetLeft());
		}
	}
}

CDiagramEntity* CProcessLineEdge::GetSource() const
{
	return m_source;
}

CDiagramEntity* CProcessLineEdge::GetDestination() const
{
	return m_dest;
}

CString CProcessLineEdge::GetDefaultGetString() const
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

	CString str;

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

	str.Format(_T("%s:%f,%f,%f,%f,%s,%s,%i,%s,%s"), GetType(), GetLeft(), GetTop(), GetRight(), GetBottom(), title, name, GetGroup(), sourceString, destString);

	return str;

}

void CProcessLineEdge::DrawSelectionMarkers(CDC* dc, CRect rect) const
{
	CRect rectSelect;

	dc->SelectStockObject(BLACK_BRUSH);
	rectSelect = GetSelectionMarkerRect(DEHT_CENTER, rect);
	dc->Rectangle(rectSelect);

	CDiagramLine::DrawSelectionMarkers(dc, rect);
}

CRect CProcessLineEdge::GetSelectionMarkerRect(UINT marker, CRect rect) const
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
