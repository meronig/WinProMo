#include "../stdafx.h"
#include "ProcessEditor.h"
#include "ProcessEntityContainer.h"
#include "ProcessControlFactory.h"

#include <math.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CProcessEditor

CProcessEditor::CProcessEditor()
/* ============================================================
	Function :		CProcessEditor::CProcessEditor
	Description :	constructor

	Return :		void
	Parameters :	none

	Usage :

   ============================================================*/
{

	SetBackgroundColor(RGB(250, 250, 230));
	SetSnapToGrid(FALSE);
	SetRestraints(RESTRAINT_VIRTUAL);
	//SetPopupMenu(new CFlowchartMenu);

}

CProcessEditor::~CProcessEditor()
/* ============================================================
	Function :		CProcessEditor::~CProcessEditor
	Description :	destructor

	Return :		void
	Parameters :	none

	Usage :

   ============================================================*/
{
}

/////////////////////////////////////////////////////////////////////////////
// CProcessEditor overrides

void CProcessEditor::DrawGrid(CDC* dc, CRect /*rect*/, double zoom) const
/* ============================================================
	Function :		CProcessEditor::DrawGrid
	Description :	Draws the editor grid. We override this to
					draw the grid as a series of dots.

	Return :		void
	Parameters :	CDC* dc		-	CDC to draw to
					CRect		-	Complete rect
					double zoom	-	Current zoom level

	Usage :			Do not call directly.

   ============================================================*/
{

	COLORREF gridcol = GetGridColor();

	dc->SelectStockObject(BLACK_PEN);

	int stepx = GetVirtualSize().cx / GetGridSize().cx;
	int stepy = GetVirtualSize().cy / GetGridSize().cy;

	for (int x = 0; x <= stepx; x++)
		for (int y = 0; y <= stepy; y++)
			dc->SetPixel(round((double)(GetGridSize().cx * x) * zoom), round((double)(GetGridSize().cy * y) * zoom), gridcol);

}

void CProcessEditor::DrawObjects(CDC* dc, double zoom) const
/* ============================================================
	Function :		CProcessEditor::DrawObjects
	Description :	Draws the object

	Return :		void
	Parameters :	CDC* dc		-	CDC to draw to
					double zoom	-	Zoom level (use this value
									instead of GetZoom())

	Usage :			Overridden to draw draw dragged blocks
					and edges.

   ============================================================*/
{

	CDiagramEditor::DrawObjects(dc, zoom);
	CProcessEntityContainer* objs = static_cast<CProcessEntityContainer*>(GetDiagramEntityContainer());
	if (objs)
	{

		// draws blocks being dragged over all the others
		if (GetInteractMode() == MODE_MOVING) {
			for (int i = 0; i < GetObjectCount(); i++)
			{
				CProcessEntityBlock* block = dynamic_cast<CProcessEntityBlock*>(objs->GetAt(i));
				if (block) {
					if (block->IsSelected()) {
						DrawObjectsR(block, dc, zoom);
					}
				}

			}
		}

		// draws edges being reconnected (resized) over all the others
		if (GetInteractMode() == MODE_RESIZING) {
			CProcessLineEdge* edge = dynamic_cast<CProcessLineEdge*>(GetSelectedObject());
			if (edge) {
				if (edge->IsSelected()) {
					edge->DrawObject(dc, zoom);
				}
			}
		}
	}
}

void CProcessEditor::SaveObjects(CStringArray& stra)
/* ============================================================
	Function :		CProcessEditor::SaveObjects
	Description :	Saves all the objects to a CStringArray.

	Return :		void
	Parameters :	CStringArray& stra	-	CStringArray to
											save to.

	Usage :			Overridden to save the edges as well.

   ============================================================*/
{

	CDiagramEditor::SaveObjects(stra);
	CProcessEntityContainer* objs = static_cast<CProcessEntityContainer*>(GetDiagramEntityContainer());


}

/////////////////////////////////////////////////////////////////////////////
// CProcessEditor message handlers


