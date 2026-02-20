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

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CProMoIncomingEdgesAuto

IMPLEMENT_DYNCREATE(CProMoIncomingEdgesAuto, CProMoBlockChildAuto)

CProMoIncomingEdgesAuto::CProMoIncomingEdgesAuto()
{
}

CProMoIncomingEdgesAuto::~CProMoIncomingEdgesAuto()
{
}

void CProMoIncomingEdgesAuto::SetElementAutoObject(CProMoElementAuto* pElementAuto) {
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
	DISP_FUNCTION(CProMoIncomingEdgesAuto, "Count", Count, VT_I4, VTS_NONE)
	DISP_FUNCTION(CProMoIncomingEdgesAuto, "Add", Add, VT_BOOL, VTS_DISPATCH)
	DISP_FUNCTION(CProMoIncomingEdgesAuto, "Remove", Remove, VT_BOOL, VTS_VARIANT)
	DISP_PROPERTY_PARAM(CProMoIncomingEdgesAuto, "Item", GetItem, SetItem, VT_DISPATCH, VTS_VARIANT)
	DISP_DEFVALUE(CProMoIncomingEdgesAuto, "Item")
	//}}AFX_DISPATCH_MAP
END_DISPATCH_MAP()

// Note: we add support for IID_IProMoIncomingEdgesAuto to support typesafe binding
//  from VBA.  This IID must match the GUID that is attached to the 
//  dispinterface in the .ODL file.

// {18EA376B-08C3-11F1-9744-000C2976A615}
static const IID IID_IProMoIncomingEdgesAuto =
{ 0x18ea376b, 0x8c3, 0x11f1, { 0x97, 0x44, 0x0, 0xc, 0x29, 0x76, 0xa6, 0x15 } };

BEGIN_INTERFACE_MAP(CProMoIncomingEdgesAuto, CProMoBlockChildAuto)
	INTERFACE_PART(CProMoIncomingEdgesAuto, IID_IProMoIncomingEdgesAuto, Dispatch)
END_INTERFACE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CProMoIncomingEdgesAuto message handlers

long CProMoIncomingEdgesAuto::Count() 
{
	if (GetBlockModel()) {
		CObArray incomingEdges;
		GetBlockModel()->GetIncomingEdges(incomingEdges);
		return incomingEdges.GetSize();
	}

	return 0;
}

LPDISPATCH CProMoIncomingEdgesAuto::GetItem(const VARIANT FAR& Item) 
{
	CVariantWrapper wrapper(Item);

	if (GetBlockModel()) {
		CObArray incomingEdges;
		CProMoEdgeModel* pModel = NULL;
		GetBlockModel()->GetIncomingEdges(incomingEdges);
		if (wrapper.GetType() != VT_BSTR) {
			if (wrapper.GetInt() >= 0 && wrapper.GetInt() < incomingEdges.GetSize()) {
				pModel = dynamic_cast<CProMoEdgeModel*>(incomingEdges.GetAt(wrapper.GetInt()));
			}
		}
		else {
			for (int i = 0; i < incomingEdges.GetSize(); i++) {
				pModel = dynamic_cast<CProMoEdgeModel*>(incomingEdges.GetAt(i));
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

void CProMoIncomingEdgesAuto::SetItem(const VARIANT FAR& Item, LPDISPATCH newValue) 
{
	SetNotSupported();

}

BOOL CProMoIncomingEdgesAuto::Add(LPDISPATCH Item) 
{
	// TODO: Add your dispatch handler code here

	return TRUE;
}

BOOL CProMoIncomingEdgesAuto::Remove(const VARIANT FAR& Item) 
{
	// TODO: Add your dispatch handler code here

	return TRUE;
}

VARIANT CProMoIncomingEdgesAuto::GetIDs() 
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
{
	SetNotSupported();

}
