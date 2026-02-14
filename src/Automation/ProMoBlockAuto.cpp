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


CProMoSubBlocksAuto* CProMoBlockAuto::GetSubBlocksAutoObject()
{
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
	//}}AFX_DISPATCH_MAP
END_DISPATCH_MAP()

// Note: we add support for IID_IProMoBlockAuto to support typesafe binding
//  from VBA.  This IID must match the GUID that is attached to the 
//  dispinterface in the .ODL file.

// {18EA3768-08C3-11F1-9744-000C2976A615}
static const IID IID_IProMoBlockAuto =
{ 0x18ea3768, 0x8c3, 0x11f1, { 0x97, 0x44, 0x0, 0xc, 0x29, 0x76, 0xa6, 0x15 } };

BEGIN_INTERFACE_MAP(CProMoBlockAuto, CProMoElementAuto)
	INTERFACE_PART(CProMoBlockAuto, IID_IProMoBlockAuto, Dispatch)
END_INTERFACE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CProMoBlockAuto message handlers

OLE_COLOR CProMoBlockAuto::GetFillColor() 
{
	// TODO: Add your property handler here

	return RGB(0,0,0);
}

void CProMoBlockAuto::SetFillColor(OLE_COLOR nNewValue) 
{
	// TODO: Add your property handler here

}

BOOL CProMoBlockAuto::GetFillPattern() 
{
	// TODO: Add your property handler here

	return TRUE;
}

void CProMoBlockAuto::SetFillPattern(BOOL bNewValue) 
{
	// TODO: Add your property handler here

}

long CProMoBlockAuto::GetFillStyle() 
{
	// TODO: Add your property handler here

	return 0;
}

void CProMoBlockAuto::SetFillStyle(long nNewValue) 
{
	// TODO: Add your property handler here

}

LPDISPATCH CProMoBlockAuto::GetParent() 
{
	// TODO: Add your property handler here

	return NULL;
}

void CProMoBlockAuto::SetParent(LPDISPATCH newValue) 
{
	// TODO: Add your property handler here

}

LPDISPATCH CProMoBlockAuto::GetSubBlocks() 
{
	if (m_pSubBlocks) {
		return m_pSubBlocks->GetIDispatch(TRUE);
	}

	return NULL;
}

void CProMoBlockAuto::SetSubBlocks(LPDISPATCH newValue) 
{
	SetNotSupported();

}

LPDISPATCH CProMoBlockAuto::GetBoundaryBlocks() 
{
	if (m_pBoundaryBlocks) {
		return m_pBoundaryBlocks->GetIDispatch(TRUE);
	}

	return NULL;
}

void CProMoBlockAuto::SetBoundaryBlocks(LPDISPATCH newValue) 
{
	SetNotSupported();

}

long CProMoBlockAuto::GetBoundaryAttachment() 
{
	// TODO: Add your property handler here

	return 0;
}

void CProMoBlockAuto::SetBoundaryAttachment(long nNewValue) 
{
	// TODO: Add your property handler here

}

BOOL CProMoBlockAuto::IsBoundaryBlock() 
{
	// TODO: Add your dispatch handler code here

	return TRUE;
}

BOOL CProMoBlockAuto::IsSubBlock() 
{
	// TODO: Add your dispatch handler code here

	return TRUE;
}

LPDISPATCH CProMoBlockAuto::GetOutgoingEdges() 
{
	if (m_pOutgoingEdges) {
		return m_pOutgoingEdges->GetIDispatch(TRUE);
	}

	return NULL;
}

void CProMoBlockAuto::SetOutgoingEdges(LPDISPATCH newValue) 
{
	SetNotSupported();

}

LPDISPATCH CProMoBlockAuto::GetIncomingEdges() 
{
	if (m_pIncomingEdges) {
		return m_pIncomingEdges->GetIDispatch(TRUE);
	}

	return NULL;
}

void CProMoBlockAuto::SetIncomingEdges(LPDISPATCH newValue) 
{
	SetNotSupported();

}

double CProMoBlockAuto::GetTop() 
{
	// TODO: Add your property handler here

	return 0.0;
}

void CProMoBlockAuto::SetTop(double newValue) 
{
	// TODO: Add your property handler here

}

double CProMoBlockAuto::GetBottom() 
{
	// TODO: Add your property handler here

	return 0.0;
}

void CProMoBlockAuto::SetBottom(double newValue) 
{
	// TODO: Add your property handler here

}

double CProMoBlockAuto::GetLeft() 
{
	// TODO: Add your property handler here

	return 0.0;
}

void CProMoBlockAuto::SetLeft(double newValue) 
{
	// TODO: Add your property handler here

}

double CProMoBlockAuto::GetRight() 
{
	// TODO: Add your property handler here

	return 0.0;
}

void CProMoBlockAuto::SetRight(double newValue) 
{
	// TODO: Add your property handler here

}

double CProMoBlockAuto::GetWidth() 
{
	// TODO: Add your property handler here

	return 0.0;
}

void CProMoBlockAuto::SetWidth(double newValue) 
{
	// TODO: Add your property handler here

}

double CProMoBlockAuto::GetHeight() 
{
	// TODO: Add your property handler here

	return 0.0;
}

void CProMoBlockAuto::SetHeight(double newValue) 
{
	// TODO: Add your property handler here

}

