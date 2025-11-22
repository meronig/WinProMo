/* ==========================================================================

	Copyright © 2025 Technical University of Denmark

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
#include "../FileUtils/FileParser.h"
#include "ProMoLabel.h"

CProMoEntityContainer::CProMoEntityContainer(CDiagramClipboardHandler* clip)
/* ============================================================
	Function :		CProMoEntityContainer::CProMoEntityContainer
	Description :	constructor

	Return :		void
	Parameters :	none

	Usage :

   ============================================================*/
{
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
					remove all labels refering to this object,
					and, if the object is a block, all its
					subblocks.

	Return :		void
	Parameters :	int index	-	Index for object to remove.

   ============================================================*/
{
	CDiagramEntity* obj = GetAt(index);
	CObArray labels;

	if (obj)
	{
		CString name = obj->GetName();
		
		CProMoBlockView *block = dynamic_cast<CProMoBlockView*>(obj);
		if (block){
			// remove sub-blocks
			CObArray subBlockModels;
			((CProMoBlockModel*)block->GetModel())->GetSubBlocks(subBlockModels);
			for (int i = 0; i < subBlockModels.GetSize(); i++) {
				CProMoBlockModel* subBlockModel = NULL;
				subBlockModel = dynamic_cast<CProMoBlockModel*>(subBlockModels.GetAt(i));
				if (subBlockModel) {
					Remove(subBlockModel->GetMainView());
				}
			}
			// disconnect block from parent
			block->UnlinkFromParent();
			// identify labels
			block->GetModel()->GetLabels(labels);
			
		}

		CProMoEdgeView* edge = dynamic_cast<CProMoEdgeView*>(obj);
		if (edge) {
			// remove labels only if the edge view is the last segment
			if (edge->IsFirstSegment() && edge->IsLastSegment()) {
				// identify labels
				edge->GetModel()->GetLabels(labels);
			}
		}

		// remove labels
		for (int i = 0; i < labels.GetSize(); i++) {
			CProMoLabel* label = NULL;
			label = dynamic_cast<CProMoLabel*>(labels.GetAt(i));
			if (label) {
				Remove(label);
			}
		}

		CDiagramEntityContainer::RemoveAt(index);
	}

}

void CProMoEntityContainer::ReplicateRelations(const CObArray& source, CObArray& destination) 
/* ============================================================
	Function :		CProMoEntityContainer::ReplicateRelations
	Description :	Replicate node-edge and nesting relations 
					between objects inside source array to the 
					objects	inside target array.
	Access :		Protected

	Return :		void
	Parameters :	CObArray source	-	Array of source 
										objects
	Parameters :	CObArray source	-	Array of target
										objects

	Usage :			source and destination must have the same
					size and, for each position, the object in
					destination must be a clone of the one in
					source.

   ============================================================*/
{
	ASSERT(destination.GetSize() == source.GetSize());

	int i = 0;

	for (i = 0; i < source.GetSize(); i++) {
		CProMoEdgeView* edgeView = dynamic_cast<CProMoEdgeView*>(source.GetAt(i));
		CProMoEdgeView* newEdgeView = dynamic_cast<CProMoEdgeView*>(destination.GetAt(i));
		CProMoBlockView* blockView = dynamic_cast<CProMoBlockView*>(source.GetAt(i));
		CProMoBlockView* newBlockView = dynamic_cast<CProMoBlockView*>(destination.GetAt(i));
		
		for (int j = 0; j < source.GetSize(); j++) {
			CProMoLabel* label = dynamic_cast<CProMoLabel*>(source.GetAt(j));
			CProMoLabel* newLabel = dynamic_cast<CProMoLabel*>(destination.GetAt(j));
			CProMoEdgeView* connectedEdgeView = dynamic_cast<CProMoEdgeView*>(source.GetAt(j));
			CProMoEdgeView* newConnectedEdgeView = dynamic_cast<CProMoEdgeView*>(destination.GetAt(j));
			CProMoBlockView* connectedBlockView = dynamic_cast<CProMoBlockView*>(source.GetAt(j));
			CProMoBlockView* newConnectedBlockView = dynamic_cast<CProMoBlockView*>(destination.GetAt(j));
				
			if (blockView && newBlockView) {
				//preserve block nesting
				if (connectedBlockView && newConnectedBlockView) {
					if (connectedBlockView->GetBlockModel()->HasSubBlock(blockView->GetBlockModel())) {
						newConnectedBlockView->LinkSubBlock(newBlockView);
					}
				}
				//preserve links between blocks and labels
				if (label && newLabel) {
					if (label->GetModel() == blockView->GetModel()) {
						newBlockView->LinkLabel(newLabel);
					}
				}
			}
				
			if (edgeView && newEdgeView) {
				
				//preserve links within edges and cardinalities with model
				if (connectedEdgeView && newConnectedEdgeView) {
					if (edgeView->GetSource() == connectedEdgeView) {
						newEdgeView->SetSource(newConnectedEdgeView);
					}
				}
				
				//preserve links between edges and blocks
				if (connectedBlockView && newConnectedBlockView) {
					if (edgeView->GetSource() == connectedBlockView && edgeView->IsFirstSegment()) {
						newEdgeView->SetSource(newConnectedBlockView);
					}
					if (edgeView->GetDestination() == connectedBlockView && edgeView->IsLastSegment()) {
						newEdgeView->SetDestination(newConnectedBlockView);
					}
				}

				//preserve links between edges and labels
				if (label && newLabel) {
					if (label->GetModel() == edgeView->GetModel()) {
						newEdgeView->LinkLabel(newLabel);
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
	Clear();

	CObArray models;

	LoadModels(stra, fact, models);
	LoadViews(stra, fact, models);
	LoadProperties(stra, models);

	LinkViews(stra, models);
	LinkModels(stra, models);
	LoadLabels(stra, fact, models);
	
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
			for (unsigned int j = 0; j < currModel->GetPropertiesCount(); j++) {
				CProMoProperty* prop = currModel->GetProperty(j);
				SaveProperties(stra, prop);
			}
		}
	}
}

void CProMoEntityContainer::ReorderR(CProMoBlockView* block, CObArray& newOrder) 
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
					CObArray newOrder		-	Array of 
												elements to be
												reordered.

   ============================================================*/
{
	ASSERT(block->GetModel());
	newOrder.Add(block);
	//check for connected incoming edges
	CObArray edges; 
	CObArray views;
	CObArray labels;
	((CProMoBlockModel*)block->GetModel())->GetIncomingEdges(edges);
	for (int i = 0; i < edges.GetSize(); i++) {
		CProMoEdgeModel* edgeModel = dynamic_cast<CProMoEdgeModel*>(edges.GetAt(i));
		if (edgeModel) {
			views.RemoveAll();
			edgeModel->GetViews(views);
			CProMoBlockModel* sourceModel = edgeModel->GetSource();
			if (sourceModel) {
				for (int j = 0; j < newOrder.GetSize(); j++) {
					//source node has already been explored
					if (newOrder.GetAt(j) == sourceModel->GetMainView()) {
						//add all edge views
						newOrder.Append(views);
						//add all edge labels
						labels.RemoveAll();
						edgeModel->GetLabels(labels);
						newOrder.Append(labels);
					}
				}
			}
			//no source node exists
			else {
				//add all edge views
				newOrder.Append(views);
				//add all edge labels
				labels.RemoveAll();
				edgeModel->GetLabels(labels);
				newOrder.Append(labels);
			}
		}
	}

	edges.RemoveAll();

	//check for connected outgoing edges
	((CProMoBlockModel*)block->GetModel())->GetOutgoingEdges(edges);
	for (int i = 0; i < edges.GetSize(); i++) {
		CProMoEdgeModel* edgeModel = dynamic_cast<CProMoEdgeModel*>(edges.GetAt(i));
		if (edgeModel) {
			views.RemoveAll();
			edgeModel->GetViews(views);
			CProMoBlockModel* destModel = edgeModel->GetDestination();
			if (destModel) {
				//do not include self-loops
				if (destModel != block->GetModel()) {
					for (int j = 0; j < newOrder.GetSize(); j++) {
						//destination node has already been explored
						if (newOrder.GetAt(j) == destModel->GetMainView()) {
							//add all edge views
							newOrder.Append(views);
							//add all edge labels
							labels.RemoveAll();
							edgeModel->GetLabels(labels);
							newOrder.Append(labels);
						}
					}
				}
			}
			//no destination node exists
			else {
				//add all edge views
				newOrder.Append(views);
				//add all edge labels
				labels.RemoveAll();
				edgeModel->GetLabels(labels);
				newOrder.Append(labels);
			}
		}
	}

	// Check for labels
	labels.RemoveAll();
	block->GetModel()->GetLabels(labels);
	newOrder.Append(labels);
	

	int max = GetSize();

	// check for subblocks
	CObArray subBlockModels;
	
	((CProMoBlockModel*)block->GetModel())->GetSubBlocks(subBlockModels);
	
	for (int t = 0; t < max; t++) {
		CProMoBlockView* subBlockView = dynamic_cast<CProMoBlockView*>(GetAt(t));
		if (subBlockView) {
			for (int i = 0; i < subBlockModels.GetSize(); i++) {
				CProMoBlockModel* subBlockModel = dynamic_cast<CProMoBlockModel*>(subBlockModels.GetAt(i));
				if (subBlockView == subBlockModel->GetMainView()) {
					ReorderR(subBlockView, newOrder);
				}
			}
		}
	}

	// check for boundary blocks
	CObArray boundaryBlockModels;

	((CProMoBlockModel*)block->GetModel())->GetBoundaryBlocks(boundaryBlockModels, DEHT_BODY);

	for (int t = 0; t < max; t++) {
		CProMoBlockView* boundaryBlockView = dynamic_cast<CProMoBlockView*>(GetAt(t));
		if (boundaryBlockView) {
			for (int i = 0; i < boundaryBlockModels.GetSize(); i++) {
				CProMoBlockModel* boundaryBlockModel = dynamic_cast<CProMoBlockModel*>(boundaryBlockModels.GetAt(i));
				if (boundaryBlockView == boundaryBlockModel->GetMainView()) {
					ReorderR(boundaryBlockView, newOrder);
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

	// Step 1: blocks and edges
	for (int t = 0; t < max; t++)
	{
		CDiagramEntity *obj = dynamic_cast<CDiagramEntity*>(GetAt(t));
		if (obj) {
			CProMoBlockView* blockView = dynamic_cast<CProMoBlockView*>(obj);
			if (blockView) {
				if (!((CProMoBlockModel*)blockView->GetModel())->IsSubBlock() && !((CProMoBlockModel*)blockView->GetModel())->IsBoundaryBlock()) {
					ReorderR(blockView, newOrder);
				}
			}
			CProMoEdgeView* edgeView = dynamic_cast<CProMoEdgeView*>(obj);
			if (edgeView) {
				//edge is disconnected, so add it immediately
				if (!(((CProMoEdgeModel*)edgeView->GetModel())->GetSource() || ((CProMoEdgeModel*)edgeView->GetModel())->GetDestination())) {
					newOrder.Add(edgeView);
					if (edgeView->IsFirstSegment()) {
						//add the labels
						CObArray labels; 
						edgeView->GetModel()->GetLabels(labels);
						newOrder.Append(labels);
					}
				}
			}
			CProMoLabel* label = dynamic_cast<CProMoLabel*>(obj);
			if (label) {
				//label is disconnected, so add it immediately
				if (!(label->GetModel())) {
					newOrder.Add(label);
				}
			}
		}
	}
	
	objs = GetData();
	objs->RemoveAll();

	objs->Append(newOrder);

}

void CProMoEntityContainer::SetTarget(CProMoBlockView* obj, unsigned int attachment)
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
					unsigned int attachment	-	The type of
												attachment for
												the dragged block

   ============================================================*/
{
	if (obj)
		obj->SetTarget(attachment);
}

CProMoBlockView* CProMoEntityContainer::GetTarget() const
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
			ReplicateRelations(item->arr, *GetData());

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
			ReplicateRelations(*GetData(), item->arr);

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

void CProMoEntityContainer::LoadModels(const CStringArray& stra, CProMoControlFactory& fact, CObArray& models)
/* ============================================================
	Function :		CProMoEntityContainer::LoadModels
	Description :	Creates model objects from their string 
					representation in "stra".
	Access :		Protected

	Return :		void
	Parameters :	CStringArray& stra			-	The array
													to read
					CProMoControlFactory& fact	-	The factory
													object to
													create
													objects
					CObArray& models			-	The array
													that will
													contain
													model 
													objects
													being
													created

   ============================================================*/
{
	int max = static_cast<int>(stra.GetSize());
	int t = 0;

	Clear();

	//create models
	for (t = 0; t < max; t++)
	{
		CString str = stra.GetAt(t);
		if (!FromString(str))
		{
			//check for unicity
			CProMoModel* model = fact.CreateModelFromString(str);
			if (model)
				if (!GetNamedModel(models, model->GetName()))
					models.Add(model);
		}
	}
}

void CProMoEntityContainer::LoadViews(const CStringArray& stra, CProMoControlFactory& fact, const CObArray& models)
/* ============================================================
	Function :		CProMoEntityContainer::LoadViews
	Description :	Creates view objects from their string
					representation in "stra", and links them
					to the corresponding model.
	Access :		Protected

	Return :		void
	Parameters :	CStringArray& stra			-	The array
													to read
					CProMoControlFactory& fact	-	The factory
													object to
													create
													objects
					CObArray& models			-	The array
													that will
													contain
													model
													objects
													to be linked
													to the view
													objects

   ============================================================*/
{
	int max = static_cast<int>(stra.GetSize());
	int t = 0;
	
	//create views and link them to corresponding model
	for (t = 0; t < max; t++)
	{
		CString str = stra.GetAt(t);
		if (!FromString(str))
		{
			CDiagramEntity* obj = NULL;

			CString nodeName = CProMoBlockView::GetNameFromString(str);
			CString modelName = CProMoBlockView::GetModelFromString(str);

			if (!GetNamedView(nodeName)) {
				CProMoModel* blockModel = GetNamedModel(models, modelName);
				if (blockModel) {
					obj = fact.CreateViewFromString(str, blockModel);
				}
			}
				
			//If no model exists for that view, create one from scratch
			if (!obj) {
				obj = fact.CreateViewFromString(str);
			}
			if (obj) {
				Add(obj);
			}
		}
	}

}

void CProMoEntityContainer::LoadLabels(const CStringArray& stra, CProMoControlFactory& fact, const CObArray& models)
/* ============================================================
	Function :		CProMoEntityContainer::LoadLabels
	Description :	Creates label objects from their string
					representation in "stra", and links them
					to the corresponding model.
	Access :		Protected

	Return :		void
	Parameters :	CStringArray& stra			-	The array
													to read
					CProMoControlFactory& fact	-	The factory
													object to
													create
													objects
					CObArray& models			-	The array
													that will
													contain
													model
													objects
													to be linked
													to the label
													objects

   ============================================================*/
{
	int max = static_cast<int>(stra.GetSize());
	int t = 0;

	//create labels and link them to corresponding model
	for (t = 0; t < max; t++)
	{
		CString str = stra.GetAt(t);
		if (!FromString(str))
		{
			CDiagramEntity* obj = NULL;

			CString nodeName = CProMoBlockView::GetNameFromString(str);
			CString modelName = CProMoBlockView::GetModelFromString(str);

			if (!GetNamedView(nodeName)) {
				CProMoModel* blockModel = GetNamedModel(models, modelName);
				if (blockModel) {
					obj = fact.CreateLabelFromString(str, blockModel);
				}
			}

			//If no model exists for that label, create the label as unlinked
			if (!obj) {
				obj = fact.CreateLabelFromString(str);
			}
			if (obj) {
				Add(obj);
			}
		}
	}
}

void CProMoEntityContainer::LoadProperties(const CStringArray& stra, const CObArray& models)
/* ============================================================
	Function :		CProMoEntityContainer::LoadProperties
	Description :	Loads properties for model objects
					from their string representation in
					"stra".
	Access :		Protected

	Return :		void
	Parameters :	CStringArray& stra			-	The array
													to read
					CObArray& models			-	The array
													that will
													contain
													model
													objects
													whose 
													properties
													must be set
													from "stra"

   ============================================================*/
{
	for (int i = 0; i < models.GetSize(); i++) {
		CProMoModel* model = dynamic_cast<CProMoModel*>(models.GetAt(i));
		if (model) {
			for (int j = 0; j < stra.GetSize(); j++) {
				CString str = stra.GetAt(j);
				CString header;
				CFileParser::GetHeaderFromString(str,header);
				if (header == _T("property")) {
					if (model->GetName() == CProMoProperty::GetElementFromString(str)) {
						for (unsigned int k = 0; k < model->GetPropertiesCount(); k++) {
							CProMoProperty* prop = model->GetProperty(k);
							prop->FromString(str);
						}
					}
				}
			}
		}
	}
}


void CProMoEntityContainer::LinkModels(const CStringArray& stra, const CObArray& models)
/* ============================================================
	Function :		CProMoEntityContainer::LinkModels
	Description :	Links model objects to preserve the 
					relations specified in their string 
					representation in "stra".
	Access :		Protected

	Return :		void
	Parameters :	CStringArray& stra			-	The array
													to read
					CObArray& models			-	The array
													that will
													contain
													model
													objects

   ============================================================*/
{
	int max = static_cast<int>(stra.GetSize());
	int t = 0;
	
	//create logical links between elements
	for (t = 0; t < max; t++)
	{
		CString str = stra.GetAt(t);
		if (!FromString(str))
		{
			BOOL result = FALSE;
			
			CString nodeName = CProMoModel::GetNameFromString(str);

			//current element is a block model
			CProMoBlockModel* blockModel = dynamic_cast<CProMoBlockModel*>(GetNamedModel(models, nodeName));
			if (blockModel) {
				CString parentName = blockModel->GetParentFromString(str);

				CProMoBlockModel* parent = dynamic_cast<CProMoBlockModel*>(GetNamedModel(models, parentName));
				if (parent && blockModel->GetMainView()) {
					parent->GetMainView()->LinkSubBlock(blockModel->GetMainView());
				}
						
			}

			//current element is an edge model
			CProMoEdgeModel* edgeModel = dynamic_cast<CProMoEdgeModel*>(GetNamedModel(models, nodeName));
			if (edgeModel) {
				CString sourceName = edgeModel->GetSourceFromString(str);
				CString destName = edgeModel->GetDestinationFromString(str);

				CProMoBlockModel* source = dynamic_cast<CProMoBlockModel*>(GetNamedModel(models, sourceName));
				if (source && edgeModel->GetFirstSegment()) {
					edgeModel->GetFirstSegment()->SetSource(source->GetMainView());
				}
				CProMoBlockModel* dest = dynamic_cast<CProMoBlockModel*>(GetNamedModel(models, destName));
				if (dest && edgeModel->GetLastSegment()) {
					edgeModel->GetLastSegment()->SetDestination(dest->GetMainView());
				}
						
			}
		}
	}

}

void CProMoEntityContainer::LinkViews(const CStringArray& stra, const CObArray& models)
/* ============================================================
	Function :		CProMoEntityContainer::LinkViews
	Description :	Links view objects to preserve the
					relations specified in their string
					representation in "stra".
	Access :		Protected

	Return :		void
	Parameters :	CStringArray& stra			-	The array
													to read
					CObArray& models			-	The array
													that will
													contain
													model
													objects

   ============================================================*/
{
	int max = static_cast<int>(stra.GetSize());
	int t = 0;

	//create logical links between elements
	for (t = 0; t < max; t++)
	{
		CString str = stra.GetAt(t);
		if (!FromString(str))
		{
			BOOL result = FALSE;

			CString nodeName = CProMoBlockView::GetNameFromString(str);
			
			//current element is an edge view
			CProMoEdgeView* edgeView = dynamic_cast<CProMoEdgeView*>(GetNamedView(nodeName));
			if (edgeView) {

				CString sourceName = edgeView->GetSourceFromString(str);
				CString destName = edgeView->GetDestinationFromString(str);

				CDiagramEntity* source = GetNamedView(sourceName);
				if (source) {
					edgeView->SetSource(source);
				}
				CDiagramEntity* dest = GetNamedView(destName);
				if (dest) {
					edgeView->SetDestination(dest);
				}
			}
		}
	}

}

void CProMoEntityContainer::SaveProperties(CStringArray& stra, CProMoProperty* prop)
/* ============================================================
	Function :		CProMoEntityContainer::SaveProperty
	Description :	Saves a string representation of leaf-level
					properties (i.e., simple properties,
					components of a composite property, and
					values for a multi-value property) to 
					"stra", starting from the top-level property
					"prop".
	Access :		Public

	Return :		void
	Parameters :	CStringArray& stra		-	The array to 
												fill
					CProMoProperty* prop	-	The property
												to save	

   ============================================================*/
{
	if (prop) {
		if (prop->IsPersistent()) {
			if (!(prop->IsMultiValue() || prop->GetType() == PROPTYPE_COMPOSITE)) {
				stra.Add(prop->GetString());
			}
			else {
				for (int i = 0; i < prop->GetChildrenCount(); i++) {
					SaveProperties(stra, prop->GetChild(i));
				}
			}
		}
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

	CString header;
	CString data;
	CFileParser::GetHeaderFromString(str, header);
	
	if (header == m_modelType) {
		CTokenizer* tok = CFileParser::Tokenize(str);
		int size = tok->GetSize();
		if (size >= 2)
		{
			int right;
			int bottom;

			tok->GetAt(0, right);
			tok->GetAt(1, bottom);

			SetVirtualSize(CSize(right, bottom));
			result = TRUE;
		}
		delete tok;
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