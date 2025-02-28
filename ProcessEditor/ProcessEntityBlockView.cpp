#include "ProcessEntityBlockView.h"
#include "LinkFactory.h"
#include "../stdafx.h"
#include "../DiagramEditor/Tokenizer.h"
#include "ProcessLineEdgeView.h"
#include "ProcessLineEdgeModel.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

CProcessEntityBlockView::CProcessEntityBlockView()
/* ============================================================
	Function :		CProcessEntityBlock::CProcessEntityBlock
	Description :	constructor

	Return :		void
	Parameters :	none

	Usage :

   ============================================================*/
{

	SetConstraints(CSize(128, 32), CSize(-1, -1));
	SetType(_T("process_block_view"));

	CString title;
	title.LoadString(IDS_PROCESS_BLOCK);
	SetTitle(title);
	this->m_target = false;

	SetPropertyDialog(&m_dlg, CPropertyDialog::IDD);

	SetName(CLinkFactory::GetID());

	SetMoved(FALSE);

	m_blockmodel = NULL;
	setModel(new CProcessEntityBlockModel());
}

CProcessEntityBlockView::~CProcessEntityBlockView()
/* ============================================================
	Function :		CProcessEntityBlock::~CProcessEntityBlock
	Description :	destructor

	Return :		void
	Parameters :	none

	Usage :

   ============================================================*/
{

	if (m_dlg.m_hWnd)
		m_dlg.DestroyWindow();

	setModel(NULL);

}

void CProcessEntityBlockView::Draw(CDC* dc, CRect rect)
/* ============================================================
	Function :		CProcessEntityBlock::Draw
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
	ASSERT_VALID(this->getModel());

	dc->SelectStockObject(BLACK_PEN);
	dc->SelectStockObject(WHITE_BRUSH);

	CSize sz = GetMarkerSize();
	CPoint pt;
	pt.x = round((double)sz.cx * GetZoom());
	pt.y = round((double)sz.cy * GetZoom());

	if (IsTarget()) {
		CPen p;
		p.CreatePen(PS_SOLID, 3, RGB(255, 0, 0));
		CPen* pOldPen = dc->SelectObject(&p);
		dc->RoundRect(rect, pt);
	}
	else {
		dc->RoundRect(rect, pt);
	}

	CFont font;
	CString str;
	/* uncomment line below for debug */
	//str.Format(_T("%d,%d"), getModel()->getIncomingEdges()->GetSize(), getModel()->getOutgoingEdges()->GetSize());
	str = GetTitle();
	font.CreateFont(-round(12.0 * GetZoom()), 0, 0, 0, FW_NORMAL, 0, 0, 0, 0, 0, 0, 0, 0, _T("Courier New"));
	dc->SelectObject(&font);
	int mode = dc->SetBkMode(TRANSPARENT);
	
	if (this->getModel()->getSubBlocks()->IsEmpty()) {
		dc->DrawText(str, rect, DT_NOPREFIX | DT_SINGLELINE | DT_VCENTER | DT_CENTER);
	}
	else {
		dc->DrawText(str, rect, DT_NOPREFIX | DT_SINGLELINE | DT_TOP | DT_CENTER);
	}
	dc->SelectStockObject(DEFAULT_GUI_FONT);
	dc->SetBkMode(mode);
}

void CProcessEntityBlockView::Highlight(CDC* dc, CRect rect) {
	CPen p;
	p.CreatePen(PS_SOLID, 3, RGB(255, 0, 0));
	CPen *pOldPen = dc->SelectObject(&p);
	CSize sz = GetMarkerSize();
	CPoint pt;
	pt.x = round((double)sz.cx * GetZoom());
	pt.y = round((double)sz.cy * GetZoom());
	dc->RoundRect(rect, pt);
	dc->SelectObject(pOldPen);
}

bool CProcessEntityBlockView::IsTarget()
{
	return m_target;
}

void CProcessEntityBlockView::SetTarget(BOOL isTarget)
{
	m_target = isTarget;
}

