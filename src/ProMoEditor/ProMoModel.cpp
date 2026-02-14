/* ==========================================================================

	Copyright © 2025 Technical University of Denmark

	CProMoModel

	Author :		Giovanni Meroni

	Purpose :		"CProMoModel" is the base class for the model of all 
					objects (views) that can be drawn and managed by 
					"CProMoEditor".

	Description :	"CProMoModel" is derived from "CObject", to allow 
					instances to be stored in "CObArrays".
					A model can have 1 or more associated views.

	Usage :			Classes should be derived from "CProMoModel". "Clone" 
					must be overridden, returning a copy of the this 
					pointer.

   ========================================================================*/
#include "stdafx.h"
#include "ProMoModel.h"
#include "../DiagramEditor/Tokenizer.h"
#include "ProMoNameFactory.h"
#include "../FileUtils/FileParser.h"
#include "ProMoLabel.h"
#include "ProMoProperty.h"
#include "../Automation/ProMoElementAuto.h"
#include "../DiagramEditor/DiagramEntityContainer.h"

CProMoModel::CProMoModel()
/* ============================================================
	Function :		CProMoModel::CProMoModel
	Description :	Constructor
	Access :		Public

	Return :		void
	Parameters :	none

	Usage :

	============================================================*/
{
	SetType(_T("promo_model"));
	SetName(CProMoNameFactory::GetID());
	CreateProperties();

	m_autoObject = NULL;

}

CProMoModel::~CProMoModel()
/* ============================================================
	Function :		CProMoModel::~CProMoModel
	Description :	Destructor
	Access :		Public

	Return :		void
	Parameters :	none

	Usage :

   ============================================================*/
{
	UnlinkAllLabels();
	ClearProperties();

	ReleaseAutomationObject();
}

CProMoModel* CProMoModel::Clone()
/* ============================================================
	Function :		CProMoModel::Clone
	Description :	Clone this object to a new object.
	Access :		Public

	Return :		CProMoModel*	-	The new object.
	Parameters :	none

	Usage :			Call to create a clone of the object. The
					caller will have to delete the object.

   ============================================================*/
{
	CProMoModel* obj = new CProMoModel;
	return obj;
}

void CProMoModel::Copy(CProMoModel* obj)
/* ============================================================
	Function :		CProMoModel::Copy
	Description :	Copy the information in "obj" to this object.
	Access :		Public

	Return :		void
	Parameters :	CProMoModel* obj	-	The object to copy
												from.

	Usage :			Copies basic information. from "obj" to this.
					"GetType" can be used to check for the correct
					object type in overridden versions.
   ============================================================*/
{
	for (int i = 0; i < m_properties.GetSize(); i++) {
		CProMoProperty* prop = dynamic_cast<CProMoProperty*>(m_properties.GetAt(i));
		if (prop) {
			if (prop->IsPersistent()) {
				CVariantWrapper value = obj->GetPropertyValue(prop->GetFullName());
				prop->SetValue(value);
			}
		}
	}
}

void CProMoModel::LinkView(CDiagramEntity* view)
/* ============================================================
	Function :		CProMoModel::LinkView
	Description :	Links a new view to this object.
	Access :		Protected

	Return :		void
	Parameters :	CDiagramEntity* view - the view to link

   ============================================================*/
{
	m_views.Add(view);
}

void CProMoModel::UnlinkView(CDiagramEntity* view)
/* ============================================================
	Function :		CProMoModel::UnlinkView
	Description :	Unlinks a view from this object.
	Access :		Protected

	Return :		void
	Parameters :	CDiagramEntity* view - the view to unlink

   ============================================================*/
{
	for (int i = static_cast<int>(m_views.GetSize()) - 1; i >= 0 ; i--) {
		CDiagramEntity* tempView = dynamic_cast<CDiagramEntity*>(m_views.GetAt(i));
		if (tempView) {
			if (tempView == view) {
				m_views.RemoveAt(i);
			}
		}
	}
}