CProcessEntityBlock* CProcessEditor::GetTargetBlock(CPoint point) {
	ResetTarget();

	CProcessEntityContainer* objs = static_cast<CProcessEntityContainer*>(GetDiagramEntityContainer());
	for (int j = GetObjectCount() - 1; j >= 0; j--) {
		CProcessEntityBlock* currObj = dynamic_cast<CProcessEntityBlock*>(objs->GetAt(j));

		if (currObj) {

			CPoint virtpoint(point);
			//ScreenToVirtual(virtpoint);
			int hitCode = currObj->GetHitCode(virtpoint);
			if (hitCode == DEHT_BODY) {
				// We found the object that was clicked
				if (!currObj->IsSelected()) {
					//drawing a new element
					if (IsDrawing()) {
						// new block
						CProcessEntityBlock* newObj = dynamic_cast<CProcessEntityBlock*>(GetDrawingObject());
						if (newObj) {
							if (newObj->canBeNested(currObj)) {
								return currObj;
							}
						}
						// new edge
						CProcessLineEdge* newEdge = dynamic_cast<CProcessLineEdge*>(GetDrawingObject());
						if (newEdge) {
							if (newEdge->canConnectSource(currObj)) {
								return currObj;
							}
						}
					}
					//moving blocks
					else if ((GetInteractMode() == MODE_MOVING)) {
						bool isValid = true;
						// check that no circular dependencies exist with selected objects
						for (int i = GetObjectCount() - 1; i >= 0; i--) {
							CProcessEntityBlock* selObj = dynamic_cast<CProcessEntityBlock*>(objs->GetAt(i));
							if (selObj) {
								if (selObj->IsSelected()) {
									if (!(selObj->canBeNested(currObj))) {
										isValid = false;
										break;
									}
									/*if (selObj->contains(currObj, true)) {
										isValid = false;
										break;
									}*/
								}
							}
						}
						if (isValid) {
							return currObj;
						}
					}
					//resizing (moving) edges
					if (GetInteractMode() == MODE_RESIZING) {
						CProcessLineEdge* edge = dynamic_cast<CProcessLineEdge*>(GetSelectedObject());
						//use actual point rather than cursor position
						if (edge) {
							if (GetSubMode() == DEHT_BOTTOMRIGHT) {
								if (edge->canConnectDestination(currObj)) {
									return currObj;
								}
							}
							else if (GetSubMode() == DEHT_TOPLEFT) {
								if (edge->canConnectSource(currObj)) {
									return currObj;
								}
							}
						}
					}			
				}
			}
		}
	}
	return NULL;
}

CProcessEntityBlock* CProcessEditor::GetConnectedBlock(CProcessLineEdge* line, BOOL backwards, BOOL ifSelected)
{
	CDiagramEntity* element;

	if (backwards) {
		element = line->GetSource();
	}
	else {
		element = line->GetDestination();
	}

	CProcessEntityBlock* block = dynamic_cast<CProcessEntityBlock*>(element);
	if (block) {
		return block;
	}
	CProcessLineEdge* edge = dynamic_cast<CProcessLineEdge*>(element);
	if (edge) {
		if (ifSelected) {
			if (!edge->IsSelected()) {
				return NULL;
			}
		}
		return GetConnectedBlock(edge, backwards, ifSelected);
	}
		
	return NULL;
}

void CProcessEditor::DeselectChildBlocks(CProcessEntityBlock* block)
{
	for (int i = 0; i < block->getSubBlocks()->GetSize(); i++) {
		CProcessEntityBlock* subBlock = dynamic_cast<CProcessEntityBlock*>(block->getSubBlocks()->GetAt(i));
		subBlock->Select(false);
		DeselectChildBlocks(subBlock);
	}
}

void CProcessEditor::SelectChildBlocks(CProcessEntityBlock* block)
{
	for (int i = 0; i < block->getSubBlocks()->GetSize(); i++) {
		CProcessEntityBlock* subBlock = dynamic_cast<CProcessEntityBlock*>(block->getSubBlocks()->GetAt(i));
		subBlock->Select(true);
		SelectChildBlocks(subBlock);
	}
}


