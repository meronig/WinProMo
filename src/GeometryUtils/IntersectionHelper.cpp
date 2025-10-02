#include "stdafx.h"
#include "IntersectionHelper.h"
#include "GeometryHelper.h"

static const CDoublePoint NO_INTERSECTION(-1.0, -1.0);

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

	return NO_INTERSECTION;
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
        return NO_INTERSECTION; // Avoid divide-by-zero


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
            return NO_INTERSECTION;
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

CDoublePoint CIntersectionHelper::SegmentIntersectsPolygon(const CDoublePoint& p1, const CDoublePoint& p2, const CDoubleRect& rect, const CObArray* points)
{
    if (!points || points->GetSize() < 3)
        return NO_INTERSECTION; // Not a valid polygon

    // Scale normalized vertices into polygon coordinates
    CArray<CDoublePoint, CDoublePoint&> scaled;
    scaled.SetSize(points->GetSize());

    for (int i = 0; i < points->GetSize(); ++i)
    {
        CDoublePoint* v = reinterpret_cast<CDoublePoint*>(points->GetAt(i));
        if (v)
        {
            scaled[i] = CGeometryHelper::ScaleVertex(*v, rect); // maps [0,1] -> rect coords
        }
        else
        {
            return NO_INTERSECTION; // safety check
        }
    }

    // Check segment against each polygon edge
    for (int i = 0; i < scaled.GetSize(); ++i)
    {
        const CDoublePoint& q1 = scaled[i];
        const CDoublePoint& q2 = scaled[(i + 1) % scaled.GetSize()]; // wrap to first

        CDoublePoint inter = SegmentIntersectsSegment(p1, p2, q1, q2);
        if (!(inter.x == -1.0 && inter.y == -1.0))
            return inter; // Found an intersection
    }

    return NO_INTERSECTION; // No edge intersection
}

CDoublePoint CIntersectionHelper::SegmentIntersectsSegment(const CDoublePoint& p1, const CDoublePoint& p2,
    const CDoublePoint& q1, const CDoublePoint& q2)
{
    auto cross = [](const CDoublePoint& a, const CDoublePoint& b, const CDoublePoint& c) {
        return (b.x - a.x) * (c.y - a.y) - (b.y - a.y) * (c.x - a.x);
        };

    double d1 = cross(p1, p2, q1);
    double d2 = cross(p1, p2, q2);
    double d3 = cross(q1, q2, p1);
    double d4 = cross(q1, q2, p2);

    if (((d1 > 0 && d2 < 0) || (d1 < 0 && d2 > 0)) &&
        ((d3 > 0 && d4 < 0) || (d3 < 0 && d4 > 0)))
    {
        // Compute intersection point
        double A1 = p2.y - p1.y;
        double B1 = p1.x - p2.x;
        double C1 = A1 * p1.x + B1 * p1.y;

        double A2 = q2.y - q1.y;
        double B2 = q1.x - q2.x;
        double C2 = A2 * q1.x + B2 * q1.y;

        double det = A1 * B2 - A2 * B1;
        if (det != 0.0)
        {
            double x = (B2 * C1 - B1 * C2) / det;
            double y = (A1 * C2 - A2 * C1) / det;
            return CDoublePoint(x, y);
        }
    }

    return NO_INTERSECTION;
}