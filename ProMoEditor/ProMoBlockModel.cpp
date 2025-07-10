/* ==========================================================================
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
	this->m_parentBlock = NULL;

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
	int i = 0;
	for (i = static_cast<int>(m_incomingEdges.GetSize()) - 1; i >= 0; i--) {
		CProMoEdgeModel* edge = dynamic_cast<CProMoEdgeModel*>(this->m_incomingEdges.GetAt(i));
		if (edge) {
			edge->SetDestination(NULL);
		}
	}
	for (i = static_cast<int>(m_outgoingEdges.GetSize()) - 1; i >= 0; i--) {
		CProMoEdgeModel* edge = dynamic_cast<CProMoEdgeModel*>(this->m_outgoingEdges.GetAt(i));
		if (edge) {
			edge->SetSource(NULL);
		}
	}
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

BOOL CProMoBlockModel::CanBeNested(CProMoBlockModel* block)
/* ============================================================
	Function :		CProMoBlockModel::CanBeNested
	Description :	Returns if the block being passed as input
					parameter can be nested.
					Override to implement diagram-specific logic.
	Access :		Public

	Return :		BOOL					-	"TRUE" if the 
												block can be 
												nested
	Parameters :	CProMoBlockModel* block	-	the block that
												should be 
												nested

   ============================================================*/
{
	if (Contains(block, TRUE)) {
		return FALSE;
	}
	return TRUE;
}

void CProMoBlockModel::LinkSubBlock(CProMoBlockModel* block)
/* ============================================================
	Function :		CProMoBlockModel::LinkSubBlock
	Description :	Makes the block being passed as input 
					parameter a child of this block
	Access :		Public

	Return :		void
	Parameters :	CProMoBlockModel* block	-	the block that
												should be
												a child block

   ============================================================*/
{
	if (block->Contains(this, TRUE)) {
		ASSERT(FALSE);
		//better to throw an exception
		return;
	}

	m_subblocks.Add(block);

	if (block->m_parentBlock != NULL) {
		block->m_parentBlock->UnlinkSubBlock(block);
	}
	block->m_parentBlock = this;
}

void CProMoBlockModel::UnlinkSubBlock(CProMoBlockModel* subblock)
/* ============================================================
	Function :		CProMoBlockModel::UnlinkSubBlock
	Description :	Removes the block being passed as input 
					parameter from the children of this block
	Access :		Public

	Return :		void
	Parameters :	CProMoBlockModel* block	-	the block that
												should be
												removed

   ============================================================*/
{
	for (int i = 0; i < m_subblocks.GetSize(); i++) {
		if (m_subblocks.GetAt(i) == subblock) {
			m_subblocks.RemoveAt(i);
			subblock->m_parentBlock = NULL;
		}
	}
}

void CProMoBlockModel::UnlinkAllSubBlocks()
/* ============================================================
	Function :		CProMoBlockModel::UnlinkAllSubBlocks
	Description :	Removes all the children of this block
	Access :		Public

	Return :		void
	Parameters :	none

   ============================================================*/
{
	for (int i = 0; i < m_subblocks.GetSize(); i++) {
		CProMoBlockModel* child = dynamic_cast<CProMoBlockModel*>(this->m_subblocks.GetAt(i));
		if (child) {
			child->m_parentBlock = NULL;
		}
	}
	this->m_subblocks.RemoveAll();
}

CObArray* CProMoBlockModel::GetSubBlocks()
/* ============================================================
	Function :		CProMoBlockModel::GetSubBlocks
	Description :	Accessor for the internal child blocks array
	Access :		Public

	Return :		CObArray*	-	A pointer to the child 
									blocks array
	Parameters :	none

   ============================================================*/
{
	return &m_subblocks;
}