CPoint CProcessEntityBlockView::getIntersection(CPoint innerPoint, CPoint outerPoint)
{
	CRect r = GetRect();
	
	double xA = r.left;
	double yA = r.top;
	double xC = r.right;
	double yC = r.bottom;
	double xX = innerPoint.x;
	double yX = innerPoint.y;
	double xY = outerPoint.x;
	double yY = outerPoint.y;
	
	double t = 0;

	if (innerPoint.x >= r.left && innerPoint.x <= r.right && innerPoint.y >= r.top && innerPoint.y <= r.bottom) {
		if (!(outerPoint.x >= r.left && outerPoint.x <= r.right && outerPoint.y >= r.top && outerPoint.y <= r.bottom)) {

			if (xY == xX) {
				t = max((yA - yX) / (yY - yX), (yC - yX) / (yY - yX));
			}
			else {
				if (yY == yX) {
					t = max((xA - xX) / (xY - xX), (xC - xX) / (xY - xX));
				}
				else {
					if (xY > xX) {
						if (yY > yX) {
							t = min((xC - xX) / (xY - xX), (yC - yX) / (yY - yX));
						}
						else {
							t = min((xC - xX) / (xY - xX), (yA - yX) / (yY - yX));
						}
					}
					else {
						if (yY > yX) {
							t = min((xA - xX) / (xY - xX), (yC - yX) / (yY - yX));
						}
						else {
							t = min((xA - xX) / (xY - xX), (yA - yX) / (yY - yX));
						}
					}
				}
			}
			
			CPoint result;

			result.x = t * xY + (1 - t) * xX;
			result.y = t * yY + (1 - t) * yX;

			/* uncomment for debugging */
			/*msg.Format(_T("intersection: (%d, %d)"), result.x, result.y);
			AfxMessageBox(msg);*/

			return result;
		}
	}

	return CPoint(-1,-1);
}


void CProcessEntityBlockView::recomputeIntersectionLinks() {
	ASSERT_VALID(this->getModel());
	CProcessEntityBlockModel* model = this->getModel();
	//recompute intersection for edges
	
	for (int i = 0; i < model->getIncomingEdges()->GetSize(); i++) {
		CProcessLineEdgeModel* edgeModel = dynamic_cast<CProcessLineEdgeModel*>(model->getIncomingEdges()->GetAt(i));
		if (edgeModel) {
			CProcessLineEdgeView* edgeView = edgeModel->getLastSegment();
			//destination: bottomright
			CPoint pt = getIntersection(edgeView->GetRect().BottomRight(), edgeView->GetRect().TopLeft());
			if (pt.x >= 0) {
				edgeView->SetBottom(pt.y);
				edgeView->SetRight(pt.x);
			}
		}

	}

	for (int i = 0; i < model->getOutgoingEdges()->GetSize(); i++) {
		CProcessLineEdgeModel* edgeModel = dynamic_cast<CProcessLineEdgeModel*>(model->getOutgoingEdges()->GetAt(i));
		if (edgeModel) {
			CProcessLineEdgeView* edgeView = edgeModel->getFirstSegment();
			//destination: topleft
			CPoint pt = getIntersection(edgeView->GetRect().TopLeft(), edgeView->GetRect().BottomRight());
			if (pt.x >= 0) {
				edgeView->SetTop(pt.y);
				edgeView->SetLeft(pt.x);
			}
		}
	}
	
	//recompute intersection for sub-blocks
	for (int i = 0; i < model->getSubBlocks()->GetSize(); i++) {
		CProcessEntityBlockModel* childModel = dynamic_cast<CProcessEntityBlockModel*>(model->getSubBlocks()->GetAt(i));
		if (childModel) {
			CProcessEntityBlockView* childView = dynamic_cast<CProcessEntityBlockView*>(childModel->getMainView());
			if (childView) {
				childView->recomputeIntersectionLinks();
			}
		}
	}

}

CProcessEntityBlockModel* CProcessEntityBlockView::getModel() const
{
	return m_blockmodel;
}

