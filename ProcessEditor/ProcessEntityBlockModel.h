#ifndef _PROCESSENTITYBLOCKMODEL_H_
#define _PROCESSENTITYBLOCKMODEL_H_

#include "ProcessModel.h"
//#include "ProcessLineEdgeModel.h"
//#include "ProcessEntityBlockView.h"

class CProcessEntityBlockView;

class CProcessEntityBlockModel : public CProcessModel
{
public:
	friend class CProcessLineEdgeModel;
	CProcessEntityBlockModel();
	virtual ~CProcessEntityBlockModel();
	virtual CProcessModel* Clone();
	
	virtual void linkSubBlock(CProcessEntityBlockModel* subblock);
	virtual void unlinkSubBlock(CProcessEntityBlockModel* subblock);
	virtual void unlinkSubBlocks();
	virtual CObArray* getSubBlocks();
	virtual void setParentBlock(CProcessEntityBlockModel* parent);
	virtual CProcessEntityBlockModel* getParentBlock() const;
	virtual BOOL contains(CProcessEntityBlockModel* block, BOOL recursive);
	virtual BOOL canBeNested(CProcessEntityBlockModel* block);

	virtual void linkOutgoingEdge(CProcessLineEdgeModel* edge);
	virtual void unlinkOutgoingEdge(CProcessLineEdgeModel* edge);
	virtual void unlinkOutgoingEdges();
	virtual CObArray* getOutgoingEdges();
	virtual void linkIncomingEdge(CProcessLineEdgeModel* edge);
	virtual void unlinkIncomingEdge(CProcessLineEdgeModel* edge);
	virtual void unlinkIncomingEdges();
	virtual CObArray* getIncomingEdges();
	virtual CProcessEntityBlockView* getMainView() const;

	static	CProcessModel* CreateFromString(const CString& str);

	

protected:
	CObArray m_subblocks;
	CObArray m_outgoingEdges;
	CObArray m_incomingEdges;
	CProcessEntityBlockModel* parentBlock;

	virtual CString				GetDefaultGetString() const;

};
#endif //_PROCESSENTITYBLOCKMODEL_H_
