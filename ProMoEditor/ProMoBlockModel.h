#ifndef _PROMOBLOCKMODEL_H_
#define _PROMOBLOCKMODEL_H_

#include "ProMoModel.h"

class CProMoBlockView;

class CProMoBlockModel : public CProMoModel
{
public:
	friend class CProMoEdgeModel;
	CProMoBlockModel();
	virtual ~CProMoBlockModel();
	virtual CProMoModel* Clone();
	
	virtual void linkSubBlock(CProMoBlockModel* subblock);
	virtual void unlinkSubBlock(CProMoBlockModel* subblock);
	virtual void unlinkSubBlocks();
	virtual CObArray* getSubBlocks();
	virtual void setParentBlock(CProMoBlockModel* parent);
	virtual CProMoBlockModel* getParentBlock() const;
	virtual BOOL contains(CProMoBlockModel* block, BOOL recursive);
	virtual BOOL canBeNested(CProMoBlockModel* block);

	virtual void linkOutgoingEdge(CProMoEdgeModel* edge);
	virtual void unlinkOutgoingEdge(CProMoEdgeModel* edge);
	virtual void unlinkOutgoingEdges();
	virtual CObArray* getOutgoingEdges();
	virtual void linkIncomingEdge(CProMoEdgeModel* edge);
	virtual void unlinkIncomingEdge(CProMoEdgeModel* edge);
	virtual void unlinkIncomingEdges();
	virtual CObArray* getIncomingEdges();
	virtual CProMoBlockView* getMainView() const;

	static	CProMoModel* CreateFromString(const CString& str);

	

protected:
	CObArray m_subblocks;
	CObArray m_outgoingEdges;
	CObArray m_incomingEdges;
	CProMoBlockModel* m_parentBlock;

	virtual CString				GetDefaultGetString() const;

};
#endif //_PROMOBLOCKMODEL_H_