void CProcessEntityBlockView::setModel(CProcessEntityBlockModel* model)
{
	if (m_blockmodel != model) {
		CProcessEntityBlockModel* oldModel = m_blockmodel;
		m_blockmodel = model;

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

void CProcessEntityBlockView::autoResize()
{
	ASSERT_VALID(this->getModel());
	CProcessEntityBlockModel* model = this->getModel();
	for (int i = 0; i < model->getSubBlocks()->GetSize(); i++) {
		CProcessEntityBlockModel* childModel = dynamic_cast<CProcessEntityBlockModel*>(model->getSubBlocks()->GetAt(i));
		if (childModel) {
			CProcessEntityBlockView* childView = dynamic_cast<CProcessEntityBlockView*>(childModel->getMainView());
			if (childView) {
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
			}
		}
	}
	
	if (model->getParentBlock() != NULL) {
		if (model->getParentBlock()->getMainView() != NULL) {
			model->getParentBlock()->getMainView()->autoResize();
		}
	}
	else {
		this->recomputeIntersectionLinks();
	}
}

CString CProcessEntityBlockView::GetDefaultGetString() const
{
	/* ============================================================
	Function :		CProcessEntityBlock::GetDefaultString
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

	str.Format(_T("%s:%s,%f,%f,%f,%f,%s,%i,%s"), GetType(), name, GetLeft(), GetTop(), GetRight(), GetBottom(), title, GetGroup(), model);
	
	return str;

}

BOOL CProcessEntityBlockView::GetDefaultFromString(CString& str)
/* ============================================================
	Function :		CDiagramEntity::GetDefaultFromString
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

		SetRect(left, top, right, bottom);

		title.Replace(_T("\\colon"), _T(":"));
		title.Replace(_T("\\semicolon"), _T(";"));
		title.Replace(_T("\\comma"), _T(","));
		title.Replace(_T("\\newline"), _T("\r\n"));

		name.Replace(_T("\\colon"), _T(":"));
		name.Replace(_T("\\semicolon"), _T(";"));
		name.Replace(_T("\\comma"), _T(","));
		name.Replace(_T("\\newline"), _T("\r\n"));

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

CDiagramEntity* CProcessEntityBlockView::Clone()
/* ============================================================
	Function :		CProcessEntityBlock::Clone
	Description :	Clone this object to a new object.

	Return :		CDiagramEntity*	-	The new object.
	Parameters :	none

	Usage :			Call to create a clone of the object. The
					caller will have to delete the object.

   ============================================================*/
{

	//Hierarchy is not copied: if multiple blocks are selected, they become root nodes
	CProcessEntityBlockView* obj = new CProcessEntityBlockView;
	obj->Copy(this);
	obj->setModel(new CProcessEntityBlockModel());
	return obj;

}

void CProcessEntityBlockView::SetRect(double left, double top, double right, double bottom)
{
	ASSERT_VALID(this->getModel());
	CProcessEntityBlockModel* model = this->getModel();
	//note: reposition links
	

	for (int i = 0; i < model->getIncomingEdges()->GetSize(); i++) {
		double newRight = 0;
		double newBottom = 0;
		CProcessLineEdgeModel* edgeModel = dynamic_cast<CProcessLineEdgeModel*>(model->getIncomingEdges()->GetAt(i));
		if (edgeModel) {
			CProcessLineEdgeView* edgeView = edgeModel->getLastSegment();
			//destination: bottomright
			if (!edgeView->IsSelected()) {
				if (GetBottom() - 1 < edgeView->GetBottom() && edgeView->GetBottom() < GetBottom() + 1) {
					newBottom = bottom;
					if (GetRight() - 1 >= edgeView->GetRight() && edgeView->GetRight() >= GetLeft() + 1) {
						newRight = edgeView->GetRight() + right - GetRight();
					}
				}
				if (GetTop() - 1 < edgeView->GetBottom() && edgeView->GetBottom() < GetTop() + 1) {
					newBottom = top;
					if (GetRight() - 1 >= edgeView->GetRight() && edgeView->GetRight() >= GetLeft() + 1) {
						newRight = edgeView->GetRight() + right - GetRight();
					}
				}
				if (GetRight() - 1 < edgeView->GetRight() && edgeView->GetRight() < GetRight() + 1) {
					newRight = right;
					if (GetBottom() - 1 >= edgeView->GetBottom() || edgeView->GetBottom() >= GetTop() + 1) {
						newBottom = edgeView->GetBottom() + bottom - GetBottom();
					}
				}
				if (GetLeft() - 1 < edgeView->GetRight() && edgeView->GetRight() < GetLeft() + 1) {
					newRight = left;
					if (GetBottom() - 1 >= edgeView->GetBottom() || edgeView->GetBottom() >= GetTop() + 1) {
						newBottom = edgeView->GetBottom() + bottom - GetBottom();
					}
				}
				edgeView->SetBottom(newBottom);
				edgeView->SetRight(newRight);
			}
		}

	}

	for (int i = 0; i < model->getOutgoingEdges()->GetSize(); i++) {
		double newTop = 0;
		double newLeft = 0;
		CProcessLineEdgeModel* edgeModel = dynamic_cast<CProcessLineEdgeModel*>(model->getOutgoingEdges()->GetAt(i));
		if (edgeModel) {
			CProcessLineEdgeView* edgeView = edgeModel->getFirstSegment();
			if (!edgeView->IsSelected()) {
				//destination: topleft
				if (GetBottom() - 1 < edgeView->GetTop() && edgeView->GetTop() < GetBottom() + 1) {
					newTop = bottom;
					if (GetRight() - 1 >= edgeView->GetLeft() && edgeView->GetLeft() >= GetLeft() + 1) {
						newLeft = edgeView->GetLeft() + right - GetRight();
					}
				}
				if (GetTop() - 1 < edgeView->GetTop() && edgeView->GetTop() < GetTop() + 1) {
					newTop = top;
					if (GetRight() - 1 >= edgeView->GetLeft() && edgeView->GetLeft() >= GetLeft() + 1) {
						newLeft = edgeView->GetLeft() + right - GetRight();
					}
				}
				if (GetRight() - 1 < edgeView->GetLeft() && edgeView->GetLeft() < GetRight() + 1) {
					newLeft = right;
					if (GetBottom() - 1 >= edgeView->GetTop() || edgeView->GetTop() >= GetTop() + 1) {
						newTop = edgeView->GetTop() + bottom - GetBottom();
					}
				}
				if (GetLeft() - 1 < edgeView->GetLeft() && edgeView->GetLeft() < GetLeft() + 1) {
					newLeft = left;
					if (GetBottom() - 1 >= edgeView->GetTop() || edgeView->GetTop() >= GetTop() + 1) {
						newTop = edgeView->GetTop() + bottom - GetBottom();
					}
				}
				edgeView->SetTop(newTop);
				edgeView->SetLeft(newLeft);
			}
		}

	}
	
	double deltaY = GetTop() - top;
	double deltaX = GetLeft() - left;

	if (deltaX != 0 || deltaY != 0) {

		for (int i = 0; i < model->getSubBlocks()->GetCount(); i++) {
			CProcessEntityBlockModel* childModel = dynamic_cast<CProcessEntityBlockModel*>(model->getSubBlocks()->GetAt(i));
			if (childModel) {
				CProcessEntityBlockView* childView = dynamic_cast<CProcessEntityBlockView*>(childModel->getMainView());
				if (childView) {
					//move child nodes that are not selected (otherwise they will be moved twice)
					if (!childView->IsSelected()) {
						childView->SetRect(childView->GetLeft() - deltaX, childView->GetTop() - deltaY, childView->GetRight() - deltaX, childView->GetBottom() - deltaY);
					}
				}
			}
		}
	}

	CDiagramEntity::SetRect(left, top, right, bottom);


}

CDiagramEntity* CProcessEntityBlockView::CreateFromString(const CString& str)
/* ============================================================
	Function :		CProcessEntityBlock::CreateFromString
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

	CProcessEntityBlockView* obj = new CProcessEntityBlockView;
	if (!obj->FromString(str))
	{
		delete obj;
		obj = NULL;
	}

	return obj;

}

int CProcessEntityBlockView::GetHitCode(CPoint point) const
/* ============================================================
	Function :		CProcessEntityBlock::GetHitCode
	Description :	Returns the hit point constant for point.

	Return :		int				-	The hit point,
										DEHT_NONE if none.
	Parameters :	CPoint point	-	The point to check

	Usage :			Call to see in what part of the object point
					lies.

   ============================================================*/
{

	int result = DEHT_NONE;
	CRect rect = GetRect();

	if (rect.PtInRect(point))
		result = DEHT_BODY;

	return result;

}

HCURSOR CProcessEntityBlockView::GetCursor(int /*hit*/) const
/* ============================================================
	Function :		CProcessEntityBlock::GetCursor
	Description :	Returns the cursor for the given hit point.

	Return :		HCURSOR	-	The cursor to show
	Parameters :	int hit	-	The hit point constant (DEHT_)
								to get the cursor for.

	Usage :			Call to get the cursor for a specific hit
					point constant.

   ============================================================*/
{

	HCURSOR cursor = LoadCursor(NULL, IDC_SIZEALL);
	return cursor;

}


void CProcessEntityBlockView::SetMoved(BOOL moved)
/* ============================================================
	Function :		CProcessEntityBlock::SetMoved
	Description :	Sets the moved-flag of the object.

	Return :		void
	Parameters :	BOOL moved	-	TRUE if the object is moved
									while moving linked objects,
									FALSE if not.

	Usage :			To avoid infinite recursion while moving
					linked objects, we use a flag to mark this
					object as already moved.

   ============================================================*/
{

	m_moved = moved;

}

BOOL CProcessEntityBlockView::GetMoved()
/* ============================================================
	Function :		CProcessEntityBlock::GetMoved
	Description :	Gets the moved-flag of the object.

	Return :		BOOL	-	TRUE if the object is moved
									while moving linked objects,
									FALSE if not.

	Parameters :	none

	Usage :			To avoid infinite recursion while moving
					linked objects, we use a flag to mark this
					object as already moved.

   ============================================================*/
{

	return m_moved;

}


