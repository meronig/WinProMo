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
/* ============================================================
	Function :		CProMoLabelsAuto::CProMoLabelsAuto
	Description :	Constructor
	Access :		Public

	Return :		void
	Parameters :	none
	============================================================ */
{
}

CProMoLabelsAuto::~CProMoLabelsAuto()
/* ============================================================
	Function :		CProMoLabelsAuto::~CProMoLabelsAuto
	Description :	Destructor
	Access :		Public

	Return :		void
	Parameters :	none
	============================================================ */
{
}

void CProMoLabelsAuto::SetDiagramAutoObject(CProMoDiagramAutoAbs* pDiagramAuto) 
/* ============================================================
	Function :		CProMoLabelsAuto::SetDiagramAutoObject
	Description :	Sets the diagram automation object to the
					object passed as a parameter. Overridden
					to avoid creating circular references between
					COM objects that would prevent them from being
					released.
	Access :		Public

	Return :		void
	Parameters :	CProMoDiagramAutoAbs* pDiagramAuto	-	The diagram
															automation
															object to set.
   ============================================================*/
{
	SetAppAutoObject(pDiagramAuto ? pDiagramAuto->GetAppAutoObject() : NULL);
	m_pDiagramAuto = pDiagramAuto;
}

void CProMoLabelsAuto::SetElementAutoObject(CProMoElementAuto* pElementAuto) 
/* ============================================================
	Function :		CProMoLabelsAuto::SetElementAutoObject
	Description :	Sets the element automation object to the
					object passed as a parameter. Overridden
					to avoid creating circular references between
					COM objects that would prevent them from being
					released.
	Access :		Public

	Return :		void
	Parameters :	CProMoElementAuto* pElementAuto	-	The element
														automation
														object to set.
   ============================================================*/
{
	SetDiagramAutoObject(pElementAuto ? pElementAuto->GetDiagramAutoObject() : NULL);
	m_pElementAuto = pElementAuto;
}

CProMoElementAuto* CProMoLabelsAuto::GetElementAutoObject() const
/* ============================================================
	Function :		CProMoLabelsAuto::GetElementAutoObject
	Description :	Returns the element automation object.
					Overridden not to throw an exception if the 
					element automation object is not set, because 
					in this case the collection is associated to 
					the diagram, and not to an element.
	Access :		Public

	Return :		CProMoElementAuto*	-	The element automation
											object.
	Parameters :	none
   ============================================================*/
{
	ThrowIfNoDiagramAutoObject();
	return m_pElementAuto;
}

