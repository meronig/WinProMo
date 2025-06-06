#include "stdafx.h"
#include "ProcessEntityBlockModel.h"
#include "ProcessLineEdgeModel.h"
#include "LinkFactory.h"

CProcessEntityBlockModel::CProcessEntityBlockModel() {
	SetType(_T("process_block_model"));
	SetName(CLinkFactory::GetID());
	this->parentBlock = NULL;

}

CProcessEntityBlockModel::~CProcessEntityBlockModel() {
	int i = 0;
	for (i = static_cast<int>(m_incomingEdges.GetSize()) - 1; i >= 0; i--) {
		CProcessLineEdgeModel* edge = dynamic_cast<CProcessLineEdgeModel*>(this->m_incomingEdges.GetAt(i));
		if (edge) {
			edge->SetDestination(NULL);
		}
	}
	for (i = static_cast<int>(m_outgoingEdges.GetSize()) - 1; i >= 0; i--) {
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

BOOL CProcessEntityBlockModel::canBeNested(CProcessEntityBlockModel* block)
{
	if (contains(block, TRUE)) {
		return FALSE;
	}
	return TRUE;
}

void CProcessEntityBlockModel::linkSubBlock(CProcessEntityBlockModel* subblock)
{
	if (subblock->contains(this, TRUE)) {
		ASSERT(FALSE);
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

BOOL CProcessEntityBlockModel::contains(CProcessEntityBlockModel* block, BOOL recursive) {
	BOOL contains = FALSE;
	/*if (this == block) {
		contains = true;
	}
	*/
	for (int i = 0; i < m_subblocks.GetSize(); i++) {

		CProcessEntityBlockModel* child = dynamic_cast<CProcessEntityBlockModel*>(this->m_subblocks.GetAt(i));
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

CProcessModel* CProcessEntityBlockModel::CreateFromString(const CString& str)
/* ============================================================
	Function :		CProcessEntityBlock::CreateFromString
	Description :	Static factory function that creates and
					returns an instance of this class if str
					is a valid representation.

	Return :		CDiagramEntity*		-	The object, or NULL
											if str is not a
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

	CProcessEntityBlockModel* obj = new CProcessEntityBlockModel;
	if (!obj->FromString(str))
	{
		delete obj;
		obj = NULL;
	}

	return obj;

}

CString CProcessEntityBlockModel::GetDefaultGetString() const
{
	/* ============================================================
	Function :		CProcessEntityBlock::GetDefaultString
	Description :	Gets the default properties of the object
					as a string.
	Access :		Protected

	Return :		CString	-	Resulting string
	Parameters :	none

	Usage :			Call as a part of the saving of objects
					to disk.

   ============================================================*/
   
	CString str;

	CString name = GetName();
	CDiagramEntity::CStringReplace(name, _T(":"), _T("\\colon"));
	CDiagramEntity::CStringReplace(name, _T(";"), _T("\\semicolon"));
	CDiagramEntity::CStringReplace(name, _T(","), _T("\\comma"));
	CDiagramEntity::CStringReplace(name, _T("\r\n"), _T("\\newline"));

	CString parentString = _T("");


	if (parentBlock) {
		parentString = parentBlock->GetName();
		CDiagramEntity::CStringReplace(parentString, _T(":"), _T("\\colon"));
		CDiagramEntity::CStringReplace(parentString, _T(";"), _T("\\semicolon"));
		CDiagramEntity::CStringReplace(parentString, _T(","), _T("\\comma"));
		CDiagramEntity::CStringReplace(parentString, _T("\r\n"), _T("\\newline"));
		
	}

	str.Format(_T("%s:%s,%s"), (LPCTSTR)GetType(), (LPCTSTR)name, (LPCTSTR)parentString);

	return str;

}
