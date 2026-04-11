/* ==========================================================================

	Copyright © 2026 Technical University of Denmark

	CProMoSubBlocksAuto

	Author :		Giovanni Meroni

	Purpose :		"CProMoSubBlocksAuto" is an automation object that
					represents the collection of subblocks in a block. It
					provides methods to access the subblocks, to add new
					subblocks, and to unlink existing subblocks.

	Description :	"CProMoSubBlocksAuto" provides the implementation
					of the methods and properties that are common to all
					subblocks collections.

   ========================================================================*/
#include "stdafx.h"
#include "ProMoSubBlocksAuto.h"
#include "../ProMoEditor/ProMoBlockModel.h"
#include "../FileUtils/SafeArrayWrapper.h"
#include "ProMoBlockAuto.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CProMoSubBlocksAuto

IMPLEMENT_DYNCREATE(CProMoSubBlocksAuto, CProMoBlockChildAuto)

CProMoSubBlocksAuto::CProMoSubBlocksAuto()
/* ============================================================
	Function :		CProMoSubBlocksAuto::CProMoSubBlocksAuto
	Description :	Constructor
	Access :		Public

	Return :		void
	Parameters :	none
	============================================================ */
{
}

CProMoSubBlocksAuto::~CProMoSubBlocksAuto()
/* ============================================================
	Function :		CProMoSubBlocksAuto::~CProMoSubBlocksAuto
	Description :	Destructor
	Access :		Public

	Return :		void
	Parameters :	none
	============================================================ */
{
}

void CProMoSubBlocksAuto::SetElementAutoObject(CProMoElementAuto* pElementAuto) 
/* ============================================================
	Function :		CProMoSubBlocksAuto::SetElementAutoObject
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

BEGIN_MESSAGE_MAP(CProMoSubBlocksAuto, CProMoBlockChildAuto)
	//{{AFX_MSG_MAP(CProMoSubBlocksAuto)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

BEGIN_DISPATCH_MAP(CProMoSubBlocksAuto, CProMoBlockChildAuto)
	//{{AFX_DISPATCH_MAP(CProMoSubBlocksAuto)
	DISP_PROPERTY_EX(CProMoSubBlocksAuto, "IDs", GetIDs, SetIDs, VT_VARIANT)
	DISP_FUNCTION(CProMoSubBlocksAuto, "Count", Count, VT_I2, VTS_NONE)
	DISP_FUNCTION(CProMoSubBlocksAuto, "Add", Add, VT_BOOL, VTS_DISPATCH)
	DISP_FUNCTION(CProMoSubBlocksAuto, "Remove", Remove, VT_BOOL, VTS_VARIANT)
	//Common to CProMoElementChildAuto
	DISP_FUNCTION(CProMoElementChildAuto, "Element", Element, VT_DISPATCH, VTS_NONE)
	//Common to CProMoDiagramChildAuto
	DISP_FUNCTION(CProMoDiagramChildAuto, "Diagram", Diagram, VT_DISPATCH, VTS_NONE)
	//Common to CProMoAppChildAuto
	DISP_FUNCTION(CProMoAppChildAuto, "Application", Application, VT_DISPATCH, VTS_NONE)
	//Default property
	DISP_PROPERTY_PARAM(CProMoSubBlocksAuto, "Item", GetItem, SetItem, VT_DISPATCH, VTS_VARIANT)
	DISP_DEFVALUE(CProMoSubBlocksAuto, "Item")
	//}}AFX_DISPATCH_MAP
END_DISPATCH_MAP()

// Note: we add support for IID_IProMoSubBlocksAuto to support typesafe binding
//  from VBA.  This IID must match the GUID that is attached to the 
//  dispinterface in the .ODL file.

// {38EA376C-08C3-11F1-9744-000C2976A615}
static const IID IID_IProMoSubBlocksAuto =
{ 0x38ea376c, 0x8c3, 0x11f1, { 0x97, 0x44, 0x0, 0xc, 0x29, 0x76, 0xa6, 0x15 } };

BEGIN_INTERFACE_MAP(CProMoSubBlocksAuto, CProMoBlockChildAuto)
	INTERFACE_PART(CProMoSubBlocksAuto, IID_IProMoSubBlocksAuto, Dispatch)
END_INTERFACE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CProMoSubBlocksAuto message handlers

short CProMoSubBlocksAuto::Count()
/* ============================================================
	Function :		CProMoSubBlocksAuto::Count
	Description :	Returns the number of subblocks in the collection.
	Access :		Public

	Return :		short	-	The number of subblocks in the collection.
	Parameters :	none
	============================================================ */
{
	if (GetBlockModel()) {
		CObArray subBlocks;
		GetBlockModel()->GetSubBlocks(subBlocks);
		return subBlocks.GetSize();
	}

	return 0;
}

