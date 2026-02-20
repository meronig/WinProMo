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
{
}

CProMoEdgeSegmentsAuto::~CProMoEdgeSegmentsAuto()
{
}


void CProMoEdgeSegmentsAuto::SetElementAutoObject(CProMoElementAuto* pElementAuto) {
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
	DISP_FUNCTION(CProMoEdgeSegmentsAuto, "Count", Count, VT_I4, VTS_NONE)
	DISP_PROPERTY_PARAM(CProMoEdgeSegmentsAuto, "Item", GetItem, SetItem, VT_DISPATCH, VTS_I4)
	DISP_DEFVALUE(CProMoEdgeSegmentsAuto, "Item")
	//}}AFX_DISPATCH_MAP
END_DISPATCH_MAP()

// Note: we add support for IID_IProMoEdgeSegments to support typesafe binding
//  from VBA.  This IID must match the GUID that is attached to the 
//  dispinterface in the .ODL file.

// {18EA376E-08C3-11F1-9744-000C2976A615}
static const IID IID_IProMoEdgeSegmentsAuto =
{ 0x18ea376e, 0x8c3, 0x11f1, { 0x97, 0x44, 0x0, 0xc, 0x29, 0x76, 0xa6, 0x15 } };

BEGIN_INTERFACE_MAP(CProMoEdgeSegmentsAuto, CProMoEdgeChildAuto)
	INTERFACE_PART(CProMoEdgeSegmentsAuto, IID_IProMoEdgeSegmentsAuto, Dispatch)
END_INTERFACE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CProMoEdgeSegmentsAuto message handlers

long CProMoEdgeSegmentsAuto::Count() 
{
	if (GetEdgeModel()) {
		CObArray edgeViews;
		GetEdgeModel()->GetViews(edgeViews);
		return (long)edgeViews.GetSize();
	}

	return 0;
}

LPDISPATCH CProMoEdgeSegmentsAuto::GetItem(long Item) 
{
	if (GetEdgeModel()) {
		CProMoEdgeView* pView = GetEdgeModel()->GetFirstSegment();
		for (int i = 0; pView && i < Item; i++) {
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

void CProMoEdgeSegmentsAuto::SetItem(long Item, LPDISPATCH newValue) 
{
	SetNotSupported();

}
