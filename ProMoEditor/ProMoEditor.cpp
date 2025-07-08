/* ==========================================================================
	CProMoEditor

	Author :		Giovanni Meroni

	Purpose :		CProMoEditor is a diagram editor that can handle nested
					blocks connected through edges. This class can be derived
					to implement a visual editor for a domain-specific
					language, or any language that can be generalized as a
					graph of nested nodes (e.g., UML State Chart diagrams, 
					Petri Nets, etc.). To achieve so, CProMoEditor extends
					CDiagramEditor.
	
	Description :	CProMoEditor handles several messages and overrides
					drawing to manage nested blocks and connected edges.
					Additionally, it decouples the visual representation
					of the elements from their structural properties, 
					according to the model-view principle. Therefore,
					edge-node and parent-child links are handled by the
					model classes, whereas their position and visual
					appearance on the canvas is handled by view classes.
					Model classes are not directly exposed. Instead, they
					can be accessed through their corresponding view 
					classes. The model-view decoupling also allows to
					associate multiple views for each model. This makes it
					possible to draw edges consisting in multiple linked 
					segments (each segment being a view), each segment 
					behaving like an independent line, yet all referring to 
					the same model.

	Usage :			CProMoEditor should be instantiated in the same way
					as a CDiagramEditor.

					The package uses RTTI (run time type information) to
					identify object types, using dynamic_cast, so the
					project must enable this feature.

   ========================================================================*/
#include "stdafx.h"
#include "ProMoEditor.h"
#include "ProMoEntityContainer.h"
#include "ProMoEdgeModel.h"
#include "../PropertyItem/PropertyWrappers.h"
#include "../PropertyItem/CustomPropertyItem.h"
#include "../PropertyItem/TypedPropertyItem.h"

#include <math.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

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

	CProMoEntityContainer* objs = static_cast<CProMoEntityContainer*>(GetDiagramEntityContainer());
	if (objs) {
		objs->SaveObjects(stra);
	}
}


