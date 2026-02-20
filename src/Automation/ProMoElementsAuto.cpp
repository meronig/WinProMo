/* ==========================================================================

	Copyright © 2026 Technical University of Denmark

	CProMoElementsAuto

	Author :		Giovanni Meroni

	Purpose :		"CProMoElementsAuto" is an automation object that
					represents the collection of elements in a diagram.
					It provides methods to access the elements, to add new
					elements, and to delete existing elements.

	Description :	"CProMoElementsAuto" provides the implementation
					of the methods and properties that are common to all
					elements collections.

   ========================================================================*/
#include "stdafx.h"
#include "ProMoElementsAuto.h"
#include "../FileUtils/SafeArrayWrapper.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CProMoElementsAuto

IMPLEMENT_DYNCREATE(CProMoElementsAuto, CProMoDiagramChildAuto)

CProMoElementsAuto::CProMoElementsAuto()
{
}

CProMoElementAuto* CProMoElementsAuto::GetElementAutoObject(CProMoModel* pModel)
{
	if (pModel) {
		return dynamic_cast<CProMoElementAuto*>(pModel->GetAutomationObject());
	}
	return NULL;
}

CProMoElementsAuto::~CProMoElementsAuto()
{
}


BEGIN_MESSAGE_MAP(CProMoElementsAuto, CProMoDiagramChildAuto)
	//{{AFX_MSG_MAP(CProMoElementsAuto)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

BEGIN_DISPATCH_MAP(CProMoElementsAuto, CProMoDiagramChildAuto)
	//{{AFX_DISPATCH_MAP(CProMoElementsAuto)
	DISP_PROPERTY_EX(CProMoElementsAuto, "IDs", GetIDs, SetIDs, VT_VARIANT)
	DISP_FUNCTION(CProMoElementsAuto, "Count", Count, VT_I2, VTS_NONE)
	DISP_FUNCTION(CProMoElementsAuto, "Add", Add, VT_DISPATCH, VTS_VARIANT)
	DISP_FUNCTION(CProMoElementsAuto, "Remove", Remove, VT_BOOL, VTS_VARIANT)
	DISP_PROPERTY_PARAM(CProMoElementsAuto, "Item", GetItem, SetItem, VT_DISPATCH, VTS_VARIANT)
	DISP_DEFVALUE(CProMoElementsAuto, "Item")
	//}}AFX_DISPATCH_MAP
END_DISPATCH_MAP()

// Note: we add support for IID_IProMoElementsAuto to support typesafe binding
//  from VBA.  This IID must match the GUID that is attached to the 
//  dispinterface in the .ODL file.

// {7E3C6CD4-01D3-11F1-9743-000C2976A615}
static const IID IID_IProMoElementsAuto =
{ 0x7e3c6cd4, 0x1d3, 0x11f1, { 0x97, 0x43, 0x0, 0xc, 0x29, 0x76, 0xa6, 0x15 } };

BEGIN_INTERFACE_MAP(CProMoElementsAuto, CProMoDiagramChildAuto)
	INTERFACE_PART(CProMoElementsAuto, IID_IProMoElementsAuto, Dispatch)
END_INTERFACE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CProMoElementsAuto message handlers

short CProMoElementsAuto::Count() 
{
	if (GetContainer()) {
		CObArray models;
		GetContainer()->GetModels(models);
		return (short)models.GetSize();
	}

	return 0;
}

LPDISPATCH CProMoElementsAuto::GetItem(const VARIANT FAR& Item) 
{
	CVariantWrapper wrapper(Item);

	if (GetContainer()) {
		CObArray models;
		CProMoModel* pModel = NULL;
		GetContainer()->GetModels(models);
		if (wrapper.GetType() != VT_BSTR) {
			if (wrapper.GetInt() >= 0 && wrapper.GetInt() < models.GetSize()) {
				pModel = dynamic_cast<CProMoModel*>(models.GetAt(wrapper.GetInt()));
			}
		}
		else {
			pModel = dynamic_cast<CProMoModel*>(GetContainer()->GetNamedModel(models, wrapper.GetString()));
		}

		if (pModel) {
			CProMoElementAuto* pElementAuto = GetElementAutoObject(pModel);
			if (pElementAuto) {
				pElementAuto->SetDiagramAutoObject(GetDiagramAutoObject());
				return pElementAuto->GetIDispatch(TRUE);
			}
		}
	}

	return NULL;
}

void CProMoElementsAuto::SetItem(const VARIANT FAR& Item, LPDISPATCH newValue) 
{
	SetNotSupported();

}

LPDISPATCH CProMoElementsAuto::Add(const VARIANT FAR& elementType) 
{
	CVariantWrapper wrapper(elementType);
	CString strType = wrapper.GetString();

	CProMoEntityContainer* pContainer = GetContainer();
	if (pContainer) {

		CProMoControlFactory* pFactory = pContainer->GetControlFactory();
		if (pFactory) {
			CDiagramEntity* element = pFactory->CreateNewEntity(strType);
			if (element) {
				element->SetRect(0, 0, 1, 1); // force minimum size so that element will be visible when added to diagram
				IProMoEntity* promoEntity = dynamic_cast<IProMoEntity*>(element);
				if (promoEntity) {
					GetContainer()->Snapshot();
					pContainer->Add(element);
					CProMoModel* pModel = promoEntity->GetModel();
					if (pModel) {
						pModel->RecreateLabels(CObArray());
						GetContainer()->SetModified(TRUE);
						RefreshViews();
						CProMoElementAuto* pElementAuto = GetElementAutoObject(pModel);
						if (pElementAuto) {
							pElementAuto->SetDiagramAutoObject(GetDiagramAutoObject());
							return pElementAuto->GetIDispatch(TRUE);
						}
					}
					else {
						
						pContainer->Remove(element);
					}
				}
				else {
					// should not happen, but just in case
					delete element;
				}
			}
		}
	}

	return NULL;
}

BOOL CProMoElementsAuto::Remove(const VARIANT FAR& Item) 
{
	// TODO: Add your dispatch handler code here

	return TRUE;
}

VARIANT CProMoElementsAuto::GetIDs() 
{
	VARIANT vaResult;
	VariantInit(&vaResult);

	if (GetContainer()) {

		CStringArray names;
		CObArray elements;
		CProMoModel* pModel = NULL;
		GetContainer()->GetModels(elements);
		for (int i = 0; i < elements.GetSize(); i++) {
			pModel = dynamic_cast<CProMoModel*>(elements.GetAt(i));
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

void CProMoElementsAuto::SetIDs(const VARIANT FAR& newValue) 
{
	SetNotSupported();

}
