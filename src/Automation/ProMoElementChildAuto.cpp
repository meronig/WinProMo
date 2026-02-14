/* ==========================================================================

	Copyright © 2026 Technical University of Denmark

	CProMoElementChildAuto

	Author :		Giovanni Meroni

	Purpose :		"CProMoElementChildAuto" is an automation object that
					represents a child object of a diagram element.

	Description :	"CProMoDiagramChildAuto" is used to provide access to the
					element automation object and to manage	the lifetime of the
					automation objects. By extending "CProMoDiagramChildAuto", it
					provides access to the diagram.

	Usage :			Derived classes should use the "SetElementAutoObject" method
					to set the element automation object, which is used to manage
					the lifetime of the automation objects. The "GetModel" method
					can be used to get the model of the element, and the "Element"
					method can be used to get the element automation object. The
					"ThrowIfNoElementAutoObject" method can be used to check if
					the element automation object is set, and throw an exception
					if it is not.

   ========================================================================*/
#include "stdafx.h"
#include "ProMoElementChildAuto.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CProMoElementChildAuto

IMPLEMENT_DYNCREATE(CProMoElementChildAuto, CProMoDiagramChildAuto)

CProMoElementChildAuto::CProMoElementChildAuto()
{
	m_pElementAuto = NULL;
}

void CProMoElementChildAuto::OnFinalRelease()
{
	// When the last reference for an automation object is released
	// OnFinalRelease is called.  The base class will automatically
	// deletes the object.  Add additional cleanup required for your
	// object before calling the base class.

	SetElementAutoObject(NULL);
	CProMoDiagramChildAuto::OnFinalRelease();
}

CProMoModel* CProMoElementChildAuto::GetModel()
{
	if (m_pElementAuto) {
		return m_pElementAuto->GetModel();
	}
	return NULL;
}

CProMoElementAuto* CProMoElementChildAuto::GetElementAutoObject() const
{
	return m_pElementAuto;
}

void CProMoElementChildAuto::SetElementAutoObject(CProMoElementAuto* pElementAuto)
{
	SetDiagramAutoObject(pElementAuto ? pElementAuto->GetDiagramAutoObject() : NULL);
	
	if (m_pElementAuto == pElementAuto) {
		return;
	}
	CProMoElementAuto* oldElementAuto = m_pElementAuto;
	m_pElementAuto = pElementAuto;

	if (oldElementAuto) {
		oldElementAuto->GetIDispatch(FALSE)->Release();
	}
	if (m_pElementAuto) {
		m_pElementAuto->GetIDispatch(FALSE)->AddRef();
	}
}

void CProMoElementChildAuto::ThrowIfNoElementAutoObject() const
{
	ThrowIfNoDiagramAutoObject();
	if (!m_pElementAuto) {
		//TODO: consider a more specific error code and message
		AfxThrowOleException(E_FAIL);
	}
}

CProMoElementChildAuto::~CProMoElementChildAuto()
{
}

BEGIN_MESSAGE_MAP(CProMoElementChildAuto, CProMoDiagramChildAuto)
	//{{AFX_MSG_MAP(CProMoElementChildAuto)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

BEGIN_DISPATCH_MAP(CProMoElementChildAuto, CProMoDiagramChildAuto)
	//{{AFX_DISPATCH_MAP(CProMoElementChildAuto)
	DISP_FUNCTION(CProMoElementChildAuto, "Element", Element, VT_DISPATCH, VTS_NONE)
	//}}AFX_DISPATCH_MAP
END_DISPATCH_MAP()

// Note: we add support for IID_IProMoElementChildAuto to support typesafe binding
//  from VBA.  This IID must match the GUID that is attached to the 
//  dispinterface in the .ODL file.

// {18EA3777-08C3-11F1-9744-000C2976A615}
static const IID IID_IProMoElementChildAuto =
{ 0x18ea3777, 0x8c3, 0x11f1, { 0x97, 0x44, 0x0, 0xc, 0x29, 0x76, 0xa6, 0x15 } };

BEGIN_INTERFACE_MAP(CProMoElementChildAuto, CProMoDiagramChildAuto)
	INTERFACE_PART(CProMoElementChildAuto, IID_IProMoElementChildAuto, Dispatch)
END_INTERFACE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CProMoElementChildAuto message handlers

LPDISPATCH CProMoElementChildAuto::Element() 
{
	if (m_pElementAuto) {
		return m_pElementAuto->GetIDispatch(TRUE);
	}

	return NULL;
}
