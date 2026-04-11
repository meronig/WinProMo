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
/* ============================================================
	Function :		CProMoAppChildAuto::CProMoAppChildAuto
	Description :	Constructor
	Access :		Public

	Return :		void
	Parameters :	none
   ============================================================*/
{
	EnableAutomation();
	m_pInternalObject = NULL;
	m_pAppAuto = NULL;
}

CProMoAppChildAuto::~CProMoAppChildAuto()
/* ============================================================
	Function :		CProMoAppChildAuto::~CProMoAppChildAuto
	Description :	Destructor
	Access :		Public

	Return :		void
	Parameters :	none
   ============================================================*/
{
}

void CProMoAppChildAuto::DetachInternalObject()
/* ============================================================
	Function :		CProMoAppChildAuto::DetachInternalObject
	Description :	Detaches the internal automation host object, 
					if it exists, by calling the host's 
					ReleaseAutomationObject method and setting the 
					internal pointer to NULL.
	Access :		Protected

	Return :		void
	Parameters :	none
   ============================================================*/
{
	if (m_pInternalObject) {
		IProMoAutomationHost* host = m_pInternalObject;
		m_pInternalObject = NULL;
		host->ReleaseAutomationObject();
	}
}

void CProMoAppChildAuto::OnFinalRelease()
/* ============================================================
	Function :		CProMoAppChildAuto::OnFinalRelease
	Description :	Release the automation object. Called when
					the last reference for an automation object
					is released. The base class will
					automatically delete the object.
	Access :		Public

	Return :		void
	Parameters :	none

	Usage:			Overridden to detach the internal automation 
					host object, which will release the reference
					to the automation object and allow it to be
					destroyed when all references are released. 
					Also, the application automation object 
					reference is released by setting it to NULL. 

   ============================================================*/
{
	DetachInternalObject();
	SetAppAutoObject(NULL);
	CCmdTarget::OnFinalRelease();
}

BOOL CProMoAppChildAuto::IsAlive() const
/* ============================================================
	Function :		CProMoAppChildAuto::IsAlive
	Description :	Checks if the automation object is still 
					attached to a host.
	Access :		Public

	Return :		BOOL		-	"TRUE" if the automation 
									object is still attached to a
									host, "FALSE" otherwise.
	Parameters :	none
   ============================================================*/
{
	return m_pInternalObject != NULL;
}

void CProMoAppChildAuto::Initialize(IProMoAutomationHost* obj)
/* ============================================================
	Function :		CProMoAppChildAuto::Initialize
	Description :	Initializes the automation object by setting 
					the internal automation host object to the 
					object passed as a parameter. The internal 
					automation host object is used to manage the 
					lifetime of the automation objects.
	Access :		Public

	Return :		void
	Parameters :	IProMoAutomationHost* obj	-	the internal 
													automation host
													object to set.
   ============================================================*/
{
	m_pInternalObject = obj;
}

void CProMoAppChildAuto::Detach()
/* ============================================================
	Function :		CProMoAppChildAuto::Detach
	Description :	Detaches the automation object from the host, 
					which will release the reference to the 
					automation object and allow it to be destroyed 
					when all references are released.
	Access :		Public

	Return :		void
	Parameters :	none
   ============================================================*/
{
	if (m_pInternalObject) {
		DetachInternalObject();
		GetIDispatch(FALSE)->Release();
	}
}

void CProMoAppChildAuto::ThrowIfDetached() const
/* ============================================================
	Function :		CProMoAppChildAuto::ThrowIfDetached
	Description :	Checks if the automation object is detached from 
					the host, and if so, throws an OLE exception.
	Access :		Public

	Return :		void
	Parameters :	none
   ============================================================*/
{
	if (!m_pInternalObject) {
		//TODO: consider a more specific error code and message
		AfxThrowOleException(E_FAIL);
	}
}

void CProMoAppChildAuto::ThrowIfNoAppAutoObject() const
/* ============================================================
	Function :		CProMoAppChildAuto::ThrowIfNoAppAutoObject
	Description :	Checks if the application automation object is 
					available, and if not, throws an OLE exception.
	Access :		Public

	Return :		void
	Parameters :	none
   ============================================================*/
{
	if (!m_pAppAuto) {
		//TODO: consider a more specific error code and message
		AfxThrowOleException(E_FAIL);
	}
}

void CProMoAppChildAuto::SetAppAutoObject(CProMoAppAutoAbs* pAppAuto)
/* ============================================================
	Function :		CProMoAppChildAuto::SetAppAutoObject
	Description :	Sets the application automation object to the 
					object passed as a parameter. If the new object 
					is different from the current one, the reference 
					count of the old object is released and the new 
					object is AddRef'ed.
	Access :		Public

	Return :		void
	Parameters :	CProMoAppAutoAbs* pAppAuto	-	the application 
													automation object
													to set.
   ============================================================*/
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
/* ============================================================
	Function :		CProMoAppChildAuto::GetAppAutoObject
	Description :	Returns a pointer to the application automation 
					object.
	Access :		Public

	Return :		CProMoAppAutoAbs*	-	a pointer to the 
											application automation 
											object, or "NULL" if no
											object is set.
	Parameters :	none
   ============================================================*/
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
/* ============================================================
	Function :		CProMoAppChildAuto::Application
	Description :	Returns the IDispatch interface of the application 
					automation object.
	Access :		Public
	Return :		LPDISPATCH	-	the IDispatch interface of the 
									application automation object, or
									"NULL" if no application 
									automation object is set.
	Parameters :	none
   ============================================================*/
{
	if (m_pAppAuto) {
		return m_pAppAuto->GetIDispatch(TRUE);
	}
	return NULL;
}

