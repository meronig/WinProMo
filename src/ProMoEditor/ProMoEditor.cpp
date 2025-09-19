/* ==========================================================================

	Copyright © 2025 Technical University of Denmark

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
#include "../GeometryUtils/GeometryHelper.h"

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
	m_pageBreaksVisible = TRUE;
	m_paperSize = CSize(0,0);
	m_printResolutionX = 0;
	m_printResolutionY = 0;
	SetMargins(0,0,0,0);
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
	CProMoEntityContainer* objs = static_cast<CProMoEntityContainer*>(GetDiagramEntityContainer());
	for (int j = GetObjectCount() - 1; j >= 0; j--) {
		CProMoBlockView* currObj = dynamic_cast<CProMoBlockView*>(objs->GetAt(j));

		if (currObj) {
			ScreenToVirtual(point);
			int hitCode = currObj->GetHitCode(point);
			if (hitCode == DEHT_BODY) {
				// We found the object that was clicked
				if (!currObj->IsSelected()) {
					//drawing a new element
					if ((GetInteractMode() == MODE_DRAWING)) {
						// new block
						CProMoBlockView* newObj = dynamic_cast<CProMoBlockView*>(GetDrawingObject());
						if (newObj) {
							if (newObj->GetModel()->CanBeNestedBy(currObj->GetModel())) {
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
									if (!(selObj->GetModel()->CanBeNestedBy(currObj->GetModel()))) {
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

void CProMoEditor::DeselectInvalidElements() 
/* ============================================================
	Function :		CProMoEditor::DeselectInvalidElements
	Description :	Deselect elements that would break the 
					model consistency when moved all at once.
	Access :		Protected


	Return :		void
   ============================================================*/
{
	CProMoBlockView* selObj = NULL;
	CProMoEdgeView* selEdge = NULL;

	// deselect edges to prevent them from being moved only when no attached block is selected (on both ends)
	// also, deselect nested blocks to avoid reassigning the parent
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
		//BUG: when moving two child blocks, cannot determine target

		DeselectInvalidElements();
		
		CDiagramEditor::OnMouseMove(nFlags, point);

	}
	else if (GetInteractMode() == MODE_RESIZING){

		CDiagramEntity* element = GetSelectedObject();
		CDoubleRect oldRect;

		if (element) {
			oldRect.SetRect(element->GetLeft(), element->GetTop(), element->GetRight(), element->GetBottom());
		}

		CDiagramEditor::OnMouseMove(nFlags, point);

		CProMoBlockView* block = dynamic_cast<CProMoBlockView*>(element);
		if (block) {
			//handle shift key for nodes: keep proportions
			//note: always enabled if the block says so
			if ((nFlags & MK_SHIFT) == MK_SHIFT || block->HasLockedProportions()) {
				CDoubleRect newRect(block->GetLeft(), block->GetTop(), block->GetRight(), block->GetBottom());
				CGeometryHelper::EnforceAspectRatio(oldRect, newRect, GetSubMode(), point);
				block->SetRect(newRect.left, newRect.top, newRect.right, newRect.bottom);
			}
		}
	
		CProMoEdgeView* edge = dynamic_cast<CProMoEdgeView*>(element);
		if (edge) {

			// handle shift key for edges: mainly snap them to horizontal, vertical or 45 degrees diagonal lines
			if ((nFlags & MK_SHIFT) == MK_SHIFT) {
				CDoubleRect newRect(edge->GetLeft(), edge->GetTop(), edge->GetRight(), edge->GetBottom());
				CGeometryHelper::AlignToAxis(newRect, GetSubMode());
				edge->SetRect(newRect.left, newRect.top, newRect.right, newRect.bottom);
			}

		}
	}
	else {
		CDiagramEditor::OnMouseMove(nFlags, point);
	}

	if (GetInteractMode() == MODE_MOVING || GetInteractMode() == MODE_RESIZING || IsDrawing())
	{
		ResetTarget();
		CProMoBlockView* targetBlock = GetTargetBlock(point);
		if (targetBlock) {
			targetBlock->SetTarget(TRUE);
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
	CProMoBlockView* target = NULL;

	if (IsDrawing()) {

		//by default, where we click is topleft for a line
		//bottomdown is the resize mode set afterwards

		if (objs) {
			UnselectAll();
			// Identify clicked block (if any)
			ResetTarget();
			target = GetTargetBlock(point);
		}
	}

	// Create a new element as usual
	CDiagramEditor::OnLButtonDown(nFlags, point);
	
	if (target) {
		NestSelectedBlock(target);
		ConnectSelectedEdgeToSource(target);
	}
	SplitSelectedEdge();

	
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

		OnMouseMove(nFlags, point);
		NestSelectedBlock(objs->GetTarget());
		
	}

	if (GetInteractMode() == MODE_RESIZING) {
		if (GetSubMode() == DEHT_BOTTOMRIGHT) {
			ConnectSelectedEdgeToDestination(objs->GetTarget());
		}
		else if (GetSubMode() == DEHT_TOPLEFT) {
			ConnectSelectedEdgeToSource(objs->GetTarget());
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

void CProMoEditor::OnLButtonDblClk(UINT nFlags, CPoint point)
/* ============================================================
	Function :		CProMoEditor::OnLButtonDblClk
	Description :	Handles the "WM_LBUTTONDBLCLK" message.
	Access :		Protected

	Return :		void
	Parameters :	UINT nFlags		-	not interested
					CPoint point	-	not interested

	Usage :			Called from MFC. Do not call from code.

	============================================================*/
{

	CWnd::OnLButtonDblClk(nFlags, point);

}

void CProMoEditor::Draw(CDC* dc, CRect rect) const
/* ============================================================
	Function :		CProMoEditor::Draw
	Description :	Calls a series of (virtual) functions to
					draw to "dc". "rect" is the total rectangle
					to draw to.
					Overridden to draw page breaks when active.
	Access :		Public

	Return :		void
	Parameters :	CDC* dc		-	The "CDC" to draw to.
					CRect rect	-	The complete rectangle
									(including non-visible areas)

	Usage :			Should not normally be called from user code.
					Can be called to draw the complete window.
					Can be overriden to change drawing order.

   ============================================================*/
{
	CDiagramEditor::Draw(dc, rect);

	double zoom = GetZoom();

	if (m_pageBreaksVisible) {
		DrawPageBreaks(dc, rect, zoom);
	}
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
		//Unlink child blocks if not selected, to avoid them being deleted
		for (int i = 0; i < objs->GetSize(); i++) {
			CProMoBlockView* block = dynamic_cast<CProMoBlockView*>(objs->GetAt(i));
			if (block) {
				if (block->IsSelected()) {
					block->UnlinkAllSubBlocks();
				}
			}
		}
		DeleteAllSelected();
	}
}

void CProMoEditor::Paste()
/* ============================================================
	Function :		CProMoEditor::Paste
	Description :	Paste copied or cut objects to the screen.
					Overridden to update property panel.
	Access :		Public

	Return :		void
	Parameters :	none

	Usage :			Call to paste the contents of the clipboard
					to the screen.

   ============================================================*/
{

	CDiagramEditor::Paste();
	NotifySelectionChanged();

}

void CProMoEditor::Undo()
/* ============================================================
	Function :		CProMoEditor::Undo
	Description :	Undo the last operation.
					Overridden to update property panel.
	Access :		Public

	Return :		void
	Parameters :	none

	Usage :			Call to restore the objects to the last
					snapshot.

   ============================================================*/
{
	
	CDiagramEditor::Undo();
	NotifySelectionChanged();

}

void CProMoEditor::Redo()
/* ============================================================
	Function :		CProMoEditor::Redo
	Description :	Redo the last operation.
					Overridden to update property panel.
	Access :		Public

	Return :		void
	Parameters :	none

	Usage :			Call to redo an undo.

   ============================================================*/
{

	CDiagramEditor::Redo();
	NotifySelectionChanged();

}

void CProMoEditor::UnselectAll()
/* ============================================================
	Function :		CProMoEditor::UnselectAll
	Description :	Unselects all objects in the container.
					Overridden to update property panel.
	Access :		Public

	Return :		void
	Parameters :	none

	Usage :			Call to unselect all objects.
					Should not be callable if "GetObjectCount()
					== 0" (there are no objects in the container).

   ============================================================*/
{

	CDiagramEditor::UnselectAll();
	NotifySelectionChanged();

}

void CProMoEditor::SelectAll()
/* ============================================================
	Function :		CProMoEditor::SelectAll
	Description :	Selects all objects.
					Overridden to update property panel.
	Access :		Public

	Return :		void
	Parameters :	none

	Usage :			Call to select all objects.
					Should not be callable if "GetObjectCount()
					== 0" (there are no objects in the container).

   ============================================================*/
{

	CDiagramEditor::SelectAll();
	NotifySelectionChanged();

}

void CProMoEditor::DeleteAllSelected()
/* ============================================================
	Function :		CProMoEditor::DeleteAllSelected
	Description :	Deletes all selected objects from the
					container.
	Access :		Public

	Return :		void
	Parameters :	none

	Usage :			Call to delete all selected objects from the
					editor. Should not be callable if
					"GetSelectCount() == 0" ( or "IsAnyObjectSelected()
					== FALSE" )

   ============================================================*/
{

	CDiagramEditor::DeleteAllSelected();
	NotifySelectionChanged();

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

void CProMoEditor::NestSelectedBlock(CProMoBlockView* parentBlock)
/* ============================================================
	Function :		CProMoEditor::NestNewBlock
	Description :	Nests the currently selected block (if any)
					inside a parent block
	Access :		Protected

	Return :		void
	Parameters :	CProMoBlockView* parentBlock	-	Pointer 
														to the
														parent
														block

   ============================================================*/
{
	
	CProMoEntityContainer* objs = static_cast<CProMoEntityContainer*>(GetDiagramEntityContainer());

	CProMoBlockView* selObj = NULL;
	//for each object being selected
	for (int i = 0; i < GetObjectCount(); i++) {
		selObj = dynamic_cast<CProMoBlockView*>(objs->GetAt(i));
		if (selObj) {
			if (selObj->IsSelected()) {
				//check which is the object being dropped, if any
				if (parentBlock) {
					if (selObj->GetModel()->GetParentBlock() != parentBlock->GetModel()) {
						// Set the parent to be that object
						selObj->SetParentBlock(parentBlock);
					}
				}
				else
				{
					//no object got hit, then the selected one has no parent
					selObj->SetParentBlock(NULL);
				}
			}
		}
	}
	//Need to reorder shapes according to nesting
	objs->Reorder();

}

void CProMoEditor::SplitSelectedEdge()
/* ============================================================
	Function :		CProMoEditor::SplitSelectedEdge
	Description :	If the center of an edge has been clicked, 
					splits the edge into two and sets the 
					editor for resizing the original edge
	Access :		Protected

	Return :		void
	
   ============================================================*/
{
	if (GetSelectedObject() != NULL) {
		CProMoEdgeView* edge;
		edge = dynamic_cast<CProMoEdgeView*>(GetSelectedObject());
		if (edge) {
			// We need to split the edge into two.
			if (GetInteractMode() == MODE_RESIZING && GetSubMode() == DEHT_CENTER) {
				//take a snapshot to undo changes
				GetDiagramEntityContainer()->Snapshot();
				//split the edge into two
				CProMoEdgeView* newEdge = edge->Split();
				//add new edge
				AddObject(newEdge);
				//switch to resizing the old edge
				SetInteractMode(MODE_RESIZING, DEHT_BOTTOMRIGHT);
			}
		}
	}
}

void CProMoEditor::ConnectSelectedEdgeToSource(CProMoBlockView* sourceBlock)
/* ============================================================
	Function :		CProMoEditor::ConnectSelectedEdgeToSource
	Description :	Connects the currently selected edge 
					(if any) to a source block 
	Access :		Protected

	Return :		void
	Parameters :	CProMoBlockView* sourceBlock	-	Pointer
														to the
														source
														block

   ============================================================*/
{
	CProMoEntityContainer* objs = static_cast<CProMoEntityContainer*>(GetDiagramEntityContainer());
	// Get the element being created (which will be selected)
	if (GetSelectedObject() != NULL) {
		CProMoEdgeView* edge;
		edge = dynamic_cast<CProMoEdgeView*>(GetSelectedObject());
		if (edge) {
			//check if the current edge view is the first segment
			CProMoEdgeView* srcEdge = dynamic_cast<CProMoEdgeView*>(edge->GetSource());
			if (!srcEdge) {
				if (!(GetInteractMode() == MODE_RESIZING && GetSubMode() == DEHT_CENTER)) {
					if (sourceBlock != NULL) {
						edge->SetSource(sourceBlock);
					}
					else {
						edge->SetSource(NULL);
					}
					//Need to reorder shapes according to nesting
					objs->Reorder();
				}
			}
		}
	}
}

void CProMoEditor::ConnectSelectedEdgeToDestination(CProMoBlockView* destBlock)
/* ============================================================
	Function :		CProMoEditor::ConnectSelectedEdgeToDestination
	Description :	Connects the currently selected edge
					(if any) to a destination block
	Access :		Protected

	Return :		void
	Parameters :	CProMoBlockView* destBlock	-	Pointer to
													the
													destination
													block

   ============================================================*/
{
	CProMoEntityContainer* objs = static_cast<CProMoEntityContainer*>(GetDiagramEntityContainer());
	// Get the element being created (which will be selected)
	if (GetSelectedObject() != NULL) {
		CProMoEdgeView* edge;
		edge = dynamic_cast<CProMoEdgeView*>(GetSelectedObject());
		if (edge) {
			//check if the current edge view is the last segment
			CProMoEdgeView* destEdge = dynamic_cast<CProMoEdgeView*>(edge->GetDestination());
			if (!destEdge) {
				if (!(GetInteractMode() == MODE_RESIZING && GetSubMode() == DEHT_CENTER)) {
					if (destBlock != NULL) {
						edge->SetDestination(destBlock);
					}
					else {
						edge->SetDestination(NULL);
					}
					//Need to reorder shapes according to nesting
					objs->Reorder();
				}
			}
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

CObArray* CProMoEditor::GetProperties(CDiagramEntity* element)
/* ============================================================
	Function :		CProMoEditor::GetProperties
	Description :	Returns changeable propertis for the 
					object specified.
	Access :		Protected

	Return :		CObArray*				-	Properties for
												the element
	Parameters :	CDiagramEntity* element	-	Element whose
												properties need
												to be collected

	Usage :			Override to change the properties.

   ============================================================*/
{
	CObArray* pProps = new CObArray();

	// Example: create property items with wrappers defined in this class
	CString title = element->GetTitle(); // example getter
	CString name = element->GetName();

	// Create a property item for "Title"
	CTypedPropertyItem<CString>* pTitle = new CTypedPropertyItem<CString>(_T("Title"), element, this, &SetShapeTitle, title);
	pProps->Add(pTitle);

	// Create a property item for "Name"
	pTitle = new CTypedPropertyItem<CString>(_T("Name"), element, this, &SetShapeName, name);
	pProps->Add(pTitle);

	return pProps;
}

void CProMoEditor::DrawPageBreaks(CDC* dc, CRect rect, double zoom) const
/* ============================================================
	Function :		CProMoEditor::DrawPageBreaks
	Description :	Draws visual indicators for page breaks
	Access :		Protected

	Return :		void
	Parameters :	CDC* dc		-	"CDC" to draw to.
					CRect rect	-	Total rect to draw to.
					double zoom	-	Current zoom level.
									Coordinates can be
									multiplied with this value
									to get scaled.

	Usage :			Virtual. Can be overridden in a derived
					class to draw the page breaks. Will not be 
					called if page breaks is not visible.

   ============================================================*/
{

	// Convert to screen units

	double xzoom = zoom * (dc->GetDeviceCaps(LOGPIXELSX)) / m_printResolutionX;
	double yzoom = zoom * (dc->GetDeviceCaps(LOGPIXELSY)) / m_printResolutionY;

	if (m_printableArea.cx == 0 || m_printableArea.cy == 0)
		return;

	CPen pen(PS_DOT, 1, RGB(200, 200, 200));
	CPen* pOldPen = dc->SelectObject(&pen);

	CSize scaledPaperSize;
	
	scaledPaperSize.cx = m_printableArea.cx * xzoom;
	scaledPaperSize.cy = m_printableArea.cy * yzoom;

	int nHorzPages = (rect.Width() + scaledPaperSize.cx - 1) / scaledPaperSize.cx;
	int nVertPages = (rect.Height() + scaledPaperSize.cy - 1) / scaledPaperSize.cy;

	int i;
	// Draw vertical lines
	for (i = 1; i < nHorzPages; ++i)
	{
		int x = i * scaledPaperSize.cx;
		dc->MoveTo(x, 0);
		dc->LineTo(x, rect.Height());
	}

	// Draw horizontal lines
	for (i = 1; i < nVertPages; ++i)
	{
		int y = i * scaledPaperSize.cy;
		dc->MoveTo(0, y);
		dc->LineTo(rect.Width(), y);
	}

	dc->SelectObject(pOldPen);

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

void CProMoEditor::MiddleAlignSelected()
/* ============================================================
	Function :		CProMoEditor::MiddleAlignSelected
	Description :	Aligns all selected objects to the middle of
					the top selected object in the data container.
	Access :		Public

	Return :		void
	Parameters :	none

	Usage :			Call to align the middle of all selected
					objects.
					Should only be callable if "GetSelectCount() >
					1", that is, more than one object is selected.

   ============================================================*/
{
	PrepareForAlignment();

	if (GetSelectCount() > 1)
	{
		GetDiagramEntityContainer()->Snapshot();
		CDiagramEntity* obj = GetSelectedObject();
		if (obj)
		{
			double middle = (obj->GetTop() + obj->GetBottom()) / (double)2;
			int count = 0;
			while ((obj = GetDiagramEntityContainer()->GetAt(count++)))
			{
				if (obj->IsSelected())
				{
					double height = obj->GetBottom() - obj->GetTop();
					double bottom = middle + height / 2;
					double top = middle - height / 2;
					obj->SetRect(obj->GetLeft(), top, obj->GetRight(), bottom);
				}
			}

		}
		SetModified(TRUE);
		RedrawWindow();
	}

	AutoResizeAll();
}

void CProMoEditor::CenterAlignSelected()
/* ============================================================
	Function :		CProMoEditor::CenterAlignSelected
	Description :	Aligns all selected objects to the center of
					the top selected object in the data container.
	Access :		Public

	Return :		void
	Parameters :	none

	Usage :			Call to align the center of all selected
					objects.
					Should only be callable if "GetSelectCount() >
					1", that is, more than one object is selected.

   ============================================================*/
{
	PrepareForAlignment();

	if (GetSelectCount() > 1)
	{
		GetDiagramEntityContainer()->Snapshot();
		CDiagramEntity* obj = GetSelectedObject();
		if (obj)
		{
			double center = (obj->GetRight() + obj->GetLeft()) / (double)2;
			int count = 0;
			while ((obj = GetDiagramEntityContainer()->GetAt(count++)))
			{
				if (obj->IsSelected())
				{
					double width = obj->GetRight() - obj->GetLeft();
					double right = center + width / 2;
					double left = center - width / 2;
					obj->SetRect(left, obj->GetTop(), right, obj->GetBottom());
				}
			}

		}
		SetModified(TRUE);
		RedrawWindow();
	}

	AutoResizeAll();
}


void CProMoEditor::ShowPageBreaks(BOOL isVisible)
/* ============================================================
	Function :		CDiagramEditor::ShowPageBreaks
	Description :	Enable/disable page break indicators.
	Access :		Public

	Return :		void
	Parameters :	BOOL isVisible	-	"TRUE" if page break
										indicators should be 
										shown.

   ============================================================*/
{
	m_pageBreaksVisible = isVisible;
	if (m_hWnd)
		RedrawWindow();
}

BOOL CProMoEditor::IsPageBreaksVisible()
/* ============================================================
	Function :		CDiagramEditor::IsPageBreaksVisible
	Description :	Gets the state of the page break indicators
					state.
	Access :		Public

	Return :		BOOL	-	"TRUE" if page break indicators
								are on.
	Parameters :	none

   ============================================================*/
{
	return m_pageBreaksVisible;
}

void CProMoEditor::SetPageLayout(CDC* dc)
/* ============================================================
	Function :		CProMoEditor::SetPageLayout
	Description :	Sets the page layout from input printer dc
	Access :		Public

	Return :		void
	Parameters :	CDC* dc		-	"CDC" to read page layout
									information.

	Usage :			Virtual. Can be overridden to apply a 
					different page layout logic.

   ============================================================*/
{
	if (dc) {
		m_printResolutionX = dc->GetDeviceCaps(LOGPIXELSX);
		m_printResolutionY = dc->GetDeviceCaps(LOGPIXELSY);

		// Paper
		m_paperSize.cx = dc->GetDeviceCaps(PHYSICALWIDTH);
		m_paperSize.cy = dc->GetDeviceCaps(PHYSICALHEIGHT);

		// Printable area
		m_printableArea.cx = dc->GetDeviceCaps(HORZRES);
		m_printableArea.cy = dc->GetDeviceCaps(VERTRES);

		// Margins
		int offsetX = dc->GetDeviceCaps(PHYSICALOFFSETX);
		int offsetY = dc->GetDeviceCaps(PHYSICALOFFSETY);

		
		SetMargins(offsetX, offsetY, m_paperSize.cx - offsetX - m_printableArea.cx, m_paperSize.cy - offsetY - m_printableArea.cy);
		
		Invalidate();
	}
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

	CObArray* pProps = NULL;

	if (pSelectedEntity)
	{
		pProps = GetProperties(pSelectedEntity);
	}

	// Get main frame window
	CWnd* pMainFrame = AfxGetMainWnd();
	if (pMainFrame && ::IsWindow(pMainFrame->GetSafeHwnd()))
	{
		// Send message asynchronously to avoid blocking (optional)
		pMainFrame->PostMessage(WM_SELECTION_CHANGED, 0, (LPARAM)pProps);
	}
}

void CProMoEditor::UpdateDelete(CCmdUI* pCmdUI) const
/* ============================================================
	Function :		CProMoEditor::UpdateDelete
	Description :	Command enabling for a Delete command UI-
					element.
	Access :		Public

	Return :		void
	Parameters :	CCmdUI* pCmdUI	-	Command element to
										update

	Usage :			Can be called from a doc/view command update
					function

   ============================================================*/
{
	pCmdUI->Enable(IsAnyObjectSelected());
}


