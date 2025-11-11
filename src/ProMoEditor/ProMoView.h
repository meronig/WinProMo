/* ==========================================================================

	Copyright © 2025 Technical University of Denmark

	Author :		Giovanni Meroni

   ========================================================================*/
#ifndef _PROMOVIEW_H_
#define _PROMOVIEW_H_

#include "ProMoEntity.h"
#include "ProMoLabel.h"

#define LOCK_LINECOLOR		0x8000
#define LOCK_LINEWIDTH		0x10000
#define LOCK_LINESTYLE		0x20000

class AFX_EXT_CLASS IProMoView : public IProMoEntity
{

public:
	// Creation/initialization
	virtual ~IProMoView() {};

	virtual void LinkLabel(CProMoLabel* label) = 0;
	virtual void OnLabelChanged(CProMoLabel* label) = 0;

	virtual COLORREF GetLineColor() const = 0;
	virtual unsigned int GetLineWidth() const = 0;
	virtual unsigned int GetLineStyle() const = 0;

	virtual BOOL SetLineColor(const COLORREF& color) = 0;
	virtual BOOL SetLineWidth(const unsigned int& width) = 0;
	virtual BOOL SetLineStyle(const unsigned int& style) = 0;

protected:

	virtual void KeepElementsConnected(double left, double top, double right, double bottom) = 0;

};
#endif //_PROMOVIEW_H_
