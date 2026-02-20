/* ==========================================================================

	Copyright © 2026 Technical University of Denmark

	CProMoSubBlocksAuto

	Author :		Giovanni Meroni

	Purpose :		"CProMoSubBlocksAuto" is an automation object that
					represents the collection of subblocks in a block. It
					provides methods to access the subblocks, to add new
					subblocks, and to unlink existing subblocks.

	Description :	"CProMoSubBlocksAuto" provides the implementation
					of the methods and properties that are common to all
					subblocks collections.

   ========================================================================*/
#include "stdafx.h"
#include "ProMoSubBlocksAuto.h"
#include "../ProMoEditor/ProMoBlockModel.h"
#include "../FileUtils/SafeArrayWrapper.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CProMoSubBlocksAuto

IMPLEMENT_DYNCREATE(CProMoSubBlocksAuto, CProMoBlockChildAuto)

CProMoSubBlocksAuto::CProMoSubBlocksAuto()
{
}

CProMoSubBlocksAuto::~CProMoSubBlocksAuto()
{
}

void CProMoSubBlocksAuto::SetElementAutoObject(CProMoElementAuto* pElementAuto) {
	SetDiagramAutoObject(pElementAuto ? pElementAuto->GetDiagramAutoObject() : NULL); 
	m_pElementAuto = pElementAuto;
}

BEGIN_MESSAGE_MAP(CProMoSubBlocksAuto, CProMoBlockChildAuto)
	//{{AFX_MSG_MAP(CProMoSubBlocksAuto)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

BEGIN_DISPATCH_MAP(CProMoSubBlocksAuto, CProMoBlockChildAuto)
	//{{AFX_DISPATCH_MAP(CProMoSubBlocksAuto)
	DISP_PROPERTY_EX(CProMoSubBlocksAuto, "IDs", GetIDs, SetIDs, VT_VARIANT)
	DISP_FUNCTION(CProMoSubBlocksAuto, "Count", Count, VT_I4, VTS_NONE)
	DISP_FUNCTION(CProMoSubBlocksAuto, "Add", Add, VT_BOOL, VTS_DISPATCH)
	DISP_FUNCTION(CProMoSubBlocksAuto, "Remove", Remove, VT_BOOL, VTS_VARIANT)
	DISP_PROPERTY_PARAM(CProMoSubBlocksAuto, "Item", GetItem, SetItem, VT_DISPATCH, VTS_VARIANT)
	DISP_DEFVALUE(CProMoSubBlocksAuto, "Item")
	//}}AFX_DISPATCH_MAP
END_DISPATCH_MAP()

// Note: we add support for IID_IProMoSubBlocksAuto to support typesafe binding
//  from VBA.  This IID must match the GUID that is attached to the 
//  dispinterface in the .ODL file.

// {18EA376C-08C3-11F1-9744-000C2976A615}
static const IID IID_IProMoSubBlocksAuto =
{ 0x18ea376c, 0x8c3, 0x11f1, { 0x97, 0x44, 0x0, 0xc, 0x29, 0x76, 0xa6, 0x15 } };

BEGIN_INTERFACE_MAP(CProMoSubBlocksAuto, CProMoBlockChildAuto)
	INTERFACE_PART(CProMoSubBlocksAuto, IID_IProMoSubBlocksAuto, Dispatch)
END_INTERFACE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CProMoSubBlocksAuto message handlers

long CProMoSubBlocksAuto::Count() 
{
	if (GetBlockModel()) {
		CObArray subBlocks;
		GetBlockModel()->GetSubBlocks(subBlocks);
		return subBlocks.GetSize();
	}

	return 0;
}

LPDISPATCH CProMoSubBlocksAuto::GetItem(const VARIANT FAR& Item) 
{
	CVariantWrapper wrapper(Item);

	if (GetBlockModel()) {
		CObArray subBlocks;
		CProMoBlockModel* pModel = NULL;
		GetBlockModel()->GetSubBlocks(subBlocks);
		if (wrapper.GetType() != VT_BSTR) {
			if (wrapper.GetInt() >= 0 && wrapper.GetInt() < subBlocks.GetSize()) {
				pModel = dynamic_cast<CProMoBlockModel*>(subBlocks.GetAt(wrapper.GetInt()));
			}
		}
		else {
			for (int i = 0; i < subBlocks.GetSize(); i++) {
				pModel = dynamic_cast<CProMoBlockModel*>(subBlocks.GetAt(i));
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

void CProMoSubBlocksAuto::SetItem(const VARIANT FAR& Item, LPDISPATCH newValue) 
{
	SetNotSupported();

}

BOOL CProMoSubBlocksAuto::Add(LPDISPATCH Item) 
{
	// TODO: Add your dispatch handler code here

	return TRUE;
}

BOOL CProMoSubBlocksAuto::Remove(const VARIANT FAR& Item) 
{
	// TODO: Add your dispatch handler code here

	return TRUE;
}

VARIANT CProMoSubBlocksAuto::GetIDs()
{
	VARIANT vaResult;
	VariantInit(&vaResult);

	if (GetBlockModel()) {

		CStringArray names;
		CObArray subBlocks;
		CProMoBlockModel* pModel = NULL;
		GetBlockModel()->GetSubBlocks(subBlocks);
		for (int i = 0; i < subBlocks.GetSize(); i++) {
			pModel = dynamic_cast<CProMoBlockModel*>(subBlocks.GetAt(i));
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

void CProMoSubBlocksAuto::SetIDs(const VARIANT FAR& newValue) 
{
	SetNotSupported();
}
