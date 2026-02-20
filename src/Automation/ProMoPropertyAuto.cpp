/* ==========================================================================

	Copyright © 2026 Technical University of Denmark

	CProMoPropertyAuto

	Author :		Giovanni Meroni

	Purpose :		"CProMoPropertyAuto" is an automation object that
					represents a property of a diagram element. It provides 
					methods to access the name, the type, and the value of 
					the property (if single-value simple), to get the names 
					of the child properties (if composite), to add and remove
					values (if multivalue), to access the label associated with 
					the property (if any), and to check whether the property 
					is read-only.

	Description :	"CProMoPropertyAuto" provides the implementation of the
					methods and properties that are common to all properties.

   ========================================================================*/
#include "stdafx.h"
#include "ProMoPropertyAuto.h"
#include "../FileUtils/SafeArrayWrapper.h"
#include "ProMoLabelAuto.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CProMoPropertyAuto

IMPLEMENT_DYNCREATE(CProMoPropertyAuto, CProMoElementChildAuto)

CProMoPropertyAuto::CProMoPropertyAuto()
{
}

CProMoProperty* CProMoPropertyAuto::GetProperty() {
	ThrowIfDetached();
	ThrowIfNoElementAutoObject();

	return dynamic_cast<CProMoProperty*>(m_pInternalObject);
}

CProMoPropertyAuto::~CProMoPropertyAuto()
{
}


BEGIN_MESSAGE_MAP(CProMoPropertyAuto, CProMoElementChildAuto)
	//{{AFX_MSG_MAP(CProMoPropertyAuto)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

BEGIN_DISPATCH_MAP(CProMoPropertyAuto, CProMoElementChildAuto)
	//{{AFX_DISPATCH_MAP(CProMoPropertyAuto)
	DISP_PROPERTY_EX(CProMoPropertyAuto, "Name", GetName, SetName, VT_BSTR)
	DISP_PROPERTY_EX(CProMoPropertyAuto, "Type", GetType, SetType, VT_I4)
	DISP_PROPERTY_EX(CProMoPropertyAuto, "Value", GetValue, SetValue, VT_VARIANT)
	DISP_PROPERTY_EX(CProMoPropertyAuto, "ChildNames", GetChildNames, SetChildNames, VT_VARIANT)
	DISP_FUNCTION(CProMoPropertyAuto, "IsReadOnly", IsReadOnly, VT_BOOL, VTS_NONE)
	DISP_FUNCTION(CProMoPropertyAuto, "Label", Label, VT_DISPATCH, VTS_NONE)
	DISP_FUNCTION(CProMoPropertyAuto, "IsComposite", IsComposite, VT_BOOL, VTS_NONE)
	DISP_FUNCTION(CProMoPropertyAuto, "IsMultivalue", IsMultivalue, VT_BOOL, VTS_NONE)
	DISP_FUNCTION(CProMoPropertyAuto, "Add", Add, VT_BOOL, VTS_NONE)
	DISP_FUNCTION(CProMoPropertyAuto, "Remove", Remove, VT_BOOL, VTS_NONE)
	DISP_FUNCTION(CProMoPropertyAuto, "Count", Count, VT_I4, VTS_NONE)
	DISP_PROPERTY_PARAM(CProMoPropertyAuto, "Item", GetItem, SetItem, VT_DISPATCH, VTS_VARIANT)
	DISP_DEFVALUE(CProMoPropertyAuto, "Item")
	//}}AFX_DISPATCH_MAP
END_DISPATCH_MAP()

// Note: we add support for IID_IProMoPropertyAuto to support typesafe binding
//  from VBA.  This IID must match the GUID that is attached to the 
//  dispinterface in the .ODL file.

// {18EA3773-08C3-11F1-9744-000C2976A615}
static const IID IID_IProMoPropertyAuto =
{ 0x18ea3773, 0x8c3, 0x11f1, { 0x97, 0x44, 0x0, 0xc, 0x29, 0x76, 0xa6, 0x15 } };

BEGIN_INTERFACE_MAP(CProMoPropertyAuto, CProMoElementChildAuto)
	INTERFACE_PART(CProMoPropertyAuto, IID_IProMoPropertyAuto, Dispatch)
END_INTERFACE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CProMoPropertyAuto message handlers

BSTR CProMoPropertyAuto::GetName() 
{
	CString strResult;
	
	if (GetProperty()) {
		strResult = GetProperty()->GetName();
	}

	return strResult.AllocSysString();
}

void CProMoPropertyAuto::SetName(LPCTSTR lpszNewValue) 
{
	SetNotSupported();

}

