#include "ProcessEntityBlock.h"
#include "LinkFactory.h"
#include "../stdafx.h"
#include "../DiagramEditor/Tokenizer.h"
#include "ProcessLineEdge.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

CProcessEntityBlock::CProcessEntityBlock()
/* ============================================================
	Function :		CProcessEntityBlock::CProcessEntityBlock
	Description :	constructor

	Return :		void
	Parameters :	none

	Usage :

   ============================================================*/
{

	SetConstraints(CSize(128, 32), CSize(-1, -1));
	SetType(_T("process_block"));

	CString title;
	title.LoadString(IDS_PROCESS_BLOCK);
	SetTitle(title);
	this->parentBlock = NULL;
	this->m_target = false;

	SetPropertyDialog(&m_dlg, CPropertyDialog::IDD);

	SetName(CLinkFactory::GetID());

	SetMoved(FALSE);


}

CProcessEntityBlock::~CProcessEntityBlock()
/* ============================================================
	Function :		CProcessEntityBlock::~CProcessEntityBlock
	Description :	destructor

	Return :		void
	Parameters :	none

	Usage :

   ============================================================*/
{

	for (int i = 0; i < m_incomingEdges.GetSize(); i++) {
		CProcessLineEdge* edge = dynamic_cast<CProcessLineEdge*>(this->m_incomingEdges.GetAt(i));
		if (edge) {
			edge->SetDestination(NULL);
		}
	}
	for (int i = 0; i < m_outgoingEdges.GetSize(); i++) {
		CProcessLineEdge* edge = dynamic_cast<CProcessLineEdge*>(this->m_outgoingEdges.GetAt(i));
		if (edge) {
			edge->SetSource(NULL);
		}
	}

	if (m_dlg.m_hWnd)
		m_dlg.DestroyWindow();

}

void CProcessEntityBlock::Draw(CDC* dc, CRect rect)
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
	font.CreateFont(-round(12.0 * GetZoom()), 0, 0, 0, FW_NORMAL, 0, 0, 0, 0, 0, 0, 0, 0, _T("Courier New"));
	dc->SelectObject(&font);
	int mode = dc->SetBkMode(TRANSPARENT);
	if (this->m_subblocks.IsEmpty()) {
		dc->DrawText(GetTitle(), rect, DT_NOPREFIX | DT_SINGLELINE | DT_VCENTER | DT_CENTER);
	}
	else {
		dc->DrawText(GetTitle(), rect, DT_NOPREFIX | DT_SINGLELINE | DT_TOP | DT_CENTER);
	}
	dc->SelectStockObject(DEFAULT_GUI_FONT);
	dc->SetBkMode(mode);
}

