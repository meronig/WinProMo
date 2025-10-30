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

#define DEHT_CENTER		10

#define PROMO_LOCK_FONTNAME			0x0001
#define PROMO_LOCK_FONTSIZE			0x0002
#define PROMO_LOCK_FONTWEIGHT		0x0004
#define PROMO_LOCK_FONTITALIC		0x0008
#define PROMO_LOCK_FONTUNDERLINE	0x0010
#define PROMO_LOCK_TEXTCOLOR		0x0020
#define PROMO_LOCK_BKCOLOR			0x0040
#define PROMO_LOCK_BKMODE			0x0080
#define PROMO_LOCK_ALIGNMENT		0x0100
#define PROMO_LOCK_ROTATION			0x0200
#define PROMO_LOCK_MARGINS			0x0400
#define PROMO_LOCK_ANCHORING		0x0800
#define PROMO_LOCK_REPOSITIONING	0x1000
#define PROMO_LOCK_SELECTION		0x2000

#define PROMO_VIEW_FIRST			0
#define PROMO_VIEW_LAST				1
#define PROMO_VIEW_MID				2

class AFX_EXT_CLASS CProMoLabel :
    public CDiagramEntity
{
public:
	friend class CProMoModel;
	
	CProMoLabel();
	virtual ~CProMoLabel();

	virtual CDiagramEntity* Clone();
	virtual void	Copy(CDiagramEntity* obj);

	static	CDiagramEntity* CreateFromString(const CString& str, CProMoModel* model);

	static CString GetModelFromString(const CString& str);
	static CString GetNameFromString(const CString& str);

	virtual CProMoModel* GetModel() const;
	virtual CString GetProperty() const;
	
	virtual void SetFitTitle(BOOL hasFitTitle);
	virtual BOOL HasFitTitle();

	virtual void SetFitView(BOOL hasFitView);
	virtual BOOL HasFitView();

	virtual BOOL IsLocked(const unsigned int& flag) const;
	virtual void SetLock(const unsigned int& flag);
	virtual CDoubleRect GetTitleRect() const;
	
	virtual CString GetFontName() const;
	virtual unsigned int GetFontSize() const;
	virtual unsigned int GetFontWeight() const;
	virtual BOOL IsFontItalic() const;
	virtual BOOL IsFontUnderline() const;
	virtual COLORREF GetTextColor() const;
	virtual COLORREF GetBkColor() const;
	virtual unsigned int GetBkMode() const;
	virtual unsigned int GetTextAlignment() const;
	virtual unsigned int GetLabelAnchorPoint() const;
	virtual unsigned int GetViewAnchorPoint() const;
	virtual unsigned int GetAnchorView() const;

	virtual BOOL SetFontName(const CString& name);
	virtual BOOL SetFontSize(const unsigned int& size);
	virtual BOOL SetFontWeight(const unsigned int& weight);
	virtual BOOL SetFontItalic(const BOOL& italic);
	virtual BOOL SetFontUnderline(const BOOL& underline);
	virtual BOOL SetTextColor(const COLORREF& color);
	virtual BOOL SetBkColor(const COLORREF& color);
	virtual BOOL SetBkMode(const unsigned int& mode);
	virtual BOOL SetTextAlignment(const unsigned int& alignment);
	virtual BOOL SetLabelAnchorPoint(const unsigned int& position);
	virtual BOOL SetViewAnchorPoint(const unsigned int& position);
	virtual BOOL SetAnchorView(const unsigned int& position);

	virtual void Reposition();


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
	virtual void AutoResize();

// Overrides

public:
	static	CDiagramEntity* CreateFromString(const CString& str);

	virtual void	Draw(CDC* dc, CRect rect);

	virtual void	ShowPopup(CPoint point, CWnd* parent);

	virtual void	SetTitle(CString title);

	virtual void	SetRect(CRect rect);
	virtual void	SetRect(double left, double top, double right, double bottom);

	virtual int		GetHitCode(const CPoint& point, const CRect& rect) const;


protected:
	virtual CString				GetDefaultGetString() const;
	virtual CString				GetHeaderFromString(CString& str);
	virtual BOOL				GetDefaultFromString(CString& str);

	
};

#endif //_PROMOBLOCKVIEW_H_