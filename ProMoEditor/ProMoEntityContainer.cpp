/* ==========================================================================
	CProMoEntityContainer

	Author :		Giovanni Meroni

	Purpose :		CProMoEntityContainer is a CDiagramEntityContainer-
					derived class, holding the data for a CProMoEditor.
					
					--In addition to CDiagramEntityContainer, this class keeps
					and manages a list of links. This includes copy/paste
					and undo-handling.

	Description :	--The class uses a derived CDiagramClipboardHandler.

	Usage :			Use as a normal CDiagramEntityContainer class. The
					editor class exposes functions for command enabling.

   ========================================================================*/
#include "stdafx.h"
#include "ProMoEntityContainer.h"
#include <math.h>
#include "ProMoBlockModel.h"
#include "ProMoBlockView.h"
#include "ProMoEdgeModel.h"
#include "ProMoEdgeView.h"
#include "ProMoClipboardHandler.h"

CProMoEntityContainer::CProMoEntityContainer(CDiagramClipboardHandler* clip)
/* ============================================================
	Function :		CProMoEntityContainer::CProMoEntityContainer
	Description :	constructor

	Return :		void
	Parameters :	none

	Usage :

   ============================================================*/
{
	SetClipboardHandler(clip);
	SetUndoStackSize(10);
	m_modelType = _T("promo");
}

CProMoEntityContainer::CProMoEntityContainer(CString modelType, CDiagramClipboardHandler* clip)
/* ============================================================
	Function :		CProMoEntityContainer::CProMoEntityContainer
	Description :	constructor

	Return :		void
	Parameters :	CString modelType	-	string representing
											the type of model

	Usage :

   ============================================================*/
{
	SetClipboardHandler(clip);
	SetUndoStackSize(10);
	m_modelType = modelType;
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
			subBlockModels.Append(*(block->GetModel()->GetSubBlocks()));
			for (int i = 0; i < subBlockModels.GetSize(); i++) {
				CProMoBlockModel* subBlockModel = NULL;
				subBlockModel = dynamic_cast<CProMoBlockModel*>(subBlockModels.GetAt(i));
				if (subBlockModel) {
					this->Remove(subBlockModel->GetMainView());
				}
			}
			if (block->GetModel()->GetParentBlock()) {
				//remove from parent
				block->GetModel()->GetParentBlock()->UnlinkSubBlock(block->GetModel());
			}
		}
		CDiagramEntityContainer::RemoveAt(index);
	}

}