void CProcessEntityBlock::Highlight(CDC* dc, CRect rect) {
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

bool CProcessEntityBlock::IsTarget()
{
	return m_target;
}

void CProcessEntityBlock::SetTarget(BOOL isTarget)
{
	m_target = isTarget;
}

CPoint CProcessEntityBlock::getIntersection(CPoint innerPoint, CPoint outerPoint)
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

	/* uncomment for debugging */
	/*CString msg;
	msg.Format(_T("inner point: (%f, %f)"), xX, yX);
	AfxMessageBox(msg);
	msg.Format(_T("outer point: (%f, %f)"), xY, yY);
	AfxMessageBox(msg);
	msg.Format(_T("box: (%f, %f, %f, %f)"), xA, yA, xC, yC);
	AfxMessageBox(msg);*/


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

void CProcessEntityBlock::linkSubBlock(CProcessEntityBlock* subblock)
{
	if (subblock->contains(this, true)) {
		//ASSERT(false);
		//better to throw an exception
		return;
	}

	m_subblocks.Add(subblock);

	if (subblock->parentBlock != NULL) {
		subblock->parentBlock->unlinkSubBlock(subblock);
	}
	subblock->parentBlock = this;
}

void CProcessEntityBlock::unlinkSubBlock(CProcessEntityBlock* subblock)
{
	for (int i = 0; i < m_subblocks.GetSize(); i++) {
		if (m_subblocks.GetAt(i) == subblock) {
			m_subblocks.RemoveAt(i);
			subblock->parentBlock = NULL;
		}
	}
}

void CProcessEntityBlock::unlinkSubBlocks()
{
	for (int i = 0; i < m_subblocks.GetSize(); i++) {
		CProcessEntityBlock* child = dynamic_cast<CProcessEntityBlock*>(this->m_subblocks.GetAt(i));
		if (child) {
			child->parentBlock = NULL;
		}
	}
	this->m_subblocks.RemoveAll();
}

CObArray* CProcessEntityBlock::getSubBlocks()
{
	return &m_subblocks;
}

void CProcessEntityBlock::setParentBlock(CProcessEntityBlock* parent)
{
	if (parent != NULL) {
		parent->linkSubBlock(this);
	}
	else {
		if (this->parentBlock != NULL) {
			this->parentBlock->unlinkSubBlock(this);
		}
		this->parentBlock = NULL;
	}
}

CProcessEntityBlock* CProcessEntityBlock::getParentBlock() const
{
	return this->parentBlock;
}

bool CProcessEntityBlock::contains(CProcessEntityBlock* block, bool recursive) {
	bool contains = false;
	/*if (this == block) {
		contains = true;
	}
	*/
	for (int i = 0; i < m_subblocks.GetSize(); i++) {
		
		CProcessEntityBlock* child = dynamic_cast<CProcessEntityBlock*>(this->m_subblocks.GetAt(i));
		if (child) {
			if (child == block) {
				contains = true;
			}
			if (recursive) {
				if (child->contains(block,true)) {
					contains = true;
				}
			}
		}
		
	}
	return contains;
}

void CProcessEntityBlock::linkOutgoingEdge(CProcessLineEdge* edge)
{
	edge->SetSource(this);
}

void CProcessEntityBlock::unlinkOutgoingEdge(CProcessLineEdge* edge)
{
	if (edge->GetSource() == this) {
		edge->SetSource(NULL);
	}
}

void CProcessEntityBlock::unlinkOutgoingEdges()
{
	for (int i = 0; i < m_outgoingEdges.GetSize(); i++) {
		CProcessLineEdge* edge = dynamic_cast<CProcessLineEdge*>(m_outgoingEdges.GetAt(i));
		if (edge) {
			edge->SetSource(NULL);
		}
	}
}

CObArray* CProcessEntityBlock::getOutgoingEdges()
{
	return &m_outgoingEdges;
}

void CProcessEntityBlock::linkIncomingEdge(CProcessLineEdge* edge)
{
	edge->SetDestination(this);
}

void CProcessEntityBlock::unlinkIncomingEdge(CProcessLineEdge* edge)
{
	if (edge->GetDestination() == this) {
		edge->SetDestination(NULL);
	}
}

void CProcessEntityBlock::unlinkIncomingEdges()
{
	for (int i = 0; i < m_incomingEdges.GetSize(); i++) {
		CProcessLineEdge* edge = dynamic_cast<CProcessLineEdge*>(m_incomingEdges.GetAt(i));
		if (edge) {
			edge->SetDestination(NULL);
		}
	}
}


CObArray* CProcessEntityBlock::getIncomingEdges()
{
	return &m_incomingEdges;
}

void CProcessEntityBlock::recomputeIntersectionLinks() {
	//recompute intersection for edges
	for (int i = 0; i < m_incomingEdges.GetSize(); i++) {
		CProcessLineEdge* edge = dynamic_cast<CProcessLineEdge*>(this->m_incomingEdges.GetAt(i));
		if (edge) {
			//destination: bottomright
			CPoint pt = getIntersection(edge->GetRect().BottomRight(), edge->GetRect().TopLeft());
			if (pt.x >= 0) {
				edge->SetBottom(pt.y);
				edge->SetRight(pt.x);
			}
		}

	}

	for (int i = 0; i < m_outgoingEdges.GetSize(); i++) {
		CProcessLineEdge* edge = dynamic_cast<CProcessLineEdge*>(this->m_outgoingEdges.GetAt(i));
		if (edge) {
			//destination: topleft
			CPoint pt = getIntersection(edge->GetRect().TopLeft(), edge->GetRect().BottomRight());
			if (pt.x >= 0) {
				edge->SetTop(pt.y);
				edge->SetLeft(pt.x);
			}
		}
	}

	for (int i = 0; i < this->m_subblocks.GetSize(); i++) {
		CProcessEntityBlock* child = dynamic_cast<CProcessEntityBlock*>(this->m_subblocks.GetAt(i));
		if (child) {
			child->recomputeIntersectionLinks();
		}
	}

}

void CProcessEntityBlock::autoResize()
{
	for (int i = 0; i < this->m_subblocks.GetSize(); i++) {
		CProcessEntityBlock* child = dynamic_cast<CProcessEntityBlock*>(this->m_subblocks.GetAt(i));
		
		if (child) {
			if (child->GetBottom() > this->GetBottom()) {
				this->SetRect(GetLeft(), GetTop(), GetRight(), child->GetBottom() + 5);
			}
			if (child->GetRight() > this->GetRight()) {
				this->SetRect(GetLeft(), GetTop(), child->GetRight() + 5, GetBottom());
			}
			if (child->GetTop() < this->GetTop()) {
				this->SetRect(GetLeft(), child->GetTop() - 5, GetRight(), GetBottom());
			}
			if (child->GetLeft() < this->GetLeft()) {
				this->SetRect(child->GetLeft() - 5, GetTop(), GetRight(), GetBottom());
			}
		}
	}
	
	if (this->parentBlock != NULL) {
		this->parentBlock->autoResize();
	}
	else {
		this->recomputeIntersectionLinks();
	}
}

CString CProcessEntityBlock::GetDefaultGetString() const
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

	CString parentString = _T("");

	CProcessEntityBlock* parent = getParentBlock();

	if (parent) {
		parentString = parent->GetName();
		parentString.Replace(_T(":"), _T("\\colon"));
		parentString.Replace(_T(";"), _T("\\semicolon"));
		parentString.Replace(_T(","), _T("\\comma"));
		parentString.Replace(_T("\r\n"), _T("\\newline"));
	}

	str.Format(_T("%s:%f,%f,%f,%f,%s,%s,%i,%s"), GetType(), GetLeft(), GetTop(), GetRight(), GetBottom(), title, name, GetGroup(), parentString);

	return str;

}

