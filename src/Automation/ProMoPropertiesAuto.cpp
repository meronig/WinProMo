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
	DISP_FUNCTION(CProMoPropertiesAuto, "Count", Count, VT_I4, VTS_NONE)
	DISP_PROPERTY_PARAM(CProMoPropertiesAuto, "Item", GetItem, SetItem, VT_DISPATCH, VTS_VARIANT)
	DISP_DEFVALUE(CProMoPropertiesAuto, "Item")
	//}}AFX_DISPATCH_MAP
END_DISPATCH_MAP()

// Note: we add support for IID_IProMoPropertiesAuto to support typesafe binding
//  from VBA.  This IID must match the GUID that is attached to the 
//  dispinterface in the .ODL file.

// {18EA3772-08C3-11F1-9744-000C2976A615}
static const IID IID_IProMoPropertiesAuto =
{ 0x18ea3772, 0x8c3, 0x11f1, { 0x97, 0x44, 0x0, 0xc, 0x29, 0x76, 0xa6, 0x15 } };

BEGIN_INTERFACE_MAP(CProMoPropertiesAuto, CProMoElementChildAuto)
	INTERFACE_PART(CProMoPropertiesAuto, IID_IProMoPropertiesAuto, Dispatch)
END_INTERFACE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CProMoPropertiesAuto message handlers

long CProMoPropertiesAuto::Count() 
{
	// TODO: Add your dispatch handler code here

	return 0;
}

LPDISPATCH CProMoPropertiesAuto::GetItem(const VARIANT FAR& Item) 
{
	// TODO: Add your property handler here

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
	// TODO: Add your property handler here

	return vaResult;
}

void CProMoPropertiesAuto::SetNames(const VARIANT FAR& newValue) 
{
	SetNotSupported();

}
