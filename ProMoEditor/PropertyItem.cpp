#include "stdafx.h"
#include "PropertyItem.h"


CPropertyItem::CPropertyItem(const CString& name, CDiagramEntity* target, CDiagramEditor* editor, SetPropertyWrapper setter)
{
	m_name = name;
	m_editor = editor;
	m_target = target;
	m_setter = setter;
	m_ctrlID = 0;
}

BOOL CPropertyItem::SetValue(const CString& val)
{
	if (m_target && m_setter && m_editor) {
		BOOL result = m_setter(m_target, m_editor, val);
		if (result) {
			m_value = val;
			return TRUE;
		}
	}
	return FALSE;
}
