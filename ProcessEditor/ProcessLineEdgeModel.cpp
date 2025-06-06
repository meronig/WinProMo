#include "stdafx.h"
#include "ProcessLineEdgeModel.h"
#include "ProcessEntityBlockModel.h"
#include "LinkFactory.h"


CProcessLineEdgeModel::CProcessLineEdgeModel()
/* ============================================================
	Function :		CProcessLineEdge::CProcessLineEdge
	Description :	Constructor
	Access :		Public

	Return :		void
	Parameters :	none

	Usage :

   ============================================================*/
{
	SetType(_T("process_edge_model"));
	SetName(CLinkFactory::GetID());

	m_source = NULL;
	m_dest = NULL;
}

CProcessLineEdgeModel::~CProcessLineEdgeModel()
/* ============================================================
	Function :		CProcessLineEdge::~CProcessLineEdge
	Description :	Destructor
	Access :		Public

	Return :		void
	Parameters :	none

	Usage :

   ============================================================*/
{
	CProcessLineEdgeModel* edge = dynamic_cast<CProcessLineEdgeModel*>(m_source);
	if (edge) {
		edge->SetDestination(GetDestination());
	}


	edge = dynamic_cast<CProcessLineEdgeModel*>(m_dest);
	if (edge) {
		edge->SetSource(GetSource());
	}


	SetSource(NULL);
	SetDestination(NULL);

	
}

CProcessModel* CProcessLineEdgeModel::Clone()
/* ============================================================
	Function :		CProcessLineEdge::Clone
	Description :	Clone this object to a new object.

	Return :		CDiagramEntity*	-	The new object.
	Parameters :	none

	Usage :			Call to create a clone of the object. The
					caller will have to delete the object.

   ============================================================*/

{

	CProcessLineEdgeModel* obj = new CProcessLineEdgeModel;
	//obj->Copy(this);
	obj->m_source = NULL;
	obj->m_dest = NULL;
	return obj;
}


void CProcessLineEdgeModel::SetSource(CProcessModel* source)
{

	if (m_source != source) {

		//set the new source	
		CProcessModel* oldSource = m_source;
		m_source = source;

		if (oldSource) {
			//if a previous source block exists, remove the reference from the old source block
			CProcessEntityBlockModel* obj = dynamic_cast<CProcessEntityBlockModel*>(oldSource);
			if (obj) {
				for (int i = 0; i < obj->m_outgoingEdges.GetSize(); i++) {
					if (obj->m_outgoingEdges.GetAt(i) == this) {
						obj->m_outgoingEdges.RemoveAt(i);
					}
				}
			}
			//if a previous source edge exists, remove the reference from the old source edge
			CProcessLineEdgeModel* edge = dynamic_cast<CProcessLineEdgeModel*>(oldSource);
			if (edge) {
				//edge->SetDestination(NULL);
				edge->m_dest = NULL;
			}
		}

		if (source) {
			//if the new source block exists, add a reference to the new source block
			CProcessEntityBlockModel* obj = dynamic_cast<CProcessEntityBlockModel*>(source);
			if (obj) {
				obj->m_outgoingEdges.Add(this);
			}
			//if the new source edge exists, add a reference to the new source edge
			CProcessLineEdgeModel* edge = dynamic_cast<CProcessLineEdgeModel*>(m_source);
			if (edge) {
				edge->SetDestination(this);
				//edge->m_dest = this;
			}
		}
	}
}

void CProcessLineEdgeModel::SetDestination(CProcessModel* destination)
{
	if (m_dest != destination) {

		//set the new destination	
		CProcessModel* oldDest = m_dest;
		m_dest = destination;

		if (oldDest) {
			//if a previous destination block exists, remove the reference from the old destination block
			CProcessEntityBlockModel* obj = dynamic_cast<CProcessEntityBlockModel*>(oldDest);
			if (obj) {
				for (int i = 0; i < obj->m_incomingEdges.GetSize(); i++) {
					if (obj->m_incomingEdges.GetAt(i) == this) {
						obj->m_incomingEdges.RemoveAt(i);
					}
				}
			}
			//if a previous destination edge exists, remove the reference from the old destination edge
			CProcessLineEdgeModel* edge = dynamic_cast<CProcessLineEdgeModel*>(oldDest);
			if (edge) {
				edge->m_source = NULL;
				//edge->SetSource(NULL);
			}
		}


		if (destination) {
			//if the new destination block exists, add a reference to the new destination block
			CProcessEntityBlockModel* obj = dynamic_cast<CProcessEntityBlockModel*>(destination);
			if (obj) {
				obj->m_incomingEdges.Add(this);
			}
			//if a previous destination edge exists, remove the reference from the old destination edge
			CProcessLineEdgeModel* edge = dynamic_cast<CProcessLineEdgeModel*>(m_dest);
			if (edge) {
				//edge->m_source = this;
				edge->SetSource(this);
			}
		}
	}
}

CProcessModel* CProcessLineEdgeModel::GetSource() const
{
	return m_source;
}

CProcessModel* CProcessLineEdgeModel::GetDestination() const
{
	return m_dest;
}


BOOL CProcessLineEdgeModel::canConnectSource(CProcessModel* source)
{
	CProcessEntityBlockModel* obj = dynamic_cast<CProcessEntityBlockModel*>(source);
	if (obj) {
		return TRUE;
	}
	return FALSE;
}

BOOL CProcessLineEdgeModel::canConnectDestination(CProcessModel* destination)
{
	CProcessEntityBlockModel* obj = dynamic_cast<CProcessEntityBlockModel*>(destination);
	if (obj) {
		return TRUE;
	}
	return FALSE;
}

CProcessLineEdgeView* CProcessLineEdgeModel::getLastSegment()
{
	CObArray* views = getViews();
	for (int i = 0; i < views->GetSize(); i++) {
		CProcessLineEdgeView* view = dynamic_cast<CProcessLineEdgeView*>(views->GetAt(i));
		if (view) {
			if (view->GetDestination() == NULL) {
				return view;
			}
		}
	}
	return NULL;
}

CProcessLineEdgeView* CProcessLineEdgeModel::getFirstSegment()
{
	CObArray* views = getViews();
	for (int i = 0; i < views->GetSize(); i++) {
		CProcessLineEdgeView* view = dynamic_cast<CProcessLineEdgeView*>(views->GetAt(i));
		if (view) {
			if (view->GetSource() == NULL) {
				return view;
			}
		}
	}
	return NULL;
}


CProcessModel* CProcessLineEdgeModel::CreateFromString(const CString& str)
/* ============================================================
	Function :		CProcessEntityBlock::CreateFromString
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

	CProcessLineEdgeModel* obj = new CProcessLineEdgeModel;
	if (!obj->FromString(str))
	{
		delete obj;
		obj = NULL;
	}

	return obj;

}

CString CProcessLineEdgeModel::GetDefaultGetString() const
{
	/* ============================================================
	Function :		CProcessEntityBlock::GetDefaultString
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