/* ==========================================================================

	Copyright © 2026 Technical University of Denmark

	CProMoBlockAuto

	Author :		Giovanni Meroni

	Purpose :		"CProMoBlockAuto" is an automation object that
					represents a block in a diagram. It provides methods
					to access the sub-blocks, the boundary blocks, the 
					incoming edges, and the outgoing edges of the block, to 
					change its visual appearance (fill color, fill pattern, 
					etc.), and to move and resize it.

	Description :	"CProMoBlockAuto" provides the implementation of the
					methods and properties that are common to all blocks.

   ========================================================================*/
#include "stdafx.h"
#include "ProMoBlockAuto.h"
#include "ProMoSubBlocksAuto.h"
#include "ProMoBoundaryBlocksAuto.h"
#include "ProMoIncomingEdgesAuto.h"
#include "ProMoOutgoingEdgesAuto.h"
#include "../GeometryUtils/GeometryHelper.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CProMoBlockAuto

IMPLEMENT_DYNCREATE(CProMoBlockAuto, CProMoElementAuto)

CProMoBlockAuto::CProMoBlockAuto()
/* ============================================================
	Function :		CProMoBlockAuto::CProMoBlockAuto
	Description :	Constructor
	Access :		Public

	Return :		void
	Parameters :	none
   ============================================================*/
{
	m_pSubBlocks = NULL;
	m_pBoundaryBlocks = NULL;
	m_pIncomingEdges = NULL;
	m_pOutgoingEdges = NULL;
}

CProMoBlockAuto::~CProMoBlockAuto()
/* ============================================================
	Function :		CProMoBlockAuto::~CProMoBlockAuto
	Description :	Destructor
	Access :		Public

	Return :		void
	Parameters :	none
   ============================================================*/
{
}

CProMoBlockModel* CProMoBlockAuto::GetBlockModel() 
/* ============================================================
	Function :		CProMoBlockAuto::GetBlockModel
	Description :	Returns a pointer to the block model represented 
					by this	automation object.
	Access :		Public
	
	Return :		CProMoBlockModel*	-	a pointer to the block 
											model represented by 
											this automation object,
											or "NULL" if the model
											is not of the expected 
											type.
	Parameters :	none
   ============================================================*/
{
	return dynamic_cast<CProMoBlockModel*>(GetModel());
}

CProMoBlockView* CProMoBlockAuto::GetMainBlockView()
/* ============================================================
	Function :		CProMoBlockAuto::GetMainBlockView
	Description :	Returns a pointer to the main block view 
					associated with the block model represented by 
					this automation object.
	Access :		Public
	
	Return :		CProMoBlockView*	-	a pointer to the main block 
											view associated with the 
											block model represented by 
											this automation object, or
											"NULL" if there is no 
											main block view.
	Parameters :	none
   ============================================================*/
{
	if (GetBlockModel()) {
		return GetBlockModel()->GetMainBlockView();
	}

	return NULL;
}

CProMoSubBlocksAuto* CProMoBlockAuto::GetSubBlocksAutoObject()
/* ============================================================
	Function :		CProMoBlockAuto::GetSubBlocksAutoObject
	Description :	Returns a pointer to the automation object that 
					represents the collection of sub-blocks contained
					in this block. If the automation object does not
					exist, it is created.
	Access :		Public
	
	Return :		CProMoSubBlocksAuto*	-	a pointer to the 
												automation object 
												that represents the 
												collection of 
												sub-blocks contained 
												in this block.
	Parameters :	none
   ============================================================*/
{
	ThrowIfDetached();
	ThrowIfNoDiagramAutoObject();
	
	if (!m_pSubBlocks) {
		m_pSubBlocks = new CProMoSubBlocksAuto();
		if (m_pSubBlocks) {
			m_pSubBlocks->SetElementAutoObject(this);
		}
	}
	return m_pSubBlocks;
}

void CProMoBlockAuto::ReleaseSubBlocksAutoObject()
/* ============================================================
	Function :		CProMoBlockAuto::ReleaseSubBlocksAutoObject
	Description :	Releases the automation object that represents 
					the collection of sub-blocks contained in this 
					block, if it exists.
	Access :		Public
	
	Return :		void
	Parameters :	none
   ============================================================*/
{
	if (m_pSubBlocks) {
		m_pSubBlocks->SetElementAutoObject(NULL);
		m_pSubBlocks->GetIDispatch(FALSE)->Release();
		m_pSubBlocks = NULL;
	}
}

CProMoBoundaryBlocksAuto* CProMoBlockAuto::GetBoundaryBlocksAutoObject()
/* ============================================================
	Function :		CProMoBlockAuto::GetBoundaryBlocksAutoObject
	Description :	Returns a pointer to the automation object that 
					represents the collection of boundary blocks 
					contained in this block. If the automation object 
					does not exist, it is created.
	Access :		Public
	
	Return :		CProMoBoundaryBlocksAuto*	-	a pointer to the 
													automation object 
													that represents the 
													collection of 
													boundary blocks 
													contained in this 
													block.
	Parameters :	none
   ============================================================*/
{
	ThrowIfDetached();
	ThrowIfNoDiagramAutoObject();
	
	if (!m_pBoundaryBlocks) {
		m_pBoundaryBlocks = new CProMoBoundaryBlocksAuto();
		if (m_pBoundaryBlocks) {
			m_pBoundaryBlocks->SetElementAutoObject(this);
		}
	}
	return m_pBoundaryBlocks;
}

