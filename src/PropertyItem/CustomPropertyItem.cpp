/* ==========================================================================

	Copyright © 2025 Technical University of Denmark

	CCustomPropertyItem

	Author :		Giovanni Meroni

	Purpose :		"CCustomPropertyItem" is a class that can be used to pass
					to client applications the diagram element whose property
					needs to be modified, as well as the helper function to
					perform the modification.

	Usage:			This class be used when complex logic must be invoked to 
					change the property, and no input parameter is required.
					A typical application would be displaying a custom 
					dialog, which belongs to the diagram editor library and
					NOT to the client application, which is then used to set
					the property.

   ========================================================================*/
#include "stdafx.h"
#include "CustomPropertyItem.h"

CCustomPropertyItem::CCustomPropertyItem(const CString& name, CDiagramEntity* target, CDiagramEditor* editor, SetPropertyWrapper setter)
	: CPropertyItem(name, target, editor) 
	/* ============================================================
		Function :		CCustomPropertyItem::CCustomPropertyItem
		Description :	Constructor
		Access :		Public

		Return :		void
		Parameters :	const CString& name			-	Friendly 
														name of the 
														property to 
														change (to
														be shown by 
														the client
														application 
														UI)
						CDiagramEntity* target		-	Pointer to 
														the diagram 
														element
														whose 
														property
														should be
														changed
						CDiagramEditor* editor		-	Pointer to 
														the diagram 
														editor
														object
						SetPropertyWrapper setter	-	Pointer to
														the helper
														function
														resposible
														for setting
														the property

	   ============================================================*/
{
	m_setter = setter;
}

BOOL CCustomPropertyItem::SetValue()
/* ============================================================
	Function :		CPropertyItem::SetValue
	Description :	Sets the property by invoking the helper
					function
	Access :		Public

	Return :		BOOL		-	"TRUE" if the operation
									succeeded, "FALSE" otherwise
	Parameters :	none

   ============================================================*/
{
	if (m_target && m_setter && m_editor) {
		BOOL result = m_setter(m_target, m_editor);
		if (result) {
			return TRUE;
		}
	}
	return FALSE;
}
