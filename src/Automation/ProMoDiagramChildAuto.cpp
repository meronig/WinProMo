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
/* ============================================================
	Function :		CProMoDiagramChildAuto::CProMoDiagramChildAuto
	Description :	Constructor
	Access :		Public

	Return :		void
	Parameters :	none
   ============================================================*/
{
	m_pDiagramAuto = NULL;
}

void CProMoDiagramChildAuto::OnFinalRelease()
/* ============================================================
	Function :		CProMoDiagramChildAuto::OnFinalRelease
	Description :	Release the automation object. Called when
					the last reference for an automation object
					is released. The base class will
					automatically delete the object.
	Access :		Public

	Return :		void
	Parameters :	none

	Usage:			Overridden to release the diagram automation 
					object by setting it to NULL.

   ============================================================*/
{
	SetDiagramAutoObject(NULL);
	CProMoAppChildAuto::OnFinalRelease();
}

CProMoDiagramAutoAbs* CProMoDiagramChildAuto::GetDiagramAutoObject() const
/* ============================================================
	Function :		CProMoDiagramChildAuto::GetDiagramAutoObject
	Description :	Returns the diagram automation object.
	Access :		Public

	Return :		CProMoDiagramAutoAbs*	-	The diagram 
												automation object.
	Parameters :	none
   ============================================================*/
{
	return m_pDiagramAuto;
}

void CProMoDiagramChildAuto::SetDiagramAutoObject(CProMoDiagramAutoAbs* pDiagramAuto)
/* ============================================================
	Function :		CProMoDiagramChildAuto::SetDiagramAutoObject
	Description :	Sets the diagram automation object to the 
					object passed as a parameter. If the new object 
					is different from the current one, the reference 
					count of the old object is released and the new 
					object is AddRef'ed.
	Access :		Public

	Return :		void
	Parameters :	CProMoDiagramAutoAbs* pDiagramAuto	-	The diagram 
															automation 
															object to set.
   ============================================================*/
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
/* ============================================================
	Function :		CProMoDiagramChildAuto::ThrowIfNoDiagramAutoObject
	Description :	Checks if the diagram automation object is 
					available, and if not, throws an OLE exception.
	Access :		Public

	Return :		void
	Parameters :	none
   ============================================================*/
{
	
	if (!m_pDiagramAuto) {
		//TODO: consider a more specific error code and message
		AfxThrowOleException(E_FAIL);
	}
}

CProMoEntityContainer* CProMoDiagramChildAuto::GetContainer() 
/* ============================================================
	Function :		CProMoDiagramChildAuto::GetContainer
	Description :	Returns the container of the diagram, which is 
					used to manage the elements of the diagram.
	Access :		Public

	Return :		CProMoEntityContainer*
					The container of the diagram, or "NULL" if the 
					diagram automation object is not set.
	Parameters :	none
   ============================================================*/
{
	ThrowIfNoDiagramAutoObject();

	if (m_pDiagramAuto) {
		return m_pDiagramAuto->GetContainer();
	}
	return NULL;
}

CProMoModel* CProMoDiagramChildAuto::FindModel(const VARIANT& Item, const CObArray& collection)
/* ============================================================
	Function :		CProMoDiagramChildAuto::FindModel
	Description :	Finds a model in the given collection based on 
					the specified item, which can be either the index 
					of the model in the collection or the name of the 
					model.
	Access :		Protected

	Return :		CProMoModel*			-	A pointer to the 
												model found, or 
												"NULL" if no model 
												matching the 
												specified item is 
												found.
	Parameters :	VARIANT& Item 			-	the index or name 
												of the model to find.
					CObArray& collection	-	the collection of 
												models to search.
   ============================================================*/
{
	CVariantWrapper wrapper(Item);
	CProMoModel* pModel = NULL;

	if (wrapper.GetType() != VT_BSTR) {
		if (wrapper.GetInt() > 0 && wrapper.GetInt() <= collection.GetSize()) {
			pModel = dynamic_cast<CProMoModel*>(collection.GetAt(wrapper.GetInt() - 1));
		}
	}
	else {
		pModel = dynamic_cast<CProMoModel*>(CProMoEntityContainer::GetNamedModel(collection, wrapper.GetString()));
	}

	return pModel;
}

CProMoDiagramChildAuto::~CProMoDiagramChildAuto()
/* ============================================================
	Function :		CProMoDiagramChildAuto::~CProMoDiagramChildAuto
	Description :	Destructor
	Access :		Protected

	Return :		void
	Parameters :	none
   ============================================================*/
{
}

BEGIN_MESSAGE_MAP(CProMoDiagramChildAuto, CProMoAppChildAuto)
	//{{AFX_MSG_MAP(CProMoDiagramChildAuto)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

BEGIN_DISPATCH_MAP(CProMoDiagramChildAuto, CProMoAppChildAuto)
	//{{AFX_DISPATCH_MAP(CProMoDiagramChildAuto)
	//}}AFX_DISPATCH_MAP
END_DISPATCH_MAP()

BEGIN_INTERFACE_MAP(CProMoDiagramChildAuto, CProMoAppChildAuto)
END_INTERFACE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CProMoDiagramChildAuto message handlers


LPDISPATCH CProMoDiagramChildAuto::Diagram()
/* ============================================================
	Function :		CProMoDiagramChildAuto::Diagram
	Description :	Returns the diagram automation object.
	Access :		Public
	Return :		LPDISPATCH			-	a pointer to the 
											IDispatch interface 
											of the diagram 
											automation object, 
											or "NULL" if no
											object is set.
	Parameters :	none
   ============================================================*/
{
	if (m_pDiagramAuto) {
		return m_pDiagramAuto->GetIDispatch(TRUE);
	}
	return NULL;
}


