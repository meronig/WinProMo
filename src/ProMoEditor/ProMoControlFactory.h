/* ==========================================================================

	Copyright © 2025 Technical University of Denmark

	Author :		Giovanni Meroni

   ========================================================================*/
#ifndef _PROMOCONTROLFACTORY_H_
#define _PROMOCONTROLFACTORY_H_

#include "../DiagramEditor/DiagramEntity.h"
#include "ProMoModel.h"

class AFX_EXT_CLASS CProMoControlFactory :
public CObject {

public:
// Implementation
	virtual CDiagramEntity* CreateViewFromString( const CString& str );
	virtual CProMoModel* CreateModelFromString(const CString& str);

};

#endif // _PROMOCONTROLFACTORY_H_