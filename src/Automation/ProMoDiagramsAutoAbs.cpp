/* ==========================================================================

	Copyright © 2026 Technical University of Denmark

	CProMoDiagramsAutoAbs

	Author :		Giovanni Meroni

	Purpose :		"CProMoDiagramsAutoAbs" is an automation object that 
					represents the collection of diagrams in the application. It
					provides methods to access the open diagrams, to add new
					diagrams, and to open existing diagrams.

	Description :	"CProMoDiagramsAutoAbs" provides the implementation of the 
					"Diagrams" property, which is common to all applications, 
					and relies on pure virtual functions to get the
					list of registered diagrams and to create the diagrams
					automation object. The actual functionality is implemented in
					derived classes, which represent specific applications.

	Usage :			Derived classes shoudl implement the pure virtual functions 
					to provide the actual functionality. The base class relies 
					on the pure virtual functions to get the list of
					registered diagrams and to create the diagrams automation
					object.

   ========================================================================*/
#include "stdafx.h"
#include "ProMoDiagramsAutoAbs.h"
#include "../FileUtils/SafeArrayWrapper.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CProMoDiagramsAuto

IMPLEMENT_DYNAMIC(CProMoDiagramsAutoAbs, CProMoAppChildAuto)

CProMoDiagramsAutoAbs::CProMoDiagramsAutoAbs()
/* ============================================================
	Function :		CProMoDiagramsAutoAbs::CProMoDiagramsAutoAbs
	Description :	Constructor
	Access :		Public

	Return :		void
	Parameters :	none
   ============================================================ */
{
}

CProMoDiagramsAutoAbs::~CProMoDiagramsAutoAbs()
/* ============================================================
	Function :		CProMoDiagramsAutoAbs::~CProMoDiagramsAutoAbs
	Description :	Destructor
	Access :		Public

	Return :		void
	Parameters :	none
   ============================================================ */
{
}

void CProMoDiagramsAutoAbs::SetAppAutoObject(CProMoAppAutoAbs* pAppAuto)
/* ============================================================
	Function :		CProMoDiagramsAutoAbs::SetAppAutoObject
	Description :	Sets the application automation object to the 
					object passed as a parameter. Overridden
					to avoid creating circular references between 
					COM objects that would prevent them from being
					released.
	Access :		Public
	Return :		void
	Parameters :	pAppAuto	-	a pointer to the application 
									automation object to set for this 
									diagrams automation object.
   ============================================================ */
{
	m_pAppAuto = pAppAuto;

}

BEGIN_MESSAGE_MAP(CProMoDiagramsAutoAbs, CProMoAppChildAuto)
	//{{AFX_MSG_MAP(CProMoDiagramsAutoAbs)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

BEGIN_DISPATCH_MAP(CProMoDiagramsAutoAbs, CProMoAppChildAuto)
	//{{AFX_DISPATCH_MAP(CProMoDiagramsAutoAbs)
	//}}AFX_DISPATCH_MAP
END_DISPATCH_MAP()

BEGIN_INTERFACE_MAP(CProMoDiagramsAutoAbs, CCmdTarget)
END_INTERFACE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CProMoDiagramsAutoAbs message handlers

LPDISPATCH CProMoDiagramsAutoAbs::Add(const VARIANT FAR& documentType)
/* ============================================================
	Function :		CProMoDiagramsAutoAbs::Add
	Description :	Creates a new diagram of the specified type and 
					returns the corresponding diagram automation object.
	Access :		Public
	Return :		LPDISPATCH					-	a pointer to the 
													IDispatch interface
													of the created 
													diagram 
													automation object, 
													or "NULL" if the 
													diagram	could not
													be created.
	Parameters :	VARIANT FAR& documentType	-	the type of the 
													diagram to create.
   ============================================================ */
{
	ThrowIfNoAppAutoObject();

	CVariantWrapper wrapper(documentType);

	if (GetAppAutoObject()->CanCreateDiagram(wrapper.GetString())) {

		CProMoDiagramAutoAbs* pDiagramAuto = AddNewDiagram(wrapper.GetString());
		if (pDiagramAuto) {
			pDiagramAuto->SetAppAutoObject(GetAppAutoObject());
			return pDiagramAuto->GetIDispatch(TRUE);
		}
	}

	return NULL;
}

LPDISPATCH CProMoDiagramsAutoAbs::Open(const VARIANT FAR& fileName)
/* ============================================================
	Function :		CProMoDiagramsAutoAbs::Open
	Description :	Opens the diagram stored in the specified file and 
					returns the corresponding diagram automation object.
	Access :		Public
	Return :		LPDISPATCH			-	a pointer to the 
											IDispatch interface 
											of the opened diagram 
											automation object, or
											"NULL" if the diagram
											could not be opened.
	Parameters :	VARIANT FAR& fileName	-	the name of the file 
											that contains the diagram
											to open.
   ============================================================ */
{
	ThrowIfNoAppAutoObject();

	CVariantWrapper wrapper(fileName);
	CProMoDiagramAutoAbs* pDiagramAuto = OpenDiagram(wrapper.GetString());
	if (pDiagramAuto) {
		pDiagramAuto->SetAppAutoObject(GetAppAutoObject());
		return pDiagramAuto->GetIDispatch(TRUE);
	}
	return NULL;
}

