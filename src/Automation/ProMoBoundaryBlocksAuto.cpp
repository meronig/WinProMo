/* ==========================================================================

	Copyright © 2026 Technical University of Denmark

	CProMoBoundaryBlocksAuto

	Author :		Giovanni Meroni

	Purpose :		"CProMoBoundaryBlocksAuto" is an automation object that 
					represents the collection of boundary blocks in a block. It
					provides methods to access the boundary blocks, to add new
					boundary blocks, and to remove existing boundary blocks.

	Description :	"CProMoBoundaryBlocksAuto" provides the implementation 
					of the methods and properties that are common to all boundary
					blocks collections.

   ========================================================================*/
#include "stdafx.h"
#include "ProMoBoundaryBlocksAuto.h"
#include "../ProMoEditor/ProMoBlockModel.h"
#include "../FileUtils/SafeArrayWrapper.h"
#include "ProMoBlockAuto.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CProMoBoundaryBlocksAuto

IMPLEMENT_DYNCREATE(CProMoBoundaryBlocksAuto, CProMoBlockChildAuto)

CProMoBoundaryBlocksAuto::CProMoBoundaryBlocksAuto()
{
}

CProMoBoundaryBlocksAuto::~CProMoBoundaryBlocksAuto()
{
}

void CProMoBoundaryBlocksAuto::SetElementAutoObject(CProMoElementAuto* pElementAuto) {
	SetDiagramAutoObject(pElementAuto ? pElementAuto->GetDiagramAutoObject() : NULL);
	m_pElementAuto = pElementAuto;
}


BEGIN_MESSAGE_MAP(CProMoBoundaryBlocksAuto, CProMoBlockChildAuto)
	//{{AFX_MSG_MAP(CProMoBoundaryBlocksAuto)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

BEGIN_DISPATCH_MAP(CProMoBoundaryBlocksAuto, CProMoBlockChildAuto)
	//{{AFX_DISPATCH_MAP(CProMoBoundaryBlocksAuto)
	DISP_PROPERTY_EX(CProMoBoundaryBlocksAuto, "IDs", GetIDs, SetIDs, VT_VARIANT)
	DISP_FUNCTION(CProMoBoundaryBlocksAuto, "Count", Count, VT_I2, VTS_NONE)
	DISP_FUNCTION(CProMoBoundaryBlocksAuto, "Add", Add, VT_BOOL, VTS_DISPATCH VTS_I4)
	DISP_FUNCTION(CProMoBoundaryBlocksAuto, "Remove", Remove, VT_BOOL, VTS_VARIANT)
	DISP_PROPERTY_PARAM(CProMoBoundaryBlocksAuto, "Item", GetItem, SetItem, VT_DISPATCH, VTS_VARIANT)
	DISP_DEFVALUE(CProMoBoundaryBlocksAuto, "Item")
	//Common to CProMoElementChildAuto
	DISP_FUNCTION(CProMoElementChildAuto, "Element", Element, VT_DISPATCH, VTS_NONE)
	//Common to CProMoDiagramChildAuto
	DISP_FUNCTION(CProMoDiagramChildAuto, "Diagram", Diagram, VT_DISPATCH, VTS_NONE)
	//Common to CProMoAppChildAuto
	DISP_FUNCTION(CProMoAppChildAuto, "Application", Application, VT_DISPATCH, VTS_NONE)
	//}}AFX_DISPATCH_MAP
END_DISPATCH_MAP()

// Note: we add support for IID_IProMoBoundaryBlocksAuto to support typesafe binding
//  from VBA.  This IID must match the GUID that is attached to the 
//  dispinterface in the .ODL file.

// {38EA3761-08C3-11F1-9744-000C2976A615}
static const IID IID_IProMoBoundaryBlocksAuto =
{ 0x38ea3761, 0x8c3, 0x11f1, { 0x97, 0x44, 0x0, 0xc, 0x29, 0x76, 0xa6, 0x15 } };

BEGIN_INTERFACE_MAP(CProMoBoundaryBlocksAuto, CProMoBlockChildAuto)
	INTERFACE_PART(CProMoBoundaryBlocksAuto, IID_IProMoBoundaryBlocksAuto, Dispatch)
END_INTERFACE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CProMoBoundaryBlocksAuto message handlers