BOOL CProMoPropertyAuto::IsReadOnly() 
{
	if (GetProperty()) {
		return GetProperty()->IsReadOnly();
	}

	return TRUE;
}

long CProMoPropertyAuto::GetType() 
{
	if (GetProperty()) {
		return GetProperty()->GetType();
	}

	return 0;
}

void CProMoPropertyAuto::SetType(long nNewValue) 
{
	SetNotSupported();

}

LPDISPATCH CProMoPropertyAuto::Label() 
{
	if (GetProperty() && GetModel()) {
		CObArray labels;
		GetModel()->GetLabels(labels);
		for (int i = 0; i < labels.GetCount(); i++) {
			CProMoLabel* label = dynamic_cast<CProMoLabel*>(labels.GetAt(i));
			if (label) {
				if (label->GetProperty() == GetProperty()) {
					CProMoLabelAuto* labelAuto = dynamic_cast<CProMoLabelAuto*>(label->GetAutomationObject());
					if (labelAuto) {
						labelAuto->SetElementAutoObject(GetElementAutoObject());
						return labelAuto->GetIDispatch(TRUE);
					}
				}
			}
		}
	}

	return NULL;
}

BOOL CProMoPropertyAuto::IsComposite() 
{
	if (GetProperty()) {
		return GetProperty()->IsComposite();
	}

	return TRUE;
}

BOOL CProMoPropertyAuto::IsMultivalue() 
{
	if (GetProperty()) {
		return GetProperty()->IsMultiValue();
	}

	return TRUE;
}

VARIANT CProMoPropertyAuto::GetValue() 
{
	VARIANT vaResult;
	VariantInit(&vaResult);
	
	if (GetProperty()) {
		if (IsMultivalue() || IsComposite()) {
			GetNotSupported();
		}
		else {
			CVariantWrapper varWrapper = GetProperty()->GetValue();
			VariantCopy(&vaResult, varWrapper.GetVARIANT());
		}
	}

	return vaResult;
}

void CProMoPropertyAuto::SetValue(const VARIANT FAR& newValue) 
{
	if (GetProperty()) {
		if (IsMultivalue() || IsComposite()) {
			SetNotSupported();
			return;
		}
		CVariantWrapper varWrapper(newValue);
		GetProperty()->SetValue(varWrapper);
	}

}

BOOL CProMoPropertyAuto::Add() 
{
	// TODO: Add your dispatch handler code here

	return TRUE;
}

BOOL CProMoPropertyAuto::Remove() 
{
	// TODO: Add your dispatch handler code here

	return TRUE;
}

LPDISPATCH CProMoPropertyAuto::GetItem(const VARIANT FAR& Item) 
{
	if (!IsMultivalue() && !IsComposite()) {
		GetNotSupported();
		return NULL;
	}

	if (GetProperty()) {
		CVariantWrapper wrapper(Item);
		CProMoProperty* childProperty = NULL;
		if (wrapper.GetType() != VT_BSTR) {
			childProperty = GetProperty()->GetChild(wrapper.GetInt());
		}
		else {
			if (IsMultivalue()) {
				GetNotSupported();
				return NULL;
			}
			else
			childProperty = GetProperty()->FindChild(wrapper.GetString());
		}

		if (childProperty) {
			CProMoPropertyAuto* childPropertyAuto = dynamic_cast<CProMoPropertyAuto*>(childProperty->GetAutomationObject());
			if (childPropertyAuto) {
				childPropertyAuto->SetElementAutoObject(GetElementAutoObject());
				return childPropertyAuto->GetIDispatch(TRUE);
			}
		}
	}
	

	return NULL;
}

void CProMoPropertyAuto::SetItem(const VARIANT FAR& Item, LPDISPATCH newValue) 
{
	SetNotSupported();

}

long CProMoPropertyAuto::Count() 
{
	if (GetProperty()) {
		return GetProperty()->GetChildrenCount();
	}

	return 0;
}

VARIANT CProMoPropertyAuto::GetChildNames() 
{
	VARIANT vaResult;
	VariantInit(&vaResult);
	
	CStringArray names;

	if (GetProperty()) {
		GetProperty()->GetChildrenNames(names, FALSE);
	}

	HRESULT hr = CSafeArrayWrapper::CreateVariantFromCStringArray(names, vaResult);
	if (FAILED(hr))
		AfxThrowOleException(hr);

	return vaResult;
}

void CProMoPropertyAuto::SetChildNames(const VARIANT FAR& newValue) 
{
	SetNotSupported();

}
