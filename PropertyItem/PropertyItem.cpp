#include "stdafx.h"
#include "PropertyItem.h"


CPropertyItem::CPropertyItem(const CString& name, CDiagramEntity* target, CDiagramEditor* editor)
{
	m_name = name;
	m_editor = editor;
	m_target = target;
	m_ctrlID = 0;
}

const CString CPropertyItem::GetName()
{
	return m_name;
}

const UINT CPropertyItem::GetCtrlID()
{
	return m_ctrlID;
}

void CPropertyItem::SetCtrlID(UINT ctrlID)
{
	m_ctrlID = ctrlID;
}
