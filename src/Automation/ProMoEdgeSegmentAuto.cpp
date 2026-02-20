/* ==========================================================================

	Copyright © 2026 Technical University of Denmark

	CProMoEdgeSegmentAuto

	Author :		Giovanni Meroni

	Purpose :		"CProMoEdgeSegmentAuto" is an automation object that
					represents an edge segment. It provides methods
					to access the previous and the next segments in the edge, 
					to split the segment, and to move and resize it.

	Description :	"CProMoEdgeSegmentAuto" provides the implementation of the
					methods and properties that are common to all edge segments.

   ========================================================================*/
#include "stdafx.h"
#include "ProMoEdgeSegmentAuto.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CProMoEdgeSegmentAuto

IMPLEMENT_DYNCREATE(CProMoEdgeSegmentAuto, CProMoEdgeChildAuto)

CProMoEdgeSegmentAuto::CProMoEdgeSegmentAuto()
{
}

CProMoEdgeView* CProMoEdgeSegmentAuto::GetSegment()
{
	ThrowIfDetached();
	ThrowIfNoElementAutoObject();
	
	return dynamic_cast<CProMoEdgeView*>(m_pInternalObject);
}

CProMoEdgeSegmentAuto::~CProMoEdgeSegmentAuto()
{
}


BEGIN_MESSAGE_MAP(CProMoEdgeSegmentAuto, CProMoEdgeChildAuto)
	//{{AFX_MSG_MAP(CProMoEdgeSegmentAuto)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

BEGIN_DISPATCH_MAP(CProMoEdgeSegmentAuto, CProMoEdgeChildAuto)
	//{{AFX_DISPATCH_MAP(CProMoEdgeSegmentAuto)
	DISP_PROPERTY_EX(CProMoEdgeSegmentAuto, "Top", GetTop, SetTop, VT_R8)
	DISP_PROPERTY_EX(CProMoEdgeSegmentAuto, "Left", GetLeft, SetLeft, VT_R8)
	DISP_PROPERTY_EX(CProMoEdgeSegmentAuto, "Bottom", GetBottom, SetBottom, VT_R8)
	DISP_PROPERTY_EX(CProMoEdgeSegmentAuto, "Right", GetRight, SetRight, VT_R8)
	DISP_PROPERTY_EX(CProMoEdgeSegmentAuto, "Width", GetWidth, SetWidth, VT_R8)
	DISP_PROPERTY_EX(CProMoEdgeSegmentAuto, "Height", GetHeight, SetHeight, VT_R8)
	DISP_FUNCTION(CProMoEdgeSegmentAuto, "Split", Split, VT_DISPATCH, VTS_NONE)
	DISP_FUNCTION(CProMoEdgeSegmentAuto, "Prev", Prev, VT_DISPATCH, VTS_NONE)
	DISP_FUNCTION(CProMoEdgeSegmentAuto, "Next", Next, VT_DISPATCH, VTS_NONE)
	DISP_FUNCTION(CProMoEdgeSegmentAuto, "Remove", Remove, VT_EMPTY, VTS_NONE)
	//}}AFX_DISPATCH_MAP
END_DISPATCH_MAP()

// Note: we add support for IID_IProMoEdgeSegment to support typesafe binding
//  from VBA.  This IID must match the GUID that is attached to the 
//  dispinterface in the .ODL file.

// {18EA376F-08C3-11F1-9744-000C2976A615}
static const IID IID_IProMoEdgeSegmentAuto =
{ 0x18ea376f, 0x8c3, 0x11f1, { 0x97, 0x44, 0x0, 0xc, 0x29, 0x76, 0xa6, 0x15 } };

BEGIN_INTERFACE_MAP(CProMoEdgeSegmentAuto, CProMoEdgeChildAuto)
	INTERFACE_PART(CProMoEdgeSegmentAuto, IID_IProMoEdgeSegmentAuto, Dispatch)
END_INTERFACE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CProMoEdgeSegmentAuto message handlers

double CProMoEdgeSegmentAuto::GetTop() 
{
	if (GetSegment()) {
		return GetSegment()->GetTop();
	}

	return 0.0;
}

void CProMoEdgeSegmentAuto::SetTop(double newValue) 
{
	// TODO: Add your property handler here

}

double CProMoEdgeSegmentAuto::GetLeft() 
{
	if (GetSegment()) {
		return GetSegment()->GetLeft();
	}

	return 0.0;
}

void CProMoEdgeSegmentAuto::SetLeft(double newValue) 
{
	// TODO: Add your property handler here

}

double CProMoEdgeSegmentAuto::GetBottom() 
{
	if (GetSegment()) {
		return GetSegment()->GetBottom();
	}

	return 0.0;
}

void CProMoEdgeSegmentAuto::SetBottom(double newValue) 
{
	// TODO: Add your property handler here

}

double CProMoEdgeSegmentAuto::GetRight() 
{
	if (GetSegment()) {
		return GetSegment()->GetRight();
	}

	return 0.0;
}

void CProMoEdgeSegmentAuto::SetRight(double newValue) 
{
	// TODO: Add your property handler here

}

double CProMoEdgeSegmentAuto::GetWidth() 
{
	if (GetSegment()) {
		return GetSegment()->GetRect().Width();
	}

	return 0.0;
}

void CProMoEdgeSegmentAuto::SetWidth(double newValue) 
{
	// TODO: Add your property handler here

}

double CProMoEdgeSegmentAuto::GetHeight() 
{
	if (GetSegment()) {
		return GetSegment()->GetRect().Height();
	}


	return 0.0;
}

void CProMoEdgeSegmentAuto::SetHeight(double newValue) 
{
	// TODO: Add your property handler here

}

LPDISPATCH CProMoEdgeSegmentAuto::Split() 
{
	// TODO: Add your dispatch handler code here

	return NULL;
}

LPDISPATCH CProMoEdgeSegmentAuto::Prev() 
{
	if (GetSegment()) {
		CProMoEdgeView* pPrev = dynamic_cast<CProMoEdgeView*>(GetSegment()->GetSource());
		if (pPrev) {
			CProMoEdgeSegmentAuto* pElementAuto = dynamic_cast<CProMoEdgeSegmentAuto*>(pPrev->GetAutomationObject());
			if (pElementAuto) {
				pElementAuto->SetElementAutoObject(GetElementAutoObject());
				return pElementAuto->GetIDispatch(TRUE);
			}
		}
	}

	return NULL;
}

LPDISPATCH CProMoEdgeSegmentAuto::Next() 
{
	if (GetSegment()){
		CProMoEdgeView* pNext = dynamic_cast<CProMoEdgeView*>(GetSegment()->GetDestination());
		if (pNext) {
			CProMoEdgeSegmentAuto* pElementAuto = dynamic_cast<CProMoEdgeSegmentAuto*>(pNext->GetAutomationObject());
			if (pElementAuto) {
				pElementAuto->SetElementAutoObject(GetElementAutoObject());
				return pElementAuto->GetIDispatch(TRUE);
			}
		}
	}

	return NULL;
}

void CProMoEdgeSegmentAuto::Remove() 
{
	// TODO: Add your dispatch handler code here

}
