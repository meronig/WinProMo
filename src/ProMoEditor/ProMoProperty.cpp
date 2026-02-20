/* ==========================================================================

	Copyright © 2025 Technical University of Denmark

	CPropertyItem

	Author :		Giovanni Meroni

	Purpose :		"CProMoProperty" is a class to keep track of custom
					properties and on how they should be displayed.
					Properties are hierarchical, i.e. a property can have
					multiple child properties. Child properties represent
					either sub-properties of a composite property, or values
					of a multi-value property. 
					For multi-value properties, child properties must be of
					the same type as the parent, and their name must be an 
					incremental number (0, 1, 2, ...). The structure of a 
					value a multi-value property is determined by a 
					template property, which is cloned when a new value is 
					added.
					Properties can have a validation function, which is called
					before the value is changed, and a change function, 
					which is called after the value has changed. Properties
					can also have an edit function, which is called to
					set the property value through custom code.

   ========================================================================*/
#include "stdafx.h"
#include "ProMoProperty.h"
#include "../FileUtils/FileParser.h"
#include "../Automation/ProMoPropertyAuto.h"

CProMoProperty::CProMoProperty()
/* ============================================================
	Function :		CProMoProperty::CProMoProperty
	Description :	Constructor
	Access :		Protected

	Return :		void
	Parameters :	none

   ============================================================*/
{
	m_type = PROPTYPE_UNKNOWN;
	m_value = CVariantWrapper();
	m_readOnly = FALSE;
	m_labelVisible = TRUE;
	m_validationFunction = NULL;
	m_changeFunction = NULL;
	m_persistent = TRUE;
	m_owner = NULL;
	m_editFunction = NULL;
	m_parentProperty = NULL;
	m_template = NULL;

	m_autoObject = NULL;

}



CProMoProperty::CProMoProperty(const CString& name, const unsigned int& type, const CVariantWrapper& initValue, const BOOL& readOnly, 
	const BOOL& showLabel, const BOOL& persistent, IProMoPropertyOwner* owner, 
	ValidationFuction valFct, ChangeFuction changeFct, EditFunction editFct,
	CProMoProperty* parent, CProMoProperty* templ)
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
					CVariantWrapper& initValue	-	Initial value
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
					CProMoProperty* parent		-	Pointer to the
													parent property
													(if any)
					CProMoProperty* templ		-	Pointer to the
													template property
													(if any)

   ============================================================*/
{
	m_name = name;
	m_type = type;
	m_value = initValue;
	m_readOnly = readOnly;
	m_labelVisible = showLabel;
	m_validationFunction = valFct;
	m_changeFunction = changeFct;
	m_persistent = persistent;
	m_owner = owner;
	m_editFunction = editFct;
	if (templ) {
		m_template = templ->Clone();
	}
	else {
		m_template = NULL;
	}

	m_autoObject = NULL;

	if (parent) {
		if (parent->m_type == PROPTYPE_COMPOSITE || (parent->IsMultiValue() && parent->m_type == type && !IsMultiValue())) {
			m_parentProperty = parent;
			parent->m_childProperties.Add(this);
			return;
		}
	}
	m_parentProperty = NULL;

	
}

CProMoProperty::CProMoProperty(const CString& name, const unsigned int& type, const CVariantWrapper& initValue, const BOOL& readOnly,
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
					CVariantWrapper& initValue	-	Initial value
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
	m_value = initValue;
	m_readOnly = readOnly;
	m_labelVisible = showLabel;
	m_validationFunction = valFct;
	m_changeFunction = changeFct;	
	m_persistent = persistent;
	m_owner = owner;
	m_editFunction = NULL;
	m_parentProperty = NULL;
	m_template = NULL;

	m_autoObject = NULL;

}

