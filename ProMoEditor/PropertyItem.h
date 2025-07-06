#ifndef _PROPERTYITEM_H_
#define _PROPERTYITEM_H_

#include "../DiagramEditor/DiagramEntity.h"
#include "../DiagramEditor/DiagramEditor.h"

class AFX_EXT_CLASS CPropertyItem : public CObject
{
public:
    CString m_name;            // Property label
    CString m_value;           // Current value (as string)
    CDiagramEntity* m_target; // The object owning this property
    CDiagramEditor* m_editor; // The editor managing the object

    // Wrapper: set the property value on the target, from a string
    typedef BOOL (*SetPropertyWrapper)(CDiagramEntity*, CDiagramEditor*, const CString&);
    SetPropertyWrapper m_setter;

    //// Control type enum
    //enum ControlType { EDIT, COMBO, CHECKBOX };
    //ControlType m_controlType;

    // Control ID (assigned dynamically when created)
    UINT m_ctrlID;
public:
    CPropertyItem(const CString& name,
        CDiagramEntity* target,
        CDiagramEditor* editor,
        SetPropertyWrapper setter);
    BOOL SetValue(const CString& val);
};

#endif //_PROPERTYITEM_H_