/* ==========================================================================

	Copyright © 2026 Technical University of Denmark

	CProMoPropertyAuto

	Author :		Giovanni Meroni

	Purpose :		"CProMoPropertyAuto" is an automation object that
					represents a property of a diagram element. It provides 
					methods to access the name, the type, and the value of 
					the property (if single-value simple), to get the names 
					of the child properties (if composite), to add and remove
					values (if multivalue), to access the label associated with 
					the property (if any), and to check whether the property 
					is read-only.

	Description :	"CProMoPropertyAuto" provides the implementation of the
					methods and properties that are common to all properties.

   ========================================================================*/
#include "stdafx.h"
#include "ProMoPropertyAuto.h"
#include "../FileUtils/SafeArrayWrapper.h"
#include "ProMoLabelAuto.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CProMoPropertyAuto

IMPLEMENT_DYNCREATE(CProMoPropertyAuto, CProMoElementChildAuto)

CProMoPropertyAuto::CProMoPropertyAuto()
/* ============================================================
	Function :		CProMoPropertyAuto::CProMoPropertyAuto
	Description :	Constructor
	Access :		Public

	Return :		void
	Parameters :	none
	============================================================ */
{
}

CProMoProperty* CProMoPropertyAuto::GetProperty() 
/* ============================================================
	Function :		CProMoPropertyAuto::GetProperty
	Description :	Returns the property represented by this automation
					object.
	Access :		Public

	Return :		CProMoProperty*	-	The property represented 
										by this automation
										object, or NULL if the 
										automation object is not
										attached to any property.
	Parameters :	none
	============================================================ */
{
	ThrowIfDetached();
	ThrowIfNoElementAutoObject();

	return dynamic_cast<CProMoProperty*>(m_pInternalObject);
}

CProMoPropertyAuto::~CProMoPropertyAuto()
/* ============================================================
	Function :		CProMoPropertyAuto::~CProMoPropertyAuto
	Description :	Destructor
	Access :		Public

	Return :		void
	Parameters :	none
	============================================================ */
{
}


BEGIN_MESSAGE_MAP(CProMoPropertyAuto, CProMoElementChildAuto)
	//{{AFX_MSG_MAP(CProMoPropertyAuto)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

BEGIN_DISPATCH_MAP(CProMoPropertyAuto, CProMoElementChildAuto)
	//{{AFX_DISPATCH_MAP(CProMoPropertyAuto)
	DISP_PROPERTY_EX(CProMoPropertyAuto, "Name", GetName, SetName, VT_BSTR)
	DISP_PROPERTY_EX(CProMoPropertyAuto, "Type", GetType, SetType, VT_I4)
	DISP_PROPERTY_EX(CProMoPropertyAuto, "Value", GetValue, SetValue, VT_VARIANT)
	DISP_PROPERTY_EX(CProMoPropertyAuto, "ChildNames", GetChildNames, SetChildNames, VT_VARIANT)
	DISP_FUNCTION(CProMoPropertyAuto, "IsReadOnly", IsReadOnly, VT_BOOL, VTS_NONE)
	DISP_FUNCTION(CProMoPropertyAuto, "IsComposite", IsComposite, VT_BOOL, VTS_NONE)
	DISP_FUNCTION(CProMoPropertyAuto, "IsMultivalue", IsMultivalue, VT_BOOL, VTS_NONE)
	DISP_FUNCTION(CProMoPropertyAuto, "Label", Label, VT_DISPATCH, VTS_NONE)
	DISP_FUNCTION(CProMoPropertyAuto, "Add", Add, VT_DISPATCH, VTS_NONE)
	DISP_FUNCTION(CProMoPropertyAuto, "Remove", Remove, VT_BOOL, VTS_I2)
	DISP_FUNCTION(CProMoPropertyAuto, "Count", Count, VT_I2, VTS_NONE)
	//Common to CProMoElementChildAuto
	DISP_FUNCTION(CProMoElementChildAuto, "Element", Element, VT_DISPATCH, VTS_NONE)
	//Common to CProMoDiagramChildAuto
	DISP_FUNCTION(CProMoDiagramChildAuto, "Diagram", Diagram, VT_DISPATCH, VTS_NONE)
	//Common to CProMoAppChildAuto
	DISP_FUNCTION(CProMoAppChildAuto, "Application", Application, VT_DISPATCH, VTS_NONE)
	//Default property
	DISP_PROPERTY_PARAM(CProMoPropertyAuto, "Item", GetItem, SetItem, VT_DISPATCH, VTS_VARIANT)
	DISP_DEFVALUE(CProMoPropertyAuto, "Item")
	//}}AFX_DISPATCH_MAP
