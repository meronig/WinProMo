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
/* ============================================================
	Function :		CProMoElementsAuto::CProMoElementsAuto
	Description :	Constructor
	Access :		Public

	Return :		void
	Parameters :	none
   ============================================================ */
{
}

CProMoElementAuto* CProMoElementsAuto::GetElementAutoObject(CProMoModel* pModel)
/* ============================================================
	Function :		CProMoElementsAuto::GetElementAutoObject
	Description :	Get the automation object for the given model
	Access :		Protected

	Return :		CProMoElementAuto*	-	the automation object 
											for the given model
	Parameters :	CProMoModel* pModel	-	the model for which
											to get the automation
											object
   ============================================================ */
{
	if (pModel) {
		return dynamic_cast<CProMoElementAuto*>(pModel->GetAutomationObject());
	}
	return NULL;
}

CProMoElementsAuto::~CProMoElementsAuto()
/* ============================================================
	Function :		CProMoElementsAuto::~CProMoElementsAuto
	Description :	Destructor
	Access :		Public

	Return :		void
	Parameters :	none
   ============================================================ */
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
	//Common to CProMoDiagramChildAuto
	DISP_FUNCTION(CProMoDiagramChildAuto, "Diagram", Diagram, VT_DISPATCH, VTS_NONE)
	//Common to CProMoAppChildAuto
	DISP_FUNCTION(CProMoAppChildAuto, "Application", Application, VT_DISPATCH, VTS_NONE)
	//Default property
	DISP_PROPERTY_PARAM(CProMoElementsAuto, "Item", GetItem, SetItem, VT_DISPATCH, VTS_VARIANT)
	DISP_DEFVALUE(CProMoElementsAuto, "Item")
	//}}AFX_DISPATCH_MAP
END_DISPATCH_MAP()

// Note: we add support for IID_IProMoElementsAuto to support typesafe binding
//  from VBA.  This IID must match the GUID that is attached to the 
//  dispinterface in the .ODL file.

// {38EA3765-01D3-11F1-9743-000C2976A615}
static const IID IID_IProMoElementsAuto =
{ 0x38ea3765, 0x1d3, 0x11f1, { 0x97, 0x43, 0x0, 0xc, 0x29, 0x76, 0xa6, 0x15 } };

BEGIN_INTERFACE_MAP(CProMoElementsAuto, CProMoDiagramChildAuto)
	INTERFACE_PART(CProMoElementsAuto, IID_IProMoElementsAuto, Dispatch)
END_INTERFACE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CProMoElementsAuto message handlers

short CProMoElementsAuto::Count()
/* ============================================================
	Function :		CProMoElementsAuto::Count
	Description :	Returns the number of elements in the diagram.
	Access :		Public
	Return :		short	-	the number of elements in the diagram
	Parameters :	none
   ============================================================ */
{
	if (GetContainer()) {
		CObArray models;
		GetContainer()->GetModels(models);
		return (short)models.GetSize();
	}

	return 0;
}

LPDISPATCH CProMoElementsAuto::GetItem(const VARIANT FAR& item)
/* ============================================================
	Function :		CProMoElementsAuto::GetItem
	Description :	Returns the element specified by the given index or name.
	Access :		Public

	Return :		LPDISPATCH		-	the automation object for the 
										element specified by the given 
										index or name, or NULL if no 
										such element exists.
	Parameters :	VARIANT& item 	-	the index or name of the 
										element to return.
   ============================================================ */
{
	if (GetContainer()) {
		CObArray models;
		GetContainer()->GetModels(models);
		CProMoModel* pModel = FindModel(item, models);
	
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
/* ============================================================
	Function :		CProMoElementsAuto::SetItem
	Description :	Sets the element specified by the given index or name.
					This property is read-only, so this function 
					simply raises an exception.
	Access :		Public
	Return :		void
	Parameters :	VARIANT& Item		-	the index or name of the 
											element to set.
					LPDISPATCH newValue -	the new value for the element
   ============================================================ */
{
	SetNotSupported();

}

LPDISPATCH CProMoElementsAuto::Add(const VARIANT FAR& elementType)
/* ============================================================
	Function :		CProMoElementsAuto::Add
	Description :	Creates a new element of the specified type and 
					adds it to the diagram.
	Access :		Public
	Return :		LPDISPATCH				-	the automation object 
												for the newly created 
												element, or NULL if 
												the element could not 
												be created.
	Parameters :	VARIANT& elementType	-	the type of element to
												create, specified as 
												a string. The specific
												element types that are 
												creatable depend on 
												the specific application 
												and diagram type, and 
												are determined by the 
												container of the diagram.
   ============================================================ */
{
	CVariantWrapper wrapper(elementType);
	CString strType = wrapper.GetString();

	CProMoEntityContainer* pContainer = GetContainer();
	if (pContainer) {

		CProMoControlFactory* pFactory = pContainer->GetControlFactory();
		if (pFactory) {
			CDiagramEntity* element = pFactory->CreateNewEntity(strType);
			if (element) {
				element->SetRect(10, 10, 30, 30); // force minimum size so that element will be visible when added to diagram
				IProMoEntity* promoEntity = dynamic_cast<IProMoEntity*>(element);
				if (promoEntity) {
					GetContainer()->Snapshot();
					pContainer->Add(element);
					CProMoModel* pModel = promoEntity->GetModel();
					if (pModel) {
						pModel->RecreateLabels(CObArray());
						GetDiagramAutoObject()->NotifyChange();
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

BOOL CProMoElementsAuto::Remove(const VARIANT FAR& item) 
/* ============================================================
	Function :		CProMoElementsAuto::Remove
	Description :	Removes the element specified by the given 
					index or name from the diagram.
	Access :		Public

	Return :		BOOL			-	"TRUE" if the element 
										was successfully removed, 
										or "FALSE" if no such 
										element exists.
	Parameters :	VARIANT& item 	-	the index or name of the 
										element to remove.
   ============================================================ */
{
	if (GetContainer()) {
		CObArray models;
		GetContainer()->GetModels(models);
		CProMoModel* pModel = FindModel(item, models);
		if (pModel) {
			CProMoElementAuto* pElementAuto = GetElementAutoObject(pModel);
			pElementAuto->DeleteViewsAndLabels();
			return TRUE;
		}
	}

	return FALSE;
}

VARIANT CProMoElementsAuto::GetIDs() 
/* ============================================================
	Function :		CProMoElementsAuto::GetIDs
	Description :	Returns an array containing the names of all 
					elements in the diagram.
	Access :		Public
	Return :		VARIANT	-	a SAFEARRAY of strings containing 
								the names of all elements in the 
								diagram. If there are no elements, 
								an empty SAFEARRAY is returned.
	Parameters :	none
   ============================================================ */
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
/* ============================================================
	Function :		CProMoElementsAuto::SetIDs
	Description :	Sets the names of all elements in the diagram.
					This property is read-only, so this function 
					simply raises an exception.
	Access :		Public
	Return :		void
	Parameters :	VARIANT& newValue -	a SAFEARRAY of strings containing 
										the new names for all elements 
										in the diagram (not supported).
   ============================================================ */
{
	SetNotSupported();

}
