#include "ProcessEntityBlockModel.h"
#include "ProcessLineEdgeModel.h"

CProcessEntityBlockModel::CProcessEntityBlockModel() {
	this->parentBlock = NULL;
}

CProcessEntityBlockModel::~CProcessEntityBlockModel() {
	for (int i = m_incomingEdges.GetSize() - 1; i >= 0; i--) {
		CProcessLineEdgeModel* edge = dynamic_cast<CProcessLineEdgeModel*>(this->m_incomingEdges.GetAt(i));
		if (edge) {
			edge->SetDestination(NULL);
		}
	}
	for (int i = m_outgoingEdges.GetSize() - 1; i >= 0; i--) {
		CProcessLineEdgeModel* edge = dynamic_cast<CProcessLineEdgeModel*>(this->m_outgoingEdges.GetAt(i));
		if (edge) {
			edge->SetSource(NULL);
		}
	}
}

CProcessModel* CProcessEntityBlockModel::Clone() {
	CProcessEntityBlockModel* obj = new CProcessEntityBlockModel;
	//obj->Copy(this);
	obj->parentBlock = NULL;
	obj->m_subblocks.RemoveAll();
	return obj;
}

bool CProcessEntityBlockModel::canBeNested(CProcessEntityBlockModel* block)
{
	if (contains(block, true)) {
		return false;
	}
	return true;
}

void CProcessEntityBlockModel::linkSubBlock(CProcessEntityBlockModel* subblock)
{
	if (subblock->contains(this, true)) {
		//ASSERT(false);
		//better to throw an exception
		return;
	}

	m_subblocks.Add(subblock);

	if (subblock->parentBlock != NULL) {
		subblock->parentBlock->unlinkSubBlock(subblock);
	}
	subblock->parentBlock = this;
}

void CProcessEntityBlockModel::unlinkSubBlock(CProcessEntityBlockModel* subblock)
{
	for (int i = 0; i < m_subblocks.GetSize(); i++) {
		if (m_subblocks.GetAt(i) == subblock) {
			m_subblocks.RemoveAt(i);
			subblock->parentBlock = NULL;
		}
	}
}

void CProcessEntityBlockModel::unlinkSubBlocks()
{
	for (int i = 0; i < m_subblocks.GetSize(); i++) {
		CProcessEntityBlockModel* child = dynamic_cast<CProcessEntityBlockModel*>(this->m_subblocks.GetAt(i));
		if (child) {
			child->parentBlock = NULL;
		}
	}
	this->m_subblocks.RemoveAll();
}

CObArray* CProcessEntityBlockModel::getSubBlocks()
{
	return &m_subblocks;
}

void CProcessEntityBlockModel::setParentBlock(CProcessEntityBlockModel* parent)
{
	if (parent != NULL) {
		parent->linkSubBlock(this);
	}
	else {
		if (this->parentBlock != NULL) {
			this->parentBlock->unlinkSubBlock(this);
		}
		this->parentBlock = NULL;
	}
}

CProcessEntityBlockModel* CProcessEntityBlockModel::getParentBlock() const
{
	return this->parentBlock;
}

bool CProcessEntityBlockModel::contains(CProcessEntityBlockModel* block, bool recursive) {
	bool contains = false;
	/*if (this == block) {
		contains = true;
	}
	*/
	for (int i = 0; i < m_subblocks.GetSize(); i++) {

		CProcessEntityBlockModel* child = dynamic_cast<CProcessEntityBlockModel*>(this->m_subblocks.GetAt(i));
		if (child) {
			if (child == block) {
				contains = true;
			}
			if (recursive) {
				if (child->contains(block, true)) {
					contains = true;
				}
			}
		}

	}
	return contains;
}

void CProcessEntityBlockModel::linkOutgoingEdge(CProcessLineEdgeModel* edge)
{
	edge->SetSource(this);
}

void CProcessEntityBlockModel::unlinkOutgoingEdge(CProcessLineEdgeModel* edge)
{
	if (edge->GetSource() == this) {
		edge->SetSource(NULL);
	}
}

void CProcessEntityBlockModel::unlinkOutgoingEdges()
{
	for (int i = 0; i < m_outgoingEdges.GetSize(); i++) {
		CProcessLineEdgeModel* edge = dynamic_cast<CProcessLineEdgeModel*>(m_outgoingEdges.GetAt(i));
		if (edge) {
			edge->SetSource(NULL);
		}
	}
}

CObArray* CProcessEntityBlockModel::getOutgoingEdges()
{
	return &m_outgoingEdges;
}

void CProcessEntityBlockModel::linkIncomingEdge(CProcessLineEdgeModel* edge)
{
	edge->SetDestination(this);
}

void CProcessEntityBlockModel::unlinkIncomingEdge(CProcessLineEdgeModel* edge)
{
	if (edge->GetDestination() == this) {
		edge->SetDestination(NULL);
	}
}

void CProcessEntityBlockModel::unlinkIncomingEdges()
{
	for (int i = 0; i < m_incomingEdges.GetSize(); i++) {
		CProcessLineEdgeModel* edge = dynamic_cast<CProcessLineEdgeModel*>(m_incomingEdges.GetAt(i));
		if (edge) {
			edge->SetDestination(NULL);
		}
	}
}


CObArray* CProcessEntityBlockModel::getIncomingEdges()
{
	return &m_incomingEdges;
}

CProcessEntityBlockView* CProcessEntityBlockModel::getMainView() const
{
	if (m_views.GetSize() < 1)
		return NULL;

	//for generic blocks, only one view exists
	CProcessEntityBlockView* view = dynamic_cast<CProcessEntityBlockView*>(m_views.GetAt(0));
	return view;
}


