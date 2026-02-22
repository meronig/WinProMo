// DummyClass.cpp : implementation file
//

#include "stdafx.h"
#include "	\ add additional includes here"
#include "DummyClass.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// DummyClass

IMPLEMENT_DYNCREATE(DummyClass, CCmdTarget)

DummyClass::DummyClass()
{
	EnableAutomation();
}

DummyClass::~DummyClass()
{
}


void DummyClass::OnFinalRelease()
{
	// When the last reference for an automation object is released
	// OnFinalRelease is called.  The base class will automatically
	// deletes the object.  Add additional cleanup required for your
	// object before calling the base class.

	CCmdTarget::OnFinalRelease();
}


BEGIN_MESSAGE_MAP(DummyClass, CCmdTarget)
	//{{AFX_MSG_MAP(DummyClass)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

BEGIN_DISPATCH_MAP(DummyClass, CCmdTarget)
	//{{AFX_DISPATCH_MAP(DummyClass)
	DISP_PROPERTY_EX(DummyClass, "Prop", GetProp, SetProp, VT_BOOL)
	DISP_FUNCTION(DummyClass, "Method", Method, VT_DISPATCH, VTS_I2 VTS_VARIANT)
	DISP_FUNCTION(DummyClass, "Method2", Method2, VT_COLOR, VTS_NONE)
	DISP_FUNCTION(DummyClass, "Method3", Method3, VT_UNKNOWN, VTS_NONE)
	DISP_PROPERTY_PARAM(DummyClass, "PropIdx", GetPropIdx, SetPropIdx, VT_R8, VTS_I2)
	DISP_PROPERTY_PARAM(DummyClass, "PropDisp", GetPropDisp, SetPropDisp, VT_DISPATCH, VTS_VARIANT)
	//}}AFX_DISPATCH_MAP
END_DISPATCH_MAP()

// Note: we add support for IID_IDummyClass to support typesafe binding
//  from VBA.  This IID must match the GUID that is attached to the 
//  dispinterface in the .ODL file.

// {F639BFAD-1001-11F1-9746-000C2976A615}
static const IID IID_IDummyClass =
{ 0xf639bfad, 0x1001, 0x11f1, { 0x97, 0x46, 0x0, 0xc, 0x29, 0x76, 0xa6, 0x15 } };

BEGIN_INTERFACE_MAP(DummyClass, CCmdTarget)
	INTERFACE_PART(DummyClass, IID_IDummyClass, Dispatch)
END_INTERFACE_MAP()

/////////////////////////////////////////////////////////////////////////////
// DummyClass message handlers

LPDISPATCH DummyClass::Method(short foo, const VARIANT FAR& bar) 
{
	// TODO: Add your dispatch handler code here

	return NULL;
}

BOOL DummyClass::GetProp() 
{
	// TODO: Add your property handler here

	return TRUE;
}

void DummyClass::SetProp(BOOL bNewValue) 
{
	// TODO: Add your property handler here

}

double DummyClass::GetPropIdx(short param) 
{
	// TODO: Add your property handler here

	return 0.0;
}

void DummyClass::SetPropIdx(short param, double newValue) 
{
	// TODO: Add your property handler here

}

LPDISPATCH DummyClass::GetPropDisp(const VARIANT FAR& idx) 
{
	// TODO: Add your property handler here

	return NULL;
}

void DummyClass::SetPropDisp(const VARIANT FAR& idx, LPDISPATCH newValue) 
{
	// TODO: Add your property handler here

}

OLE_COLOR DummyClass::Method2() 
{
	// TODO: Add your dispatch handler code here

	return RGB(0,0,0);
}

LPUNKNOWN DummyClass::Method3() 
{
	// TODO: Add your dispatch handler code here

	return NULL;
}
