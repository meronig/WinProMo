#include "DoublePoint.h"
#include "DoubleRect.h"
#ifndef _INTERSECTIONHELPER_H_
#define _INTERSECTIONHELPER_H_

class AFX_EXT_CLASS CIntersectionHelper
{
public:
	static CDoublePoint SegmentIntersectsRect(const CDoublePoint& innerPoint, const CDoublePoint& outerPoint, const CDoubleRect& rect);
	static CDoublePoint SegmentIntersectsEllipse(const CDoublePoint& innerPoint, const CDoublePoint& outerPoint, const CDoubleRect& rect);
};

#endif //_INTERSECTIONHELPER_H_

