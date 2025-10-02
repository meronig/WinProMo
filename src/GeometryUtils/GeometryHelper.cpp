/* ==========================================================================

	Copyright © 2025 Technical University of Denmark

	CGeometryHelper

	Author :		Giovanni Meroni

	Purpose :		"CGeometryHelper" is a collection of handy functions
					to manipulate shape geometry properties.

   ========================================================================*/
#include "stdafx.h"
#include "GeometryHelper.h"
#include "../DiagramEditor/DiagramEntity.h"

void CGeometryHelper::EnforceAspectRatio(const CDoubleRect& oldRect, CDoubleRect& newRect, int submode, const CPoint& cursorLocation)
/* ============================================================
	Function :		CGeometryHelper::EnforceAspectRatio
	Description :	Adjusts a rectangle so that it maintains 
					the same aspect ratio as a reference 
					rectangle.

	Parameters :	CDoubleRect& oldRect	-	rectangle 
												providing the 
												original ratio
					CDoubleRect& newRect	-	rectangle
												to be adjusted
					int submode				-	which edge or 
												corner is being 
												modified
					CPoint& cursorLocation	-	current cursor 
												position, used 
												to decide 
												whether 
												horizontal or 
												vertical 
												resizing has 
												priority

	Usage :			Use when resizing should preserve the 
					proportions of oldRect.

   ============================================================*/
{
	double deltaX = 0;
	double deltaY = 0;
	
	if (submode == DEHT_TOPMIDDLE) {
		deltaY = (oldRect.top - newRect.top) / oldRect.Ratio();
		newRect.left = oldRect.left - deltaY / 2;
		newRect.right = oldRect.right + deltaY / 2;
	}
	else if (submode == DEHT_BOTTOMMIDDLE) {
		deltaY = (newRect.bottom - oldRect.bottom) / oldRect.Ratio();
		newRect.left = oldRect.left - deltaY / 2;
		newRect.right = oldRect.right + deltaY / 2;
	}
	else if (submode == DEHT_LEFTMIDDLE) {
		deltaX = (oldRect.left - newRect.left) * oldRect.Ratio();
		newRect.top = oldRect.top - deltaX / 2;
		newRect.bottom = oldRect.bottom + deltaX / 2;
	}
	else if (submode == DEHT_RIGHTMIDDLE) {
		deltaX = (newRect.right - oldRect.right) * oldRect.Ratio();
		newRect.top = oldRect.top - deltaX / 2;
		newRect.bottom = oldRect.bottom + deltaX / 2;
	}
	else if (submode == DEHT_TOPLEFT) {
		deltaY = (oldRect.top - newRect.top) / oldRect.Ratio();
		deltaX = (oldRect.left - newRect.left) * oldRect.Ratio();
		if (fabs(oldRect.top - cursorLocation.y) < fabs(oldRect.left - cursorLocation.x)) {
			newRect.left = oldRect.left - deltaY;
		}
		else {
			newRect.top = oldRect.top - deltaX;
		}
	}
	else if (submode == DEHT_TOPRIGHT) {
		deltaY = (oldRect.top - newRect.top) / oldRect.Ratio();
		deltaX = (newRect.right - oldRect.right) * oldRect.Ratio();
		if (fabs(oldRect.top - cursorLocation.y) < fabs(oldRect.right - cursorLocation.x)) {
			newRect.right = oldRect.right + deltaY;
		}
		else {
			newRect.top = oldRect.top - deltaX;
		}
	}
	else if (submode == DEHT_BOTTOMLEFT) {
		deltaY = (newRect.bottom - oldRect.bottom) / oldRect.Ratio();
		deltaX = (oldRect.left - newRect.left) * oldRect.Ratio();
		if (fabs(oldRect.bottom - cursorLocation.y) < fabs(oldRect.left - cursorLocation.x)) {
			newRect.left = oldRect.left - deltaY;
		}
		else {
			newRect.bottom = oldRect.bottom + deltaX;
		}
	}
	else if (submode == DEHT_BOTTOMRIGHT) {
		deltaY = (newRect.bottom - oldRect.bottom) / oldRect.Ratio();
		deltaX = (newRect.right - oldRect.right) * oldRect.Ratio();
		if (fabs(oldRect.bottom - cursorLocation.y) < fabs(oldRect.right - cursorLocation.x)) {
			newRect.right = oldRect.right + deltaY;
		}
		else {
			newRect.bottom = oldRect.bottom + deltaX;
		}
	}

}

void CGeometryHelper::AlignToAxis(CDoubleRect& rect, int submode)
/* ============================================================
	Function :		CGeometryHelper::AlignToAxis
	Description :	Resizes a rectangle such that its inscribed
					segment aligns with the X-axis at an angle 
					that is a multiple of 45°.

	Parameters :	CDoubleRect& rect	-	the rectangle to
											be aligned
					int submode			-	which edge or 
											corner is being 
											modified
					
	Usage :			Use when resizing should snap the 
					rectangle's inscribed diagonal to 0°, 45°, 
					90°, etc.

   ============================================================*/
{

	const double dx = fabs(rect.right - rect.left);
	const double dy = fabs(rect.bottom - rect.top);

	// Are we dragging from bottom-right, or from top-left?
	const bool fromBottomRight = (submode == DEHT_BOTTOMRIGHT);

	if (dy / 2 > dx) {
		// Snap to vertical
		if (fromBottomRight) {
			rect.right = rect.left;
		}
		else {
			rect.left = rect.right;
		}
	}
	else if (dy < dx / 2) {
		// Snap to horizontal
		if (fromBottomRight) {
			rect.bottom = rect.top;
		}
		else {
			rect.top = rect.bottom;
		}
	}
	else {
		// Snap to 45° diagonal
		if (dy > dx) {
			// Vertical dominant
			if (rect.bottom > rect.top) {
				if (fromBottomRight)
					rect.bottom = rect.top + dx;
				else
					rect.top = rect.bottom - dx;
			}
			else {
				if (fromBottomRight)
					rect.bottom = rect.top - dx;
				else
					rect.top = rect.bottom + dx;
			}
		}
		else {
			// Horizontal dominant
			if (rect.right > rect.left) {
				if (fromBottomRight)
					rect.right = rect.left + dy;
				else
					rect.left = rect.right - dy;
			}
			else {
				if (fromBottomRight)
					rect.right = rect.left - dy;
				else
					rect.left = rect.right + dy;
			}
		}
	}
}

CDoublePoint CGeometryHelper::ScaleVertex(const CDoublePoint& v, const CDoubleRect& rect)
{
	return CDoublePoint(
		rect.left + v.x * rect.Width(),
		rect.top + v.y * rect.Height()
	);
}