void CProMoBlockModel::SetParentBlock(CProMoBlockModel* parent)
/* ============================================================
	Function :		CProMoBlockModel::SetParentBlock
	Description :	Makes the block being passed as input
					parameter the parent of this block
	Access :		Public

	Return :		void
	Parameters :	CProMoBlockModel* block	-	the block that
												should be the
												parent block

   ============================================================*/
{
	if (parent != NULL) {
		parent->LinkSubBlock(this);
	}
	else {
		if (this->m_parentBlock != NULL) {
			this->m_parentBlock->UnlinkSubBlock(this);
		}
		this->m_parentBlock = NULL;
	}
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

BOOL CProMoBlockModel::Contains(CProMoBlockModel* block, BOOL recursive)
	/* ============================================================
	Function :		CProMoBlockModel::Contains
	Description :	Returns if the block being passed as input
					parameter is a (grand)child of this block
	Access :		Public

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
	Access :		Public

	Return :		void
	Parameters :	CProMoEdgeModel* edge	-	the edge that
												should be
												an outgoing edge

   ============================================================*/
{
	edge->SetSource(this);
}

void CProMoBlockModel::UnlinkOutgoingEdge(CProMoEdgeModel* edge)
/* ============================================================
	Function :		CProMoBlockModel::UnlinkOutgoingEdge
	Description :	Removes the edge being passed as input
					parameter from the outgoing edges of this 
					block
	Access :		Public

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
}

void CProMoBlockModel::UnlinkAllOutgoingEdges()
/* ============================================================
	Function :		CProMoBlockModel::UnlinkAllOutgoingEdges
	Description :	Removes all the outgoing edges of this block
	Access :		Public

	Return :		void
	Parameters :	none

   ============================================================*/
{
	for (int i = 0; i < m_outgoingEdges.GetSize(); i++) {
		CProMoEdgeModel* edge = dynamic_cast<CProMoEdgeModel*>(m_outgoingEdges.GetAt(i));
		if (edge) {
			edge->SetSource(NULL);
		}
	}
}

CObArray* CProMoBlockModel::GetOutgoingEdges()
/* ============================================================
	Function :		CProMoBlockModel::GetOutgoingEdges
	Description :	Accessor for the internal outgoing edges
					array

	Access :		Public

	Return :		CObArray*	-	A pointer to the outgoing
									edges array
	Parameters :	none

   ============================================================*/
{
	return &m_outgoingEdges;
}

void CProMoBlockModel::LinkIncomingEdge(CProMoEdgeModel* edge)
/* ============================================================
	Function :		CProMoBlockModel::LinkIncomingEdge
	Description :	Makes the edge being passed as input
					parameter an incoming edge of this block
	Access :		Public

	Return :		void
	Parameters :	CProMoEdgeModel* edge	-	the edge that
												should be
												an incoming edge

   ============================================================*/
{
	edge->SetDestination(this);
}

void CProMoBlockModel::UnlinkIncomingEdge(CProMoEdgeModel* edge)
/* ============================================================
	Function :		CProMoBlockModel::UnlinkIncomingEdge
	Description :	Removes the edge being passed as input
					parameter from the incoming edges of this
					block
	Access :		Public

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
}

void CProMoBlockModel::UnlinkAllIncomingEdges()
/* ============================================================
	Function :		CProMoBlockModel::UnlinkAllIncomingEdges
	Description :	Removes all the incoming edges of this block
	Access :		Public

	Return :		void
	Parameters :	none

   ============================================================*/
{
	for (int i = 0; i < m_incomingEdges.GetSize(); i++) {
		CProMoEdgeModel* edge = dynamic_cast<CProMoEdgeModel*>(m_incomingEdges.GetAt(i));
		if (edge) {
			edge->SetDestination(NULL);
		}
	}
}

CObArray* CProMoBlockModel::GetIncomingEdges()
/* ============================================================
	Function :		CProMoBlockModel::GetIncomingEdges
	Description :	Accessor for the internal incoming edges 
					array
	
	Access :		Public

	Return :		CObArray*	-	A pointer to the incoming
									edges array
	Parameters :	none

   ============================================================*/
{
	return &m_incomingEdges;
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
	if (m_views.GetSize() < 1)
		return NULL;

	//for generic blocks, only one view exists
	CProMoBlockView* view = dynamic_cast<CProMoBlockView*>(m_views.GetAt(0));
	return view;
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
		CDiagramEntity::CStringReplace(parentString, _T(":"), _T("\\colon"));
		CDiagramEntity::CStringReplace(parentString, _T(";"), _T("\\semicolon"));
		CDiagramEntity::CStringReplace(parentString, _T(","), _T("\\comma"));
		CDiagramEntity::CStringReplace(parentString, _T("\r\n"), _T("\\newline"));
		
	}

	str.Format(_T(",%s"), (LPCTSTR)parentString);

	return result + str;

}