void CProMoBlockAuto::ReleaseBoundaryBlocksAutoObject()
/* ============================================================
	Function :		CProMoBlockAuto::ReleaseBoundaryBlocksAutoObject
	Description :	Releases the automation object that represents 
					the collection of boundary blocks contained in this 
					block, if it exists.
	Access :		Public
	
	Return :		void
	Parameters :	none
   ============================================================*/
{
	if (m_pBoundaryBlocks) {
		m_pBoundaryBlocks->SetElementAutoObject(NULL);
		m_pBoundaryBlocks->GetIDispatch(FALSE)->Release();
		m_pBoundaryBlocks = NULL;
	}
}

CProMoIncomingEdgesAuto* CProMoBlockAuto::GetIncomingEdgesAutoObject()
/* ============================================================
	Function :		CProMoBlockAuto::GetIncomingEdgesAutoObject
	Description :	Returns a pointer to the automation object that 
					represents the collection of incoming edges 
					connected to this block. If the automation object 
					does not exist, it is created.
	Access :		Public
	
	Return :		CProMoIncomingEdgesAuto*	-	a pointer to the 
													automation object 
													that represents the 
													collection of 
													incoming edges 
													connected to this 
													block.
	Parameters :	none
   ============================================================*/
{
	ThrowIfDetached();
	ThrowIfNoDiagramAutoObject();
	
	if (!m_pIncomingEdges) {
		m_pIncomingEdges = new CProMoIncomingEdgesAuto();
		if (m_pIncomingEdges) {
			m_pIncomingEdges->SetElementAutoObject(this);
		}
	}
	return m_pIncomingEdges;
}

void CProMoBlockAuto::ReleaseIncomingEdgesAutoObject()
/* ============================================================
	Function :		CProMoBlockAuto::ReleaseIncomingEdgesAutoObject
	Description :	Releases the automation object that represents 
					the collection of incoming edges connected to this 
					block, if it exists.
	Access :		Public
	
	Return :		void
	Parameters :	none
   ============================================================*/
{
	if (m_pIncomingEdges) {
		m_pIncomingEdges->SetElementAutoObject(NULL);
		m_pIncomingEdges->GetIDispatch(FALSE)->Release();
		m_pIncomingEdges = NULL;
	}
}

CProMoOutgoingEdgesAuto* CProMoBlockAuto::GetOutgoingEdgesAutoObject()
/* ============================================================
	Function :		CProMoBlockAuto::GetOutgoingEdgesAutoObject
	Description :	Returns a pointer to the automation object that 
					represents the collection of outgoing edges 
					connected to this block. If the automation object 
					does not exist, it is created.
	Access :		Public
	
	Return :		CProMoOutgoingEdgesAuto*	-	a pointer to the 
													automation object 
													that represents the 
													collection of 
													outgoing edges 
													connected to this 
													block.
	Parameters :	none
   ============================================================*/
{
	ThrowIfDetached();
	ThrowIfNoDiagramAutoObject();
	
	if (!m_pOutgoingEdges) {
		m_pOutgoingEdges = new CProMoOutgoingEdgesAuto();
		if (m_pOutgoingEdges) {
			m_pOutgoingEdges->SetElementAutoObject(this);
		}
	}
	return m_pOutgoingEdges;
}

void CProMoBlockAuto::ReleaseOutgoingEdgesAutoObject()
/* ============================================================
	Function :		CProMoBlockAuto::ReleaseOutgoingEdgesAutoObject
	Description :	Releases the automation object that represents 
					the collection of outgoing edges connected to this 
					block, if it exists.
	Access :		Public
	
	Return :		void
	Parameters :	none
   ============================================================*/
{
	if (m_pOutgoingEdges) {
		m_pOutgoingEdges->SetElementAutoObject(NULL);
		m_pOutgoingEdges->GetIDispatch(FALSE)->Release();
		m_pOutgoingEdges = NULL;
	}
}

CProMoBlockAuto* CProMoBlockAuto::FromIDispatch(LPDISPATCH obj)
/* ============================================================
	Function :		CProMoBlockAuto::FromIDispatch
	Description :	Returns a pointer to the CProMoBlockAuto 
					automation object associated with the given 
					IDispatch pointer, if it is of the correct type.
					If the IDispatch pointer does not correspond to a 
					CProMoBlockAuto automation object, an exception is 
					thrown.
	Access :		Public
	
	Return :		CProMoBlockAuto*	-	a pointer to the 
											CProMoBlockAuto automation 
											object associated with the 
											given IDispatch pointer.
	Parameters :	LPDISPATCH obj		-	the IDispatch pointer to 
											get	the CProMoBlockAuto 
											automation object from.
   ============================================================*/
{
	CCmdTarget* pTarget = CCmdTarget::FromIDispatch(obj);

	if (!pTarget || !pTarget->IsKindOf(RUNTIME_CLASS(CProMoBlockAuto))) {
		AfxThrowOleDispatchException(
			1001,
			_T("Invalid block automation object"));
	}

	return (CProMoBlockAuto*)pTarget;
}

