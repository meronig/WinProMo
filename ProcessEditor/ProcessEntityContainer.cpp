#include "../stdafx.h"
#include "ProcessEntityContainer.h"
#include <math.h>
#include "ProcessEntityBlockModel.h"
#include "ProcessEntityBlockView.h"
#include "ProcessLineEdgeModel.h"
#include "ProcessLineEdgeView.h"

CProcessEntityContainer::CProcessEntityContainer()
/* ============================================================
	Function :		CProcessEntityContainer::CProcessEntityContainer
	Description :	constructor

	Return :		void
	Parameters :	none

	Usage :

   ============================================================*/
{
	SetUndoStackSize(10);
}

CProcessEntityContainer::~CProcessEntityContainer()
/* ============================================================
	Function :		CProcessEntityContainer::~CProcessEntityContainer
	Description :	destructor

	Return :		void
	Parameters :	none

	Usage :

   ============================================================*/
{

	//ClearLinks();
	ClearUndo();

}

// may not be needed
void CProcessEntityContainer::removeR(CProcessEntityBlockView *block) {
	CObArray* subBlockModels = block->getModel()->getSubBlocks();
	for (int i = 0; i < subBlockModels->GetSize(); i++) {
		CProcessEntityBlockModel* subBlockModel = dynamic_cast<CProcessEntityBlockModel*>(subBlockModels->GetAt(i));
		if (subBlockModel) {
			removeR(subBlockModel->getMainView());
		}
	}
	this->Remove(block);
}

