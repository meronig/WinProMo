#include "stdafx.h"
#include "BoolPropertyItem.h"


CBoolPropertyItem::CBoolPropertyItem(const CString& name, CDiagramEntity* target, CDiagramEditor* editor, SetPropertyWrapper setter, const BOOL& initialValue)
	: CPropertyItem(name, target, editor) {
	m_setter = setter;
	m_value = initialValue;
}

BOOL CBoolPropertyItem::SetValue(const BOOL& val)
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

const BOOL CBoolPropertyItem::GetValue()
{
	return m_value;
}
