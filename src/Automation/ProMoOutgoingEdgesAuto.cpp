/* ==========================================================================

	Copyright © 2026 Technical University of Denmark

	CProMoOutgoingEdgesAuto

	Author :		Giovanni Meroni

	Purpose :		"CProMoOutgoingEdgesAuto" is an automation object that
					represents the collection of outgoing edges in a block. 
					It provides methods to access the edges, to add new
					edges, and to unlink existing edges.

	Description :	"CProMoOutgoingEdgesAuto" provides the implementation
					of the methods and properties that are common to all
					outgoing edges collections.

   ========================================================================*/
#include "stdafx.h"
#include "ProMoOutgoingEdgesAuto.h"
#include "../ProMoEditor/ProMoEdgeModel.h"
#include "../FileUtils/SafeArrayWrapper.h"
#include "ProMoEdgeAuto.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CProMoOutgoingEdgesAuto

IMPLEMENT_DYNCREATE(CProMoOutgoingEdgesAuto, CProMoBlockChildAuto)

CProMoOutgoingEdgesAuto::CProMoOutgoingEdgesAuto()
/* ============================================================
	Function :		CProMoOutgoingEdgesAuto::CProMoOutgoingEdgesAuto
	Description :	Constructor
	Access :		Public

	Return :		void
	Parameters :	none
	============================================================ */
{
}

CProMoOutgoingEdgesAuto::~CProMoOutgoingEdgesAuto()
/* ============================================================
	Function :		CProMoOutgoingEdgesAuto::~CProMoOutgoingEdgesAuto
	Description :	Destructor
	Access :		Public

	Return :		void
	Parameters :	none
	============================================================ */
{
}

void CProMoOutgoingEdgesAuto::SetElementAutoObject(CProMoElementAuto* pElementAuto) 
/* ============================================================
	Function :		CProMoOutgoingEdgesAuto::SetElementAutoObject
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

BEGIN_MESSAGE_MAP(CProMoOutgoingEdgesAuto, CProMoBlockChildAuto)
	//{{AFX_MSG_MAP(CProMoOutgoingEdgesAuto)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

BEGIN_DISPATCH_MAP(CProMoOutgoingEdgesAuto, CProMoBlockChildAuto)
	//{{AFX_DISPATCH_MAP(CProMoOutgoingEdgesAuto)
	DISP_PROPERTY_EX(CProMoOutgoingEdgesAuto, "IDs", GetIDs, SetIDs, VT_VARIANT)
	DISP_FUNCTION(CProMoOutgoingEdgesAuto, "Count", Count, VT_I2, VTS_NONE)
	DISP_FUNCTION(CProMoOutgoingEdgesAuto, "Add", Add, VT_BOOL, VTS_DISPATCH)
	DISP_FUNCTION(CProMoOutgoingEdgesAuto, "Remove", Remove, VT_BOOL, VTS_VARIANT)
	//Common to CProMoElementChildAuto
	DISP_FUNCTION(CProMoElementChildAuto, "Element", Element, VT_DISPATCH, VTS_NONE)
	//Common to CProMoDiagramChildAuto
	DISP_FUNCTION(CProMoDiagramChildAuto, "Diagram", Diagram, VT_DISPATCH, VTS_NONE)
	//Common to CProMoAppChildAuto
	DISP_FUNCTION(CProMoAppChildAuto, "Application", Application, VT_DISPATCH, VTS_NONE)
	//Default property
	DISP_PROPERTY_PARAM(CProMoOutgoingEdgesAuto, "Item", GetItem, SetItem, VT_DISPATCH, VTS_VARIANT)
	DISP_DEFVALUE(CProMoOutgoingEdgesAuto, "Item")
	//}}AFX_DISPATCH_MAP
END_DISPATCH_MAP()

// Note: we add support for IID_IProMoOutgoingEdgesAuto to support typesafe binding
//  from VBA.  This IID must match the GUID that is attached to the 
//  dispinterface in the .ODL file.

// {38EA3769-08C3-11F1-9744-000C2976A615}
static const IID IID_IProMoOutgoingEdgesAuto =
{ 0x38ea3769, 0x8c3, 0x11f1, { 0x97, 0x44, 0x0, 0xc, 0x29, 0x76, 0xa6, 0x15 } };

BEGIN_INTERFACE_MAP(CProMoOutgoingEdgesAuto, CProMoBlockChildAuto)
	INTERFACE_PART(CProMoOutgoingEdgesAuto, IID_IProMoOutgoingEdgesAuto, Dispatch)
END_INTERFACE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CProMoOutgoingEdgesAuto message handlers

short CProMoOutgoingEdgesAuto::Count() 
/* ============================================================
	Function :		CProMoOutgoingEdgesAuto::Count
	Description :	Returns the number of outgoing edges in the block.
	Access :		Public

	Return :		short	-	The number of outgoing edges in the block.
	Parameters :	none
	============================================================ */
{
	if (GetBlockModel()) {
		CObArray outgoingEdges;
		GetBlockModel()->GetOutgoingEdges(outgoingEdges);
		return outgoingEdges.GetSize();
	}

	return 0;
}