void CProMoModel::UnlinkAllViews()
/* ============================================================
	Function :		CProMoModel::UnlinkAllViews
	Description :	Unlinks all views from this object.
	Access :		Protected

	Return :		void
	Parameters :	none

   ============================================================*/
{
	m_views.RemoveAll();
}

void CProMoModel::LinkLabel(CProMoLabel* label)
/* ============================================================
	Function :		CProMoModel::LinkView
	Description :	Links a new label to this object.
	Access :		Protected

	Return :		void
	Parameters :	CProMoLabel* label - the label to link

   ============================================================*/
{
	if (label) {
		if (label->m_model != this) {

			CProMoProperty* prop = FindProperty(label->m_property);
			
			if (prop) {
				if (prop->IsLabelVisible()) {
					// unlink existing label for this property (if any)
					UnlinkLabel(GetLabel(label->m_property));

					// unlink from previous model (if any)
					if (label->m_model) {
						label->m_model->UnlinkLabel(label);
					}

					// link the label
					label->m_model = this;
					m_labels.Add(label);
					CString value = prop->GetValue().GetString();
					label->SetFitTitle(TRUE);
					label->SetTitle(value);
					CustomizeLabel(label);
				}
			}

		}
	}
}

void CProMoModel::UnlinkLabel(CProMoLabel* label)
/* ============================================================
	Function :		CProMoModel::UnlinkLabel
	Description :	Unlinks a label from this object.
	Access :		Protected

	Return :		void
	Parameters :	CProMoLabel* label - the label to unlink

   ============================================================*/
{
	if (label) {
		for (int i = static_cast<int>(m_labels.GetSize()) - 1; i >= 0; i--) {
			CProMoLabel* tempLabel = dynamic_cast<CProMoLabel*>(m_labels.GetAt(i));
			if (tempLabel) {
				if (tempLabel == label) {
					tempLabel->m_model = NULL;
					m_labels.RemoveAt(i);
					CustomizeLabel(label);
				}
			}
		}
	}
}

void CProMoModel::UnlinkAllLabels()
/* ============================================================
	Function :		CProMoModel::UnlinkAllLabels
	Description :	Unlinks all labels from this object.
	Access :		Protected

	Return :		void
	Parameters :	none

   ============================================================*/
{
	for (int i = static_cast<int>(m_labels.GetSize()) - 1; i >= 0; i--) {
		CProMoLabel* label = dynamic_cast<CProMoLabel*>(m_labels.GetAt(i));
		if (label) {
			label->m_model = NULL;
			CustomizeLabel(label);
		}
	}
	m_labels.RemoveAll();
}

void CProMoModel::CustomizeLabels()
/* ============================================================
	Function :		CProMoModel::CustomizeLabels
	Description :	Customizes all the labels linked to the
					model
	Access :		Public

	Return :		void
	Parameters :	none

   ============================================================*/
{
	for (int i = 0; i < m_labels.GetSize(); i++)
	{
		CustomizeLabel((CProMoLabel*)(m_labels.GetAt(i)));
	}
}

void CProMoModel::ClearProperties() 
/* ============================================================
	Function :		CProMoModel::ClearProperties
	Description :	Destroys the properties for this object.
	Access :		Protected

	Return :		void
	Parameters :	none

   ============================================================*/
{
	for (int i = static_cast<int>(m_properties.GetSize()) - 1; i >= 0; i--) {
		CProMoProperty* prop = dynamic_cast<CProMoProperty*>(m_properties.GetAt(i));
		if (prop) {
			delete prop;
		}
	}
	m_properties.RemoveAll();
}

CProMoProperty* CProMoModel::FindPropertyR(const CString& name, CProMoProperty* prop) const
/* ============================================================
	Function :		CProMoModel::FindPropertyR
	Description :	Gets the property with the specified
					name.

	Return :		CProMoProperty&			-	The property, or
												"NULL" if no
												such property
												exists.
	Parameters :	CString& name			-	The full name of
												the property
												(e.g., parent.0.child).
					CProMoProperty* prop	-	The root node
												to start the
												search from.

   ============================================================*/
{
	if (prop) {
		if (prop->GetFullName() == name) {
			return prop;
		}
		else {
			CProMoProperty* temp = NULL;
			for (int i = 0; i < prop->GetChildrenCount(); i++) {
				temp = FindPropertyR(name, prop->GetChild(i));
				if (temp) {
					return temp;
				}
			}
		}
	}
	return NULL;
}

