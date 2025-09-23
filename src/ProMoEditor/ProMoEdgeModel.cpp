/* ==========================================================================

	Copyright © 2025 Technical University of Denmark

	CProMoEdgeModel

	Author :		Giovanni Meroni

	Purpose :		"CProMoEdgeModel" represents the model of all
					line/edge objects (views) that can be drawn and managed
					by "CProMoEditor".

	Description :	With respect to "CProMoModel", "CProMoEdgeModel" keeps
					track of source and destination "CProMoModel" objects.
					It is also assumed that an edge model has 1 or more
					views, each representing a (connected) segment of that 
					edge.

	Usage :			Models that represent a node in a graph should be
					derived from this class.

   ========================================================================*/
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
	return obj;
}


void CProMoEdgeModel::SetSource(CProMoBlockModel* source)
/* ============================================================
	Function :		CProMoEdgeModel::SetSource
	Description :	Makes the object being passed as input
					parameter the source of this edge
	Access :		Protected

	Return :		void
	Parameters :	CProMoBlockModel* source	-	the object 
													that should
													be the
													source

   ============================================================*/
{

	if (m_source != source && (!source || CanConnectSource(source))) {

		//set the new source	
		CProMoBlockModel* oldSource = m_source;
		m_source = source;

		//if a previous source block exists, remove the reference from the old source block
		if (oldSource) {
			for (int i = 0; i < oldSource->m_outgoingEdges.GetSize(); i++) {
				if (oldSource->m_outgoingEdges.GetAt(i) == this) {
					oldSource->m_outgoingEdges.RemoveAt(i);
				}
			}
		}

		//if the new source block exists, add a reference to the new source block
		if (source) {
			source->m_outgoingEdges.Add(this);
		}
	}
}

void CProMoEdgeModel::SetDestination(CProMoBlockModel* destination)
/* ============================================================
	Function :		CProMoEdgeModel::SetDestination
	Description :	Makes the object being passed as input
					parameter the destination of this edge
	Access :		Protected

	Return :		void
	Parameters :	CProMoBlockModel* destination	-	the 
														object
														that 
														should
														be the
														destination

   ============================================================*/
{
	if (m_dest != destination && (!destination || CanConnectDestination(destination))) {

		//set the new destination	
		CProMoBlockModel* oldDest = m_dest;
		m_dest = destination;

		//if a previous destination block exists, remove the reference from the old destination block
		if (oldDest) {
			for (int i = 0; i < oldDest->m_incomingEdges.GetSize(); i++) {
				if (oldDest->m_incomingEdges.GetAt(i) == this) {
					oldDest->m_incomingEdges.RemoveAt(i);
				}
			}
		}

		//if the new destination block exists, add a reference to the new destination block
		if (destination) {
			destination->m_incomingEdges.Add(this);
		}
	}
}

CProMoBlockModel* CProMoEdgeModel::GetSource() const
/* ============================================================
	Function :		CProMoEdgeModel::GetSource
	Description :	Returns a pointer to the source object
	Access :		Public

	Return :		CProMoBlockModel*	-	A pointer to the 
											source object
	Parameters :	none

   ============================================================*/
{
	return m_source;
}

CProMoBlockModel* CProMoEdgeModel::GetDestination() const
/* ============================================================
	Function :		CProMoEdgeModel::GetDestination
	Description :	Returns a pointer to the destination object
	Access :		Public

	Return :		CProMoBlockModel*	-	A pointer to the 
											destination object
	Parameters :	none

   ============================================================*/
{
	return m_dest;
}


BOOL CProMoEdgeModel::CanConnectSource(CProMoBlockModel* source)
/* ============================================================
	Function :		CProMoEdgeModel::CanConnectSource
	Description :	Returns if the object being passed as input
					parameter can be a source object.
					Override to implement diagram-specific logic.
	Access :		Public

	Return :		BOOL						-	"TRUE" if the
													object can be
													a source
	Parameters :	CProMoBlockModel* source	-	the object 
													that should 
													be the source

   ============================================================*/
{
	if (source) {
		return TRUE;
	}
	return FALSE;
}

BOOL CProMoEdgeModel::CanConnectDestination(CProMoBlockModel* destination)
/* ============================================================
	Function :		CProMoEdgeModel::CanConnectDestination
	Description :	Returns if the object being passed as input
					parameter can be a destination object.
					Override to implement diagram-specific logic.
	Access :		Public

	Return :		BOOL							-	"TRUE" if 
														the object 
														can be a 
														destination
	Parameters :	CProMoBlockModel* destination	-	the 
														object 
														that 
														should 
														be the
														destination

   ============================================================*/
{
	if (destination) {
		return TRUE;
	}
	return FALSE;
}

CProMoEdgeView* CProMoEdgeModel::GetLastSegment()
/* ============================================================
	Function :		CProMoEdgeModel::GetLastSegment
	Description :	Returns a pointer to the view for this edge
					representing the last segment.
	Access :		Public

	Return :		CProMoEdgeView*	-	The view representing
										the last segment, 
										or "NULL" if no view
										is defined.
	Parameters :	none

   ============================================================*/
{
	CObArray* views = GetViews();
	for (int i = 0; i < views->GetSize(); i++) {
		CProMoEdgeView* view = dynamic_cast<CProMoEdgeView*>(views->GetAt(i));
		if (view) {
			CProMoEdgeView* destView = dynamic_cast<CProMoEdgeView*>(view->GetDestination());
			if (!destView) {
				return view;
			}
		}
	}
	return NULL;
}

CProMoEdgeView* CProMoEdgeModel::GetFirstSegment()
/* ============================================================
	Function :		CProMoEdgeModel::GetFirstSegment
	Description :	Returns a pointer to the view for this edge
					representing the first segment.
	Access :		Public

	Return :		CProMoEdgeView*	-	The view representing
										the first segment,
										or "NULL" if no view
										is defined.
	Parameters :	none

   ============================================================*/
{
	CObArray* views = GetViews();
	for (int i = 0; i < views->GetSize(); i++) {
		CProMoEdgeView* view = dynamic_cast<CProMoEdgeView*>(views->GetAt(i));
		if (view) {
			CProMoEdgeView* sourceView = dynamic_cast<CProMoEdgeView*>(view->GetSource());
			if (!sourceView) {
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

	CString result = CProMoModel::GetDefaultGetString();

	CString str;

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

	str.Format(_T(",%s,%s"), (LPCTSTR)sourceString, (LPCTSTR)destString );

	return result + str;

}