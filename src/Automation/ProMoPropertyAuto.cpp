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
	// TODO: Add your property handler here

	return strResult.AllocSysString();
}

void CProMoPropertyAuto::SetName(LPCTSTR lpszNewValue) 
{
	// TODO: Add your property handler here

}

BOOL CProMoPropertyAuto::IsReadOnly() 
{
	// TODO: Add your dispatch handler code here

	return TRUE;
}

long CProMoPropertyAuto::GetType() 
{
	// TODO: Add your property handler here

	return 0;
}

void CProMoPropertyAuto::SetType(long nNewValue) 
{
	// TODO: Add your property handler here

}

LPDISPATCH CProMoPropertyAuto::Label() 
{
	// TODO: Add your dispatch handler code here

	return NULL;
}

BOOL CProMoPropertyAuto::IsComposite() 
{
	// TODO: Add your dispatch handler code here

	return TRUE;
}

BOOL CProMoPropertyAuto::IsMultivalue() 
{
	// TODO: Add your dispatch handler code here

	return TRUE;
}

VARIANT CProMoPropertyAuto::GetValue() 
{
	VARIANT vaResult;
	VariantInit(&vaResult);
	// TODO: Add your property handler here

	return vaResult;
}

void CProMoPropertyAuto::SetValue(const VARIANT FAR& newValue) 
{
	// TODO: Add your property handler here

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
	// TODO: Add your property handler here

	return NULL;
}

void CProMoPropertyAuto::SetItem(const VARIANT FAR& Item, LPDISPATCH newValue) 
{
	// TODO: Add your property handler here

}

long CProMoPropertyAuto::Count() 
{
	// TODO: Add your dispatch handler code here

	return 0;
}

VARIANT CProMoPropertyAuto::GetChildNames() 
{
	VARIANT vaResult;
	VariantInit(&vaResult);
	// TODO: Add your property handler here

	return vaResult;
}

void CProMoPropertyAuto::SetChildNames(const VARIANT FAR& newValue) 
{
	// TODO: Add your property handler here

}
