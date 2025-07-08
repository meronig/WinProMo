#ifndef _BOOLPROPERTYITEM_H_
#define _BOOLPROPERTYITEM_H_

#include "PropertyItem.h"
#include "../DiagramEditor/DiagramEntity.h"
#include "../DiagramEditor/DiagramEditor.h"

class AFX_EXT_CLASS CBoolPropertyItem : public CPropertyItem
{
protected:
    BOOL m_value;           // Current value (as string)

    // Wrapper: set the property value on the target, from a string
    typedef BOOL(*SetPropertyWrapper)(CDiagramEntity*, CDiagramEditor*, const BOOL&);
    SetPropertyWrapper m_setter;

public:
    CBoolPropertyItem(const CString& name,
        CDiagramEntity* target,
        CDiagramEditor* editor,
        SetPropertyWrapper setter,
        const BOOL& initialValue);
    virtual BOOL SetValue(const BOOL& val);
    virtual const BOOL GetValue();
};

#endif //_BOOLPROPERTYITEM_H_