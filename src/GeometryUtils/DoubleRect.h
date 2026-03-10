/* ==========================================================================

	Copyright © 2025 Technical University of Denmark

	Author :		Giovanni Meroni

   ========================================================================*/
#ifndef _DOUBLERECT_H_
#define _DOUBLERECT_H_

#include "DoublePoint.h"

class AFX_EXT_CLASS CDoubleRect : public CObject
{

public:
	CDoubleRect();
	CDoubleRect(const CRect& rect);
	CDoubleRect(const double& left, const double& top, const double& right, const double& bottom);
	CDoubleRect(const CDoubleRect& other);

	CDoubleRect& operator=(const CDoubleRect& other);


	double Width() const;
	double Height() const;
	double Ratio() const;
	CDoublePoint CenterPoint() const;

	CRect ToCRect() const;

	void SetRect(const CRect& rect);
	void SetRect(const double& left, const double& top, const double& right, const double& bottom);
	void SetRect(const CDoubleRect& rect);

	BOOL IsRectEmpty() const;
	BOOL IsRectNull() const;
	void UnionRect(const CDoubleRect& rect1, const CDoubleRect& rect2);

	//member variables are public to ensure efficiency and compatibility with CRect
	double top;
	double bottom;
	double left;
	double right;
};

#endif //_DOUBLERECT_H_