void CProcessEditor::OnMouseMove(UINT nFlags, CPoint point)
/* ============================================================
	Function :		CProcessEditor::OnMouseMove
	Description :	Handler for WM_MOUSEMOVE. We add handling
					to close screen redraws as we are moving
					lots of stuff (all the attached objects in
					addition to the primarily moved). We also
					do secondary movements here - that is,
					objects linked to the one(s) being moved
					must be moved as well, even if they are
					not selected.

	Return :		void
	Parameters :	UINT nFlags		-	Not used
					CPoint point	-	Not used

	Usage :			Called from MFC

   ============================================================*/
{

	if ((GetInteractMode() == MODE_MOVING) || (GetInteractMode() == MODE_RESIZING && GetSelectCount() == 1) || IsDrawing())
		SetRedraw(FALSE);

	//line: topleft or bottomright
	//prevent moving: only resize+drawing allowed

	
	// when moving a block, move all connected elements accordingly
	if (GetInteractMode() == MODE_MOVING) {

		CProcessEntityBlock* selObj = NULL;
		CProcessLineEdge* selEdge = NULL;

		double oldTop = 0;
		double oldLeft = 0;
		double deltaTop = 0;
		double deltaLeft = 0;

		//BUG: when moving two child blocks, cannot determine target

		//We have issues with snaps

		// deselect edges to prevent them from being moved
		// should be more clever to deselect edges only when no attached block is selected (on both ends)
		// also, we should deselect nested blocks to avoid reassigning the parent
		CProcessEntityContainer* objs = static_cast<CProcessEntityContainer*>(GetDiagramEntityContainer());
		for (int j = GetObjectCount() - 1; j >= 0; j--) {
			
			selObj = dynamic_cast<CProcessEntityBlock*>(objs->GetAt(j));
			if (selObj) {
				if (selObj->IsSelected()) {
					DeselectChildBlocks(selObj);
				}
			}
			
			CProcessLineEdge* currObj = dynamic_cast<CProcessLineEdge*>(objs->GetAt(j));
			if (currObj) {
				if (currObj->IsSelected()) {
					//find if a selected block exists on both ends. Otherwise, deselect
					CProcessEntityBlock* block = GetConnectedBlock(currObj, true, true);
					if (block) {
						if (!block->IsSelected()) {
							currObj->Select(false);
						}
					}
					else {
						currObj->Select(false);
					}
					block = GetConnectedBlock(currObj, false, true);
					if (block) {
						if (!block->IsSelected()) {
							currObj->Select(false);
						}
					}
					else {
						currObj->Select(false);
					}
				}
			}
		}
		// may want to iterate among selected objects until one finds a block
		selObj = dynamic_cast<CProcessEntityBlock*>(GetSelectedObject());
		if (selObj) {
			oldTop = selObj->GetTop();
			oldLeft = selObj->GetLeft();
		}


		CDiagramEditor::OnMouseMove(nFlags, point);

		if (selObj) {
			deltaTop = selObj->GetTop() - oldTop;
			deltaLeft = selObj->GetLeft() - oldLeft;
		}

		//if only one object is selected, we need to manually trigger moverect to all child blocks
		if (GetSelectCount() == 1) {
			if (selObj) {
				if (deltaLeft != 0 || deltaTop != 0) {
					for (int i = 0; i < selObj->getSubBlocks()->GetSize(); i++) {
						CProcessEntityBlock* subBlock = dynamic_cast<CProcessEntityBlock*>(selObj->getSubBlocks()->GetAt(i));
					}
				}
			}
		}
		
	}
	else if (GetInteractMode() == MODE_RESIZING){

		CDiagramEntity* element = GetSelectedObject();
		double oldTop = 0;
		double oldLeft = 0;
		double oldBottom = 0;
		double oldRight = 0;
		if (element) {
			oldTop = element->GetTop();
			oldLeft = element->GetLeft();
			oldBottom = element->GetBottom();
			oldRight = element->GetRight();
		}

		CDiagramEditor::OnMouseMove(nFlags, point);
	
		// when resizing an element, modify the behavior if SHIFT key is pressed
		if ((nFlags & MK_SHIFT) == MK_SHIFT) {

			// handle shift key for edges: mainly snap them to horizontal, vertical or 45 degrees diagonal lines
			CProcessLineEdge* edge = dynamic_cast<CProcessLineEdge*>(element);
			if (edge) {
				if (GetSubMode() == DEHT_BOTTOMRIGHT) {
					if ((abs(edge->GetBottom() - edge->GetTop())) / 2 > abs(edge->GetLeft() - edge->GetRight())) {
						edge->SetRight(edge->GetLeft());
					}
					else if (abs(edge->GetBottom() - edge->GetTop()) < (abs(edge->GetLeft() - edge->GetRight())) / 2) {
						edge->SetBottom(edge->GetTop());
					}
					else {
						if (abs(edge->GetBottom() - edge->GetTop()) > abs(edge->GetLeft() - edge->GetRight())) {
							if (edge->GetBottom() > edge->GetTop()) {
								edge->SetBottom(edge->GetTop() + abs(edge->GetLeft() - edge->GetRight()));
							}
							else {
								edge->SetBottom(edge->GetTop() - abs(edge->GetLeft() - edge->GetRight()));
							}
						}
						else {
							if (edge->GetRight() > edge->GetLeft()) {
								edge->SetRight(edge->GetLeft() + abs(edge->GetTop() - edge->GetBottom()));
							}
							else {
								edge->SetRight(edge->GetLeft() - abs(edge->GetTop() - edge->GetBottom()));
							}
						}
					}
				}

				else {
					if ((abs(edge->GetBottom() - edge->GetTop())) / 2 > abs(edge->GetLeft() - edge->GetRight())) {
						edge->SetLeft(edge->GetRight());
					}
					else if (abs(edge->GetBottom() - edge->GetTop()) < (abs(edge->GetLeft() - edge->GetRight())) / 2) {
						edge->SetTop(edge->GetBottom());
					}
					else {
						if (abs(edge->GetBottom() - edge->GetTop()) > abs(edge->GetLeft() - edge->GetRight())) {
							if (edge->GetBottom() > edge->GetTop()) {
								edge->SetTop(edge->GetBottom() - abs(edge->GetLeft() - edge->GetRight()));
							}
							else {
								edge->SetTop(edge->GetBottom() + abs(edge->GetLeft() - edge->GetRight()));
							}
						}
						else {
							if (edge->GetRight() > edge->GetLeft()) {
								edge->SetLeft(edge->GetRight() - abs(edge->GetTop() - edge->GetBottom()));
							}
							else {
								edge->SetLeft(edge->GetRight() + abs(edge->GetTop() - edge->GetBottom()));
							}
						}
					}
				}
			}
			//handle shift key for nodes: keep proportions
			CProcessEntityBlock* block = dynamic_cast<CProcessEntityBlock*>(element);
			if (block) {
				double oldRatio = (oldBottom - oldTop) / (oldRight - oldLeft);
				double deltaX = 0;
				double deltaY = 0;
				if (GetSubMode() == DEHT_TOPMIDDLE) {
					deltaY = (oldTop - block->GetTop()) / oldRatio;
					block->SetLeft(oldLeft - deltaY / 2);
					block->SetRight(oldRight + deltaY / 2);
				}
				else if (GetSubMode() == DEHT_BOTTOMMIDDLE) {
					deltaY = (block->GetBottom() - oldBottom) / oldRatio;
					block->SetLeft(oldLeft - deltaY / 2);
					block->SetRight(oldRight + deltaY / 2);
				}
				else if (GetSubMode() == DEHT_LEFTMIDDLE) {
					deltaX = (oldLeft - block->GetLeft()) * oldRatio;
					block->SetTop(oldTop - deltaX / 2);
					block->SetBottom(oldBottom + deltaX / 2);
				}
				else if (GetSubMode() == DEHT_RIGHTMIDDLE) {
					deltaX = (block->GetRight() - oldRight) * oldRatio;
					block->SetTop(oldTop - deltaX / 2);
					block->SetBottom(oldBottom + deltaX / 2);

				}
				else if (GetSubMode() == DEHT_TOPLEFT) {
					deltaY = (oldTop - block->GetTop()) / oldRatio;
					deltaX = (oldLeft - block->GetLeft()) * oldRatio;
					if (abs(oldTop - point.y) < abs(oldLeft - point.x)) {
						block->SetLeft(oldLeft - deltaY);
					}
					else {
						block->SetTop(oldTop - deltaX);
					}
				}
				else if (GetSubMode() == DEHT_TOPRIGHT) {
					deltaY = (oldTop - block->GetTop()) / oldRatio;
					deltaX = (block->GetRight() - oldRight) * oldRatio;
					if (abs(oldTop - point.y) < abs(oldRight - point.x)) {
						block->SetRight(oldRight + deltaY);
					}
					else {
						block->SetTop(oldTop - deltaX);
					}
				}
				else if (GetSubMode() == DEHT_BOTTOMLEFT) {
					deltaY = (block->GetBottom() - oldBottom) / oldRatio;
					deltaX = (oldLeft - block->GetLeft()) * oldRatio;
					if (abs(oldBottom - point.y) < abs(oldLeft - point.x)) {
						block->SetLeft(oldLeft - deltaY);
					}
					else {
						block->SetBottom(oldBottom + deltaX);
					}
				}
				else if (GetSubMode() == DEHT_BOTTOMRIGHT) {
					deltaY = (block->GetBottom() - oldBottom) / oldRatio;
					deltaX = (block->GetRight() - oldRight) * oldRatio;
					if (abs(oldBottom - point.y) < abs(oldRight - point.x)) {
						block->SetRight(oldRight + deltaY);
					}
					else {
						block->SetBottom(oldBottom + deltaX);
					}
				}
			}
		}
	
		CProcessLineEdge* edge = dynamic_cast<CProcessLineEdge*>(element);
		if (edge) {
			//check if edge is part of a multi-edge and, if so, keep it connected
			if (edge->GetSource() != NULL) {
				CProcessLineEdge* src = dynamic_cast<CProcessLineEdge*>(edge->GetSource());
				if (src) {
					src->SetRight(edge->GetLeft());
					src->SetBottom(edge->GetTop());
				}
			}
			if (edge->GetDestination() != NULL) {
				CProcessLineEdge* dest = dynamic_cast<CProcessLineEdge*>(edge->GetDestination());
				if (dest) {
					dest->SetLeft(edge->GetRight());
					dest->SetTop(edge->GetBottom());
				}
			}
		}
	}
	else {
		CDiagramEditor::OnMouseMove(nFlags, point);
	}

	if (GetInteractMode() == MODE_MOVING || GetInteractMode() == MODE_RESIZING || IsDrawing())
	{
		CPoint target = point;
		ScreenToVirtual(target);
		CProcessLineEdge* edge = NULL;
		if (GetInteractMode() == MODE_RESIZING) {
			edge = dynamic_cast<CProcessLineEdge*>(GetSelectedObject());
			//use actual point rather than cursor position
			if (edge) {
				if (GetSubMode() == DEHT_BOTTOMRIGHT) {
					target = edge->GetRect().BottomRight();
				}
				else if (GetSubMode() == DEHT_TOPLEFT)  {
					target = edge->GetRect().TopLeft();
				}
			}
		}

		//we may relax the constraint on selectcount
		if ((GetInteractMode() == MODE_MOVING) || IsDrawing() || edge) {
			//associate only one element at a time
			//TODO: consider generalizing to multiple blocks (for sure, edges are not part of the selection)
			if (GetSelectCount() <= 1) {
				/*check if we are dropping the object inside a block*/
				CProcessEntityBlock* targetBlock = GetTargetBlock(target);
				if (targetBlock) {
					targetBlock->SetTarget(true);
				}
			}
		}

		SetRedraw(TRUE);
		RedrawWindow();
	}

}

