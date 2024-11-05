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
		void MoveRect(double x, double y);
		void SetRect(double left, double top, double right, double bottom);
		static	CDiagramEntity* CreateFromString(const CString& str);

		// Overrides
		virtual void Draw(CDC* dc, CRect rect);
		virtual int		GetHitCode(CPoint point) const;
		virtual HCURSOR GetCursor(int hit) const;
		void			SetMoved(BOOL moved);
		BOOL			GetMoved();

		
		// Block-specific methods
		void linkSubBlock(CProcessEntityBlock* subblock);
		void unlinkSubBlock(CProcessEntityBlock* subblock);
		void unlinkSubBlocks();
		CObArray* getSubBlocks();
		void setParentBlock(CProcessEntityBlock* parent);
		CProcessEntityBlock* getParentBlock() const;
		bool contains(CProcessEntityBlock* block, bool recursive);

		void linkOutgoingEdge(CProcessLineEdge* edge);
		void unlinkOutgoingEdge(CProcessLineEdge* edge);
		void unlinkOutgoingEdges();
		CObArray* getOutgoingEdges();
		void linkIncomingEdge(CProcessLineEdge* edge);
		void unlinkIncomingEdge(CProcessLineEdge* edge);
		void unlinkIncomingEdges();
		CObArray* getIncomingEdges();

		void recomputeIntersectionLinks();
		
		void autoResize();
		void Highlight(CDC* dc, CRect rect);
		bool IsTarget();
		void SetTarget(BOOL isTarget);
		
		CPoint getIntersection(CPoint innerPoint, CPoint outerPoint);

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

