#include "stdafx.h"
#include "IntersectionHelper.h"
#include "GeometryHelper.h"

static const CDoublePoint NO_INTERSECTION(-1.0, -1.0);
static const double EPS = 1e-6;

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
/* ============================================================
    Function :		CIntersectionHelper::SegmentIntersectsEllipse
    Description :	Determines the point on the border of the
                    ellipse that intersects with a (virtual)
                    line. Can be used to know where to trim a
                    connected edge.
    Access :		Public

    Return :		CDoublePoint				-	point
                                                    that lies
                                                    on the
                                                    border of
                                                    the
                                                    ellipse
    Parameters :	CDoublePoint& innerPoint	-	point
                                                    that lies
                                                    inside
                                                    the
                                                    ellipse
                    CDoublePoint& outerPoint	-	point
                                                    that lies
                                                    outside
                                                    the
                                                    ellipse
                    CDoubleRect& rect			-	perimeter
                                                    of the
                                                    rectangle
                                                    incribing
                                                    the ellipse

    ============================================================*/
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

    if (a < EPS || b < EPS)
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
    if (len > EPS) {
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

    //const double EPS = 1e-9;
    double discriminant = B * B - 4.0 * A * C;

    if (discriminant < 0.0) {
        discriminant = 0.0;
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
    if (norm > EPS) {
        ex /= norm;
        ey /= norm;
        xi = cx + ex * a;
        yi = cy + ey * b;
    }

    return CDoublePoint((xi), (yi));
}

CDoublePoint CIntersectionHelper::SegmentIntersectsPolygon(const CDoublePoint& p1, const CDoublePoint& p2, const CDoubleRect& rect, const CObArray* points)
/* ============================================================
    Function :		CIntersectionHelper::SegmentIntersectsPolygon
    Description :	Determines the point on the border of the
                    polygon that intersects with a (virtual)
                    line. Can be used to know where to trim a
                    connected edge.
    Access :		Public

    Return :		CDoublePoint				-	point
                                                    that lies
                                                    on the
                                                    border of
                                                    the
                                                    polygon
    Parameters :	CDoublePoint& innerPoint	-	point
                                                    that lies
                                                    inside
                                                    the
                                                    polygon
                    CDoublePoint& outerPoint	-	point
                                                    that lies
                                                    outside
                                                    the
                                                    polygon
                    CDoubleRect& rect			-	perimeter
                                                    of the
                                                    rectangle
                                                    incribing
                                                    the polygon
                    CObArray* points            -   array of
                                                    points
                                                    representing
                                                    the vertices
                                                    of the 
                                                    polygon

    ============================================================*/
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
            scaled[i] = CGeometryHelper::ScaleToRect(*v, rect); // maps [0,1] -> rect coords
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
/* ============================================================
    Function :		CIntersectionHelper::SegmentIntersectsSegment
    Description :	Determines the point in which two segments
                    intersect with each other.
    Access :		Public

    Return :		CDoublePoint		-	point where the
                                            two segments
                                            intersect
    Parameters :	CDoublePoint& p1	-	point where the
                                            first segment
                                            starts
                    CDoublePoint& p2	-	point where the
                                            first segment
                                            ends
                    CDoublePoint& q1	-	point where the
                                            second segment
                                            starts
                    CDoublePoint& q2	-	point where the
                                            second segment
                                            ends

    ============================================================*/
{
    double d1 = (p2.x - p1.x) * (q1.y - p1.y) - (p2.y - p1.y) * (q1.x - p1.x);
    double d2 = (p2.x - p1.x) * (q2.y - p1.y) - (p2.y - p1.y) * (q2.x - p1.x);
    double d3 = (q2.x - q1.x) * (p1.y - q1.y) - (q2.y - q1.y) * (p1.x - q1.x);
    double d4 = (q2.x - q1.x) * (p2.y - q1.y) - (q2.y - q1.y) * (p2.x - q1.x);


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
        if (fabs(det) > EPS)
        {
            double x = (B2 * C1 - B1 * C2) / det;
            double y = (A1 * C2 - A2 * C1) / det;
            CDoublePoint raw(x, y);
            return ProjectToSegment(raw, p1, p2); // snap to first segment
        }
    }

    return NO_INTERSECTION;

}

CDoublePoint CIntersectionHelper::ProjectToSegment(const CDoublePoint& raw, const CDoublePoint& p1, const CDoublePoint& p2)
/* ============================================================
    Function :		CIntersectionHelper::ProjectToSegment
    Description :	Projects a point to a segment.
    Access :		Public

    Return :		CDoublePoint		-	point lying on the
                                            segment
    Parameters :	CDoublePoint& raw	-	point to be 
                                            projected
                    CDoublePoint& p1	-	point where the
                                            segment starts
                    CDoublePoint& p2	-	point where the
                                            segment ends

    ============================================================*/
{
    // If raw is NO_INTERSECTION, forward it
    if (raw.x == NO_INTERSECTION.x && raw.y == NO_INTERSECTION.y)
        return NO_INTERSECTION;

    double dx = p2.x - p1.x;
    double dy = p2.y - p1.y;
    double len2 = dx * dx + dy * dy;

    // Degenerate edge -> return endpoint A
    if (len2 < EPS) {
        return CDoublePoint(p1.x, p1.y);
    }

    // Project raw onto AB: t = ((raw-A)·(B-A)) / |B-A|^2
    double t = ((raw.x - p1.x) * dx + (raw.y - p1.y) * dy) / len2;

    // Clamp t to [0,1]
    if (t < 0.0) t = 0.0;
    else if (t > 1.0) t = 1.0;

    // Reconstruct exact point on segment
    double x = p1.x + t * dx;
    double y = p1.y + t * dy;

    return CDoublePoint(x, y);
}
