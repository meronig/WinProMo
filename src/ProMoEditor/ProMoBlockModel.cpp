/* ==========================================================================
	
	Copyright © 2025 Technical University of Denmark

	CProMoBlockModel

	Author :		Giovanni Meroni

	Purpose :		"CProMoBlockModel" represents the model of all
					block/node objects (views) that can be drawn and managed 
					by "CProMoEditor".

	Description :	With respect to "CProMoModel", "CProMoBlockModel" can 
					nest other "CProMoBlockModel" objects. It also keeps
					track of incoming and outgoing "CProMoEdgeModel" objects.
					It is also assumed that a block model has 1 primary
					view, representing the block itself.

	Usage :			Models that represent a node in a graph should be 
					derived from this class.

   ========================================================================*/
#include "stdafx.h"
#include "ProMoBlockModel.h"
#include "ProMoEdgeModel.h"
#include "ProMoNameFactory.h"
#include "../DiagramEditor/Tokenizer.h"
#include "../FileUtils/FileParser.h"
#include "ProMoLabel.h"

CProMoBlockModel::CProMoBlockModel()
	/* ============================================================
	Function :		CProMoBlockModel::CProMoBlockModel
	Description :	Constructor
	Access :		Public

	Return :		void
	Parameters :	none

	Usage :

	============================================================*/
{
	SetType(_T("promo_block_model"));
	SetName(CProMoNameFactory::GetID());
	m_parentBlock = NULL;
	m_attachmentType = DEHT_NONE;
}

CProMoBlockModel::~CProMoBlockModel()
	/* ============================================================
	Function :		CProMoBlockModel::~CProMoBlockModel
	Description :	Destructor
	Access :		Public

	Return :		void
	Parameters :	none

	Usage :

   ============================================================*/
{
	UnlinkAllIncomingEdges();
	UnlinkAllOutgoingEdges();
	UnlinkAllChildBlocks();
	SetParentBlock(NULL,DEHT_BODY);
}

CProMoModel* CProMoBlockModel::Clone() {
	/* ============================================================
	Function :		CProMoBlockModel::Clone
	Description :	Clones this object and returns a new one.
	Access :		Public

	Return :		CProMoModel*	-	The resulting clone
	Parameters :	none

	Usage :			Call to clone the current object.

   ============================================================*/
	CProMoBlockModel* obj = new CProMoBlockModel;
	return obj;
}

BOOL CProMoBlockModel::CanBeSubBlockOf(CProMoBlockModel* block) const
/* ============================================================
	Function :		CProMoBlockModel::CanBeSubBlockOf
	Description :	Returns if this block can be a subblock of the
					block being passed as input	parameter.
					Override to implement diagram-specific logic.
	Access :		Public

	Return :		BOOL					-	"TRUE" if the 
												block can be 
												nested
	Parameters :	CProMoBlockModel* block	-	the block that
												should nest
												this block

   ============================================================*/
{
	if (this == block) {
		return FALSE;
	}
	if (Contains(block, TRUE)) {
		return FALSE;
	}
	return TRUE;
}

void CProMoBlockModel::GetSubBlocks(CObArray& subblocks) const
/* ============================================================
	Function :		CProMoBlockModel::GetSubBlocks
	Description :	Returns the subblocks for this node. A
					subblock is a child block that is not
					attached to the boundary of the parent block
	Access :		Public

	Return :		void
	Parameters :	CObArray subblocks	-	A CObArray to store the
											subblocks

   ============================================================*/
{
	for (int i = 0; i < m_subblocks.GetSize(); i++) {
		CProMoBlockModel* child = dynamic_cast<CProMoBlockModel*>(this->m_subblocks.GetAt(i));
		if (child && child->m_attachmentType == DEHT_BODY) {
			subblocks.Add(child);
		}
	}
}

BOOL CProMoBlockModel::HasSubBlock(CProMoBlockModel* block) const
/* ============================================================
	Function :		CProMoBlockModel::HasSubBlock
	Description :	Returns whether the block being passed is a
					subblock of this block. A subblock is a child
					block that is not attached to the boundary of
					the parent block
	Access :		Public

	Return :		BOOL					-	"TRUE" if the 
												block is a 
												subblock	
	Parameters :	CProMoBlockModel* block	-	The block that
												should be
												checked

   ============================================================*/
{
	if (Contains(block, FALSE) && block->IsSubBlock()) {
		return TRUE;
	}
	return FALSE;
}