CProMoBlockModel* CProMoBlockAuto::GetModelFromIDispatch(LPDISPATCH obj)
/* ============================================================
	Function :		CProMoBlockAuto::GetModelFromIDispatch
	Description :	Returns a pointer to the CProMoBlockModel 
					associated with the given IDispatch pointer, if it 
					corresponds to a CProMoBlockAuto automation object. If 
					the IDispatch pointer does not correspond to a 
					CProMoBlockAuto automation object, an exception is 
					thrown.
	Access :		Public
	
	Return :		CProMoBlockModel*	-	a pointer to the 
											CProMoBlockModel associated 
											with the given IDispatch 
											pointer.
	Parameters :	LPDISPATCH obj		-	the IDispatch pointer to get
											the CProMoBlockModel from.
   ============================================================*/
{
	CProMoBlockAuto* pAuto = FromIDispatch(obj);
	if (pAuto) {
		return pAuto->GetBlockModel();
	}
	return NULL;
}

void CProMoBlockAuto::OnFinalRelease()
/* ============================================================
	Function :		CProMoBlockAuto::OnFinalRelease
	Description :	Release the automation object. Called when
					the last reference for an automation object
					is released. The base class will
					automatically delete the object.
	Access :		Public

	Return :		void
	Parameters :	none

	Usage:			Overridden to release the automation objects 
					for the sub-blocks, boundary blocks, incoming 
					edges, and outgoing edges of this block, if 
					they exist. The base class implementation will 
					delete the object when the application 
					automation object is released.

   ============================================================*/

{
	ReleaseSubBlocksAutoObject();
	ReleaseBoundaryBlocksAutoObject();
	ReleaseIncomingEdgesAutoObject();
	ReleaseOutgoingEdgesAutoObject();
	CProMoElementAuto::OnFinalRelease();
}

BEGIN_MESSAGE_MAP(CProMoBlockAuto, CProMoElementAuto)
	//{{AFX_MSG_MAP(CProMoBlockAuto)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

BEGIN_DISPATCH_MAP(CProMoBlockAuto, CProMoElementAuto)
	//{{AFX_DISPATCH_MAP(CProMoBlockAuto)
	//Common to CProMoElementAuto
	DISP_PROPERTY_EX(CProMoElementAuto, "LineColor", GetLineColor, SetLineColor, VT_COLOR)
	DISP_PROPERTY_EX(CProMoElementAuto, "LineWidth", GetLineWidth, SetLineWidth, VT_I2)
	DISP_PROPERTY_EX(CProMoElementAuto, "LineStyle", GetLineStyle, SetLineStyle, VT_I4)
	DISP_PROPERTY_EX(CProMoElementAuto, "FontName", GetFontName, SetFontName, VT_BSTR)
	DISP_PROPERTY_EX(CProMoElementAuto, "FontSize", GetFontSize, SetFontSize, VT_I2)
	DISP_PROPERTY_EX(CProMoElementAuto, "FontWeight", GetFontWeight, SetFontWeight, VT_I2)
	DISP_PROPERTY_EX(CProMoElementAuto, "FontItalic", GetFontItalic, SetFontItalic, VT_BOOL)
	DISP_PROPERTY_EX(CProMoElementAuto, "FontUnderline", GetFontUnderline, SetFontUnderline, VT_BOOL)
	DISP_PROPERTY_EX(CProMoElementAuto, "FontStrikeOut", GetFontStrikeOut, SetFontStrikeOut, VT_BOOL)
	DISP_PROPERTY_EX(CProMoElementAuto, "TextColor", GetTextColor, SetTextColor, VT_COLOR)
	DISP_PROPERTY_EX(CProMoElementAuto, "BkColor", GetBkColor, SetBkColor, VT_COLOR)
	DISP_PROPERTY_EX(CProMoElementAuto, "BkMode", GetBkMode, SetBkMode, VT_I4)
	DISP_PROPERTY_EX(CProMoElementAuto, "TextMultiLine", GetTextMultiLine, SetTextMultiLine, VT_BOOL)
	DISP_PROPERTY_EX(CProMoElementAuto, "TextHorizontalAlignment", GetTextHorizontalAlignment, SetTextHorizontalAlignment, VT_I4)
	DISP_PROPERTY_EX(CProMoElementAuto, "TextVerticalAlignment", GetTextVerticalAlignment, SetTextVerticalAlignment, VT_I4)
	DISP_PROPERTY_EX(CProMoElementAuto, "ID", GetName, SetName, VT_BSTR)
	DISP_PROPERTY_EX(CProMoElementAuto, "Labels", GetLabels, SetLabels, VT_DISPATCH)
	DISP_PROPERTY_EX(CProMoElementAuto, "Properties", GetProperties, SetProperties, VT_DISPATCH)
	DISP_PROPERTY_EX(CProMoElementAuto, "Type", GetType, SetType, VT_BSTR)
	DISP_PROPERTY_EX(CProMoElementAuto, "LockFlags", GetLockFlags, SetLockFlags, VT_I2)
	//Specific to CProMoBlockAuto
	DISP_PROPERTY_EX(CProMoBlockAuto, "FillColor", GetFillColor, SetFillColor, VT_COLOR)
	DISP_PROPERTY_EX(CProMoBlockAuto, "FillPattern", GetFillPattern, SetFillPattern, VT_BOOL)
	DISP_PROPERTY_EX(CProMoBlockAuto, "FillStyle", GetFillStyle, SetFillStyle, VT_I4)
	DISP_PROPERTY_EX(CProMoBlockAuto, "Parent", GetParent, SetParent, VT_DISPATCH)
	DISP_PROPERTY_EX(CProMoBlockAuto, "SubBlocks", GetSubBlocks, SetSubBlocks, VT_DISPATCH)
	DISP_PROPERTY_EX(CProMoBlockAuto, "BoundaryBlocks", GetBoundaryBlocks, SetBoundaryBlocks, VT_DISPATCH)
	DISP_PROPERTY_EX(CProMoBlockAuto, "BoundaryAttachment", GetBoundaryAttachment, SetBoundaryAttachment, VT_I4)
	DISP_PROPERTY_EX(CProMoBlockAuto, "OutgoingEdges", GetOutgoingEdges, SetOutgoingEdges, VT_DISPATCH)
	DISP_PROPERTY_EX(CProMoBlockAuto, "IncomingEdges", GetIncomingEdges, SetIncomingEdges, VT_DISPATCH)
	DISP_PROPERTY_EX(CProMoBlockAuto, "Top", GetTop, SetTop, VT_R8)
	DISP_PROPERTY_EX(CProMoBlockAuto, "Bottom", GetBottom, SetBottom, VT_R8)
	DISP_PROPERTY_EX(CProMoBlockAuto, "Left", GetLeft, SetLeft, VT_R8)
	DISP_PROPERTY_EX(CProMoBlockAuto, "Right", GetRight, SetRight, VT_R8)
	DISP_PROPERTY_EX(CProMoBlockAuto, "Width", GetWidth, SetWidth, VT_R8)
	DISP_PROPERTY_EX(CProMoBlockAuto, "Height", GetHeight, SetHeight, VT_R8)
	DISP_FUNCTION(CProMoBlockAuto, "IsBoundaryBlock", IsBoundaryBlock, VT_BOOL, VTS_NONE)
	DISP_FUNCTION(CProMoBlockAuto, "IsSubBlock", IsSubBlock, VT_BOOL, VTS_NONE)
	//Common to CProMoElementAuto
	DISP_FUNCTION(CProMoElementAuto, "Copy", Copy, VT_EMPTY, VTS_NONE)
	DISP_FUNCTION(CProMoElementAuto, "Cut", Cut, VT_EMPTY, VTS_NONE)
	DISP_FUNCTION(CProMoElementAuto, "Delete", Delete, VT_EMPTY, VTS_NONE)
	DISP_FUNCTION(CProMoElementAuto, "Duplicate", Duplicate, VT_DISPATCH, VTS_NONE)
	//Common to CProMoDiagramChildAuto
	DISP_FUNCTION(CProMoDiagramChildAuto, "Diagram", Diagram, VT_DISPATCH, VTS_NONE)
	//Common to CProMoAppChildAuto
	DISP_FUNCTION(CProMoAppChildAuto, "Application", Application, VT_DISPATCH, VTS_NONE)
	//}}AFX_DISPATCH_MAP
