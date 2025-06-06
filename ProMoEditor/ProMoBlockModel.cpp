#include "stdafx.h"
#include "ProMoBlockModel.h"
#include "ProMoEdgeModel.h"
#include "ProMoNameFactory.h"

CProMoBlockModel::CProMoBlockModel() {
	SetType(_T("promo_block_model"));
	SetName(CProMoNameFactory::GetID());
	this->m_parentBlock = NULL;

}

CProMoBlockModel::~CProMoBlockModel() {
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
	CProMoBlockModel* obj = new CProMoBlockModel;
	obj->m_parentBlock = NULL;
	obj->m_subblocks.RemoveAll();
	return obj;
}

BOOL CProMoBlockModel::canBeNested(CProMoBlockModel* block)
{
	if (contains(block, TRUE)) {
		return FALSE;
	}
	return TRUE;
}

void CProMoBlockModel::linkSubBlock(CProMoBlockModel* subblock)
{
	if (subblock->contains(this, TRUE)) {
		ASSERT(FALSE);
		//better to throw an exception
		return;
	}

	m_subblocks.Add(subblock);

	if (subblock->m_parentBlock != NULL) {
		subblock->m_parentBlock->unlinkSubBlock(subblock);
	}
	subblock->m_parentBlock = this;
}

void CProMoBlockModel::unlinkSubBlock(CProMoBlockModel* subblock)
{
	for (int i = 0; i < m_subblocks.GetSize(); i++) {
		if (m_subblocks.GetAt(i) == subblock) {
			m_subblocks.RemoveAt(i);
			subblock->m_parentBlock = NULL;
		}
	}
}

void CProMoBlockModel::unlinkSubBlocks()
{
	for (int i = 0; i < m_subblocks.GetSize(); i++) {
		CProMoBlockModel* child = dynamic_cast<CProMoBlockModel*>(this->m_subblocks.GetAt(i));
		if (child) {
			child->m_parentBlock = NULL;
		}
	}
	this->m_subblocks.RemoveAll();
}

CObArray* CProMoBlockModel::getSubBlocks()
{
	return &m_subblocks;
}

void CProMoBlockModel::setParentBlock(CProMoBlockModel* parent)
{
	if (parent != NULL) {
		parent->linkSubBlock(this);
	}
	else {
		if (this->m_parentBlock != NULL) {
			this->m_parentBlock->unlinkSubBlock(this);
		}
		this->m_parentBlock = NULL;
	}
}

CProMoBlockModel* CProMoBlockModel::getParentBlock() const
{
	return this->m_parentBlock;
}

BOOL CProMoBlockModel::contains(CProMoBlockModel* block, BOOL recursive) {
	BOOL contains = FALSE;
	for (int i = 0; i < m_subblocks.GetSize(); i++) {

		CProMoBlockModel* child = dynamic_cast<CProMoBlockModel*>(this->m_subblocks.GetAt(i));
		if (child) {
			if (child == block) {
				contains = TRUE;
			}
			if (recursive) {
				if (child->contains(block, TRUE)) {
					contains = TRUE;
				}
			}
		}

	}
	return contains;
}

void CProMoBlockModel::linkOutgoingEdge(CProMoEdgeModel* edge)
{
	edge->SetSource(this);
}

void CProMoBlockModel::unlinkOutgoingEdge(CProMoEdgeModel* edge)
{
	if (edge->GetSource() == this) {
		edge->SetSource(NULL);
	}
}

void CProMoBlockModel::unlinkOutgoingEdges()
{
	for (int i = 0; i < m_outgoingEdges.GetSize(); i++) {
		CProMoEdgeModel* edge = dynamic_cast<CProMoEdgeModel*>(m_outgoingEdges.GetAt(i));
		if (edge) {
			edge->SetSource(NULL);
		}
	}
}

CObArray* CProMoBlockModel::getOutgoingEdges()
{
	return &m_outgoingEdges;
}

void CProMoBlockModel::linkIncomingEdge(CProMoEdgeModel* edge)
{
	edge->SetDestination(this);
}

void CProMoBlockModel::unlinkIncomingEdge(CProMoEdgeModel* edge)
{
	if (edge->GetDestination() == this) {
		edge->SetDestination(NULL);
	}
}

void CProMoBlockModel::unlinkIncomingEdges()
{
	for (int i = 0; i < m_incomingEdges.GetSize(); i++) {
		CProMoEdgeModel* edge = dynamic_cast<CProMoEdgeModel*>(m_incomingEdges.GetAt(i));
		if (edge) {
			edge->SetDestination(NULL);
		}
	}
}


CObArray* CProMoBlockModel::getIncomingEdges()
{
	return &m_incomingEdges;
}

CProMoBlockView* CProMoBlockModel::getMainView() const
{
	if (m_views.GetSize() < 1)
		return NULL;

	//for generic blocks, only one view exists
	CProMoBlockView* view = dynamic_cast<CProMoBlockView*>(m_views.GetAt(0));
	return view;
}

CProMoModel* CProMoBlockModel::CreateFromString(const CString& str)
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
{
	CString str;

	CString name = GetName();
	CDiagramEntity::CStringReplace(name, _T(":"), _T("\\colon"));
	CDiagramEntity::CStringReplace(name, _T(";"), _T("\\semicolon"));
	CDiagramEntity::CStringReplace(name, _T(","), _T("\\comma"));
	CDiagramEntity::CStringReplace(name, _T("\r\n"), _T("\\newline"));

	CString parentString = _T("");


	if (m_parentBlock) {
		parentString = m_parentBlock->GetName();
		CDiagramEntity::CStringReplace(parentString, _T(":"), _T("\\colon"));
		CDiagramEntity::CStringReplace(parentString, _T(";"), _T("\\semicolon"));
		CDiagramEntity::CStringReplace(parentString, _T(","), _T("\\comma"));
		CDiagramEntity::CStringReplace(parentString, _T("\r\n"), _T("\\newline"));
		
	}

	str.Format(_T("%s:%s,%s"), (LPCTSTR)GetType(), (LPCTSTR)name, (LPCTSTR)parentString);

	return str;

}
