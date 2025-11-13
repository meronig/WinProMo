/* ==========================================================================

	Copyright © 2025 Technical University of Denmark

	Author :		Giovanni Meroni

   ========================================================================*/
#ifndef _PROMOLABEL_H_
#define _PROMOLABEL_H_

#include "../DiagramEditor/DiagramEntity.h"
#include "ProMoModel.h"
#include "../GeometryUtils/DoublePoint.h"
#include "../GeometryUtils/DoubleRect.h"
#include "ProMoEntity.h"

const unsigned int H_GROUP = DT_LEFT | DT_CENTER | DT_RIGHT;
const unsigned int V_GROUP = DT_TOP | DT_VCENTER | DT_BOTTOM;
const unsigned int LINE_GROUP = DT_SINGLELINE | DT_WORDBREAK;


class AFX_EXT_CLASS CProMoLabel :
    public CDiagramEntity, public IProMoEntity
{
public:
	friend class CProMoModel;
	
	CProMoLabel();
	virtual ~CProMoLabel();

	static	CDiagramEntity* CreateFromString(const CString& str, CProMoModel* model);

	static CString GetModelFromString(const CString& str);
	static CString GetNameFromString(const CString& str);

	virtual CString GetProperty() const;
	
	virtual void SetFitTitle(BOOL hasFitTitle);
	virtual BOOL HasFitTitle();

	virtual void SetFitView(BOOL hasFitView);
	virtual BOOL HasFitView();

	virtual CDoubleRect GetTitleRect() const;
	

protected:
	CProMoModel* m_model;
	CString m_property;
	unsigned int m_lockFlags;

	BOOL			m_fitTitle;
	CDoubleRect		m_titleRect;
	BOOL			m_fitView;

	CString m_fontName;
	unsigned int m_fontSize;
	unsigned int m_fontWeight;
	BOOL m_fontItalic;
	BOOL m_fontUnderline;
	BOOL m_fontStrikeOut;
	COLORREF m_textColor;
	COLORREF m_bkColor;
	unsigned int m_bkMode;
	unsigned int m_textAlignment;
	unsigned int m_rotation;
	double m_topMargin;
	double m_leftMargin;
	double m_bottomMargin;
	double m_rightMargin;
	unsigned int m_labelAnchorPoint;
	unsigned int m_viewAnchorPoint;
	unsigned int m_anchorView;
	CDoublePoint m_offset;

	BOOL m_visible;

	BOOL m_noOffset;
	
	class CScopedUpdate {
	public:
		CScopedUpdate(BOOL& flag) : m_flag(flag) { m_flag = TRUE; }
		~CScopedUpdate() { m_flag = FALSE; }
	private:
		BOOL& m_flag;
	};

	virtual CDoublePoint GetSelectionMarkerPoint(UINT marker, CDoubleRect rect) const;
	virtual CDoublePoint ComputeAnchoredPosition() const;
	virtual void UpdateOffset();
	
	virtual void SetProperty(const CString& property);
	virtual CDoubleRect ComputeTextRect(CDC* dc, double zoom);
	virtual CDiagramEntity* GetView() const;

	
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
	virtual unsigned int GetLabelAnchorPoint() const;
	virtual unsigned int GetViewAnchorPoint() const;
	virtual unsigned int GetAnchorView() const;
	virtual BOOL IsVisible() const;
	virtual void GetMargins(double& left, double& top, double& right, double& bottom) const;

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
	virtual BOOL SetLabelAnchorPoint(const unsigned int& position);
	virtual BOOL SetViewAnchorPoint(const unsigned int& position);
	virtual BOOL SetAnchorView(const unsigned int& position);
	virtual BOOL SetVisible(const BOOL& visible);
	virtual void SetMargins(double left, double top, double right, double bottom);

protected:
	virtual void SetModel(CProMoModel* model);

// Overrides

public:
	virtual CDiagramEntity* Clone();
	virtual void	Copy(CDiagramEntity* obj);

	static	CDiagramEntity* CreateFromString(const CString& str);

	virtual void	Draw(CDC* dc, CRect rect);

	virtual void	ShowPopup(CPoint point, CWnd* parent);

	virtual void	SetTitle(CString title);

	virtual void	SetRect(CRect rect);
	virtual void	SetRect(double left, double top, double right, double bottom);

	virtual int		GetHitCode(const CPoint& point, const CRect& rect) const;

	virtual void	Select(BOOL selected);


protected:
	virtual CString				GetDefaultGetString() const;
	virtual CString				GetHeaderFromString(CString& str);
	virtual BOOL				GetDefaultFromString(CString& str);

	
};

#endif //_PROMOLABEL_H_