END_DISPATCH_MAP()

// Note: we add support for IID_IProMoBlockAuto to support typesafe binding
//  from VBA.  This IID must match the GUID that is attached to the 
//  dispinterface in the .ODL file.

// {38EA3760-08C3-11F1-9744-000C2976A615}
static const IID IID_IProMoBlockAuto =
{ 0x38ea3760, 0x8c3, 0x11f1, { 0x97, 0x44, 0x0, 0xc, 0x29, 0x76, 0xa6, 0x15 } };

BEGIN_INTERFACE_MAP(CProMoBlockAuto, CProMoElementAuto)
	INTERFACE_PART(CProMoBlockAuto, IID_IProMoBlockAuto, Dispatch)
END_INTERFACE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CProMoBlockAuto message handlers

OLE_COLOR CProMoBlockAuto::GetFillColor() 
/* ============================================================
	Function :		CProMoBlockAuto::GetFillColor
	Description :	Returns the fill color of the block.
	Access :		Public
	
	Return :		OLE_COLOR	-	the fill color of the block, as an 
									OLE_COLOR value.
	Parameters :	none
   ============================================================*/
{
	if (GetMainBlockView()) {
		COLORREF color = GetMainBlockView()->GetFillColor();
		return RGB(GetRValue(color), GetGValue(color), GetBValue(color));
	}

	return RGB(0,0,0);
}

void CProMoBlockAuto::SetFillColor(OLE_COLOR nNewValue) 
/* ============================================================
	Function :		CProMoBlockAuto::SetFillColor
	Description :	Sets the fill color of the block.
	Access :		Public
	
	Return :		void
	Parameters :	OLE_COLOR nNewValue	-	the new fill color of the block, 
											as an OLE_COLOR value.
   ============================================================*/
{
	COLORREF color;
	HRESULT hr = OleTranslateColor(nNewValue, NULL, &color);
	if (FAILED(hr))
		AfxThrowOleException(hr);
	CObArray views;
	GetViews(views);

	if (HasLockFlag(LOCK_FILLCOLOR) || !GetModel()) {
		return;
	}

	GetContainer()->Snapshot();

	for (int i = 0; i < views.GetSize(); i++) {
		CProMoBlockView* view = dynamic_cast<CProMoBlockView*>(views.GetAt(i));
		if (view) {
			view->SetFillColor(nNewValue);
		}
	}
	GetDiagramAutoObject()->NotifyChange();
}

