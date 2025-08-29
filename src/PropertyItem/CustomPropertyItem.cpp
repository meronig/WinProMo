/* ==========================================================================

	Copyright © 2025 Technical University of Denmark

	Author :		Giovanni Meroni

   ========================================================================*/
#include "stdafx.h"
#include "CustomPropertyItem.h"

CCustomPropertyItem::CCustomPropertyItem(const CString& name, CDiagramEntity* target, CDiagramEditor* editor, SetPropertyWrapper setter)
	: CPropertyItem(name, target, editor) {
	m_setter = setter;
}

BOOL CCustomPropertyItem::SetValue()
{
	if (m_target && m_setter && m_editor) {
		BOOL result = m_setter(m_target, m_editor);
		if (result) {
			return TRUE;
		}
	}
	return FALSE;
}
