#include "stdafx.h"
#include "ProMoEntityContainer.h"
#include <math.h>
#include "ProMoBlockModel.h"
#include "ProMoBlockView.h"
#include "ProMoEdgeModel.h"
#include "ProMoEdgeView.h"

CProMoEntityContainer::CProMoEntityContainer()
/* ============================================================
	Function :		CProMoEntityContainer::CProMoEntityContainer
	Description :	constructor

	Return :		void
	Parameters :	none

	Usage :

   ============================================================*/
{
	SetUndoStackSize(10);
}

CProMoEntityContainer::~CProMoEntityContainer()
/* ============================================================
	Function :		CProMoEntityContainer::~CProMoEntityContainer
	Description :	destructor

	Return :		void
	Parameters :	none

	Usage :

   ============================================================*/
{

	ClearUndo();

}

// may not be needed
void CProMoEntityContainer::removeR(CProMoBlockView *block) {
	CObArray* subBlockModels = block->getModel()->GetSubBlocks();
	for (int i = 0; i < subBlockModels->GetSize(); i++) {
		CProMoBlockModel* subBlockModel = dynamic_cast<CProMoBlockModel*>(subBlockModels->GetAt(i));
		if (subBlockModel) {
			removeR(subBlockModel->GetMainView());
		}
	}
	this->Remove(block);
}

void CProMoEntityContainer::RemoveAt(int index)
/* ============================================================
	Function :		CProMoEntityContainer::RemoveAt
	Description :	Removes the object at index. Will also
					remove all links refering to this object.

	Return :		void
	Parameters :	int index	-	Index for object to remove.

	Usage :			Overridden to remove links as well.

   ============================================================*/
{

	CDiagramEntity* obj = GetAt(index);
	if (obj)
	{
		CString name = obj->GetName();
		
		CProMoBlockView *block = dynamic_cast<CProMoBlockView*>(obj);
		if (block){
			CObArray subBlockModels;
			subBlockModels.Append(*(block->getModel()->GetSubBlocks()));
			for (int i = 0; i < subBlockModels.GetSize(); i++) {
				CProMoBlockModel* subBlockModel = NULL;
				subBlockModel = dynamic_cast<CProMoBlockModel*>(subBlockModels.GetAt(i));
				if (subBlockModel) {
					this->Remove(subBlockModel->GetMainView());
				}
			}
			if (block->getModel()->GetParentBlock()) {
				//remove from parent
				block->getModel()->GetParentBlock()->UnlinkSubBlock(block->getModel());
			}
		}
		CDiagramEntityContainer::RemoveAt(index);
	}

}