BOOL CProMoBlockModel::IsSubBlock() const
/* ============================================================
	Function :		CProMoBlockModel::IsSubBlock
	Description :	Returns whether the current block is a
					subblock. A subblock is a child
					block that is not attached to the boundary of
					a parent block
	Access :		Public

	Return :		BOOL					-	"TRUE" if the
												block is a
												subblock
	Parameters :	none

   ============================================================*/
{
	if (m_parentBlock != NULL && m_attachmentType == DEHT_BODY) {
		return TRUE;
	}
	return FALSE;
}

void CProMoBlockModel::GetBoundaryBlocks(CObArray& blockList, unsigned int alignment) const
/* ============================================================
	Function :		CProMoBlockModel::GetBoundaryBlocks
	Description :	Returns the boundary blocks for this node. A
					boundary block is a child block that is
					attached to the boundary of the parent block
	Access :		Public

	Return :		void
	Parameters :	CObArray blockList		-	A CObArray to 
												store the
												boundary blocks
					unsigned int alignment	-	the alignment
												type of the
												boundary blocks
												to be returned.
												If DEHT_BODY is
												passed, all
												boundary blocks
												are returned

   ============================================================*/
{
	for (int i = 0; i < m_subblocks.GetSize(); i++) {
		CProMoBlockModel* child = dynamic_cast<CProMoBlockModel*>(this->m_subblocks.GetAt(i));

		if (child && child->m_attachmentType != DEHT_BODY) {
			if (alignment == DEHT_BODY || alignment == child->m_attachmentType) {
				blockList.Add(child);
			}
		}
	}
}

BOOL CProMoBlockModel::CanBeBoundaryOf(CProMoBlockModel* block, unsigned int alignment) const
/* ============================================================
	Function :		CProMoBlockModel::CanBeBoundaryOf
	Description :	Returns if this block can be a boundary 
					block of the block being passed as input 
					parameter.
					Override to implement diagram-specific logic.
	Access :		Public

	Return :		BOOL					-	"TRUE" if the
												block can be
												a boundary
												block
	Parameters :	CProMoBlockModel* block	-	the block that
												should have
												this block as
												boundary
					unsigned int alignment	-	the type of
												attachment for
												the boundary
												block

   ============================================================*/
{
	if (this == block) {
		return FALSE;
	}
	if (Contains(block, TRUE)) {
		return FALSE;
	}
	return TRUE;
}

BOOL CProMoBlockModel::HasBoundaryBlock(CProMoBlockModel* block) const
/* ============================================================
	Function :		CProMoBlockModel::HasBoundaryBlock
	Description :	Returns whether the block being passed is a
					boundary block of this block. A boundary 
					block is a child block that is attached to 
					the boundary of the parent block
	Access :		Public

	Return :		BOOL					-	"TRUE" if the
												block is a
												boundary block
	Parameters :	CProMoBlockModel* block	-	The block that
												should be
												checked

   ============================================================*/
{
	if (Contains(block, FALSE) && block->IsBoundaryBlock()) {
		return TRUE;
	}
	return FALSE;
}

BOOL CProMoBlockModel::IsBoundaryBlock() const
/* ============================================================
	Function :		CProMoBlockModel::IsBoundaryBlock
	Description :	Returns whether the current block is a
					boundary block. A boundary block is a child
					block that is attached to the boundary of
					a parent block
	Access :		Public

	Return :		BOOL					-	"TRUE" if the
												block is a
												boundary block
	Parameters :	none

   ============================================================*/
{
	if (m_parentBlock && m_attachmentType != DEHT_BODY && m_attachmentType != DEHT_NONE) {
		return TRUE;
	}
	return FALSE;
}

unsigned int CProMoBlockModel::GetBoundaryAttachment() const
/* ============================================================
	Function :		CProMoBlockModel::GetBoundaryAttachment
	Description :	Returns the attachment type of this block
					when it is a boundary block
	Access :		Public

	Return :		unsigned int			-	The attachment
												type
	Parameters :	none

   ============================================================*/
{
	return m_attachmentType;
}