BOOL CProMoBlockAuto::GetFillPattern() 
/* ============================================================
	Function :		CProMoBlockAuto::GetFillPattern
	Description :	Returns whether the block has a fill pattern.
	Access :		Public
	
	Return :		BOOL	-	"TRUE" if the block has a fill 
								pattern, or "FALSE" if it does not.
	Parameters :	none
   ============================================================*/
{
	if (GetMainBlockView()) {
		return GetMainBlockView()->IsFillPattern();
	}

	return FALSE;
}

void CProMoBlockAuto::SetFillPattern(BOOL bNewValue) 
/* ============================================================
	Function :		CProMoBlockAuto::SetFillPattern
	Description :	Sets whether the block has a fill pattern.
	Access :		Public
	
	Return :		void
	Parameters :	BOOL bNewValue	-	"TRUE" to set the block to 
										have a fill pattern, or 
										"FALSE" to set it to have no 
										fill pattern.
   ============================================================*/
{
	CObArray views;
	GetViews(views);

	if (HasLockFlag(LOCK_FILLSTYLE) || !GetModel()) {
		return;
	}

	GetContainer()->Snapshot();

	for (int i = 0; i < views.GetSize(); i++) {
		CProMoBlockView* view = dynamic_cast<CProMoBlockView*>(views.GetAt(i));
		if (view) {
			view->SetFillPattern(bNewValue);
		}
	}
	GetDiagramAutoObject()->NotifyChange();
}

long CProMoBlockAuto::GetFillStyle() 
/* ============================================================
	Function :		CProMoBlockAuto::GetFillStyle
	Description :	Returns the fill style of the block.
	Access :		Public
	
	Return :		long	-	the fill style of the block, as a 
								short integer value. The specific 
								values and their meanings depend on 
								the implementation of the block view.
	Parameters :	none
   ============================================================*/
{
	if (GetMainBlockView()) {
		return GetMainBlockView()->GetFillStyle();
	}

	return 0;
}

void CProMoBlockAuto::SetFillStyle(long nNewValue) 
/* ============================================================
	Function :		CProMoBlockAuto::SetFillStyle
	Description :	Sets the fill style of the block.
	Access :		Public
	
	Return :		void
	Parameters :	long nNewValue	-	the new fill style of the block, as a 
										short integer value. The specific 
										values and their meanings depend on 
										the implementation of the block view.
   ============================================================*/
{
	CObArray views;
	GetViews(views);

	if (HasLockFlag(LOCK_FILLSTYLE) || !GetModel()) {
		return;
	}

	GetContainer()->Snapshot();

	for (int i = 0; i < views.GetSize(); i++) {
		CProMoBlockView* view = dynamic_cast<CProMoBlockView*>(views.GetAt(i));
		if (view) {
			view->SetFillStyle(nNewValue);
		}
	}
	GetDiagramAutoObject()->NotifyChange();
}

LPDISPATCH CProMoBlockAuto::GetParent() 
/* ============================================================
	Function :		CProMoBlockAuto::GetParent
	Description :	Returns a pointer to the automation object that 
					represents the parent block of this block (that
					is, the block that contains this block as a 
					sub-block or as a boundary block), if it exists. 
					If this block has no parent block, "NULL" is 
					returned.
	Access :		Public
	
	Return :		LPDISPATCH	-	a pointer to the automation object 
									that represents the parent block 
									of this block, or "NULL" if this 
									block has no parent block.
	Parameters :	none
   ============================================================*/
{
	if (GetBlockModel()) {
		CProMoBlockModel* pModel = GetBlockModel()->GetParentBlock();
		if (pModel) {
			CProMoElementAuto* pModelAuto = dynamic_cast<CProMoElementAuto*>(pModel->GetAutomationObject());
			if (pModelAuto) {
				pModelAuto->SetDiagramAutoObject(GetDiagramAutoObject());
				return pModelAuto->GetIDispatch(TRUE);
			}
		}
	}

	return NULL;
}

void CProMoBlockAuto::SetParent(LPDISPATCH newValue) 
/* ============================================================
	Function :		CProMoBlockAuto::SetParent
	Description :	Sets the parent block of this block to the block 
					represented by the given automation object.
					This property is read-only, so this function
					simply raises an exception. To set the parent block 
					of this block, the "SubBlocks" or "BoundaryBlocks" 
					collection of the new parent block should be used 
					to add this block as a sub-block or boundary block 
					of the new parent block.
	Access :		Public
	
	Return :		void
	Parameters :	LPDISPATCH newValue	-	a pointer to the automation object that 
											represents the new parent block of 
											this block.
   ============================================================*/
{
	SetNotSupported();

}

LPDISPATCH CProMoBlockAuto::GetSubBlocks()
/* ============================================================
	Function :		CProMoBlockAuto::GetSubBlocks
	Description :	Returns a pointer to the automation object that 
					represents the collection of sub-blocks contained
					in this block.
	Access :		Public
	
	Return :		LPDISPATCH	-	a pointer to the automation object 
									that represents the collection of 
									sub-blocks contained in this block.
	Parameters :	none
   ============================================================*/
{
	if (GetSubBlocksAutoObject()) {
		return GetSubBlocksAutoObject()->GetIDispatch(TRUE);
	}

	return NULL;
}

