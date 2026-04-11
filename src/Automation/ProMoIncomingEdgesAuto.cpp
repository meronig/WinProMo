/* ==========================================================================

	Copyright © 2026 Technical University of Denmark

	CProMoIncomingEdgesAuto

	Author :		Giovanni Meroni

	Purpose :		"CProMoIncomingEdgesAuto" is an automation object that
					represents the collection of incoming edges in a block.
					It provides methods to access the edges, to add new
					edges, and to unlink existing edges.

	Description :	"CProMoIncomingEdgesAuto" provides the implementation
					of the methods and properties that are common to all
					incoming edges collections.

   ========================================================================*/
#include "stdafx.h"
#include "ProMoIncomingEdgesAuto.h"
#include "../ProMoEditor/ProMoEdgeModel.h"
#include "../FileUtils/SafeArrayWrapper.h"
#include "ProMoEdgeAuto.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CProMoIncomingEdgesAuto

IMPLEMENT_DYNCREATE(CProMoIncomingEdgesAuto, CProMoBlockChildAuto)

CProMoIncomingEdgesAuto::CProMoIncomingEdgesAuto()
/* ============================================================
	Function :		CProMoIncomingEdgesAuto::CProMoIncomingEdgesAuto
	Description :	Constructor
	Access :		Public

	Return :		void
	Parameters :	none
	============================================================ */
{
}

CProMoIncomingEdgesAuto::~CProMoIncomingEdgesAuto()
/* ============================================================
	Function :		CProMoIncomingEdgesAuto::~CProMoIncomingEdgesAuto
	Description :	Destructor
	Access :		Public

	Return :		void
	Parameters :	none
	============================================================ */
{
}

void CProMoIncomingEdgesAuto::SetElementAutoObject(CProMoElementAuto* pElementAuto) 
/* ============================================================
	Function :		CProMoIncomingEdgesAuto::SetElementAutoObject
	Description :	Sets the element automation object to the
					object passed as a parameter. Overridden
					to avoid creating circular references between
					COM objects that would prevent them from being
					released.
	Access :		Public

	Return :		void
	Parameters :	CProMoElementAuto* pElementAuto	-	The element
														automation
														object to set.
   ============================================================*/

{
	SetDiagramAutoObject(pElementAuto ? pElementAuto->GetDiagramAutoObject() : NULL);
	m_pElementAuto = pElementAuto;
}


BEGIN_MESSAGE_MAP(CProMoIncomingEdgesAuto, CProMoBlockChildAuto)
	//{{AFX_MSG_MAP(CProMoIncomingEdgesAuto)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

BEGIN_DISPATCH_MAP(CProMoIncomingEdgesAuto, CProMoBlockChildAuto)
	//{{AFX_DISPATCH_MAP(CProMoIncomingEdgesAuto)
	DISP_PROPERTY_EX(CProMoIncomingEdgesAuto, "IDs", GetIDs, SetIDs, VT_VARIANT)
	DISP_FUNCTION(CProMoIncomingEdgesAuto, "Count", Count, VT_I2, VTS_NONE)
	DISP_FUNCTION(CProMoIncomingEdgesAuto, "Add", Add, VT_BOOL, VTS_DISPATCH)
	DISP_FUNCTION(CProMoIncomingEdgesAuto, "Remove", Remove, VT_BOOL, VTS_VARIANT)
	//Common to CProMoElementChildAuto
	DISP_FUNCTION(CProMoElementChildAuto, "Element", Element, VT_DISPATCH, VTS_NONE)
	//Common to CProMoDiagramChildAuto
	DISP_FUNCTION(CProMoDiagramChildAuto, "Diagram", Diagram, VT_DISPATCH, VTS_NONE)
	//Common to CProMoAppChildAuto
	DISP_FUNCTION(CProMoAppChildAuto, "Application", Application, VT_DISPATCH, VTS_NONE)
	//Defaut property
	DISP_PROPERTY_PARAM(CProMoIncomingEdgesAuto, "Item", GetItem, SetItem, VT_DISPATCH, VTS_VARIANT)
	DISP_DEFVALUE(CProMoIncomingEdgesAuto, "Item")
	//}}AFX_DISPATCH_MAP
END_DISPATCH_MAP()

// Note: we add support for IID_IProMoIncomingEdgesAuto to support typesafe binding
//  from VBA.  This IID must match the GUID that is attached to the 
//  dispinterface in the .ODL file.

// {38EA3766-08C3-11F1-9744-000C2976A615}
static const IID IID_IProMoIncomingEdgesAuto =
{ 0x38ea3766, 0x8c3, 0x11f1, { 0x97, 0x44, 0x0, 0xc, 0x29, 0x76, 0xa6, 0x15 } };

BEGIN_INTERFACE_MAP(CProMoIncomingEdgesAuto, CProMoBlockChildAuto)
	INTERFACE_PART(CProMoIncomingEdgesAuto, IID_IProMoIncomingEdgesAuto, Dispatch)
END_INTERFACE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CProMoIncomingEdgesAuto message handlers

short CProMoIncomingEdgesAuto::Count() 
/* ============================================================
	Function :		CProMoIncomingEdgesAuto::Count
	Description :	Returns the number of incoming edges in the block.
	Access :		Public

	Return :		short	-	The number of incoming edges.
	Parameters :	none
	============================================================ */
{
	if (GetBlockModel()) {
		CObArray incomingEdges;
		GetBlockModel()->GetIncomingEdges(incomingEdges);
		return incomingEdges.GetSize();
	}

	return 0;
}

