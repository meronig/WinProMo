#ifndef _PROMOCONTROLFACTORY_H_
#define _PROMOCONTROLFACTORY_H_

#include "../DiagramEditor/DiagramEntity.h"
#include "ProMoModel.h"

class CProMoControlFactory {

public:
// Implementation
	CDiagramEntity* CreateViewFromString( const CString& str );
	CProMoModel* CreateModelFromString(const CString& str);

};

#endif // _PROMOCONTROLFACTORY_H_