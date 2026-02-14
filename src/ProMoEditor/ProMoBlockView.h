/* ==========================================================================

	Copyright © 2025 Technical University of Denmark

	Author :		Giovanni Meroni

   ========================================================================*/
#ifndef _PROMOBLOCKVIEW_H_
#define _PROMOBLOCKVIEW_H_

#include "../DiagramEditor/DiagramEntity.h"
#include "ProMoBlockModel.h"
#include "../GeometryUtils/DoublePoint.h"
#include "../GeometryUtils/DoubleRect.h"
#include "ProMoView.h"

#define SHAPE_CUSTOM 0
#define SHAPE_RECTANGLE 1
#define SHAPE_ELLIPSE 2
#define SHAPE_POLYGON 3

#define LOCK_FILLCOLOR		0x40000
#define LOCK_FILLSTYLE		0x80000


class AFX_EXT_CLASS CProMoBlockView : public CDiagramEntity, public IProMoView
{

public:
	// Creation/initialization
	CProMoBlockView();
	virtual ~CProMoBlockView();

	static	CDiagramEntity* CreateFromString(const CString& str, CProMoModel* model);
	static	CDiagramEntity* Create(const CString& str);

	static CString GetModelFromString(const CString& str);
	static CString GetNameFromString(const CString& str);
		
	virtual BOOL IsTarget() const;
	virtual unsigned int GetTargetAttachment() const;
	virtual void SetTarget(unsigned int attachment);
	
	virtual void SetLockedProportions(BOOL hasLockedProportions);
	virtual BOOL HasLockedProportions() const;

	virtual CProMoBlockModel* GetBlockModel() const;

	virtual void LinkSubBlock(CProMoBlockView* block);
	virtual void UnlinkSubBlock(CProMoBlockView* block);
	virtual void UnlinkAllSubBlocks();
	
	virtual void LinkBoundaryBlock(CProMoBlockView* block, unsigned int attachment);
	virtual void UnlinkBoundaryBlock(CProMoBlockView* block);
	virtual void UnlinkAllBoundaryBlocks();
	
	virtual void UnlinkFromParent();
	
	
	virtual CPoint GetIntersection(CPoint innerPoint, CPoint outerPoint);

	virtual COLORREF GetFillColor() const;
	virtual BOOL IsFillPattern() const;
	virtual unsigned int GetFillStyle() const;

	virtual BOOL SetFillColor(const COLORREF& color);
	virtual BOOL SetFillPattern(const BOOL& pattern);
	virtual BOOL SetFillStyle(const unsigned int& style);
	

protected:
	unsigned int m_targetAttachment;
	CProMoBlockModel* m_blockModel;

	virtual void RecomputeIntersectionLinks();
	virtual CPoint MapPointToNewRect(CPoint oldPoint, double left, double top, double right, double bottom);
	
	virtual void SetShape(const int& type);
	virtual int GetShape() const;

	virtual BOOL AddVertex(const CDoublePoint &point);
	virtual void GetVertices(CObArray& vertices) const;
	virtual void ClearVertices();

	virtual void DrawShape(CDC* dc, CRect& rect);
	virtual void Highlight(CDC* dc, CRect rect);
	
	virtual BOOL IsFitCompatible(UINT shapeAnchor, UINT labelAnchor) const;
	virtual void AdjustToLabel(CProMoLabel* label);
	

private:
	BOOL			m_moved;
	BOOL			m_lockProportions;
	CDoubleRect		m_titleRect;
	int				m_shape;
	CObArray		m_vertices;
	COLORREF		m_bkColor;
	unsigned int	m_bkMode;
	BOOL			m_visible;
	unsigned int	m_lockFlags;
	COLORREF		m_lineColor;
	unsigned int	m_lineWidth;
	unsigned int	m_lineStyle;
	COLORREF		m_fillColor;
	BOOL			m_fillPattern;
	unsigned int	m_fillStyle;

	CProMoAppChildAuto* m_autoObject;

	
// Implements
public:
	virtual BOOL HasType(const CString& type) const;
	
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
	
	virtual void LinkLabel(CProMoLabel* label);
	virtual void OnLabelChanged(CProMoLabel* label);

	virtual COLORREF GetLineColor() const;
	virtual unsigned int GetLineWidth() const;
	virtual unsigned int GetLineStyle() const;

	virtual BOOL SetLineColor(const COLORREF& color);
	virtual BOOL SetLineWidth(const unsigned int& width);
	virtual BOOL SetLineStyle(const unsigned int& style);

	virtual CProMoAppChildAuto* GetAutomationObject();
	virtual void ReleaseAutomationObject();

protected:
	virtual void SetModel(CProMoModel* model);
	
	virtual void KeepElementsConnected(double left, double top, double right, double bottom);

// Overrides
public:
	virtual CDiagramEntity* Clone();
	virtual void	Copy(CDiagramEntity* obj);

	static	CDiagramEntity* CreateFromString(const CString& str);

	virtual void Draw(CDC* dc, CRect rect);
	virtual int		GetHitCode(CPoint point) const;
	virtual int		GetHitCode(const CPoint& point, const CRect& rect) const;

	virtual void	ShowPopup(CPoint point, CWnd* parent);

	virtual void	SetTitle(CString title);

	virtual void	SetRect(CRect rect);
	virtual void	SetRect(double left, double top, double right, double bottom);

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
#endif //_PROMOBLOCKVIEW_H_