void CProcessEntityContainer::RemoveAt(int index)
/* ============================================================
	Function :		CProcessEntityContainer::RemoveAt
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
		
		CProcessEntityBlockView *block = dynamic_cast<CProcessEntityBlockView*>(obj);
		if (block){
			CObArray subBlockModels;
			subBlockModels.Append(*(block->getModel()->getSubBlocks()));
			for (int i = 0; i < subBlockModels.GetSize(); i++) {
				CProcessEntityBlockModel* subBlockModel = NULL;
				subBlockModel = dynamic_cast<CProcessEntityBlockModel*>(subBlockModels.GetAt(i));
				if (subBlockModel) {
					this->Remove(subBlockModel->getMainView());
				}
			}
			if (block->getModel()->getParentBlock()) {
				//remove from parent
				block->getModel()->getParentBlock()->unlinkSubBlock(block->getModel());
			}
		}
		CDiagramEntityContainer::RemoveAt(index);
	}

}

void CProcessEntityContainer::ReplicateRelations(CObArray* source, CObArray* destination) {
	ASSERT(destination->GetSize() == source->GetSize());

	//preserve links for edgeViews and cardinalities with model
	for (int i = 0; i < source->GetSize(); i++) {
		CProcessLineEdgeView* edgeView = dynamic_cast<CProcessLineEdgeView*>(source->GetAt(i));
		CProcessLineEdgeView* newEdgeView = dynamic_cast<CProcessLineEdgeView*>(destination->GetAt(i));
		if (edgeView && newEdgeView) {
			if (edgeView->GetSource() != NULL) {
				for (int j = 0; j < source->GetSize(); j++) {
					CProcessLineEdgeView* sourceEdgeView = dynamic_cast<CProcessLineEdgeView*>(source->GetAt(j));
					CProcessLineEdgeView* newSourceEdgeView = dynamic_cast<CProcessLineEdgeView*>(destination->GetAt(j));
					if (edgeView->GetSource() == sourceEdgeView) {
						newEdgeView->SetSource(newSourceEdgeView);
						newEdgeView->setModel(newSourceEdgeView->getModel());
					}
				}
			}
		}
	}
	for (int i = 0; i < source->GetSize(); i++) {
		//preserve links for edgeModels
		CProcessLineEdgeView* edgeView = dynamic_cast<CProcessLineEdgeView*>(source->GetAt(i));
		CProcessLineEdgeView* newEdgeView = dynamic_cast<CProcessLineEdgeView*>(destination->GetAt(i));
		if (edgeView && newEdgeView) {
			CProcessLineEdgeModel* edgeModel = dynamic_cast<CProcessLineEdgeModel*>(edgeView->getModel());
			CProcessLineEdgeModel* newEdgeModel = dynamic_cast<CProcessLineEdgeModel*>(newEdgeView->getModel());
			if (edgeModel && newEdgeModel) {
				if (edgeModel->GetSource() != NULL || edgeModel->GetDestination() != NULL) {
					for (int j = 0; j < source->GetSize(); j++) {
						CProcessEntityBlockView* connectedBlockView = dynamic_cast<CProcessEntityBlockView*>(source->GetAt(j));
						CProcessEntityBlockView* newConnectedBlockView = dynamic_cast<CProcessEntityBlockView*>(destination->GetAt(j));
						if (connectedBlockView && newConnectedBlockView) {
							CProcessEntityBlockModel* connectedBlockModel = connectedBlockView->getModel();
							CProcessEntityBlockModel* newConnectedBlockModel = newConnectedBlockView->getModel();

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
		CProcessEntityBlockView* blockView = dynamic_cast<CProcessEntityBlockView*>(source->GetAt(i));
		CProcessEntityBlockView* newBlockView = dynamic_cast<CProcessEntityBlockView*>(destination->GetAt(i));
		if (blockView && newBlockView) {
			CProcessEntityBlockModel* blockModel = blockView->getModel();
			CProcessEntityBlockModel* newBlockModel = newBlockView->getModel();
			if (blockModel->getParentBlock() != NULL) {
				for (int j = 0; j < source->GetSize(); j++) {
					CProcessEntityBlockView* parentBlockView = dynamic_cast<CProcessEntityBlockView*>(source->GetAt(j));
					CProcessEntityBlockView* newParentBlockView = dynamic_cast<CProcessEntityBlockView*>(destination->GetAt(j));
					if (parentBlockView && newParentBlockView) {
						CProcessEntityBlockModel* parentBlockModel = parentBlockView->getModel();
						CProcessEntityBlockModel* newParentBlockModel = newParentBlockView->getModel();
						if (blockModel->getParentBlock() == parentBlockModel) {
							newBlockModel->setParentBlock(newParentBlockModel);
							break;
						}
					}
				}
			}
		}
	}

}

void CProcessEntityContainer::reorderR(CProcessEntityBlockView* block, CObArray* m_newOrder) {
	m_newOrder->Add(block);
	//ASSERT(false);
	ASSERT(block->getModel());
	CObArray *subBlockViews = block->getModel()->getSubBlocks();

	int max = GetSize();

	for (int t = 0; t < max; t++) {
		CProcessEntityBlockView* blockView = dynamic_cast<CProcessEntityBlockView*>(GetAt(t));
		if (blockView) {
			for (int i = 0; i < subBlockViews->GetSize(); i++) {
				CProcessEntityBlockModel* subBlockModel = dynamic_cast<CProcessEntityBlockModel*>(subBlockViews->GetAt(i));
				if (blockView == subBlockModel->getMainView()) {
					reorderR(blockView, m_newOrder);
				}
			}
		}
	}
}

void CProcessEntityContainer::reorder()
{
	int count = 0;
	int max = GetSize();
	CObArray *m_obj;
	CObArray m_newOrderNodes;
	CObArray m_newOrderEdges;


	for (int t = 0; t < max; t++)
	{
		CDiagramEntity *obj = dynamic_cast<CDiagramEntity*>(GetAt(t));
		if (obj) {
			CProcessEntityBlockView* blockView = dynamic_cast<CProcessEntityBlockView*>(obj);
			if (blockView) {
				if (blockView->getModel()->getParentBlock() == NULL) {
					reorderR(blockView, &m_newOrderNodes);
				}
			}
			else {
				m_newOrderEdges.Add(obj);
			}
		}
	}

	m_obj = GetData();
	m_obj->RemoveAll();

	m_obj->Append(m_newOrderNodes);
	m_obj->Append(m_newOrderEdges);

}

void CProcessEntityContainer::SetTarget(CProcessEntityBlockView* obj, BOOL select)
{
	if (obj)
		obj->SetTarget(select);
}

CProcessEntityBlockView* CProcessEntityContainer::getTarget()
{
	CProcessEntityBlockView* currObj = NULL;

	for (int j = GetSize() - 1; j >= 0; j--) {
		currObj = dynamic_cast<CProcessEntityBlockView*>(GetAt(j));
		if (currObj) {
			if (currObj->IsTarget()) {
				return currObj;
			}
		}
	}
	return NULL;
}


double CProcessEntityContainer::Dist(CPoint point1, CPoint point2)
/* ============================================================
	Function :		CProcessEntityContainer::Dist
	Description :	Calculates the distance between point1 and
					point2.

	Return :		double			-	Resulting distance
	Parameters :	CPoint point1	-	First point to test
					CPoint point2	-	Second point to test

	Usage :			Used to find the closest link points between
					two objects.

   ============================================================*/
{

	double width = abs(point1.x - point2.x);
	double height = abs(point1.y - point2.y);

	double hyp = _hypot(width, height);

	return hyp;

}