void CProMoBlockModel::LinkChildBlock(CProMoBlockModel* block, unsigned int attachment)
/* ============================================================
	Function :		CProMoBlockModel::LinkChildBlock
	Description :	Makes the block being passed as input 
					parameter a child of this block
	Access :		Protected

	Return :		void
	Parameters :	CProMoBlockModel* block	-	the block that
												should be
												a child block
					unsigned int attachment	-	the type of
												attachment for
												the child block

   ============================================================*/
{
	//check if a circular nesting dependency would be created
	if (block->Contains(this, TRUE)) {
		return;
	}

	//check if the block can be a subblock of this block
	if (attachment == DEHT_BODY && !block->CanBeSubBlockOf(this)) {
		return;
	}

	//check if the block can be a boundary of this block
	if (attachment != DEHT_BODY && !block->CanBeBoundaryOf(this, attachment)) {
		return;
	}

	// Block is already linked
	if (Contains(block, FALSE)) {
		block->m_attachmentType = attachment;
		return;
	}

	m_subblocks.Add(block);
	
	if (block->m_parentBlock != NULL) {
		block->m_parentBlock->UnlinkChildBlock(block);
	}
	block->m_attachmentType = attachment;
	block->m_parentBlock = this;
	CustomizeLabels();
}

void CProMoBlockModel::UnlinkChildBlock(CProMoBlockModel* subblock)
/* ============================================================
	Function :		CProMoBlockModel::UnlinkChildBlock
	Description :	Removes the block being passed as input 
					parameter from the children of this block
	Access :		Protected

	Return :		void
	Parameters :	CProMoBlockModel* block	-	the block that
												should be
												removed

   ============================================================*/
{
	for (int i = m_subblocks.GetSize() - 1; i >= 0; i--) {
		if (m_subblocks.GetAt(i) == subblock) {
			subblock->m_parentBlock = NULL;
			subblock->m_attachmentType = DEHT_NONE;
			m_subblocks.RemoveAt(i);
		}
	}
	CustomizeLabels();

}

void CProMoBlockModel::UnlinkAllChildBlocks()
/* ============================================================
	Function :		CProMoBlockModel::UnlinkAllChildBlocks
	Description :	Removes all the children of this block
	Access :		Protected

	Return :		void
	Parameters :	none

   ============================================================*/
{
	for (int i = m_subblocks.GetSize() - 1; i >= 0; i--) {
		CProMoBlockModel* child = dynamic_cast<CProMoBlockModel*>(this->m_subblocks.GetAt(i));
		if (child) {
			child->m_parentBlock = NULL;
			child->m_attachmentType = DEHT_NONE;
			m_subblocks.RemoveAt(i);
		}
	}
	CustomizeLabels();

}

void CProMoBlockModel::SetParentBlock(CProMoBlockModel* parent, unsigned int attachment)
/* ============================================================
	Function :		CProMoBlockModel::SetParentBlock
	Description :	Makes the block being passed as input
					parameter the parent of this block
	Access :		Protected

	Return :		void
	Parameters :	CProMoBlockModel* block	-	the block that
												should be the
												parent block
					unsigned int attachment	-	the type of
												attachment for
												the current block

   ============================================================*/
{
	if (parent == m_parentBlock) {
		m_attachmentType = attachment;
		return;
	}
	if (parent != NULL) {
		parent->LinkChildBlock(this, attachment);
	}
	else {
		if (this->m_parentBlock != NULL) {
			this->m_parentBlock->UnlinkChildBlock(this);
		}
		this->m_parentBlock = NULL;
		this->m_attachmentType = DEHT_NONE;
	}
	CustomizeLabels();

}

CProMoBlockModel* CProMoBlockModel::GetParentBlock() const
/* ============================================================
	Function :		CProMoBlockModel::GetParentBlock
	Description :	Returns a pointer to the parent block
	Access :		Public

	Return :		CProMoBlockModel*	-	A pointer to the parent
											block
	Parameters :	none

   ============================================================*/
{
	return this->m_parentBlock;
}


CString CProMoBlockModel::GetParentFromString(const CString& str)
/* ============================================================
	Function :		CProMoBlockModel::GetParentFromString
	Description :	Static factory function that 
					parses a formatted string and extracts the 
					name of the parent block
	Access :		Public

	Return :		CString			-	The name of the parent 
										block
	Parameters :	CString& str	-	The string to be parsed

   ============================================================*/
{
	CTokenizer* tok = CFileParser::Tokenize(str);
	CString parentName;
	if (tok) {
		tok->GetAt(1, parentName);
		delete tok;
	}
	return parentName;
}

