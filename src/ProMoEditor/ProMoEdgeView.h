/* ==========================================================================

    Copyright © 2025 Technical University of Denmark

    Author :		Giovanni Meroni

   ========================================================================*/
#ifndef _PROMOEDGEVIEW_H_
#define _PROMOEDGEVIEW_H_

#include "../DiagramEditor/DiagramLine.h"
#include "ProMoBlockView.h"
#include "ProMoView.h"

#define DEHT_CENTER		10

class AFX_EXT_CLASS CProMoEdgeView :
    public CDiagramLine, public IProMoView
{
public:
    // Creation/initialization
    CProMoEdgeView();
    virtual ~CProMoEdgeView();
    
    static	CDiagramEntity* CreateFromString(const CString& str, CProMoModel* model);
    
    static CString GetSourceFromString(const CString& str);
    static CString GetDestinationFromString(const CString& str);
    static CString GetModelFromString(const CString& str);
    static CString GetNameFromString(const CString& str);

    // Edge-specific methods
    virtual void SetSource(CDiagramEntity *source);
    virtual void SetDestination(CDiagramEntity *destination);
    virtual CDiagramEntity* GetSource() const;
    virtual CDiagramEntity* GetDestination() const;
    virtual BOOL IsFirstSegment() const;
    virtual BOOL IsLastSegment() const;
    virtual CProMoEdgeView* Split();

protected:
    virtual void DrawLine(CDC* dc, CRect rect);
    virtual void DrawHead(CDC* dc, CRect rect, double size);
    virtual void DrawTail(CDC* dc, CRect rect, double size);
    
    // Model-view links
    virtual void SetSourceEdge(CProMoEdgeView* source);
    virtual void SetSourceBlock(CProMoBlockView* source);
    virtual void SetDestinationEdge(CProMoEdgeView* destination);
    virtual void SetDestinationBlock(CProMoBlockView* destination);
    
    CProMoEdgeView* m_source;
    CProMoEdgeView* m_dest;

    CProMoEdgeModel* m_edgeModel;	

private:
    BOOL m_propagating;
    COLORREF		m_bkColor;
	unsigned int	m_bkMode;
    BOOL			m_visible;
    unsigned int	m_lockFlags;
    COLORREF		m_lineColor;
    unsigned int	m_lineWidth;
    unsigned int	m_lineStyle;

    class CScopedUpdate {
    public:
        CScopedUpdate(BOOL& flag) : m_flag(flag) { m_flag = TRUE; }
        ~CScopedUpdate() { m_flag = FALSE; }
    private:
        BOOL& m_flag;
    };

    // Implements
public:
    virtual CProMoModel* GetModel() const;
    virtual void AutoResize();
    virtual void Reposition();

    virtual BOOL IsLocked(const unsigned int& flag) const;
    virtual unsigned int GetLock() const;
    virtual void SetLock(const unsigned int& flag);

    virtual CString GetFontName() const;
    virtual unsigned int GetFontSize() const;
    virtual unsigned int GetFontWeight() const;
    virtual BOOL IsFontItalic() const;
    virtual BOOL IsFontUnderline() const;
    virtual BOOL IsFontStrikeOut() const;
    virtual COLORREF GetTextColor() const;
    virtual COLORREF GetBkColor() const;
    virtual unsigned int GetBkMode() const;
    virtual unsigned int GetTextHorizontalAlignment() const;
    virtual unsigned int GetTextVerticalAlignment() const;
    virtual BOOL HasTextAlignmentFlag(unsigned int flag) const;
    virtual unsigned int GetTextAlignment() const;
    virtual BOOL IsVisible() const;
    //virtual void GetMargins(double& left, double& top, double& right, double& bottom) const;

    virtual BOOL SetFontName(const CString& name);
    virtual BOOL SetFontSize(const unsigned int& size);
    virtual BOOL SetFontWeight(const unsigned int& weight);
    virtual BOOL SetFontItalic(const BOOL& italic);
    virtual BOOL SetFontUnderline(const BOOL& underline);
    virtual BOOL SetFontStrikeOut(const BOOL& strikeOut);
    virtual BOOL SetTextColor(const COLORREF& color);
    virtual BOOL SetBkColor(const COLORREF& color);
    virtual BOOL SetBkMode(const unsigned int& mode);
    virtual BOOL SetTextHorizontalAlignment(const unsigned int& flag);
    virtual BOOL SetTextVerticalAlignment(const unsigned int& flag);
    virtual BOOL SetTextAlignmentFlag(const unsigned int& flag, const BOOL& enabled);
    virtual BOOL SetTextAlignment(const unsigned int& alignment);
    virtual BOOL SetVisible(const BOOL& visible);
    //virtual void SetMargins(double left, double top, double right, double bottom);

    virtual void LinkLabel(CProMoLabel* label);
    virtual void OnLabelChanged(CProMoLabel* label);

    virtual COLORREF GetLineColor() const;
    virtual unsigned int GetLineWidth() const;
    virtual unsigned int GetLineStyle() const;

    virtual BOOL SetLineColor(const COLORREF& color);
    virtual BOOL SetLineWidth(const unsigned int& width);
    virtual BOOL SetLineStyle(const unsigned int& style);

protected:
    virtual void SetModel(CProMoModel* model);

    virtual void KeepElementsConnected(double left, double top, double right, double bottom);

// Overrides
public:
    virtual	CDiagramEntity* Clone();
    virtual void	Copy(CDiagramEntity* obj);
    
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
    virtual CString				GetHeaderFromString(CString& str);
    virtual BOOL				GetDefaultFromString(CString& str);

    virtual CRect	GetSelectionMarkerRect(UINT marker, CRect rect) const;


};

#endif //_PROMOEDGEVIEW_H_