/* ==========================================================================

	Copyright © 2026 Technical University of Denmark

	CProMoLabelsAuto

	Author :		Giovanni Meroni

	Purpose :		"CProMoLabelsAuto" is an automation object that
					represents either the collection of labels of a diagram 
					element, or the collection of labels of a diagram. 
					In the first case, it provides methods to access the 
					labels. In the second case, to also provides methods to
					add new labels, and to remove existing labels.

	Description :	"CProMoLabelsAuto" provides the implementation
					of the methods and properties that are common to all
					labels collections.

   ========================================================================*/
#include "stdafx.h"
#include "ProMoLabelsAuto.h"
#include "../ProMoEditor/ProMoLabel.h"
#include "../FileUtils/SafeArrayWrapper.h"
#include "ProMoLabelAuto.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CProMoLabelsAuto

IMPLEMENT_DYNCREATE(CProMoLabelsAuto, CProMoElementChildAuto)

CProMoLabelsAuto::CProMoLabelsAuto()
{
}

CProMoLabelsAuto::~CProMoLabelsAuto()
{
}

void CProMoLabelsAuto::SetDiagramAutoObject(CProMoDiagramAutoAbs* pDiagramAuto) {
	CProMoAppChildAuto::SetAppAutoObject(pDiagramAuto ? pDiagramAuto->GetAppAutoObject() : NULL);
	m_pDiagramAuto = pDiagramAuto;
}

void CProMoLabelsAuto::SetElementAutoObject(CProMoElementAuto* pElementAuto) {
	CProMoDiagramChildAuto::SetDiagramAutoObject(pElementAuto ? pElementAuto->GetDiagramAutoObject() : NULL);
	m_pElementAuto = pElementAuto;
}

void CProMoLabelsAuto::GetLabels(CObArray& labels)
{
	ThrowIfNoDiagramAutoObject();
	
	if (GetElementAutoObject()) {
		// Collection is associated to an element, so we return the labels of the element
		if (GetModel()) {
			GetModel()->GetLabels(labels);
		}
	} else {
		// Collection is associated to the diagram, so we return the labels of the diagram
		if (GetContainer()) {
			GetContainer()->GetLabels(labels, TRUE);
		}
	}
}

BEGIN_MESSAGE_MAP(CProMoLabelsAuto, CCmdTarget)
	//{{AFX_MSG_MAP(CProMoLabelsAuto)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

BEGIN_DISPATCH_MAP(CProMoLabelsAuto, CCmdTarget)
	//{{AFX_DISPATCH_MAP(CProMoLabelsAuto)
	DISP_PROPERTY_EX(CProMoLabelsAuto, "IDs", GetIDs, SetIDs, VT_VARIANT)
	DISP_FUNCTION(CProMoLabelsAuto, "Add", Add, VT_DISPATCH, VTS_NONE)
	DISP_FUNCTION(CProMoLabelsAuto, "Count", Count, VT_I4, VTS_NONE)
	DISP_FUNCTION(CProMoLabelsAuto, "Remove", Remove, VT_BOOL, VTS_VARIANT)
	DISP_PROPERTY_PARAM(CProMoLabelsAuto, "Item", GetItem, SetItem, VT_DISPATCH, VTS_VARIANT)
	DISP_DEFVALUE(CProMoLabelsAuto, "Item")
	//}}AFX_DISPATCH_MAP
END_DISPATCH_MAP()

// Note: we add support for IID_IProMoLabelsAuto to support typesafe binding
//  from VBA.  This IID must match the GUID that is attached to the 
//  dispinterface in the .ODL file.

// {18EA3771-08C3-11F1-9744-000C2976A615}
static const IID IID_IProMoLabelsAuto =
{ 0x18ea3771, 0x8c3, 0x11f1, { 0x97, 0x44, 0x0, 0xc, 0x29, 0x76, 0xa6, 0x15 } };

