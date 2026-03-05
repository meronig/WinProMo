/* ==========================================================================

	Copyright © 2025 Technical University of Denmark

	Author :		Giovanni Meroni

   ========================================================================*/
#ifndef _PROMOENTITY_H_
#define _PROMOENTITY_H_

#include "ProMoModel.h"
#include "../Automation/ProMoAutomationHost.h"

#define DEHT_CENTER		10
#define DEHT_TOP		11
#define DEHT_BOTTOM		12
#define DEHT_LEFT		13
#define DEHT_RIGHT		14

#define LOCK_FONTNAME			0x0001
#define LOCK_FONTSIZE			0x0002
#define LOCK_FONTWEIGHT		0x0004
#define LOCK_FONTITALIC		0x0008
#define LOCK_FONTUNDERLINE	0x0010
#define LOCK_FONTSTRIKEOUT	0x0020
#define LOCK_TEXTCOLOR		0x0040
#define LOCK_BKCOLOR			0x0080
#define LOCK_BKMODE			0x0100
#define LOCK_ALIGNMENT		0x0200
#define LOCK_ROTATION			0x0400
#define LOCK_MARGINS			0x0800
#define LOCK_ANCHORING		0x1000
#define LOCK_REPOSITIONING	0x2000
#define LOCK_SELECTION		0x4000

#define VIEW_FIRST			0
#define VIEW_LAST				1
#define VIEW_MID				2

class AFX_EXT_CLASS IProMoEntity : public IProMoAutomationHost
{

public:
	// Creation/initialization
	virtual ~IProMoEntity() {};

	// Model-view links
	virtual CProMoModel* GetModel() const = 0;

	virtual BOOL HasType(const CString& type) const = 0;

	virtual void AutoResize() = 0;

	virtual void Reposition() = 0;

	//Style
	virtual BOOL IsLocked(const unsigned int& flag) const = 0;
	virtual unsigned int GetLock() const = 0;
	virtual void SetLock(const unsigned int& flag) = 0;

	virtual CString GetFontName() const = 0;
	virtual unsigned int GetFontSize() const = 0;
	virtual unsigned int GetFontWeight() const = 0;
	virtual BOOL IsFontItalic() const = 0;
	virtual BOOL IsFontUnderline() const = 0;
	virtual BOOL IsFontStrikeOut() const = 0;
	virtual COLORREF GetTextColor() const = 0;
	virtual COLORREF GetBkColor() const = 0;
	virtual unsigned int GetBkMode() const = 0;
	virtual BOOL HasTextAlignmentFlag(unsigned int flag) const = 0;
	virtual unsigned int GetTextHorizontalAlignment() const = 0;
	virtual unsigned int GetTextVerticalAlignment() const = 0;
	virtual unsigned int GetTextAlignment() const = 0;
	virtual BOOL IsTextMultiline() const = 0;
	virtual BOOL IsVisible() const = 0;
	//virtual void GetMargins(double& left, double& top, double& right, double& bottom) const = 0;

	virtual BOOL SetFontName(const CString& name) = 0;
	virtual BOOL SetFontSize(const unsigned int& size) = 0;
	virtual BOOL SetFontWeight(const unsigned int& weight) = 0;
	virtual BOOL SetFontItalic(const BOOL& italic) = 0;
	virtual BOOL SetFontUnderline(const BOOL& underline) = 0;
	virtual BOOL SetFontStrikeOut(const BOOL& strikeOut) = 0;
	virtual BOOL SetTextColor(const COLORREF& color) = 0;
	virtual BOOL SetBkColor(const COLORREF& color) = 0;
	virtual BOOL SetBkMode(const unsigned int& mode) = 0;
	virtual BOOL SetTextAlignmentFlag(const unsigned int& flag, const BOOL& enabled) = 0;
	virtual BOOL SetTextHorizontalAlignment(const unsigned int& flag) = 0;
	virtual BOOL SetTextVerticalAlignment(const unsigned int& flag) = 0;
	virtual BOOL SetTextAlignment(const unsigned int& alignment) = 0;
	virtual BOOL SetTextMultiline(const BOOL& multiline) = 0;
	virtual BOOL SetVisible(const BOOL& visible) = 0;
	//virtual void SetMargins(double left, double top, double right, double bottom) = 0;


protected:
	
	virtual void SetModel(CProMoModel* model) = 0;

	

};
#endif //_PROMOENTITY_H_

