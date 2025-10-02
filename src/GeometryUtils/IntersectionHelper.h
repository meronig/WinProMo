#include "DoublePoint.h"
#include "DoubleRect.h"
#ifndef _INTERSECTIONHELPER_H_
#define _INTERSECTIONHELPER_H_

class AFX_EXT_CLASS CIntersectionHelper
{
public:
	static CDoublePoint SegmentIntersectsRect(const CDoublePoint& innerPoint, const CDoublePoint& outerPoint, const CDoubleRect& rect);
	static CDoublePoint SegmentIntersectsEllipse(const CDoublePoint& innerPoint, const CDoublePoint& outerPoint, const CDoubleRect& rect);
	static CDoublePoint SegmentIntersectsPolygon(const CDoublePoint& p1, const CDoublePoint& p2, const CDoubleRect& rect, const CObArray* points);
protected:
	static CDoublePoint SegmentIntersectsSegment(const CDoublePoint& p1, const CDoublePoint& p2, const CDoublePoint& q1, const CDoublePoint& q2);
	
};

#endif //_INTERSECTIONHELPER_H_

