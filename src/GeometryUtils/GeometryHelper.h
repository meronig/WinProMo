#ifndef _GEOMETRYHELPER_H_
#define _GEOMETRYHELPER_H_

#include "DoubleRect.h"
#include "DoublePoint.h"

class AFX_EXT_CLASS CGeometryHelper
{
public:
	static void EnforceAspectRatio(const CDoubleRect &oldRect, CDoubleRect &newRect, int submode, const CPoint &cursorLocation);
	static void AlignToAxis(CDoubleRect &rect, int submode);
	static CDoublePoint ScaleToRect(const CDoublePoint& v, const CDoubleRect& rect);
};

#endif //_GEOMETRYHELPER_H_