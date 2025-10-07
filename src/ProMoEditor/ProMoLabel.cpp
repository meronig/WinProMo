#include "stdafx.h"
#include "ProMoLabel.h"
#include "ProMoNameFactory.h"
#include "../DiagramEditor/Tokenizer.h"
#include "../FileUtils/FileParser.h"
#include "../resource.h"

CProMoLabel::CProMoLabel()
/* ============================================================
	Function :		CProMoLabel::CProMoLabel
	Description :	constructor

	Return :		void
	Parameters :	none

	Usage :

   ============================================================*/
{
	SetConstraints(CSize(128, 32), CSize(-1, -1));
	SetType(_T("promo_label"));

	SetZoom(1.0);

	CString title;
	BOOL result;
	result = title.LoadString(IDS_PROMO_BLOCK);
	if (result) {
		SetTitle(title);
	}
	
	SetName(CProMoNameFactory::GetID());

	m_entity = NULL;
	m_selectable = TRUE;
}

CProMoLabel::~CProMoLabel()
/* ============================================================
	Function :		CProMoLabel::~CProMoLabel
	Description :	destructor

	Return :		void
	Parameters :	none

	Usage :

   ============================================================*/
{

}

CDiagramEntity* CProMoLabel::Clone()
/* ============================================================
	Function :		CProMoLabel::Clone
	Description :	Clone this object to a new object.

	Return :		CDiagramEntity*	-	The new object.
	Parameters :	none

	Usage :			Call to create a clone of the object. The
					caller will have to delete the object.

   ============================================================*/
{

	//Hierarchy is not copied: if multiple blocks are selected, they become root nodes
	CProMoLabel* obj = new CProMoLabel;
	obj->Copy(this);
	obj->SetName(CProMoNameFactory::GetID());
	return obj;

}

void CProMoLabel::Copy(CDiagramEntity* obj)
/* ============================================================
	Function :		CProMoLabel::Copy
	Description :	Copy the information in "obj" to this object.
	Access :		Public

	Return :		void
	Parameters :	CDiagramEntity* obj	-	The object to copy
												from.

	Usage :			Copies basic information. from "obj" to this.
					"GetType" can be used to check for the correct
					object type in overridden versions.
   ============================================================*/
{
	CDiagramEntity::Copy(obj);
	CProMoLabel* objView = dynamic_cast<CProMoLabel*>(obj);
	//TODO revise
	//SetLockedProportions(objView->HasLockedProportions());
	//SetFitTitle(objView->HasFitTitle());
}

void CProMoLabel::Draw(CDC* dc, CRect rect)
/* ============================================================
	Function :		CProMoLabel::Draw
	Description :	Draws the object.

	Return :		void
	Parameters :	CDC* dc		-	The CDC to draw to.
					CRect rect	-	The real rectangle of the
									object.

	Usage :			The function should clean up all selected
					objects. Note that the CDC is a memory CDC,
					so creating a memory CDC in this function
					will probably not speed up the function.

   ============================================================*/
{
	CFont font;
	CString str;
	/* uncomment line below for debug */
	//str.Format(_T("%d,%d"), getModel()->getIncomingEdges()->GetSize(), getModel()->getOutgoingEdges()->GetSize());
	str = GetTitle();
	font.CreateFont(-round(12.0 * GetZoom()), 0, 0, 0, FW_NORMAL, 0, 0, 0, 0, 0, 0, 0, 0, _T("Courier New"));
	dc->SelectObject(&font);
	int mode = dc->SetBkMode(TRANSPARENT);

	dc->DrawText(str, rect, DT_NOPREFIX | DT_SINGLELINE | DT_VCENTER | DT_CENTER);
	
	dc->SelectStockObject(DEFAULT_GUI_FONT);
	dc->SetBkMode(mode);
}

void CProMoLabel::ShowPopup(CPoint point, CWnd* parent)
/* ============================================================
	Function :		CProMoLabel::ShowPopup
	Description :	Shows the popup menu for the object.
	Access :		Public

	Return :		void
	Parameters :	CPoint point	-	The point to track.
					CWnd* parent	-	The parent "CWnd" of the
										menu (should be the
										"CDiagramEditor")

   ============================================================*/
{

	CMenu menu;
	if (menu.CreatePopupMenu())
	{

		menu.AppendMenu(MF_STRING, ID_EDIT_CUT, _T("Cut"));
		menu.AppendMenu(MF_STRING, ID_EDIT_COPY, _T("Copy"));
		menu.TrackPopupMenu(TPM_LEFTALIGN | TPM_RIGHTBUTTON, point.x, point.y, parent);

	}

}

CDiagramEntity* CProMoLabel::GetEntity() const
/* ============================================================
	Function :		CProMoLabel::GetEntity()
	Description :	Returns a pointer to the entity associated
					to this label
	Access :		Public

	Return :		CDiagramEntity*	-	A pointer to the
										entity
	Parameters :	none

   ============================================================*/
{
	return m_entity;
}

CString CProMoLabel::GetProperty() const
/* ============================================================
	Function :		CProMoLabel::GetProperty()
	Description :	Returns the name of the property being
					displayed
	Access :		Public

	Return :		CString	-	The name of the property being
								displayed
	Parameters :	none

   ============================================================*/
{
	return m_property;
}

BOOL CProMoLabel::IsSelectable() const
/* ============================================================
	Function :		CProMoLabel::IsSelectable
	Description :	Returns if the label can be selected by the
					end user
	Access :		Public

	Return :		BOOL	-	"TRUE" if the label can be 
								selected
	Parameters :	none

   ============================================================*/
{
	return m_selectable;
}

