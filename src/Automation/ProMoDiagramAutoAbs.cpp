/* ==========================================================================

	Copyright © 2026 Technical University of Denmark

	CProMoDiagramAutoAbs

	Author :		Giovanni Meroni

	Purpose :		"CProMoDiagramAutoAbs" is an automation object that 
					represents a diagram in the application. It provides methods
					to access the elements of the diagram, to get and set the 
					size of the diagram, to access the labels of the diagram, 
					to get and set the creatable element types, to save and 
					close the diagram, and to undo and redo changes to the 
					diagram.

	Description :	"CProMoDiagramAutoAbs" provides the implementation of the 
					methods and properties that are common to all diagrams, 
					and relies on pure virtual functions to get the list of
					registered diagrams and to create the diagrams automation
					object. The actual functionality is implemented in derived 
					classes, which represent specific applications.

	Usage :			Derived classes should implement the pure virtual functions 
					to provide the actual functionality. The base class 
					provides the implementation of the methods and properties 
					that are common to all diagrams, and relies on the pure 
					virtual functions to get the list of registered diagrams
					and to create the diagrams automation object.

   ========================================================================*/
#include "stdafx.h"
#include "ProMoDiagramAutoAbs.h"
#include "../FileUtils/SafeArrayWrapper.h"
#include "ProMoLabelsAuto.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CProMoDiagramAuto

IMPLEMENT_DYNAMIC(CProMoDiagramAutoAbs, CProMoAppChildAuto)

CProMoDiagramAutoAbs::CProMoDiagramAutoAbs()
{
	m_pLabels = NULL;
}

CProMoDiagramAutoAbs::~CProMoDiagramAutoAbs()
{
	
}


CProMoLabelsAuto* CProMoDiagramAutoAbs::GetLabelsAutoObject()
{
	ThrowIfDetached();

	if (!m_pLabels) {
		m_pLabels = new CProMoLabelsAuto();
		if (m_pLabels) {
			m_pLabels->SetDiagramAutoObject(this);
		}
	}
	return m_pLabels;
}

void CProMoDiagramAutoAbs::ReleaseLabelsAutoObject()
{
	if (m_pLabels) {
		m_pLabels->SetDiagramAutoObject(NULL);
		m_pLabels->GetIDispatch(FALSE)->Release();
		m_pLabels = NULL;
	}
}

void CProMoDiagramAutoAbs::NotifyChange()
{
	GetContainer()->SetModified(TRUE);
	RefreshWindow();
}

void CProMoDiagramAutoAbs::OnFinalRelease()
{
	// When the last reference for an automation object is released
	// OnFinalRelease is called.  The base class will automatically
	// deletes the object.  Add additional cleanup required for your
	// object before calling the base class.
	ReleaseLabelsAutoObject();
	CProMoAppChildAuto::OnFinalRelease();
}

BEGIN_MESSAGE_MAP(CProMoDiagramAutoAbs, CProMoAppChildAuto)
	//{{AFX_MSG_MAP(CProMoDiagramAutoAbs)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

BEGIN_DISPATCH_MAP(CProMoDiagramAutoAbs, CProMoAppChildAuto)
	//{{AFX_DISPATCH_MAP(CProMoDiagramAutoAbs)
	//}}AFX_DISPATCH_MAP
END_DISPATCH_MAP()

BEGIN_INTERFACE_MAP(CProMoDiagramAutoAbs, CProMoAppChildAuto)
END_INTERFACE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CProMoDiagramAutoAbs message handlers

void CProMoDiagramAutoAbs::Activate()
{
	// TODO: Add your dispatch handler code here

}

void CProMoDiagramAutoAbs::Redo(short times)
{
	for (short i = 0; i < times; ++i) {
		if (GetContainer()) {
			GetContainer()->Redo();
		}
	}
	NotifyChange();
}

void CProMoDiagramAutoAbs::Undo(short times)
{
	for (short i = 0; i < times; ++i) {
		if (GetContainer()) {
			GetContainer()->Undo();
		}
	}
	NotifyChange();
}

BSTR CProMoDiagramAutoAbs::Path()
{
	CString strResult;
	// TODO: Add your dispatch handler code here

	return strResult.AllocSysString();
}

BSTR CProMoDiagramAutoAbs::Type()
{
	CString strResult;
	if (GetContainer()) {
		strResult = GetContainer()->GetModelType();
	}

	return strResult.AllocSysString();
}

LPDISPATCH CProMoDiagramAutoAbs::GetElements()
{
	if (GetContainer()) {
		CProMoDiagramChildAuto* pContainerAuto = dynamic_cast<CProMoDiagramChildAuto*>(GetContainer()->GetAutomationObject());
		if (pContainerAuto) {
			pContainerAuto->SetDiagramAutoObject(this);
			return pContainerAuto->GetIDispatch(TRUE);
		}
	}

	return NULL;
}

void CProMoDiagramAutoAbs::SetElements(LPDISPATCH newValue)
{
	SetNotSupported();
}

long CProMoDiagramAutoAbs::GetWidth()
{
	if (GetContainer()) {
		return GetContainer()->GetVirtualSize().cx;
	}
	
	return 0;
}

void CProMoDiagramAutoAbs::SetWidth(long nNewValue)
{
	if (GetContainer()) {
		GetContainer()->SetVirtualSize(CSize(nNewValue, GetContainer()->GetVirtualSize().cy));
		NotifyChange();
	}
}

long CProMoDiagramAutoAbs::GetHeight()
{
	if (GetContainer()) {
		return GetContainer()->GetVirtualSize().cy;
	}

	return 0;
}

void CProMoDiagramAutoAbs::SetHeight(long nNewValue)
{
	if (GetContainer()) {
		GetContainer()->SetVirtualSize(CSize(GetContainer()->GetVirtualSize().cx, nNewValue));
		NotifyChange();
	}
}

void CProMoDiagramAutoAbs::Save(BOOL noPrompt)
{
	if (GetContainer()) {
		SaveDiagram(noPrompt);
	}
}

void CProMoDiagramAutoAbs::SaveAs(const VARIANT FAR& fileName)
{
	if (GetContainer()) {
		SaveDiagramAs(CVariantWrapper(fileName).GetString());
	}
}

void CProMoDiagramAutoAbs::Close(BOOL saveChanges)
{
	if (GetContainer()) {
		if (saveChanges) {
			SaveDiagram(FALSE);
		}
		CloseDiagram();
	}
}

LPDISPATCH CProMoDiagramAutoAbs::GetLabels() 
{
	if (GetLabelsAutoObject())
	{
		return GetLabelsAutoObject()->GetIDispatch(TRUE);
	}
	
	return NULL;
}

void CProMoDiagramAutoAbs::SetLabels(LPDISPATCH newValue) 
{
	SetNotSupported();

}

VARIANT CProMoDiagramAutoAbs::GetCreatableElementTypes() 
{
	VARIANT vaResult;
	VariantInit(&vaResult);
	
	CStringArray names;

	if (GetContainer()) {
		if (GetContainer()->GetControlFactory()) {
			CStringArray controlTypes;
			GetContainer()->GetControlFactory()->GetEntityTypes(controlTypes);
			for (int i = 0; i < controlTypes.GetSize(); ++i)
				names.Add(controlTypes[i]);
		}
	}

	HRESULT hr = CSafeArrayWrapper::CreateVariantFromCStringArray(names, vaResult);
	if (FAILED(hr))
		AfxThrowOleException(hr);

	return vaResult;
}

void CProMoDiagramAutoAbs::SetCreatableElementTypes(const VARIANT FAR& newValue) 
{
	SetNotSupported();

}
