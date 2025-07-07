#include "stdafx.h"
#include "StringPropertyItem.h"


CStringPropertyItem::CStringPropertyItem(const CString& name, CDiagramEntity* target, CDiagramEditor* editor, SetPropertyWrapper setter, CString initialValue)
: CPropertyItem(name, target, editor) {
	m_setter = setter;
	m_value = initialValue;
}

BOOL CStringPropertyItem::SetValue(const CString& val)
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

CString CStringPropertyItem::GetValue()
{
	return m_value;
}
