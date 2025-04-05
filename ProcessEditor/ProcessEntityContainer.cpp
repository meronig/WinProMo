#include "../stdafx.h"
#include "ProcessEntityContainer.h"
#include <math.h>
#include "ProcessEntityBlockModel.h"

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


void CProcessEntityContainer::Undo()
/* ============================================================
	Function :		CProcessEntityContainer::Undo
	Description :	Undo the latest operation

	Return :		void
	Parameters :	none

	Usage :			Overridden to also undo link operations.

   ============================================================*/
{

	CDiagramEntityContainer::Undo();


}

void CProcessEntityContainer::Snapshot()
/* ============================================================
	Function :		CProcessEntityContainer::Snapshot
	Description :	Creates a snapshot of the current data
					state for the undo-functionality.

	Return :		void
	Parameters :	none

	Usage :			Overridden to save the link state as well.

   ============================================================*/
{

	CDiagramEntityContainer::Snapshot();
	
	//CObArray* undo = new CObArray;

	
	
}

void CProcessEntityContainer::ClearUndo()
/* ============================================================
	Function :		CProcessEntityContainer::ClearUndo
	Description :	Clears the undo-array

	Return :		void
	Parameters :	none

	Usage :			Overridden to also clear the link undo
					states.

   ============================================================*/
{

	CDiagramEntityContainer::ClearUndo();
	
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