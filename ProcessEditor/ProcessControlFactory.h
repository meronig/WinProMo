#ifndef _PROCESSCONTROLFACTORY_H_
#define _PROCESSCONTROLFACTORY_H_

#include "../DiagramEditor/DiagramEntity.h"

class CProcessControlFactory {

public:
// Implementation
	static CDiagramEntity* CreateFromString( const CString& str );

};

#endif // _PROCESSCONTROLFACTORY_H_