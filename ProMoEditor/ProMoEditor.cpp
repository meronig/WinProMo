#include "stdafx.h"
#include "ProMoEditor.h"
#include "ProMoEntityContainer.h"
#include "ProMoEdgeModel.h"

#include <math.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CProMoEditor

CProMoEditor::CProMoEditor()
/* ============================================================
	Function :		CProMoEditor::CProMoEditor
	Description :	constructor

	Return :		void
	Parameters :	none

	Usage :

   ============================================================*/
{

	SetBackgroundColor(RGB(250, 250, 230));
	SetSnapToGrid(FALSE);
	SetRestraints(RESTRAINT_VIRTUAL);
	
}

CProMoEditor::~CProMoEditor()
/* ============================================================
	Function :		CProMoEditor::~CProMoEditor
	Description :	destructor

	Return :		void
	Parameters :	none

	Usage :

   ============================================================*/
{
}

/////////////////////////////////////////////////////////////////////////////
// CProcessEditor overrides

void CProMoEditor::DrawGrid(CDC* dc, CRect /*rect*/, double zoom) const
/* ============================================================
	Function :		CProMoEditor::DrawGrid
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

void CProMoEditor::DrawObjects(CDC* dc, double zoom) const
/* ============================================================
	Function :		CProMoEditor::DrawObjects
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
	CProMoEntityContainer* objs = static_cast<CProMoEntityContainer*>(GetDiagramEntityContainer());
	if (objs)
	{

		// draws blocks being dragged over all the others
		if (GetInteractMode() == MODE_MOVING) {
			for (int i = 0; i < GetObjectCount(); i++)
			{
				CProMoBlockView* block = dynamic_cast<CProMoBlockView*>(objs->GetAt(i));
				if (block) {
					if (block->IsSelected()) {
						DrawObjectsR(block, dc, zoom);
					}
				}

			}
		}

		// draws edges being reconnected (resized) over all the others
		if (GetInteractMode() == MODE_RESIZING) {
			CProMoEdgeView* edge = dynamic_cast<CProMoEdgeView*>(GetSelectedObject());
			if (edge) {
				if (edge->IsSelected()) {
					edge->DrawObject(dc, zoom);
				}
			}
		}
	}
}

void CProMoEditor::SaveObjects(CStringArray& stra)
/* ============================================================
	Function :		CProMoEditor::SaveObjects
	Description :	Saves all the objects to a CStringArray.

	Return :		void
	Parameters :	CStringArray& stra	-	CStringArray to
											save to.

	Usage :			Overridden to save the model as well.

   ============================================================*/
{

	CDiagramEditor::SaveObjects(stra);
	CProMoEntityContainer* objs = static_cast<CProMoEntityContainer*>(GetDiagramEntityContainer());

	CObArray models;

	int i;
	for (i = 0; i < objs->GetSize(); i++) {
		CProMoBlockView* currObjBlock = dynamic_cast<CProMoBlockView*>(objs->GetAt(i));
		if (currObjBlock) {
			models.Add(currObjBlock->getModel());
		}
		CProMoEdgeView* currObjEdge = dynamic_cast<CProMoEdgeView*>(objs->GetAt(i));
		if (currObjEdge) {
			models.Add(currObjEdge->getModel());
		}
	}

	for (i = 0; i < models.GetSize(); i++) {
		CProMoModel* currModel = dynamic_cast<CProMoModel*>(models.GetAt(i));
		BOOL found = FALSE;
		for (int j = 0; j < i; j++) {
			CProMoModel* prevModel = dynamic_cast<CProMoModel*>(models.GetAt(j));
			if (prevModel == currModel) {
				found = TRUE;
				break;
			}
		}
		if (!found) {
			stra.Add(currModel->GetString());
		}
	}
}

/////////////////////////////////////////////////////////////////////////////
// CProMoEditor message handlers


