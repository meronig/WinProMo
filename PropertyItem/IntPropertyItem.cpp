#include "stdafx.h"
#include "IntPropertyItem.h"


CIntPropertyItem::CIntPropertyItem(const CString& name, CDiagramEntity* target, CDiagramEditor* editor, SetPropertyWrapper setter, const int& initialValue)
	: CPropertyItem(name, target, editor) {
	m_setter = setter;
	m_value = initialValue;
}

BOOL CIntPropertyItem::SetValue(const int& val)
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

const int CIntPropertyItem::GetValue()
{
	return m_value;
}