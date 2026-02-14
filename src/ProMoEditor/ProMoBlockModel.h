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
	virtual void GetSubBlocks(CObArray& blockList) const;
	virtual BOOL CanBeSubBlockOf(CProMoBlockModel* block) const;
	virtual BOOL HasSubBlock(CProMoBlockModel* block) const;
	virtual BOOL IsSubBlock() const;
	virtual void GetBoundaryBlocks(CObArray& blockList, unsigned int alignment) const;
	virtual BOOL CanBeBoundaryOf(CProMoBlockModel* block, unsigned int alignment) const;
	virtual BOOL HasBoundaryBlock(CProMoBlockModel* block) const;
	virtual BOOL IsBoundaryBlock() const;
	virtual unsigned int GetBoundaryAttachment() const;
	virtual CProMoBlockModel* GetParentBlock() const;

	// Outgoing edge links
	virtual void GetOutgoingEdges(CObArray& edgeList) const;
	
	// Incoming edge links
	virtual void GetIncomingEdges(CObArray& edgeList) const;
	
	// Model-view links
	virtual CProMoBlockView* GetMainView() const;

	static CString GetParentFromString(const CString& str);
	static unsigned int GetAttachmentTypeFromString(const CString& str);
	

protected:
	CObArray m_subblocks;
	CObArray m_outgoingEdges;
	CObArray m_incomingEdges;
	CProMoBlockModel* m_parentBlock;
	unsigned int m_attachmentType;

	// Parent-child block links
	virtual BOOL Contains(CProMoBlockModel* block, BOOL recursive) const;
	virtual void LinkChildBlock(CProMoBlockModel* subblock, unsigned int attachment);
	virtual void UnlinkChildBlock(CProMoBlockModel* subblock);
	virtual void UnlinkAllChildBlocks();
	virtual void SetParentBlock(CProMoBlockModel* parent, unsigned int attachment);
	
	// Outgoing edge links
	virtual void LinkOutgoingEdge(CProMoEdgeModel* edge);
	virtual void UnlinkOutgoingEdge(CProMoEdgeModel* edge);
	virtual void UnlinkAllOutgoingEdges();
	
	// Incoming edge links
	virtual void LinkIncomingEdge(CProMoEdgeModel* edge);
	virtual void UnlinkIncomingEdge(CProMoEdgeModel* edge);
	virtual void UnlinkAllIncomingEdges();
	
	virtual void CustomizeLabel(CProMoLabel* label);

	//Overrides
public:
	static	CProMoModel* CreateFromString(const CString& str);

	virtual CProMoAppChildAuto* GetAutomationObject();

protected:
	virtual CString				GetDefaultGetString() const;

};
#endif //_PROMOBLOCKMODEL_H_