void CProMoModel::RecreateLabelsR(CObArray& list, CProMoProperty* prop)
/* ============================================================
	Function :		CProMoModel::RecreateLabelsR
	Description :	Recreates labels for all the properties
					that need to be displayed, if some of them
					are not present.
	Access :		Protected

	Return :		void
	Parameters :	CObArray* list			-	A pointer to
												the labels
												being created
												(if any)
					CProMoProperty* prop	-	Property to
												start from.
					

   ============================================================*/
{
	if (prop) {
		if (!GetLabel(prop->GetFullName()) && prop->IsLabelVisible()) {
			CProMoLabel* label = new CProMoLabel();
			label->SetProperty(prop->GetFullName());
			LinkLabel(label);
			CObArray viewList;
			GetViews(viewList);
			if (viewList.GetSize() > 0) {
				CDiagramEntity* view = dynamic_cast<CDiagramEntity*>(viewList.GetAt(0));
				if (view) {
					if (view->GetParent()) {
						view->GetParent()->Add(label);
					}
				}
			}
			list.Add(label);
		}
		if (prop->GetType() == PROPTYPE_COMPOSITE || prop->IsMultiValue()) {
			for (int i = 0; i < prop->GetChildrenCount(); i++) {
				CProMoProperty* child = prop->GetChild(i);
				RecreateLabelsR(list, child);
			}
		} 
	}
}

void CProMoModel::GetPropertyNamesR(CStringArray& array, CProMoProperty* prop) const
/* ============================================================
	Function :		CProMoModel::GetPropertyNamesR
	Description :	Gets the names of all child properties for the
					current property.
	Access :		Public

	Return :		void
	Parameters :	CStringArray& array	-	The names of all
											properties.
					CProMoProperty* prop-	The parent property

   ============================================================*/
{
	if (prop) {
		array.Add(prop->GetFullName());
		if (prop->GetType() == PROPTYPE_COMPOSITE || prop->IsMultiValue()) {
			for (int i = 0; i < prop->GetChildrenCount(); i++) {
				CProMoProperty* child = prop->GetChild(i);
				GetPropertyNamesR(array, child);
			}
		}
	}
}

void CProMoModel::OnPropertyChanged(CProMoProperty* prop)
/* ============================================================
	Function :		CProMoModel::OnPropertyChanged
	Description :	Notification that a property has changed.
	Access :		Public

	Return :		void
	Parameters :	CProMoProperty* prop	-	Property that
												changed.

	Usage :			Can be called by a property to notify the
					model that it changed, and to trigger UI
					updates.

   ============================================================*/
{
	CProMoLabel* label = GetLabel(prop->GetFullName());
	if (label) {
		label->SetTitle(prop->GetValue().GetString());
	}

}

void CProMoModel::CreateProperties()
/* ============================================================
	Function :		CProMoModel::CreateProperties
	Description :	Creates the properties for this object.
	Access :		Protected

	Return :		void
	Parameters :	none

   ============================================================*/
{
	ClearProperties();
	CVariantWrapper wrapper;
	wrapper.SetString(_T("Title"));
	AddProperty(new CProMoProperty(_T("Title"), PROPTYPE_STRING, wrapper, FALSE, TRUE, TRUE, this));
}

void CProMoModel::AddProperty(CProMoProperty* prop)
/* ============================================================
	Function :		CProMoModel::AddProperty
	Description :	Adds a property to this object.
	Access :		Protected

	Return :		void
	Parameters :	CProMoProperty* prop - the property to add
   ============================================================*/
{
	if (prop) {
		m_properties.Add(prop);
	}
}

void CProMoModel::GetViews(CObArray& viewList) const
/* ============================================================
	Function :		CProMoModel::GetViews
	Description :	Returns all the views associated to the model
	Access :		Public

	Return :		void
	Parameters :	CObArray	-	A CObArray that will contain
									the views

   ============================================================*/
{
	viewList.Append(m_views);
}