CProcessEntityBlockView* CProcessEntityContainer::GetPrimarySelected()
/* ============================================================
	Function :		CProcessEntityContainer::GetPrimarySelected
	Description :	Returns the primary object of the two
					currently selected.

	Return :		CProcessEntityBlock*	-	Primary object or
											NULL if none.
	Parameters :	none

	Usage :			Returns NULL if not exactly two objects are
					selected.

   ============================================================*/
{

	CProcessEntityBlockView* result = NULL;

	if (GetSelectCount() == 2)
	{
		int max = GetSize();

		for (int t = 0; t < max; t++)
		{
			CProcessEntityBlockView* obj = dynamic_cast<CProcessEntityBlockView*>(GetAt(t));
			if (obj && obj->IsSelected())
			{
				if (result == NULL)
					result = obj;
			}
		}
	}

	return result;

}

CProcessEntityBlockView* CProcessEntityContainer::GetSecondarySelected()
/* ============================================================
	Function :		CProcessEntityContainer::GetSecondarySelected
	Description :	Returns the secondary object of the two
					currently selected.

	Return :		CProcessEntityBlock*	-	secondary object or
											NULL if none.
	Parameters :	none

	Usage :			Returns NULL if not exactly two objects are
					selected.

   ============================================================*/
{

	CProcessEntityBlockView* result = NULL;

	if (GetSelectCount() == 2)
	{
		int max = GetSize();

		for (int t = 0; t < max; t++)
		{
			CProcessEntityBlockView* obj = dynamic_cast<CProcessEntityBlockView*>(GetAt(t));
			if (obj && obj->IsSelected())
				result = obj;
		}
	}

	return result;

}

int	CProcessEntityContainer::GetSelectCount()
/* ============================================================
	Function :		int	CProcessEntityContainer::GetSelectCount
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
		CProcessEntityBlockView* obj = dynamic_cast<CProcessEntityBlockView*>(GetAt(t));

		if (obj && obj->IsSelected())
			count++;
	}

	return count;

}


void CProcessEntityContainer::GetCurrentFromStack(CObArray& arr)
/* ============================================================
	Function :		CProcessEntityContainer::GetCurrentFromStack
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
			int count = (item->arr).GetSize();
			for (int t = 0; t < count; t++)
			{

				CDiagramEntity* obj = static_cast<CDiagramEntity*>((item->arr).GetAt(t));
				Add(obj->Clone());

			}

			// Set the saved virtual size as well
			SetVirtualSize(item->pt);

			//Replicate relations
			ReplicateRelations(&item->arr, GetData());

			delete item;
			arr.RemoveAt(arr.GetUpperBound());

		}
	}
}

void CProcessEntityContainer::AddCurrentToStack(CObArray& arr)
/* ============================================================
	Function :		CProcessEntityContainer::AddCurrentToStack
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
			item->pt = GetVirtualSize();

			// Save all objects
			int count = GetData()->GetSize();
			for (int t = 0; t < count; t++)
				(item->arr).Add(GetAt(t)->Clone());

			//Replicate relations
			ReplicateRelations(GetData(), &item->arr);

			// Add to undo stack
			arr.Add(item);

		}
	}
}
