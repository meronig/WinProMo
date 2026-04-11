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
/* ============================================================
	Function :		CProMoAppAutoAbs::CProMoAppAutoAbs
	Description :	Constructor
	Access :		Public

	Return :		void
	Parameters :	none

   ============================================================*/
{
	EnableAutomation();

	// To keep the application running as long as an OLE automation 
	//	object is active, the constructor calls AfxOleLockApp.

	AfxOleLockApp();

	m_pDiagrams = NULL;
}

CProMoAppAutoAbs::~CProMoAppAutoAbs()
/* ============================================================
	Function :		CProMoAppAutoAbs::~CProMoAppAutoAbs
	Description :	Destructor
	Access :		Public

	Return :		void
	Parameters :	none

   ============================================================*/
{
	// To terminate the application when all objects created with
	// 	with OLE automation, the destructor calls AfxOleUnlockApp.

	AfxOleUnlockApp();
	
}


void CProMoAppAutoAbs::OnFinalRelease()
/* ============================================================
	Function :		CProMoAppAutoAbs::OnFinalRelease
	Description :	Release the automation object. Called when 
					the last reference for an automation object 
					is released. The base class will 
					automatically delete the object.
	Access :		Public

	Return :		void
	Parameters :	none

	Usage:			Overridden to release the diagrams automation 
					object when the application automation object 
					is released.

   ============================================================*/
{
	ReleaseDiagramsAutoObject();
	CCmdTarget::OnFinalRelease();
}

CProMoDiagramsAutoAbs* CProMoAppAutoAbs::GetDiagramsAutoObject()
/* ============================================================
	Function :		CProMoAppAutoAbs::GetDiagramsAutoObject
	Description :	Returns a pointer to the automation object that 
					represents the collection of diagrams currently
					open. If the automation object does not
					exist, it is created.
	Access :		Public

	Return :		CProMoLabelsAuto*	-	a pointer to the
											automation object
											that represents the
											collection of
											open diagrams.
	Parameters :	none

   ============================================================*/
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
/* ============================================================
	Function :		CProMoAppAutoAbs::ReleaseDiagramsAutoObject
	Description :	Releases the automation object that represents 
					the collection of open diagrams, if it exists.
	Access :		Public

	Return :		void
	Parameters :	none
   ============================================================*/
{
	if (m_pDiagrams)
	{
		m_pDiagrams->SetAppAutoObject(NULL);
		m_pDiagrams->GetIDispatch(FALSE)->Release();
		m_pDiagrams = NULL;
	}
}

BOOL CProMoAppAutoAbs::CanCreateDiagram(const CString& diagramType)
/* ============================================================
	Function :		CProMoAppAutoAbs::CanCreateDiagram
	Description :	Checks if a diagram of the specified type 
					can be created.
	Access :		Public

	Return :		BOOL					-	"TRUE" if a diagram
												of the specified 
												type can be created, 
												"FALSE" otherwise.
	Parameters :	CString& diagramType	-	the type of the 
												diagram to check.
   ============================================================*/
{
	CStringArray types;
	GetRegisteredDiagrams(types);

	for (int i = 0; i < types.GetSize(); i++) {
		if (types.GetAt(i) == diagramType) {
			return TRUE;
		}
	}

	return FALSE;
}

BEGIN_MESSAGE_MAP(CProMoAppAutoAbs, CCmdTarget)
	//{{AFX_MSG_MAP(CProMoAppAutoAbs)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

BEGIN_DISPATCH_MAP(CProMoAppAutoAbs, CCmdTarget)
	//{{AFX_DISPATCH_MAP(CProMoAppAutoAbs)
	//}}AFX_DISPATCH_MAP
END_DISPATCH_MAP()

BEGIN_INTERFACE_MAP(CProMoAppAutoAbs, CCmdTarget)
END_INTERFACE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CProMoAppAutoAbs message handlers

