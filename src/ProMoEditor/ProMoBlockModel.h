/* ==========================================================================

	Copyright © 2025 Technical University of Denmark

	Author :		Giovanni Meroni

   ========================================================================*/
#ifndef _PROMOBLOCKMODEL_H_
#define _PROMOBLOCKMODEL_H_

#include "ProMoModel.h"

class AFX_EXT_CLASS CProMoBlockView;

class AFX_EXT_CLASS CProMoBlockModel : public CProMoModel
{
public:
	friend class CProMoEdgeModel;
	friend class CProMoBlockView;
	
	// Creation/initialization
	CProMoBlockModel();
	virtual ~CProMoBlockModel();
	
	virtual CProMoModel* Clone();
	
	// Parent-child block links
	virtual CObArray* GetSubBlocks();
	virtual CProMoBlockModel* GetParentBlock() const;
	virtual BOOL Contains(CProMoBlockModel* block, BOOL recursive);
	virtual BOOL CanBeNestedBy(CProMoBlockModel* block);

	// Outgoing edge links
	virtual CObArray* GetOutgoingEdges();
	
	// Incoming edge links
	virtual CObArray* GetIncomingEdges();
	
	// Model-view links
	virtual CProMoBlockView* GetMainView() const;

	static CString GetParentFromString(const CString& str);
	

protected:
	CObArray m_subblocks;
	CObArray m_outgoingEdges;
	CObArray m_incomingEdges;
	CProMoBlockModel* m_parentBlock;

	// Parent-child block links
	virtual void LinkSubBlock(CProMoBlockModel* subblock);
	virtual void UnlinkSubBlock(CProMoBlockModel* subblock);
	virtual void UnlinkAllSubBlocks();
	virtual void SetParentBlock(CProMoBlockModel* parent);
	
	// Outgoing edge links
	virtual void LinkOutgoingEdge(CProMoEdgeModel* edge);
	virtual void UnlinkOutgoingEdge(CProMoEdgeModel* edge);
	virtual void UnlinkAllOutgoingEdges();
	
	// Incoming edge links
	virtual void LinkIncomingEdge(CProMoEdgeModel* edge);
	virtual void UnlinkIncomingEdge(CProMoEdgeModel* edge);
	virtual void UnlinkAllIncomingEdges();
	

	//Overrides
public:
	static	CProMoModel* CreateFromString(const CString& str);

protected:
	virtual CString				GetDefaultGetString() const;

};
#endif //_PROMOBLOCKMODEL_H_
