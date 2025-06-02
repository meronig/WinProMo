#ifndef _PROCESSENTITYBLOCKVIEW_H_
#define _PROCESSENTITYBLOCKVIEW_H_

#include "../DiagramEditor/DiagramEntity.h"
#include "PropertyDialog.h"
#include "ProcessEntityBlockModel.h"
class CProcessEntityBlockView : public CDiagramEntity
{

	public:
		friend class CProcessLineEdgeView;
		// Construction/initialization/destruction
		CProcessEntityBlockView();
		virtual ~CProcessEntityBlockView();
		virtual CDiagramEntity* Clone();
		virtual void SetRect(double left, double top, double right, double bottom);
		static	CDiagramEntity* CreateFromString(const CString& str);

		// Overrides
		virtual void Draw(CDC* dc, CRect rect);
		virtual int		GetHitCode(CPoint point) const;
		virtual HCURSOR GetCursor(int hit) const;
		
		virtual void	SetMoved(BOOL moved);
		virtual BOOL	GetMoved();
		
		// Block-specific methods
		
		virtual void recomputeIntersectionLinks();
		virtual CProcessEntityBlockModel* getModel() const;
		virtual void setModel(CProcessEntityBlockModel*);
		
		virtual void autoResize();
		virtual void Highlight(CDC* dc, CRect rect);
		virtual BOOL IsTarget();
		virtual void SetTarget(BOOL isTarget);
		
		virtual CPoint getIntersection(CPoint innerPoint, CPoint outerPoint);

	protected:
		virtual CString				GetDefaultGetString() const;
		virtual BOOL				GetDefaultFromString(CString& str);
		BOOL m_target;

	private:
		CPropertyDialog	m_dlg;
		BOOL			m_moved;
		CProcessEntityBlockModel* m_blockmodel;

};
#endif //_PROCESSENTITYBLOCKVIEW_H_