END_DISPATCH_MAP()

// Note: we add support for IID_IProMoPropertyAuto to support typesafe binding
//  from VBA.  This IID must match the GUID that is attached to the 
//  dispinterface in the .ODL file.

// {38EA376B-08C3-11F1-9744-000C2976A615}
static const IID IID_IProMoPropertyAuto =
{ 0x38ea376b, 0x8c3, 0x11f1, { 0x97, 0x44, 0x0, 0xc, 0x29, 0x76, 0xa6, 0x15 } };

BEGIN_INTERFACE_MAP(CProMoPropertyAuto, CProMoElementChildAuto)
	INTERFACE_PART(CProMoPropertyAuto, IID_IProMoPropertyAuto, Dispatch)
END_INTERFACE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CProMoPropertyAuto message handlers

BSTR CProMoPropertyAuto::GetName() 
/* ============================================================
	Function :		CProMoPropertyAuto::GetName
	Description :	Returns the name of the property represented 
					by this automation object.
	Access :		Public
	Return :		BSTR	-	The name of the property represented by this
								automation object, or an empty string if the
								automation object is not attached to any property.
	Parameters :	none
	============================================================ */
{
	CString strResult;
	
	if (GetProperty()) {
		strResult = GetProperty()->GetName();
	}

	return strResult.AllocSysString();
}

void CProMoPropertyAuto::SetName(LPCTSTR lpszNewValue)
/* ============================================================
	Function :		CProMoElementAuto::SetName
	Description :	Set the name of this property. This property
					is read-only, so this function simply raises
					an exception.
	Access :		Public
	Return :		void
	Parameters :	LPCTSTR lpszNewValue	-	the new name of this
												property
   ============================================================ */

{
	SetNotSupported();

}

BOOL CProMoPropertyAuto::IsReadOnly()
/* ============================================================
	Function :		CProMoPropertyAuto::IsReadOnly
	Description :	Returns whether the property represented by this
					automation object is read-only.
	Access :		Public

	Return :		BOOL	-	"TRUE" if the property is read-only,
								"FALSE"	otherwise.
	Parameters :	none
	============================================================ */
{
	if (GetProperty()) {
		return GetProperty()->IsReadOnly();
	}

	return TRUE;
}

long CProMoPropertyAuto::GetType() 
/* ============================================================
	Function :		CProMoPropertyAuto::GetType
	Description :	Returns the data type of the property 
					represented by this	automation object.
	Access :		Public

	Return :		long	-	the type of the property represented by this
								automation object.
	Parameters :	none
	============================================================ */
{
	if (GetProperty()) {
		return GetProperty()->GetType();
	}

	return 0;
}

void CProMoPropertyAuto::SetType(long nNewValue)
/* ============================================================
	Function :		CProMoPropertyAuto::SetType
	Description :	Set the data type of this property. This property
					is read-only, so this function simply raises
					an exception.
	Access :		Public

	Return :		void
	Parameters :	long nNewValue	-	the new type of this property
   ============================================================ */
{
	SetNotSupported();

}

LPDISPATCH CProMoPropertyAuto::Label() 
/* ============================================================
	Function :		CProMoPropertyAuto::Label
	Description :	Returns the label that displays the value of
					the property represented by this automation 
					object, if any.
	Access :		Public

	Return :		LPDISPATCH	-	A dispatch interface to the label
									associated with the property represented
									by this automation object, or NULL if
									the property has no label or if the
									automation object is not attached to
									any property.
	Parameters :	none
   ============================================================ */
{
	if (GetProperty() && GetModel()) {
		CObArray labels;
		GetModel()->GetLabels(labels);
		for (int i = 0; i < labels.GetSize(); i++) {
			CProMoLabel* label = dynamic_cast<CProMoLabel*>(labels.GetAt(i));
			if (label) {
				if (label->GetProperty() == GetProperty()) {
					CProMoLabelAuto* labelAuto = dynamic_cast<CProMoLabelAuto*>(label->GetAutomationObject());
					if (labelAuto) {
						labelAuto->SetElementAutoObject(GetElementAutoObject());
						return labelAuto->GetIDispatch(TRUE);
					}
				}
			}
		}
	}

	return NULL;
}