void CProcessEditor::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
/* ============================================================
	Function :		CProcessEditor::OnKeyDown
	Description :	Handles the WM_KEYDOWN-message. We
					override this as objects might be moved and
					we will have to move unlinked objects as
					well.

	Return :		void
	Parameters :	UINT nChar		-	Not used
					UINT nRepCnt	-	Not used
					UINT nFlags		-	Not used

	Usage :			Called from MFC

   ============================================================*/
{

	//SetRedraw(FALSE);
	CDiagramEditor::OnKeyDown(nChar, nRepCnt, nFlags);

	
}

void CProcessEditor::OnLButtonDown(UINT nFlags, CPoint point)
{
	BOOL goon = TRUE;
	int count = 0;
	CDiagramEntityContainer* objs = GetDiagramEntityContainer();
	CProcessEntityBlock* parent = NULL;

	if (IsDrawing()) {

		//by default, where we click is topleft for a line
		//bottomdown is the resize mode set afterwards

		if (objs) {

			UnselectAll();

			// Identify clicked block (if any)
			CPoint virtpoint = point;
			ScreenToVirtual(virtpoint);

			parent = GetTargetBlock(virtpoint);

		}
	}

	// Create a new element as usual
	CDiagramEditor::OnLButtonDown(nFlags, point);

	
	// Get the element being created (which will be selected)
	if (GetSelectedObject() != NULL) {
		CProcessEntityBlock* obj;
		obj = dynamic_cast<CProcessEntityBlock*>(GetSelectedObject());
		if (obj) {
			if (parent != NULL) {
				obj->setParentBlock(parent);
				parent->autoResize();
			}
		}
		CProcessLineEdge* edge;
		edge = dynamic_cast<CProcessLineEdge*>(GetSelectedObject());
		if (edge) {
			if (GetInteractMode() == MODE_RESIZING && GetSubMode() == DEHT_CENTER) {
				//take a snapshot to undo changes
				GetDiagramEntityContainer()->Snapshot();
				//split the edge into two
				CProcessLineEdge* newEdge = new CProcessLineEdge;
				//compute the length and position of both edges
				CRect edgeRect = edge->GetRect();
				CRect newEdgeRect(edgeRect);
				edgeRect.bottom = edgeRect.top + (edgeRect.Height() / 2);
				edgeRect.right = edgeRect.left + (edgeRect.Width() / 2);
				edge->SetRect(edgeRect);
				newEdgeRect.top = newEdgeRect.bottom - (newEdgeRect.Height() / 2);;
				newEdgeRect.left = newEdgeRect.right - (newEdgeRect.Width() / 2);;
				newEdge->SetRect(newEdgeRect);
				newEdge->Select(false);
				//update edge links
				newEdge->SetDestination(edge->GetDestination());
				newEdge->SetSource(edge);
				//add new edge
				AddObject(newEdge);
				//switch to resizing the old edge
				SetInteractMode(MODE_RESIZING, DEHT_BOTTOMRIGHT);
			}
			else {
				if (parent != NULL) {
					edge->SetSource(parent);
				}
			}
		}
	}

}

