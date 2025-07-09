#ifndef _TYPEDPROPERTYITEM_H_
#define _TYPEDPROPERTYITEM_H_

#include "PropertyItem.h"
#include "../DiagramEditor/DiagramEntity.h"
#include "../DiagramEditor/DiagramEditor.h"
#include <afxtempl.h>

template <class T> 
class CTypedPropertyItem : public CPropertyItem
{
protected:
    T m_value;           // Current value (as string)
    CArray <T, T> m_options;

    // Wrapper: set the property value on the target, from a string
    typedef BOOL(*SetPropertyWrapper)(CDiagramEntity*, CDiagramEditor*, const T&);
    SetPropertyWrapper m_setter;

public:
    CTypedPropertyItem(const CString& name,
        CDiagramEntity* target,
        CDiagramEditor* editor,
        SetPropertyWrapper setter,
        const T& initialValue);
    virtual BOOL SetValue(const T& val);
    virtual const T GetValue();
    virtual void AddOption(const T& option);
    virtual int GetOptionsCount();
    virtual const T& GetOption(const int& index);
};

#include "TypedPropertyItem.hxx"

template AFX_EXT_CLASS class CTypedPropertyItem<CString>;
template AFX_EXT_CLASS class CTypedPropertyItem<UINT>;

#endif //_TYPEDPROPERTYITEM_H_
