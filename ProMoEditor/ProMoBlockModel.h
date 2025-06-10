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
	
	virtual void LinkSubBlock(CProMoBlockModel* subblock);
	virtual void UnlinkSubBlock(CProMoBlockModel* subblock);
	virtual void UnlinkAllSubBlocks();
	virtual CObArray* GetSubBlocks();
	virtual void SetParentBlock(CProMoBlockModel* parent);
	virtual CProMoBlockModel* GetParentBlock() const;
	virtual BOOL Contains(CProMoBlockModel* block, BOOL recursive);
	virtual BOOL CanBeNested(CProMoBlockModel* block);

	virtual void LinkOutgoingEdge(CProMoEdgeModel* edge);
	virtual void UnlinkOutgoingEdge(CProMoEdgeModel* edge);
	virtual void UnlinkAllOutgoingEdges();
	virtual CObArray* GetOutgoingEdges();
	virtual void LinkIncomingEdge(CProMoEdgeModel* edge);
	virtual void UnlinkIncomingEdge(CProMoEdgeModel* edge);
	virtual void UnlinkAllIncomingEdges();
	virtual CObArray* GetIncomingEdges();
	virtual CProMoBlockView* GetMainView() const;

	static	CProMoModel* CreateFromString(const CString& str);

	

protected:
	CObArray m_subblocks;
	CObArray m_outgoingEdges;
	CObArray m_incomingEdges;
	CProMoBlockModel* m_parentBlock;

	virtual CString				GetDefaultGetString() const;

};
#endif //_PROMOBLOCKMODEL_H_
