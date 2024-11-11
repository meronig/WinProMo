#ifndef _PROCESSLINEEDGEMODEL_H_
#define _PROCESSLINEEDGEMODEL_H_

#include "ProcessModel.h"
#include "ProcessLineEdgeView.h"
#include "ProcessEntityBlockModel.h"

class CProcessLineEdgeModel : public CProcessModel
{

public:
    CProcessLineEdgeModel();
    virtual ~CProcessLineEdgeModel();
    virtual	CProcessModel* Clone();
    virtual void SetSource(CProcessModel* source);
    virtual void SetDestination(CProcessModel* destination);
    virtual CProcessModel* GetSource() const;
    virtual CProcessModel* GetDestination() const;
    virtual bool canConnectSource(CProcessModel* source);
    virtual bool canConnectDestination(CProcessModel* destination);
    virtual CProcessLineEdgeView* getLastSegment();
    virtual CProcessLineEdgeView* getFirstSegment();


protected:
    CProcessModel* m_source;
    CProcessModel* m_dest;

};

#endif //_PROCESSLINEEDGEVIEW_H_