CDiagramEntity* CProcessEntityBlock::Clone()
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
	CProcessEntityBlock* obj = new CProcessEntityBlock;
	obj->Copy(this);
	obj->parentBlock = NULL;
	obj->m_subblocks.RemoveAll();
	return obj;

}

void CProcessEntityBlock::MoveRect(double x, double y) {

	/*CRect r = GetRect();

	double x = r.left;
	double y = r.top;*/

	for (int i = 0; i < m_subblocks.GetCount(); i++) {
		CProcessEntityBlock* child = dynamic_cast<CProcessEntityBlock*>(m_subblocks.GetAt(i));
		//move child nodes that are not selected (otherwise they will be moved twice)
		if (!child->IsSelected()) {
			/* test */
			//child->MoveRect(x, y);
		}
	}
	
	CDiagramEntity::MoveRect(x, y);
	

	//need to move connecting points for linked edges

	//note: may be handled by resize operations
	
	//for (int i = 0; i < m_incomingEdges.GetCount(); i++) {
	//	CProcessLineEdge* edge = dynamic_cast<CProcessLineEdge*>(m_incomingEdges.GetAt(i));
	//	if (edge) {
	//		//destination: bottomright
	//		edge->SetBottom(edge->GetBottom() + y);
	//		edge->SetRight(edge->GetRight() + x);
	//	}
	//}
	//
	//for (int i = 0; i < m_outgoingEdges.GetCount(); i++) {
	//	CProcessLineEdge* edge = dynamic_cast<CProcessLineEdge*>(m_outgoingEdges.GetAt(i));
	//	if (edge) {
	//		//source: topleft
	//		edge->SetTop(edge->GetTop() + y);
	//		edge->SetLeft(edge->GetLeft() + x);
	//	}
	//}

	//note: in some cases, there may be an intersection, so recompute the intersection
}

