#ifndef _PROCESSENTITYBLOCK_H_
#define _PROCESSENTITYBLOCK_H_

#include "../DiagramEditor/DiagramEntity.h"
#include "PropertyDialog.h"
class CProcessEntityBlock : public CDiagramEntity
{

	public:
		friend class CProcessLineEdge;
		// Construction/initialization/destruction
		CProcessEntityBlock();
		virtual ~CProcessEntityBlock();
		virtual CDiagramEntity* Clone();
		virtual void MoveRect(double x, double y);
		virtual void SetRect(double left, double top, double right, double bottom);
		static	CDiagramEntity* CreateFromString(const CString& str);

		// Overrides
		virtual void Draw(CDC* dc, CRect rect);
		virtual int		GetHitCode(CPoint point) const;
		virtual HCURSOR GetCursor(int hit) const;
		
		virtual void	SetMoved(BOOL moved);
		virtual BOOL	GetMoved();
		
		// Block-specific methods
		virtual void linkSubBlock(CProcessEntityBlock* subblock);
		virtual void unlinkSubBlock(CProcessEntityBlock* subblock);
		virtual void unlinkSubBlocks();
		virtual CObArray* getSubBlocks();
		virtual void setParentBlock(CProcessEntityBlock* parent);
		virtual CProcessEntityBlock* getParentBlock() const;
		virtual bool contains(CProcessEntityBlock* block, bool recursive);

		virtual void linkOutgoingEdge(CProcessLineEdge* edge);
		virtual void unlinkOutgoingEdge(CProcessLineEdge* edge);
		virtual void unlinkOutgoingEdges();
		virtual CObArray* getOutgoingEdges();
		virtual void linkIncomingEdge(CProcessLineEdge* edge);
		virtual void unlinkIncomingEdge(CProcessLineEdge* edge);
		virtual void unlinkIncomingEdges();
		virtual CObArray* getIncomingEdges();

		virtual void recomputeIntersectionLinks();
		
		virtual void autoResize();
		virtual void Highlight(CDC* dc, CRect rect);
		virtual bool IsTarget();
		virtual void SetTarget(BOOL isTarget);
		virtual bool canBeNested(CProcessEntityBlock* block);
		
		virtual CPoint getIntersection(CPoint innerPoint, CPoint outerPoint);

	protected:
		virtual CString				GetDefaultGetString() const;
		CObArray m_subblocks;
		CObArray m_outgoingEdges;
		CObArray m_incomingEdges;
		CProcessEntityBlock* parentBlock;
		bool m_target;

	private:
		CPropertyDialog	m_dlg;
		BOOL			m_moved;

};
#endif //_PROCESSENTITYBLOCK_H_