CProMoBlockView* CProMoEditor::GetTargetBlock(CPoint point) 
/* ============================================================
	Function :		CProMoEditor::GetTargetBlock
	Description :	Gets the topmost block that contains the
					input point
	Access :		Protected

	Return :		CProMoBlockView*	-	Pointer to the target
											block
	Parameters :	CPoint point		-	Point to identify the 
											target block

   ============================================================*/
{
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
					if ((GetInteractMode() == MODE_DRAWING)) {
						// new block
						CProMoBlockView* newObj = dynamic_cast<CProMoBlockView*>(GetDrawingObject());
						if (newObj) {
							if (newObj->GetModel()->CanBeNested(currObj->GetModel())) {
								return currObj;
							}
						}
						// new edge
						CProMoEdgeView* newEdge = dynamic_cast<CProMoEdgeView*>(GetDrawingObject());
						if (newEdge) {
							if (newEdge->GetModel()->CanConnectSource(currObj->GetModel())) {
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
									if (!(selObj->GetModel()->CanBeNested(currObj->GetModel()))) {
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
								if (edge->GetModel()->CanConnectDestination(currObj->GetModel())) {
									return currObj;
								}
							}
							else if (GetSubMode() == DEHT_TOPLEFT) {
								if (edge->GetModel()->CanConnectSource(currObj->GetModel())) {
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

CProMoBlockView* CProMoEditor::GetConnectedBlock(CProMoEdgeView* line, BOOL backwards)
/* ============================================================
	Function :		CProMoEditor::GetConnectedBlock
	Description :	Gets the block that is connected to the
					input edge.
	Access :		Protected


	Return :		CProMoBlockView*		-	Pointer to the
												connected block
	Parameters :	CProMoEdgeView* line	-	Pointer to the
												edge
					BOOL backwards			-	TRUE if the edge
												should be
												explored
												backwards (i.e.,
												the source edge
												needs to be
												found)

   ============================================================*/
{
	CProMoBlockModel* model = NULL;
	if (backwards) {
		model = dynamic_cast<CProMoBlockModel*>(line->GetModel()->GetSource());
		if (model) {
			return model->GetMainView();
		}
	}
	else {
		model = dynamic_cast<CProMoBlockModel*>(line->GetModel()->GetDestination());
		if (model) {
			return model->GetMainView();
		}
	}

	return NULL;
}

void CProMoEditor::DeselectChildBlocks(CProMoBlockView* block)
/* ============================================================
	Function :		CProMoEditor::DeselectChildBlocks
	Description :	Recursively deselects all blocks that are 
					children of the input block.
	Access :		Protected


	Return :		void
	Parameters :	CProMoBlockView* block	-	Pointer to the
												block

   ============================================================*/
{
	ASSERT(block->GetModel()!=NULL);
	CProMoBlockModel* model = block->GetModel();
	for (int i = 0; i < model->GetSubBlocks()->GetSize(); i++) {
		CProMoBlockModel* subBlock = dynamic_cast<CProMoBlockModel*>(model->GetSubBlocks()->GetAt(i));
		subBlock->GetMainView()->Select(FALSE);
		DeselectChildBlocks(subBlock->GetMainView());
	}
}

void CProMoEditor::SelectChildBlocks(CProMoBlockView* block)
/* ============================================================
	Function :		CProMoEditor::DeselectChildBlocks
	Description :	Recursively selects all blocks that are 
					children of the input block.
	Access :		Protected


	Return :		void
	Parameters :	CProMoBlockView* block	-	Pointer to the
												block

   ============================================================*/
{
	ASSERT(block->GetModel() != NULL);
	CProMoBlockModel* model = block->GetModel();
	for (int i = 0; i < model->GetSubBlocks()->GetSize(); i++) {
		CProMoBlockModel* subBlock = dynamic_cast<CProMoBlockModel*>(model->GetSubBlocks()->GetAt(i));
		subBlock->GetMainView()->Select(TRUE);
		SelectChildBlocks(subBlock->GetMainView());
	}
}


void CProMoEditor::OnMouseMove(UINT nFlags, CPoint point)
/* ============================================================
	Function :		CProMoEditor::OnMouseMove
	Description :	Handler for WM_MOUSEMOVE. 
					Overridden to identify target block for 
					elements being drawn/moved/resized, to keep
					linked elements connected, and to handle
					SHIFT/CTRL keys to keep proportions.

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
					CProMoBlockView* block = GetConnectedBlock(currObj, TRUE);
					if (block) {
						if (!block->IsSelected()) {
							currObj->Select(FALSE);
						}
					}
					else {
						currObj->Select(FALSE);
					}
					block = GetConnectedBlock(currObj, FALSE);
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

		CProMoBlockView* block = dynamic_cast<CProMoBlockView*>(element);
		if (block) {
			//handle shift key for nodes: keep proportions
			//note: always enabled if the block says so
			if ((nFlags & MK_SHIFT) == MK_SHIFT || block->HasLockedProportions()) {
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

			// handle shift key for edges: mainly snap them to horizontal, vertical or 45 degrees diagonal lines
			if ((nFlags & MK_SHIFT) == MK_SHIFT) {
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
/* ============================================================
	Function :		CProMoEditor::OnLButtonDown
	Description :	Handles the "WM_LBUTTONDOWN" message. We
					select/deselect objects and set internal
					modes as appropriate.
					Overridden to support splitting an edge
					into two connected segments by clicking on
					the center marker.
	Access :		Protected

	Return :		void
	Parameters :	UINT nFlags		-	Key-down flag
					CPoint point	-	Mouse position

	Usage :			Called from MFC. Do not call from code.

   ============================================================*/
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
				obj->GetModel()->SetParentBlock(parent->GetModel());
				parent->AutoResize();
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
				newEdge->SetModel(edge->GetModel());
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


void CProMoEditor::OnLButtonUp(UINT nFlags, CPoint point) 
/* ============================================================
	Function :		CProMoEditor::OnLButtonUp
	Description :	Handles the "WM_LBUTTONUP" message.
					Overridden to set parent block for current
					block being draw/moved, and source/target 
					block for current edge being drawn/resized.
	Access :		Protected

	Return :		void
	Parameters :	UINT nFlags		-	not interested.
					CPoint point	-	The position of the mouse.

	Usage :			Called from MFC. Do not call from code.

   ============================================================*/
{

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
					currObj = objs->GetTarget();
					if (currObj) {
						if (selObj->GetModel()->GetParentBlock() != currObj->GetModel()) {
							// Set the parent to be that object
							selObj->GetModel()->SetParentBlock(currObj->GetModel());
						}
					}
					else	
					{
						//no object got hit, then the selected one has no parent
						selObj->GetModel()->SetParentBlock(NULL);
					}
				}
			}
		}
		//Need to reorder shapes according to nesting
		static_cast<CProMoEntityContainer*>(objs)->Reorder();
	}


	//bug: never called when a new object is created, whereas it should
	if (GetInteractMode() == MODE_RESIZING) {
		//resizing an edge
		CProMoEdgeView* edge = dynamic_cast<CProMoEdgeView*>(GetSelectedObject());
		if (edge) {
			currObj = objs->GetTarget();
			if (currObj) {
				if (GetSubMode() == DEHT_BOTTOMRIGHT) {
					CProMoEdgeView* destEdge = dynamic_cast<CProMoEdgeView*>(edge->GetDestination());
					if (!destEdge) {
						edge->GetModel()->SetDestination(currObj->GetModel());
					}
				}
				else if (GetSubMode() == DEHT_TOPLEFT) {
					CProMoEdgeView* srcEdge = dynamic_cast<CProMoEdgeView*>(edge->GetSource());
					if (!srcEdge) {
						edge->GetModel()->SetSource(currObj->GetModel());
					}
				}
			}
			//no target, unlink models
			else {
				if (GetSubMode() == DEHT_BOTTOMRIGHT) {
					CProMoEdgeView* destEdge = dynamic_cast<CProMoEdgeView*>(edge->GetDestination());
					if (!destEdge) {
						edge->GetModel()->SetDestination(NULL);
					}
				}
				else if (GetSubMode() == DEHT_TOPLEFT) {
					CProMoEdgeView* srcEdge = dynamic_cast<CProMoEdgeView*>(edge->GetSource());
					if (!srcEdge) {
						edge->GetModel()->SetSource(NULL);
					}
				}
			}
			//Need to reorder shapes according to nesting
			static_cast<CProMoEntityContainer*>(objs)->Reorder();
		}
	}

	//reset target, so that blocks appear as normal
	ResetTarget();

	CDiagramEditor::OnLButtonUp(nFlags, point);
	//do the auto-resize on all blocks
	AutoResizeAll();
	//notify that the selected object has changed
	NotifySelectionChanged();
	RedrawWindow();
}




void CProMoEditor::Cut()
/* ============================================================
	Function :		CProMoEditor::Cut
	Description :	Cut the currently selected items to the
					internal "CProMoEntityContainer" clipboard.
					Overridden to unlink subblocks if 
					individually selected.
	Access :		Public

	Return :		void
	Parameters :	none

	Usage :			Call to delete and place the currently
					selected objects to the 'clipboard'.

   ============================================================*/
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
					block->GetModel()->UnlinkAllSubBlocks();
				}
			}

		}
		DeleteAllSelected();
	}
}

