#include "stdafx.h"
#include "ProMoModel.h"
#include "../DiagramEditor/Tokenizer.h"



void CProMoModel::linkView(CDiagramEntity* view)
{
	m_views.Add(view);
}

void CProMoModel::unlinkView(CDiagramEntity* view)
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

void CProMoModel::unlinkViews()
{
	m_views.RemoveAll();
}

CObArray* CProMoModel::getViews()
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

	CTokenizer main(str, _T(":"));
	CString header;
	CString data;
	if (main.GetSize() == 2)
	{

		main.GetAt(0, header);
		main.GetAt(1, data);
		header.TrimLeft();
		header.TrimRight();
		data.TrimLeft();
		data.TrimRight();

		str = data;
	}

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
	CString data(str);
	if (data[data.GetLength() - 1] == _TCHAR(';'))
		data = data.Left(data.GetLength() - 1); // Strip the ';'

	CTokenizer tok(data);
	int size = tok.GetSize();
	if (size >= 1)
	{
		CString name;
		int count = 0;

		tok.GetAt(count++, name);
		
		CDiagramEntity::CStringReplace(name, _T("\\colon"), _T(":"));
		CDiagramEntity::CStringReplace(name, _T("\\semicolon"), _T(";"));
		CDiagramEntity::CStringReplace(name, _T("\\comma"), _T(","));
		CDiagramEntity::CStringReplace(name, _T("\\newline"), _T("\r\n"));

		SetName(name);
		
		// Rebuild rest of string
		str = _T("");
		for (int t = count; t < size; t++)
		{
			tok.GetAt(t, data);

			str += data;
			if (t < size - 1)
				str += _T(",");
		}

		result = TRUE;
	}

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
	CDiagramEntity::CStringReplace(name, _T(":"), _T("\\colon"));
	CDiagramEntity::CStringReplace(name, _T(";"), _T("\\semicolon"));
	CDiagramEntity::CStringReplace(name, _T(","), _T("\\comma"));
	CDiagramEntity::CStringReplace(name, _T("\r\n"), _T("\\newline"));

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