BOOL CProMoBlockModel::Contains(CProMoBlockModel* block, BOOL recursive) const
	/* ============================================================
	Function :		CProMoBlockModel::Contains
	Description :	Returns if the block being passed as input
					parameter is a (grand)child of this block
	Access :		Protected

	Return :		BOOL					-	"TRUE" if the 
												block is a
												(grand)child of
												this block
	Parameters :	CProMoBlockModel* block	-	the block that
												should be the
												(grand)child of
												this block
					BOOL recursive			-	if FALSE, do not
												extend search to 
												child blocks

   ============================================================*/
{
	BOOL contains = FALSE;
	for (int i = 0; i < m_subblocks.GetSize(); i++) {

		CProMoBlockModel* child = dynamic_cast<CProMoBlockModel*>(this->m_subblocks.GetAt(i));
		if (child) {
			if (child == block) {
				contains = TRUE;
			}
			if (recursive) {
				if (child->Contains(block, TRUE)) {
					contains = TRUE;
				}
			}
		}

	}
	return contains;
}

void CProMoBlockModel::LinkOutgoingEdge(CProMoEdgeModel* edge)
/* ============================================================
	Function :		CProMoBlockModel::LinkOutgoingEdge
	Description :	Makes the edge being passed as input
					parameter an outgoing edge of this block
	Access :		Protected

	Return :		void
	Parameters :	CProMoEdgeModel* edge	-	the edge that
												should be
												an outgoing edge

   ============================================================*/
{
	edge->SetSource(this);
	CustomizeLabels();

}

void CProMoBlockModel::UnlinkOutgoingEdge(CProMoEdgeModel* edge)
/* ============================================================
	Function :		CProMoBlockModel::UnlinkOutgoingEdge
	Description :	Removes the edge being passed as input
					parameter from the outgoing edges of this 
					block
	Access :		Protected

	Return :		void
	Parameters :	CProMoEdgeModel* edge	-	the edge that
												should be 
												removed from the
												outgoing edges

   ============================================================*/
{
	if (edge->GetSource() == this) {
		edge->SetSource(NULL);
	}
	CustomizeLabels();

}

void CProMoBlockModel::UnlinkAllOutgoingEdges()
/* ============================================================
	Function :		CProMoBlockModel::UnlinkAllOutgoingEdges
	Description :	Removes all the outgoing edges of this block
	Access :		Protected

	Return :		void
	Parameters :	none

   ============================================================*/
{
	for (int i = static_cast<int>(m_outgoingEdges.GetSize()) - 1; i >= 0; i--) {
		CProMoEdgeModel* edge = dynamic_cast<CProMoEdgeModel*>(this->m_outgoingEdges.GetAt(i));
		if (edge) {
			edge->SetSource(NULL);
		}
	}
	CustomizeLabels();

}

void CProMoBlockModel::GetOutgoingEdges(CObArray& edgeList) const
/* ============================================================
	Function :		CProMoBlockModel::GetOutgoingEdges
	Description :	Returns the outgoing edges for the current
					block

	Access :		Public

	Return :		void
	Parameters :	CObArray	-	A CObArray that will contain
									the edges

   ============================================================*/
{
	edgeList.Append(m_outgoingEdges);
}

void CProMoBlockModel::LinkIncomingEdge(CProMoEdgeModel* edge)
/* ============================================================
	Function :		CProMoBlockModel::LinkIncomingEdge
	Description :	Makes the edge being passed as input
					parameter an incoming edge of this block
	Access :		Protected

	Return :		void
	Parameters :	CProMoEdgeModel* edge	-	the edge that
												should be
												an incoming edge

   ============================================================*/
{
	edge->SetDestination(this);
	CustomizeLabels();

}

void CProMoBlockModel::UnlinkIncomingEdge(CProMoEdgeModel* edge)
/* ============================================================
	Function :		CProMoBlockModel::UnlinkIncomingEdge
	Description :	Removes the edge being passed as input
					parameter from the incoming edges of this
					block
	Access :		Protected

	Return :		void
	Parameters :	CProMoEdgeModel* edge	-	the edge that
												should be
												removed from the
												incoming edges

   ============================================================*/
{
	if (edge->GetDestination() == this) {
		edge->SetDestination(NULL);
	}
	CustomizeLabels();

}