void CProcessEditor::OnLButtonUp(UINT nFlags, CPoint point) {

	CProcessEntityBlock* currObj = NULL;
	CProcessEntityContainer* objs = static_cast<CProcessEntityContainer*>(GetDiagramEntityContainer());

	if (GetInteractMode() == MODE_MOVING) {

		
		CProcessEntityBlock* selObj = NULL;
		//for each object being selected
		for (int i = 0; i < GetObjectCount(); i++) {
			selObj = dynamic_cast<CProcessEntityBlock*>(objs->GetAt(i));
			if (selObj) {
				if (selObj->IsSelected()) {
					//trigger mouse movement, so to maintain hierarchy in case no movement is made
					OnMouseMove(nFlags, point);
					//check which is the object being dropped, if any
					currObj = objs->getTarget();
					if (currObj) {
						if (selObj->getParentBlock() != currObj) {
							// Set the parent to be that object
							selObj->setParentBlock(currObj);
						}
					}
					else	
					{
						//no object got hit, then the selected one has no parent
						selObj->setParentBlock(NULL);
					}
				}
			}
		}
		//Need to reorder shapes according to nesting
		static_cast<CProcessEntityContainer*>(objs)->reorder();
	}


	//bug: never called when a new object is created, whereas it should
	if (GetInteractMode() == MODE_RESIZING) {
		//resizing an edge
		CProcessLineEdge* edge = dynamic_cast<CProcessLineEdge*>(GetSelectedObject());
		if (edge) {
			currObj = objs->getTarget();
			if (GetSubMode() == DEHT_BOTTOMRIGHT) {
				CProcessLineEdge* destEdge = dynamic_cast<CProcessLineEdge*>(edge->GetDestination());
				if (!destEdge) {
					edge->SetDestination(currObj);
				}
			}
			else if (GetSubMode() == DEHT_TOPLEFT) {
				CProcessLineEdge* srcEdge = dynamic_cast<CProcessLineEdge*>(edge->GetSource());
				if (!srcEdge) {
					edge->SetSource(currObj);
				}
			}
			
			//Need to reorder shapes according to nesting
			static_cast<CProcessEntityContainer*>(objs)->reorder();
		}
	}

	//reset target, so that blocks appear as normal
	ResetTarget();

	CDiagramEditor::OnLButtonUp(nFlags, point);
	//do the auto-resize on all blocks
	AutoResizeAll();
	RedrawWindow();
}


