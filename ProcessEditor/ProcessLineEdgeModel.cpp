#include "ProcessLineEdgeModel.h"
#include "ProcessEntityBlockModel.h"

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


bool CProcessLineEdgeModel::canConnectSource(CProcessModel* source)
{
	CProcessEntityBlockModel* obj = dynamic_cast<CProcessEntityBlockModel*>(source);
	if (obj) {
		return true;
	}
	return false;
}

bool CProcessLineEdgeModel::canConnectDestination(CProcessModel* destination)
{
	CProcessEntityBlockModel* obj = dynamic_cast<CProcessEntityBlockModel*>(destination);
	if (obj) {
		return true;
	}
	return false;
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