void CProMoEditor::DrawObjectsR(CProMoBlockView* block, CDC* dc, double zoom) const
/* ============================================================
	Function :		CProMoEditor::DrawObjectsR
	Description :	Draws the input block and connected elements
					hierarchically: subblocks are always drawn 
					in the foreground, regardless of current 
					ordering, siblings follow the ordering 
					in CProcessEntityContainer
	Access :		Protected

	Return :		void
	Parameters :	CProMoBlockView* block	-	Pointer to the
												block
					CDC* dc					-	CDC to draw to
					double zoom				-	Zoom level 
												(use this value
												instead of 
												GetZoom())

   ============================================================*/
{
	int i = 0;
	block->DrawObject(dc, zoom);
	int count = GetObjectCount();
	for (i = 0; i < count; i++)
	{
		CProMoEntityContainer* objs = static_cast<CProMoEntityContainer*>(GetDiagramEntityContainer());
		CProMoBlockView* child = dynamic_cast<CProMoBlockView*>(objs->GetAt(i));
		if (child) {
			if (block->GetModel()->Contains(child->GetModel(), FALSE)) {
				DrawObjectsR(child, dc, zoom);
			}
		}
	}
	for (i = 0; i < block->GetModel()->GetIncomingEdges()->GetSize(); i++) {
		CProMoEdgeView* edge = dynamic_cast<CProMoEdgeView*>(block->GetModel()->GetIncomingEdges()->GetAt(i));
		if (edge) {
			edge->DrawObject(dc, zoom);
		}
	}
	for (i = 0; i < block->GetModel()->GetOutgoingEdges()->GetSize(); i++) {
		CProMoEdgeView* edge = dynamic_cast<CProMoEdgeView*>(block->GetModel()->GetOutgoingEdges()->GetAt(i));
		if (edge) {
			edge->DrawObject(dc, zoom);
		}
	}
}