LPDISPATCH CProMoDiagramsAutoAbs::GetItem(const VARIANT FAR& Item)
/* ============================================================
	Function :		CProMoDiagramsAutoAbs::GetItem
	Description :	Returns the diagram automation object corresponding 
					to the specified index or name.
	Access :		Public
	Return :		LPDISPATCH			-	a pointer to the 
											IDispatch interface 
											of the diagram 
											automation object 
											corresponding to the 
											specified index or name, 
											or "NULL" if no diagram
											 with the specified index
											 or name is found.
	Parameters :	VARIANT FAR& Item 	-	the index or name of the 
											diagram to return.
   ============================================================ */
{
	ThrowIfNoAppAutoObject();

	CVariantWrapper wrapper(Item);

	if (wrapper.GetType() != VT_BSTR) {
		CProMoDiagramAutoAbs* pDiagramAuto = GetDiagramAutoObject(wrapper.GetInt());
		if (pDiagramAuto) {
			pDiagramAuto->SetAppAutoObject(GetAppAutoObject());
			return pDiagramAuto->GetIDispatch(TRUE);
		}
	}
	else {
		CProMoDiagramAutoAbs* pDiagramAuto = GetDiagramAutoObject(wrapper.GetString());
		if (pDiagramAuto) {
			pDiagramAuto->SetAppAutoObject(GetAppAutoObject());
			return pDiagramAuto->GetIDispatch(TRUE);
		}
	}

	return NULL;
}

void CProMoDiagramsAutoAbs::SetItem(const VARIANT FAR& Item, LPDISPATCH newValue)
/* ============================================================
	Function :		CProMoDiagramsAutoAbs::SetItem
	Description :	Sets the diagram automation object corresponding 
					to the specified index or name. This property is 
					read-only, so this function simply raises an 
					exception.
	Access :		Public
	Return :		void
	Parameters :	VARIANT FAR& Item 	-	the index or name of the 
											diagram to set.
					LPDISPATCH newValue	-	a pointer to the new 
											IDispatch interface of the
											diagram automation object to
											set for the specified index or
											name.
   ============================================================ */
{
	SetNotSupported();

}

short CProMoDiagramsAutoAbs::Count()
/* ============================================================
	Function :		CProMoDiagramsAutoAbs::Count
	Description :	Returns the number of open diagrams.
	Access :		Public

	Return :		short	-	the number of open diagrams.
	Parameters :	none
   ============================================================ */
{
	ThrowIfNoAppAutoObject();
	
	return GetOpenDiagramsCount();
}

void CProMoDiagramsAutoAbs::Save(BOOL noPrompt)
/* ============================================================
	Function :		CProMoDiagramsAutoAbs::Save
	Description :	Saves all open diagrams. If "noPrompt" is 
					"TRUE", the diagrams are saved without prompting
					the user. If "noPrompt" is "FALSE", the user is
					prompted for each diagram whether to save it or not.
	Access :		Public

	Return :		void
	Parameters :	noPrompt	-	a boolean value that indicates 
									whether to save the diagrams 
									without prompting the user.
   ============================================================ */
{
	ThrowIfNoAppAutoObject();
	
	for (int i = GetOpenDiagramsCount() - 1; i >= 0; --i) {
		CProMoDiagramAutoAbs* pDiagramAuto = GetDiagramAutoObject(i);
		if (pDiagramAuto) {
			pDiagramAuto->Save(noPrompt);
		}
	}
}

void CProMoDiagramsAutoAbs::Close(BOOL saveChanges)
/* ============================================================
	Function :		CProMoDiagramsAutoAbs::Close
	Description :	Closes all open diagrams. If "saveChanges" is 
					"TRUE", the user is prompted to save any unsaved
					changes for each diagram before closing it. If 
					"saveChanges" is "FALSE", the diagrams are closed
					immediately without prompting the user.
	Access :		Public

	Return :		void
	Parameters :	saveChanges	-	a boolean value that indicates 
									whether to prompt the user to 
									save any unsaved changes before
									closing the diagrams.
   ============================================================ */
{
	ThrowIfNoAppAutoObject();
	
	for (int i = GetOpenDiagramsCount() - 1; i >= 0; --i) {
		CProMoDiagramAutoAbs* pDiagramAuto = GetDiagramAutoObject(i);
		if (pDiagramAuto) {
			pDiagramAuto->Close(saveChanges);
		}
	}

}
VARIANT CProMoDiagramsAutoAbs::GetIDs() 
/* ============================================================
	Function :		CProMoDiagramsAutoAbs::GetIDs
	Description :	Returns a list of the names of the open diagrams.
	Access :		Public

	Return :		VARIANT			-	a VARIANT containing a 
										safe array of BSTRs with 
										the names of the open 
										diagrams.
	Parameters :	none
   ============================================================ */
{
	ThrowIfNoAppAutoObject();

	VARIANT vaResult;
	VariantInit(&vaResult);
	
	CStringArray names;
	GetOpenDiagrams(names);

	HRESULT hr = CSafeArrayWrapper::CreateVariantFromCStringArray(names, vaResult);
	if (FAILED(hr))
		AfxThrowOleException(hr);

	return vaResult;
}

void CProMoDiagramsAutoAbs::SetIDs(const VARIANT FAR& newValue) 
/* ============================================================
	Function :		CProMoDiagramsAutoAbs::SetIDs
	Description :	Sets the list of the names of the open diagrams. 
					This property is read-only, so this function simply
					raises an exception.
	Access :		Public
	Return :		void
	Parameters :	newValue	-	a VARIANT containing a safe array of 
									BSTRs with the names of the open 
									diagrams to set.
   ============================================================ */
{
	SetNotSupported();

}