CProMoProperty::CProMoProperty(const CString& name, const unsigned int& type, const CVariantWrapper& initValue, const BOOL& readOnly, 
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
					CVariantWrapper& initValue	-	Initial value
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
	m_value = initValue;
	m_readOnly = readOnly;
	m_labelVisible = showLabel;
	m_validationFunction = NULL;
	m_changeFunction = NULL;
	m_persistent = persistent;
	m_owner = owner;
	m_editFunction = NULL;
	m_parentProperty = NULL;
	m_template = NULL;

	m_autoObject = NULL;

}

CProMoProperty::~CProMoProperty()
/* ============================================================
	Function :		CProMoProperty::~CProMoProperty
	Description :	Destructor
	Access :		Public

	Return :		void

   ============================================================*/
{
	ClearChildren();
	if (m_template) {
		delete m_template;
		m_template = NULL;
	}
	ReleaseAutomationObject();
}

BOOL CProMoProperty::SetValue(const CVariantWrapper& val)
/* ============================================================
	Function :		CProMoProperty::SetValue
	Description :	Sets the property by invoking the helper
					function
	Access :		Public

	Return :		BOOL				-	"TRUE" if the 
											operation succeeded,
											"FALSE" otherwise
	Parameters :	CVariantWrapper& val	-	The value to set for
											the property

   ============================================================*/
{
	if (m_type == PROPTYPE_COMPOSITE)
		return FALSE; // cannot set value for composite properties
	if (IsMultiValue())
		return FALSE; // cannot set value for multivalue properties
	if (m_readOnly)
		return FALSE;
	if (m_validationFunction && !m_validationFunction(this, val))
		return FALSE;
	m_value = val;
	if (m_changeFunction)
		m_changeFunction(this, val);
	
	if (m_owner)
		m_owner->OnPropertyChanged(this);

	return TRUE;
	
}

CVariantWrapper& CProMoProperty::GetValue()
/* ============================================================
	Function :		CProMoProperty::GetValue
	Description :	Gets the value currently associated
					to the property
	Access :		Public

	Return :		CVariantWrapper&	-	the current value for
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

IProMoPropertyOwner* CProMoProperty::GetPropertyOwner() const
/* ============================================================
	Function :		CProMoProperty::GetPropertyOwner
	Description :	Gets the pointer to the object to which
					the property belongs
	Access :		Public
	Return :		IProMoPropertyOwner*	-	the pointer to the
											object to which the
											property belongs
	Parameters :	none
   ============================================================*/
{
	return m_owner;
}

BOOL CProMoProperty::IsReadOnly() const
/* ============================================================
	Function :		CProMoProperty::IsReadOnly
	Description :	Returns "TRUE" if the property is
					read-only
	Access :		Public

	Return :		BOOL	-	"TRUE" if the property is
								read-only, "FALSE" otherwise
	Parameters :	none

   ============================================================*/
{
	return m_readOnly;
}

BOOL CProMoProperty::IsLabelVisible() const
/* ============================================================
	Function :		CProMoProperty::IsLabelVisible
	Description :	Returns "TRUE" if no label should be
					shown for the property
	Access :		Public

	Return :		BOOL	-	"TRUE" if no label should be
								visible, "FALSE" otherwise
	Parameters :	none

   ============================================================*/
{
	return m_labelVisible;
}

BOOL CProMoProperty::IsPersistent() const
/* ============================================================
	Function :		CProMoProperty::IsPersistent
	Description :	Returns "TRUE" if the property should be
					serialized
	Access :		Public

	Return :		BOOL	-	"TRUE" if the property should be
								serialized, "FALSE" otherwise
	Parameters :	none

   ============================================================*/
{
	return m_persistent;
}

BOOL CProMoProperty::IsComposite() const
/* ============================================================
	Function :		CProMoProperty::IsComposite
	Description :	Returns "TRUE" if the property is a
					composite property, i.e. it can have
					child properties
	Access :		Public
	Return :		BOOL	-	"TRUE" if the property is a
								composite property, "FALSE"
								otherwise
	Parameters :	none
   ============================================================*/
{
	return m_type == PROPTYPE_COMPOSITE;
}

