/* ==========================================================================

	Copyright © 2025 Technical University of Denmark

	CDoubleRect

	Author :		Giovanni Meroni

	Purpose :		"CDoublePoint" is a class representing a point
					- similarly to MFC CPoint - whose coordinates are
					expressed with double, thus achieving higher precision.

   ========================================================================*/
#include "StdAfx.h"
#include "DoublePoint.h"

CDoublePoint::CDoublePoint()
/* ============================================================
	Function :		CDoublePoint::CDoublePoint
	Description :	Constructor
	Access :		Public

	Return :		void
	Parameters :	none

	Usage :

   ============================================================*/
{
	x = 0;
	y = 0;
}

CDoublePoint::CDoublePoint(const CPoint& pt)
/* ============================================================
	Function :		CDoublePoint::CDoublePoint
	Description :	Constructor
	Access :		Public

	Return :		void
	Parameters :	CPoint& pt	-	A 'CPoint' rectangle to
									copy coordinates from

	Usage :

   ============================================================*/
{
	CDoublePoint::SetPoint(pt);
}

CDoublePoint::CDoublePoint(const double& x, const double& y)
/* ============================================================
	Function :		CDoublePoint::CDoublePoint
	Description :	Constructor
	Access :		Public

	Return :		void
	Parameters :	double& x		-	horizontal position
					double& y		-	vertical position

	Usage :

   ============================================================*/
{
	CDoublePoint::SetPoint(x,y);
}

CDoublePoint::CDoublePoint(const CDoublePoint& other)
/* ============================================================
	Function :		CDoublePoint::CDoublePoint
	Description :	Copy constructor
	Access :		Public

	Return :		void
	Parameters :	CDoublePoint& other	-	point to copy 
											information from

	Usage :

   ============================================================*/
{
	x = other.x;
	y = other.y;
}

CDoublePoint& CDoublePoint::operator=(const CDoublePoint& other)
/* ============================================================
	Function :		CDoublePoint::operator=
	Description :	Assignment operator
	Access :		Public

   ============================================================*/
{
	if (this != &other) {
		// call CObject assignment if ever needed
		x = other.x;
		y = other.y;
	}
	return *this;
}

CPoint CDoublePoint::ToCPoint() const
/* ============================================================
	Function :		CDoublePoint::ToCPoint
	Description :	Returns the point.
	Access :		Public

	Return :		CPoint	-	The point.
	Parameters :	none

	Usage :			Call to get the object position.
					Will round of fractions.

   ============================================================*/
{
	return CPoint((int)x, (int)y);
}

void CDoublePoint::SetPoint(const CPoint& pt)
/* ============================================================
	Function :		CDoublePoint::SetPoint
	Description :	Sets the position, normalized.
	Access :		Public

	Return :		void
	Parameters :	CPoint& pt	-	The position to set.

   ============================================================*/
{

	SetPoint(static_cast<double>(pt.x),
		static_cast<double>(pt.y));

}

void CDoublePoint::SetPoint(const double& x, const double& y)
/* ============================================================
	Function :		CDoublePoint::SetPoint
	Description :	Sets the position.
	Access :		Public

	Return :		void
	Parameters :	double& x		-	horizontal position
					double& y		-	vertical position

   ============================================================*/
{
	this->x = x;
	this->y = y;
}
