/* ==========================================================================

	Copyright © 2025 Technical University of Denmark

	Author :		Giovanni Meroni

   ========================================================================*/
#ifndef _PROMOEDITOR_H_
#define _PROMOEDITOR_H_

#include "../DiagramEditor/DiagramEditor.h"
#include "ProMoBlockView.h"
#include "ProMoEdgeView.h"
#include "ProMoControlFactory.h"
#include "../GeometryUtils/GeometryHelper.h"


#define WM_SELECTION_CHANGED (WM_APP + 100)

class AFX_EXT_CLASS CProMoEditor : public CDiagramEditor
{
public:
	// Construction/initialization/destruction
	CProMoEditor();
	virtual ~CProMoEditor();

public:
	virtual void	Load(const CStringArray& stra);
	virtual void NotifySelectionChanged();
	
	virtual void	MiddleAlignSelected();
	virtual void	CenterAlignSelected();
	
	virtual void SetFontName(const CString& name);
	virtual void SetFontSize(const unsigned int& size);
	virtual void SetFontWeight(const unsigned int& weight);
	virtual void SetFontItalic(const BOOL& italic);
	virtual void SetFontUnderline(const BOOL& underline);
	virtual void SetFontStrikeOut(const BOOL& strikeOut);
	virtual void SetTextColor(const COLORREF& color);
	virtual void SetBkColor(const COLORREF& color);
	virtual void SetBkMode(const unsigned int& mode);
	virtual void SetTextHorizontalAlignment(const unsigned int& flag);
	virtual void SetTextVerticalAlignment(const unsigned int& flag);
	virtual void SetTextAlignmentFlag(const unsigned int& flag, const BOOL& enabled);
	virtual void SetTextAlignment(const unsigned int& alignment);
	virtual void SetTextMultiline(const BOOL& multiline);
	virtual void SetLineColor(const COLORREF& color);
	virtual void SetLineWidth(const unsigned int& width);
	virtual void SetLineStyle(const unsigned int& style);
	virtual void SetFillColor(const COLORREF& color);
	virtual void SetFillPattern(const BOOL& pattern);
	virtual void SetFillStyle(const unsigned int& style);

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
	virtual BOOL IsTextMultiline() const;
	virtual COLORREF GetLineColor() const;
	virtual unsigned int GetLineWidth() const;
	virtual unsigned int GetLineStyle() const;
	virtual COLORREF GetFillColor() const;
	virtual BOOL IsFillPattern() const;
	virtual unsigned int GetFillStyle() const;

	virtual BOOL IsLocked(unsigned int lockType) const;
	virtual BOOL IsAnyLabelSelected() const;
	virtual BOOL IsAnyBlockSelected() const;
	virtual BOOL IsAnyEdgeSelected() const;

protected:
	virtual void DrawObjectsR(CProMoBlockView* block, CDC* dc, double zoom) const;
	virtual void ResetTarget();
	virtual CProMoBlockView* GetTarget() const;
	virtual void IdentifyTarget(CPoint point);
	virtual void SetTarget(CProMoBlockView* obj, unsigned int attachment);
	virtual void AttachSelectedBlock(CProMoBlockView* parentBlock);
	virtual BOOL RepositionSelectedBoundaryBlock();
	virtual void SplitSelectedEdge();
	virtual void CreateLabels();
	virtual void ConnectSelectedEdgeToSource(CProMoBlockView* sourceBlock);
	virtual void ConnectSelectedEdgeToDestination(CProMoBlockView* sourceBlock);
	virtual CProMoBlockView* GetConnectedBlock(CProMoEdgeView* line, BOOL backwards) const;
	virtual void SelectBoundaryBlocks(CProMoBlockView* block);
	virtual void DeselectInvalidElements();
	virtual void PrepareForAlignment();
	virtual void AutoResizeAll();
	virtual void DrawPageBreaks(CDC* dc, CRect rect, double zoom) const;
	virtual void HandleSelectedElements(CProMoBlockView* target, BOOL isNew);
	virtual void HandlePostResize(CDiagramEntity* element, UINT nFlags, CDoubleRect& oldRect, CPoint& point);
	virtual void DeselectLabels(CProMoBlockView* block);
	virtual void DeselectSubBlocks(CProMoBlockView* block);
	virtual void DeselectBoundaryBlocks(CProMoBlockView* block);

// Overrides:
public:
	// Visuals
	virtual void	Draw(CDC* dc, CRect rect) const;

	// Command handlers
	virtual void	Cut();
	virtual void	Paste();
	virtual void	Undo();
	virtual void	Redo();
	virtual void	SelectAll();
	virtual void	UnselectAll();
	virtual void	DeleteAllSelected();
	virtual void	LeftAlignSelected();
	virtual void	RightAlignSelected();
	virtual void	TopAlignSelected();
	virtual void	BottomAlignSelected();
	
	// Property Accessors
	virtual void	ShowPageBreaks(BOOL isVisible);
	virtual BOOL	IsPageBreaksVisible();
	virtual void	SetPageLayout(CDC* dc);
		
protected:
	virtual void DrawGrid(CDC* dc, CRect rect, double zoom) const;
	virtual void DrawObjects(CDC* dc, double zoom) const;
	virtual void SaveObjects(CStringArray& stra);

	// Message handlers
	virtual afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	virtual afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	virtual afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	virtual afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);

protected:
	BOOL m_pageBreaksVisible;
	int m_printResolutionX;
	int m_printResolutionY;
	CSize m_paperSize;
	CSize m_printableArea;
};

#endif //_PROMOEDITOR_H_
