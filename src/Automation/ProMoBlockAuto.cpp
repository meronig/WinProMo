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
{
	m_pSubBlocks = NULL;
	m_pBoundaryBlocks = NULL;
	m_pIncomingEdges = NULL;
	m_pOutgoingEdges = NULL;
}

CProMoBlockAuto::~CProMoBlockAuto()
{
}

CProMoBlockModel* CProMoBlockAuto::GetBlockModel() {
	
	return dynamic_cast<CProMoBlockModel*>(GetModel());
}

CProMoBlockView* CProMoBlockAuto::GetMainBlockView()
{
	if (GetBlockModel()) {
		return GetBlockModel()->GetMainBlockView();
	}

	return NULL;
}

CProMoSubBlocksAuto* CProMoBlockAuto::GetSubBlocksAutoObject()
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
{
	if (m_pSubBlocks) {
		m_pSubBlocks->SetElementAutoObject(NULL);
		m_pSubBlocks->GetIDispatch(FALSE)->Release();
		m_pSubBlocks = NULL;
	}
}

CProMoBoundaryBlocksAuto* CProMoBlockAuto::GetBoundaryBlocksAutoObject()
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
{
	if (m_pBoundaryBlocks) {
		m_pBoundaryBlocks->SetElementAutoObject(NULL);
		m_pBoundaryBlocks->GetIDispatch(FALSE)->Release();
		m_pBoundaryBlocks = NULL;
	}
}

CProMoIncomingEdgesAuto* CProMoBlockAuto::GetIncomingEdgesAutoObject()
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
{
	if (m_pIncomingEdges) {
		m_pIncomingEdges->SetElementAutoObject(NULL);
		m_pIncomingEdges->GetIDispatch(FALSE)->Release();
		m_pIncomingEdges = NULL;
	}
}

CProMoOutgoingEdgesAuto* CProMoBlockAuto::GetOutgoingEdgesAutoObject()
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
{
	if (m_pOutgoingEdges) {
		m_pOutgoingEdges->SetElementAutoObject(NULL);
		m_pOutgoingEdges->GetIDispatch(FALSE)->Release();
		m_pOutgoingEdges = NULL;
	}
}

