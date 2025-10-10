/* ==========================================================================

	Copyright © 2025 Technical University of Denmark

	CPropertyItem

	Author :		Giovanni Meroni

	Purpose :		"CProMoProperty" is a class to keep track of custom
					properties and on how they should be displayed.

   ========================================================================*/
#include "stdafx.h"
#include "ProMoProperty.h"

CProMoProperty::CProMoProperty(const CString& name, const unsigned int& type, const COleVariant& initialValue, const BOOL& readOnly, 
	const BOOL& showLabel, const BOOL& persistent, IProMoPropertyOwner* owner, 
	ValidationFuction valFct, ChangeFuction changeFct, EditFunction editFct)
/* ============================================================
	Function :		CProMoProperty::CProMoProperty
	Description :	Constructor
	Access :		Public

	Return :		void
	Parameters :	const CString& name			-	Name of the
													property
													to change
					unsigned int& type			-	Type of the
													property
					COleVariant& initialValue	-	Initial value
													of the
													property
					BOOL& readOnly				-	"TRUE" if the
													property is
													read-only
					BOOL& showLabel				-	"TRUE" if the
													property should
													be shown as a
													label
					BOOL& persistent			-	"TRUE" if the
													property should
													be serialized
					IProMoPropertyOwner* owner	-	Pointer to the
													object to which
													the property
													belongs
					ValidationFuction valFct	-	Pointer to the
													helper function
													to validate
													the property
													value before
													setting it
					ChangeFuction changeFct		-	Pointer to the
													helper function
													to perform
													operations after
													the property
													value has
													changed
					EditFunction editFct		-	Pointer to the
													helper function
													to invoke when
													the property
													needs to be
													edited	

   ============================================================*/
{
	m_name = name;
	m_type = type;
	m_value = initialValue;
	m_readOnly = readOnly;
	m_labelVisible = showLabel;
	m_validationFunction = valFct;
	m_changeFunction = changeFct;
	m_persistent = persistent;
	m_owner = owner;
	m_editFunction = editFct;
}

CProMoProperty::CProMoProperty(const CString& name, const unsigned int& type, const COleVariant& initialValue, const BOOL& readOnly,
	const BOOL& showLabel, const BOOL& persistent, IProMoPropertyOwner* owner,
	ValidationFuction valFct, ChangeFuction changeFct)
/* ============================================================
	Function :		CProMoProperty::CProMoProperty
	Description :	Constructor
	Access :		Public

	Return :		void
	Parameters :	const CString& name			-	Name of the
													property
													to change
					unsigned int& type			-	Type of the
													property
					COleVariant& initialValue	-	Initial value
													of the
													property
					BOOL& readOnly				-	"TRUE" if the
													property is
													read-only
					BOOL& showLabel				-	"TRUE" if the
													property should
													be shown as a
													label
					BOOL& persistent			-	"TRUE" if the
													property should
													be serialized
					IProMoPropertyOwner* owner	-	Pointer to the
													object to which
													the property
													belongs	
					ValidationFuction valFct	-	Pointer to the
													helper function
													to validate
													the property
													value before
													setting it
					ChangeFuction changeFct		-	Pointer to the
													helper function
													to perform
													operations after
													the property
													value has
													changed

   ============================================================*/
{
	m_name = name;
	m_type = type;
	m_value = initialValue;
	m_readOnly = readOnly;
	m_labelVisible = showLabel;
	m_validationFunction = valFct;
	m_changeFunction = changeFct;	
	m_persistent = persistent;
	m_owner = owner;
	m_editFunction = NULL;
}

CProMoProperty::CProMoProperty(const CString& name, const unsigned int& type, const COleVariant& initialValue, const BOOL& readOnly, 
	const BOOL& showLabel, const BOOL& persistent, IProMoPropertyOwner* owner)
/* ============================================================
	Function :		CProMoProperty::CProMoProperty
	Description :	Constructor
	Access :		Public

	Return :		void
	Parameters :	const CString& name			-	Name of the
													property
													to change
					unsigned int& type			-	Type of the
													property
					COleVariant& initialValue	-	Initial value
													of the
													property
					BOOL& readOnly				-	"TRUE" if the
													property is
													read-only
					BOOL& showLabel				-	"TRUE" if the
													property should
													be shown as a
													label
					BOOL& persistent			-	"TRUE" if the
													property should
													be serialized
					IProMoPropertyOwner* owner	-	Pointer to the
													object to which
													the property
													belongs

   ============================================================*/
{
	m_name = name;
	m_type = type;
	m_value = initialValue;
	m_readOnly = readOnly;
	m_labelVisible = showLabel;
	m_validationFunction = NULL;
	m_changeFunction = NULL;
	m_persistent = persistent;
	m_owner = owner;
	m_editFunction = NULL;
}

