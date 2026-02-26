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

BEGIN_INTERFACE_MAP(CProMoEdgeChildAuto, CProMoElementChildAuto)
END_INTERFACE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CProMoEdgeChildAuto message handlers
