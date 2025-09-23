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
#include "ProMoBlockView.h"
#include "ProMoNameFactory.h"
#include "../DiagramEditor/Tokenizer.h"
#include "ProMoEdgeView.h"
#include "ProMoEdgeModel.h"
#include "../resource.h"

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
	m_blockmodel = NULL;
	m_lockProportions = FALSE;
	m_fitTitle = FALSE;

	SetConstraints(CSize(128, 32), CSize(-1, -1));
	m_titleRect = CRect(CPoint(0,0),GetMinimumSize());
	SetType(_T("promo_block_view"));

	CString title;
	BOOL result;
	result = title.LoadString(IDS_PROMO_BLOCK);
	SetModel(new CProMoBlockModel());
	if (result) {
		SetTitle(title);
	}
	this->m_target = FALSE;

	SetName(CProMoNameFactory::GetID());

	
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
	ASSERT_VALID(this->GetModel());

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
	
	if (this->GetModel()->GetSubBlocks()->GetSize() == 0) {
		dc->DrawText(str, rect, DT_NOPREFIX | DT_SINGLELINE | DT_VCENTER | DT_CENTER);
	}
	else {
		dc->DrawText(str, rect, DT_NOPREFIX | DT_SINGLELINE | DT_TOP | DT_CENTER);
	}
	dc->SelectStockObject(DEFAULT_GUI_FONT);
	dc->SetBkMode(mode);
}



void CProMoBlockView::Highlight(CDC* dc, CRect rect) {
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
	return m_target;
}