BOOL CProMoModel::FromString(const CString& str)
/* ============================================================
	Function :		CProMoModel::FromString
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
	if (header == GetType())
		if (GetDefaultFromString(data))
			result = TRUE;

	return result;

}

CString CProMoModel::GetHeaderFromString(CString& str)
/* ============================================================
	Function :		CProMoModel::GetHeaderFromString
	Description :	Gets the header from "str".
	Access :		Protected

	Return :		CString			-	The type of "str".
	Parameters :	CString& str	-	"CString" to get type from.

	Usage :			Call as a part of loading the object. "str"
					will have the type removed after the call.

   ============================================================*/
{
	CString header;

	CFileParser::GetHeaderFromString(str,header);
	
	return header;
}

BOOL CProMoModel::GetDefaultFromString(CString& str)
/* ============================================================
	Function :		CProMoModel::GetDefaultFromString
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
	if (size >= 1)
	{
		CString name;
		int count = 0;

		tok->GetAt(count++, name);

		CFileParser::DecodeString(name);

		SetName(name);

		result = TRUE;

	}

	delete tok;

	return result;

}

BOOL CProMoModel::LoadFromString(CString& data)
/* ============================================================
	Function :		CProMoModel::LoadFromString
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
	if (header == GetType())
		if (GetDefaultFromString(data))
			result = TRUE;

	return result;

}

CProMoModel* CProMoModel::CreateFromString(const CString& str)
/* ============================================================
	Function :		CProMoModel::CreateFromString
	Description :	Static factory function that creates and
					returns an instance of this class if "str"
					is a valid representation.
	Access :		Public

	Return :		CProMoModel*		-	The object, or "NULL"
											if "str" is not a
											representation of
											this type.
	Parameters :	const CString& str	-	The string to create
											from.

	Usage :			Can be used as a factory for text file loads.
					Each object type should have its own
					version - the default one is a model
					implementation.

   ============================================================*/
{

	CProMoModel* obj = new CProMoModel;
	if (!obj->FromString(str))
	{
		delete obj;
		obj = NULL;
	}

	return obj;

}

CString CProMoModel::GetString() const
/* ============================================================
	Function :		CProMoModel::GetString
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

CString CProMoModel::GetDefaultGetString() const
/* ============================================================
	Function :		CProMoModel::GetDefaultString
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

	CString name = GetName();

	CFileParser::EncodeString(name);

	str.Format(_T("%s:%s"), (LPCTSTR)GetType(), (LPCTSTR)name);

	return str;
}

CString CProMoModel::GetType() const
/* ============================================================
	Function :		CProMoModel::GetType
	Description :	Returns the object type.
	Access :		Public

	Return :		CString	-	The type of the object.
	Parameters :	none

	Usage :			Call to get the type of the object. The type
					is used when saving and loading objects
					to/from a text file.

   ============================================================*/
{
	return m_type;
}

void CProMoModel::SetType(CString type)
/* ============================================================
	Function :		CProMoModel::SetType
	Description :	Set the object type.
	Access :		Public

	Return :		void
	Parameters :	CString type	-	The type to set

	Usage :			Call to set the object type - normally in
					the "ctor" of this object. The type is used
					when saving and loading objects to/from a
					text file.

   ============================================================*/
{
	m_type = type;
}

CString CProMoModel::GetName() const
/* ============================================================
	Function :		CProMoModel::GetName
	Description :	Gets the Name property
	Access :		Public

	Return :		CString	-	The current name
	Parameters :	none

	Usage :			Call to get the name of the object. Name is
					a property that the object can use in
					whatever way it wants.


   ============================================================*/
{

	return m_name;

}

void CProMoModel::SetName(CString name)
/* ============================================================
	Function :		CProMoModel::SetName
	Description :	Sets the Name property
	Access :		Public

	Return :		void
	Parameters :	CString name	-	The new name

	Usage :			Call to set the name of the object. Name is
					a property that the object can use in
					whatever way it wants.

   ============================================================*/
{

	m_name = name;

}