BOOL CProMoPropertyAuto::IsComposite() 
/* ============================================================
	Function :		CProMoPropertyAuto::IsComposite
	Description :	Returns whether the property represented by this
					automation object is composite (made of child
					properties).
	Access :		Public
	Return :		BOOL	-	"TRUE" if the property is composite,
								"FALSE"	otherwise.
	Parameters :	none
   ============================================================ */
{
	if (GetProperty()) {
		return GetProperty()->IsComposite();
	}

	return TRUE;
}

BOOL CProMoPropertyAuto::IsMultivalue() 
/* ============================================================
	Function :		CProMoPropertyAuto::IsMultivalue
	Description :	Returns whether the property represented by this
					automation object is multi-value (i.e. it can have
					multiple values, like a list).
	Access :		Public
	Return :		BOOL	-	"TRUE" if the property is multi-value,
								"FALSE"	otherwise.
	Parameters :	none
   ============================================================ */
{
	if (GetProperty()) {
		return GetProperty()->IsMultiValue();
	}

	return TRUE;
}

VARIANT CProMoPropertyAuto::GetValue() 
/* ============================================================
	Function :		CProMoPropertyAuto::GetValue
	Description :	Returns the value of the property represented by
					this automation object. This method is only
					applicable if the property is a single-value simple
					property; if the property is composite or multi-value,
					this method raises an exception.
	Access :		Public

	Return :		VARIANT	-	the value of the property represented by this
								automation object. If the automation object
								is not attached to any property, an empty
								variant is returned.
	Parameters :	none
   ============================================================ */
{
	VARIANT vaResult;
	VariantInit(&vaResult);
	
	if (GetProperty()) {
		if (IsMultivalue() || IsComposite()) {
			GetNotSupported();
		}
		else {
			CVariantWrapper varWrapper = GetProperty()->GetValue();
			VariantCopy(&vaResult, varWrapper.GetVARIANT());
		}
	}

	return vaResult;
}

void CProMoPropertyAuto::SetValue(const VARIANT FAR& newValue) 
/* ============================================================
	Function :		CProMoPropertyAuto::SetValue
	Description :	Sets the value of the property represented by this
					automation object. This method is only applicable if
					the property is a single-value simple property; if the
					property is composite or multi-value, this method raises
					an exception.
	Access :		Public

	Return :		void
	Parameters :	VARIANT FAR& newValue	-	the new value of the property
   ============================================================ */
{
	if (GetProperty()) {
		if (IsMultivalue() || IsComposite() | IsReadOnly()) {
			SetNotSupported();
			return;
		}
		CVariantWrapper varWrapper(newValue);
		GetContainer()->Snapshot();
		GetProperty()->SetValue(varWrapper);
		GetDiagramAutoObject()->NotifyChange();
	}

}

LPDISPATCH CProMoPropertyAuto::Add()
/* ============================================================
	Function :		CProMoPropertyAuto::Add
	Description :	Adds a new value to the property represented by
					this automation object and returns the automation
					object of the new value. This method is only
					applicable if the property is multi-value.
	Access :		Public

	Return :		LPDISPATCH	-	a dispatch interface to the automation
									object of the new value added to the
									property represented by this automation
									object, or NULL if the property is not
									multi-value or if the automation object
									is not attached to any property.
	Parameters :	none
   ============================================================ */
{
	if (GetProperty()) {
		if (IsMultivalue() && !IsReadOnly()) {
			GetContainer()->Snapshot();
			CProMoProperty* newProp = GetProperty()->AddChild();
			GetDiagramAutoObject()->NotifyChange();
			if (newProp) {
				CProMoPropertyAuto* newPropAuto = dynamic_cast<CProMoPropertyAuto*>(newProp->GetAutomationObject());
				if (newPropAuto) {
					newPropAuto->SetElementAutoObject(GetElementAutoObject());
					return newPropAuto->GetIDispatch(TRUE);
				}
			}
		}
	}

	return NULL;
}

BOOL CProMoPropertyAuto::Remove(short index)
/* ============================================================
	Function :		CProMoPropertyAuto::Remove
	Description :	Removes the value with the specified index from the
					property represented by this automation object. This
					method is only applicable if the property is multi-value.
	Access :		Public

	Return :		BOOL		-	"TRUE" if the value was successfully removed,
									"FALSE" if the value was not removed because
									the index was out of range, or if the property
									is not multi-value or if the automation object
									is not attached to any property.
	Parameters :	short index	-	the index of the value to remove.
   ============================================================ */
{
	if (GetProperty()) {
		if (IsMultivalue() && !IsReadOnly() && index > 0) {
			if (GetProperty()->GetChild(index - 1)) {
				GetContainer()->Snapshot();
				GetProperty()->RemoveChild(index - 1);
				GetDiagramAutoObject()->NotifyChange();
				return TRUE;
			}
		}
	}

	return FALSE;
}

