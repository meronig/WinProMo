/* ==========================================================================

	Copyright © 2026 Technical University of Denmark

	CProMoAppChildAuto

	Author :		Giovanni Meroni

	Purpose :		"CProMoAppChildAuto" is an automation object that represents 
					a child object of the application. 

	Description :	"CProMoAppChildAuto" is used to provide 
					access to the application automation object and to manage 
					the lifetime of the automation objects.

	Usage :			Derived classes should use the "Initialize" method to set 
					the internal automation host object, which is used to manage
					the lifetime of the automation objects. The "Detach" method 
					can be used to detach the automation object from the host, 
					which will release the reference to the automation object and
					allow it to be destroyed when all references are released. The 
					"IsAlive" method can be used to check if the automation object 
					is still attached to a host, and the "RefreshViews" method 
					can be used to refresh any views that are associated with the 
					automation object.

   ========================================================================*/
#include "stdafx.h"
#include "ProMoAppChildAuto.h"
#include "ProMoAppAutoAbs.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CProMoAppChildAuto

IMPLEMENT_DYNCREATE(CProMoAppChildAuto, CCmdTarget)

CProMoAppChildAuto::CProMoAppChildAuto()
{
	EnableAutomation();
	m_pInternalObject = NULL;
	m_pAppAuto = NULL;
}

CProMoAppChildAuto::~CProMoAppChildAuto()
{
}

void CProMoAppChildAuto::DetachInternalObject()
{
	if (m_pInternalObject) {
		IProMoAutomationHost* host = m_pInternalObject;
		m_pInternalObject = NULL;
		host->ReleaseAutomationObject();
	}
}

void CProMoAppChildAuto::OnFinalRelease()
{
	// When the last reference for an automation object is released
	// OnFinalRelease is called.  The base class will automatically
	// deletes the object.  Add additional cleanup required for your
	// object before calling the base class.

	DetachInternalObject();
	SetAppAutoObject(NULL);
	CCmdTarget::OnFinalRelease();
}

BOOL CProMoAppChildAuto::IsAlive() const
{
	return m_pInternalObject != NULL;
}

void CProMoAppChildAuto::Initialize(IProMoAutomationHost* obj)
{
	m_pInternalObject = obj;
}

void CProMoAppChildAuto::Detach()
{
	if (m_pInternalObject) {
		DetachInternalObject();
		GetIDispatch(FALSE)->Release();
	}
}

void CProMoAppChildAuto::ThrowIfDetached() const
{
	if (!m_pInternalObject) {
		//TODO: consider a more specific error code and message
		AfxThrowOleException(E_FAIL);
	}
}

void CProMoAppChildAuto::ThrowIfNoAppAutoObject() const
{
	if (!m_pAppAuto) {
		//TODO: consider a more specific error code and message
		AfxThrowOleException(E_FAIL);
	}
}

void CProMoAppChildAuto::SetAppAutoObject(CProMoAppAutoAbs* pAppAuto)
{
	if (m_pAppAuto == pAppAuto) {
		return;
	}
	CProMoAppAutoAbs* oldAppAuto = m_pAppAuto;
	m_pAppAuto = pAppAuto;

	if (oldAppAuto) {
		oldAppAuto->GetIDispatch(FALSE)->Release();
	}
	if (m_pAppAuto) {
		m_pAppAuto->GetIDispatch(FALSE)->AddRef();
	}
}

CProMoAppAutoAbs* CProMoAppChildAuto::GetAppAutoObject() const
{
	return m_pAppAuto;
}

BEGIN_MESSAGE_MAP(CProMoAppChildAuto, CCmdTarget)
	//{{AFX_MSG_MAP(CProMoAppChildAuto)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

BEGIN_DISPATCH_MAP(CProMoAppChildAuto, CCmdTarget)
	//{{AFX_DISPATCH_MAP(CProMoAppChildAuto)
	//}}AFX_DISPATCH_MAP
END_DISPATCH_MAP()

BEGIN_INTERFACE_MAP(CProMoAppChildAuto, CCmdTarget)
END_INTERFACE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CProMoAppChildAuto message handlers

LPDISPATCH CProMoAppChildAuto::Application()
{
	if (m_pAppAuto) {
		return m_pAppAuto->GetIDispatch(TRUE);
	}
	return NULL;
}