void CProMoBlockAuto::SetSubBlocks(LPDISPATCH newValue) 
/* ============================================================
	Function :		CProMoBlockAuto::SetSubBlocks
	Description :	Sets the collection of sub-blocks contained in this 
					block to the collection represented by the given 
					automation object.
					This property is read-only, so this function
					simply raises an exception. To set the sub-blocks 
					contained in this block, the "SubBlocks" collection 
					of this block should be used to add or remove sub-blocks.
	Access :		Public
	
	Return :		void
	Parameters :	LPDISPATCH newValue	-	a pointer to the automation object that 
											represents the new collection of 
											sub-blocks contained in this block.
   ============================================================*/
{
	SetNotSupported();

}

LPDISPATCH CProMoBlockAuto::GetBoundaryBlocks() 
/* ============================================================
	Function :		CProMoBlockAuto::GetBoundaryBlocks
	Description :	Returns a pointer to the automation object that 
					represents the collection of boundary blocks 
					contained in this block.
	Access :		Public
	
	Return :		LPDISPATCH	-	a pointer to the automation object 
									that represents the collection of 
									boundary blocks contained in this 
									block.
	Parameters :	none
   ============================================================*/
{
	if (GetBoundaryBlocksAutoObject()) {
		return GetBoundaryBlocksAutoObject()->GetIDispatch(TRUE);
	}

	return NULL;
}

void CProMoBlockAuto::SetBoundaryBlocks(LPDISPATCH newValue) 
/* ============================================================
	Function :		CProMoBlockAuto::SetBoundaryBlocks
	Description :	Sets the collection of boundary blocks contained in 
					this block to the collection represented by the given 
					automation object.
					This property is read-only, so this function
					simply raises an exception. To set the boundary 
					blocks contained in this block, the "BoundaryBlocks" 
					collection of this block should be used to add 
					or remove boundary blocks.
	Access :		Public
	
	Return :		void
	Parameters :	LPDISPATCH newValue	-	a pointer to the automation object 
											that represents the new collection of 
											boundary blocks contained in this block.
   ============================================================*/
{
	SetNotSupported();

}

long CProMoBlockAuto::GetBoundaryAttachment() 
/* ============================================================
	Function :		CProMoBlockAuto::GetBoundaryAttachment
	Description :	Returns the boundary attachment of this block, 
					that is, the type of attachment to the parent 
					block that this block has if it is a boundary 
					block. If this block is not a boundary block, 
					the return value is undefined.
	Access :		Public
	
	Return :		long	-	the boundary attachment of this 
								block, as a short integer value. 
								The specific values and	their 
								meanings depend on the implementation
								of the block model and view.
	Parameters :	none
   ============================================================*/
{
	if (GetBlockModel()) {
		return GetBlockModel()->GetBoundaryAttachment();
	}

	return 0;
}

void CProMoBlockAuto::SetBoundaryAttachment(long nNewValue) 
/* ============================================================
	Function :		CProMoBlockAuto::SetBoundaryAttachment
	Description :	Sets the boundary attachment of this block to the 
					given value. This property is read-only, so 
					this function simply raises an exception. 
					To set the boundary attachment of this block,
					the "BoundaryBlocks" collection of the parent 
					block should be used to remove this block and
					add it again with the desired boundary attachment.
	Access :		Public
	
	Return :		void
	Parameters :	long nNewValue	-	the new boundary attachment of this 
										block, as a short integer value.
   ============================================================*/
{
	SetNotSupported();
}

BOOL CProMoBlockAuto::IsBoundaryBlock() 
/* ============================================================
	Function :		CProMoBlockAuto::IsBoundaryBlock
	Description :	Returns whether this block is a boundary block.
	Access :		Public
	
	Return :		BOOL	-	"TRUE" if this block is a boundary 
								block, or "FALSE" if it is not.
	Parameters :	none
   ============================================================*/
{
	if (GetBlockModel()) {
		return GetBlockModel()->IsBoundaryBlock();
	}

	return FALSE;
}

BOOL CProMoBlockAuto::IsSubBlock() 
/* ============================================================
	Function :		CProMoBlockAuto::IsSubBlock
	Description :	Returns whether this block is a sub-block.
	Access :		Public
	
	Return :		BOOL	-	"TRUE" if this block is a sub-block, 
								or "FALSE" if it is not.
	Parameters :	none
   ============================================================*/
{
	if (GetBlockModel()) {
		return GetBlockModel()->IsSubBlock();
	}

	return FALSE;
}

LPDISPATCH CProMoBlockAuto::GetOutgoingEdges() 
/* ============================================================
	Function :		CProMoBlockAuto::GetOutgoingEdges
	Description :	Returns a pointer to the automation object that 
					represents the collection of outgoing edges 
					connected to this block.
	Access :		Public
	
	Return :		LPDISPATCH	-	a pointer to the automation object 
									that represents the collection of 
									outgoing edges connected to this 
									block.
	Parameters :	none
   ============================================================*/
{
	if (GetOutgoingEdgesAutoObject()) {
		return GetOutgoingEdgesAutoObject()->GetIDispatch(TRUE);
	}

	return NULL;
}