void CProMoBlockAuto::OnFinalRelease()
{
	// When the last reference for an automation object is released
	// OnFinalRelease is called.  The base class will automatically
	// deletes the object.  Add additional cleanup required for your
	// object before calling the base class.
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
	DISP_PROPERTY_EX(CProMoElementAuto, "LockAspectRatio", GetLockAspectRatio, SetLockAspectRatio, VT_BOOL)
	DISP_PROPERTY_EX(CProMoElementAuto, "LineColor", GetLineColor, SetLineColor, VT_COLOR)
	DISP_PROPERTY_EX(CProMoElementAuto, "LineWidth", GetLineWidth, SetLineWidth, VT_I2)
	DISP_PROPERTY_EX(CProMoElementAuto, "LineStyle", GetLineStyle, SetLineStyle, VT_I2)
	DISP_PROPERTY_EX(CProMoElementAuto, "FontName", GetFontName, SetFontName, VT_BSTR)
	DISP_PROPERTY_EX(CProMoElementAuto, "FontSize", GetFontSize, SetFontSize, VT_I2)
	DISP_PROPERTY_EX(CProMoElementAuto, "FontWeight", GetFontWeight, SetFontWeight, VT_I2)
	DISP_PROPERTY_EX(CProMoElementAuto, "FontItalic", GetFontItalic, SetFontItalic, VT_BOOL)
	DISP_PROPERTY_EX(CProMoElementAuto, "FontUnderline", GetFontUnderline, SetFontUnderline, VT_BOOL)
	DISP_PROPERTY_EX(CProMoElementAuto, "FontStrikeOut", GetFontStrikeOut, SetFontStrikeOut, VT_BOOL)
	DISP_PROPERTY_EX(CProMoElementAuto, "TextColor", GetTextColor, SetTextColor, VT_COLOR)
	DISP_PROPERTY_EX(CProMoElementAuto, "BkColor", GetBkColor, SetBkColor, VT_COLOR)
	DISP_PROPERTY_EX(CProMoElementAuto, "BkMode", GetBkMode, SetBkMode, VT_I2)
	DISP_PROPERTY_EX(CProMoElementAuto, "TextAlignment", GetTextAlignment, SetTextAlignment, VT_I2)
	DISP_PROPERTY_EX(CProMoElementAuto, "TextHorizontalAlignment", GetTextHorizontalAlignment, SetTextHorizontalAlignment, VT_I2)
	DISP_PROPERTY_EX(CProMoElementAuto, "TextVerticalAlignment", GetTextVerticalAlignment, SetTextVerticalAlignment, VT_I2)
	DISP_PROPERTY_EX(CProMoElementAuto, "ID", GetName, SetName, VT_BSTR)
	DISP_PROPERTY_EX(CProMoElementAuto, "Labels", GetLabels, SetLabels, VT_DISPATCH)
	DISP_PROPERTY_EX(CProMoElementAuto, "Properties", GetProperties, SetProperties, VT_DISPATCH)
	DISP_PROPERTY_EX(CProMoElementAuto, "Type", GetType, SetType, VT_BSTR)
	//Specific to CProMoBlockAuto
	DISP_PROPERTY_EX(CProMoBlockAuto, "FillColor", GetFillColor, SetFillColor, VT_COLOR)
	DISP_PROPERTY_EX(CProMoBlockAuto, "FillPattern", GetFillPattern, SetFillPattern, VT_BOOL)
	DISP_PROPERTY_EX(CProMoBlockAuto, "FillStyle", GetFillStyle, SetFillStyle, VT_I2)
	DISP_PROPERTY_EX(CProMoBlockAuto, "Parent", GetParent, SetParent, VT_DISPATCH)
	DISP_PROPERTY_EX(CProMoBlockAuto, "SubBlocks", GetSubBlocks, SetSubBlocks, VT_DISPATCH)
	DISP_PROPERTY_EX(CProMoBlockAuto, "BoundaryBlocks", GetBoundaryBlocks, SetBoundaryBlocks, VT_DISPATCH)
	DISP_PROPERTY_EX(CProMoBlockAuto, "BoundaryAttachment", GetBoundaryAttachment, SetBoundaryAttachment, VT_I2)
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
{
	if (GetMainBlockView()) {
		COLORREF color = GetMainBlockView()->GetFillColor();
		return RGB(GetRValue(color), GetGValue(color), GetBValue(color));
	}

	return RGB(0,0,0);
}

void CProMoBlockAuto::SetFillColor(OLE_COLOR nNewValue) 
{
	// TODO: Add your property handler here

}

BOOL CProMoBlockAuto::GetFillPattern() 
{
	if (GetMainBlockView()) {
		return GetMainBlockView()->IsFillPattern();
	}

	return FALSE;
}

void CProMoBlockAuto::SetFillPattern(BOOL bNewValue) 
{
	// TODO: Add your property handler here

}

short CProMoBlockAuto::GetFillStyle() 
{
	if (GetMainBlockView()) {
		return GetMainBlockView()->GetFillStyle();
	}

	return 0;
}

void CProMoBlockAuto::SetFillStyle(short nNewValue) 
{
	// TODO: Add your property handler here

}

LPDISPATCH CProMoBlockAuto::GetParent() 
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
{
	// TODO: Add your property handler here

}

LPDISPATCH CProMoBlockAuto::GetSubBlocks() 
{
	if (GetSubBlocksAutoObject()) {
		return GetSubBlocksAutoObject()->GetIDispatch(TRUE);
	}

	return NULL;
}

void CProMoBlockAuto::SetSubBlocks(LPDISPATCH newValue) 
{
	SetNotSupported();

}

LPDISPATCH CProMoBlockAuto::GetBoundaryBlocks() 
{
	if (GetBoundaryBlocksAutoObject()) {
		return GetBoundaryBlocksAutoObject()->GetIDispatch(TRUE);
	}

	return NULL;
}

void CProMoBlockAuto::SetBoundaryBlocks(LPDISPATCH newValue) 
{
	SetNotSupported();

}

short CProMoBlockAuto::GetBoundaryAttachment() 
{
	if (GetBlockModel()) {
		return GetBlockModel()->GetBoundaryAttachment();
	}

	return 0;
}

void CProMoBlockAuto::SetBoundaryAttachment(short nNewValue) 
{
	SetNotSupported();
}

BOOL CProMoBlockAuto::IsBoundaryBlock() 
{
	if (GetBlockModel()) {
		return GetBlockModel()->IsBoundaryBlock();
	}

	return FALSE;
}

BOOL CProMoBlockAuto::IsSubBlock() 
{
	if (GetBlockModel()) {
		return GetBlockModel()->IsSubBlock();
	}

	return FALSE;
}

LPDISPATCH CProMoBlockAuto::GetOutgoingEdges() 
{
	if (GetOutgoingEdgesAutoObject()) {
		return GetOutgoingEdgesAutoObject()->GetIDispatch(TRUE);
	}

	return NULL;
}

void CProMoBlockAuto::SetOutgoingEdges(LPDISPATCH newValue) 
{
	SetNotSupported();

}

LPDISPATCH CProMoBlockAuto::GetIncomingEdges() 
{
	if (GetIncomingEdgesAutoObject()) {
		return GetIncomingEdgesAutoObject()->GetIDispatch(TRUE);
	}

	return NULL;
}

void CProMoBlockAuto::SetIncomingEdges(LPDISPATCH newValue) 
{
	SetNotSupported();

}

double CProMoBlockAuto::GetTop() 
{
	if (GetMainBlockView()) {
		return GetMainBlockView()->GetTop();
	}

	return 0.0;
}

void CProMoBlockAuto::SetTop(double newValue) 
{
	if (GetMainBlockView()) {
		GetContainer()->Snapshot();
		GetMainBlockView()->SetRect(GetMainBlockView()->GetLeft(), newValue, GetMainBlockView()->GetRight(), GetMainBlockView()->GetBottom() - GetMainBlockView()->GetTop() + newValue);
		GetDiagramAutoObject()->NotifyChange();

	}

}

double CProMoBlockAuto::GetBottom() 
{
	if (GetMainBlockView()) {
		return GetMainBlockView()->GetBottom();
	}

	return 0.0;
}

void CProMoBlockAuto::SetBottom(double newValue) 
{
	if (GetMainBlockView()) {
		GetContainer()->Snapshot();
		GetMainBlockView()->SetRect(GetMainBlockView()->GetLeft(), GetMainBlockView()->GetTop() - GetMainBlockView()->GetBottom() + newValue, GetMainBlockView()->GetRight(), newValue);
		GetDiagramAutoObject()->NotifyChange();

	}

}

double CProMoBlockAuto::GetLeft() 
{
	if (GetMainBlockView()) {
		return GetMainBlockView()->GetLeft();
	}

	return 0.0;
}

void CProMoBlockAuto::SetLeft(double newValue) 
{
	if (GetMainBlockView()) {
		GetContainer()->Snapshot();
		GetMainBlockView()->SetRect(newValue, GetMainBlockView()->GetTop(), GetMainBlockView()->GetRight() - GetMainBlockView()->GetLeft() + newValue, GetMainBlockView()->GetBottom());
		GetDiagramAutoObject()->NotifyChange();

	}

}

double CProMoBlockAuto::GetRight() 
{
	if (GetMainBlockView()) {
		return GetMainBlockView()->GetRight();
	}

	return 0.0;
}

void CProMoBlockAuto::SetRight(double newValue) 
{
	if (GetMainBlockView()) {
		GetContainer()->Snapshot();
		GetMainBlockView()->SetRect(GetMainBlockView()->GetLeft() - GetMainBlockView()->GetRight() + newValue, GetMainBlockView()->GetTop(), newValue, GetMainBlockView()->GetBottom());
		GetDiagramAutoObject()->NotifyChange();

	}

}

double CProMoBlockAuto::GetWidth() 
{
	if (GetMainBlockView()) {
		return GetMainBlockView()->GetRect().Width();
	}

	return 0.0;
}

void CProMoBlockAuto::SetWidth(double newValue) 
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
{
	if (GetMainBlockView()) {
		return GetMainBlockView()->GetRect().Height();
	}

	return 0.0;
}

void CProMoBlockAuto::SetHeight(double newValue) 
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