BEGIN_INTERFACE_MAP(CProMoLabelsAuto, CCmdTarget)
	INTERFACE_PART(CProMoLabelsAuto, IID_IProMoLabelsAuto, Dispatch)
END_INTERFACE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CProMoLabelsAuto message handlers

LPDISPATCH CProMoLabelsAuto::Add() 
{
	ThrowIfNoDiagramAutoObject();

	if (GetElementAutoObject()) {
		// Collection is associated to an element, so we cannot add a label to it
		AfxThrowOleException(E_FAIL);
		return NULL;
	} else {
		// Collection is associated to the diagram, so we add a label to the diagram
		CProMoEntityContainer* pContainer = GetContainer();
		if (pContainer) {
			CProMoLabel* element = new CProMoLabel;
			element->SetRect(0, 0, 1, 1);
			GetContainer()->Snapshot();
			pContainer->Add(element);
			GetContainer()->SetModified(TRUE);
			RefreshViews();
			CProMoElementAuto* pElementAuto = dynamic_cast<CProMoElementAuto*>(element->GetAutomationObject());
			if (pElementAuto) {
				pElementAuto->SetDiagramAutoObject(GetDiagramAutoObject());
				return pElementAuto->GetIDispatch(TRUE);
			}
		}
	}
		
	return NULL;
}

long CProMoLabelsAuto::Count() 
{
	CObArray labels;
	GetLabels(labels);
	return labels.GetSize();
}

BOOL CProMoLabelsAuto::Remove(const VARIANT FAR& Item) 
{
	// TODO: Add your dispatch handler code here

	return TRUE;
}

LPDISPATCH CProMoLabelsAuto::GetItem(const VARIANT FAR& Item) 
{
	CVariantWrapper wrapper(Item);
	
	CObArray labels;
	CProMoLabel* pLabel = NULL;
	GetLabels(labels);

	if (wrapper.GetType() != VT_BSTR) {
		if (wrapper.GetInt() >= 0 && wrapper.GetInt() < labels.GetSize()) {
			pLabel = dynamic_cast<CProMoLabel*>(labels.GetAt(wrapper.GetInt()));
		}
	}
	else {
		for (int i = 0; i < labels.GetSize(); i++) {
			pLabel = dynamic_cast<CProMoLabel*>(labels.GetAt(i));
			if (pLabel && pLabel->GetName() == wrapper.GetString()) {
				break;
			}
			pLabel = NULL;
		}
	}

	if (pLabel) {
		CProMoLabelAuto* pElementAuto = dynamic_cast<CProMoLabelAuto*>(pLabel->GetAutomationObject());
		if (pElementAuto) {
			if (GetElementAutoObject()) {
				// Collection is associated to an element, so we set the element auto object to the label auto object
				pElementAuto->SetElementAutoObject(GetElementAutoObject());
			} else {
				// Collection is associated to the diagram, so we set the diagram auto object to the label auto object
				pElementAuto->SetDiagramAutoObject(GetDiagramAutoObject());
			}
			return pElementAuto->GetIDispatch(TRUE);
		}
	}

	return NULL;
}

void CProMoLabelsAuto::SetItem(const VARIANT FAR& Item, LPDISPATCH newValue) 
{
	SetNotSupported();

}

VARIANT CProMoLabelsAuto::GetIDs() 
{
	VARIANT vaResult;
	VariantInit(&vaResult);
	
	CStringArray names;
	CObArray labels;
	CProMoLabel* pLabel = NULL;
	GetLabels(labels);

	for (int i = 0; i < labels.GetSize(); i++) {
		pLabel = dynamic_cast<CProMoLabel*>(labels.GetAt(i));
		if (pLabel) {
			names.Add(pLabel->GetName());
		}
	}

	HRESULT hr = CSafeArrayWrapper::CreateVariantFromCStringArray(names, vaResult);
	if (FAILED(hr))
		AfxThrowOleException(hr);
	
	return vaResult;
}

void CProMoLabelsAuto::SetIDs(const VARIANT FAR& newValue) 
{
	SetNotSupported();

}
