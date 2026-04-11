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
/* ============================================================
	Function :		CProMoDiagramAutoAbs::CProMoDiagramAutoAbs
	Description :	Constructor
	Access :		Public

	Return :		void
	Parameters :	none
   ============================================================ */
{
	m_pLabels = NULL;
}

CProMoDiagramAutoAbs::~CProMoDiagramAutoAbs()
/* ============================================================
	Function :		CProMoDiagramAutoAbs::~CProMoDiagramAutoAbs
	Description :	Destructor
	Access :		Public

	Return :		void
	Parameters :	none
   ============================================================ */
{
}


CProMoLabelsAuto* CProMoDiagramAutoAbs::GetLabelsAutoObject()
/* ============================================================
	Function :		CProMoDiagramAutoAbs::GetLabelsAutoObject
	Description :	Returns a pointer to the automation object that 
					represents the collection of labels directly 
					associated to this diagram (and not to one of its 
					elements). If the automation object does not
					exist, it is created.
	Access :		Public

	Return :		CProMoLabelsAuto*	-	a pointer to the
											automation object
											that represents the
											collection of
											labels associated to
											this diagram.
	Parameters :	none
   ============================================================ */
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
/* ============================================================
	Function :		CProMoDiagramAutoAbs::ReleaseLabelsAutoObject
	Description :	Releases the automation object that represents 
					the collection of labels associated to this
					diagram, if it exists.
	Access :		Public

	Return :		void
	Parameters :	none
   ============================================================ */
{
	if (m_pLabels) {
		m_pLabels->SetDiagramAutoObject(NULL);
		m_pLabels->GetIDispatch(FALSE)->Release();
		m_pLabels = NULL;
	}
}

void CProMoDiagramAutoAbs::NotifyChange()
/* ============================================================
	Function :		CProMoDiagramAutoAbs::NotifyChange
	Description :	Notify the application that a change has been 
					made to the diagram. This method should be called
					after any change is made to the diagram, to ensure 
					that the application is aware of the change and can 
					update the user interface accordingly.
	Access :		Public
	Return :		void
	Parameters :	none
   ============================================================ */
{
	GetContainer()->SetModified(TRUE);
	RefreshWindow();
}

