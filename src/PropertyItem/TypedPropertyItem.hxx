/* ==========================================================================

	Copyright © 2025 Technical University of Denmark

	CTypedPropertyItem

	Author :		Giovanni Meroni

	Purpose :		"CTypedPropertyItem" is a template class that can be 
					used to pass to client applications the diagram element 
					whose property needs to be modified, as well as 
					the helper function to perform the modification.

	Usage:			This class be used when the new value for the property
					is determined by the client application, and is 
					directly passed. This allows the client application 
					to implement its own dialog/control to change the
					property, independently from the diagram editor 
					library.

========================================================================*/
template <class T>
CTypedPropertyItem<T>::CTypedPropertyItem(const CString& name, CDiagramEntity* target, CDiagramEditor* editor, SetPropertyWrapper setter, const T& initialValue)
	: CPropertyItem(name, target, editor) {
	m_setter = setter;
	m_value = initialValue;
}

template <class T>
BOOL CTypedPropertyItem<T>::SetValue(const T& val)
/* ============================================================
	Function :		CTypedPropertyItem<T>::SetValue
	Description :	Sets the property by invoking the helper
					function
	Access :		Public

	Return :		BOOL		-	"TRUE" if the operation
									succeeded, "FALSE" otherwise
	Parameters :	T& val		-	The value to set for the
									property

   ============================================================*/
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
/* ============================================================
	Function :		CTypedPropertyItem<T>::GetValue
	Description :	Gets the value currently associated 
					to the property
	Access :		Public

	Return :		T		-	the current value for the
								property
	Parameters :	none

   ============================================================*/
{
	return m_value;
}

template <class T>
void CTypedPropertyItem<T>::AddOption(const T& option)
/* ============================================================
	Function :		CTypedPropertyItem<T>::AddOption
	Description :	Adds an option to the list of possible
					values that the property can assume. Can be 
					used by the client application to build 
					list and combo box controls to set the 
					property
	Access :		Public

	Return :		none
	Parameters :	T& val		-	The value to be added to 
									the list of possible options

   ============================================================*/
{
	m_options.Add(option);
}

template <class T>
int CTypedPropertyItem<T>::GetOptionsCount()
/* ============================================================
	Function :		CTypedPropertyItem<T>::GetValue
	Description :	Returns the number of options available for
					the property
	Access :		Public

	Return :		int		-	the number of available options
								for the property
	Parameters :	none

   ============================================================*/
{
	return m_options.GetSize();
}

template <class T>
const T& CTypedPropertyItem<T>::GetOption(const int& index)
/* ============================================================
	Function :		CTypedPropertyItem<T>::GetOption
	Description :	Returns the option having the specified
					index
	Access :		Public

	Return :		T&			-	the option having the 
									specified index
	Parameters :	int index	-	the index for the option
									to be returned

   ============================================================*/
{
	if (index < m_options.GetSize() - 1)
		return m_options.GetAt(index);
	return m_value;
}
