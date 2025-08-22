/* ==========================================================================

    Copyright © 2025 Technical University of Denmark

    Author :		Giovanni Meroni

   ========================================================================*/
#ifndef _PROPERTYITEM_H_
#define _PROPERTYITEM_H_

#include "../DiagramEditor/DiagramEntity.h"
#include "../DiagramEditor/DiagramEditor.h"

class AFX_EXT_CLASS CPropertyItem : public CObject {

protected:
    CString m_name;            // Property label
    CDiagramEntity* m_target; // The object owning this property
    CDiagramEditor* m_editor; // The editor managing the object

    // Control ID (assigned dynamically when created)
    UINT m_ctrlID;
public:
    CPropertyItem(const CString& name,
        CDiagramEntity* target,
        CDiagramEditor* editor);
    
    virtual const CString GetName();
    virtual const UINT GetCtrlID();
    virtual void SetCtrlID(UINT ctrlID);
};

#endif //_PROPERTYITEM_H_