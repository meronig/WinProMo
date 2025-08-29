/* ==========================================================================

    Copyright © 2025 Technical University of Denmark

    Author :		Giovanni Meroni

   ========================================================================*/
#ifndef _CUSTOMPROPERTYITEM_H_
#define _CUSTOMPROPERTYITEM_H_

#include "PropertyItem.h"
#include "../DiagramEditor/DiagramEntity.h"
#include "../DiagramEditor/DiagramEditor.h"

class AFX_EXT_CLASS CCustomPropertyItem :
    public CPropertyItem
{
protected:
    // Wrapper: set the property value on the target, from a string
    typedef BOOL(*SetPropertyWrapper)(CDiagramEntity*, CDiagramEditor*);
    SetPropertyWrapper m_setter;

public:
    CCustomPropertyItem(const CString& name,
        CDiagramEntity* target,
        CDiagramEditor* editor,
        SetPropertyWrapper setter);
    virtual BOOL SetValue();
    
};

#endif //_CUSTOMPROPERTYITEM_H_