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
{
}

CProMoDiagramsAutoAbs::~CProMoDiagramsAutoAbs()
{

}

void CProMoDiagramsAutoAbs::SetAppAutoObject(CProMoAppAutoAbs* pAppAuto)
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
{
	SetNotSupported();

}

short CProMoDiagramsAutoAbs::Count()
{
	ThrowIfNoAppAutoObject();
	
	return GetOpenDiagramsCount();
}

void CProMoDiagramsAutoAbs::Save(BOOL noPrompt)
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
{
	SetNotSupported();

}
