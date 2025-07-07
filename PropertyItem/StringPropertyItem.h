#ifndef _STRINGPROPERTYITEM_H_
#define _STRINGPROPERTYITEM_H_

#include "PropertyItem.h"
#include "../DiagramEditor/DiagramEntity.h"
#include "../DiagramEditor/DiagramEditor.h"

class AFX_EXT_CLASS CStringPropertyItem : public CPropertyItem
{
protected:
    CString m_value;           // Current value (as string)
    
    // Wrapper: set the property value on the target, from a string
    typedef BOOL (*SetPropertyWrapper)(CDiagramEntity*, CDiagramEditor*, const CString&);
    SetPropertyWrapper m_setter;

public:
    CStringPropertyItem(const CString& name,
        CDiagramEntity* target,
        CDiagramEditor* editor,
        SetPropertyWrapper setter,
        CString initialValue);
    virtual BOOL SetValue(const CString& val);
    virtual CString GetValue();
};

#endif //_PROPERTYITEM_H_