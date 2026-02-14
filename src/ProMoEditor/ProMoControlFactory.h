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
	virtual CDiagramEntity* CreateViewFromString(const CString& str, CProMoModel* model);
	virtual CDiagramEntity* CreateLabelFromString(const CString& str);
	virtual CDiagramEntity* CreateLabelFromString(const CString& str, CProMoModel* model);
	virtual CProMoModel* CreateModelFromString(const CString& str);
	virtual CDiagramEntity* CreateNewEntity(const CString& str);
	virtual void GetEntityTypes(CStringArray& typeList);

};

#endif // _PROMOCONTROLFACTORY_H_