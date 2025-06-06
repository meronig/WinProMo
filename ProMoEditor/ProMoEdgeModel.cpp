#include "stdafx.h"
#include "ProMoEdgeModel.h"
#include "ProMoBlockModel.h"
#include "ProMoNameFactory.h"


CProMoEdgeModel::CProMoEdgeModel()
/* ============================================================
	Function :		CProMoEdgeModel::CProMoEdgeModel
	Description :	Constructor
	Access :		Public

	Return :		void
	Parameters :	none

	Usage :

   ============================================================*/
{
	SetType(_T("promo_edge_model"));
	SetName(CProMoNameFactory::GetID());

	m_source = NULL;
	m_dest = NULL;
}

CProMoEdgeModel::~CProMoEdgeModel()
/* ============================================================
	Function :		CProMoEdgeModel::~CProMoEdgeModel
	Description :	Destructor
	Access :		Public

	Return :		void
	Parameters :	none

	Usage :

   ============================================================*/
{
	CProMoEdgeModel* edge = dynamic_cast<CProMoEdgeModel*>(m_source);
	if (edge) {
		edge->SetDestination(GetDestination());
	}


	edge = dynamic_cast<CProMoEdgeModel*>(m_dest);
	if (edge) {
		edge->SetSource(GetSource());
	}


	SetSource(NULL);
	SetDestination(NULL);

	
}

CProMoModel* CProMoEdgeModel::Clone()
/* ============================================================
	Function :		CProMoEdgeModel::Clone
	Description :	Clone this object to a new object.

	Return :		CProMoModel*	-	The new object.
	Parameters :	none

	Usage :			Call to create a clone of the object. The
					caller will have to delete the object.

   ============================================================*/

{

	CProMoEdgeModel* obj = new CProMoEdgeModel;
	obj->m_source = NULL;
	obj->m_dest = NULL;
	return obj;
}


void CProMoEdgeModel::SetSource(CProMoModel* source)
{

	if (m_source != source) {

		//set the new source	
		CProMoModel* oldSource = m_source;
		m_source = source;

		if (oldSource) {
			//if a previous source block exists, remove the reference from the old source block
			CProMoBlockModel* obj = dynamic_cast<CProMoBlockModel*>(oldSource);
			if (obj) {
				for (int i = 0; i < obj->m_outgoingEdges.GetSize(); i++) {
					if (obj->m_outgoingEdges.GetAt(i) == this) {
						obj->m_outgoingEdges.RemoveAt(i);
					}
				}
			}
			//if a previous source edge exists, remove the reference from the old source edge
			CProMoEdgeModel* edge = dynamic_cast<CProMoEdgeModel*>(oldSource);
			if (edge) {
				//edge->SetDestination(NULL);
				edge->m_dest = NULL;
			}
		}

		if (source) {
			//if the new source block exists, add a reference to the new source block
			CProMoBlockModel* obj = dynamic_cast<CProMoBlockModel*>(source);
			if (obj) {
				obj->m_outgoingEdges.Add(this);
			}
			//if the new source edge exists, add a reference to the new source edge
			CProMoEdgeModel* edge = dynamic_cast<CProMoEdgeModel*>(m_source);
			if (edge) {
				edge->SetDestination(this);
				//edge->m_dest = this;
			}
		}
	}
}

void CProMoEdgeModel::SetDestination(CProMoModel* destination)
{
	if (m_dest != destination) {

		//set the new destination	
		CProMoModel* oldDest = m_dest;
		m_dest = destination;

		if (oldDest) {
			//if a previous destination block exists, remove the reference from the old destination block
			CProMoBlockModel* obj = dynamic_cast<CProMoBlockModel*>(oldDest);
			if (obj) {
				for (int i = 0; i < obj->m_incomingEdges.GetSize(); i++) {
					if (obj->m_incomingEdges.GetAt(i) == this) {
						obj->m_incomingEdges.RemoveAt(i);
					}
				}
			}
			//if a previous destination edge exists, remove the reference from the old destination edge
			CProMoEdgeModel* edge = dynamic_cast<CProMoEdgeModel*>(oldDest);
			if (edge) {
				edge->m_source = NULL;
				//edge->SetSource(NULL);
			}
		}


		if (destination) {
			//if the new destination block exists, add a reference to the new destination block
			CProMoBlockModel* obj = dynamic_cast<CProMoBlockModel*>(destination);
			if (obj) {
				obj->m_incomingEdges.Add(this);
			}
			//if a previous destination edge exists, remove the reference from the old destination edge
			CProMoEdgeModel* edge = dynamic_cast<CProMoEdgeModel*>(m_dest);
			if (edge) {
				//edge->m_source = this;
				edge->SetSource(this);
			}
		}
	}
}

