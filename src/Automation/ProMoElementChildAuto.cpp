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
/* ============================================================
	Function :		CProMoElementChildAuto::CProMoElementChildAuto
	Description :	Constructor
	Access :		Public

	Return :		void
	Parameters :	none
   ============================================================ */
{
	m_pElementAuto = NULL;
}

void CProMoElementChildAuto::OnFinalRelease()
/* ============================================================
	Function :		CProMoElementChildAuto::OnFinalRelease
	Description :	Release the automation object. Called when
					the last reference for an automation object
					is released. The base class will
					automatically delete the object.
	Access :		Public

	Return :		void
	Parameters :	none

	Usage:			Overridden to release the element automation
					object by setting it to NULL.

   ============================================================*/
{
	SetElementAutoObject(NULL);
	CProMoDiagramChildAuto::OnFinalRelease();
}

CProMoModel* CProMoElementChildAuto::GetModel()
/* ============================================================
	Function :		CProMoElementChildAuto::GetModel
	Description :	Get the model associated with this element
	Access :		Public

	Return :		CProMoModel*	-	the model associated with
										this element
	Parameters :	none
   ============================================================ */
{
	ThrowIfNoElementAutoObject();

	if (m_pElementAuto) {
		return m_pElementAuto->GetModel();
	}
	return NULL;
}

CProMoElementAuto* CProMoElementChildAuto::GetElementAutoObject() const
/* ============================================================
	Function :		CProMoDiagramChildAuto::GetElementAutoObject
	Description :	Returns the element automation object.
	Access :		Public

	Return :		CProMoElementAuto*	-	The element automation 
											object.
	Parameters :	none
   ============================================================*/
{
	ThrowIfNoElementAutoObject();
	return m_pElementAuto;
}

void CProMoElementChildAuto::SetElementAutoObject(CProMoElementAuto* pElementAuto)
/* ============================================================
	Function :		CProMoElementChildAuto::SetElementAutoObject
	Description :	Sets the element automation object to the
					object passed as a parameter. If the new object
					is different from the current one, the reference
					count of the old object is released and the new
					object is AddRef'ed.
	Access :		Public

	Return :		void
	Parameters :	CProMoElementAuto* pDiagramAuto	-	The element 
														automation 
														object to set.
   ============================================================*/
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
/* ============================================================
	Function :		CProMoElementChildAuto::ThrowIfNoElementAutoObject
	Description :	Checks if the element automation object is
					available, and if not, throws an OLE exception.
	Access :		Public

	Return :		void
	Parameters :	none
   ============================================================*/
{
	ThrowIfNoDiagramAutoObject();
	if (!m_pElementAuto) {
		//TODO: consider a more specific error code and message
		AfxThrowOleException(E_FAIL);
	}
}


CProMoElementChildAuto::~CProMoElementChildAuto()
/* ============================================================
	Function :		CProMoElementChildAuto::~CProMoElementChildAuto
	Description :	Destructor
	Access :		Protected

	Return :		void
	Parameters :	none
   ============================================================ */
{
}

BEGIN_MESSAGE_MAP(CProMoElementChildAuto, CProMoDiagramChildAuto)
	//{{AFX_MSG_MAP(CProMoElementChildAuto)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

BEGIN_DISPATCH_MAP(CProMoElementChildAuto, CProMoDiagramChildAuto)
	//{{AFX_DISPATCH_MAP(CProMoElementChildAuto)
	//}}AFX_DISPATCH_MAP
END_DISPATCH_MAP()

BEGIN_INTERFACE_MAP(CProMoElementChildAuto, CProMoDiagramChildAuto)
END_INTERFACE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CProMoElementChildAuto message handlers

LPDISPATCH CProMoElementChildAuto::Element() 
/* ============================================================
	Function :		CProMoElementChildAuto::Element
	Description :	Returns the element automation object.
	Access :		Public
	Return :		LPDISPATCH			-	a pointer to the
											IDispatch interface
											of the element
											automation object,
											or "NULL" if no
											object is set.
	Parameters :	none
   ============================================================*/
{
	if (m_pElementAuto) {
		return m_pElementAuto->GetIDispatch(TRUE);
	}

	return NULL;
}
