#ifndef _PROCESSLINEEDGE_H_
#define _PROCESSLINEEDGE_H_

#include "../DiagramEditor/DiagramLine.h"
#include "PropertyDialog.h"
#include "ProcessEntityBlock.h"

#define DEHT_CENTER		10

class CProcessLineEdge :
    public CDiagramLine
{
public:
    CProcessLineEdge();
    virtual ~CProcessLineEdge();
    virtual	CDiagramEntity* Clone();
    static	CDiagramEntity* CreateFromString(const CString& str);

    virtual void SetSource(CDiagramEntity *source);
    virtual void SetDestination(CDiagramEntity *destination);
    virtual CDiagramEntity* GetSource() const;
    virtual CDiagramEntity* GetDestination() const;

    // Overrides
    virtual void	Draw(CDC* dc, CRect rect);
	virtual int		GetHitCode( const CPoint& point, const CRect& rect ) const;

    virtual HCURSOR GetCursor(int hit) const;

    virtual bool canConnectSource(CDiagramEntity* source);
    virtual bool canConnectDestination(CDiagramEntity* destination);

protected:
    virtual CString				GetDefaultGetString() const;
    virtual void	DrawSelectionMarkers( CDC* dc, CRect rect ) const;
    virtual CRect	GetSelectionMarkerRect(UINT marker, CRect rect) const;

	

private:
    CDiagramEntity *m_source;
    CDiagramEntity *m_dest;
    CPropertyDialog	m_dlg;
};

#endif //_PROCESSLINEEDGE_H_