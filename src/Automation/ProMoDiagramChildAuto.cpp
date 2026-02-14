/* ==========================================================================

	Copyright © 2026 Technical University of Denmark

	CProMoDiagramChildAuto

	Author :		Giovanni Meroni

	Purpose :		"CProMoDiagramChildAuto" is an automation object that 
					represents a child object of the diagram (i.e., the document).

	Description :	"CProMoDiagramChildAuto" is used to provide access to the 
					diagram automation object and to manage	the lifetime of the 
					automation objects. By extending "CProMoAppChildAuto", it 
					provides access to the application

	Usage :			Derived classes should use the "SetDiagramAutoObject" method 
					to set the diagram automation object, which is used to manage 
					the lifetime of the automation objects. The "GetContainer" 
					method can be used to get the container of the diagram, which
					is used to manage the elements of the diagram. The 
					"ThrowIfNoDiagramAutoObject" method can be used to check if 
					the diagram automation object is set, and throw an exception 
					if it is not.

   ========================================================================*/
#include "stdafx.h"
#include "ProMoDiagramChildAuto.h"
#include "ProMoAppAutoAbs.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CProMoDiagramChildAuto

IMPLEMENT_DYNCREATE(CProMoDiagramChildAuto, CProMoAppChildAuto)

CProMoDiagramChildAuto::CProMoDiagramChildAuto()
{
	m_pDiagramAuto = NULL;
}

void CProMoDiagramChildAuto::OnFinalRelease()
{
	// When the last reference for an automation object is released
	// OnFinalRelease is called.  The base class will automatically
	// deletes the object.  Add additional cleanup required for your
	// object before calling the base class.

	SetDiagramAutoObject(NULL);
	CProMoAppChildAuto::OnFinalRelease();
}

CProMoDiagramAutoAbs* CProMoDiagramChildAuto::GetDiagramAutoObject() const
{
	return m_pDiagramAuto;
}

void CProMoDiagramChildAuto::SetDiagramAutoObject(CProMoDiagramAutoAbs* pDiagramAuto)
{
	SetAppAutoObject(pDiagramAuto ? pDiagramAuto->GetAppAutoObject() : NULL);
	
	if (m_pDiagramAuto == pDiagramAuto) {
		return;
	}
	CProMoDiagramAutoAbs* oldDiagramAuto = m_pDiagramAuto;
	m_pDiagramAuto = pDiagramAuto;

	if (oldDiagramAuto) {
		oldDiagramAuto->GetIDispatch(FALSE)->Release();
	}
	if (m_pDiagramAuto) {
		m_pDiagramAuto->GetIDispatch(FALSE)->AddRef();
	}

}

void CProMoDiagramChildAuto::ThrowIfNoDiagramAutoObject() const
{
	ThrowIfNoAppAutoObject();

	if (!m_pDiagramAuto) {
		//TODO: consider a more specific error code and message
		AfxThrowOleException(E_FAIL);
	}
}

CProMoEntityContainer* CProMoDiagramChildAuto::GetContainer() 
{
	if (m_pDiagramAuto) {
		return m_pDiagramAuto->GetContainer();
	}
	return NULL;
}

CProMoDiagramChildAuto::~CProMoDiagramChildAuto()
{
}

BEGIN_MESSAGE_MAP(CProMoDiagramChildAuto, CProMoAppChildAuto)
	//{{AFX_MSG_MAP(CProMoDiagramChildAuto)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

BEGIN_DISPATCH_MAP(CProMoDiagramChildAuto, CProMoAppChildAuto)
	//{{AFX_DISPATCH_MAP(CProMoDiagramChildAuto)
	DISP_FUNCTION(CProMoDiagramChildAuto, "Diagram", Diagram, VT_DISPATCH, VTS_NONE)
	//}}AFX_DISPATCH_MAP
END_DISPATCH_MAP()

BEGIN_INTERFACE_MAP(CProMoDiagramChildAuto, CProMoAppChildAuto)
END_INTERFACE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CProMoDiagramChildAuto message handlers


LPDISPATCH CProMoDiagramChildAuto::Diagram()
{
	if (m_pDiagramAuto) {
		return m_pDiagramAuto->GetIDispatch(TRUE);
	}
	return NULL;
}


