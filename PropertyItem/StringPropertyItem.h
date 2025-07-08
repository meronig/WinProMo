#ifndef _STRINGPROPERTYITEM_H_
#define _STRINGPROPERTYITEM_H_

#include "PropertyItem.h"
#include "../DiagramEditor/DiagramEntity.h"
#include "../DiagramEditor/DiagramEditor.h"
#include <afxtempl.h>

class AFX_EXT_CLASS CStringPropertyItem : public CPropertyItem
{
protected:
    CString m_value;           // Current value (as string)
    CArray <CString, CString> m_options;
    
    // Wrapper: set the property value on the target, from a string
    typedef BOOL (*SetPropertyWrapper)(CDiagramEntity*, CDiagramEditor*, const CString&);
    SetPropertyWrapper m_setter;

public:
    CStringPropertyItem(const CString& name,
        CDiagramEntity* target,
        CDiagramEditor* editor,
        SetPropertyWrapper setter,
        const CString& initialValue);
    virtual BOOL SetValue(const CString& val);
    virtual const CString GetValue();
    virtual void AddOption(const CString& option);
    virtual int GetOptionsCount();
    virtual const CString& GetOption(const int& index);
};

#endif //_STRINGPROPERTYITEM_H_