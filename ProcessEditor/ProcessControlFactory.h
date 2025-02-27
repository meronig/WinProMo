#ifndef _PROCESSCONTROLFACTORY_H_
#define _PROCESSCONTROLFACTORY_H_

#include "../DiagramEditor/DiagramEntity.h"
#include "ProcessModel.h"

class CProcessControlFactory {

public:
// Implementation
	static CDiagramEntity* CreateViewFromString( const CString& str );
	static CProcessModel* CreateModelFromString(const CString& str);

};

#endif // _PROCESSCONTROLFACTORY_H_