void CProMoBlockAuto::SetOutgoingEdges(LPDISPATCH newValue) 
/* ============================================================
	Function :		CProMoBlockAuto::SetOutgoingEdges
	Description :	Sets the collection of outgoing edges connected to 
					this block to the collection represented by the 
					given automation object.
					This property is read-only, so this function
					simply raises an exception. To set the outgoing 
					edges connected to this block, the "OutgoingEdges" 
					collection of this block should be used to add 
					or remove outgoing edges.
	Access :		Public
	
	Return :		void
	Parameters :	LPDISPATCH newValue	-	a pointer to the automation 
											object that represents the new 
											collection of outgoing edges 
											connected to this block.
   ============================================================*/
{
	SetNotSupported();

}

LPDISPATCH CProMoBlockAuto::GetIncomingEdges()
/* ============================================================
	Function :		CProMoBlockAuto::GetIncomingEdges
	Description :	Returns a pointer to the automation object that 
					represents the collection of incoming edges 
					connected to this block.
	Access :		Public
	
	Return :		LPDISPATCH	-	a pointer to the automation object 
									that represents the collection of 
									incoming edges connected to this 
									block.
	Parameters :	none
   ============================================================*/
{
	if (GetIncomingEdgesAutoObject()) {
		return GetIncomingEdgesAutoObject()->GetIDispatch(TRUE);
	}

	return NULL;
}

void CProMoBlockAuto::SetIncomingEdges(LPDISPATCH newValue)
/* ============================================================
	Function :		CProMoBlockAuto::SetIncomingEdges
	Description :	Sets the collection of incoming edges connected to 
					this block to the collection represented by the 
					given automation object.
					This property is read-only, so this function
					simply raises an exception. To set the incoming 
					edges connected to this block, the "IncomingEdges" 
					collection of this block should be used to add or 
					remove incoming edges.
	Access :		Public
	
	Return :		void
	Parameters :	LPDISPATCH newValue	-	a pointer to the automation object 
											that represents the new collection of 
											incoming edges connected to this block.
   ============================================================*/
{
	SetNotSupported();

}

double CProMoBlockAuto::GetTop() 
/* ============================================================
	Function :		CProMoBlockAuto::GetTop
	Description :	Returns the top coordinate of this block.
	Access :		Public
	
	Return :		double	-	the top coordinate of this block.
	Parameters :	none
   ============================================================*/
{
	if (GetMainBlockView()) {
		return GetMainBlockView()->GetTop();
	}

	return 0.0;
}

void CProMoBlockAuto::SetTop(double newValue) 
/* ============================================================
	Function :		CProMoBlockAuto::SetTop
	Description :	Sets the top coordinate of this block to the 
					given value. The width and height of the block 
					remain unchanged, so the bottom and right 
					coordinates of the block are adjusted accordingly.
	Access :		Public
	
	Return :		void
	Parameters :	double newValue	-	the new top coordinate of 
										this block.
   ============================================================*/
{
	if (GetMainBlockView()) {
		GetContainer()->Snapshot();
		GetMainBlockView()->SetRect(GetMainBlockView()->GetLeft(), newValue, GetMainBlockView()->GetRight(), GetMainBlockView()->GetBottom() - GetMainBlockView()->GetTop() + newValue);
		GetDiagramAutoObject()->NotifyChange();

	}

}

double CProMoBlockAuto::GetBottom()
/* ============================================================
	Function :		CProMoBlockAuto::GetBottom
	Description :	Returns the bottom coordinate of this block.
	Access :		Public
	
	Return :		double	-	the bottom coordinate of this block.
	Parameters :	none
   ============================================================*/
{
	if (GetMainBlockView()) {
		return GetMainBlockView()->GetBottom();
	}

	return 0.0;
}

void CProMoBlockAuto::SetBottom(double newValue) 
/* ============================================================
	Function :		CProMoBlockAuto::SetBottom
	Description :	Sets the bottom coordinate of this block to the 
					given value. The width and height of the block 
					remain unchanged, so the top and right coordinates 
					of the block are adjusted accordingly.
	Access :		Public
	
	Return :		void
	Parameters :	double newValue	-	the new bottom coordinate of 
										this block.
   ============================================================*/
{
	if (GetMainBlockView()) {
		GetContainer()->Snapshot();
		GetMainBlockView()->SetRect(GetMainBlockView()->GetLeft(), GetMainBlockView()->GetTop() - GetMainBlockView()->GetBottom() + newValue, GetMainBlockView()->GetRight(), newValue);
		GetDiagramAutoObject()->NotifyChange();

	}

}

double CProMoBlockAuto::GetLeft() 
/* ============================================================
	Function :		CProMoBlockAuto::GetLeft
	Description :	Returns the left coordinate of this block.
	Access :		Public
	
	Return :		double	-	the left coordinate of this block.
	Parameters :	none
   ============================================================*/
{
	if (GetMainBlockView()) {
		return GetMainBlockView()->GetLeft();
	}

	return 0.0;
}