void CProMoLabelsAuto::GetLabels(CObArray& labels)
/* ============================================================
	Function :		CProMoLabelsAuto::GetLabels
	Description :	Fills the array passed as a parameter with the
					labels of the collection.
	Access :		Protected

	Return :		void
	Parameters :	CObArray& labels	-	The array to fill with the
											labels of the collection.
   ============================================================*/
{
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

CProMoLabel* CProMoLabelsAuto::FindLabel(const VARIANT& Item, const CObArray& collection)
/* ============================================================
	Function :		CProMoLabelsAuto::FindLabel
	Description :	Finds the label in the collection that is 
					identified by the parameter "Item". "Item" can
					be either the name or the index of the label to
					find.
	Access :		Protected

	Return :		CProMoLabel*			-	The label identified by the
												parameter "Item", or NULL if
												the parameter does not identify
												a label in the collection.
	Parameters :	VARIANT& Item			-	The name or index
												of the label to find.
					CObArray& collection	-	The collection of
												labels to search in.
   ============================================================*/
{
	CVariantWrapper wrapper(Item);
	CProMoLabel* pModel = NULL;

	if (wrapper.GetType() != VT_BSTR) {
		if (wrapper.GetInt() >= 0 && wrapper.GetInt() < collection.GetSize()) {
			pModel = dynamic_cast<CProMoLabel*>(collection.GetAt(wrapper.GetInt()));
		}
	}
	else {
		for (int i = 0; i < collection.GetSize(); i++) {
			pModel = dynamic_cast<CProMoLabel*>(collection.GetAt(i));
			if (pModel && pModel->GetName() == wrapper.GetString()) {
				break;
			}
			pModel = NULL;
		}
	}

	return pModel;
}

BEGIN_MESSAGE_MAP(CProMoLabelsAuto, CProMoElementChildAuto)
	//{{AFX_MSG_MAP(CProMoLabelsAuto)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

BEGIN_DISPATCH_MAP(CProMoLabelsAuto, CProMoElementChildAuto)
	//{{AFX_DISPATCH_MAP(CProMoLabelsAuto)
	DISP_PROPERTY_EX(CProMoLabelsAuto, "IDs", GetIDs, SetIDs, VT_VARIANT)
	DISP_FUNCTION(CProMoLabelsAuto, "Count", Count, VT_I2, VTS_NONE)
	DISP_FUNCTION(CProMoLabelsAuto, "Add", Add, VT_DISPATCH, VTS_NONE)
	DISP_FUNCTION(CProMoLabelsAuto, "Remove", Remove, VT_BOOL, VTS_VARIANT)
	//Common to CProMoElementChildAuto
	DISP_FUNCTION(CProMoElementChildAuto, "Element", Element, VT_DISPATCH, VTS_NONE)
	//Common to CProMoDiagramChildAuto
	DISP_FUNCTION(CProMoDiagramChildAuto, "Diagram", Diagram, VT_DISPATCH, VTS_NONE)
	//Common to CProMoAppChildAuto
	DISP_FUNCTION(CProMoAppChildAuto, "Application", Application, VT_DISPATCH, VTS_NONE)
	//Default property
	DISP_PROPERTY_PARAM(CProMoLabelsAuto, "Item", GetItem, SetItem, VT_DISPATCH, VTS_VARIANT)
	DISP_DEFVALUE(CProMoLabelsAuto, "Item")
	//}}AFX_DISPATCH_MAP
END_DISPATCH_MAP()

// Note: we add support for IID_IProMoLabelsAuto to support typesafe binding
//  from VBA.  This IID must match the GUID that is attached to the 
//  dispinterface in the .ODL file.

// {38EA3768-08C3-11F1-9744-000C2976A615}
static const IID IID_IProMoLabelsAuto =
{ 0x38ea3768, 0x8c3, 0x11f1, { 0x97, 0x44, 0x0, 0xc, 0x29, 0x76, 0xa6, 0x15 } };

BEGIN_INTERFACE_MAP(CProMoLabelsAuto, CProMoElementChildAuto)
	INTERFACE_PART(CProMoLabelsAuto, IID_IProMoLabelsAuto, Dispatch)
END_INTERFACE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CProMoLabelsAuto message handlers

LPDISPATCH CProMoLabelsAuto::Add() 
/* ============================================================
	Function :		CProMoLabelsAuto::Add
	Description :	Adds a new label to the collection. If the
					collection is associated to an element, an
					exception is thrown. If the collection
					is associated to the diagram, the new label is
					added to the diagram.
	Access :		Public

	Return :		LPDISPATCH	-	The automation object of the new
									label added to the collection.
	Parameters :	none
   ============================================================ */
{
	if (GetElementAutoObject()) {
		// Collection is associated to an element, so we cannot add a label to it
		AfxThrowOleException(E_FAIL);
		return NULL;
	} else {
		// Collection is associated to the diagram, so we add a label to the diagram
		CProMoEntityContainer* pContainer = GetContainer();
		if (pContainer) {
			CProMoLabel* element = new CProMoLabel;
			element->SetRect(0, 0, 10, 10);
			GetContainer()->Snapshot();
			pContainer->Add(element);
			GetDiagramAutoObject()->NotifyChange();
			CProMoLabelAuto* pElementAuto = dynamic_cast<CProMoLabelAuto*>(element->GetAutomationObject());
			if (pElementAuto) {
				pElementAuto->SetDiagramAutoObject(GetDiagramAutoObject());
				return pElementAuto->GetIDispatch(TRUE);
			}
		}
	}
		
	return NULL;
}

short CProMoLabelsAuto::Count() 
/* ============================================================
	Function :		CProMoLabelsAuto::Count
	Description :	Returns the number of labels in the collection.
	Access :		Public

	Return :		short	-	The number of labels in the collection.
	Parameters :	none
	============================================================ */
{
	CObArray labels;
	GetLabels(labels);
	return labels.GetSize();
}

BOOL CProMoLabelsAuto::Remove(const VARIANT FAR& item) 
/* ============================================================
	Function :		CProMoLabelsAuto::Remove
	Description :	Removes the label identified by the parameter
					"Item" from the collection. "Item" can be
					either the name or the index of the label to
					remove.
	Access :		Public
	Return :		BOOL			-	"TRUE" if a label identified by
										the parameter "Item" was found
										in the collection and removed;
										"FALSE" otherwise.
	Parameters :	VARIANT Item 	-	the name or index of the
										label to remove.
   ============================================================ */
{
	CObArray labels;
	GetLabels(labels);
	CProMoLabel* pLabel = FindLabel(item, labels);
	if (pLabel) {
		GetContainer()->Snapshot();
		GetContainer()->Remove(pLabel);
		GetDiagramAutoObject()->NotifyChange();
		return TRUE;
	}
	
	return FALSE;
}

LPDISPATCH CProMoLabelsAuto::GetItem(const VARIANT FAR& item) 
/* ============================================================
	Function :		CProMoLabelsAuto::GetItem
	Description :	Returns the label automation object corresponding
					to the specified index or name.
	Access :		Public
	Return :		LPDISPATCH			-	a pointer to the
											IDispatch interface
											of the label
											automation object
											corresponding to the
											specified index or name,
											or "NULL" if no label
											with the specified index
											or name is found.
	Parameters :	VARIANT FAR& Item 	-	the index or name of the
											label to return.
   ============================================================ */
{
	CObArray labels;
	GetLabels(labels);
	CProMoLabel* pLabel = FindLabel(item, labels);

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
/* ============================================================
	Function :		CProMoLabelsAuto::SetItem
	Description :	Sets the label automation object corresponding
					to the specified index or name. This property is
					read-only, so this function simply raises an
					exception.
	Access :		Public
	Return :		void
	Parameters :	VARIANT FAR& Item 	-	the index or name of the
											label to set.
					LPDISPATCH newValue	-	a pointer to the new
											IDispatch interface of the
											label automation object to
											set for the specified index or
											name.
   ============================================================ */
{
	SetNotSupported();

}

VARIANT CProMoLabelsAuto::GetIDs() 
/* ============================================================
	Function :		CProMoLabelsAuto::GetIDs
	Description :	Returns a SAFEARRAY of VARIANT containing the names
					of the labels in the collection.
	Access :		Public

	Return :		VARIANT	-	a VARIANT containing a SAFEARRAY
								of BSTRs with the names of the
								labels in the collection.
	Parameters :	none
   ============================================================ */
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
/* ============================================================
	Function :		CProMoLabelsAuto::SetIDs
	Description :	Sets the list of the names of the labels.
					This property is read-only, so this function simply
					raises an exception.
	Access :		Public

	Return :		void
	Parameters :	VARIANT FAR& newValue	-	a VARIANT containing 
												a safe array of
												BSTRs with the 
												names of the labels
												to set.
   ============================================================ */
{
	SetNotSupported();

}