void CProMoModel::GetPropertyNames(CStringArray& array, const BOOL& recursive) const
/* ============================================================
	Function :		CProMoModel::GetPropertyNames
	Description :	Gets the names of all properties for the
					current object.
	Access :		Public

	Return :		void
	Parameters :	CStringArray& array	-	The names of all
											properties.
					BOOL& recursive		-	"TRUE" if the full
											name of child
											properties should
											also be returned.

   ============================================================*/
{
	for (int i = 0; i < m_properties.GetSize(); i++) {
		CProMoProperty* prop = dynamic_cast<CProMoProperty*>(m_properties.GetAt(i));
		if (recursive) {
			GetPropertyNamesR(array, prop);
		}
		else {
			if (prop) {
				array.Add(prop->GetFullName());
			}
		}
	}
}

unsigned int CProMoModel::GetPropertyType(const CString& name) const
/* ============================================================
	Function :		CProMoModel::GetPropertyType
	Description :	Gets the data type of the specified property
	Access :		Public

	Return :		unsigned int		-	The data type of 
											the property,
											or "TYPE_UNKNOWN"
											if the property
											does not exist.
	Parameters :	CString& name		-	The name of the
											property.

   ============================================================*/
{
	CProMoProperty* prop = FindProperty(name);
	if (prop) {
		return prop->GetType();
	}
	return PROPTYPE_UNKNOWN;
}

const CVariantWrapper& CProMoModel::GetPropertyValue(const CString& name) const
/* ============================================================
	Function :		CProMoModel::GetPropertyValue
	Description :	Gets the value of the specified property
	Access :		Public

	Return :		CVariantWrapper&		-	The value of the
											property, or an
											empty variant if
											the property
											does not exist.
	Parameters :	CString& name		-	The name of the
											property to set.
	
   ============================================================*/
{
	static const CVariantWrapper empty;
	CProMoProperty* prop = FindProperty(name);
	if (prop) {
		return prop->GetValue();
	}
	return empty;
}

BOOL CProMoModel::SetPropertyValue(const CString& name, const CVariantWrapper& value)
/* ============================================================
	Function :		CProMoModel::SetPropertyValue
	Description :	Sets the value of the specified property
	Access :		Public

	Return :		BOOL				-	"TRUE" if the 
											operation succeded.
	Parameters :	CString& name		-	The name of the
											property to set.
					CVariantWrapper& value	-	The new value.

   ============================================================*/
{
	CProMoProperty* prop = FindProperty(name);
	if (prop) {
		BOOL result = prop->SetValue(value);
		// update linked label (if any)
		if (result) {
			OnPropertyChanged(prop);
		}
		return result;
	}
	
	return FALSE;
}

unsigned int CProMoModel::GetPropertiesCount() const
/* ============================================================
	Function :		CProMoModel::GetPropertiesCount
	Description :	Returns the number of properties
	Access :		Public

	Return :		unsigned int		-	The number of
											properties.
	Parameters :	none

   ============================================================*/
{
	return static_cast<int>(m_properties.GetSize());
}

CProMoProperty* CProMoModel::GetProperty(const int& index) const
/* ============================================================
	Function :		CProMoModel::GetProperty
	Description :	Gets the property at position "index"
	Access :		Public

	Return :		CProMoProperty&		-	The property, or
											"NULL" if "index"
											is out of range.
	Parameters :	int& index			-	The position of
											the property.

   ============================================================*/
{
	if (index < m_properties.GetSize()) {
		CProMoProperty* prop = dynamic_cast<CProMoProperty*>(m_properties.GetAt(index));
		if (prop) {
			return prop;
		}
	}
	return NULL;
}

CProMoProperty* CProMoModel::FindProperty(const CString& name) const
/* ============================================================
	Function :		CProMoModel::FindProperty
	Description :	Gets the property with the specified
					name.

	Return :		CProMoProperty&		-	The property, or
											"NULL" if no
											such property
											exists.
	Parameters :	CString& name		-	The full name of 
											the property
											(e.g., parent.0.child).

   ============================================================*/
{
	CProMoProperty* result = NULL;
	for (int i = 0; i < m_properties.GetSize(); i++) {
		CProMoProperty* prop = dynamic_cast<CProMoProperty*>(m_properties.GetAt(i));
		if (prop) {
			result = FindPropertyR(name, prop);
			if (result) {
				return result;
			}
		}
	}
	return NULL;
}

