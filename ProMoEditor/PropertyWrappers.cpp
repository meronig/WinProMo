#include "StdAfx.h"
#include "PropertyWrappers.h"
#include "ProMoBlockView.h"
#include "ProMoEdgeView.h"
#include "ProMoBlockModel.h"
#include "ProMoEdgeModel.h"

BOOL SetShapeTitle(CDiagramEntity* entity, CDiagramEditor* editor, const CString& val)
/* ============================================================
	Function :		SetShapeTitle
	Description :	Wrapper function to set object's title.

	Return :		BOOL					-	TRUE if the
												operation
												succeeded
	Parameters :	CDiagramEntity* entity	-	The object to
												modify
					CDiagramEditor* editor	-	The editor to
												which the
												object to modify
												belongs
					CString& val			-	The new title

	Usage :			Pass a pointer to this function when
					bulding the CPropertyItem object to populate
					the properties dialog.

   ============================================================*/
{
	if (entity) {
		entity->SetTitle(val);
		return TRUE;
	}
	return FALSE;
}

/* ============================================================
	Function :		SetShapeName
	Description :	Wrapper function to set object's name.

	Return :		BOOL					-	TRUE if the
												operation
												succeeded
	Parameters :	CDiagramEntity* entity	-	The object to
												modify
					CDiagramEditor* editor	-	The editor to
												which the
												object to modify
												belongs
					CString& val			-	The new name

	Usage :			Pass a pointer to this function when
					bulding the CPropertyItem object to populate
					the properties dialog.

   ============================================================*/
BOOL SetShapeName(CDiagramEntity* entity, CDiagramEditor* editor, const CString& val)
{
	if (!entity || !editor) {
		return FALSE;
	}

	if (val.IsEmpty()) {
		return FALSE;
	}

	// Check for unicity
	int i;
	for (i = 0; i < editor->GetObjectCount(); i++) {
		CDiagramEntity* e = editor->GetObject(i);
		if (e) {
			if (e->GetName() == val) {
				return FALSE;
			}
			
			// Uncomment these lines if unicity should apply also to model 
			// elements (and not just on view elements)

			/*
			CProMoBlockView* bv = dynamic_cast<CProMoBlockView*>(e);
			if (bv) {
				if (bv->GetModel()) {
					if (bv->GetModel()->GetName() == val) {
						return FALSE;
					}
				}
			}
			CProMoEdgeView* ev = dynamic_cast<CProMoEdgeView*>(e);
			if (ev) {
				if (ev->GetModel()) {
					if (ev->GetModel()->GetName() == val) {
						return FALSE;
					}
				}
			}
			*/
		}
	}
	entity->SetName(val);
	return TRUE;
	
}