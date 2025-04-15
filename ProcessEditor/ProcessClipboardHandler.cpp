/* ==========================================================================
	CProcessClipboardHandler

	Author :		Giovanni Meroni

	Purpose :		CProcessClipboardHandler is a clipboard handler that 
					includes links in the clipboard.	

	Description :	Links are saved and loaded to/from  a separate 
					CObArray.

   ========================================================================*/
#include "../stdafx.h"
#include "ProcessClipboardHandler.h"
#include "LinkFactory.h"
#include "../DiagramEditor/DiagramEntityContainer.h"
#include "ProcessEntityContainer.h"
#include "ProcessLineEdgeView.h"
#include "ProcessLineEdgeModel.h"
#include "../DiagramEditor/GroupFactory.h"

CProcessClipboardHandler::CProcessClipboardHandler()
/* ============================================================
	Function :		CProcessClipboardHandler::CProcessClipboardHandler
	Description :	constructor
					
	Return :		void
	Parameters :	none

	Usage :			

   ============================================================*/
{
}

CProcessClipboardHandler::~CProcessClipboardHandler()
/* ============================================================
	Function :		CProcessClipboardHandler::~CProcessClipboardHandler
	Description :	destructor
					
	Return :		void
	Parameters :	none

	Usage :			

   ============================================================*/
{

	ClearPaste();

}

void CProcessClipboardHandler::Copy( CDiagramEntity* obj )
/* ============================================================
	Function :		CProcessClipboardHandler::Copy
	Description :	Copies obj to the paste array
					
	Return :		void
	Parameters :	CDiagramEntity* obj	-	Object to copy.
					
	Usage :			Overridden to assign a new id.

   ============================================================*/
{
	ASSERT(false);

	if( obj )
	{
		ClearPaste();
		CDiagramEntity* newobj = obj->Clone();
		newobj->Select( TRUE );
		newobj->MoveRect( 10, 10 );
		newobj->SetName( CLinkFactory::GetID() );
		GetData()->Add( newobj );
	}

}

void CProcessClipboardHandler::Paste( CDiagramEntityContainer* container )
/* ============================================================
	Function :		CProcessClipboardHandler::Paste
	Description :	Pastes the contents of the paste array to 
					the data array.
					
	Return :		void
	Parameters :	none

	Usage :			Overridden to paste links as well.

   ============================================================*/
{
	CDWordArray	oldgroup;
	CDWordArray	newgroup;

	CObArray* paste = GetData();
	CObArray clones;

	int max = paste->GetSize();
	for (int t = 0; t < max; t++)
	{
		CDiagramEntity* obj = static_cast<CDiagramEntity*>(paste->GetAt(t));
		if (obj->GetGroup())
		{
			int size = oldgroup.GetSize();
			BOOL found = FALSE;
			for (int i = 0; i < size; i++)
				if (obj->GetGroup() == static_cast<int> (oldgroup[i]))
					found = TRUE;

			if (!found)
			{
				oldgroup.Add(obj->GetGroup());
				newgroup.Add(CGroupFactory::GetNewGroup());
			}
		}
	}

	for (int t = 0; t < max; t++)
	{
		CDiagramEntity* obj = static_cast<CDiagramEntity*>(paste->GetAt(t));
		CDiagramEntity* clone = obj->Clone();
		clones.Add(clone);

		int group = 0;
		if (obj->GetGroup())
		{
			int size = oldgroup.GetSize();
			for (int i = 0; i < size; i++)
				if (obj->GetGroup() == static_cast<int>(oldgroup[i]))
					group = newgroup[i];
		}

		clone->SetGroup(group);
		clone->SetParent(container);
		container->Add(clone);
	}
	//todo: reactivate
	ReplicateRelations(paste, &clones);

	//CDiagramClipboardHandler::Paste( container );
	//int max = m_pasteLinks.GetSize();
	CProcessEntityContainer* flow = static_cast< CProcessEntityContainer* >( container );
	/*for( int t = 0 ; t < max ; t++ )
		flow->AddLink( ( static_cast< CFlowchartLink* >( m_pasteLinks[ t ] ) )->Clone() );*/

}


void CProcessClipboardHandler::ReplicateRelations(CObArray* source, CObArray* destination) {
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

void CProcessClipboardHandler::CopyAllSelected( CDiagramEntityContainer* container )
/* ============================================================
	Function :		CProcessClipboardHandler::CopyAllSelected
	Description :	Copies all the selected items to the paste 
					array.
					
	Return :		void
	Parameters :	none

	Usage :			Overridden to add links as well. New ids 
					are assigned to the copied objects, and the 
					copied links are updated.

   ============================================================*/
{
	
	CDiagramClipboardHandler::CopyAllSelected( container );
	CProcessEntityContainer* flow = static_cast< CProcessEntityContainer* >( container );
	/*CObArray* links = flow->GetLinkArray();

	int max = links->GetSize();
	for( int t = 0; t < max ; t++ )
	{
		CFlowchartLink* link = static_cast< CFlowchartLink* >( links->GetAt(t ) );
		m_pasteLinks.Add( link->Clone() );
	}*/

	CObArray originals;
	CObArray* paste = GetData();
	CObArray* arr = container->GetData();

	int max = arr->GetSize();
	
	for (int t = 0; t < max; t++)
	{
		CDiagramEntity* obj = static_cast<CDiagramEntity*>(arr->GetAt(t));
		if (obj->IsSelected())
		{
			originals.Add(obj);
		}
	}
	//todo: reactivate
	ReplicateRelations(&originals, paste);


	//for( int t = 0; t < max ; t++ )
	//{
	//	CDiagramEntity* obj = static_cast< CDiagramEntity* >( paste->GetAt( t ) );
	//	CString newID = CLinkFactory::GetID();

	//	/*int maxlinks = m_pasteLinks.GetSize();
	//	for( int i = 0 ; i < maxlinks ; i++ )
	//	{
	//		CFlowchartLink* link = static_cast< CFlowchartLink* >( m_pasteLinks[ i ] );
	//		if( link->from == obj->GetName() )
	//			link->from = newID;
	//		if( link->to == obj->GetName() )
	//			link->to = newID;
	//	}*/

	//	obj->SetName( newID );

	//}

}

void CProcessClipboardHandler::ClearPaste()
/* ============================================================
	Function :		CProcessClipboardHandler::ClearPaste
	Description :	Clears the paste array.
					
	Return :		void
	Parameters :	none

	Usage :			Overridden to clear the paste link array as 
					well.

   ============================================================*/
{

	CDiagramClipboardHandler::ClearPaste();

	/*int max = m_pasteLinks.GetSize();
	for( int t = max - 1 ; t >= 0 ; t-- )
		delete m_pasteLinks[t];

	m_pasteLinks.RemoveAll();*/

}