LPDISPATCH CProMoPropertyAuto::GetItem(const VARIANT FAR& Item) 
/* ============================================================
	Function :		CProMoPropertyAuto::GetItem
	Description :	Returns the value with the specified index or name
					from the property represented by this automation object.
					This method is only applicable if the property is composite
					or multi-value; if the property is a single-value simple
					property, this method raises an exception.
	Access :		Public

	Return :		LPDISPATCH			-	a pointer to the IDispatch 
											interface of the value
											corresponding to the specified 
											index or name, or "NULL"
											if no value with the specified 
											index or name is found, or if
											the property is a single-value 
											simple property, or if the
											automation object is not 
											attached to any property.
	Parameters :	VARIANT FAR& Item 	-	the index or name of the 
											value to return.
   ============================================================ */
{
	if (!IsMultivalue() && !IsComposite()) {
		GetNotSupported();
		return NULL;
	}

	if (GetProperty()) {
		CVariantWrapper wrapper(Item);
		CProMoProperty* childProperty = NULL;
		if (wrapper.GetType() != VT_BSTR) {
			if (wrapper.GetInt() > 0) {
				childProperty = GetProperty()->GetChild(wrapper.GetInt() - 1);
			}
		}
		else {
			if (IsMultivalue()) {
				GetNotSupported();
				return NULL;
			}
			else
			childProperty = GetProperty()->FindChild(wrapper.GetString());
		}

		if (childProperty) {
			CProMoPropertyAuto* childPropertyAuto = dynamic_cast<CProMoPropertyAuto*>(childProperty->GetAutomationObject());
			if (childPropertyAuto) {
				childPropertyAuto->SetElementAutoObject(GetElementAutoObject());
				return childPropertyAuto->GetIDispatch(TRUE);
			}
		}
	}
	

	return NULL;
}

void CProMoPropertyAuto::SetItem(const VARIANT FAR& Item, LPDISPATCH newValue) 
/* ============================================================
	Function :		CProMoPropertyAuto::SetItem
	Description :	Sets the value with the specified index or name
					in the property represented by this automation object.
					This property is read-only, so this function simply
					raises an exception.
	Access :		Public
	Return :		void
	Parameters :	VARIANT FAR& Item 	-	the index or name of the 
											value to set.
					LPDISPATCH newValue -	a dispatch interface 
											to the new value.
   ============================================================ */
{
	SetNotSupported();

}

short CProMoPropertyAuto::Count()
/* ============================================================
	Function :		CProMoPropertyAuto::Count
	Description :	Returns the number of values contained in the
					property represented by this automation object. This
					method is only applicable if the property is composite
					or multi-value.
	Access :		Public

	Return :		short	-	the number of values contained in the
								property represented by this automation
								object, or 0 if the property is a single-value
								simple property or if the automation object is not
								attached to any property.
	Parameters :	none
   ============================================================ */
{
	if (GetProperty()) {
		return GetProperty()->GetChildrenCount();
	}

	return 0;
}

VARIANT CProMoPropertyAuto::GetChildNames()
/* ============================================================
	Function :		CProMoPropertyAuto::GetChildNames
	Description :	Returns the names of the child properties of the
					property represented by this automation object. This
					method is only applicable if the property is composite.
	Access :		Public
	Return :		VARIANT	-	a VARIANT containing a SAFEARRAY
								of BSTRs with the names of the
								child properties of the property 
								represented by this automation object.
	Parameters :	none
   ============================================================ */
{
	VARIANT vaResult;
	VariantInit(&vaResult);
	
	CStringArray names;

	if (GetProperty()) {
		GetProperty()->GetChildrenNames(names, FALSE);
	}

	HRESULT hr = CSafeArrayWrapper::CreateVariantFromCStringArray(names, vaResult);
	if (FAILED(hr))
		AfxThrowOleException(hr);

	return vaResult;
}

void CProMoPropertyAuto::SetChildNames(const VARIANT FAR& newValue) 
/* ============================================================
	Function :		CProMoPropertyAuto::SetChildNames
	Description :	Sets the names of the child properties of the
					property represented by this automation object. This
					property is read-only, so this function simply raises
					an exception.
	Access :		Public
	Return :		void
	Parameters :	VARIANT FAR& newValue	-	a VARIANT containing a SAFEARRAY
												of BSTRs with the new names of the
												child properties of the property 
												represented by this automation object.
   ============================================================ */
{
	SetNotSupported();

}
