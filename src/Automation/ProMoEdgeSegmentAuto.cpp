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
#include <math.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CProMoEdgeSegmentAuto

IMPLEMENT_DYNCREATE(CProMoEdgeSegmentAuto, CProMoEdgeChildAuto)

CProMoEdgeSegmentAuto::CProMoEdgeSegmentAuto()
/* ============================================================
	Function :		CProMoEdgeSegmentAuto::CProMoEdgeSegmentAuto
	Description :	Constructor
	Access :		Public

	Return :		void
	Parameters :	none
	============================================================ */
{
}

CProMoEdgeView* CProMoEdgeSegmentAuto::GetSegment()
/* ============================================================
	Function :		CProMoEdgeSegmentAuto::GetSegment
	Description :	Returns the edge segment represented by this
					automation object.
	Access :		Public

	Return :		CProMoEdgeView*	-	The edge segment represented 
										by this automation object, 
										or NULL if the automation 
										object is not properly 
										initialized.
	Parameters :	none
	============================================================ */
{
	ThrowIfDetached();
	ThrowIfNoElementAutoObject();
	
	return dynamic_cast<CProMoEdgeView*>(m_pInternalObject);
}

void CProMoEdgeSegmentAuto::KeepElementsConnected()
/* ============================================================
	Function :		CProMoEdgeSegmentAuto::KeepElementsConnected
	Description :	Invoked after moving or resizing an edge segment, 
					to keep the source and destination blocks connected
					to the edge.
	Access :		Protected

	Return :		void
	Parameters :	none
	============================================================ */
{
	// resize source and destination blocks (if they exist), so to invoke the logic to keep edges connected
	if (GetEdgeModel()) {
		if (GetEdgeModel()->GetSource()) {
			GetEdgeModel()->GetSource()->GetMainBlockView()->SetLeft(GetEdgeModel()->GetSource()->GetMainBlockView()->GetLeft());
		}
		if (GetEdgeModel()->GetDestination()) {
			GetEdgeModel()->GetDestination()->GetMainBlockView()->SetLeft(GetEdgeModel()->GetDestination()->GetMainBlockView()->GetLeft());
		}
	}
	GetEdgeModel()->GetMainView()->Reposition();
}

CProMoEdgeSegmentAuto::~CProMoEdgeSegmentAuto()
/* ============================================================
	Function :		CProMoEdgeSegmentAuto::~CProMoEdgeSegmentAuto
	Description :	Destructor
	Access :		Protected

	Return :		void
	Parameters :	none
	============================================================ */
{
}


BEGIN_MESSAGE_MAP(CProMoEdgeSegmentAuto, CProMoEdgeChildAuto)
	//{{AFX_MSG_MAP(CProMoEdgeSegmentAuto)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

BEGIN_DISPATCH_MAP(CProMoEdgeSegmentAuto, CProMoEdgeChildAuto)
	//{{AFX_DISPATCH_MAP(CProMoEdgeSegmentAuto)
	DISP_PROPERTY_EX(CProMoEdgeSegmentAuto, "StartY", GetTop, SetTop, VT_R8)
	DISP_PROPERTY_EX(CProMoEdgeSegmentAuto, "StartX", GetLeft, SetLeft, VT_R8)
	DISP_PROPERTY_EX(CProMoEdgeSegmentAuto, "EndY", GetBottom, SetBottom, VT_R8)
	DISP_PROPERTY_EX(CProMoEdgeSegmentAuto, "EndX", GetRight, SetRight, VT_R8)
	DISP_PROPERTY_EX(CProMoEdgeSegmentAuto, "Width", GetWidth, SetWidth, VT_R8)
	DISP_PROPERTY_EX(CProMoEdgeSegmentAuto, "Height", GetHeight, SetHeight, VT_R8)
	DISP_FUNCTION(CProMoEdgeSegmentAuto, "Split", Split, VT_DISPATCH, VTS_NONE)
	DISP_FUNCTION(CProMoEdgeSegmentAuto, "Prev", Prev, VT_DISPATCH, VTS_NONE)
	DISP_FUNCTION(CProMoEdgeSegmentAuto, "Next", Next, VT_DISPATCH, VTS_NONE)
	DISP_FUNCTION(CProMoEdgeSegmentAuto, "Remove", Remove, VT_EMPTY, VTS_NONE)
	//Common to CProMoElementChildAuto
	DISP_FUNCTION(CProMoElementChildAuto, "Element", Element, VT_DISPATCH, VTS_NONE)
	//Common to CProMoDiagramChildAuto
	DISP_FUNCTION(CProMoDiagramChildAuto, "Diagram", Diagram, VT_DISPATCH, VTS_NONE)
	//Common to CProMoAppChildAuto
	DISP_FUNCTION(CProMoAppChildAuto, "Application", Application, VT_DISPATCH, VTS_NONE)
	//}}AFX_DISPATCH_MAP
