/* ==========================================================================
	CProcessClipboardHandler

	Author :		Giovanni Meroni

	Purpose :		CProcessClipboardHandler is a clipboard handler that 
					includes links in the clipboard.	

	Description :	Links are saved and loaded to/from  a separate 
					CObArray.

   ========================================================================*/
#include "stdafx.h"
#include "ProcessClipboardHandler.h"
#include "LinkFactory.h"
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
	CProcessEntityContainer* processContainer = static_cast<CProcessEntityContainer*>(container);
	
	CDWordArray	oldgroup;
	CDWordArray	newgroup;

	CObArray* paste = GetData();
	CObArray clones;
	int t = 0;

	int max = static_cast<int>(paste->GetSize());
	for (t = 0; t < max; t++)
	{
		CDiagramEntity* obj = static_cast<CDiagramEntity*>(paste->GetAt(t));
		if (obj->GetGroup())
		{
			int size = static_cast<int>(oldgroup.GetSize());
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

	for (t = 0; t < max; t++)
	{
		CDiagramEntity* obj = static_cast<CDiagramEntity*>(paste->GetAt(t));
		CDiagramEntity* clone = obj->Clone();
		clones.Add(clone);

		int group = 0;
		if (obj->GetGroup())
		{
			int size = static_cast<int>(oldgroup.GetSize());
			for (int i = 0; i < size; i++)
				if (obj->GetGroup() == static_cast<int>(oldgroup[i]))
					group = newgroup[i];
		}

		clone->SetGroup(group);
		clone->SetParent(processContainer);
		processContainer->Add(clone);
	}
	
	processContainer->ReplicateRelations(paste, &clones);

	
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
	CProcessEntityContainer* processContainer = static_cast< CProcessEntityContainer* >( container );
	/*CObArray* links = flow->GetLinkArray();

	int max = links->GetSize();
	for( int t = 0; t < max ; t++ )
	{
		CFlowchartLink* link = static_cast< CFlowchartLink* >( links->GetAt(t ) );
		m_pasteLinks.Add( link->Clone() );
	}*/

	CObArray originals;
	CObArray* paste = GetData();
	CObArray* arr = processContainer->GetData();

	int max = static_cast<int>(arr->GetSize());
	
	for (int t = 0; t < max; t++)
	{
		CDiagramEntity* obj = static_cast<CDiagramEntity*>(arr->GetAt(t));
		if (obj->IsSelected())
		{
			originals.Add(obj);
		}
	}
	
	processContainer->ReplicateRelations(&originals, paste);

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

