/* ==========================================================================

	Copyright © 2025 Technical University of Denmark

	Author :		Giovanni Meroni

   ========================================================================*/
#ifndef _PROPERTYWRAPPERS_H_
#define _PROPERTYWRAPPERS_H_

#include "../DiagramEditor/DiagramEntity.h"
#include "../DiagramEditor/DiagramEditor.h"

BOOL SetShapeTitle(CDiagramEntity* entity, CDiagramEditor* editor, const CString& val);
BOOL SetShapeName(CDiagramEntity* entity, CDiagramEditor* editor, const CString& val);

#endif //_PROPERTYWRAPPERS_H_
