/* ==========================================================================

	Copyright © 2026 Technical University of Denmark

	CProMoEdgeChildAuto

	Author :		Giovanni Meroni

	Purpose :		"CProMoEdgeChildAuto" is an automation object that
					represents an edge of a diagram element.

	Description :	"CProMoEdgeChildAuto" is used to provide access to the
					edge automation object and to manage the lifetime of the
					automation objects. By extending "CProMoElementChildAuto", it
					provides access to the diagram.

	Usage :			Derived classes should use the "GetEdgeModel" method to get 
					the model of the edge, which is used to manage the properties 
					of the edge.

   ========================================================================*/
#include "stdafx.h"
#include "ProMoEdgeChildAuto.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CProMoEdgeChildAuto

IMPLEMENT_DYNCREATE(CProMoEdgeChildAuto, CProMoElementChildAuto)

CProMoEdgeChildAuto::CProMoEdgeChildAuto()
{
}

CProMoEdgeModel* CProMoEdgeChildAuto::GetEdgeModel()
{
	return dynamic_cast<CProMoEdgeModel*>(GetModel());
}

CProMoEdgeChildAuto::~CProMoEdgeChildAuto()
{
}


BEGIN_MESSAGE_MAP(CProMoEdgeChildAuto, CProMoElementChildAuto)
	//{{AFX_MSG_MAP(CProMoEdgeChildAuto)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

BEGIN_DISPATCH_MAP(CProMoEdgeChildAuto, CProMoElementChildAuto)
	//{{AFX_DISPATCH_MAP(CProMoEdgeChildAuto)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_DISPATCH_MAP
END_DISPATCH_MAP()

// Note: we add support for IID_IProMoEdgeChildAuto to support typesafe binding
//  from VBA.  This IID must match the GUID that is attached to the 
//  dispinterface in the .ODL file.

// {18EA3778-08C3-11F1-9744-000C2976A615}
static const IID IID_IProMoEdgeChildAuto =
{ 0x18ea3778, 0x8c3, 0x11f1, { 0x97, 0x44, 0x0, 0xc, 0x29, 0x76, 0xa6, 0x15 } };

BEGIN_INTERFACE_MAP(CProMoEdgeChildAuto, CProMoElementChildAuto)
	INTERFACE_PART(CProMoEdgeChildAuto, IID_IProMoEdgeChildAuto, Dispatch)
END_INTERFACE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CProMoEdgeChildAuto message handlers
