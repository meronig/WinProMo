/* ==========================================================================
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
#include "ProMoBlockView.h"
#include "ProMoNameFactory.h"
#include "../DiagramEditor/Tokenizer.h"
#include "ProMoEdgeView.h"
#include "ProMoEdgeModel.h"

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

	SetConstraints(CSize(128, 32), CSize(-1, -1));
	SetType(_T("promo_block_view"));

	CString title;
	BOOL result;
	result = title.LoadString(IDS_PROMO_BLOCK);
	if (result) {
		SetTitle(title);
	}
	this->m_target = FALSE;

	SetPropertyDialog(&m_dlg, CPropertyDialog::IDD);

	SetName(CProMoNameFactory::GetID());

	m_blockmodel = NULL;
	setModel(new CProMoBlockModel());
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

	if (m_dlg.m_hWnd)
		m_dlg.DestroyWindow();

	setModel(NULL);

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
	
	if (this->getModel()->GetSubBlocks()->GetSize() == 0) {
		dc->DrawText(str, rect, DT_NOPREFIX | DT_SINGLELINE | DT_VCENTER | DT_CENTER);
	}
	else {
		dc->DrawText(str, rect, DT_NOPREFIX | DT_SINGLELINE | DT_TOP | DT_CENTER);
	}
	dc->SelectStockObject(DEFAULT_GUI_FONT);
	dc->SetBkMode(mode);
}

void CProMoBlockView::Highlight(CDC* dc, CRect rect) {
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

BOOL CProMoBlockView::IsTarget()
{
	return m_target;
}

void CProMoBlockView::SetTarget(BOOL isTarget)
{
	m_target = isTarget;
}

CPoint CProMoBlockView::getIntersection(CPoint innerPoint, CPoint outerPoint)
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
			result.x = static_cast<LONG>(t * xY + (1 - t) * xX);
			result.y = static_cast<LONG>(t * yY + (1 - t) * yX);

			/* uncomment for debugging */
			/*msg.Format(_T("intersection: (%d, %d)"), result.x, result.y);
			AfxMessageBox(msg);*/

			return result;
		}
	}

	return CPoint(-1,-1);
}


void CProMoBlockView::recomputeIntersectionLinks() {
	ASSERT_VALID(this->getModel());
	CProMoBlockModel* model = this->getModel();
	//recompute intersection for edges
	int i = 0;
	
	for (i = 0; i < model->GetIncomingEdges()->GetSize(); i++) {
		CProMoEdgeModel* edgeModel = dynamic_cast<CProMoEdgeModel*>(model->GetIncomingEdges()->GetAt(i));
		if (edgeModel) {
			CProMoEdgeView* edgeView = edgeModel->GetLastSegment();
			//destination: bottomright
			CPoint pt = getIntersection(edgeView->GetRect().BottomRight(), edgeView->GetRect().TopLeft());
			if (pt.x >= 0) {
				edgeView->SetBottom(pt.y);
				edgeView->SetRight(pt.x);
			}
		}

	}

	for (i = 0; i < model->GetOutgoingEdges()->GetSize(); i++) {
		CProMoEdgeModel* edgeModel = dynamic_cast<CProMoEdgeModel*>(model->GetOutgoingEdges()->GetAt(i));
		if (edgeModel) {
			CProMoEdgeView* edgeView = edgeModel->GetFirstSegment();
			//destination: topleft
			CPoint pt = getIntersection(edgeView->GetRect().TopLeft(), edgeView->GetRect().BottomRight());
			if (pt.x >= 0) {
				edgeView->SetTop(pt.y);
				edgeView->SetLeft(pt.x);
			}
		}
	}
	
	//recompute intersection for sub-blocks
	for (i = 0; i < model->GetSubBlocks()->GetSize(); i++) {
		CProMoBlockModel* childModel = dynamic_cast<CProMoBlockModel*>(model->GetSubBlocks()->GetAt(i));
		if (childModel) {
			CProMoBlockView* childView = dynamic_cast<CProMoBlockView*>(childModel->GetMainView());
			if (childView) {
				childView->recomputeIntersectionLinks();
			}
		}
	}

}

CProMoBlockModel* CProMoBlockView::getModel() const
{
	return m_blockmodel;
}

void CProMoBlockView::setModel(CProMoBlockModel* model)
{
	if (m_blockmodel != model) {
		CProMoBlockModel* oldModel = m_blockmodel;
		m_blockmodel = model;

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

void CProMoBlockView::autoResize()
{
	ASSERT_VALID(this->getModel());
	CProMoBlockModel* model = this->getModel();
	for (int i = 0; i < model->GetSubBlocks()->GetSize(); i++) {
		CProMoBlockModel* childModel = dynamic_cast<CProMoBlockModel*>(model->GetSubBlocks()->GetAt(i));
		if (childModel) {
			CProMoBlockView* childView = dynamic_cast<CProMoBlockView*>(childModel->GetMainView());
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
	
	if (model->GetParentBlock() != NULL) {
		if (model->GetParentBlock()->GetMainView() != NULL) {
			model->GetParentBlock()->GetMainView()->autoResize();
		}
	}
	else {
		this->recomputeIntersectionLinks();
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

	str.Format(_T("%s:%s,%f,%f,%f,%f,%s,%i,%s"), (LPCTSTR)GetType(), (LPCTSTR)name, GetLeft(), GetTop(), GetRight(), GetBottom(), (LPCTSTR)title, GetGroup(), (LPCTSTR)model);
	
	return str;

}

BOOL CProMoBlockView::GetDefaultFromString(CString& str)
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
	obj->setModel(new CProMoBlockModel());
	obj->SetName(CProMoNameFactory::GetID());
	return obj;

}

void CProMoBlockView::SetRect(double left, double top, double right, double bottom)
{
	ASSERT_VALID(this->getModel());
	CProMoBlockModel* model = this->getModel();
	//note: reposition links
	int i = 0;

	for (i = 0; i < model->GetIncomingEdges()->GetSize(); i++) {
		double newRight = 0;
		double newBottom = 0;
		CProMoEdgeModel* edgeModel = dynamic_cast<CProMoEdgeModel*>(model->GetIncomingEdges()->GetAt(i));
		if (edgeModel) {
			CProMoEdgeView* edgeView = edgeModel->GetLastSegment();
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

	for (i = 0; i < model->GetOutgoingEdges()->GetSize(); i++) {
		double newTop = 0;
		double newLeft = 0;
		CProMoEdgeModel* edgeModel = dynamic_cast<CProMoEdgeModel*>(model->GetOutgoingEdges()->GetAt(i));
		if (edgeModel) {
			CProMoEdgeView* edgeView = edgeModel->GetFirstSegment();
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

		for (i = 0; i < model->GetSubBlocks()->GetSize(); i++) {
			CProMoBlockModel* childModel = dynamic_cast<CProMoBlockModel*>(model->GetSubBlocks()->GetAt(i));
			if (childModel) {
				CProMoBlockView* childView = dynamic_cast<CProMoBlockView*>(childModel->GetMainView());
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

int CProMoBlockView::GetHitCode(CPoint point) const
/* ============================================================
	Function :		CProMoBlockView::GetHitCode
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

HCURSOR CProMoBlockView::GetCursor(int /*hit*/) const
/* ============================================================
	Function :		CProMoBlockView::GetCursor
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