/////////////////////////////////////////////////////////////////////////////
// CProcessEditor private helpers


CDiagramEntity* CProcessEditor::GetNamedObject(const CString& name) const
/* ============================================================
	Function :		CProcessEditor::GetNamedObject
	Description :	Returns the object with the name attribute
					name.

	Return :		CDiagramEntity*	-	The object, or NULL
											if not found.
	Parameters :	const CString& name	-	The name of the
											object to find.

	Usage :			Call to get the object with the name name,
					if it exists.

   ============================================================*/
{

	CDiagramEntity* result = NULL;

	int count = GetObjectCount();
	CDiagramEntity* obj;
	for (int t = 0; t < count; t++)
	{
		obj = GetObject(t);
		if (obj && obj->GetName() == name)
			result = obj;
	}

	//return dynamic_cast<CProcessEntityBlock*>(result);
	return result;

}

void CProcessEditor::Cut()
{
	CDiagramEntityContainer* objs = GetDiagramEntityContainer();
	if (objs)
	{
		objs->Snapshot();
		objs->CopyAllSelected();
		for (int i = 0; i < objs->GetSize(); i++) {
			CProcessEntityBlock* block = dynamic_cast<CProcessEntityBlock*>(objs->GetAt(i));
			if (block) {
				if (block->IsSelected()) {
					block->unlinkSubBlocks();
				}
			}

		}
		DeleteAllSelected();
	}
}

