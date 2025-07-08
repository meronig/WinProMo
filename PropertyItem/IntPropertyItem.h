#ifndef _LISTPROPERTYITEM_H_
#define _LISTPROPERTYITEM_H_

#include "PropertyItem.h"
#include "../DiagramEditor/DiagramEntity.h"
#include "../DiagramEditor/DiagramEditor.h"

class AFX_EXT_CLASS CIntPropertyItem : public CPropertyItem
{
protected:
    int m_value;           // Current value (as string)

    // Wrapper: set the property value on the target, from a string
    typedef BOOL(*SetPropertyWrapper)(CDiagramEntity*, CDiagramEditor*, const int&);
    SetPropertyWrapper m_setter;

public:
    CIntPropertyItem(const CString& name,
        CDiagramEntity* target,
        CDiagramEditor* editor,
        SetPropertyWrapper setter,
        const int& initialValue);
    virtual BOOL SetValue(const int& val);
    virtual const int GetValue();
    
};

#endif //_LISTPROPERTYITEM_H_