#include "ProcessModel.h"


void CProcessModel::linkView(CDiagramEntity* view)
{
	m_views.Add(view);
}

void CProcessModel::unlinkView(CDiagramEntity* view)
{
	for (int i = m_views.GetSize() - 1; i >= 0 ; i--) {
		CDiagramEntity* tempView = dynamic_cast<CDiagramEntity*>(m_views.GetAt(i));
		if (tempView) {
			if (tempView == view) {
				m_views.RemoveAt(i);
			}
		}
	}
}

void CProcessModel::unlinkViews()
{
	m_views.RemoveAll();
}

CObArray* CProcessModel::getViews()
{
	return &m_views;
}