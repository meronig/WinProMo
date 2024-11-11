#ifndef _PROCESSMODEL_H_
#define _PROCESSMODEL_H_

#include "../StdAfx.h"
#include "../DiagramEditor/DiagramEntity.h"

class CProcessModel : public CObject
{
public:
	virtual void linkView(CDiagramEntity* view);
	virtual void unlinkView(CDiagramEntity* view);
	virtual void unlinkViews();
	virtual CObArray* getViews();

protected:
	CObArray m_views;
};

#endif //_PROCESSMODEL_H_