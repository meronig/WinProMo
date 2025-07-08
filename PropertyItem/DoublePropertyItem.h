#ifndef _DOUBLEPROPERTYITEM_H_
#define _DOUBLEPROPERTYITEM_H_

#include "PropertyItem.h"
#include "../DiagramEditor/DiagramEntity.h"
#include "../DiagramEditor/DiagramEditor.h"

class AFX_EXT_CLASS CDoublePropertyItem : public CPropertyItem
{
protected:
    double m_value;           // Current value (as string)

    // Wrapper: set the property value on the target, from a string
    typedef BOOL(*SetPropertyWrapper)(CDiagramEntity*, CDiagramEditor*, const double&);
    SetPropertyWrapper m_setter;

public:
    CDoublePropertyItem(const CString& name,
        CDiagramEntity* target,
        CDiagramEditor* editor,
        SetPropertyWrapper setter,
        const double& initialValue);
    virtual BOOL SetValue(const double& val);
    virtual const double GetValue();
};

#endif //_DOUBLEPROPERTYITEM_H_