void CProMoEntityContainer::ReplicateRelations(CObArray* source, CObArray* destination) 
/* ============================================================
	Function :		CProMoEntityContainer::ReplicateRelations
	Description :	Replicate node-edge and nesting relations 
					between objects inside source array to the 
					objects	inside target array.
	Access :		Protected

	Return :		void
	Parameters :	CObArray* source	-	Array of source 
											objects
	Parameters :	CObArray* source	-	Array of target
											objects

	Usage :			source and destination must have the same
					size and, for each position, the object in
					destination must be a clone of the one in
					source.

   ============================================================*/
{
	ASSERT(destination->GetSize() == source->GetSize());

	int i = 0;
	//preserve links for edgeViews and cardinalities with model
	for (i = 0; i < source->GetSize(); i++) {
		CProMoEdgeView* edgeView = dynamic_cast<CProMoEdgeView*>(source->GetAt(i));
		CProMoEdgeView* newEdgeView = dynamic_cast<CProMoEdgeView*>(destination->GetAt(i));
		if (edgeView && newEdgeView) {
			for (int j = 0; j < source->GetSize(); j++) {
				CProMoEdgeView* sourceEdgeView = dynamic_cast<CProMoEdgeView*>(source->GetAt(j));
				CProMoEdgeView* newSourceEdgeView = dynamic_cast<CProMoEdgeView*>(destination->GetAt(j));
				if (sourceEdgeView && newSourceEdgeView) {
					if (edgeView->GetSource() == sourceEdgeView) {
						newEdgeView->SetSource(newSourceEdgeView);
					}
					if (edgeView->GetModel() == sourceEdgeView->GetModel()) {
						newSourceEdgeView->SetModel(newEdgeView->GetModel());
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
			CProMoEdgeModel* edgeModel = dynamic_cast<CProMoEdgeModel*>(edgeView->GetModel());
			CProMoEdgeModel* newEdgeModel = dynamic_cast<CProMoEdgeModel*>(newEdgeView->GetModel());
			if (edgeModel && newEdgeModel) {
				if (edgeModel->GetSource() != NULL || edgeModel->GetDestination() != NULL) {
					for (int j = 0; j < source->GetSize(); j++) {
						CProMoBlockView* connectedBlockView = dynamic_cast<CProMoBlockView*>(source->GetAt(j));
						CProMoBlockView* newConnectedBlockView = dynamic_cast<CProMoBlockView*>(destination->GetAt(j));
						if (connectedBlockView && newConnectedBlockView) {
							CProMoBlockModel* connectedBlockModel = connectedBlockView->GetModel();
							CProMoBlockModel* newConnectedBlockModel = newConnectedBlockView->GetModel();

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
			CProMoBlockModel* blockModel = blockView->GetModel();
			CProMoBlockModel* newBlockModel = newBlockView->GetModel();
			if (blockModel->GetParentBlock() != NULL) {
				for (int j = 0; j < source->GetSize(); j++) {
					CProMoBlockView* parentBlockView = dynamic_cast<CProMoBlockView*>(source->GetAt(j));
					CProMoBlockView* newParentBlockView = dynamic_cast<CProMoBlockView*>(destination->GetAt(j));
					if (parentBlockView && newParentBlockView) {
						CProMoBlockModel* parentBlockModel = parentBlockView->GetModel();
						CProMoBlockModel* newParentBlockModel = newParentBlockView->GetModel();
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

void CProMoEntityContainer::Load(const CStringArray& stra, CProMoControlFactory& fact)
/* ============================================================
	Function :		CProMoEntityContainer::Load
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

	Usage :			Call to load the data of the container from a
					"CStringArray". Virtual. Can be overridden in
					a derived class to add non-container data
					before and after the objects

   ============================================================*/
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
				if (!GetNamedView(obj->GetName()))
					Add(obj);

			CProMoModel* model = fact.CreateModelFromString(str);
			if (model)
				if (!GetNamedModel(models, model->GetName()))
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
					CProMoBlockView* blockView = dynamic_cast<CProMoBlockView*>(GetNamedView(nodeName));
					if (blockView) {
						if (size >= 8) {
							tok.GetAt(7, modelName);
							CProMoBlockModel* blockModel = dynamic_cast<CProMoBlockModel*>(GetNamedModel(models, modelName));
							if (blockModel) {
								//required to avoid dangling pointers in case of malformed input files
								CProMoModel* oldMod = blockView->GetModel();
								if (oldMod)
									DeleteModel(models, oldMod->GetName());
								blockView->SetModel(blockModel);
							}
							else {
								//input file is malformed: create a new model to avoid inconsistencies
								blockView->SetModel(new CProMoBlockModel);
							}
						}
					}

					//current element is an edge view
					CProMoEdgeView* edgeView = dynamic_cast<CProMoEdgeView*>(GetNamedView(nodeName));
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
								CProMoModel* oldMod = edgeView->GetModel();
								if (oldMod)
									DeleteModel(models, oldMod->GetName());
								edgeView->SetModel(edgeModel);
							}
							else {
								//input file is malformed: create a new model to avoid inconsistencies
								edgeView->SetModel(new CProMoEdgeModel);
							}

							CDiagramEntity* source = dynamic_cast<CDiagramEntity*>(GetNamedView(sourceName));
							if (source) {
								edgeView->SetSource(source);
							}
							CDiagramEntity* dest = dynamic_cast<CDiagramEntity*>(GetNamedView(destName));
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

	SetModified(FALSE);
}

void CProMoEntityContainer::Save(CStringArray& stra)
/* ============================================================
	Function :		CProMoEntityContainer::Save
	Description :	Saves a string representation of the
					container (normally the virtual size) and
					all objects to "stra".
	Access :		Public

	Return :		void
	Parameters :	CStringArray& stra	-	The array to fill

	Usage :			Call to save the data of the container to a
					"CStringArray". Virtual. Can be overridden in
					a derived class to add non-container data
					before and after the objects

   ============================================================*/
{
	stra.Add(GetString());
	
	SaveObjects(stra);

	SetModified(FALSE);
}

void CProMoEntityContainer::SaveObjects(CStringArray& stra)
/* ============================================================
	Function :		CProMoEntityContainer::SaveObjects
	Description :	Saves a string representation of the
					current objects to "stra", one object in
					each string.
	Access :		Public

	Return :		void
	Parameters :	CStringArray& stra	-	The array to fill

	Usage :			Virtual. Can be overridden in a derived
					class to add more per-object information to
					the save array.

   ============================================================*/
{
	int count = 0;
	CDiagramEntity* obj;
	while ((obj = GetAt(count++)))
		stra.Add(obj->GetString());


	CObArray models;

	int i;
	for (i = 0; i < GetSize(); i++) {
		CProMoBlockView* currObjBlock = dynamic_cast<CProMoBlockView*>(GetAt(i));
		if (currObjBlock) {
			models.Add(currObjBlock->GetModel());
		}
		CProMoEdgeView* currObjEdge = dynamic_cast<CProMoEdgeView*>(GetAt(i));
		if (currObjEdge) {
			models.Add(currObjEdge->GetModel());
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

void CProMoEntityContainer::ReorderR(CProMoBlockView* block, CObArray* newOrder) 
/* ============================================================
	Function :		CProMoEntityContainer::ReorderR
	Description :	Helper method to recursively reorder 
					objects that are child of the current 
					block, such that they are drawn after 
					parent blocks, and connected edges are 
					drawn after both source and destination 
					blocks are drawn.
	Access :		Private

	Return :		void
	Parameters :	CProMoBlockView* block	-	Current block
					CObArray* newOrder		-	Array of 
												elements to be
												reordered.

   ============================================================*/
{
	ASSERT(block->GetModel());
	newOrder->Add(block);
	//check for connected incoming edges
	CObArray* edges = block->GetModel()->GetIncomingEdges();
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
	edges = block->GetModel()->GetOutgoingEdges();
	if (edges) {
		for (int i = 0; i < edges->GetSize(); i++) {
			CProMoEdgeModel* edgeModel = dynamic_cast<CProMoEdgeModel*>(edges->GetAt(i));
			if (edgeModel) {
				CObArray* views = edgeModel->GetViews();
				CProMoBlockModel* destModel = dynamic_cast<CProMoBlockModel*>(edgeModel->GetDestination());
				if (destModel) {
					//do not include self-loops
					if (destModel != block->GetModel()) {
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


	CObArray *subBlockViews = block->GetModel()->GetSubBlocks();

	int max = GetSize();

	for (int t = 0; t < max; t++) {
		CProMoBlockView* blockView = dynamic_cast<CProMoBlockView*>(GetAt(t));
		if (blockView) {
			for (int i = 0; i < subBlockViews->GetSize(); i++) {
				CProMoBlockModel* subBlockModel = dynamic_cast<CProMoBlockModel*>(subBlockViews->GetAt(i));
				if (blockView == subBlockModel->GetMainView()) {
					ReorderR(blockView, newOrder);
				}
			}
		}
	}
}

void CProMoEntityContainer::Reorder()
/* ============================================================
	Function :		CProMoEntityContainer::Reorder
	Description :	Reorders objects such that child blocks
					are drawn after parent blocks, and
					connected edges are drawn after both source
					and destination blocks are drawn.
	Access :		Public

	Return :		void
	Parameters :	none

   ============================================================*/
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
				if (blockView->GetModel()->GetParentBlock() == NULL) {
					ReorderR(blockView, &newOrder);
				}
			}
			CProMoEdgeView* edgeView = dynamic_cast<CProMoEdgeView*>(obj);
			if (edgeView) {
				//edge is disconnected, so add it immediately
				if (!(edgeView->GetModel()->GetSource() || edgeView->GetModel()->GetDestination())) {
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
/* ============================================================
	Function :		CProMoEntityContainer::SetTarget
	Description :	Makes the block being passed as input a 
					target for the current drawing operation 
					(e.g., when dragging another object over 
					it)
	Access :		Public

	Return :		void
	Parameters :	CProMoBlockView* obj	-	Pointer to the
												block
					BOOL select				-	"TRUE" if the 
												block should be 
												the target

   ============================================================*/
{
	if (obj)
		obj->SetTarget(select);
}

CProMoBlockView* CProMoEntityContainer::GetTarget()
/* ============================================================
	Function :		CProMoEntityContainer::GetTarget
	Description :	Returns a pointer to the block that is the
					target for the current drawing operation
					(e.g., when dragging another object over
					it)
	Access :		Public

	Return :		CProMoBlockView* obj	-	Pointer to the
												block
	Parameters :	none

   ============================================================*/
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
	Function :		CProMoEntityContainer::GetSelectCount
	Description :	Returns the number of currently selected
					objects.

	Return :		int		-	The number of selected objects.
	Parameters :	none

	Usage :			Call to see how many objects are selected.
					Overridden to consider only blocks.

   ============================================================*/
{
	//Note: check if overriding is actually needed for alignment
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
	Access :		Protected

	Return :		void
	Parameters :	CObArray& arr	-	Array to add current
										object state from

	Usage :			Called to get the current object state from
					"arr". Overridden to replicate node-edge 
					relations

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
	Access :		Protected

	Return :		void
	Parameters :	CObArray& arr	-	Array to add current
										object state to

	Usage :			Called to add the current object state to
					"arr". Overridden to replicate node-edge 
					relations

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

CDiagramEntity* CProMoEntityContainer::GetNamedView(const CString& name) const
/* ============================================================
	Function :		CProMoEntityContainer::GetNamedView
	Description :	Returns the element with the name attribute
					name.
	Access :		Protected

	Return :		CDiagramEntity*		-	The view for the
											element, or NULL
											if not found.
	Parameters :	const CString& name	-	The name of the
											element to find.

	Usage :			Call to get the element with the name name,
					if it exists.

   ============================================================*/
{

	CDiagramEntity* result = NULL;

	int count = GetSize();
	CDiagramEntity* obj;
	for (int t = 0; t < count; t++)
	{
		obj = GetAt(t);
		if (obj && obj->GetName() == name)
			result = obj;
	}

	return result;

}

CProMoModel* CProMoEntityContainer::GetNamedModel(const CObArray& array, const CString& name) const
/* ============================================================
	Function :		CProMoEntityContainer::GetNamedModel
	Description :	Returns the model with the name attribute
					name.
	Access :		Protected

	Return :		CProMoModel*			-	The object, or
												NULL if not
												found.
	Parameters :	const CObArray& array	-	Array of models
					const CString& name		-	The name of the
												object to find.

	Usage :			Call to get the object with the name name,
					if it exists.

   ============================================================*/
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

void CProMoEntityContainer::DeleteModel(CObArray& array, const CString& name)
/* ============================================================
	Function :		CProMoEntityContainer::DeleteModel
	Description :	Deletes the model with the name name from
					the input array
	Access :		Protected

	Return :		void
	Parameters :	const CObArray& array	-	Array of models
					const CString& name		-	The name of the
												object to find.

   ============================================================*/
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

CString CProMoEntityContainer::GetString() const
/* ============================================================
	Function :		CProMoEntityContainer::GetString
	Description :	Returns a string representation of the
					virtual paper size
	Access :		Public

	Return :		CString	-	Resulting string
	Parameters :	none

	Usage :			Overridden to save model type information.

   ============================================================*/
{

	CString str;
	str.Format(_T("%s:%i,%i;"), (LPCTSTR)m_modelType, GetVirtualSize().cx, GetVirtualSize().cy);
	return str;

}


BOOL CProMoEntityContainer::FromString(const CString& str)
/* ============================================================
	Function :		CProMoEntityContainer::FromString
	Description :	Sets the virtual paper size from a string.
	Access :		Public

	Return :		BOOL				-	"TRUE" if the string
											represented a
											paper.
	Parameters :	const CString& str	-	The string
											representation.

	Usage :			Overridden to check for model type 
					information.

   ============================================================*/
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
		if (header == m_modelType)
		{
			CTokenizer tok(data.Left(data.GetLength() - 1));
			int size = tok.GetSize();
			if (size == 2)
			{
				int right;
				int bottom;

				tok.GetAt(0, right);
				tok.GetAt(1, bottom);

				SetVirtualSize(CSize(right, bottom));
				result = TRUE;
			}
		}
	}

	return result;

}

CString CProMoEntityContainer::GetModelType() const
/* ============================================================
	Function :		CProMoEntityContainer::GetModelType
	Description :	Returns a string representation of the
					type of model
	Access :		Public

	Return :		CString	-	Resulting string
	Parameters :	none
   ============================================================*/
{

	return m_modelType;

}

int CProMoEntityContainer::ObjectsInPaste()
/* ============================================================
	Function :		CProMoEntityContainer::ObjectsInPaste
	Description :	Returns the number of objects in the paste
					array.
	Access :		Public

	Return :		int		-	The number of objects.
	Parameters :	none

	Usage :			Overridden to return 0 in case of elements
					incompatible with current model type.

   ============================================================*/
{
	CProMoClipboardHandler* clip = dynamic_cast<CProMoClipboardHandler*>(GetClipboardHandler());
	if (clip) {
		if (clip->GetModelType() != m_modelType) {
			return 0;
		}
	}
	return CDiagramEntityContainer::ObjectsInPaste();

}