CProMoModel* CProMoEdgeModel::GetSource() const
{
	return m_source;
}

CProMoModel* CProMoEdgeModel::GetDestination() const
{
	return m_dest;
}


BOOL CProMoEdgeModel::canConnectSource(CProMoModel* source)
{
	CProMoBlockModel* obj = dynamic_cast<CProMoBlockModel*>(source);
	if (obj) {
		return TRUE;
	}
	return FALSE;
}

BOOL CProMoEdgeModel::canConnectDestination(CProMoModel* destination)
{
	CProMoBlockModel* obj = dynamic_cast<CProMoBlockModel*>(destination);
	if (obj) {
		return TRUE;
	}
	return FALSE;
}

CProMoEdgeView* CProMoEdgeModel::getLastSegment()
{
	CObArray* views = getViews();
	for (int i = 0; i < views->GetSize(); i++) {
		CProMoEdgeView* view = dynamic_cast<CProMoEdgeView*>(views->GetAt(i));
		if (view) {
			if (view->GetDestination() == NULL) {
				return view;
			}
		}
	}
	return NULL;
}

CProMoEdgeView* CProMoEdgeModel::getFirstSegment()
{
	CObArray* views = getViews();
	for (int i = 0; i < views->GetSize(); i++) {
		CProMoEdgeView* view = dynamic_cast<CProMoEdgeView*>(views->GetAt(i));
		if (view) {
			if (view->GetSource() == NULL) {
				return view;
			}
		}
	}
	return NULL;
}


CProMoModel* CProMoEdgeModel::CreateFromString(const CString& str)
/* ============================================================
	Function :		CProMoEdgeModel::CreateFromString
	Description :	Static factory function that creates and
					returns an instance of this class if str
					is a valid representation.

	Return :		CProMoModel*		-	The object, or NULL
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

	CProMoEdgeModel* obj = new CProMoEdgeModel;
	if (!obj->FromString(str))
	{
		delete obj;
		obj = NULL;
	}

	return obj;

}

CString CProMoEdgeModel::GetDefaultGetString() const
{
	/* ============================================================
	Function :		CProMoEdgeModel::GetDefaultString
	Description :	Gets the default properties of the object
					as a string.
	Access :		Protected

	Return :		CString	-	Resulting string
	Parameters :	none

	Usage :			Call as a part of the saving of objects
					to disk.

   ============================================================*/

	CString str;

	CString name = GetName();
	CDiagramEntity::CStringReplace(name, _T(":"), _T("\\colon"));
	CDiagramEntity::CStringReplace(name, _T(";"), _T("\\semicolon"));
	CDiagramEntity::CStringReplace(name, _T(","), _T("\\comma"));
	CDiagramEntity::CStringReplace(name, _T("\r\n"), _T("\\newline"));

	CString sourceString = _T("");
	CString destString = _T("");


	if (m_source) {
		sourceString = m_source->GetName();
		CDiagramEntity::CStringReplace(sourceString, _T(":"), _T("\\colon"));
		CDiagramEntity::CStringReplace(sourceString, _T(";"), _T("\\semicolon"));
		CDiagramEntity::CStringReplace(sourceString, _T(","), _T("\\comma"));
		CDiagramEntity::CStringReplace(sourceString, _T("\r\n"), _T("\\newline"));
	}

	if (m_dest) {
		destString = m_dest->GetName();
		CDiagramEntity::CStringReplace(destString, _T(":"), _T("\\colon"));
		CDiagramEntity::CStringReplace(destString, _T(";"), _T("\\semicolon"));
		CDiagramEntity::CStringReplace(destString, _T(","), _T("\\comma"));
		CDiagramEntity::CStringReplace(destString, _T("\r\n"), _T("\\newline"));
	}

	str.Format(_T("%s:%s,%s,%s"), (LPCTSTR)GetType(), (LPCTSTR)name, (LPCTSTR)sourceString, (LPCTSTR)destString);

	return str;

}