LPDISPATCH CProMoAppAutoAbs::GetDiagrams()
/* ============================================================
	Function :		CProMoAppAutoAbs::GetDiagrams
	Description :	Returns the diagrams collection automation object.
	Access :		Public
	
	Return :		LPDISPATCH			-	a pointer to the 
											IDispatch interface 
											of the diagrams 
											automation object.
	Parameters :	none
   ============================================================*/
{
	if (GetDiagramsAutoObject())
	{
		return GetDiagramsAutoObject()->GetIDispatch(TRUE);
	}
	return NULL;
}

void CProMoAppAutoAbs::SetDiagrams(LPDISPATCH newValue)
/* ============================================================
	Function :		CProMoAppAutoAbs::SetDiagrams
	Description :	Sets the diagrams collection automation object. 
					This property is read-only, so this function 
					simply raises an exception.
	Access :		Public
	
	Return :		void
	Parameters :	LPDISPATCH newValue	-	a pointer to the 
											IDispatch interface 
											of the new diagrams 
											automation object.
   ============================================================*/ 
{
	SetNotSupported();
}

LPDISPATCH CProMoAppAutoAbs::ActiveDiagram()
/* ============================================================
	Function :		CProMoAppAutoAbs::ActiveDiagram
	Description :	Returns the active diagram automation object.
	Access :		Public
	
	Return :		LPDISPATCH			-	a pointer to the 
											IDispatch interface 
											of the active diagram 
											automation object, or 
											"NULL" if there is no 
											active diagram.
	Parameters :	none
   ============================================================*/
{
	CProMoDiagramAutoAbs* pActiveDiagram = GetActiveDiagram();

	if (pActiveDiagram)
	{
		pActiveDiagram->SetAppAutoObject(this);
		return pActiveDiagram->GetIDispatch(TRUE);
	}

	return NULL;
}

void CProMoAppAutoAbs::Quit(BOOL saveChanges)
/* ============================================================
	Function :		CProMoAppAutoAbs::Quit
	Description :	Closes the application.
	Access :		Public
	
	Return :		void
	Parameters :	BOOL saveChanges	-	"TRUE" if the application 
											should prompt the user 
											to save any unsaved 
											changes before quitting.
											"FALSE" if the application 
											should quit immediately 
											without prompting
											(any unsaved diagram
											will be discarded).
   ============================================================*/
{
	if (!saveChanges)
	{
		ForceQuit();
	}

	CWnd* pMainWnd = AfxGetMainWnd();
	if (pMainWnd && ::IsWindow(pMainWnd->GetSafeHwnd()))
		pMainWnd->PostMessage(WM_CLOSE);
	else
		PostQuitMessage(0);
}

VARIANT CProMoAppAutoAbs::GetCreatableDiagramTypes()
/* ============================================================
	Function :		CProMoAppAutoAbs::GetCreatableDiagramTypes
	Description :	Returns the list of creatable diagram types.
	Access :		Public
	
	Return :		VARIANT				-	a VARIANT containing a 
											SafeArray of BSTRs, 
											each representing a 
											creatable diagram type.
	Parameters :	none
   ============================================================*/
{
	VARIANT vaResult;
	VariantInit(&vaResult);
	
	CStringArray names;
	GetRegisteredDiagrams(names);

	HRESULT hr = CSafeArrayWrapper::CreateVariantFromCStringArray(names, vaResult);
	if (FAILED(hr))
		AfxThrowOleException(hr);

	return vaResult;
}

void CProMoAppAutoAbs::SetCreatableDiagramTypes(const VARIANT FAR& newValue) 
/* ============================================================
	Function :		CProMoAppAutoAbs::SetCreatableDiagramTypes
	Description :	Sets the list of creatable diagram types. This 
					property is read-only, so this function simply 
					raises an exception.
	Access :		Public
	
	Return :		void
	Parameters :	VARIANT newValue	-	a VARIANT containing a 
											SafeArray of BSTRs, 
											each representing a new 
											creatable diagram type.
   ============================================================*/
{
	SetNotSupported();

}