CProMoBlockView* CProMoEditor::GetTargetBlock(CPoint point) {
	ResetTarget();

	CProMoEntityContainer* objs = static_cast<CProMoEntityContainer*>(GetDiagramEntityContainer());
	for (int j = GetObjectCount() - 1; j >= 0; j--) {
		CProMoBlockView* currObj = dynamic_cast<CProMoBlockView*>(objs->GetAt(j));

		if (currObj) {

			CPoint virtpoint(point);
			int hitCode = currObj->GetHitCode(virtpoint);
			if (hitCode == DEHT_BODY) {
				// We found the object that was clicked
				if (!currObj->IsSelected()) {
					//drawing a new element
					if (IsDrawing()) {
						// new block
						CProMoBlockView* newObj = dynamic_cast<CProMoBlockView*>(GetDrawingObject());
						if (newObj) {
							if (newObj->getModel()->CanBeNested(currObj->getModel())) {
								return currObj;
							}
						}
						// new edge
						CProMoEdgeView* newEdge = dynamic_cast<CProMoEdgeView*>(GetDrawingObject());
						if (newEdge) {
							if (newEdge->getModel()->canConnectSource(currObj->getModel())) {
								return currObj;
							}
						}
					}
					//moving blocks
					else if ((GetInteractMode() == MODE_MOVING)) {
						BOOL isValid = TRUE;
						// check that no circular dependencies exist with selected objects
						for (int i = GetObjectCount() - 1; i >= 0; i--) {
							CProMoBlockView* selObj = dynamic_cast<CProMoBlockView*>(objs->GetAt(i));
							if (selObj) {
								if (selObj->IsSelected()) {
									if (!(selObj->getModel()->CanBeNested(currObj->getModel()))) {
										isValid = FALSE;
										break;
									}
								}
							}
						}
						if (isValid) {
							return currObj;
						}
					}
					//resizing (moving) edges
					if (GetInteractMode() == MODE_RESIZING) {
						CProMoEdgeView* edge = dynamic_cast<CProMoEdgeView*>(GetSelectedObject());
						//use actual point rather than cursor position
						if (edge) {
							if (GetSubMode() == DEHT_BOTTOMRIGHT) {
								if (edge->getModel()->canConnectDestination(currObj->getModel())) {
									return currObj;
								}
							}
							else if (GetSubMode() == DEHT_TOPLEFT) {
								if (edge->getModel()->canConnectSource(currObj->getModel())) {
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

CProMoBlockView* CProMoEditor::GetConnectedBlock(CProMoEdgeView* line, BOOL backwards, BOOL ifSelected)
{
	CProMoBlockModel* model = NULL;
	if (backwards) {
		model = dynamic_cast<CProMoBlockModel*>(line->getModel()->GetSource());
		if (model) {
			return model->GetMainView();
		}
	}
	else {
		model = dynamic_cast<CProMoBlockModel*>(line->getModel()->GetDestination());
		if (model) {
			return model->GetMainView();
		}
	}

	return NULL;
}

void CProMoEditor::DeselectChildBlocks(CProMoBlockView* block)
{
	ASSERT(block->getModel()!=NULL);
	CProMoBlockModel* model = block->getModel();
	for (int i = 0; i < model->GetSubBlocks()->GetSize(); i++) {
		CProMoBlockModel* subBlock = dynamic_cast<CProMoBlockModel*>(model->GetSubBlocks()->GetAt(i));
		subBlock->GetMainView()->Select(FALSE);
		DeselectChildBlocks(subBlock->GetMainView());
	}
}

void CProMoEditor::SelectChildBlocks(CProMoBlockView* block)
{
	ASSERT(block->getModel() != NULL);
	CProMoBlockModel* model = block->getModel();
	for (int i = 0; i < model->GetSubBlocks()->GetSize(); i++) {
		CProMoBlockModel* subBlock = dynamic_cast<CProMoBlockModel*>(model->GetSubBlocks()->GetAt(i));
		subBlock->GetMainView()->Select(TRUE);
		SelectChildBlocks(subBlock->GetMainView());
	}
}


void CProMoEditor::OnMouseMove(UINT nFlags, CPoint point)
/* ============================================================
	Function :		CProMoEditor::OnMouseMove
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

		CProMoBlockView* selObj = NULL;
		CProMoEdgeView* selEdge = NULL;

		//BUG: when moving two child blocks, cannot determine target

		//We have issues with snaps

		// deselect edges to prevent them from being moved
		// should be more clever to deselect edges only when no attached block is selected (on both ends)
		// also, we should deselect nested blocks to avoid reassigning the parent
		CProMoEntityContainer* objs = static_cast<CProMoEntityContainer*>(GetDiagramEntityContainer());
		for (int j = GetObjectCount() - 1; j >= 0; j--) {
			
			selObj = dynamic_cast<CProMoBlockView*>(objs->GetAt(j));
			if (selObj) {
				if (selObj->IsSelected()) {
					DeselectChildBlocks(selObj);
				}
			}
			
			CProMoEdgeView* currObj = dynamic_cast<CProMoEdgeView*>(objs->GetAt(j));
			if (currObj) {
				if (currObj->IsSelected()) {
					//find if a selected block exists on both ends. Otherwise, deselect
					CProMoBlockView* block = GetConnectedBlock(currObj, TRUE, TRUE);
					if (block) {
						if (!block->IsSelected()) {
							currObj->Select(FALSE);
						}
					}
					else {
						currObj->Select(FALSE);
					}
					block = GetConnectedBlock(currObj, FALSE, TRUE);
					if (block) {
						if (!block->IsSelected()) {
							currObj->Select(FALSE);
						}
					}
					else {
						currObj->Select(FALSE);
					}
				}
			}
		}
		
		CDiagramEditor::OnMouseMove(nFlags, point);

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
			CProMoEdgeView* edge = dynamic_cast<CProMoEdgeView*>(element);
			if (edge) {
				if (GetSubMode() == DEHT_BOTTOMRIGHT) {
					if ((fabs(edge->GetBottom() - edge->GetTop())) / 2 > fabs(edge->GetLeft() - edge->GetRight())) {
						edge->SetRight(edge->GetLeft());
					}
					else if (fabs(edge->GetBottom() - edge->GetTop()) < (fabs(edge->GetLeft() - edge->GetRight())) / 2) {
						edge->SetBottom(edge->GetTop());
					}
					else {
						if (fabs(edge->GetBottom() - edge->GetTop()) > fabs(edge->GetLeft() - edge->GetRight())) {
							if (edge->GetBottom() > edge->GetTop()) {
								edge->SetBottom(edge->GetTop() + fabs(edge->GetLeft() - edge->GetRight()));
							}
							else {
								edge->SetBottom(edge->GetTop() - fabs(edge->GetLeft() - edge->GetRight()));
							}
						}
						else {
							if (edge->GetRight() > edge->GetLeft()) {
								edge->SetRight(edge->GetLeft() + fabs(edge->GetTop() - edge->GetBottom()));
							}
							else {
								edge->SetRight(edge->GetLeft() - fabs(edge->GetTop() - edge->GetBottom()));
							}
						}
					}
				}

				else {
					if ((fabs(edge->GetBottom() - edge->GetTop())) / 2 > fabs(edge->GetLeft() - edge->GetRight())) {
						edge->SetLeft(edge->GetRight());
					}
					else if (fabs(edge->GetBottom() - edge->GetTop()) < (fabs(edge->GetLeft() - edge->GetRight())) / 2) {
						edge->SetTop(edge->GetBottom());
					}
					else {
						if (fabs(edge->GetBottom() - edge->GetTop()) > fabs(edge->GetLeft() - edge->GetRight())) {
							if (edge->GetBottom() > edge->GetTop()) {
								edge->SetTop(edge->GetBottom() - fabs(edge->GetLeft() - edge->GetRight()));
							}
							else {
								edge->SetTop(edge->GetBottom() + fabs(edge->GetLeft() - edge->GetRight()));
							}
						}
						else {
							if (edge->GetRight() > edge->GetLeft()) {
								edge->SetLeft(edge->GetRight() - fabs(edge->GetTop() - edge->GetBottom()));
							}
							else {
								edge->SetLeft(edge->GetRight() + fabs(edge->GetTop() - edge->GetBottom()));
							}
						}
					}
				}
			}
			//handle shift key for nodes: keep proportions
			CProMoBlockView* block = dynamic_cast<CProMoBlockView*>(element);
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
					if (fabs(oldTop - point.y) < fabs(oldLeft - point.x)) {
						block->SetLeft(oldLeft - deltaY);
					}
					else {
						block->SetTop(oldTop - deltaX);
					}
				}
				else if (GetSubMode() == DEHT_TOPRIGHT) {
					deltaY = (oldTop - block->GetTop()) / oldRatio;
					deltaX = (block->GetRight() - oldRight) * oldRatio;
					if (fabs(oldTop - point.y) < fabs(oldRight - point.x)) {
						block->SetRight(oldRight + deltaY);
					}
					else {
						block->SetTop(oldTop - deltaX);
					}
				}
				else if (GetSubMode() == DEHT_BOTTOMLEFT) {
					deltaY = (block->GetBottom() - oldBottom) / oldRatio;
					deltaX = (oldLeft - block->GetLeft()) * oldRatio;
					if (fabs(oldBottom - point.y) < fabs(oldLeft - point.x)) {
						block->SetLeft(oldLeft - deltaY);
					}
					else {
						block->SetBottom(oldBottom + deltaX);
					}
				}
				else if (GetSubMode() == DEHT_BOTTOMRIGHT) {
					deltaY = (block->GetBottom() - oldBottom) / oldRatio;
					deltaX = (block->GetRight() - oldRight) * oldRatio;
					if (fabs(oldBottom - point.y) < fabs(oldRight - point.x)) {
						block->SetRight(oldRight + deltaY);
					}
					else {
						block->SetBottom(oldBottom + deltaX);
					}
				}
			}
		}
	
		CProMoEdgeView* edge = dynamic_cast<CProMoEdgeView*>(element);
		if (edge) {
			//check if edge is part of a multi-edge and, if so, keep it connected
			if (edge->GetSource() != NULL) {
				CProMoEdgeView* src = dynamic_cast<CProMoEdgeView*>(edge->GetSource());
				if (src) {
					src->SetRight(edge->GetLeft());
					src->SetBottom(edge->GetTop());
				}
			}
			if (edge->GetDestination() != NULL) {
				CProMoEdgeView* dest = dynamic_cast<CProMoEdgeView*>(edge->GetDestination());
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
		CProMoEdgeView* edge = NULL;
		if (GetInteractMode() == MODE_RESIZING) {
			edge = dynamic_cast<CProMoEdgeView*>(GetSelectedObject());
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
				CProMoBlockView* targetBlock = GetTargetBlock(target);
				if (targetBlock) {
					targetBlock->SetTarget(TRUE);
				}
			}
		}

		SetRedraw(TRUE);
		RedrawWindow();
	}

}

void CProMoEditor::OnLButtonDown(UINT nFlags, CPoint point)
{
	BOOL goon = TRUE;
	int count = 0;
	CDiagramEntityContainer* objs = GetDiagramEntityContainer();
	CProMoBlockView* parent = NULL;

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
		CProMoBlockView* obj;
		obj = dynamic_cast<CProMoBlockView*>(GetSelectedObject());
		if (obj) {
			if (parent != NULL) {
				obj->getModel()->SetParentBlock(parent->getModel());
				parent->autoResize();
			}
		}
		CProMoEdgeView* edge;
		edge = dynamic_cast<CProMoEdgeView*>(GetSelectedObject());
		if (edge) {
			if (GetInteractMode() == MODE_RESIZING && GetSubMode() == DEHT_CENTER) {
				//take a snapshot to undo changes
				GetDiagramEntityContainer()->Snapshot();
				//split the edge into two
				CProMoEdgeView* newEdge = new CProMoEdgeView;
				//compute the length and position of both edges
				CRect edgeRect = edge->GetRect();
				CRect newEdgeRect(edgeRect);
				edgeRect.bottom = edgeRect.top + (edgeRect.Height() / 2);
				edgeRect.right = edgeRect.left + (edgeRect.Width() / 2);
				edge->SetRect(edgeRect);
				newEdgeRect.top = newEdgeRect.bottom - (newEdgeRect.Height() / 2);;
				newEdgeRect.left = newEdgeRect.right - (newEdgeRect.Width() / 2);;
				newEdge->SetRect(newEdgeRect);
				newEdge->Select(FALSE);
				//update edge links
				newEdge->SetDestination(edge->GetDestination());
				newEdge->SetSource(edge);
				newEdge->setModel(edge->getModel());
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

void CProMoEditor::OnLButtonUp(UINT nFlags, CPoint point) {

	CProMoBlockView* currObj = NULL;
	CProMoEntityContainer* objs = static_cast<CProMoEntityContainer*>(GetDiagramEntityContainer());

	if (GetInteractMode() == MODE_MOVING) {

		
		CProMoBlockView* selObj = NULL;
		//for each object being selected
		for (int i = 0; i < GetObjectCount(); i++) {
			selObj = dynamic_cast<CProMoBlockView*>(objs->GetAt(i));
			if (selObj) {
				if (selObj->IsSelected()) {
					//trigger mouse movement, so to maintain hierarchy in case no movement is made
					OnMouseMove(nFlags, point);
					//check which is the object being dropped, if any
					currObj = objs->getTarget();
					if (currObj) {
						if (selObj->getModel()->GetParentBlock() != currObj->getModel()) {
							// Set the parent to be that object
							selObj->getModel()->SetParentBlock(currObj->getModel());
						}
					}
					else	
					{
						//no object got hit, then the selected one has no parent
						selObj->getModel()->SetParentBlock(NULL);
					}
				}
			}
		}
		//Need to reorder shapes according to nesting
		static_cast<CProMoEntityContainer*>(objs)->reorder();
	}


	//bug: never called when a new object is created, whereas it should
	if (GetInteractMode() == MODE_RESIZING) {
		//resizing an edge
		CProMoEdgeView* edge = dynamic_cast<CProMoEdgeView*>(GetSelectedObject());
		if (edge) {
			currObj = objs->getTarget();
			if (currObj) {
				if (GetSubMode() == DEHT_BOTTOMRIGHT) {
					CProMoEdgeView* destEdge = dynamic_cast<CProMoEdgeView*>(edge->GetDestination());
					if (!destEdge) {
						edge->getModel()->SetDestination(currObj->getModel());
					}
				}
				else if (GetSubMode() == DEHT_TOPLEFT) {
					CProMoEdgeView* srcEdge = dynamic_cast<CProMoEdgeView*>(edge->GetSource());
					if (!srcEdge) {
						edge->getModel()->SetSource(currObj->getModel());
					}
				}
			}
			//no target, unlink models
			else {
				if (GetSubMode() == DEHT_BOTTOMRIGHT) {
					CProMoEdgeView* destEdge = dynamic_cast<CProMoEdgeView*>(edge->GetDestination());
					if (!destEdge) {
						edge->getModel()->SetDestination(NULL);
					}
				}
				else if (GetSubMode() == DEHT_TOPLEFT) {
					CProMoEdgeView* srcEdge = dynamic_cast<CProMoEdgeView*>(edge->GetSource());
					if (!srcEdge) {
						edge->getModel()->SetSource(NULL);
					}
				}
			}
			//Need to reorder shapes according to nesting
			static_cast<CProMoEntityContainer*>(objs)->reorder();
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
// CProMoEditor private helpers


CDiagramEntity* CProMoEditor::GetNamedObject(const CString& name) const
/* ============================================================
	Function :		CProMoEditor::GetNamedObject
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

	return result;

}

void CProMoEditor::Cut()
{
	CDiagramEntityContainer* objs = GetDiagramEntityContainer();
	if (objs)
	{
		objs->Snapshot();
		objs->CopyAllSelected();
		for (int i = 0; i < objs->GetSize(); i++) {
			CProMoBlockView* block = dynamic_cast<CProMoBlockView*>(objs->GetAt(i));
			if (block) {
				if (block->IsSelected()) {
					block->getModel()->UnlinkAllSubBlocks();
				}
			}

		}
		DeleteAllSelected();
	}
}

//draws blocks hierarchically: subblocks are always drawn in the foreground, regardless
//of current ordering, siblings follow the ordering in CProcessEntityContainer
void CProMoEditor::DrawObjectsR(CProMoBlockView* block, CDC* dc, double zoom) const
{
	int i = 0;
	block->DrawObject(dc, zoom);
	int count = GetObjectCount();
	for (i = 0; i < count; i++)
	{
		CProMoEntityContainer* objs = static_cast<CProMoEntityContainer*>(GetDiagramEntityContainer());
		CProMoBlockView* child = dynamic_cast<CProMoBlockView*>(objs->GetAt(i));
		if (child) {
			if (block->getModel()->Contains(child->getModel(), FALSE)) {
				DrawObjectsR(child, dc, zoom);
			}
		}
	}
	for (i = 0; i < block->getModel()->GetIncomingEdges()->GetSize(); i++) {
		CProMoEdgeView* edge = dynamic_cast<CProMoEdgeView*>(block->getModel()->GetIncomingEdges()->GetAt(i));
		if (edge) {
			edge->DrawObject(dc, zoom);
		}
	}
	for (i = 0; i < block->getModel()->GetOutgoingEdges()->GetSize(); i++) {
		CProMoEdgeView* edge = dynamic_cast<CProMoEdgeView*>(block->getModel()->GetOutgoingEdges()->GetAt(i));
		if (edge) {
			edge->DrawObject(dc, zoom);
		}
	}
}

void CProMoEditor::ResetTarget()
{
	CProMoEntityContainer* objs = static_cast<CProMoEntityContainer*>(GetDiagramEntityContainer());
	if (objs)
	{
		int count = 0;
		CProMoBlockView* obj;
		for (int i = 0; i < objs->GetSize(); i++) {
			obj = dynamic_cast<CProMoBlockView*>(objs->GetAt(i));
			SetTarget(obj, FALSE);
		}
	}
}

void CProMoEditor::SetTarget(CProMoBlockView* obj, BOOL select)
{
	if (obj) {
		CProMoEntityContainer* objs = static_cast<CProMoEntityContainer*>(GetDiagramEntityContainer());
		if (objs) {
			objs->SetTarget(obj, select);
		}
	}

}

void CProMoEditor::PrepareForAlignment() {

	CProMoBlockView* currObj = NULL;
	CProMoEntityContainer* objs = static_cast<CProMoEntityContainer*>(GetDiagramEntityContainer());
	CProMoBlockView* selObj = NULL;
	CProMoEdgeView* selEdge = NULL;

	for (int i = 0; i < GetObjectCount(); i++) {
		selObj = dynamic_cast<CProMoBlockView*>(objs->GetAt(i));
		if (selObj) {
			if (selObj->IsSelected()) {
				DeselectChildBlocks(selObj);
			}
		}
		selEdge = dynamic_cast<CProMoEdgeView*>(objs->GetAt(i));
		if (selEdge) {
			selEdge->Select(FALSE);
		}
	}
}

void CProMoEditor::AutoResizeAll()
{
	CProMoEntityContainer* objs = static_cast<CProMoEntityContainer*>(GetDiagramEntityContainer());
	CProMoBlockView* selObj = NULL;

	for (int i = 0; i < GetObjectCount(); i++) {
		selObj = dynamic_cast<CProMoBlockView*>(objs->GetAt(i));
		if (selObj) {
			selObj->autoResize();
		}
	}
	RedrawWindow();
}

CProMoModel* CProMoEditor::GetNamedModel(const CObArray& array, const CString& name) const
{
	CProMoModel* result = NULL;

	int count = static_cast<int>(array.GetSize());
	CProMoModel* obj;
	for (int t = 0; t < count; t++)
	{
		obj = dynamic_cast<CProMoModel*>(array.GetAt(t));
		if (obj && obj->GetName() == name)
			result = obj;
	}

	return result;
}

void CProMoEditor::DeleteModel(CObArray& array, const CString& name)
{
	int count = static_cast<int>(array.GetSize());
	CProMoModel* obj;
	for (int t = 0; t < count; t++)
	{
		obj = dynamic_cast<CProMoModel*>(array.GetAt(t));
		if (obj && obj->GetName() == name)
			array.RemoveAt(t);
	}
}


void CProMoEditor::LeftAlignSelected()
{
	PrepareForAlignment();
	CDiagramEditor::LeftAlignSelected();
	AutoResizeAll();	
}

void CProMoEditor::RightAlignSelected()
{
	PrepareForAlignment();
	CDiagramEditor::RightAlignSelected();
	AutoResizeAll();
}

void CProMoEditor::TopAlignSelected()
{
	PrepareForAlignment();
	CDiagramEditor::TopAlignSelected();
	AutoResizeAll();
}

void CProMoEditor::BottomAlignSelected()
{
	PrepareForAlignment();
	CDiagramEditor::BottomAlignSelected();
	AutoResizeAll();
}

void CProMoEditor::Load(const CStringArray& stra, CProMoControlFactory& fact)
{
	int max = static_cast<int>(stra.GetSize());
	int t = 0;

	CObArray models;

	//First read: create model and view elements
	for (t = 0; t < max; t++)
	{
		CString str = stra.GetAt(t);
		if (!FromString(str))
		{
			//check for unicity
			CDiagramEntity* obj = fact.CreateViewFromString(str);
			if (obj)
				if(!GetNamedObject(obj->GetName()))
					AddObject(obj);

			CProMoModel* model = fact.CreateModelFromString(str);
			if (model)
				if(!GetNamedModel(models, model->GetName()))
					models.Add(model);
		}
	}

	//Second read: create logical links between elements
	for (t = 0; t < max; t++)
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

				CString nodeName;
				CString modelName;

				CTokenizer tok(data.Left(data.GetLength() - 1));
				int size = tok.GetSize();

				if (size >= 1) {
					tok.GetAt(0, nodeName);
					
					//current element is a block view
					CProMoBlockView* blockView = dynamic_cast<CProMoBlockView*>(GetNamedObject(nodeName));
					if (blockView) {
						if (size >= 8) {
							tok.GetAt(7, modelName);
							CProMoBlockModel* blockModel = dynamic_cast<CProMoBlockModel*>(GetNamedModel(models, modelName));
							if (blockModel) {
								//required to avoid dangling pointers in case of malformed input files
								CProMoModel* oldMod = blockView->getModel();
								if(oldMod)
									DeleteModel(models, oldMod->GetName());
								blockView->setModel(blockModel);
							}
							else {
								//input file is malformed: create a new model to avoid inconsistencies
								blockView->setModel(new CProMoBlockModel);
							}
						}
					}
					
					//current element is an edge view
					CProMoEdgeView* edgeView = dynamic_cast<CProMoEdgeView*>(GetNamedObject(nodeName));
					if (edgeView) {

						if (size >= 10) {
							CString modelName;
							CString sourceName;
							CString destName;
							tok.GetAt(7, modelName);
							tok.GetAt(8, sourceName);
							tok.GetAt(9, destName);

							CProMoEdgeModel* edgeModel = dynamic_cast<CProMoEdgeModel*>(GetNamedModel(models, modelName));
							if (edgeModel) {
								CProMoModel* oldMod = edgeView->getModel();
								if (oldMod)
									DeleteModel(models, oldMod->GetName());
								edgeView->setModel(edgeModel);
							}
							else {
								//input file is malformed: create a new model to avoid inconsistencies
								edgeView->setModel(new CProMoEdgeModel);
							}

							CDiagramEntity* source = dynamic_cast<CDiagramEntity*>(GetNamedObject(sourceName));
							if (source) {
								edgeView->SetSource(source);
							}
							CDiagramEntity* dest = dynamic_cast<CDiagramEntity*>(GetNamedObject(destName));
							if (dest) {
								edgeView->SetDestination(dest);
							}
						}
					}

					//current element is a block model
					CProMoBlockModel* blockModel = dynamic_cast<CProMoBlockModel*>(GetNamedModel(models, nodeName));
					if (blockModel) {
						if (size >= 2) {
							CString parentName;
							tok.GetAt(1, parentName);

							CProMoBlockModel* parent = dynamic_cast<CProMoBlockModel*>(GetNamedModel(models, parentName));
							if (parent) {
								blockModel->SetParentBlock(parent);
							}
						}
					}

					//current element is an edge model
					CProMoEdgeModel* edgeModel = dynamic_cast<CProMoEdgeModel*>(GetNamedModel(models, nodeName));
					if (edgeModel) {
						if (size >= 3) {
							CString sourceName;
							CString destName;
							tok.GetAt(1, sourceName);
							tok.GetAt(2, destName);

							CProMoBlockModel* source = dynamic_cast<CProMoBlockModel*>(GetNamedModel(models, sourceName));
							if (source) {
								edgeModel->SetSource(source);
							}
							CProMoBlockModel* dest = dynamic_cast<CProMoBlockModel*>(GetNamedModel(models, destName));
							if (dest) {
								edgeModel->SetDestination(dest);
							}
						}
					}
				}

			}
		}
	}

}