void CProMoEditor::ResetTarget()
/* ============================================================
	Function :		CProMoEditor::ResetTarget
	Description :	Unsets the target for the current drawing 
					operation
	Access :		Protected

	Return :		void
	Parameters :	none

   ============================================================*/
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
/* ============================================================
	Function :		CProMoEditor::SetTarget
	Description :	Makes the block being passed as input a
					target for the current drawing operation
					(e.g., when dragging another object over
					it)
	Access :		Protected

	Return :		void
	Parameters :	CProMoBlockView* obj	-	Pointer to the
												block
					BOOL select				-	"TRUE" if the
												block should be
												the target

   ============================================================*/
{
	if (obj) {
		CProMoEntityContainer* objs = static_cast<CProMoEntityContainer*>(GetDiagramEntityContainer());
		if (objs) {
			objs->SetTarget(obj, select);
		}
	}

}

void CProMoEditor::PrepareForAlignment() 
/* ============================================================
	Function :		CProMoEditor::PrepareForAlignment
	Description :	Deselects child blocks and selects 
					connected edges, so that they are correctly
					moved when the alignment takes place.
	Access :		Protected

	Return :		void
	Parameters :	none

   ============================================================*/
{

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
/* ============================================================
	Function :		CProMoEditor::AutoResizeAll
	Description :	Automatically resizes all blocks to prevent
					child blocks from protruding.
	Access :		Protected

	Return :		void
	Parameters :	none

   ============================================================*/
{
	CProMoEntityContainer* objs = static_cast<CProMoEntityContainer*>(GetDiagramEntityContainer());
	CProMoBlockView* selObj = NULL;

	for (int i = 0; i < GetObjectCount(); i++) {
		selObj = dynamic_cast<CProMoBlockView*>(objs->GetAt(i));
		if (selObj) {
			selObj->AutoResize();
		}
	}
	RedrawWindow();
}



void CProMoEditor::LeftAlignSelected()
/* ============================================================
	Function :		CProMoEditor::LeftAlignSelected
	Description :	Aligns all selected objects to the left of
					the top selected object in the data container.
					Overridden to handle child blocks and
					connected edges.
	Access :		Public

	Return :		void
	Parameters :	none

	Usage :			Call to align the left edge of all selected
					objects.
					Should only be callable if "GetSelectCount() >
					1", that is, more than one object is selected.

   ============================================================*/
{
	PrepareForAlignment();
	CDiagramEditor::LeftAlignSelected();
	AutoResizeAll();	
}

void CProMoEditor::RightAlignSelected()
/* ============================================================
	Function :		CProMoEditor::RightAlignSelected
	Description :	Aligns all selected objects to the right of
					the top selected object in the data container.
					Overridden to handle child blocks and
					connected edges.
	Access :		Public

	Return :		void
	Parameters :	none

	Usage :			Call to align the right edge of all selected
					objects.
					Should only be callable if "GetSelectCount() >
					1", that is, more than one object is selected.

   ============================================================*/
{
	PrepareForAlignment();
	CDiagramEditor::RightAlignSelected();
	AutoResizeAll();
}

void CProMoEditor::TopAlignSelected()
/* ============================================================
	Function :		CProMoEditor::TopAlignSelected
	Description :	Aligns all selected objects to the top of
					the top selected object in the data container.
					Overridden to handle child blocks and
					connected edges.
	Access :		Public

	Return :		void
	Parameters :	none

	Usage :			Call to align the top edge of all selected
					objects.
					Should only be callable if "GetSelectCount() >
					1", that is, more than one object is selected.

   ============================================================*/
{
	PrepareForAlignment();
	CDiagramEditor::TopAlignSelected();
	AutoResizeAll();
}

void CProMoEditor::BottomAlignSelected()
/* ============================================================
	Function :		CProMoEditor::BottomAlignSelected
	Description :	Aligns all selected objects to the bottom of
					the top selected object in the data container.
					Overridden to handle child blocks and
					connected edges.
	Access :		Public

	Return :		void
	Parameters :	none

	Usage :			Call to align the bottom edge of all selected
					objects.
					Should only be callable if "GetSelectCount() >
					1", that is, more than one object is selected.

   ============================================================*/
{
	PrepareForAlignment();
	CDiagramEditor::BottomAlignSelected();
	AutoResizeAll();
}

void CProMoEditor::Load(const CStringArray& stra, CProMoControlFactory* fact)
/* ============================================================
	Function :		CProMoEditor::Load
	Description :	Sets the container properties (normally 
					the virtual size) and creates objects from 
					their string representation in "stra".
	Access :		Public

	Return :		void
	Parameters :	CStringArray& stra			-	The array 
													to read
					CProMoControlFactory& fact	-	The factory
													object to
													create
													objects

	Usage :			Call to load the data of the editor from a
					"CStringArray". Virtual. Can be overridden in
					a derived class to add non-container data
					before and after the objects

   ============================================================*/
{
	CProMoEntityContainer* objs = static_cast<CProMoEntityContainer*>(GetDiagramEntityContainer());
	if (objs)
		objs->Load(stra, fact);

}

void CProMoEditor::NotifySelectionChanged()
/* ============================================================
	Function :		CProMoEditor::NotifySelectionChanged
	Description :	Notifies that the selected object has
					changed.
	Access :		Public

	Return :		void
	Parameters :	none

	Usage :			Call whenever the selected object(s) is 
					changed.

   ============================================================*/
{
	CDiagramEntity* pSelectedEntity = GetSelectedObject();

	CObArray* pProps = new CObArray();

	if (pSelectedEntity)
	{
		// Example: create property items with wrappers defined in this class
		CString title = pSelectedEntity->GetTitle(); // example getter
		CString name = pSelectedEntity->GetName();

		// Create a property item for "Title"
		CTypedPropertyItem<CString>* pTitle = new CTypedPropertyItem<CString>(_T("Title"), pSelectedEntity, this, &SetShapeTitle, title);
		pTitle->AddOption("Foo");
		pTitle->AddOption("Bar");
		pProps->Add(pTitle);

		// Create a property item for "Name"
		pTitle = new CTypedPropertyItem<CString>(_T("Name"), pSelectedEntity, this, &SetShapeName, name);
		pProps->Add(pTitle);

	}

	// Get main frame window
	CWnd* pMainFrame = AfxGetMainWnd();
	if (pMainFrame && ::IsWindow(pMainFrame->GetSafeHwnd()))
	{
		// Send message asynchronously to avoid blocking (optional)
		pMainFrame->PostMessage(WM_SELECTION_CHANGED, 0, (LPARAM)pProps);
	}
}