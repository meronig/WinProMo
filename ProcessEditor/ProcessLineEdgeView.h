#ifndef _PROCESSLINEEDGEVIEW_H_
#define _PROCESSLINEEDGEVIEW_H_

//#include "../DiagramEditor/DiagramEntity.h"
#include "../DiagramEditor/DiagramLine.h"
#include "PropertyDialog.h"
#include "ProcessEntityBlockView.h"
//#include "ProcessLineEdgeModel.h"



#define DEHT_CENTER		10

class CProcessLineEdgeView :
    public CDiagramLine
{
public:
    CProcessLineEdgeView();
    virtual ~CProcessLineEdgeView();
    virtual	CDiagramEntity* Clone();
    static	CDiagramEntity* CreateFromString(const CString& str);

    virtual void SetSource(CDiagramEntity *source);
    virtual void SetDestination(CDiagramEntity *destination);
    virtual CDiagramEntity* GetSource() const;
    virtual CDiagramEntity* GetDestination() const;
    virtual CProcessLineEdgeModel* getModel() const;
    virtual void setModel(CProcessLineEdgeModel* model);


    // Overrides
    virtual void	Draw(CDC* dc, CRect rect);
	virtual int		GetHitCode( const CPoint& point, const CRect& rect ) const;

    virtual HCURSOR GetCursor(int hit) const;

protected:
    virtual CString				GetDefaultGetString() const;
    virtual void	DrawSelectionMarkers( CDC* dc, CRect rect ) const;
    virtual CRect	GetSelectionMarkerRect(UINT marker, CRect rect) const;
    virtual void DrawArrowHead(CDC* dc, POINT p0, POINT p1, int head_length, int head_width);
    virtual void DrawArrowTail(CDC* dc, POINT p0, POINT p1, int circleDiameter);
    virtual void Reposition();
	

private:
    CProcessLineEdgeView *m_source;
    CProcessLineEdgeView *m_dest;
    CPropertyDialog	m_dlg;
    CProcessLineEdgeModel* m_edgemodel;
};

#endif //_PROCESSLINEEDGEVIEW_H_