CString CProMoModel::Export(UINT /*format*/) const
/* ============================================================
	Function :		CProMoModel::Export
	Description :	Exports the object to format
	Access :		Public

	Return :		CString		-	The object representation
									in format.
	Parameters :	UINT format	-	The format to export to.

	Usage :			Virtual function to allow easy exporting of
					the objects to different text based formats.

   ============================================================*/
{

	return _T("");

}

CString CProMoModel::GetNameFromString(const CString& str)
/* ============================================================
	Function :		CProMoModel::GetNameFromString
	Description :	Static factory function that
					parses a formatted string and extracts the
					name of the object
	Access :		Public

	Return :		CString			-	The name of the object
	Parameters :	CString& str	-	The string to be parsed

   ============================================================*/
{
	CTokenizer* tok = CFileParser::Tokenize(str);
	CString name;
	if (tok) {
		tok->GetAt(0, name);
		delete tok;
	}
	return name;
}

void CProMoModel::GetLabels(CObArray& labelList) const
/* ============================================================
	Function :		CProMoModel::GetLabels
	Description :	Returns the labels associated to the model
	Access :		Public

	Return :		void
	Parameters :	CObArray	-	A CObArray that will contain
									the labels

   ============================================================*/
{
	labelList.Append(m_labels);
}

CProMoLabel* CProMoModel::GetLabel(CString property) const
/* ============================================================
	Function :		CProMoModel::GetLabel
	Description :	Returns a pointer to the label displaying
					a specific property
	Access :		Public

	Return :		CProMoLabel*		-	A pointer to the 
											label
	Parameters :	CString property	-	The full name of the
											property

   ============================================================*/
{
	for (int i = 0; i < m_labels.GetSize(); i++) {
		CProMoLabel* label = dynamic_cast<CProMoLabel*>(m_labels.GetAt(i));
		if (label) {
			if (label->GetPropertyName() == property) {
				return label;
			}
		}
	}
	return NULL;
}

void CProMoModel::RecreateLabels(CObArray& labelList)
/* ============================================================
	Function :		CProMoModel::RecreateLabels
	Description :	Recreates labels for all the properties
					that need to be displayed, if some of them
					are not present.
	Access :		Public

	Return :		void
	Parameters :	CObArray	-	A CObArray that will contain
									the labels being created
									(if any)

   ============================================================*/
{
	for (int i = 0; i < m_properties.GetSize(); i++) {
		CProMoProperty* prop = dynamic_cast<CProMoProperty*>(m_properties.GetAt(i));
		RecreateLabelsR(labelList, prop);
	}
}

void CProMoModel::CustomizeLabel(CProMoLabel* label)
/* ============================================================
	Function :		CProMoModel::CustomizeLabel
	Description :	Customizes the input label.
	Access :		Public

	Return :		void
	Parameters :	CProMoLabel*			-	A pointer to the 
												label to customize

   ============================================================*/
{
	if (label) {

		if (!label->GetModel()) {
			//unlock all options
			label->SetLock(0);
		}

		label->Reposition();
	}
}

CProMoAppChildAuto* CProMoModel::GetAutomationObject()
/* ============================================================
	Function :		CProMoModel::GetAutomationObject
	Description :	Returns a pointer to the automation object
					associated with this container, creating it
					if it does not already exist.
	Access :		Public
	Return :		CProMoAutomationObject*	-	The pointer.
	Parameters :	none
   ============================================================*/
{
	if (!m_autoObject) {
		m_autoObject = new CProMoElementAuto();
		m_autoObject->Initialize(this);
	}
	return m_autoObject;
}

void CProMoModel::ReleaseAutomationObject()
/* ============================================================
	Function :		CProMoModel::ReleaseAutomationObject
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