void CProcessEntityBlock::SetRect(double left, double top, double right, double bottom)
{
	//note: reposition links
	for (int i = 0; i < m_incomingEdges.GetSize(); i++) {
		double newRight = 0;
		double newBottom = 0;
		CProcessLineEdge* edge = dynamic_cast<CProcessLineEdge*>(this->m_incomingEdges.GetAt(i));
		if (edge) {
			//destination: bottomright
			if (!edge->IsSelected()) {
				if (GetBottom() - 1 < edge->GetBottom() && edge->GetBottom() < GetBottom() + 1) {
					newBottom = bottom;
					if (GetRight() - 1 >= edge->GetRight() && edge->GetRight() >= GetLeft() + 1) {
						newRight = edge->GetRight() + right - GetRight();
					}
				}
				if (GetTop() - 1 < edge->GetBottom() && edge->GetBottom() < GetTop() + 1) {
					newBottom = top;
					if (GetRight() - 1 >= edge->GetRight() && edge->GetRight() >= GetLeft() + 1) {
						newRight = edge->GetRight() + right - GetRight();
					}
				}
				if (GetRight() - 1 < edge->GetRight() && edge->GetRight() < GetRight() + 1) {
					newRight = right;
					if (GetBottom() - 1 >= edge->GetBottom() || edge->GetBottom() >= GetTop() + 1) {
						newBottom = edge->GetBottom() + bottom - GetBottom();
					}
				}
				if (GetLeft() - 1 < edge->GetRight() && edge->GetRight() < GetLeft() + 1) {
					newRight = left;
					if (GetBottom() - 1 >= edge->GetBottom() || edge->GetBottom() >= GetTop() + 1) {
						newBottom = edge->GetBottom() + bottom - GetBottom();
					}
				}
				edge->SetBottom(newBottom);
				edge->SetRight(newRight);
			}
		}

	}

	for (int i = 0; i < m_outgoingEdges.GetSize(); i++) {
		double newTop = 0;
		double newLeft = 0;
		CProcessLineEdge* edge = dynamic_cast<CProcessLineEdge*>(this->m_outgoingEdges.GetAt(i));
		if (edge) {
			if (!edge->IsSelected()) {
				//destination: topleft
				if (GetBottom() - 1 < edge->GetTop() && edge->GetTop() < GetBottom() + 1) {
					newTop = bottom;
					if (GetRight() - 1 >= edge->GetLeft() && edge->GetLeft() >= GetLeft() + 1) {
						newLeft = edge->GetLeft() + right - GetRight();
					}
				}
				if (GetTop() - 1 < edge->GetTop() && edge->GetTop() < GetTop() + 1) {
					newTop = top;
					if (GetRight() - 1 >= edge->GetLeft() && edge->GetLeft() >= GetLeft() + 1) {
						newLeft = edge->GetLeft() + right - GetRight();
					}
				}
				if (GetRight() - 1 < edge->GetLeft() && edge->GetLeft() < GetRight() + 1) {
					newLeft = right;
					if (GetBottom() - 1 >= edge->GetTop() || edge->GetTop() >= GetTop() + 1) {
						newTop = edge->GetTop() + bottom - GetBottom();
					}
				}
				if (GetLeft() - 1 < edge->GetLeft() && edge->GetLeft() < GetLeft() + 1) {
					newLeft = left;
					if (GetBottom() - 1 >= edge->GetTop() || edge->GetTop() >= GetTop() + 1) {
						newTop = edge->GetTop() + bottom - GetBottom();
					}
				}
				edge->SetTop(newTop);
				edge->SetLeft(newLeft);
			}
		}

	}
	
	/* new */
	double deltaY = GetTop() - top;
	double deltaX = GetLeft() - left;

	if (deltaX != 0 || deltaY != 0) {

		for (int i = 0; i < m_subblocks.GetCount(); i++) {
			CProcessEntityBlock* child = dynamic_cast<CProcessEntityBlock*>(m_subblocks.GetAt(i));
			//move child nodes that are not selected (otherwise they will be moved twice)
			if (!child->IsSelected()) {
				child->SetRect(child->GetLeft() - deltaX, child->GetTop() - deltaY, child->GetRight() - deltaX, child->GetBottom() - deltaY);
			}
		}
	}

	CDiagramEntity::SetRect(left, top, right, bottom);


}

CDiagramEntity* CProcessEntityBlock::CreateFromString(const CString& str)
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

	CProcessEntityBlock* obj = new CProcessEntityBlock;
	if (!obj->FromString(str))
	{
		delete obj;
		obj = NULL;
	}

	return obj;

}

int CProcessEntityBlock::GetHitCode(CPoint point) const
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

HCURSOR CProcessEntityBlock::GetCursor(int /*hit*/) const
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


void CProcessEntityBlock::SetMoved(BOOL moved)
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

BOOL CProcessEntityBlock::GetMoved()
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


