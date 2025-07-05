#ifndef _PROPERTYITEM_H_
#define _PROPERTYITEM_H_

#include "../DiagramEditor/DiagramEntity.h"

class AFX_EXT_CLASS CPropertyItem : public CObject
{
public:
    CString m_name;            // Property label
    CString m_value;           // Current value (as string)
    CDiagramEntity* m_target; // The object owning this property

    // Wrapper: set the property value on the target, from a string
    typedef void (*SetPropertyWrapper)(CDiagramEntity*, const CString&);
    SetPropertyWrapper m_setter;

    //// Control type enum
    //enum ControlType { EDIT, COMBO, CHECKBOX };
    //ControlType m_controlType;

    // Control ID (assigned dynamically when created)
    UINT m_ctrlID;
public:
    CPropertyItem(const CString& name,
        CDiagramEntity* target,
        SetPropertyWrapper setter);
    void SetValue(const CString& val);
};

#endif //_PROPERTYITEM_H_