/* ==========================================================================

	Copyright © 2025 Technical University of Denmark

	CPropertyItem

	Author :		Giovanni Meroni

	Purpose :		"CProMoModelProperty" is a class to keep track of custom
					model properties and on how they should be displayed.

   ========================================================================*/
#include "stdafx.h"
#include "ProMoModelProperty.h"

CProMoModelProperty::CProMoModelProperty(const CString& name, const unsigned int& type, const COleVariant& initialValue, const BOOL& readOnly, 
	const BOOL& showLabel, const BOOL& persistent, CProMoModel* model, 
	ValidationFuction validationFct, ChangeFuction changeFct)
/* ============================================================
	Function :		CProMoModelProperty::CProMoModelProperty
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
					CProMoModel* model			-	Pointer to the
													model to which
													the property
													belongs	
					ValidationFuction			-	Pointer to the
													helper function
													to validate
													the property
													value before
													setting it
					ChangeFuction				-	Pointer to the
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
	m_validationFunction = validationFct;
	m_changeFunction = changeFct;	
	m_persistent = persistent;
	m_model = model;
}

CProMoModelProperty::CProMoModelProperty(const CString& name, const unsigned int& type, const COleVariant& initialValue, const BOOL& readOnly, const BOOL& showLabel, const BOOL& persistent)
/* ============================================================
	Function :		CProMoModelProperty::CProMoModelProperty
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
	m_model = NULL;
}

BOOL CProMoModelProperty::SetValue(const COleVariant& val)
/* ============================================================
	Function :		CProMoModelProperty::SetValue
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
	if (m_validationFunction && !m_validationFunction(this, val))
		return FALSE;

	m_value = val;
	if (m_changeFunction)
		m_changeFunction(this, val);

	return TRUE;
	
}

COleVariant& CProMoModelProperty::GetValue()
/* ============================================================
	Function :		CProMoModelProperty::GetValue
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

const CString& CProMoModelProperty::GetName()
/* ============================================================
	Function :		CProMoModelProperty::GetName
	Description :	Gets the name of the property
	Access :		Public

	Return :		CString&	-	the name of the property
	Parameters :	none

   ============================================================*/
{
	return m_name;
}

const unsigned int& CProMoModelProperty::GetType()
/* ============================================================
	Function :		CProMoModelProperty::GetType
	Description :	Gets the type of the property
	Access :		Public

	Return :		unsigned int&	-	the type of the property
	Parameters :	none

   ============================================================*/
{
	return m_type;
}

const BOOL& CProMoModelProperty::IsReadOnly()
/* ============================================================
	Function :		CProMoModelProperty::IsReadOnly
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

const BOOL& CProMoModelProperty::IsLabelVisible()
/* ============================================================
	Function :		CProMoModelProperty::IsLabelVisible
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

const BOOL& CProMoModelProperty::IsPersistent()
/* ============================================================
	Function :		CProMoModelProperty::IsPersistent
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

void CProMoModelProperty::AddOption(const COleVariant& option)
/* ============================================================
	Function :		CProMoModelProperty::AddOption
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

int CProMoModelProperty::GetOptionsCount()
/* ============================================================
	Function :		CProMoModelProperty::GetValue
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

const COleVariant& CProMoModelProperty::GetOption(const int& index)
/* ============================================================
	Function :		CProMoModelProperty::GetOption
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
