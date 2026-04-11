/* ==========================================================================

	Copyright © 2026 Technical University of Denmark

	CProMoEdgeSegmentsAuto

	Author :		Giovanni Meroni

	Purpose :		"CProMoEdgeSegmentsAuto" is an automation object that
					represents the collection of segments composing an edge.
					It provides methods to access the segments.

	Description :	"CProMoEdgeSegmentsAuto" provides the implementation
					of the methods and properties that are common to all
					edge segments collections.

   ========================================================================*/
#include "stdafx.h"
#include "ProMoEdgeSegmentsAuto.h"
#include "ProMoEdgeSegmentAuto.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CProMoEdgeSegmentsAuto

IMPLEMENT_DYNCREATE(CProMoEdgeSegmentsAuto, CProMoEdgeChildAuto)

CProMoEdgeSegmentsAuto::CProMoEdgeSegmentsAuto()
/* ============================================================
	Function :		CProMoEdgeSegmentsAuto::CProMoEdgeSegmentsAuto
	Description :	Constructor
	Access :		Public

	Return :		void
	Parameters :	none
	============================================================ */
{
}

CProMoEdgeSegmentsAuto::~CProMoEdgeSegmentsAuto()
/* ============================================================
	Function :		CProMoEdgeSegmentsAuto::~CProMoEdgeSegmentsAuto
	Description :	Destructor
	Access :		Public

	Return :		void
	Parameters :	none
	============================================================ */
{
}


void CProMoEdgeSegmentsAuto::SetElementAutoObject(CProMoElementAuto* pElementAuto) 
/* ============================================================
	Function :		CProMoEdgeSegmentsAuto::SetElementAutoObject
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

BEGIN_MESSAGE_MAP(CProMoEdgeSegmentsAuto, CProMoEdgeChildAuto)
	//{{AFX_MSG_MAP(CProMoEdgeSegmentsAuto)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

BEGIN_DISPATCH_MAP(CProMoEdgeSegmentsAuto, CProMoEdgeChildAuto)
	//{{AFX_DISPATCH_MAP(CProMoEdgeSegmentsAuto)
	DISP_FUNCTION(CProMoEdgeSegmentsAuto, "Count", Count, VT_I2, VTS_NONE)
	//Common to CProMoElementChildAuto
	DISP_FUNCTION(CProMoElementChildAuto, "Element", Element, VT_DISPATCH, VTS_NONE)
	//Common to CProMoDiagramChildAuto
	DISP_FUNCTION(CProMoDiagramChildAuto, "Diagram", Diagram, VT_DISPATCH, VTS_NONE)
	//Common to CProMoAppChildAuto
	DISP_FUNCTION(CProMoAppChildAuto, "Application", Application, VT_DISPATCH, VTS_NONE)
	//Default property
	DISP_PROPERTY_PARAM(CProMoEdgeSegmentsAuto, "Item", GetItem, SetItem, VT_DISPATCH, VTS_I2)
	DISP_DEFVALUE(CProMoEdgeSegmentsAuto, "Item")
	//}}AFX_DISPATCH_MAP
END_DISPATCH_MAP()

// Note: we add support for IID_IProMoEdgeSegments to support typesafe binding
//  from VBA.  This IID must match the GUID that is attached to the 
//  dispinterface in the .ODL file.

// {38EA3764-08C3-11F1-9744-000C2976A615}
static const IID IID_IProMoEdgeSegmentsAuto =
{ 0x38ea3764, 0x8c3, 0x11f1, { 0x97, 0x44, 0x0, 0xc, 0x29, 0x76, 0xa6, 0x15 } };

BEGIN_INTERFACE_MAP(CProMoEdgeSegmentsAuto, CProMoEdgeChildAuto)
	INTERFACE_PART(CProMoEdgeSegmentsAuto, IID_IProMoEdgeSegmentsAuto, Dispatch)
END_INTERFACE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CProMoEdgeSegmentsAuto message handlers

short CProMoEdgeSegmentsAuto::Count() 
/* ============================================================
	Function :		CProMoEdgeSegmentsAuto::Count
	Description :	Returns the number of segments composing this edge.
	Access :		Public

	Return :		short	-	the number of segments composing this edge
	Parameters :	none
   ============================================================ */
{
	if (GetEdgeModel()) {
		CObArray edgeViews;
		GetEdgeModel()->GetViews(edgeViews);
		return edgeViews.GetSize();
	}

	return 0;
}

LPDISPATCH CProMoEdgeSegmentsAuto::GetItem(short Item)
/* ============================================================
	Function :		CProMoEdgeSegmentsAuto::GetItem
	Description :	Returns the segment automation object corresponding
					to the specified index.
	Access :		Public

	Return :		LPDISPATCH	-	a pointer to the IDispatch interface of
									the segment automation object corresponding
									to the specified index, or "NULL" if no
									segment automation object corresponds to
									the specified index.
	Parameters :	short Item -	the index of the segment automation object
									to return.
   ============================================================ */
{
	if (GetEdgeModel()) {
		CProMoEdgeView* pView = GetEdgeModel()->GetFirstSegment();
		for (int i = 1; pView && i < Item; i++) {
			pView = dynamic_cast<CProMoEdgeView*>(pView->GetDestination());
		}
		if (pView) {
			CProMoEdgeSegmentAuto* pElementAuto = dynamic_cast<CProMoEdgeSegmentAuto*>(pView->GetAutomationObject());
			if (pElementAuto) {
				pElementAuto->SetElementAutoObject(GetElementAutoObject());
				return pElementAuto->GetIDispatch(TRUE);
			}
		}
	}

	return NULL;
}

void CProMoEdgeSegmentsAuto::SetItem(short Item, LPDISPATCH newValue) 
/* ============================================================
	Function :		CProMoEdgeSegmentsAuto::SetItem
	Description :	Sets the segment automation object corresponding
					to the specified index. This property is read-only,
					so this function simply raises an exception.
	Access :		Public

	Return :		void
	Parameters :	short Item			-	the index of the segment automation object
											to set.
					LPDISPATCH newValue	-	a pointer to the new IDispatch interface of
											the segment automation object to set for the
											specified index.
   ============================================================ */
{
	SetNotSupported();

}