BOOL CProMoProperty::SetValue(const COleVariant& val)
/* ============================================================
	Function :		CProMoProperty::SetValue
	Description :	Sets the property by invoking the helper
					function
	Access :		Public

	Return :		BOOL				-	"TRUE" if the 
											operation succeeded,
											"FALSE" otherwise
	Parameters :	COleVariant& val	-	The value to set for
											the property

   ============================================================*/
{
	if (m_readOnly)
		return FALSE;
	if (m_value == val)
		return TRUE; // no change
	if (m_validationFunction && !m_validationFunction(this, val))
		return FALSE;
	m_value = val;
	if (m_changeFunction)
		m_changeFunction(this, val);
	
	if (m_owner)
		m_owner->OnPropertyChanged(this);

	return TRUE;
	
}

COleVariant& CProMoProperty::GetValue()
/* ============================================================
	Function :		CProMoProperty::GetValue
	Description :	Gets the value currently associated
					to the property
	Access :		Public

	Return :		COleVariant&	-	the current value for
										the property
	Parameters :	none

   ============================================================*/
{
	return m_value;
}

const CString& CProMoProperty::GetName()
/* ============================================================
	Function :		CProMoProperty::GetName
	Description :	Gets the name of the property
	Access :		Public

	Return :		CString&	-	the name of the property
	Parameters :	none

   ============================================================*/
{
	return m_name;
}

const unsigned int& CProMoProperty::GetType()
/* ============================================================
	Function :		CProMoProperty::GetType
	Description :	Gets the type of the property
	Access :		Public

	Return :		unsigned int&	-	the type of the property
	Parameters :	none

   ============================================================*/
{
	return m_type;
}

const BOOL& CProMoProperty::IsReadOnly()
/* ============================================================
	Function :		CProMoProperty::IsReadOnly
	Description :	Returns "TRUE" if the property is
					read-only
	Access :		Public

	Return :		BOOL&	-	"TRUE" if the property is
								read-only, "FALSE" otherwise
	Parameters :	none

   ============================================================*/
{
	return m_readOnly;
}

const BOOL& CProMoProperty::IsLabelVisible()
/* ============================================================
	Function :		CProMoProperty::IsLabelVisible
	Description :	Returns "TRUE" if no label should be
					shown for the property
	Access :		Public

	Return :		BOOL&	-	"TRUE" if no label should be
								visible, "FALSE" otherwise
	Parameters :	none

   ============================================================*/
{
	return m_labelVisible;
}

const BOOL& CProMoProperty::IsPersistent()
/* ============================================================
	Function :		CProMoProperty::IsPersistent
	Description :	Returns "TRUE" if the property should be
					serialized
	Access :		Public

	Return :		BOOL&	-	"TRUE" if the property should be
								serialized, "FALSE" otherwise
	Parameters :	none

   ============================================================*/
{
	return m_persistent;
}

const BOOL& CProMoProperty::HasHandler()
/* ============================================================
	Function :		CProMoProperty::HasHandler
	Description :	Returns "TRUE" if the property has an
					associated handler function
	Access :		Public

	Return :		BOOL&	-	"TRUE" if the property has an
								associated handler function,
								"FALSE" otherwise
	Parameters :	none

   ============================================================*/
{
	if (m_editFunction) {
		return TRUE;
	}
	return FALSE;
}

BOOL CProMoProperty::InvokeHandler(CWnd* parent)
/* ============================================================
	Function :		CProMoProperty::InvokeHandler
	Description :	Invokes the handler function associated
					to the property, which is used to determine
					the value to be set for the property.
	Access :		Public

	Return :		BOOL			-	"TRUE" if the operation
										succeeded, "FALSE"
										otherwise
	Parameters :	CWnd* parent	-	The parent window
										for any dialog
										that might be
										created by the
										handler function

   ============================================================*/
{
	if (m_editFunction)
		return m_editFunction(this, parent);
	return FALSE;
}

void CProMoProperty::AddOption(const COleVariant& option)
/* ============================================================
	Function :		CProMoProperty::AddOption
	Description :	Adds an option to the list of possible
					values that the property can assume. Can be
					used by the client application to build
					list and combo box controls to set the
					property
	Access :		Public

	Return :		none
	Parameters :	COleVariant& val	-	The value to be 
											added to the list 
											of possible options

   ============================================================*/
{
	m_options.Add(option);
}

int CProMoProperty::GetOptionsCount()
/* ============================================================
	Function :		CProMoProperty::GetValue
	Description :	Returns the number of options available for
					the property
	Access :		Public

	Return :		int		-	the number of available options
								for the property
	Parameters :	none

   ============================================================*/
{
	return m_options.GetSize();
}

const COleVariant& CProMoProperty::GetOption(const int& index)
/* ============================================================
	Function :		CProMoProperty::GetOption
	Description :	Returns the option having the specified
					index
	Access :		Public

	Return :		COleVariant&	-	the option having the
										specified index
	Parameters :	int index		-	the index for the option
										to be returned

   ============================================================*/
{
	if (index < m_options.GetSize() - 1)
		return m_options.GetAt(index);
	return m_value;
}