END_DISPATCH_MAP()

// Note: we add support for IID_IProMoEdgeSegment to support typesafe binding
//  from VBA.  This IID must match the GUID that is attached to the 
//  dispinterface in the .ODL file.

// {38EA3763-08C3-11F1-9744-000C2976A615}
static const IID IID_IProMoEdgeSegmentAuto =
{ 0x38ea3763, 0x8c3, 0x11f1, { 0x97, 0x44, 0x0, 0xc, 0x29, 0x76, 0xa6, 0x15 } };

BEGIN_INTERFACE_MAP(CProMoEdgeSegmentAuto, CProMoEdgeChildAuto)
	INTERFACE_PART(CProMoEdgeSegmentAuto, IID_IProMoEdgeSegmentAuto, Dispatch)
END_INTERFACE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CProMoEdgeSegmentAuto message handlers

double CProMoEdgeSegmentAuto::GetTop()
/* ============================================================
	Function :		CProMoEdgeSegmentAuto::GetTop
	Description :	Returns the Y coordinate of the start point of the
					edge segment.
	Access :		Public

	Return :		double	-	The Y coordinate of the start point of the
								edge segment.
	Parameters :	none
	============================================================ */
{
	if (GetSegment()) {
		return GetSegment()->GetTop();
	}

	return 0.0;
}

void CProMoEdgeSegmentAuto::SetTop(double newValue) 
/* ============================================================
	Function :		CProMoEdgeSegmentAuto::SetTop
	Description :	Sets the Y coordinate of the start point of the
					edge segment.
	Access :		Public

	Return :		void
	Parameters :	double newValue	-	The Y coordinate of the start point of the
										edge segment.
	============================================================ */
{
	if (GetSegment()) {
		GetContainer()->Snapshot();
		GetSegment()->SetRect(GetSegment()->GetLeft(), newValue, GetSegment()->GetRight(), GetSegment()->GetBottom());
		KeepElementsConnected();
		GetDiagramAutoObject()->NotifyChange();
	}
}

double CProMoEdgeSegmentAuto::GetLeft()
/* ============================================================
	Function :		CProMoEdgeSegmentAuto::GetLeft
	Description :	Returns the X coordinate of the start point of the
					edge segment.
	Access :		Public

	Return :		double	-	The X coordinate of the start point of the
								edge segment.
	Parameters :	none
	============================================================ */
{
	if (GetSegment()) {
		return GetSegment()->GetLeft();
	}

	return 0.0;
}

void CProMoEdgeSegmentAuto::SetLeft(double newValue) 
/* ============================================================
	Function :		CProMoEdgeSegmentAuto::SetLeft
	Description :	Sets the X coordinate of the start point of the
					edge segment.
	Access :		Public

	Return :		void
	Parameters :	double newValue	-	The X coordinate of the start point of the
										edge segment.
	============================================================ */
{
	if (GetSegment()) {
		GetContainer()->Snapshot();
		GetSegment()->SetRect(newValue, GetSegment()->GetTop(), GetSegment()->GetRight(), GetSegment()->GetBottom());
		KeepElementsConnected();
		GetDiagramAutoObject()->NotifyChange();

	}
}

double CProMoEdgeSegmentAuto::GetBottom() 
/* ============================================================
	Function :		CProMoEdgeSegmentAuto::GetBottom
	Description :	Returns the Y coordinate of the end point of the
					edge segment.
	Access :		Public

	Return :		double	-	The Y coordinate of the end point of the
								edge segment.
	Parameters :	none
	============================================================ */
{
	if (GetSegment()) {
		return GetSegment()->GetBottom();
	}

	return 0.0;
}

void CProMoEdgeSegmentAuto::SetBottom(double newValue) 
/* ============================================================
	Function :		CProMoEdgeSegmentAuto::SetBottom
	Description :	Sets the Y coordinate of the end point of the
					edge segment.
	Access :		Public

	Return :		void
	Parameters :	double newValue	-	The Y coordinate of the end point of the
										edge segment.
	============================================================ */
{
	if (GetSegment()) {
		GetContainer()->Snapshot();
		GetSegment()->SetRect(GetSegment()->GetLeft(), GetSegment()->GetTop(), GetSegment()->GetRight(), newValue);
		KeepElementsConnected();
		GetDiagramAutoObject()->NotifyChange();

	}
}

double CProMoEdgeSegmentAuto::GetRight() 
/* ============================================================
	Function :		CProMoEdgeSegmentAuto::GetRight
	Description :	Returns the X coordinate of the end point of the
					edge segment.
	Access :		Public

	Return :		double	-	The X coordinate of the end point of the
								edge segment.
	Parameters :	none
	============================================================ */
{
	if (GetSegment()) {
		return GetSegment()->GetRight();
	}

	return 0.0;
}