void CProMoBlockView::SetTarget(BOOL isTarget)
/* ============================================================
	Function :		CProMoBlockView::SetTarget
	Description :	Makes the current block a target for the
					current drawing operation (e.g., when 
					dragging another object over it)
	Access :		Public

	Return :		void
	Parameters :	BOOL isTarget	-	"TRUE" if the block 
										should be the target

   ============================================================*/
{
	m_target = isTarget;
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

BOOL CProMoBlockView::HasLockedProportions()
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

void CProMoBlockView::SetFitTitle(BOOL hasFitTitle)
/* ============================================================
	Function :		CProMoBlockView::SetFitTitle
	Description :	Sets whether the block should fit the title
	Access :		Public

	Return :		void
	Parameters :	BOOL hasFitTitle	-	"TRUE" if the block
											must fit the title

   ============================================================*/
{
	m_fitTitle = hasFitTitle;
}

BOOL CProMoBlockView::HasFitTitle()
/* ============================================================
	Function :		CProMoBlockView::HasFitTitle
	Description :	Returns if the block must fit the title
	Access :		Public

	Return :		BOOL	-	"TRUE" if the block must fit the
								title
	Parameters :	none

   ============================================================*/
{
	return m_fitTitle;
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
					Override this method if the shape being
					drawn is changed, in order to compute the 
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
			result.x = (t * xY + (1 - t) * xX);
			result.y = (t * yY + (1 - t) * yX);

			/* uncomment for debugging */
			/*msg.Format(_T("intersection: (%d, %d)"), result.x, result.y);
			AfxMessageBox(msg);*/

			return result;
		}
	}

	return CPoint(-1,-1);
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
	if (m_fitTitle) {
		CFont font;
		double zoom = GetZoom();
		if (zoom == 0) {
			zoom = 1.0;
		}
		font.CreateFont(-round(12.0 * zoom), 0, 0, 0, FW_NORMAL, 0, 0, 0, 0, 0, 0, 0, 0, _T("Courier New"));
		m_titleRect = ComputeTextRect(title, font);

	}

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
	ASSERT_VALID(this->GetModel());
	CProMoBlockModel* model = this->GetModel();
	//note: reposition links
	int i = 0;

	for (i = 0; i < model->GetIncomingEdges()->GetSize(); i++) {
		CProMoEdgeModel* edgeModel = dynamic_cast<CProMoEdgeModel*>(model->GetIncomingEdges()->GetAt(i));
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

	for (i = 0; i < model->GetOutgoingEdges()->GetSize(); i++) {
		CProMoEdgeModel* edgeModel = dynamic_cast<CProMoEdgeModel*>(model->GetOutgoingEdges()->GetAt(i));
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

	if (deltaX != 0 || deltaY != 0) {

		for (i = 0; i < model->GetSubBlocks()->GetSize(); i++) {
			CProMoBlockModel* childModel = dynamic_cast<CProMoBlockModel*>(model->GetSubBlocks()->GetAt(i));
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

CRect CProMoBlockView::ComputeTextRect(const CString &text, const CFont& font)
/* ============================================================
	Function :		CProMoBlockView::ComputeTextRect
	Description :	Computes a CRect that fully contains the
					input string, using the default font.
	Access :		Protected

	Return :		CRect				-	"CRect" that will
											fully contain the
											text
	Parameters :	CString text		-	"CString" that 
											contains the text
					CFont font			-	"CFont" specifying
											the font, size and
											style to be used
	Usage :			Call to determine (without drawing on 
					display) the size of the input text. Can be
					used to resize the block and/or to set the
					minimum size such that the text can fit in
					it.

   ============================================================*/
{
	CDC dc;
	dc.CreateCompatibleDC(NULL);
	dc.SelectObject(font);
	int mode = dc.SetBkMode(TRANSPARENT);

	CRect textBounds(0, 0, 0, 0);
	dc.DrawText(text, &textBounds, DT_NOPREFIX | DT_SINGLELINE | DT_TOP | DT_CALCRECT);

	textBounds.right = textBounds.right + 4;
	textBounds.bottom = textBounds.bottom + 4;

	if (m_lockProportions) {

		double minWidth = GetMinimumSize().cx;
		double minHeight = GetMinimumSize().cy;

		double width = textBounds.Width();
		double height = textBounds.Height();

		// aspect ratio from minimum size
		double aspect = (double)minHeight / (double)minWidth;

		// scaling factors needed to satisfy requested bounds
		double scaleX = width / minWidth;
		double scaleY = height / minHeight;

		// pick the larger scale so both constraints are satisfied
		double scale = max(scaleX, scaleY);

		double newWidth = minWidth * scale;
		double newHeight = minHeight * scale;

		// update textBounds while keeping its top-left fixed
		textBounds.right = textBounds.left + newWidth;
		textBounds.bottom = textBounds.top + newHeight;

	}
	
	return textBounds;
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
	ASSERT_VALID(this->GetModel());
	CProMoBlockModel* model = this->GetModel();
	//recompute intersection for edges
	int i = 0;
	
	for (i = 0; i < model->GetIncomingEdges()->GetSize(); i++) {
		CProMoEdgeModel* edgeModel = dynamic_cast<CProMoEdgeModel*>(model->GetIncomingEdges()->GetAt(i));
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

	for (i = 0; i < model->GetOutgoingEdges()->GetSize(); i++) {
		CProMoEdgeModel* edgeModel = dynamic_cast<CProMoEdgeModel*>(model->GetOutgoingEdges()->GetAt(i));
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
	for (i = 0; i < model->GetSubBlocks()->GetSize(); i++) {
		CProMoBlockModel* childModel = dynamic_cast<CProMoBlockModel*>(model->GetSubBlocks()->GetAt(i));
		if (childModel) {
			CProMoBlockView* childView = childModel->GetMainView();
			if (childView) {
				childView->RecomputeIntersectionLinks();
			}
		}
	}

}

CProMoBlockModel* CProMoBlockView::GetModel() const
/* ============================================================
	Function :		CProMoBlockView::GetModel
	Description :	Returns a pointer to the model of this 
					block
	Access :		Public

	Return :		CProMoBlockModel*	-	A pointer to the 
											model
	Parameters :	none

   ============================================================*/
{
	return m_blockmodel;
}

void CProMoBlockView::SetModel(CProMoBlockModel* model)
/* ============================================================
	Function :		CProMoBlockView::SetModel
	Description :	Makes the object being passed as input
					parameter the model for this block
	Access :		Protected

	Return :		void
	Parameters :	CProMoBlockModel* block	-	the object that
												should be the
												model

   ============================================================*/
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
	ASSERT_VALID(this->GetModel());
	CProMoBlockModel* model = this->GetModel();
	for (int i = 0; i < model->GetSubBlocks()->GetSize(); i++) {
		CProMoBlockModel* childModel = dynamic_cast<CProMoBlockModel*>(model->GetSubBlocks()->GetAt(i));
		if (childModel) {
			CProMoBlockView* childView = childModel->GetMainView();
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
			model->GetParentBlock()->GetMainView()->AutoResize();
		}
	}
	else {
		this->RecomputeIntersectionLinks();
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
	if (GetModel()) {
		GetModel()->Copy(objView->GetModel());
	}
	SetLockedProportions(objView->HasLockedProportions());
	SetFitTitle(objView->HasFitTitle());
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
	if (m_fitTitle) {

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

	CProMoBlockModel* blockModel = dynamic_cast<CProMoBlockModel*>(model);

	if (blockModel) {
		obj->SetModel(blockModel);
	}

	return obj;

}

void CProMoBlockView::SetParentBlock(CProMoBlockView* parent)
/* ============================================================
	Function :		CProMoBlockView::SetParentBlock
	Description :	Makes the block being passed as input
					parameter the parent of this block
	Access :		Public

	Return :		void
	Parameters :	CProMoBlockView* block	-	the block that
												should be the
												parent block

   ============================================================*/
{
	if (parent) {
		GetModel()->SetParentBlock(parent->GetModel());
	}
	else {
		GetModel()->SetParentBlock(NULL);
	}
}

void CProMoBlockView::UnlinkAllSubBlocks()
/* ============================================================
	Function :		CProMoBlockView::UnlinkAllSubBlocks
	Description :	Removes all the children of this block
	Access :		Public

	Return :		void
	Parameters :	none

   ============================================================*/
{
	GetModel()->UnlinkAllSubBlocks();
}