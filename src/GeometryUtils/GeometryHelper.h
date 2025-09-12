#ifndef _GEOMETRYHELPERS_H_
#define _GEOMETRYHELPERS_H_

#include "DoubleRect.h"

class CGeometryHelper
{
public:
	static void EnforceAspectRatio(const CDoubleRect &oldRect, CDoubleRect &newRect, int submode, const CPoint &cursorLocation);
	static void AlignToAxis(CDoubleRect &rect, int submode);
};

#endif //_GEOMETRYHELPERS_H_