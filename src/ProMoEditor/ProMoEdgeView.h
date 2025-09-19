/* ==========================================================================

    Copyright © 2025 Technical University of Denmark

    Author :		Giovanni Meroni

   ========================================================================*/
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
    virtual void	Copy(CDiagramEntity* obj);
    static	CDiagramEntity* CreateFromString(const CString& str, CProMoModel* model);

    virtual CProMoEdgeModel* GetModel() const;

    // Edge-specific methods
    virtual void SetSource(CDiagramEntity *source);
    virtual void SetDestination(CDiagramEntity *destination);
    virtual CDiagramEntity* GetSource() const;
    virtual CDiagramEntity* GetDestination() const;
    virtual BOOL IsFirstSegment() const;
    virtual BOOL IsLastSegment() const;
    virtual CProMoEdgeView* Split();
 
protected:
    virtual void DrawHead(CDC* dc, CRect rect, int size);
    virtual void DrawTail(CDC* dc, CRect rect, int size);
    virtual void Reposition();
    
    // Model-view links
    virtual void SetModel(CProMoEdgeModel* model);
    virtual void SetSourceEdge(CProMoEdgeView* source);
    virtual void SetSourceBlock(CProMoBlockView* source);
    virtual void SetDestinationEdge(CProMoEdgeView* destination);
    virtual void SetDestinationBlock(CProMoBlockView* destination);
    
    CProMoEdgeView* m_source;
    CProMoEdgeView* m_dest;

    CProMoEdgeModel* m_edgemodel;	

private:
    CPropertyDialog	m_dlg;

    BOOL m_propagating;

    class CScopedUpdate {
    public:
        CScopedUpdate(BOOL& flag) : m_flag(flag) { m_flag = TRUE; }
        ~CScopedUpdate() { m_flag = FALSE; }
    private:
        BOOL& m_flag;
    };

// Overrides
public:
    static	CDiagramEntity* CreateFromString(const CString& str);

    virtual void	Draw(CDC* dc, CRect rect);
    virtual int		GetHitCode(const CPoint& point, const CRect& rect) const;
    virtual HCURSOR GetCursor(int hit) const;
    virtual void	DrawSelectionMarkers(CDC* dc, CRect rect) const;

    virtual void	ShowPopup(CPoint point, CWnd* parent);

    virtual void	SetRect(CRect rect);
    virtual void    SetRect(double left, double top, double right, double bottom);
    virtual void	SetLeft(double left);
    virtual void	SetRight(double right);
    virtual void	SetTop(double top);
    virtual void	SetBottom(double bottom);


protected:
    virtual CString				GetDefaultGetString() const;
    virtual BOOL				GetDefaultFromString(CString& str);

    virtual CRect	GetSelectionMarkerRect(UINT marker, CRect rect) const;


};

#endif //_PROMOEDGEVIEW_H_