/* ==========================================================================

	Copyright © 2025 Technical University of Denmark

	CPropertyItem

	Author :		Giovanni Meroni

	Purpose :		"CPropertyItem" is a class that can be used to pass to
					client applications the diagram element whose property
					needs to be modified.

	Usage:			This class should not be directly instantiated. Instead,
					a derived class containing a pointer to a helper 
					function to modify the desired property should be 
					created.

   ========================================================================*/
#include "stdafx.h"
#include "PropertyItem.h"


CPropertyItem::CPropertyItem(const CString& name, CDiagramEntity* target, CDiagramEditor* editor)
/* ============================================================
	Function :		CPropertyItem::CPropertyItem
	Description :	Constructor
	Access :		Public

	Return :		void
	Parameters :	const CString& name		-	Friendly name 
												of the property 
												to change (to 
												be shown by the
												client 
												application UI)
					CDiagramEntity* target	-	Pointer to the
												diagram element
												whose property
												should be
												changed
					CDiagramEditor* editor	-	Pointer to the
												diagram editor
												object

   ============================================================*/
{
	m_name = name;
	m_editor = editor;
	m_target = target;
	m_ctrlID = 0;
}

const CString CPropertyItem::GetName()
/* ============================================================
	Function :		CPropertyItem::GetName
	Description :	Returns the friendly name of the property
	Access :		Public

	Return :		CString		-	Friendly name of the 
									property to change (to 
									be shown by the client) 
	Parameters :	none

   ============================================================*/
{
	return m_name;
}

const UINT CPropertyItem::GetCtrlID()
/* ============================================================
	Function :		CPropertyItem::GetCtrlID
	Description :	Returns the ID of the control responsible 
					for modifying the property
	Access :		Public

	Return :		UINT		-	ID of the control 
									responsible for changing
									the property
	Parameters :	none

   ============================================================*/
{
	return m_ctrlID;
}

void CPropertyItem::SetCtrlID(UINT ctrlID)
/* ============================================================
	Function :		CPropertyItem::SetCtrlID
	Description :	Sets the ID of the control responsible
					for modifying the property
	Access :		Public

	Return :		none
	Parameters :	UINT		-	ID of the control
									responsible for changing
									the property

   ============================================================*/
{
	m_ctrlID = ctrlID;
}
