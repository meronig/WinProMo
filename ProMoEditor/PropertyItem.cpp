#include "stdafx.h"
#include "PropertyItem.h"


CPropertyItem::CPropertyItem(const CString& name, CDiagramEntity* target, SetPropertyWrapper setter)
{
	m_name = name;
	m_target = target;
	m_setter = setter;
	m_ctrlID = 0;
}

void CPropertyItem::SetValue(const CString& val)
{
	m_value = val;
	if (m_target && m_setter)
		m_setter(m_target, val);
}