void CProMoEntityContainer::ReplicateRelations(CObArray* source, CObArray* destination) {
	ASSERT(destination->GetSize() == source->GetSize());

	int i = 0;
	//preserve links for edgeViews and cardinalities with model
	for (i = 0; i < source->GetSize(); i++) {
		CProMoEdgeView* edgeView = dynamic_cast<CProMoEdgeView*>(source->GetAt(i));
		CProMoEdgeView* newEdgeView = dynamic_cast<CProMoEdgeView*>(destination->GetAt(i));
		if (edgeView && newEdgeView) {
			if (edgeView->GetSource() != NULL) {
				for (int j = 0; j < source->GetSize(); j++) {
					CProMoEdgeView* sourceEdgeView = dynamic_cast<CProMoEdgeView*>(source->GetAt(j));
					CProMoEdgeView* newSourceEdgeView = dynamic_cast<CProMoEdgeView*>(destination->GetAt(j));
					if (edgeView->GetSource() == sourceEdgeView) {
						newEdgeView->SetSource(newSourceEdgeView);
						newEdgeView->setModel(newSourceEdgeView->getModel());
					}
				}
			}
		}
	}
	for (i = 0; i < source->GetSize(); i++) {
		//preserve links for edgeModels
		CProMoEdgeView* edgeView = dynamic_cast<CProMoEdgeView*>(source->GetAt(i));
		CProMoEdgeView* newEdgeView = dynamic_cast<CProMoEdgeView*>(destination->GetAt(i));
		if (edgeView && newEdgeView) {
			CProMoEdgeModel* edgeModel = dynamic_cast<CProMoEdgeModel*>(edgeView->getModel());
			CProMoEdgeModel* newEdgeModel = dynamic_cast<CProMoEdgeModel*>(newEdgeView->getModel());
			if (edgeModel && newEdgeModel) {
				if (edgeModel->GetSource() != NULL || edgeModel->GetDestination() != NULL) {
					for (int j = 0; j < source->GetSize(); j++) {
						CProMoBlockView* connectedBlockView = dynamic_cast<CProMoBlockView*>(source->GetAt(j));
						CProMoBlockView* newConnectedBlockView = dynamic_cast<CProMoBlockView*>(destination->GetAt(j));
						if (connectedBlockView && newConnectedBlockView) {
							CProMoBlockModel* connectedBlockModel = connectedBlockView->getModel();
							CProMoBlockModel* newConnectedBlockModel = newConnectedBlockView->getModel();

							if (edgeModel->GetSource() == connectedBlockModel) {
								newEdgeModel->SetSource(newConnectedBlockModel);
							}
							if (edgeModel->GetDestination() == connectedBlockModel) {
								newEdgeModel->SetDestination(newConnectedBlockModel);
							}
						}
					}
				}
			}
		}
		//preserve nesting for nodes
		CProMoBlockView* blockView = dynamic_cast<CProMoBlockView*>(source->GetAt(i));
		CProMoBlockView* newBlockView = dynamic_cast<CProMoBlockView*>(destination->GetAt(i));
		if (blockView && newBlockView) {
			CProMoBlockModel* blockModel = blockView->getModel();
			CProMoBlockModel* newBlockModel = newBlockView->getModel();
			if (blockModel->GetParentBlock() != NULL) {
				for (int j = 0; j < source->GetSize(); j++) {
					CProMoBlockView* parentBlockView = dynamic_cast<CProMoBlockView*>(source->GetAt(j));
					CProMoBlockView* newParentBlockView = dynamic_cast<CProMoBlockView*>(destination->GetAt(j));
					if (parentBlockView && newParentBlockView) {
						CProMoBlockModel* parentBlockModel = parentBlockView->getModel();
						CProMoBlockModel* newParentBlockModel = newParentBlockView->getModel();
						if (blockModel->GetParentBlock() == parentBlockModel) {
							newBlockModel->SetParentBlock(newParentBlockModel);
							break;
						}
					}
				}
			}
		}
	}

}

void CProMoEntityContainer::reorderR(CProMoBlockView* block, CObArray* newOrder) {
	ASSERT(block->getModel());
	newOrder->Add(block);
	//check for connected incoming edges
	CObArray* edges = block->getModel()->GetIncomingEdges();
	if (edges) {
		for (int i = 0; i < edges->GetSize(); i++) {
			CProMoEdgeModel* edgeModel = dynamic_cast<CProMoEdgeModel*>(edges->GetAt(i));
			if (edgeModel) {
				CObArray* views = edgeModel->GetViews();
				CProMoBlockModel* sourceModel = dynamic_cast<CProMoBlockModel*>(edgeModel->GetSource());
				if (sourceModel) {
					for (int j = 0; j < newOrder->GetSize(); j++) {
						//source node has already been explored
						if (newOrder->GetAt(j) == sourceModel->GetMainView()) {
							//add all edge views
							newOrder->Append(*views);
						}
					}
				}
				//no source node exists
				else {
					//add all edge views
					newOrder->Append(*views);
				}
			}
		}
	}

	//check for connected outgoing edges
	edges = block->getModel()->GetOutgoingEdges();
	if (edges) {
		for (int i = 0; i < edges->GetSize(); i++) {
			CProMoEdgeModel* edgeModel = dynamic_cast<CProMoEdgeModel*>(edges->GetAt(i));
			if (edgeModel) {
				CObArray* views = edgeModel->GetViews();
				CProMoBlockModel* destModel = dynamic_cast<CProMoBlockModel*>(edgeModel->GetDestination());
				if (destModel) {
					//do not include self-loops
					if (destModel != block->getModel()) {
						for (int j = 0; j < newOrder->GetSize(); j++) {
							//destination node has already been explored
							if (newOrder->GetAt(j) == destModel->GetMainView()) {
								//add all edge views
								newOrder->Append(*views);
							}
						}
					}
				}
				//no destination node exists
				else {
					//add all edge views
					newOrder->Append(*views);
				}
			}
		}
	}


	CObArray *subBlockViews = block->getModel()->GetSubBlocks();

	int max = GetSize();

	for (int t = 0; t < max; t++) {
		CProMoBlockView* blockView = dynamic_cast<CProMoBlockView*>(GetAt(t));
		if (blockView) {
			for (int i = 0; i < subBlockViews->GetSize(); i++) {
				CProMoBlockModel* subBlockModel = dynamic_cast<CProMoBlockModel*>(subBlockViews->GetAt(i));
				if (blockView == subBlockModel->GetMainView()) {
					reorderR(blockView, newOrder);
				}
			}
		}
	}
}

