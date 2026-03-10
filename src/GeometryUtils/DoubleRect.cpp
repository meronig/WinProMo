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

CDoubleRect::CDoubleRect(const CRect& rect)
/* ============================================================
	Function :		CDoubleRect::CDoubleRect
	Description :	Constructor
	Access :		Public

	Return :		void
	Parameters :	CRect& rect	-	A 'CRect' rectangle to
									copy coordinates from

	Usage :

   ============================================================*/
{
	CDoubleRect::SetRect(rect);
}

CDoubleRect::CDoubleRect(const double& left, const double& top, const double& right, const double& bottom)
/* ============================================================
	Function :		CDoubleRect::CDoubleRect
	Description :	Constructor
	Access :		Public

	Return :		void
	Parameters :	double& left	-	Left edge
					double& top		-	Top edge
					double& right	-	Right edge
					double& bottom	-	Bottom edge

	Usage :

   ============================================================*/
{
	CDoubleRect::SetRect(left, top, right, bottom);
}

CDoubleRect::CDoubleRect(const CDoubleRect &other)
/* ============================================================
	Function :		CDoubleRect::CDoubleRect
	Description :	Copy constructor
	Access :		Public

	Return :		void
	Parameters :	CDoubleRect& other	-	rect to copy
											information from

	Usage :

   ============================================================*/
{
	CDoubleRect::SetRect(other);
}

CDoubleRect& CDoubleRect::operator=(const CDoubleRect& other)
/* ============================================================
	Function :		CDoubleRect::operator=
	Description :	Assignment operator
	Access :		Public

   ============================================================*/
{
	if (this != &other) {
		top = other.top;
		left = other.left;
		bottom = other.bottom;
		right = other.right;
	}
	return *this;
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

CDoublePoint CDoubleRect::CenterPoint() const
/* ============================================================
	Function :		CDoubleRect::CenterPoint
	Description :	Returns the center of the rectangle

	Return :		CDoublePoint	-	Center of the rectangle
	Parameters :	none

   ============================================================*/
{
	return CDoublePoint(left + (right - left) / 2, top + (bottom - top) / 2);
}

CRect CDoubleRect::ToCRect() const
/* ============================================================
	Function :		CDoubleRect::ToCRect
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

void CDoubleRect::SetRect(const CRect &rect)
/* ============================================================
	Function :		CDoubleRect::SetRect
	Description :	Sets the object rectangle, normalized.
	Access :		Public

	Return :		void
	Parameters :	CRect& rect	-	The rectangle to set.

   ============================================================*/
{

	SetRect(static_cast<double>(rect.left),
		static_cast<double>(rect.top),
		static_cast<double>(rect.right),
		static_cast<double>(rect.bottom));

}

void CDoubleRect::SetRect(const double& left, const double& top, const double& right, const double& bottom)
/* ============================================================
	Function :		CDoubleRect::SetRect
	Description :	Sets the object rectangle.
	Access :		Public

	Return :		void
	Parameters :	double& left	-	Left edge
					double& top		-	Top edge
					double& right	-	Right edge
					double& bottom	-	Bottom edge

   ============================================================*/
{
	this->left = left;
	this->top = top;
	this->right = right;
	this->bottom = bottom;
}

void CDoubleRect::SetRect(const CDoubleRect& rect)
/* ============================================================
	Function :		CDoubleRect::SetRect
	Description :	Sets the object rectangle, normalized.
	Access :		Public

	Return :		void
	Parameters :	CDoubleRect& rect	-	The rectangle to set.

   ============================================================*/
{
	top = rect.top;
	left = rect.left;
	bottom = rect.bottom;
	right = rect.right;
}

BOOL CDoubleRect::IsRectEmpty() const 
/* ============================================================
	Function :		CDoubleRect::IsRectEmpty
	Description :	Determines if the rectangle is empty, that
					is, its width and/or height is 0 or negative
	Access :		Public

	Return :		BOOL	-	"TRUE" if the rectangle is empty
	Parameters :	none

   ============================================================*/
{
	return (Width() <= 0 || Height() <= 0);
}

BOOL CDoubleRect::IsRectNull() const 
/* ============================================================
	Function :		CDoubleRect::IsRectNull
	Description :	Determines if the rectangle is null, that
					is, its left, right, top and bottom values
					are all 0.
	Access :		Public

	Return :		BOOL	-	"TRUE" if the rectangle is null
	Parameters :	none

   ============================================================*/
{
	return (left == 0 && right == 0 && top == 0 && bottom == 0);
}

void CDoubleRect::UnionRect(const CDoubleRect& rect1, const CDoubleRect& rect2)
/* ============================================================
	Function :		CDoubleRect::UnionRect
	Description :	Sets the object rectangle as the union of
					the two source rectangles
	Access :		Public

	Return :		void
	Parameters :	CRect& rect1	-	The first rectangle to use.
					CRect& rect2	-	The second rectangle to use.

   ============================================================*/
{

	if (rect1.IsRectEmpty()) {
		SetRect(rect2);
		return;
	}
	if (rect2.IsRectEmpty()) {
		SetRect(rect1);
		return;
	}

	left = min(rect1.left, rect2.left);
	top = min(rect1.top, rect2.top);
	right = max(rect1.right, rect2.right);
	bottom = max(rect1.bottom, rect2.bottom);
}
