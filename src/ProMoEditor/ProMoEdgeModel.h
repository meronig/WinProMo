/* ==========================================================================

    Copyright © 2025 Technical University of Denmark

    Author :		Giovanni Meroni

   ========================================================================*/
#ifndef _PROMOEDGEMODEL_H_
#define _PROMOEDGEMODEL_H_

#include "ProMoModel.h"
#include "ProMoEdgeView.h"
#include "ProMoBlockModel.h"

class AFX_EXT_CLASS CProMoEdgeModel : public CProMoModel
{

public:
    friend class CProMoEdgeView;
    friend class CProMoBlockModel;

    // Creation/initialization
    CProMoEdgeModel();
    virtual ~CProMoEdgeModel();
    
    virtual	CProMoModel* Clone();

    // Source links
    virtual CProMoBlockModel* GetSource() const;
    virtual BOOL CanConnectSource(CProMoBlockModel* source);

    // Destination links
    virtual CProMoBlockModel* GetDestination() const;
    virtual BOOL CanConnectDestination(CProMoBlockModel* destination);

    // Model-view links
    virtual CProMoEdgeView* GetLastSegment();
    virtual CProMoEdgeView* GetFirstSegment();

    
protected:
    virtual void SetSource(CProMoBlockModel* source);
    virtual void SetDestination(CProMoBlockModel* destination);

    CProMoBlockModel* m_source;
    CProMoBlockModel* m_dest;

// Overrides
public:
    static	CProMoModel* CreateFromString(const CString& str);

protected:
    virtual CString				GetDefaultGetString() const;


};

#endif //_PROMOEDGEMODEL_H_