void CProMoDiagramAutoAbs::OnFinalRelease()
/* ============================================================
	Function :		CProMoDiagramAutoAbs::OnFinalRelease
	Description :	Release the automation object. Called when
					the last reference for an automation object
					is released. The base class will
					automatically delete the object.
	Access :		Public

	Return :		void
	Parameters :	none

	Usage:			Overridden to release the automation object 
					for the labels of this diagram, if it exists.
					The base class implementation will 
					delete the object when the application 
					automation object is released.

   ============================================================*/
{
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

void CProMoDiagramAutoAbs::Redo(short times)
/* ============================================================
	Function :		CProMoDiagramAutoAbs::Redo
	Description :	Redo the last change to the diagram. This method
					can be called multiple times to redo multiple changes.
	Access :		Public

	Return :		void
	Parameters :	short times - The number of times to redo the last change.
   ============================================================ */
{
	for (short i = 0; i < times; ++i) {
		if (GetContainer()) {
			GetContainer()->Redo();
		}
	}
	NotifyChange();
}

void CProMoDiagramAutoAbs::Undo(short times)
/* ============================================================
	Function :		CProMoDiagramAutoAbs::Undo
	Description :	Undo the last change to the diagram. This method
					can be called multiple times to undo multiple changes.
	Access :		Public

	Return :		void
	Parameters :	short times - The number of times to undo the last change.
   ============================================================ */
{
	for (short i = 0; i < times; ++i) {
		if (GetContainer()) {
			GetContainer()->Undo();
		}
	}
	NotifyChange();
}

BSTR CProMoDiagramAutoAbs::Path()
/* ============================================================
	Function :		CProMoDiagramAutoAbs::Path
	Description :	Get the file path of the diagram. If the diagram
					has not been saved, an empty string is returned.
	Access :		Public
	Return :		BSTR - The file path of the diagram.
	Parameters :	none
   ============================================================ */
{
	CString strResult;
	
	strResult = GetFilePath();
	
	return strResult.AllocSysString();
}

BSTR CProMoDiagramAutoAbs::Type()
/* ============================================================
	Function :		CProMoDiagramAutoAbs::Type
	Description :	Get the type of the diagram.
	Access :		Public

	Return :		BSTR - The type of the diagram.
	Parameters :	none
   ============================================================ */
{
	CString strResult;
	if (GetContainer()) {
		strResult = GetContainer()->GetModelType();
	}

	return strResult.AllocSysString();
}

void CProMoDiagramAutoAbs::Export(const VARIANT FAR& fileName, ExportFormat format, ExportElement scope, double zoom, short resolution)
/* ============================================================
	Function :		CProMoDiagramAutoAbs::Export
	Description :	Export the diagram to a file. The format of the 
					exported file is determined by the "format" 
					parameter, and can be either raster or metafile. 
					The "scope" parameter determines whether the entire
					diagram, only the selected elements, or only the canvas
					is exported. The "zoom" parameter determines the zoom
					level of the exported diagram (only for metafile), 
					and the "resolution" parameter determines the 
					resolution of the exported file (in dots per inch,
					only for raster).
	Access :		Public

	Return :		void
	Parameters :	VARIANT FAR& fileName	-	The name of the file 
												to export to.
					ExportFormat format		-	The format of the 
												exported file (raster
												or metafile).
					ExportElement scope		-	The scope of the
												export (entire 
												diagram, selection, 
												or canvas).
					double zoom				-	The zoom level of 
												the exported diagram.
					short resolution		-	The resolution of 
												the exported file 
												(in dots per inch).
   ============================================================ */
{
	if (GetContainer()) {
		ExportDiagram(CVariantWrapper(fileName).GetString(), format, scope, zoom, resolution);
	}
}

LPDISPATCH CProMoDiagramAutoAbs::GetElements()
/* ============================================================
	Function :		CProMoDiagramAutoAbs::GetElements
	Description :	Returns the elements collection automation object.
	Access :		Public
	Return :		LPDISPATCH	-	A dispatch interface to the 
									collection of elements in the
									diagram.
	Parameters :	none
   ============================================================ */
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
/* ============================================================
	Function :		CProMoDiagramAutoAbs::SetElements
	Description :	Sets the elements collection automation object.
					This property is read-only, so this function
					simply raises an exception.
	Access :		Public
	Return :		void
	Parameters :	LPDISPATCH newValue	-	A dispatch interface to the 
											new collection of elements in 
											the diagram (not supported).
   ============================================================ */
{
	SetNotSupported();
}

long CProMoDiagramAutoAbs::GetWidth()
/* ============================================================
	Function :		CProMoDiagramAutoAbs::GetWidth
	Description :	Gets the width of the diagram.
	Access :		Public

	Return :		long - The width of the diagram.
	Parameters :	none
   ============================================================ */
{
	if (GetContainer()) {
		return GetContainer()->GetVirtualSize().cx;
	}
	
	return 0;
}

void CProMoDiagramAutoAbs::SetWidth(long nNewValue)
/* ============================================================
	Function :		CProMoDiagramAutoAbs::SetWidth
	Description :	Sets the width of the diagram to the given value.
					The height of the diagram remains unchanged.
	Access :		Public

	Return :		void
	Parameters :	long nNewValue - The new width of the diagram.
   ============================================================ */
{
	if (GetContainer()) {
		GetContainer()->Snapshot();
		GetContainer()->SetVirtualSize(CSize(nNewValue, GetContainer()->GetVirtualSize().cy));
		NotifyChange();
	}
}

long CProMoDiagramAutoAbs::GetHeight()
/* ============================================================
	Function :		CProMoDiagramAutoAbs::GetHeight
	Description :	Gets the height of the diagram.
	Access :		Public

	Return :		long - The height of the diagram.
	Parameters :	none
   ============================================================ */
{
	if (GetContainer()) {
		return GetContainer()->GetVirtualSize().cy;
	}

	return 0;
}

void CProMoDiagramAutoAbs::SetHeight(long nNewValue)
/* ============================================================
	Function :		CProMoDiagramAutoAbs::SetHeight
	Description :	Sets the height of the diagram to the given value.
					The width of the diagram remains unchanged.
	Access :		Public

	Return :		void
	Parameters :	long nNewValue - The new height of the diagram.
   ============================================================ */
{
	if (GetContainer()) {
		GetContainer()->Snapshot();
		GetContainer()->SetVirtualSize(CSize(GetContainer()->GetVirtualSize().cx, nNewValue));
		NotifyChange();
	}
}

void CProMoDiagramAutoAbs::Save(BOOL noPrompt)
/* ============================================================
	Function :		CProMoDiagramAutoAbs::Save
	Description :	Saves the diagram. If the diagram has not been 
					saved before, or if "noPrompt" is "FALSE", the 
					user is prompted to choose a file name and 
					location to save the diagram. If "noPrompt" 
					is "TRUE" and the diagram has been saved 
					before, the diagram is saved to the 
					existing file without prompting the user.
	Access :		Public

	Return :		void
	Parameters :	BOOL noPrompt	-	Whether to prompt the user 
										for a file name and location 
										if the diagram has not been 
										saved before.
   ============================================================ */
{
	if (GetContainer()) {
		SaveDiagram(noPrompt);
	}
}

void CProMoDiagramAutoAbs::SaveAs(const VARIANT FAR& fileName)
/* ============================================================
	Function :		CProMoDiagramAutoAbs::SaveAs
	Description :	Saves the diagram to the specified file. If the 
					diagram has not been saved before, this method is 
					equivalent to calling "Save" with "noPrompt" set to
					"TRUE". If the diagram has been saved before, this 
					method saves the diagram to the specified file, and 
					the existing file is not modified.
	Access :		Public
	Return :		void
	Parameters :	VARIANT FAR& fileName	-	The name of the file 
												to save the diagram to.
   ============================================================ */
{
	if (GetContainer()) {
		SaveDiagramAs(CVariantWrapper(fileName).GetString());
	}
}

void CProMoDiagramAutoAbs::Close(BOOL saveChanges)
/* ============================================================
	Function :		CProMoDiagramAutoAbs::Close
	Description :	Closes the diagram. If "saveChanges" is "TRUE", 
					the user is prompted to save any unsaved changes to 
					the diagram before it is closed. If "saveChanges" is 
					"FALSE", the diagram is closed immediately without 
					prompting the user, and any unsaved changes are 
					discarded.
	Access :		Public
	Return :		void
	Parameters :	BOOL saveChanges	-	Whether to prompt the user 
											to save any unsaved changes 
											before closing the diagram.
   ============================================================ */
{
	if (GetContainer()) {
		if (saveChanges) {
			SaveDiagram(FALSE);
		}
		CloseDiagram();
	}
}

LPDISPATCH CProMoDiagramAutoAbs::GetLabels()
/* ============================================================
	Function :		CProMoDiagramAutoAbs::GetLabels
	Description :	Returns the labels collection automation object.
	Access :		Public
	Return :		LPDISPATCH	-	A dispatch interface to the
									collection of labels in the
									diagram.
	Parameters :	none
   ============================================================ */
{
	if (GetLabelsAutoObject())
	{
		return GetLabelsAutoObject()->GetIDispatch(TRUE);
	}
	
	return NULL;
}

void CProMoDiagramAutoAbs::SetLabels(LPDISPATCH newValue) 
/* ============================================================
	Function :		CProMoDiagramAutoAbs::SetLabels
	Description :	Sets the labels collection automation object.
					This property is read-only, so this function
					simply raises an exception.
	Access :		Public
	Return :		void
	Parameters :	LPDISPATCH newValue	-	A dispatch interface to the
											new collection of labels in
											the diagram (not supported).
   ============================================================ */
{
	SetNotSupported();

}

VARIANT CProMoDiagramAutoAbs::GetCreatableElementTypes()
/* ============================================================
	Function :		CProMoDiagramAutoAbs::GetCreatableElementTypes
	Description :	Gets the list of creatable element types in the diagram.
					The list is returned as a variant containing a safe array
					of strings, where each string is the name of a creatable
					element type. The actual element types that are creatable
					depend on the specific application and diagram type, and 
					are determined by the container of the diagram.
	Access :		Public
	Return :		VARIANT	-	A variant containing a safe array of strings,
								where each string is the name of a creatable
								element type in the diagram.
	Parameters :	none
   ============================================================ */
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
/* ============================================================
	Function :		CProMoDiagramAutoAbs::SetCreatableElementTypes
	Description :	Sets the list of creatable element types in the diagram.
					This property is read-only, so this function simply raises
					an exception.
	Access :		Public
	Return :		void
	Parameters :	VARIANT FAR& newValue	-	A variant containing a 
												safe array of strings,
												where each string is 
												the name of a creatable
												element type in the 
												diagram (not supported).
   ============================================================ */
{
	SetNotSupported();

}