LPDISPATCH CProMoIncomingEdgesAuto::GetItem(const VARIANT FAR& item)
/* ============================================================
	Function :		CProMoIncomingEdgesAuto::GetItem
	Description :	Returns the edge automation object corresponding
					to the specified index or name.
	Access :		Public
	Return :		LPDISPATCH			-	a pointer to the
											IDispatch interface
											of the edge
											automation object
											corresponding to the
											specified index or name,
											or "NULL" if no edge
											with the specified index
											or name is found.
	Parameters :	VARIANT FAR& Item 	-	the index or name of the
											edge to return.
   ============================================================ */
{
	if (GetBlockModel()) {
		CObArray incomingEdges;
		GetBlockModel()->GetIncomingEdges(incomingEdges);
		CProMoEdgeModel* pModel = dynamic_cast<CProMoEdgeModel*>(FindModel(item, incomingEdges));
		
		if (pModel) {
			CProMoElementAuto* pElementAuto = dynamic_cast<CProMoElementAuto*>(pModel->GetAutomationObject());
			if (pElementAuto) {
				pElementAuto->SetDiagramAutoObject(GetDiagramAutoObject());
				return pElementAuto->GetIDispatch(TRUE);
			}
		}
	}

	return NULL;
}

void CProMoIncomingEdgesAuto::SetItem(const VARIANT FAR& Item, LPDISPATCH newValue)
/* ============================================================
	Function :		CProMoIncomingEdgesAuto::SetItem
	Description :	Sets the edge automation object corresponding
					to the specified index or name. This property is
					read-only, so this function simply raises an
					exception.
	Access :		Public
	Return :		void
	Parameters :	VARIANT FAR& Item 	-	the index or name of the
											edge to set.
					LPDISPATCH newValue	-	a pointer to the new
											IDispatch interface of the
											edge automation object to
											set for the specified index or
											name.
   ============================================================ */
{
	SetNotSupported();

}

BOOL CProMoIncomingEdgesAuto::Add(LPDISPATCH item) 
/* ============================================================
	Function :		CProMoIncomingEdgesAuto::Add
	Description :	Adds an edge to the collection. The edge to add
					is specified by passing a pointer to its automation
					object's IDispatch interface as a parameter. The edge
					is added as an incoming edge of the block associated
					to the current automation object.
	Access :		Public
	Return :		BOOL			-	"TRUE" if the edge is successfully added
										to the collection, "FALSE" otherwise.
	Parameters :	LPDISPATCH item -	a pointer to the IDispatch interface of
										the edge automation object corresponding
										to the edge to add to the collection.
   ============================================================ */
{
	if (GetBlockModel()) {
		if (item) {
			CProMoEdgeAuto* pEdgeAuto = CProMoEdgeAuto::FromIDispatch(item);
			if (pEdgeAuto) {
				return pEdgeAuto->SetDestinationBlock(GetBlockModel());
			}
		}
	}
	
	return FALSE;
}

BOOL CProMoIncomingEdgesAuto::Remove(const VARIANT FAR& item) 
/* ============================================================
	Function :		CProMoIncomingEdgesAuto::Remove
	Description :	Removes an edge from the collection. The edge to remove
					is specified by passing its index or name as a parameter.
					The edge is removed from being an incoming edge of the block
					represented by the current automation object.
	Access :		Public
	Return :		BOOL				-	"TRUE" if the edge is 
											successfully removed
											from the collection, 
											"FALSE" otherwise.
	Parameters :	VARIANT FAR& Item 	-	the index or name of 
											the edge to remove 
											from the collection.
   ============================================================ */
{
	if (GetBlockModel()) {
		CObArray incomingEdges;
		GetBlockModel()->GetIncomingEdges(incomingEdges);
		CProMoEdgeModel* pModel = dynamic_cast<CProMoEdgeModel*>(FindModel(item, incomingEdges));
		if (pModel) {
			CProMoEdgeView* pView = dynamic_cast<CProMoEdgeView*>(pModel->GetLastSegment());
			if (pView) {
				GetContainer()->Snapshot();
				pView->SetDestination(NULL);
				GetDiagramAutoObject()->NotifyChange();
				return TRUE;
			}
		}
	}

	return FALSE;
}

VARIANT CProMoIncomingEdgesAuto::GetIDs() 
/* ============================================================
	Function :		CProMoIncomingEdgesAuto::GetIDs
	Description :	Returns a SAFEARRAY containing the names of the
					incoming edges in the block.
	Access :		Public

	Return :		VARIANT	-	a VARIANT containing a SAFEARRAY
								of BSTRs with the names of the edges
								in the collection.
	Parameters :	none
   ============================================================ */
{
	VARIANT vaResult;
	VariantInit(&vaResult);

	if (GetBlockModel()) {

		CStringArray names;
		CObArray incomingEdges;
		CProMoEdgeModel* pModel = NULL;
		GetBlockModel()->GetIncomingEdges(incomingEdges);
		for (int i = 0; i < incomingEdges.GetSize(); i++) {
			pModel = dynamic_cast<CProMoEdgeModel*>(incomingEdges.GetAt(i));
			if (pModel) {
				names.Add(pModel->GetName());
			}
		}

		HRESULT hr = CSafeArrayWrapper::CreateVariantFromCStringArray(names, vaResult);
		if (FAILED(hr))
			AfxThrowOleException(hr);
	}

	return vaResult;
}

void CProMoIncomingEdgesAuto::SetIDs(const VARIANT FAR& newValue) 
/* ============================================================
	Function :		CProMoIncomingEdgesAuto::SetIDs
	Description :	Sets the list of the names of the incoming edges.
					This property is read-only, so this function simply
					raises an exception.
	Access :		Public

	Return :		void
	Parameters :	VARIANT FAR& newValue	-	a VARIANT containing
												a safe array of
												BSTRs with the
												names of the incoming
												edges to set.
   ============================================================ */
{
	SetNotSupported();

}