//draws blocks hierarchically: subblocks are always drawn in the foreground, regardless
//of current ordering, siblings follow the ordering in CProcessEntityContainer
void CProcessEditor::DrawObjectsR(CProcessEntityBlock* block, CDC* dc, double zoom) const
{
	block->DrawObject(dc, zoom);
	int count = GetObjectCount();
	for (int i = 0; i < count; i++)
	{
		CProcessEntityContainer* objs = static_cast<CProcessEntityContainer*>(GetDiagramEntityContainer());
		CProcessEntityBlock* child = dynamic_cast<CProcessEntityBlock*>(objs->GetAt(i));
		if (child) {
			if (block->contains(child, false)) {
				DrawObjectsR(child, dc, zoom);
			}
		}
	}
	for (int i = 0; i < block->getIncomingEdges()->GetSize(); i++) {
		CProcessLineEdge* edge = dynamic_cast<CProcessLineEdge*>(block->getIncomingEdges()->GetAt(i));
		if (edge) {
			edge->DrawObject(dc, zoom);
		}
	}
	for (int i = 0; i < block->getOutgoingEdges()->GetSize(); i++) {
		CProcessLineEdge* edge = dynamic_cast<CProcessLineEdge*>(block->getOutgoingEdges()->GetAt(i));
		if (edge) {
			edge->DrawObject(dc, zoom);
		}
	}
}

void CProcessEditor::ResetTarget()
{
	CProcessEntityContainer* objs = static_cast<CProcessEntityContainer*>(GetDiagramEntityContainer());
	if (objs)
	{
		int count = 0;
		CProcessEntityBlock* obj;
		for (int i = 0; i < objs->GetSize(); i++) {
			obj = dynamic_cast<CProcessEntityBlock*>(objs->GetAt(i));
			SetTarget(obj, FALSE);
		}
	}
}

void CProcessEditor::SetTarget(CProcessEntityBlock* obj, BOOL select)
{
	if (obj) {
		CProcessEntityContainer* objs = static_cast<CProcessEntityContainer*>(GetDiagramEntityContainer());
		if (objs) {
			objs->SetTarget(obj, select);
		}
	}

}

void CProcessEditor::PrepareForAlignment() {

	CProcessEntityBlock* currObj = NULL;
	CProcessEntityContainer* objs = static_cast<CProcessEntityContainer*>(GetDiagramEntityContainer());
	CProcessEntityBlock* selObj = NULL;
	CProcessLineEdge* selEdge = NULL;

	for (int i = 0; i < GetObjectCount(); i++) {
		selObj = dynamic_cast<CProcessEntityBlock*>(objs->GetAt(i));
		if (selObj) {
			if (selObj->IsSelected()) {
				DeselectChildBlocks(selObj);
			}
		}
		selEdge = dynamic_cast<CProcessLineEdge*>(objs->GetAt(i));
		if (selEdge) {
			selEdge->Select(false);
		}
	}
}