BOOL CProMoProperty::HasHandler() const
/* ============================================================
	Function :		CProMoProperty::HasHandler
	Description :	Returns "TRUE" if the property has an
					associated handler function
	Access :		Public

	Return :		BOOL	-	"TRUE" if the property has an
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

BOOL CProMoProperty::IsMultiValue() const
/* ============================================================
	Function :		CProMoProperty::IsMultivalue
	Description :	Returns "TRUE" if the property accepts
					multiple values
	Access :		Public

	Return :		BOOL	-	"TRUE" if the property is 
								multi-value, "FALSE" otherwise
	Parameters :	none

   ============================================================*/
{
	if (m_template && m_type == m_template->m_type) {
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

CProMoProperty* CProMoProperty::Clone()
/* ============================================================
	Function :		CProMoProperty::Clone
	Description :	Clone this object to a new object.
	Access :		Public

	Return :		CProMoProperty*	-	The new object.
	Parameters :	none

	Usage :			Call to create a clone of the object. The
					caller will have to delete the object.

   ============================================================*/
{
	int i;
	CProMoProperty* obj = new CProMoProperty;
	obj->m_name = m_name;
	obj->m_type = m_type;
	obj->m_value = m_value;
	obj->m_changeFunction = m_changeFunction;
	obj->m_editFunction = m_editFunction;
	obj->m_owner = m_owner;
	obj->m_readOnly = m_readOnly;
	obj->m_labelVisible = m_labelVisible;
	obj->m_validationFunction = m_validationFunction;
	obj->m_persistent = m_persistent;
	
	// Clone options
	for (i = 0; i < m_options.GetSize(); ++i) {
		CProMoProperty* option = GetOption(i);
		if (option) {
			obj->m_options.Add(option->Clone());
		}
	}

	// Recursively clone children
	for (i = 0; i < m_childProperties.GetSize(); ++i)
	{
		CProMoProperty* child = (CProMoProperty*)m_childProperties.GetAt(i);
		if (child)
		{
			CProMoProperty* clonedChild = child->Clone();
			obj->m_childProperties.Add(clonedChild);
			clonedChild->m_parentProperty = obj;
		}
	}

	// Clone template if any
	if (m_template) {
		obj->m_template = m_template->Clone();
	}
	else {
		obj->m_template = NULL;
	}

	return obj;
}

CProMoProperty* CProMoProperty::AddChild()
/* ============================================================
	Function :		CProMoProperty::AddChild
	Description :	Adds a new child property to the
					current property. The new property is a
					clone of the template property. Valid only
					for multi-value properties.
	Access :		Public

	Return :		CProMoProperty*	-	The new child property.
	Parameters :	none

	Usage :			Call to add a new value to multi-value 
					properties.

   ============================================================*/
{
	if (m_readOnly || !m_template) {
		return NULL; // cannot add child properties to read-only properties
	}
	
	CProMoProperty* newChild = m_template->Clone();

	// Determine next numeric index
	int nextIndex = static_cast<int>(m_childProperties.GetSize());
	CString numberedName;
	numberedName.Format(_T("%d"), nextIndex);
	newChild->m_name = numberedName;
		
	newChild->m_parentProperty = this;
	m_childProperties.Add(newChild);
	return newChild;
}

void CProMoProperty::ClearChildren()
/* ============================================================
	Function :		CProMoProperty::ClearChildren
	Description :	Removes all child properties of the
					current property. Has effect only
					for multi-value properties.
	Access :		Public

	Return :		void
	Parameters :	none

	Usage :			Call to remove all values for multi-value
					properties.

   ============================================================*/
{
	for (int i = 0; i < m_childProperties.GetSize(); i++) {
		CProMoProperty* prop = (CProMoProperty*)m_childProperties.GetAt(i);
		if (prop) {
			delete prop;
		}
	}
	m_childProperties.RemoveAll();
}

int CProMoProperty::GetChildrenCount() const
/* ============================================================
	Function :		CProMoProperty::GetChildrenCount
	Description :	Returns the number of children available for
					the property. Only applicable to composite
					and multi-value properties
					
	Access :		Public

	Return :		int		-	the number of available children
								for the property
	Parameters :	none

   ============================================================*/
{
	return static_cast<int>(m_childProperties.GetSize());
}

CProMoProperty* CProMoProperty::GetChild(const int& index) const
/* ============================================================
	Function :		CProMoProperty::GetChild
	Description :	Returns the children having the specified
					index. Only applicable to composite and
					multi-value properties
	Access :		Public

	Return :		CProMoProperty*	-	the child having the
										specified index
	Parameters :	int index		-	the index for the child
										to be returned

   ============================================================*/
{
	if (index < m_childProperties.GetSize()) {
		return (CProMoProperty*)m_childProperties.GetAt(index);
	}
	return NULL;
}

CProMoProperty* CProMoProperty::FindChild(const CString& name) const
/* ============================================================
	Function :		CProMoProperty::FindChild
	Description :	Returns the child having the specified name.
					Only applicable to composite and multi-value
					properties. The search is performed only on
					the direct children of the property, and does
					not include grandchildren or other descendants.
	Access :		Public
	Return :		CProMoProperty*	-	the child having the
										specified name
	Parameters :	CString name	-	the name for the child
										to be returned
   ============================================================*/
{
	CProMoProperty* result = NULL;
	for (int i = 0; i < m_childProperties.GetSize(); i++) {
		CProMoProperty* prop = dynamic_cast<CProMoProperty*>(m_childProperties.GetAt(i));
		if (prop) {
			result = FindChildR(name, prop, prop);
			if (result) {
				return result;
			}
		}
	}
	return NULL;
}

void CProMoProperty::GetChildrenNames(CStringArray& array, const BOOL& recursive) const
/* ============================================================
	Function :		CProMoProperty::GetChildrenNames
	Description :	Fills "array" with the names of the child
					properties of the current property. If
					"recursive" is "TRUE", also fills the array
					with the names of all descendant properties,
					prefixed with the path to reach them (e.g.,
					"ChildProperty.0.GrandChildProperty").
	Access :		Public
	Return :		void
	Parameters :	CStringArray& array	-	the array to be filled
					BOOL& recursive		-	if "TRUE", also fills
											the array with the
											names of all
											descendant
											properties, with
											the path to reach
											them
   ============================================================*/
{
	for (int i = 0; i < m_childProperties.GetSize(); i++) {
		CProMoProperty* prop = dynamic_cast<CProMoProperty*>(m_childProperties.GetAt(i));
		if (recursive) {
			GetChildrenNamesR(array, prop, prop);
		}
		else {
			if (prop) {
				array.Add(prop->GetFullName());
			}
		}
	}
}

CString CProMoProperty::GetFullName() const
/* ============================================================
	Function :		CProMoProperty::GetFullName
	Description :	Gets the full name of the property, 
					including the path representing parent 
					properties (e.g., "ParentProperty.0.Property").
	Access :		Public

	Return :		CString&	-	the full name of the property
	Parameters :	none

   ============================================================*/
{
	CString result = m_name;
	const CProMoProperty* parent = m_parentProperty;

	while (parent)
	{
		// Prepend parent's name
		result = parent->m_name + _T(".") + result;
		parent = parent->m_parentProperty;
	}

	return result;
}

CProMoProperty* CProMoProperty::AddOption()
/* ============================================================
	Function :		CProMoProperty::AddOption
	Description :	Adds an option to the list of possible
					values that the property can assume. Can be
					used by the client application to build
					list and combo box controls to set the
					property.
	Access :		Public

	Return :		CProMoProperty*		-	The new option being
											added
	Parameters :	none

   ============================================================*/
{
	CProMoProperty* option = NULL;
	if (IsMultiValue()) {
		if (!m_template) {
			return NULL;
		}
		//An option has the same structure as a template
		option = m_template->Clone();
	}
	else {
		//An option has the same structure as the property itself
		option = this->Clone();
	}
	if (option) {
		option->m_parentProperty = this;
		option->m_persistent = FALSE;
		m_options.Add(option);
	}
	return option;
}

int CProMoProperty::GetOptionsCount() const
/* ============================================================
	Function :		CProMoProperty::GetOptionsCount
	Description :	Returns the number of options available for
					the property.
	Access :		Public

	Return :		int		-	the number of available options
								for the property
	Parameters :	none

   ============================================================*/
{
	return static_cast<int>(m_options.GetSize());
}

CProMoProperty* CProMoProperty::GetOption(const int& index)
/* ============================================================
	Function :		CProMoProperty::GetOption
	Description :	Returns the option having the specified
					index.
	Access :		Public

	Return :		CProMoProperty*	-	the option having the
										specified index
	Parameters :	int index		-	the index for the option
										to be returned

   ============================================================*/
{
	if (index < m_options.GetSize()) {
		CProMoProperty* option = dynamic_cast<CProMoProperty*>(m_options.GetAt(index));
		return option;
	}
	return NULL;
}


CString CProMoProperty::GetHeaderFromString(CString& str)
/* ============================================================
	Function :		CProMoProperty::GetHeaderFromString
	Description :	Gets the header from "str".
	Access :		Protected

	Return :		CString			-	The type of "str".
	Parameters :	CString& str	-	"CString" to get type from.

	Usage :			Call as a part of loading the object. "str"
					will have the type removed after the call.

   ============================================================*/
{
	CString header;

	CFileParser::GetHeaderFromString(str, header);

	return header;
}

BOOL CProMoProperty::GetDefaultFromString(CString& str)
/* ============================================================
	Function :		CProMoProperty::GetDefaultFromString
	Description :	Gets the default properties from "str"
	Access :		Protected

	Return :		BOOL			-	"TRUE" if the default
										properties could be loaded ok.
	Parameters :	CString& str	-	"CString" to get the
										default properties from.

	Usage :			Call as a part of loading the object from
					disk. The default object properties will
					be stripped from "str" and the object
					properties set from the data.

   ============================================================*/
{
	BOOL result = FALSE;

	CTokenizer* tok = CFileParser::Tokenize(str);

	int size = tok->GetSize();
	if (size >= 2)
	{
		CString fullProp;
		int type;
		int count = 0;

		tok->GetAt(count++, fullProp);

		CFileParser::DecodeString(fullProp);

		if (fullProp.Find(GetFullName()) == 0) {
			// the string is in the path of the current property
			CString relProp = fullProp.Mid(GetFullName().GetLength());
			
			if (relProp.IsEmpty()) {
				//this is a leaf node
				
				tok->GetAt(count++, type);
				m_type = type;

				CString stringValue;
				int intValue;
				double doubleValue;
				CVariantWrapper wrapper;

				switch (type) {
				case PROPTYPE_STRING:
					tok->GetAt(count++, stringValue);
					CFileParser::DecodeString(stringValue);
					wrapper.SetString(stringValue);
					break;
				case PROPTYPE_INT:
					tok->GetAt(count++, intValue);
					wrapper.SetInt(intValue);
					break;
				case PROPTYPE_BOOL: // BOOLs are stored as ints (0/1)
					tok->GetAt(count++, intValue);
					wrapper.SetBool(intValue);
					break;
				case PROPTYPE_DOUBLE:
					tok->GetAt(count++, doubleValue);
					wrapper.SetDouble(doubleValue);
					break;
				default:
					break;
				}
				SetValue(wrapper);

				result = TRUE;
			}
			else {
				// this is not a leaf node, check if it is a child property
				if (relProp[0] == _T('.')) {
					relProp = relProp.Mid(1); // remove leading dot
					CTokenizer childTok(relProp, '.');
					if (childTok.GetSize() > 0) {
						CString childName;
						childTok.GetAt(0, childName);
						// Just ensure the child exists (find or create)
						CProMoProperty* prop = HandleChild(childName);
						if (prop) {
							result = prop->GetDefaultFromString(str);
						}
					}
				}
			}
			
		}
		
	}

	delete tok;

	return result;

}

CProMoProperty* CProMoProperty::HandleChild(const CString& str)
/* ============================================================
	Function :		CProMoProperty::HandleChild
	Description :	Returns the child property having the
					specified name, or creates a new one if
					the property is multi-value and the name
					matches the next expected index.
	Access :		Protected

	Return :		CProMoProperty*	-	The new child property.
	Parameters :	none

	Usage :			Call when de-serializing properties.

   ============================================================*/
{
	CProMoProperty* prop = NULL;
	// Try to find an existing child first
	for (int i = 0; i < m_childProperties.GetSize(); ++i)
	{
		prop = (CProMoProperty*)m_childProperties.GetAt(i);
		if (prop && prop->m_name == str)
			return prop;
	}

	// If not found — can we create a new one?
	if (m_template)
	{
		// Only create if the next expected index matches the requested name
		int nextIndex = static_cast<int>(m_childProperties.GetSize());
		CString expectedName;
		expectedName.Format(_T("%d"), nextIndex);

		if (str == expectedName) {
			return AddChild();
		}
	}
	
	return NULL;
}


CProMoProperty* CProMoProperty::FindChildR(const CString& name, CProMoProperty* prop, const CProMoProperty* root)
/* ============================================================
	Function :		CProMoProperty::FindChildR
	Description :	Recursive helper function to find a child
					property by name.
	Access :		Protected
	Return :		CProMoProperty*		-	the child property having
											the specified name
	Parameters :	CString name		-	the name for the child
											to be returned
					CProMoProperty* prop -	the current property
					CProMoProperty* root -	the root property to
											calculate relative
											names
   ============================================================*/
{
	if (prop) {
		if (prop->GetRelativeName(root) == name) {
			return prop;
		}
		else {
			CProMoProperty* temp = NULL;
			for (int i = 0; i < prop->GetChildrenCount(); i++) {
				temp = FindChildR(name, prop->GetChild(i), root);
				if (temp) {
					return temp;
				}
			}
		}
	}
	return NULL;
}

void CProMoProperty::GetChildrenNamesR(CStringArray& array, CProMoProperty* prop, const CProMoProperty* root)
/* ============================================================
	Function :		CProMoProperty::GetChildrenNamesR
	Description :	Recursive helper function to get the names of
					all child properties.
	Access :		Protected
	Return :		void
	Parameters :	CStringArray& array			-	Array to fill
					CProMoProperty* prop		-	The current property
					const CProMoProperty* root -	The root property to
													calculate relative
													names
   ============================================================*/
{
	if (prop) {
		array.Add(prop->GetRelativeName(root));
		if (prop->GetType() == PROPTYPE_COMPOSITE || prop->IsMultiValue()) {
			for (int i = 0; i < prop->GetChildrenCount(); i++) {
				CProMoProperty* child = prop->GetChild(i);
				GetChildrenNamesR(array, child, root);
			}
		}
	}
}

CString CProMoProperty::GetRelativeName(const CProMoProperty* ancestor) const
/* ============================================================
	Function :		CProMoProperty::GetRelativeName
	Description :	Gets the name of the property relative to a
					specified ancestor property.
	Access :		Protected
	Return :		CString					-	The relative name of the
												property
	Parameters :	CProMoProperty* ancestor -	The ancestor
												property to which the
												name should be relative
	Usage :			Call to get the name of a property relative
					to an ancestor, e.g., when building a list of
					child properties.
   ============================================================*/
{
	CString result = m_name;
	const CProMoProperty* parent = m_parentProperty;

	while (parent && parent != ancestor)
	{
		result = parent->m_name + _T(".") + result;
		parent = parent->m_parentProperty;
	}

	return result;
}

CString CProMoProperty::GetElementFromString(const CString& str)
/* ============================================================
	Function :		CProMoModel::GetElementFromString
	Description :	Static factory function that
					parses a formatted string and extracts the
					name of the associated object
	Access :		Public

	Return :		CString			-	The name of the object
	Parameters :	CString& str	-	The string to be parsed

   ============================================================*/
{
	CTokenizer* tok = CFileParser::Tokenize(str);
	CString name;
	if (tok) {
		tok->GetAt(3, name);
		delete tok;
	}
	return name;
}

BOOL CProMoProperty::FromString(const CString& str)
/* ============================================================
	Function :		CProMoProperty::FromString
	Description :	Sets the values for an object from "str".
	Access :		Public

	Return :		BOOL				-	"TRUE" if "str"
											represents an
											object of this
											type.
	Parameters :	const CString& str	-	Possible text
											format
											representation.

	Usage :			Can be called to fill an existing object
					with information from a string created with
					"GetString".

   ============================================================*/
{

	BOOL result = FALSE;
	CString data(str);
	CString header = GetHeaderFromString(data);
	if (header == CString("property"))
		if (GetDefaultFromString(data))
			result = TRUE;

	return result;

}

BOOL CProMoProperty::LoadFromString(CString& data)
/* ============================================================
	Function :		CProMoProperty::LoadFromString
	Description :	Loads the object from "data".
	Access :		Public

	Return :		BOOL			-	"TRUE" if "str" is a
										well-formed object prefix.
	Parameters :	CString& data	-	String to load from

	Usage :			Call to load the first part of an object
					from string.

   ============================================================*/
{

	BOOL result = FALSE;
	CString header = GetHeaderFromString(data);
	if (header == CString("property"))
		if (GetDefaultFromString(data))
			result = TRUE;

	return result;

}

CString CProMoProperty::GetString() const
/* ============================================================
	Function :		CProMoProperty::GetString
	Description :	Creates a string representing the object.
	Access :		Public

	Return :		CString	-	The resulting string
	Parameters :	none

	Usage :			Used to save this object to a text file.

   ============================================================*/
{

	CString str = GetDefaultGetString();

	str += _T(";");

	return str;

}

CString CProMoProperty::GetDefaultGetString() const
/* ============================================================
	Function :		CProMoProperty::GetDefaultGetString
	Description :	Gets the default properties of the object
					as a string.
	Access :		Protected

	Return :		CString	-	Resulting string
	Parameters :	none

	Usage :			Call as a part of the saving of objects
					to disk.

   ============================================================*/
{
	CString str;

	CString name = GetFullName();

	CFileParser::EncodeString(name);

	
	CString value;
	CString ownerRef;

	if (m_persistent) {

		value = m_value.GetString();
		if (m_type == PROPTYPE_STRING) {
			CFileParser::EncodeString(value);
		}
	}
	if (m_owner) {
		CDiagramEntity* view = dynamic_cast<CDiagramEntity*>(m_owner);
		if (view) {
			ownerRef = view->GetName();
		}
		CProMoModel* model = dynamic_cast<CProMoModel*>(m_owner);
		if (model) {
			ownerRef = model->GetName();
		}
	}

	str.Format(_T("property:%s,%d,%s,%s"), (LPCTSTR)name, m_type, (LPCTSTR)value, (LPCTSTR)ownerRef);

	return str;
}

CProMoAppChildAuto* CProMoProperty::GetAutomationObject()
/* ============================================================
	Function :		CProMoProperty::GetAutomationObject
	Description :	Returns a pointer to the automation object
					associated with this container, creating it
					if it does not already exist.
	Access :		Public
	Return :		CProMoAutomationObject*	-	The pointer.
	Parameters :	none
   ============================================================*/
{
	if (!m_autoObject) {
		m_autoObject = new CProMoPropertyAuto();
		m_autoObject->Initialize(this);
	}
	return m_autoObject;
}

void CProMoProperty::ReleaseAutomationObject()
/* ============================================================
	Function :		CProMoProperty::ReleaseAutomationObject
	Description :	Releases the pointer to the automation object
					associated with this container.
	Access :		Public
	Return :		void
	Parameters :	none
   ============================================================*/
{
	if (m_autoObject) {
		CProMoAppChildAuto* autoObject = m_autoObject;
		m_autoObject = NULL;
		autoObject->Detach();
	}
}