BOOL CProMoBoundaryBlocksAuto::Add(LPDISPATCH item, short attachment) 
{
	if (GetBlockModel()) {
		if (item) {
			CProMoBlockModel* pBlockModel = CProMoBlockAuto::GetModelFromIDispatch(item);
			CProMoBlockView* pBlockView = pBlockModel->GetMainBlockView();
			// a valid block is passed
			if (pBlockModel) {
				// check if the parent block has changed
				if (GetBlockModel() != pBlockModel->GetParentBlock() || !pBlockModel->IsBoundaryBlock()) {
					// check if the block can be attached to boundary
					if (pBlockModel->CanBeBoundaryOf(GetBlockModel(), attachment)) {
						GetContainer()->Snapshot();
						// disconnect from old parent block (if any)
						pBlockView->UnlinkFromParent();
						CProMoBlockView* pParentView = GetBlockModel()->GetMainBlockView();
						// TODO REVISE
						CRect parentBlockRect = pParentView->GetRect();
						CRect blockRect = pBlockView->GetRect();
						CRect intersection;
						intersection.IntersectRect(parentBlockRect, blockRect);

						if (intersection.IsRectEmpty()) {
							switch (attachment) {
							case DEHT_TOP:
								pBlockView->SetRect(parentBlockRect.CenterPoint().x, parentBlockRect.top - 5, parentBlockRect.CenterPoint().x + blockRect.Width(), parentBlockRect.top - 5 + blockRect.Height());
								break;
							case DEHT_BOTTOM:
								pBlockView->SetRect(parentBlockRect.CenterPoint().x, parentBlockRect.bottom - 5, parentBlockRect.CenterPoint().x + blockRect.Width(), parentBlockRect.bottom - 5 + blockRect.Height());
								break;
							case DEHT_LEFT:
								pBlockView->SetRect(parentBlockRect.left - 5, parentBlockRect.CenterPoint().y, parentBlockRect.left - 5 + blockRect.Width(), parentBlockRect.CenterPoint().y + blockRect.Height());
								break;
							case DEHT_RIGHT:
								pBlockView->SetRect(parentBlockRect.right - 5, parentBlockRect.CenterPoint().y, parentBlockRect.right - 5 + blockRect.Width(), parentBlockRect.CenterPoint().y + blockRect.Height());
								break;
							}
						}

						pParentView->LinkBoundaryBlock(pBlockView, attachment);
						GetDiagramAutoObject()->NotifyChange();
						return TRUE;
					}
				}
			}
		}
	}

	return FALSE;
}

short CProMoBoundaryBlocksAuto::Count() 
{
	if (GetBlockModel()) {
		CObArray boundaryBlocks;
		GetBlockModel()->GetBoundaryBlocks(boundaryBlocks, DEHT_BODY);
		return boundaryBlocks.GetSize();
	}

	return 0;
}

BOOL CProMoBoundaryBlocksAuto::Remove(const VARIANT FAR& item) 
{
	if (GetBlockModel()) {
		CObArray boundaryBlocks;
		GetBlockModel()->GetBoundaryBlocks(boundaryBlocks, DEHT_BODY);
		CProMoBlockModel* pModel = dynamic_cast<CProMoBlockModel*>(FindModel(item, boundaryBlocks));

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

LPDISPATCH CProMoBoundaryBlocksAuto::GetItem(const VARIANT FAR& item) 
{
	if (GetBlockModel()) {
		CObArray boundaryBlocks;
		GetBlockModel()->GetBoundaryBlocks(boundaryBlocks, DEHT_BODY);
		CProMoBlockModel* pModel = dynamic_cast<CProMoBlockModel*>(FindModel(item, boundaryBlocks));

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

void CProMoBoundaryBlocksAuto::SetItem(const VARIANT FAR& Item, LPDISPATCH newValue) 
{
	SetNotSupported();

}

VARIANT CProMoBoundaryBlocksAuto::GetIDs() 
{
	VARIANT vaResult;
	VariantInit(&vaResult);

	if (GetBlockModel()) {

		CStringArray names;
		CObArray boundaryBlocks;
		CProMoBlockModel* pModel = NULL;
		GetBlockModel()->GetBoundaryBlocks(boundaryBlocks,DEHT_BODY);
		for (int i = 0; i < boundaryBlocks.GetSize(); i++) {
			pModel = dynamic_cast<CProMoBlockModel*>(boundaryBlocks.GetAt(i));
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

void CProMoBoundaryBlocksAuto::SetIDs(const VARIANT FAR& newValue) 
{
	SetNotSupported();

}