void CProMoLabel::SetEntity(CDiagramEntity* model)
/* ============================================================
	Function :		CProMoLabel::SetEntity
	Description :	Makes the object being passed as input
					parameter the entity for this label
	Access :		Protected

	Return :		void
	Parameters :	CDiagramEntity* entity	-	the object that
												should be the
												entity

   ============================================================*/
{
	//TODO revise
	/*
	if (m_blockmodel != model) {
		CProMoBlockModel* oldModel = m_blockmodel;
		m_blockmodel = model;

		//link this class to the new model
		if (model) {
			model->LinkView(this);
		}
		//unlink this class from the old model
		if (oldModel) {
			oldModel->UnlinkView(this);
			//if the old model has no views, delete it
			if (oldModel->GetViews()->GetSize() == 0) {
				delete oldModel;
			}
		}
	}
	*/
}

void CProMoLabel::SetProperty(const CString& property)
/* ============================================================
	Function :		CProMoLabel::SetProperty
	Description :	Sets the property displayed by the label
	Access :		Public

	Return :		void
	Parameters :	CString title	-	The name of the 
										property

   ============================================================*/
{
	m_property = property;
}

void CProMoLabel::Selectable(const BOOL& select)
/* ============================================================
	Function :		CProMoLabel::Selectable
	Description :	Sets whether the label can be selected by
					the end user
	Access :		Public

	Return :		void
	Parameters :	const BOOL& select	-	"TRUE" if the label
											can be selected

   ============================================================*/
{
	m_selectable = select;
}

CDiagramEntity* CProMoLabel::CreateFromString(const CString& str, CDiagramEntity* entity)
/* ============================================================
	Function :		CProMoLabel::CreateFromString
	Description :	Static factory function that creates and
					returns an instance of this class if str
					is a valid representation.

	Return :		CDiagramEntity*			-	The object, or
												NULL if str is
												not a
												representation 
												of this type.
	Parameters :	const CString& str		-	The string to 
												create from.
					CDiagramEntity* entity	-	A block or edge
												view to be
												associated to 
												the object 
												being created.
					

	Usage :			Can be used as a factory for text file loads.
					Each object type should have its own
					version - the default one is a model
					implementation.

   ============================================================*/
{

	CProMoLabel* obj = new CProMoLabel;
	if (!obj->FromString(str))
	{
		delete obj;
		obj = NULL;
	}
	else {
		if (entity) {
			obj->SetEntity(entity);
		}
	}

	return obj;

}

CString CProMoLabel::GetEntityFromString(const CString& str)
/* ============================================================
	Function :		CProMoLabel::GetEntityFromString
	Description :	Static factory function that
					parses a formatted string and extracts the
					name of the associated entity object
	Access :		Public

	Return :		CString			-	The name of the model
	Parameters :	CString& str	-	The string to be parsed

   ============================================================*/
{
	CTokenizer* tok = CFileParser::Tokenize(str);
	CString entityName;
	if (tok) {
		//TODO revise
		tok->GetAt(7, entityName);
		delete tok;
	}
	return entityName;
}

CString CProMoLabel::GetNameFromString(const CString& str)
/* ============================================================
	Function :		CProMoLabel::GetNameFromString
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

CDiagramEntity* CProMoLabel::CreateFromString(const CString& str)
/* ============================================================
	Function :		CProMoLabel::CreateFromString
	Description :	Static factory function that creates and
					returns an instance of this class if str
					is a valid representation.

	Return :		CDiagramEntity*		-	The object, or NULL
											if str is not a
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

	CProMoLabel* obj = new CProMoLabel;
	if (!obj->FromString(str))
	{
		delete obj;
		obj = NULL;
	}

	return obj;

}

CString CProMoLabel::GetDefaultGetString() const
{
	/* ============================================================
	Function :		CProMoLabel::GetDefaultString
	Description :	Gets the default properties of the object
					as a string.
	Access :		Protected

	Return :		CString	-	Resulting string
	Parameters :	none

	Usage :			Call as a part of the saving of objects
					to disk.

   ============================================================*/
	
	CString str;

	CString entity;
	CString title;
	CString property;
	if (m_entity) {
		entity = GetEntity()->GetName();
		CFileParser::EncodeString(entity);
		property = GetProperty();
		CFileParser::EncodeString(property);
	}
	else {
		title = GetTitle();
		CFileParser::EncodeString(title);
	}
		
	CString name = GetName();
	CFileParser::EncodeString(name);

	str.Format(_T("%s:%s,%f,%f,%f,%f,%s,%i,%s,%s"), (LPCTSTR)GetType(), (LPCTSTR)name, GetLeft(), GetTop(), GetRight(), GetBottom(), (LPCTSTR)title, GetGroup(), (LPCTSTR)entity, (LPCTSTR)property);

	return str;

}

CString CProMoLabel::GetHeaderFromString(CString& str)
/* ============================================================
	Function :		CProMoLabel::GetHeaderFromString
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

BOOL CProMoLabel::GetDefaultFromString(CString& str)
/* ============================================================
	Function :		CProMoLabel::GetDefaultFromString
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
	if (tok) {

		int size = tok->GetSize();
		if (size >= 8)
		{
			CString name;
			double left;
			double top;
			double right;
			double bottom;
			CString title;
			int group;
			int count = 0;

			tok->GetAt(count++, name);
			tok->GetAt(count++, left);
			tok->GetAt(count++, top);
			tok->GetAt(count++, right);
			tok->GetAt(count++, bottom);
			tok->GetAt(count++, title);
			tok->GetAt(count++, group);

			SetRect(left, top, right, bottom);

			CFileParser::DecodeString(title);
			CFileParser::DecodeString(name);

			SetTitle(title);
			SetName(name);
			SetGroup(group);

			result = TRUE;
		}
		delete tok;
	}

	return result;

}