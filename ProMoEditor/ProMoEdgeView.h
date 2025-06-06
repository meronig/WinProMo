#ifndef _PROMOEDGEVIEW_H_
#define _PROMOEDGEVIEW_H_

#include "../DiagramEditor/DiagramLine.h"
#include "PropertyDialog.h"
#include "ProMoBlockView.h"



#define DEHT_CENTER		10

class CProMoEdgeView :
    public CDiagramLine
{
public:
    CProMoEdgeView();
    virtual ~CProMoEdgeView();
    virtual	CDiagramEntity* Clone();
    static	CDiagramEntity* CreateFromString(const CString& str);

    virtual void SetSource(CDiagramEntity *source);
    virtual void SetDestination(CDiagramEntity *destination);
    virtual CDiagramEntity* GetSource() const;
    virtual CDiagramEntity* GetDestination() const;
    virtual CProMoEdgeModel* getModel() const;
    virtual void setModel(CProMoEdgeModel* model);


    // Overrides
    virtual void	Draw(CDC* dc, CRect rect);
	virtual int		GetHitCode( const CPoint& point, const CRect& rect ) const;

    virtual HCURSOR GetCursor(int hit) const;

protected:
    virtual CString				GetDefaultGetString() const;
    virtual BOOL				GetDefaultFromString(CString& str);

    virtual void	DrawSelectionMarkers( CDC* dc, CRect rect ) const;
    virtual CRect	GetSelectionMarkerRect(UINT marker, CRect rect) const;
    virtual void DrawArrowHead(CDC* dc, POINT p0, POINT p1, int head_length, int head_width);
    virtual void DrawArrowTail(CDC* dc, POINT p0, POINT p1, int circleDiameter);
    virtual void Reposition();
	

private:
    CProMoEdgeView *m_source;
    CProMoEdgeView *m_dest;
    CPropertyDialog	m_dlg;
    CProMoEdgeModel* m_edgemodel;
};

#endif //_PROMOEDGEVIEW_H_