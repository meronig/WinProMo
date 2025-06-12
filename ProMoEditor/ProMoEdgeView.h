#ifndef _PROMOEDGEVIEW_H_
#define _PROMOEDGEVIEW_H_

#include "../DiagramEditor/DiagramLine.h"
#include "PropertyDialog.h"
#include "ProMoBlockView.h"

#define DEHT_CENTER		10

class AFX_EXT_CLASS CProMoEdgeView :
    public CDiagramLine
{
public:
    // Creation/initialization
    CProMoEdgeView();
    virtual ~CProMoEdgeView();
    
    virtual	CDiagramEntity* Clone();
    
    // Model-view links
    virtual CProMoEdgeModel* GetModel() const;
    virtual void SetModel(CProMoEdgeModel* model);

    // Edge-specific methods
    virtual void SetSource(CDiagramEntity *source);
    virtual void SetDestination(CDiagramEntity *destination);
    virtual CDiagramEntity* GetSource() const;
    virtual CDiagramEntity* GetDestination() const;

 
protected:
    virtual void DrawHead(CDC* dc, CRect rect, int size);
    virtual void DrawTail(CDC* dc, CRect rect, int size);
    virtual void Reposition();

    CProMoEdgeView* m_source;
    CProMoEdgeView* m_dest;

    CProMoEdgeModel* m_edgemodel;	

private:
    CPropertyDialog	m_dlg;

// Overrides
public:
    static	CDiagramEntity* CreateFromString(const CString& str);

    virtual void	Draw(CDC* dc, CRect rect);
    virtual int		GetHitCode(const CPoint& point, const CRect& rect) const;
    virtual HCURSOR GetCursor(int hit) const;
    virtual void	DrawSelectionMarkers(CDC* dc, CRect rect) const;


protected:
    virtual CString				GetDefaultGetString() const;
    virtual BOOL				GetDefaultFromString(CString& str);

    virtual CRect	GetSelectionMarkerRect(UINT marker, CRect rect) const;


};

#endif //_PROMOEDGEVIEW_H_