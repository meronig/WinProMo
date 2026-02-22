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

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CProMoOutgoingEdgesAuto

IMPLEMENT_DYNCREATE(CProMoOutgoingEdgesAuto, CProMoBlockChildAuto)

CProMoOutgoingEdgesAuto::CProMoOutgoingEdgesAuto()
{
}

CProMoOutgoingEdgesAuto::~CProMoOutgoingEdgesAuto()
{
}

void CProMoOutgoingEdgesAuto::SetElementAutoObject(CProMoElementAuto* pElementAuto) {
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
	DISP_PROPERTY_PARAM(CProMoOutgoingEdgesAuto, "Item", GetItem, SetItem, VT_DISPATCH, VTS_VARIANT)
	DISP_DEFVALUE(CProMoOutgoingEdgesAuto, "Item")
	//}}AFX_DISPATCH_MAP
END_DISPATCH_MAP()

// Note: we add support for IID_IProMoOutgoingEdgesAuto to support typesafe binding
//  from VBA.  This IID must match the GUID that is attached to the 
//  dispinterface in the .ODL file.

// {18EA376A-08C3-11F1-9744-000C2976A615}
static const IID IID_IProMoOutgoingEdgesAuto =
{ 0x18ea376a, 0x8c3, 0x11f1, { 0x97, 0x44, 0x0, 0xc, 0x29, 0x76, 0xa6, 0x15 } };

BEGIN_INTERFACE_MAP(CProMoOutgoingEdgesAuto, CProMoBlockChildAuto)
	INTERFACE_PART(CProMoOutgoingEdgesAuto, IID_IProMoOutgoingEdgesAuto, Dispatch)
END_INTERFACE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CProMoOutgoingEdgesAuto message handlers

short CProMoOutgoingEdgesAuto::Count() 
{
	if (GetBlockModel()) {
		CObArray outgoingEdges;
		GetBlockModel()->GetOutgoingEdges(outgoingEdges);
		return outgoingEdges.GetSize();
	}

	return 0;
}

LPDISPATCH CProMoOutgoingEdgesAuto::GetItem(const VARIANT FAR& Item) 
{
	CVariantWrapper wrapper(Item);

	if (GetBlockModel()) {
		CObArray outgoingEdges;
		CProMoEdgeModel* pModel = NULL;
		GetBlockModel()->GetOutgoingEdges(outgoingEdges);
		if (wrapper.GetType() != VT_BSTR) {
			if (wrapper.GetInt() >= 0 && wrapper.GetInt() < outgoingEdges.GetSize()) {
				pModel = dynamic_cast<CProMoEdgeModel*>(outgoingEdges.GetAt(wrapper.GetInt()));
			}
		}
		else {
			for (int i = 0; i < outgoingEdges.GetSize(); i++) {
				pModel = dynamic_cast<CProMoEdgeModel*>(outgoingEdges.GetAt(i));
				if (pModel && pModel->GetName() == wrapper.GetString()) {
					break;
				}
				pModel = NULL;
			}
		}

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
{
	SetNotSupported();

}

BOOL CProMoOutgoingEdgesAuto::Add(LPDISPATCH Item) 
{
	// TODO: Add your dispatch handler code here

	return TRUE;
}

BOOL CProMoOutgoingEdgesAuto::Remove(const VARIANT FAR& Item) 
{
	// TODO: Add your dispatch handler code here

	return TRUE;
}

VARIANT CProMoOutgoingEdgesAuto::GetIDs() 
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
{
	SetNotSupported();

}