void CProMoBlockModel::UnlinkAllIncomingEdges()
/* ============================================================
	Function :		CProMoBlockModel::UnlinkAllIncomingEdges
	Description :	Removes all the incoming edges of this block
	Access :		Protected

	Return :		void
	Parameters :	none

   ============================================================*/
{
	for (int i = static_cast<int>(m_incomingEdges.GetSize()) - 1; i >= 0; i--) {
		CProMoEdgeModel* edge = dynamic_cast<CProMoEdgeModel*>(this->m_incomingEdges.GetAt(i));
		if (edge) {
			edge->SetDestination(NULL);
		}
	}
	CustomizeLabels();

}

void CProMoBlockModel::GetIncomingEdges(CObArray& edgeList) const
/* ============================================================
	Function :		CProMoBlockModel::GetIncomingEdges
	Description :	Returns the incoming edges for the current
					block
	
	Access :		Public

	Return :		void
	Parameters :	CObArray	-	A CObArray that will contain
									the edges

   ============================================================*/
{
	edgeList.Append(m_incomingEdges);
}

CProMoBlockView* CProMoBlockModel::GetMainView() const
/* ============================================================
	Function :		CProMoBlockModel::GetMainView
	Description :	Returns a pointer to the primary view for
					this block.
	Access :		Public

	Return :		CProMoBlockView*	-	The primary view, 
											or "NULL" if no view
											is defined.
	Parameters :	none

   ============================================================*/
{
	// for generic blocks, only one view exists
	// to make the code more robust, return the first view whose class is CProMoBlockView or a derived one
	for (int i = 0; i < m_views.GetSize(); i++) {
		CProMoBlockView* view = dynamic_cast<CProMoBlockView*>(m_views.GetAt(i));
		if (view) {
			return view;
		}
	}

	return NULL;
}

CProMoModel* CProMoBlockModel::CreateFromString(const CString& str)
/* ============================================================
	Function :		CProMoBlockModel::CreateFromString
	Description :	Static factory function that creates and
					returns an instance of this class if "str"
					is a valid representation.
	Access :		Public

	Return :		CProMoModel*		-	The object, or "NULL"
											if "str" is not a
											representation of
											this type.
	Parameters :	const CString& str	-	The string to create
											from.

	Usage :			Can be used as a factory for text file loads.
					Each object type should have its own
					version - the default one is a model
					implementation.

   ============================================================*/
{

	CProMoBlockModel* obj = new CProMoBlockModel;
	if (!obj->FromString(str))
	{
		delete obj;
		obj = NULL;
	}

	return obj;

}

CString CProMoBlockModel::GetDefaultGetString() const
/* ============================================================
	Function :		CProMoBlockModel::GetDefaultString
	Description :	Gets the default properties of the object
					as a string.
	Access :		Protected

	Return :		CString	-	Resulting string
	Parameters :	none

	Usage :			Call as a part of the saving of objects
					to disk.

   ============================================================*/
{
	CString result = CProMoModel::GetDefaultGetString();

	CString str;

	CString parentString = _T("");


	if (m_parentBlock) {
		parentString = m_parentBlock->GetName();
		CFileParser::EncodeString(parentString);

	}

	str.Format(_T(",%s"), (LPCTSTR)parentString);

	return result + str;

}

void CProMoBlockModel::CustomizeLabel(CProMoLabel* label)
/* ============================================================
	Function :		CProMoBlockModel::CustomizeLabel
	Description :	Customizes the input label. Overridden to
					reposition the title label depending on
					whether the block is a leaf or intermediate
					node.
	Access :		Public

	Return :		void
	Parameters :	CProMoLabel*		-	A pointer to the
											label to customize

   ============================================================*/
{
	if (label) {
		if (label->GetPropertyName() == CString("Title") && label->GetModel()) {
			label->SetFitView(TRUE);
			label->SetLock(LOCK_REPOSITIONING);
			CObArray subBlocks;
			GetSubBlocks(subBlocks);
			if (subBlocks.GetSize() > 0) {
				label->SetViewAnchorPoint(DEHT_TOPMIDDLE);
				label->SetLabelAnchorPoint(DEHT_TOPMIDDLE);
			}
			else {
				label->SetViewAnchorPoint(DEHT_CENTER);
				label->SetLabelAnchorPoint(DEHT_CENTER);
			}
		}
	}

	CProMoModel::CustomizeLabel(label);
}