LPDISPATCH CProMoSubBlocksAuto::GetItem(const VARIANT FAR& item) 
/* ============================================================
	Function :		CProMoSubBlocksAuto::GetItem
	Description :	Returns the block automation object corresponding
					to the specified index or name.
	Access :		Public
	Return :		LPDISPATCH			-	a pointer to the
											IDispatch interface
											of the block
											automation object
											corresponding to the
											specified index or name,
											or "NULL" if no block
											with the specified index
											or name is found.
	Parameters :	VARIANT FAR& Item 	-	the index or name of the
											block to return.
   ============================================================ */
{
	if (GetBlockModel()) {
		CObArray subBlocks;
		GetBlockModel()->GetSubBlocks(subBlocks);
		CProMoBlockModel* pModel = dynamic_cast<CProMoBlockModel*>(FindModel(item, subBlocks));
		
		if (pModel) {
			CProMoElementAuto* pElementAuto = dynamic_cast<CProMoElementAuto*>(pModel->GetAutomationObject());
			if (pElementAuto) {
				pElementAuto->SetDiagramAutoObject(GetDiagramAutoObject());
				return pElementAuto->GetIDispatch(TRUE);
			}
		}
	}

	return NULL;
}

void CProMoSubBlocksAuto::SetItem(const VARIANT FAR& Item, LPDISPATCH newValue) 
/* ============================================================
	Function :		CProMoSubBlocksAuto::SetItem
	Description :	Sets the block automation object corresponding
					to the specified index or name. This property is
					read-only, so this function simply raises an
					exception.
	Access :		Public
	Return :		void
	Parameters :	VARIANT FAR& Item 	-	the index or name of the
											block to set.
					LPDISPATCH newValue	-	a pointer to the new
											IDispatch interface of the
											block automation object to
											set for the specified index or
											name.
   ============================================================ */
{
	SetNotSupported();

}

BOOL CProMoSubBlocksAuto::Add(LPDISPATCH item) 
/* ============================================================
	Function :		CProMoSubBlocksAuto::Add
	Description :	Adds a block to the collection. The block to add
					is specified by passing a pointer to its automation
					object's IDispatch interface as a parameter. The block
					is added as a subblock of the block associated to the
					current automation object.
	Access :		Public
	Return :		BOOL			-	"TRUE" if the block is successfully added
										to the collection, "FALSE" otherwise.
	Parameters :	LPDISPATCH item -	a pointer to the IDispatch interface of
										the block automation object corresponding
										to the block to add to the collection.
   ============================================================ */
{
	if (GetBlockModel()) {
		if (item) {
			CProMoBlockModel* pBlockModel = CProMoBlockAuto::GetModelFromIDispatch(item);
			CProMoBlockView* pBlockView = pBlockModel->GetMainBlockView();
			// a valid block is passed
			if (pBlockModel) {
				// check if the parent block has changed
				if (GetBlockModel() != pBlockModel->GetParentBlock() || !pBlockModel->IsSubBlock()) {
					// check if the block can be nested
					if (pBlockModel->CanBeSubBlockOf(GetBlockModel())) {
						GetContainer()->Snapshot();
						// disconnect from old parent block (if any)
						pBlockView->UnlinkFromParent();
						CProMoBlockView* pParentView = GetBlockModel()->GetMainBlockView();
						CRect parentBlockRect = pParentView->GetRect();
						CRect blockRect = pBlockView->GetRect();
						if (!parentBlockRect.PtInRect(blockRect.TopLeft())) {
							// move child block at the top-left of the parent
							//pBlockView->SetRect(parentBlockRect.left + 5, parentBlockRect.top + 5, parentBlockRect.left + 5 + blockRect.Width(), parentBlockRect.top + 5 + blockRect.Height());
						}
						pParentView->LinkSubBlock(pBlockView);
						pParentView->AutoResize();
						GetDiagramAutoObject()->NotifyChange();
						return TRUE;
					}
				}
			}
		}
	}
	
	return FALSE;
}

