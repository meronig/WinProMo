/* ==========================================================================

	Copyright © 2026 Technical University of Denmark

	CProMoAppAutoAbs

	Author :		Giovanni Meroni

	Purpose :		"CProMoAppAutoAbs" is an automation object that represents 
					the application itself. It is the root object of the 
					automation object model.

	Description :	"CProMoAppAutoAbs" provides the implementation of the 
					"Diagrams" property, which is common to all applications, 
					and relies on pure virtual functions to get the list of 
					registered diagrams and to create the diagrams automation 
					object. The actual functionality is implemented in derived 
					classes, which represent specific applications.

	Usage :			Derived classes should implement the pure virtual functions 
					to provide the actual functionality. The base class provides 
					the implementation of the "Diagrams" property, which is 
					common to all applications, and relies on the pure virtual 
					functions to get the list of registered diagrams and to 
					create the diagrams automation object.

   ========================================================================*/
#include "stdafx.h"
#include "ProMoAppAutoAbs.h"
#include "ProMoDiagramsAutoAbs.h"
#include "../FileUtils/SafeArrayWrapper.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CProMoAppAutoAbs

IMPLEMENT_DYNAMIC(CProMoAppAutoAbs, CCmdTarget)

CProMoAppAutoAbs::CProMoAppAutoAbs()
{
	EnableAutomation();

	// To keep the application running as long as an OLE automation 
	//	object is active, the constructor calls AfxOleLockApp.

	AfxOleLockApp();

	m_pDiagrams = NULL;
}

CProMoAppAutoAbs::~CProMoAppAutoAbs()
{
	// To terminate the application when all objects created with
	// 	with OLE automation, the destructor calls AfxOleUnlockApp.

	AfxOleUnlockApp();
	
}


void CProMoAppAutoAbs::OnFinalRelease()
{
	// When the last reference for an automation object is released
	// OnFinalRelease is called.  The base class will automatically
	// deletes the object.  Add additional cleanup required for your
	// object before calling the base class.
	ReleaseDiagramsAutoObject();
	CCmdTarget::OnFinalRelease();
}

CProMoDiagramsAutoAbs* CProMoAppAutoAbs::GetDiagramsAutoObject()
{
	if (!m_pDiagrams)
	{
		m_pDiagrams = CreateDiagramsAutoObject();
		if (m_pDiagrams)
		{
			m_pDiagrams->SetAppAutoObject(this);
		}
	}
	return m_pDiagrams;
}

void CProMoAppAutoAbs::ReleaseDiagramsAutoObject()
{
	if (m_pDiagrams)
	{
		m_pDiagrams->SetAppAutoObject(NULL);
		m_pDiagrams->GetIDispatch(FALSE)->Release();
		m_pDiagrams = NULL;
	}
}

BEGIN_MESSAGE_MAP(CProMoAppAutoAbs, CCmdTarget)
	//{{AFX_MSG_MAP(CProMoAppAutoAbs)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

BEGIN_DISPATCH_MAP(CProMoAppAutoAbs, CCmdTarget)
	//{{AFX_DISPATCH_MAP(CProMoAppAutoAbs)
	DISP_PROPERTY_EX(CProMoAppAutoAbs, "Diagrams", GetDiagrams, SetDiagrams, VT_DISPATCH)
	DISP_PROPERTY_EX(CProMoAppAutoAbs, "CreatableDiagramTypes", GetCreatableDiagramTypes, SetCreatableDiagramTypes, VT_VARIANT)
	DISP_FUNCTION(CProMoAppAutoAbs, "ActiveDocument", ActiveDiagram, VT_DISPATCH, VTS_NONE)
	DISP_FUNCTION(CProMoAppAutoAbs, "Quit", Quit, VT_EMPTY, VTS_BOOL)
	//}}AFX_DISPATCH_MAP
END_DISPATCH_MAP()

BEGIN_INTERFACE_MAP(CProMoAppAutoAbs, CCmdTarget)
END_INTERFACE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CProMoAppAutoAbs message handlers

LPDISPATCH CProMoAppAutoAbs::GetDiagrams()
{
	if (GetDiagramsAutoObject())
	{
		return GetDiagramsAutoObject()->GetIDispatch(TRUE);
	}
	return NULL;
}

void CProMoAppAutoAbs::SetDiagrams(LPDISPATCH newValue)
{
	SetNotSupported();
}

LPDISPATCH CProMoAppAutoAbs::ActiveDiagram()
{
	// TODO: Add your dispatch handler code here

	return NULL;
}

void CProMoAppAutoAbs::Quit(BOOL saveChanges)
{
	// TODO: Add your dispatch handler code here

}

VARIANT CProMoAppAutoAbs::GetCreatableDiagramTypes() 
{
	VARIANT vaResult;
	VariantInit(&vaResult);
	
	//if (!pTypes)
	//	AfxThrowOleException(E_POINTER);

	//CStringArray names;

	//GetRegisteredDiagrams(names);

	//COleSafeArray sa;
	//DWORD cElements = (DWORD)names.GetSize();
	//sa.Create(VT_BSTR, 1, &cElements);

	//for (LONG i = 0; i < names.GetSize(); ++i)
	//	sa.PutElement(&i, names[i].AllocSysString());

	//VariantClear(pTypes);
	//*pTypes = sa.Detach();   // Transfers ownership

	CStringArray names;
	GetRegisteredDiagrams(names);

	HRESULT hr = CSafeArrayWrapper::CreateVariantFromCStringArray(names, vaResult);
	if (FAILED(hr))
		AfxThrowOleException(hr);

	return vaResult;
}

void CProMoAppAutoAbs::SetCreatableDiagramTypes(const VARIANT FAR& newValue) 
{
	// TODO: Add your property handler here

}