void CProMoEntityContainer::reorder()
{
	int count = 0;
	int max = GetSize();
	CObArray *objs;
	CObArray newOrder;

	for (int t = 0; t < max; t++)
	{
		CDiagramEntity *obj = dynamic_cast<CDiagramEntity*>(GetAt(t));
		if (obj) {
			CProMoBlockView* blockView = dynamic_cast<CProMoBlockView*>(obj);
			if (blockView) {
				if (blockView->getModel()->GetParentBlock() == NULL) {
					reorderR(blockView, &newOrder);
				}
			}
			CProMoEdgeView* edgeView = dynamic_cast<CProMoEdgeView*>(obj);
			if (edgeView) {
				//edge is disconnected, so add it immediately
				if (!(edgeView->getModel()->GetSource() || edgeView->getModel()->GetDestination())) {
					newOrder.Add(edgeView);
				}
			}
		}
	}

	objs = GetData();
	objs->RemoveAll();

	objs->Append(newOrder);

}

void CProMoEntityContainer::SetTarget(CProMoBlockView* obj, BOOL select)
{
	if (obj)
		obj->SetTarget(select);
}

CProMoBlockView* CProMoEntityContainer::getTarget()
{
	CProMoBlockView* currObj = NULL;

	for (int j = GetSize() - 1; j >= 0; j--) {
		currObj = dynamic_cast<CProMoBlockView*>(GetAt(j));
		if (currObj) {
			if (currObj->IsTarget()) {
				return currObj;
			}
		}
	}
	return NULL;
}


int	CProMoEntityContainer::GetSelectCount()
/* ============================================================
	Function :		int	CProMoEntityContainer::GetSelectCount
	Description :	Returns the number of currently selected
					objects.

	Return :		int		-	The number of selected objects.
	Parameters :	none

	Usage :			Call to see how many objects are selected.

   ============================================================*/
{

	int count = 0;
	int max = GetSize();

	for (int t = 0; t < max; t++)
	{
		CProMoBlockView* obj = dynamic_cast<CProMoBlockView*>(GetAt(t));

		if (obj && obj->IsSelected())
			count++;
	}

	return count;

}


void CProMoEntityContainer::GetCurrentFromStack(CObArray& arr)
/* ============================================================
	Function :		CProMoEntityContainer::GetCurrentFromStack
	Description :	Sets the current objects from "arr".
	Access :		Private

	Return :		void
	Parameters :	CObArray& arr	-	Array to add current
										object state from

	Usage :			Called to get the current object state from
					"arr"

   ============================================================*/
{
	if (arr.GetSize())
	{
		// We remove all current data
		RemoveAll();

		// We get the entry from the undo-stack
		// and clone it into the container data
		CUndoItem* item = static_cast<CUndoItem*>(arr.GetAt(arr.GetUpperBound()));
		if (item)
		{
			int count = static_cast<int>((item->arr).GetSize());
			for (int t = 0; t < count; t++)
			{

				CDiagramEntity* obj = static_cast<CDiagramEntity*>((item->arr).GetAt(t));
				Add(obj->Clone());

			}

			// Set the saved virtual size as well
			SetVirtualSize(CSize(item->pt));

			//Replicate relations
			ReplicateRelations(&item->arr, GetData());

			delete item;
			arr.RemoveAt(arr.GetUpperBound());

		}
	}
}

void CProMoEntityContainer::AddCurrentToStack(CObArray& arr)
/* ============================================================
	Function :		CProMoEntityContainer::AddCurrentToStack
	Description :	Adds the current objects to "arr".
	Access :		Private

	Return :		void
	Parameters :	CObArray& arr	-	Array to add current
										object state to

	Usage :			Called to add the current object state to
					"arr"

   ============================================================*/
{

	if (GetUndoStackSize())
	{
		CUndoItem* item = new CUndoItem;

		while (!item && arr.GetSize())
		{

			// We seem - however unlikely -
			// to be out of memory.
			// Remove first element in
			// the stack and try again
			delete arr.GetAt(0);
			arr.RemoveAt(0);
			item = new CUndoItem;

		}

		if (item)
		{

			// Save current virtual size
			item->pt = CPoint(GetVirtualSize());

			// Save all objects
			int count = static_cast<int>(GetData()->GetSize());
			for (int t = 0; t < count; t++)
				(item->arr).Add(GetAt(t)->Clone());

			//Replicate relations
			ReplicateRelations(GetData(), &item->arr);

			// Add to undo stack
			arr.Add(item);

		}
	}
}
