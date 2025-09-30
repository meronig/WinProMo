#include "stdafx.h"
#include "IntersectionHelper.h"

CDoublePoint CIntersectionHelper::SegmentIntersectsRect(const CDoublePoint& innerPoint, const CDoublePoint& outerPoint, const CDoubleRect& rect)
/* ============================================================
	Function :		CIntersectionHelper::SegmentIntersectsRect
	Description :	Determines the point on the border of the
					rectangle that intersects with a (virtual)
					line. Can be used to know where to trim a
					connected edge.
	Access :		Public

	Return :		CDoublePoint				-	point 
													that lies
													on the 
													border of
													the 
													rectangle
	Parameters :	CDoublePoint& innerPoint	-	point 
													that lies
													inside 
													the 
													rectangle
					CDoublePoint& outerPoint	-	point 
													that lies
													outside 
													the 
													rectangle
					CDoubleRect& rect			-	perimeter
													of the
													rectangle

============================================================*/
{
	
	double t = 0;

	if (innerPoint.x >= rect.left && innerPoint.x <= rect.right && innerPoint.y >= rect.top && innerPoint.y <= rect.bottom) {
		if (!(outerPoint.x >= rect.left && outerPoint.x <= rect.right && outerPoint.y >= rect.top && outerPoint.y <= rect.bottom)) {

			if (outerPoint.x == innerPoint.x) {
				t = max((rect.top - innerPoint.y) / (outerPoint.y - innerPoint.y), (rect.bottom - innerPoint.y) / (outerPoint.y - innerPoint.y));
			}
			else {
				if (outerPoint.y == innerPoint.y) {
					t = max((rect.left - innerPoint.x) / (outerPoint.x - innerPoint.x), (rect.right - innerPoint.x) / (outerPoint.x - innerPoint.x));
				}
				else {
					if (outerPoint.x > innerPoint.x) {
						if (outerPoint.y > innerPoint.y) {
							t = min((rect.right - innerPoint.x) / (outerPoint.x - innerPoint.x), (rect.bottom - innerPoint.y) / (outerPoint.y - innerPoint.y));
						}
						else {
							t = min((rect.right - innerPoint.x) / (outerPoint.x - innerPoint.x), (rect.top - innerPoint.y) / (outerPoint.y - innerPoint.y));
						}
					}
					else {
						if (outerPoint.y > innerPoint.y) {
							t = min((rect.left - innerPoint.x) / (outerPoint.x - innerPoint.x), (rect.bottom - innerPoint.y) / (outerPoint.y - innerPoint.y));
						}
						else {
							t = min((rect.left - innerPoint.x) / (outerPoint.x - innerPoint.x), (rect.top - innerPoint.y) / (outerPoint.y - innerPoint.y));
						}
					}
				}
			}

			CDoublePoint result;
			result.x = (t * outerPoint.x + (1 - t) * innerPoint.x);
			result.y = (t * outerPoint.y + (1 - t) * innerPoint.y);

			/* uncomment for debugging */
			/*msg.Format(_T("intersection: (%d, %d)"), result.x, result.y);
			AfxMessageBox(msg);*/

			return result;
		}
	}

	return CDoublePoint(-1, -1);
}

CDoublePoint CIntersectionHelper::SegmentIntersectsEllipse(const CDoublePoint& innerPoint, const CDoublePoint& outerPoint, const CDoubleRect& rect)
{
    double ipx = innerPoint.x;
    double ipy = innerPoint.y;
    double opx = outerPoint.x;
    double opy = outerPoint.y;

    // 1. Normalize ellipse bounds
    double left = min(rect.left, rect.right);
    double right = max(rect.left, rect.right);
    double top = min(rect.top, rect.bottom);
    double bottom = max(rect.top, rect.bottom);

    // 2. Center and radii
    double cx = (left + right) / 2.0;
    double cy = (top + bottom) / 2.0;
    double a = (right - left) / 2.0;
    double b = (bottom - top) / 2.0;

    if (a < 1e-6 || b < 1e-6)
        return CPoint(-1, -1); // Avoid divide-by-zero


    // 3. Translate points to ellipse-centered coordinate system
    double x1 = (opx - cx) / a;
    double y1 = (opy - cy) / b;
    double x2 = (ipx - cx) / a;
    double y2 = (ipy - cy) / b;

    // Parametrize the segment: P(t) = (x1, y1) + t * (dx, dy)
    double dx = x2 - x1;
    double dy = y2 - y1;

    const double pushOut = 1.5;
    double len = sqrt(dx * dx + dy * dy);
    if (len > 1e-6) {
        double scale = (len + pushOut / max(a, b)) / len;
        x2 = x1 + dx * scale;
        y2 = y1 + dy * scale;
        dx = x2 - x1;
        dy = y2 - y1;
    }

    // 4. Solve for intersection with unit circle (x² + y² = 1)
    double A = dx * dx + dy * dy;
    double B = 2.0 * (x1 * dx + y1 * dy);
    double C = x1 * x1 + y1 * y1 - 1.0;

    const double EPS = 1e-9;
    double discriminant = B * B - 4.0 * A * C;

    if (discriminant < 0.0) {
        if (discriminant > -EPS) {
            // Treat as tangent
            discriminant = 0.0;
        }
        else {
            // Truly no intersection
            return CDoublePoint(-1, -1);
        }
    }

    double sqrtD = sqrt(discriminant);
    double t1 = (-B - sqrtD) / (2.0 * A);
    double t2 = (-B + sqrtD) / (2.0 * A);

    // 5. Select the valid t  [0, 1] closest to innerPoint
    double t = (fabs(t1) < fabs(t2)) ? t1 : t2;
    t = max(0.0, min(1.0, t));  // Clamp to segment range

    // 5. Transform back to original space
    double xi = (x1 + t * dx) * a + cx;
    double yi = (y1 + t * dy) * b + cy;

    // Optional: snap exactly on ellipse (helps long-term stability)
    double ex = (xi - cx) / a;
    double ey = (yi - cy) / b;
    double norm = sqrt(ex * ex + ey * ey);
    if (norm > 1e-6) {
        ex /= norm;
        ey /= norm;
        xi = cx + ex * a;
        yi = cy + ey * b;
    }

    return CDoublePoint((xi + 0.5), (yi + 0.5));
}