BOOL CProMoSubBlocksAuto::Remove(const VARIANT FAR& item) 
/* ============================================================
	Function :		CProMoSubBlocksAuto::Remove
	Description :	Removes a block from the collection. The block to remove
					is specified by passing its index or name as a parameter.
					The block is removed from being a subblock of the block
					represented by the current automation object, and becomes
					a top-level block in the diagram.
	Access :		Public
	Return :		BOOL				-	"TRUE" if the block is 
											successfully removed
											from the collection, 
											"FALSE" otherwise.
	Parameters :	VARIANT FAR& Item 	-	the index or name of 
											the block to remove 
											from the collection.
   ============================================================ */
{
	if (GetBlockModel()) {
		CObArray subBlocks;
		GetBlockModel()->GetSubBlocks(subBlocks);
		CProMoBlockModel* pModel = dynamic_cast<CProMoBlockModel*>(FindModel(item, subBlocks));
		
		if (pModel) {
			CProMoBlockView* pView = pModel->GetMainBlockView();
			if (pView) {
				GetContainer()->Snapshot();
				pView->UnlinkFromParent();
				GetDiagramAutoObject()->NotifyChange();
				return TRUE;
			}
		}
	}

	return FALSE;
}

VARIANT CProMoSubBlocksAuto::GetIDs()
/* ============================================================
	Function :		CProMoSubBlocksAuto::GetIDs
	Description :	Returns a SAFEARRAY of VARIANT containing the names
					of the sub-blocks in the collection.
	Access :		Public

	Return :		VARIANT	-	a VARIANT containing a SAFEARRAY 
								of BSTRs with the names of the 
								sub-blocks in the collection.
	Parameters :	none
   ============================================================ */
{
	VARIANT vaResult;
	VariantInit(&vaResult);

	if (GetBlockModel()) {

		CStringArray names;
		CObArray subBlocks;
		CProMoBlockModel* pModel = NULL;
		GetBlockModel()->GetSubBlocks(subBlocks);
		for (int i = 0; i < subBlocks.GetSize(); i++) {
			pModel = dynamic_cast<CProMoBlockModel*>(subBlocks.GetAt(i));
			if (pModel) {
				names.Add(pModel->GetName());
			}
		}

		HRESULT hr = CSafeArrayWrapper::CreateVariantFromCStringArray(names, vaResult);
		if (FAILED(hr))
			AfxThrowOleException(hr);
	}

	return vaResult;
}

void CProMoSubBlocksAuto::SetIDs(const VARIANT FAR& newValue) 
/* ============================================================
	Function :		CProMoSubBlocksAuto::SetIDs
	Description :	Sets the list of the names of the sub-blocks.
					This property is read-only, so this function simply
					raises an exception.
	Access :		Public

	Return :		void
	Parameters :	VARIANT FAR& newValue	-	a VARIANT containing
												a safe array of
												BSTRs with the
												names of the sub-blocks
												to set.
   ============================================================ */
{
	SetNotSupported();
}
