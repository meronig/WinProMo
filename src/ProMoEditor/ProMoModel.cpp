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
			if (label->m_model) {
				label->m_model->UnlinkLabel(label);
			}
			label->m_model = this;
			m_labels.Add(label);
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
			CProMoLabel* tempView = dynamic_cast<CProMoLabel*>(m_labels.GetAt(i));
			if (tempView) {
				if (tempView == label) {
					tempView->m_model = NULL;
					m_labels.RemoveAt(i);
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
		CProMoLabel* tempView = dynamic_cast<CProMoLabel*>(m_labels.GetAt(i));
		if (tempView) {
			tempView->m_model = NULL;
		}
	}
	m_labels.RemoveAll();
}

CObArray* CProMoModel::GetViews()
/* ============================================================
	Function :		CProMoModel::GetViews
	Description :	Accessor for the internal views array
	Access :		Public

	Return :		CObArray*	-	A pointer to the views
									array
	Parameters :	none

   ============================================================*/
{
	return &m_views;
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

CObArray* CProMoModel::GetLabels()
/* ============================================================
	Function :		CProMoModel::GetLabels
	Description :	Accessor for the internal labels array
	Access :		Public

	Return :		CObArray*	-	A pointer to the labels
									array
	Parameters :	none

   ============================================================*/
{
	return &m_labels;
}

CProMoLabel* CProMoModel::GetLabel(CString property)
/* ============================================================
	Function :		CProMoModel::GetLabel
	Description :	Returns a pointer to the label displaying
					a specific property
	Access :		Public

	Return :		CProMoLabel*		-	A pointer to the 
											label
	Parameters :	CString property	-	The name of the
											property

   ============================================================*/
{
	for (int i = 0; i < m_labels.GetSize(); i++) {
		CProMoLabel* label = dynamic_cast<CProMoLabel*>(m_labels.GetAt(i));
		if (label) {
			if (label->GetProperty() == property) {
				return label;
			}
		}
	}
	return NULL;
}

CObArray* CProMoModel::RecreateLabels()
/* ============================================================
	Function :		CProMoModel::RecreateLabels
	Description :	Recreates labels for all the properties
					that need to be displayed, if some of them
					are not present.
	Access :		Public

	Return :		CObArray*	-	A pointer to the labels
									being created (if any)
	Parameters :	none

   ============================================================*/
{
	CObArray* arr = new CObArray;
	// Test, make it more modular
	if (!GetLabel("title")) {
		CProMoLabel* label = new CProMoLabel();
		label->SetProperty("title");

		LinkLabel(label);
		arr->Add(label);
	}
	return arr;
}

