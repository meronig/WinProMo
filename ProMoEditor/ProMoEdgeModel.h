#ifndef _PROMOEDGEMODEL_H_
#define _PROMOEDGEMODEL_H_

#include "ProMoModel.h"
#include "ProMoEdgeView.h"
#include "ProMoBlockModel.h"

class CProMoEdgeModel : public CProMoModel
{

public:
    CProMoEdgeModel();
    virtual ~CProMoEdgeModel();
    virtual	CProMoModel* Clone();
    virtual void SetSource(CProMoModel* source);
    virtual void SetDestination(CProMoModel* destination);
    virtual CProMoModel* GetSource() const;
    virtual CProMoModel* GetDestination() const;
    virtual BOOL canConnectSource(CProMoModel* source);
    virtual BOOL canConnectDestination(CProMoModel* destination);
    virtual CProMoEdgeView* getLastSegment();
    virtual CProMoEdgeView* getFirstSegment();

    static	CProMoModel* CreateFromString(const CString& str);

protected:
    CProMoModel* m_source;
    CProMoModel* m_dest;

    virtual CString				GetDefaultGetString() const;


};

#endif //_PROMOEDGEMODEL_H_