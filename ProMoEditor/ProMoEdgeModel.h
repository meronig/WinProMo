#ifndef _PROMOEDGEMODEL_H_
#define _PROMOEDGEMODEL_H_

#include "ProMoModel.h"
#include "ProMoEdgeView.h"
#include "ProMoBlockModel.h"

class CProMoEdgeModel : public CProMoModel
{

public:
    // Creation/initialization
    CProMoEdgeModel();
    virtual ~CProMoEdgeModel();
    
    virtual	CProMoModel* Clone();

    // Source links
    virtual void SetSource(CProMoModel* source);
    virtual CProMoModel* GetSource() const;
    virtual BOOL CanConnectSource(CProMoModel* source);

    // Destination links
    virtual void SetDestination(CProMoModel* destination);
    virtual CProMoModel* GetDestination() const;
    virtual BOOL CanConnectDestination(CProMoModel* destination);

    // Model-view links
    virtual CProMoEdgeView* GetLastSegment();
    virtual CProMoEdgeView* GetFirstSegment();

    
protected:
    CProMoModel* m_source;
    CProMoModel* m_dest;

// Overrides
public:
    static	CProMoModel* CreateFromString(const CString& str);

protected:
    virtual CString				GetDefaultGetString() const;


};

#endif //_PROMOEDGEMODEL_H_