/* ==========================================================================

	Copyright © 2025-26 Technical University of Denmark

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
	virtual CDiagramEntity* CreateViewFromString( const CString& str ) = 0;
	virtual CDiagramEntity* CreateViewFromString(const CString& str, CProMoModel* model) = 0;
	virtual CDiagramEntity* CreateLabelFromString(const CString& str);
	virtual CDiagramEntity* CreateLabelFromString(const CString& str, CProMoModel* model);
	virtual CProMoModel* CreateModelFromString(const CString& str) = 0;
	virtual CDiagramEntity* CreateNewEntity(const CString& str) = 0;
	virtual void GetEntityTypes(CStringArray& typeList) = 0;

};

#endif // _PROMOCONTROLFACTORY_H_