/* ==========================================================================

	Copyright © 2025 Technical University of Denmark

	CDoubleRect

	Author :		Giovanni Meroni

	Purpose :		"CDoubleRect" is a class representing a rectangle 
					- similarly to MFC CRect - whose coordinates are 
					expressed with double, thus achieving higher precision.

   ========================================================================*/
#include "StdAfx.h"
#include "DoubleRect.h"
#include "../DiagramEditor/DiagramEntity.h"

CDoubleRect::CDoubleRect()
/* ============================================================
	Function :		CDoubleRect::CDoubleRect
	Description :	Constructor
	Access :		Public

	Return :		void
	Parameters :	none

	Usage :

   ============================================================*/
{
	top = 0;
	bottom = 0;
	left = 0;
	right = 0;
}

CDoubleRect::CDoubleRect(CRect rect)
/* ============================================================
	Function :		CDoubleRect::CDoubleRect
	Description :	Constructor
	Access :		Public

	Return :		void
	Parameters :	CRect rect	-	A 'CRect' rectangle to
									copy coordinates from

	Usage :

   ============================================================*/
{
	CDoubleRect::SetRect(rect);
}

CDoubleRect::CDoubleRect(double left, double top, double right, double bottom)
/* ============================================================
	Function :		CDoubleRect::CDoubleRect
	Description :	Constructor
	Access :		Public

	Return :		void
	Parameters :	double left		-	Left edge
					double top		-	Top edge
					double right	-	Right edge
					double bottom	-	Bottom edge

	Usage :

   ============================================================*/
{
	CDoubleRect::SetRect(left, top, right, bottom);
}

double CDoubleRect::Width() const
/* ============================================================
	Function :		CDoubleRect::GetWidth
	Description :	Returns the width of the rectangle

	Return :		double	-	Rectangle width
	Parameters :	none

   ============================================================*/
{
	return right - left;
}

double CDoubleRect::Height() const
/* ============================================================
	Function :		CDoubleRect::GetHeight
	Description :	Returns the height of the rectangle

	Return :		double	-	Rectangle height
	Parameters :	none

   ============================================================*/
{
	return bottom - top;
}

double CDoubleRect::Ratio() const
/* ============================================================
	Function :		CDoubleRect::GetRatio
	Description :	Returns the ratio of the rectangle, 
					expressed as height:width

	Return :		double	-	Rectangle ratio
	Parameters :	none

   ============================================================*/
{
	return Height() / Width();
}

CRect CDoubleRect::ToCRect() const
/* ============================================================
	Function :		CDoubleRect::GetRect
	Description :	Returns the object rectangle.
	Access :		Public

	Return :		CRect	-	The object rectangle.
	Parameters :	none

	Usage :			Call to get the object position and size.
					Will round of fractions.

   ============================================================*/
{
	return CRect((int)left, (int)top, (int)right, (int)bottom);
}

void CDoubleRect::SetRect(CRect rect)
/* ============================================================
	Function :		CDoubleRect::SetRect
	Description :	Sets the object rectangle, normalized.
	Access :		Public

	Return :		void
	Parameters :	CRect rect	-	The rectangle to set.

   ============================================================*/
{

	SetRect(static_cast<double>(rect.left),
		static_cast<double>(rect.top),
		static_cast<double>(rect.right),
		static_cast<double>(rect.bottom));

}

void CDoubleRect::SetRect(double left, double top, double right, double bottom)
/* ============================================================
	Function :		CDoubleRect::SetRect
	Description :	Sets the object rectangle.
	Access :		Public

	Return :		void
	Parameters :	double left		-	Left edge
					double top		-	Top edge
					double right	-	Right edge
					double bottom	-	Bottom edge

   ============================================================*/
{
	this->left = left;
	this->top = top;
	this->right = right;
	this->bottom = bottom;
}
