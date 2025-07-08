template <class T>
CTypedPropertyItem<T>::CTypedPropertyItem(const CString& name, CDiagramEntity* target, CDiagramEditor* editor, SetPropertyWrapper setter, const T& initialValue)
	: CPropertyItem(name, target, editor) {
	m_setter = setter;
	m_value = initialValue;
}

template <class T>
BOOL CTypedPropertyItem<T>::SetValue(const T& val)
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

template <class T>
const T CTypedPropertyItem<T>::GetValue()
{
	return m_value;
}

template <class T>
void CTypedPropertyItem<T>::AddOption(const T& option)
{
	m_options.Add(option);
}

template <class T>
int CTypedPropertyItem<T>::GetOptionsCount()
{
	return m_options.GetSize();
}

template <class T>
const T& CTypedPropertyItem<T>::GetOption(const int& index)
{
	return m_options.GetAt(index);
}
