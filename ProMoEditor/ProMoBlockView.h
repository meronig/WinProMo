#ifndef _PROMOBLOCKVIEW_H_
#define _PROMOBLOCKVIEW_H_

#include "../DiagramEditor/DiagramEntity.h"
#include "PropertyDialog.h"
#include "ProMoBlockModel.h"
class CProMoBlockView : public CDiagramEntity
{

	public:
		friend class CProMoEdgeView;
		// Construction/initialization/destruction
		CProMoBlockView();
		virtual ~CProMoBlockView();
		virtual CDiagramEntity* Clone();
		virtual void SetRect(double left, double top, double right, double bottom);
		static	CDiagramEntity* CreateFromString(const CString& str);

		// Overrides
		virtual void Draw(CDC* dc, CRect rect);
		virtual int		GetHitCode(CPoint point) const;
		virtual HCURSOR GetCursor(int hit) const;
		
		// Block-specific methods
		
		virtual void recomputeIntersectionLinks();
		virtual CProMoBlockModel* getModel() const;
		virtual void setModel(CProMoBlockModel*);
		
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
		CProMoBlockModel* m_blockmodel;

};
#endif //_PROMOBLOCKVIEW_H_

