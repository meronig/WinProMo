/* ==========================================================================
	CProMoClipboardHandler

	Author :		Giovanni Meroni

	Purpose :		CProMoClipboardHandler is a clipboard handler that 
					includes links in the clipboard.	

	Description :	Links are saved and loaded to/from  a separate 
					CObArray.

   ========================================================================*/
#include "stdafx.h"
#include "ProMoClipboardHandler.h"
#include "ProMoNameFactory.h"
#include "ProMoEntityContainer.h"
#include "ProMoEdgeView.h"
#include "ProMoEdgeModel.h"
#include "../DiagramEditor/GroupFactory.h"

CProMoClipboardHandler::CProMoClipboardHandler()
/* ============================================================
	Function :		CProMoClipboardHandler::CProMoClipboardHandler
	Description :	constructor
					
	Return :		void
	Parameters :	none

	Usage :			

   ============================================================*/
{
}

CProMoClipboardHandler::~CProMoClipboardHandler()
/* ============================================================
	Function :		CProMoClipboardHandler::~CProMoClipboardHandler
	Description :	destructor
					
	Return :		void
	Parameters :	none

	Usage :			

   ============================================================*/
{


}

CString CProMoClipboardHandler::GetModelType()
/* ============================================================
	Function :		CProMoClipboardHandler::GetModelType
	Description :	Returns a string representation of the
					type of model from which the elements were
					copied into the clipboard.

	Access :		Public

	Return :		CString	-	Resulting string
	Parameters :	none
   ============================================================*/
{
	return m_modelType;
}

void CProMoClipboardHandler::Copy( CDiagramEntity* obj )
/* ============================================================
	Function :		CProMoClipboardHandler::Copy
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
		newobj->SetName( CProMoNameFactory::GetID() );
		GetData()->Add( newobj );
	}

}

void CProMoClipboardHandler::Paste( CDiagramEntityContainer* container )
/* ============================================================
	Function :		CProMoClipboardHandler::Paste
	Description :	Pastes the contents of the paste array to 
					the data array.
					
	Return :		void
	Parameters :	none

	Usage :			Overridden to preserve relations between
					nodes and edges.

   ============================================================*/
{
	CProMoEntityContainer* processContainer = static_cast<CProMoEntityContainer*>(container);

	if (processContainer) {

		if (m_modelType == processContainer->GetModelType()) {

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

	}
	
}




void CProMoClipboardHandler::CopyAllSelected( CDiagramEntityContainer* container )
/* ============================================================
	Function :		CProMoClipboardHandler::CopyAllSelected
	Description :	Copies all the selected items to the paste 
					array.
					
	Return :		void
	Parameters :	none

	Usage :			Overridden to preserve relations between
					nodes and edges.

   ============================================================*/
{
	
	CDiagramClipboardHandler::CopyAllSelected( container );
	CProMoEntityContainer* processContainer = static_cast< CProMoEntityContainer* >( container );

	if (processContainer) {
		m_modelType = processContainer->GetModelType();

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

}

