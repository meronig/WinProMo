/* ==========================================================================

	Copyright © 2026 Technical University of Denmark

	CProMoBlockChildAuto

	Author :		Giovanni Meroni

	Purpose :		"CProMoBlockChildAuto" is an automation object that
					represents a block of a diagram element.

	Description :	"CProMoBlockChildAuto" is used to provide access to the
					block automation object and to manage the lifetime of the
					automation objects. By extending "CProMoElementChildAuto", it
					provides access to the diagram.

	Usage :			Derived classes should use the "GetBlockModel" method to get
					the model of the block, which is used to manage the properties
					of the block.

   ========================================================================*/
#include "stdafx.h"
#include "ProMoBlockChildAuto.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CProMoBlockChildAuto

IMPLEMENT_DYNCREATE(CProMoBlockChildAuto, CProMoElementChildAuto)

CProMoBlockChildAuto::CProMoBlockChildAuto()
{
}

CProMoBlockModel* CProMoBlockChildAuto::GetBlockModel()
{
	return dynamic_cast<CProMoBlockModel*>(GetModel());
}

CProMoBlockChildAuto::~CProMoBlockChildAuto()
{
}

BEGIN_MESSAGE_MAP(CProMoBlockChildAuto, CProMoElementChildAuto)
	//{{AFX_MSG_MAP(CProMoBlockChildAuto)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

BEGIN_DISPATCH_MAP(CProMoBlockChildAuto, CProMoElementChildAuto)
	//{{AFX_DISPATCH_MAP(CProMoBlockChildAuto)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_DISPATCH_MAP
END_DISPATCH_MAP()

BEGIN_INTERFACE_MAP(CProMoBlockChildAuto, CProMoElementChildAuto)
END_INTERFACE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CProMoBlockChildAuto message handlers