void CProcessEditor::AutoResizeAll()
{
	CProcessEntityContainer* objs = static_cast<CProcessEntityContainer*>(GetDiagramEntityContainer());
	CProcessEntityBlock* selObj = NULL;

	for (int i = 0; i < GetObjectCount(); i++) {
		selObj = dynamic_cast<CProcessEntityBlock*>(objs->GetAt(i));
		if (selObj) {
		//	if (selObj->IsSelected()) {
				selObj->autoResize();
		//	}
		}
	}
	RedrawWindow();
}


void CProcessEditor::LeftAlignSelected()
{
	PrepareForAlignment();
	CDiagramEditor::LeftAlignSelected();
	AutoResizeAll();	
}

void CProcessEditor::RightAlignSelected()
{
	PrepareForAlignment();
	CDiagramEditor::RightAlignSelected();
	AutoResizeAll();
}

void CProcessEditor::TopAlignSelected()
{
	PrepareForAlignment();
	CDiagramEditor::TopAlignSelected();
	AutoResizeAll();
}

void CProcessEditor::BottomAlignSelected()
{
	PrepareForAlignment();
	CDiagramEditor::BottomAlignSelected();
	AutoResizeAll();
}

void CProcessEditor::Load(const CStringArray& stra)
{
	int max = stra.GetSize();

	//First read: create objects
	for (int t = 0; t < max; t++)
	{
		CString str = stra.GetAt(t);
		if (!FromString(str))
		{
			CDiagramEntity* obj = CProcessControlFactory::CreateFromString(str);
			if (obj)
				//m_objs.Add(obj);
				AddObject(obj);

			/*
			CGSMEntity* obj;

			obj = CGSMEntity::CreateFromString( str );
			if( !obj )
				obj = CDiagramLine::CreateFromString( str );

			if( obj )
				m_editor.AddObject( obj );
			*/
		}
	}
	//Second read: create logical links between objects
	for (int t = 0; t < max; t++)
	{
		CString str = stra.GetAt(t);
		if (!FromString(str))
		{
			BOOL result = FALSE;
			CTokenizer main(str, _T(":"));
			CString header;
			CString data;
			if (main.GetSize() == 2)
			{
				main.GetAt(0, header);
				main.GetAt(1, data);
				header.TrimLeft();
				header.TrimRight();
				data.TrimLeft();
				data.TrimRight();
				// Note: code cannot be reused for derived classes
				if (header == _T("process_block"))
				{
					CTokenizer tok(data.Left(data.GetLength() - 1));
					int size = tok.GetSize();
					if (size >= 8) {
						CString nodeName;
						CString parentName;
						tok.GetAt(5, nodeName);
						tok.GetAt(7, parentName);
						CProcessEntityBlock* node = dynamic_cast<CProcessEntityBlock*>(GetNamedObject(nodeName));
						if (node) {
							CProcessEntityBlock* parent = dynamic_cast<CProcessEntityBlock*>(GetNamedObject(parentName));
							if (parent) {
								node->setParentBlock(parent);
							}
						}
					}
				}
				else if (header == _T("process_edge")) {
					CTokenizer tok(data.Left(data.GetLength() - 1));
					int size = tok.GetSize();
					if (size >= 9) {
						CString nodeName;
						CString sourceName;
						CString destName;
						tok.GetAt(5, nodeName);
						tok.GetAt(7, sourceName);
						tok.GetAt(8, destName);
						CProcessLineEdge* edge = dynamic_cast<CProcessLineEdge*>(GetNamedObject(nodeName));
						if (edge) {
							CDiagramEntity* source = dynamic_cast<CDiagramEntity*>(GetNamedObject(sourceName));
							if (source) {
								edge->SetSource(source);
							}
							CDiagramEntity* dest = dynamic_cast<CDiagramEntity*>(GetNamedObject(destName));
							if (dest) {
								edge->SetDestination(dest);
							}
						}
					}
				}
			}
		}
	}

}
