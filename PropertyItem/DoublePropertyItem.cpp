#include "stdafx.h"
#include "DoublePropertyItem.h"


CDoublePropertyItem::CDoublePropertyItem(const CString& name, CDiagramEntity* target, CDiagramEditor* editor, SetPropertyWrapper setter, const double& initialValue)
	: CPropertyItem(name, target, editor) {
	m_setter = setter;
	m_value = initialValue;
}

BOOL CDoublePropertyItem::SetValue(const double& val)
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

const double CDoublePropertyItem::GetValue()
{
	return m_value;
}