void CProMoEdgeSegmentAuto::SetRight(double newValue)
/* ============================================================
	Function :		CProMoEdgeSegmentAuto::SetRight
	Description :	Sets the X coordinate of the end point of the
					edge segment.
	Access :		Public

	Return :		void
	Parameters :	double newValue	-	The X coordinate of the end point of the
										edge segment.
	============================================================ */
{
	if (GetSegment()) {
		GetContainer()->Snapshot();
		GetSegment()->SetRect(GetSegment()->GetLeft(), GetSegment()->GetTop(), newValue, GetSegment()->GetBottom());
		KeepElementsConnected();
		GetDiagramAutoObject()->NotifyChange();

	}
}

double CProMoEdgeSegmentAuto::GetWidth() 
/* ============================================================
	Function :		CProMoEdgeSegmentAuto::GetWidth
	Description :	Returns the width of the edge segment.
	Access :		Public

	Return :		double	-	The width of the edge segment.
	Parameters :	none
	============================================================ */
{
	if (GetSegment()) {
		return fabs(GetSegment()->GetRect().Width());
	}

	return 0.0;
}

void CProMoEdgeSegmentAuto::SetWidth(double newValue) 
/* ============================================================
	Function :		CProMoEdgeSegmentAuto::SetWidth
	Description :	Sets the width of the edge segment. This property
					is read-only, since changing the width of an
					edge segment would change the shape of the edge,
					and this is not supported by the current edge model.
	Access :		Public

	Return :		void
	Parameters :	double newValue	-	The width of the edge segment.
	============================================================ */
{
	SetNotSupported();
}

double CProMoEdgeSegmentAuto::GetHeight() 
/* ============================================================
	Function :		CProMoEdgeSegmentAuto::GetHeight
	Description :	Returns the height of the edge segment.
	Access :		Public

	Return :		double	-	The height of the edge segment.
	Parameters :	none
	============================================================ */
{
	if (GetSegment()) {
		return fabs(GetSegment()->GetRect().Height());
	}


	return 0.0;
}

void CProMoEdgeSegmentAuto::SetHeight(double newValue)
/* ============================================================
	Function :		CProMoEdgeSegmentAuto::SetHeight
	Description :	Sets the height of the edge segment. This property
					is read-only, since changing the height of an
					edge segment would change the shape of the edge,
					and this is not supported by the current edge model.
	Access :		Public

	Return :		void
	Parameters :	double newValue	-	The height of the edge segment.
	============================================================ */
{
	SetNotSupported();
}

LPDISPATCH CProMoEdgeSegmentAuto::Split() 
/* ============================================================
	Function :		CProMoEdgeSegmentAuto::Split
	Description :	Splits the edge segment, by adding a new point in
					the middle of the segment. The new segment is added
					after the current one.
	Access :		Public

	Return :		LPDISPATCH	-	The new edge segment created by the split operation, 
									or NULL if the split operation failed.
	Parameters :	none
	============================================================ */
{
	if (GetSegment()) {
		GetContainer()->Snapshot();
		CProMoEdgeView* newSegment = GetSegment()->Split();
		GetDiagramAutoObject()->NotifyChange();
		if (newSegment) {
			CProMoEdgeSegmentAuto* pElementAuto = dynamic_cast<CProMoEdgeSegmentAuto*>(newSegment->GetAutomationObject());
			if (pElementAuto) {
				pElementAuto->SetElementAutoObject(GetElementAutoObject());
				return pElementAuto->GetIDispatch(TRUE);
			}
		}
	}

	return NULL;
}

LPDISPATCH CProMoEdgeSegmentAuto::Prev() 
/* ============================================================
	Function :		CProMoEdgeSegmentAuto::Prev
	Description :	Returns the previous edge segment in the edge.
	Access :		Public

	Return :		LPDISPATCH	-	The previous edge segment in the edge, 
									or NULL if this is the first segment.
	Parameters :	none
	============================================================ */
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
/* ============================================================
	Function :		CProMoEdgeSegmentAuto::Next
	Description :	Returns the next edge segment in the edge.
	Access :		Public

	Return :		LPDISPATCH	-	The next edge segment in the edge, 
									or NULL if this is the last segment.
	Parameters :	none
	============================================================ */
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
/* ============================================================
	Function :		CProMoEdgeSegmentAuto::Remove
	Description :	Removes the edge segment. If this is the only segment
					in the edge, the operation is not performed, since
					an edge must have at least one segment.
	Access :		Public

	Return :		void
	Parameters :	none
	============================================================ */
{
	if (GetSegment() && GetContainer()) {
		CObArray viewList;
		GetEdgeModel()->GetViews(viewList);
		if (viewList.GetSize() <= 1) {
			// if this is the only segment, do not remove it
			return;
		}
		GetContainer()->Snapshot(); 
		GetContainer()->Remove(GetSegment());
		GetDiagramAutoObject()->NotifyChange();
	}

}
