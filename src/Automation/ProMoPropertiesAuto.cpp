/* ==========================================================================

	Copyright © 2026 Technical University of Denmark

	CProMoPropertiesAuto

	Author :		Giovanni Meroni

	Purpose :		"CProMoPropertiesAuto" is an automation object that
					represents the collection of properties of a diagram
					element. It provides methods to access the properties.

	Description :	"CProMoPropertiesAuto" provides the implementation
					of the methods and properties that are common to all
					element properties collections.

   ========================================================================*/
#include "stdafx.h"
#include "ProMoPropertiesAuto.h"
#include "../FileUtils/SafeArrayWrapper.h"
#include "ProMoPropertyAuto.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CProMoPropertiesAuto

IMPLEMENT_DYNCREATE(CProMoPropertiesAuto, CProMoElementChildAuto)

CProMoPropertiesAuto::CProMoPropertiesAuto()
{
}

CProMoPropertiesAuto::~CProMoPropertiesAuto()
{
}

void CProMoPropertiesAuto::SetElementAutoObject(CProMoElementAuto* pElementAuto) {
	SetDiagramAutoObject(pElementAuto ? pElementAuto->GetDiagramAutoObject() : NULL);
	m_pElementAuto = pElementAuto;
}

BEGIN_MESSAGE_MAP(CProMoPropertiesAuto, CProMoElementChildAuto)
	//{{AFX_MSG_MAP(CProMoPropertiesAuto)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

BEGIN_DISPATCH_MAP(CProMoPropertiesAuto, CProMoElementChildAuto)
	//{{AFX_DISPATCH_MAP(CProMoPropertiesAuto)
	DISP_PROPERTY_EX(CProMoPropertiesAuto, "Names", GetNames, SetNames, VT_VARIANT)
	DISP_FUNCTION(CProMoPropertiesAuto, "Count", Count, VT_I2, VTS_NONE)
	DISP_PROPERTY_PARAM(CProMoPropertiesAuto, "Item", GetItem, SetItem, VT_DISPATCH, VTS_VARIANT)
	DISP_DEFVALUE(CProMoPropertiesAuto, "Item")
	//Common to CProMoElementChildAuto
	DISP_FUNCTION(CProMoPropertiesAuto, "Element", Element, VT_DISPATCH, VTS_NONE)
	//Common to CProMoDiagramChildAuto
	DISP_FUNCTION(CProMoPropertiesAuto, "Diagram", Diagram, VT_DISPATCH, VTS_NONE)
	//Common to CProMoAppChildAuto
	DISP_FUNCTION(CProMoPropertiesAuto, "Application", Application, VT_DISPATCH, VTS_NONE)
	//}}AFX_DISPATCH_MAP
END_DISPATCH_MAP()

// Note: we add support for IID_IProMoPropertiesAuto to support typesafe binding
//  from VBA.  This IID must match the GUID that is attached to the 
//  dispinterface in the .ODL file.

// {38EA376A-08C3-11F1-9744-000C2976A615}
static const IID IID_IProMoPropertiesAuto =
{ 0x38ea376A, 0x8c3, 0x11f1, { 0x97, 0x44, 0x0, 0xc, 0x29, 0x76, 0xa6, 0x15 } };

BEGIN_INTERFACE_MAP(CProMoPropertiesAuto, CProMoElementChildAuto)
	INTERFACE_PART(CProMoPropertiesAuto, IID_IProMoPropertiesAuto, Dispatch)
END_INTERFACE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CProMoPropertiesAuto message handlers

short CProMoPropertiesAuto::Count() 
{
	if (GetModel()) {
		return GetModel()->GetPropertiesCount();
	}

	return 0;
}

LPDISPATCH CProMoPropertiesAuto::GetItem(const VARIANT FAR& Item) 
{
	CVariantWrapper wrapper(Item);

	CProMoProperty* pProperty = NULL;
	
	if (GetModel()) {

		if (wrapper.GetType() != VT_BSTR) {
			pProperty = GetModel()->GetProperty(wrapper.GetInt());

		}
		else {
			pProperty = GetModel()->FindProperty(wrapper.GetString());
		}

		if (pProperty) {
			CProMoPropertyAuto* pElementAuto = dynamic_cast<CProMoPropertyAuto*>(pProperty->GetAutomationObject());
			if (pElementAuto) {
				pElementAuto->SetElementAutoObject(GetElementAutoObject());
				return pElementAuto->GetIDispatch(TRUE);
			}
		}
	}

	return NULL;
}

void CProMoPropertiesAuto::SetItem(const VARIANT FAR& Item, LPDISPATCH newValue) 
{
	SetNotSupported();

}

VARIANT CProMoPropertiesAuto::GetNames() 
{
	VARIANT vaResult;
	VariantInit(&vaResult);
	
	CStringArray names;

	if (GetModel()) {
		GetModel()->GetPropertyNames(names, FALSE);
	}

	HRESULT hr = CSafeArrayWrapper::CreateVariantFromCStringArray(names, vaResult);
	if (FAILED(hr))
		AfxThrowOleException(hr);

	return vaResult;
}

void CProMoPropertiesAuto::SetNames(const VARIANT FAR& newValue) 
{
	SetNotSupported();

}