LPDISPATCH CProMoOutgoingEdgesAuto::GetItem(const VARIANT FAR& item) 
/* ============================================================
	Function :		CProMoOutgoingEdgesAuto::GetItem
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
		CObArray outgoingEdges;
		GetBlockModel()->GetOutgoingEdges(outgoingEdges);
		CProMoEdgeModel* pModel = dynamic_cast<CProMoEdgeModel*>(FindModel(item, outgoingEdges));

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

void CProMoOutgoingEdgesAuto::SetItem(const VARIANT FAR& Item, LPDISPATCH newValue) 
/* ============================================================
	Function :		CProMoOutgoingEdgesAuto::SetItem
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

BOOL CProMoOutgoingEdgesAuto::Add(LPDISPATCH item) 
/* ============================================================
	Function :		CProMoOutgoingEdgesAuto::Add
	Description :	Adds an edge to the collection. The edge to add
					is specified by passing a pointer to its automation
					object's IDispatch interface as a parameter. The edge
					is added as an outgoing edge of the block associated
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
				return pEdgeAuto->SetSourceBlock(GetBlockModel());
			}
		}
	}

	return FALSE;

}

BOOL CProMoOutgoingEdgesAuto::Remove(const VARIANT FAR& item) 
/* ============================================================
	Function :		CProMoOutgoingEdgesAuto::Remove
	Description :	Removes an edge from the collection. The edge to remove
					is specified by passing its index or name as a parameter.
					The edge is removed from being an outgoing edge of the block
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
		CObArray outgoingEdges;
		GetBlockModel()->GetOutgoingEdges(outgoingEdges);
		CProMoEdgeModel* pModel = dynamic_cast<CProMoEdgeModel*>(FindModel(item, outgoingEdges));
		if (pModel) {
			CProMoEdgeView* pView = dynamic_cast<CProMoEdgeView*>(pModel->GetFirstSegment());
			if (pView) {
				GetContainer()->Snapshot();
				pView->SetSource(NULL);
				GetDiagramAutoObject()->NotifyChange();
				return TRUE;
			}
		}
	}

	return FALSE;
}

VARIANT CProMoOutgoingEdgesAuto::GetIDs() 
/* ============================================================
	Function :		CProMoOutgoingEdgesAuto::GetIDs
	Description :	Returns an array containing the names of the edges
					in the collection.
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
		CObArray outgoingEdges;
		CProMoEdgeModel* pModel = NULL;
		GetBlockModel()->GetOutgoingEdges(outgoingEdges);
		for (int i = 0; i < outgoingEdges.GetSize(); i++) {
			pModel = dynamic_cast<CProMoEdgeModel*>(outgoingEdges.GetAt(i));
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

void CProMoOutgoingEdgesAuto::SetIDs(const VARIANT FAR& newValue) 
/* ============================================================
	Function :		CProMoOutgoingEdgesAuto::SetIDs
	Description :	Sets the list of the names of the outgoing edges.
					This property is read-only, so this function simply
					raises an exception.
	Access :		Public

	Return :		void
	Parameters :	VARIANT FAR& newValue	-	a VARIANT containing
												a safe array of
												BSTRs with the
												names of the outgoing
												edges to set.
   ============================================================ */
{
	SetNotSupported();

}