void CProMoBlockAuto::SetLeft(double newValue) 
/* ============================================================
	Function :		CProMoBlockAuto::SetLeft
	Description :	Sets the left coordinate of this block to the 
					given value. The width and height of the block 
					remain unchanged, so the top and bottom 
					coordinates of the block are adjusted accordingly.
	Access :		Public
	
	Return :		void
	Parameters :	double newValue	-	the new left coordinate of 
										this block.
   ============================================================*/
{
	if (GetMainBlockView()) {
		GetContainer()->Snapshot();
		GetMainBlockView()->SetRect(newValue, GetMainBlockView()->GetTop(), GetMainBlockView()->GetRight() - GetMainBlockView()->GetLeft() + newValue, GetMainBlockView()->GetBottom());
		GetDiagramAutoObject()->NotifyChange();

	}

}

double CProMoBlockAuto::GetRight() 
/* ============================================================
	Function :		CProMoBlockAuto::GetRight
	Description :	Returns the right coordinate of this block.
	Access :		Public
	
	Return :		double	-	the right coordinate of this block.
	Parameters :	none
   ============================================================*/
{
	if (GetMainBlockView()) {
		return GetMainBlockView()->GetRight();
	}

	return 0.0;
}

void CProMoBlockAuto::SetRight(double newValue) 
/* ============================================================
	Function :		CProMoBlockAuto::SetRight
	Description :	Sets the right coordinate of this block to the 
					given value. The width and height of the block 
					remain unchanged, so the top and bottom coordinates 
					of the block are adjusted accordingly.
	Access :		Public
	
	Return :		void
	Parameters :	double newValue	-	the new right coordinate of 
										this block.
   ============================================================*/
{
	if (GetMainBlockView()) {
		GetContainer()->Snapshot();
		GetMainBlockView()->SetRect(GetMainBlockView()->GetLeft() - GetMainBlockView()->GetRight() + newValue, GetMainBlockView()->GetTop(), newValue, GetMainBlockView()->GetBottom());
		GetDiagramAutoObject()->NotifyChange();

	}

}

double CProMoBlockAuto::GetWidth() 
/* ============================================================
	Function :		CProMoBlockAuto::GetWidth
	Description :	Returns the width of this block.
	Access :		Public
	
	Return :		double	-	the width of this block.
	Parameters :	none
   ============================================================*/
{
	if (GetMainBlockView()) {
		return GetMainBlockView()->GetRect().Width();
	}

	return 0.0;
}

void CProMoBlockAuto::SetWidth(double newValue)
/* ============================================================
	Function :		CProMoBlockAuto::SetWidth
	Description :	Sets the width of this block to the given value. 
					The left coordinate of the block remains unchanged, 
					so the right coordinate of the block is adjusted 
					accordingly. The height of the block also remains 
					unchanged, so the top and bottom coordinates of the 
					block are not adjusted.
	Access :		Public
	
	Return :		void
	Parameters :	double newValue	-	the new width of this block.
   ============================================================*/
{
	if (GetMainBlockView()) {

		CDoubleRect oldRect(GetMainBlockView()->GetLeft(), GetMainBlockView()->GetTop(), GetMainBlockView()->GetRight(), GetMainBlockView()->GetBottom());
		CDoubleRect newRect(GetMainBlockView()->GetLeft(), GetMainBlockView()->GetTop(), GetMainBlockView()->GetLeft() + newValue, GetMainBlockView()->GetBottom());

		if (GetMainBlockView()->HasLockedProportions()) {
			CGeometryHelper::EnforceAspectRatio(oldRect, newRect, DEHT_RIGHTMIDDLE, CPoint(0, 0));
		}

		GetContainer()->Snapshot();
		GetMainBlockView()->SetRect(newRect.ToCRect());
		GetMainBlockView()->AutoResize();
		GetDiagramAutoObject()->NotifyChange();

	}

}

double CProMoBlockAuto::GetHeight() 
/* ============================================================
	Function :		CProMoBlockAuto::GetHeight
	Description :	Returns the height of this block.
	Access :		Public
	
	Return :		double	-	the height of this block.
	Parameters :	none
   ============================================================*/
{
	if (GetMainBlockView()) {
		return GetMainBlockView()->GetRect().Height();
	}

	return 0.0;
}

void CProMoBlockAuto::SetHeight(double newValue) 
/* ============================================================
	Function :		CProMoBlockAuto::SetHeight
	Description :	Sets the height of this block to the given value. 
					The top coordinate of the block remains unchanged, 
					so the bottom coordinate of the block is adjusted 
					accordingly. The width of the block also remains 
					unchanged, so the left and right coordinates of the 
					block are not adjusted.
	Access :		Public
	
	Return :		void
	Parameters :	double newValue	-	the new height of this block.
   ============================================================*/
{
	if (GetMainBlockView()) {
		CDoubleRect oldRect(GetMainBlockView()->GetLeft(), GetMainBlockView()->GetTop(), GetMainBlockView()->GetRight(), GetMainBlockView()->GetBottom());
		CDoubleRect newRect(GetMainBlockView()->GetLeft(), GetMainBlockView()->GetTop(), GetMainBlockView()->GetRight(), GetMainBlockView()->GetTop() + newValue);

		if (GetMainBlockView()->HasLockedProportions()) {
			CGeometryHelper::EnforceAspectRatio(oldRect, newRect, DEHT_BOTTOMMIDDLE, CPoint(0, 0));
		}

		GetContainer()->Snapshot();
		GetMainBlockView()->SetRect(newRect.ToCRect());
		GetMainBlockView()->AutoResize();
		GetDiagramAutoObject()->NotifyChange();

	}
}

