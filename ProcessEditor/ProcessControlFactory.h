#ifndef _PROCESSCONTROLFACTORY_H_
#define _PROCESSCONTROLFACTORY_H_

#include "../DiagramEditor/DiagramEntity.h"
#include "ProcessModel.h"

class CProcessControlFactory {

public:
// Implementation
	CDiagramEntity* CreateViewFromString( const CString& str );
	CProcessModel* CreateModelFromString(const CString& str);

};

#endif // _PROCESSCONTROLFACTORY_H_