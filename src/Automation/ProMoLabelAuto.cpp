/* ==========================================================================

	Copyright © 2026 Technical University of Denmark

	CProMoLabelAuto

	Author :		Giovanni Meroni

	Purpose :		"CProMoLabelAuto" is an automation object that
					represents a label in a diagram. It provides methods
					to access the property whose value is displayed by the 
					label (if any), to copy, cut, delete, and duplicate the 
					label, to change its visual appearance (fill color, 
					fill pattern, etc.), and to move and resize it.

	Description :	"CProMoLabelAuto" provides the implementation of the
					methods and properties that are common to all labels.

   ========================================================================*/
#include "stdafx.h"
#include "ProMoLabelAuto.h"
#include "ProMoPropertyAuto.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CProMoLabelAuto

IMPLEMENT_DYNCREATE(CProMoLabelAuto, CProMoElementChildAuto)

CProMoLabelAuto::CProMoLabelAuto()
/* ============================================================
	Function :		CProMoLabelAuto::CProMoLabelAuto
	Description :	Constructor
	Access :		Public

	Return :		void
	Parameters :	none
	============================================================ */
{
}

CProMoLabel* CProMoLabelAuto::GetLabel()
/* ============================================================
	Function :		CProMoLabelAuto::GetLabel
	Description :	Returns the label represented by this automation
					object.
	Access :		Public

	Return :		CProMoLabel*	-	The label represented 
										by this automation object, 
										or NULL if the automation 
										object is not properly 
										initialized.
	Parameters :	none
	============================================================ */
{
	ThrowIfDetached();
	ThrowIfNoDiagramAutoObject();
	
	return dynamic_cast<CProMoLabel*>(m_pInternalObject);
}

CProMoElementAuto* CProMoLabelAuto::GetElementAutoObject() const
/* ============================================================
	Function :		CProMoLabelAuto::GetElementAutoObject
	Description :	Returns the element automation object.
					Overridden not to throw an exception if the
					element automation object is not set, because
					in this case the label is associated to
					the diagram, and not to an element.
	Access :		Public

	Return :		CProMoElementAuto*	-	The element automation
											object.
	Parameters :	none
   ============================================================*/
{
	ThrowIfNoDiagramAutoObject();
	return m_pElementAuto;
}

CProMoLabelAuto::~CProMoLabelAuto()
/* ============================================================
	Function :		CProMoLabelAuto::~CProMoLabelAuto
	Description :	Destructor
	Access :		Public

	Return :		void
	Parameters :	none
	============================================================ */
{
}

BEGIN_MESSAGE_MAP(CProMoLabelAuto, CProMoElementChildAuto)
	//{{AFX_MSG_MAP(CProMoLabelAuto)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

BEGIN_DISPATCH_MAP(CProMoLabelAuto, CProMoElementChildAuto)
	//{{AFX_DISPATCH_MAP(CProMoLabelAuto)
	DISP_PROPERTY_EX(CProMoLabelAuto, "FontName", GetFontName, SetFontName, VT_BSTR)
	DISP_PROPERTY_EX(CProMoLabelAuto, "FontSize", GetFontSize, SetFontSize, VT_I2)
	DISP_PROPERTY_EX(CProMoLabelAuto, "FontWeight", GetFontWeight, SetFontWeight, VT_I2)
	DISP_PROPERTY_EX(CProMoLabelAuto, "FontItalic", GetFontItalic, SetFontItalic, VT_BOOL)
	DISP_PROPERTY_EX(CProMoLabelAuto, "FontUnderline", GetFontUnderline, SetFontUnderline, VT_BOOL)
	DISP_PROPERTY_EX(CProMoLabelAuto, "FontStrikeOut", GetFontStrikeOut, SetFontStrikeOut, VT_BOOL)
	DISP_PROPERTY_EX(CProMoLabelAuto, "TextColor", GetTextColor, SetTextColor, VT_COLOR)
	DISP_PROPERTY_EX(CProMoLabelAuto, "BkColor", GetBkColor, SetBkColor, VT_COLOR)
	DISP_PROPERTY_EX(CProMoLabelAuto, "BkMode", GetBkMode, SetBkMode, VT_I4)
	DISP_PROPERTY_EX(CProMoLabelAuto, "TextMultiLine", GetTextMultiLine, SetTextMultiLine, VT_BOOL)
	DISP_PROPERTY_EX(CProMoLabelAuto, "TextHorizontalAlignment", GetTextHorizontalAlignment, SetTextHorizontalAlignment, VT_I4)
	DISP_PROPERTY_EX(CProMoLabelAuto, "TextVerticalAlignment", GetTextVerticalAlignment, SetTextVerticalAlignment, VT_I4)
	DISP_PROPERTY_EX(CProMoLabelAuto, "Text", GetText, SetText, VT_BSTR)
	DISP_PROPERTY_EX(CProMoLabelAuto, "ID", GetName, SetName, VT_BSTR)
	DISP_PROPERTY_EX(CProMoLabelAuto, "Top", GetTop, SetTop, VT_R8)
	DISP_PROPERTY_EX(CProMoLabelAuto, "Bottom", GetBottom, SetBottom, VT_R8)
	DISP_PROPERTY_EX(CProMoLabelAuto, "Left", GetLeft, SetLeft, VT_R8)
	DISP_PROPERTY_EX(CProMoLabelAuto, "Right", GetRight, SetRight, VT_R8)
	DISP_PROPERTY_EX(CProMoLabelAuto, "Width", GetWidth, SetWidth, VT_R8)
	DISP_PROPERTY_EX(CProMoLabelAuto, "Height", GetHeight, SetHeight, VT_R8)
	DISP_PROPERTY_EX(CProMoLabelAuto, "LockFlags", GetLockFlags, SetLockFlags, VT_I2)
	DISP_FUNCTION(CProMoLabelAuto, "Cut", Cut, VT_EMPTY, VTS_NONE)
	DISP_FUNCTION(CProMoLabelAuto, "Copy", Copy, VT_EMPTY, VTS_NONE)
	DISP_FUNCTION(CProMoLabelAuto, "Delete", Delete, VT_EMPTY, VTS_NONE)
	DISP_FUNCTION(CProMoLabelAuto, "Duplicate", Duplicate, VT_DISPATCH, VTS_NONE)
	DISP_FUNCTION(CProMoLabelAuto, "Property", Property, VT_DISPATCH, VTS_NONE)
	//Common to CProMoElementChildAuto
	DISP_FUNCTION(CProMoElementChildAuto, "Element", Element, VT_DISPATCH, VTS_NONE)
	//Common to CProMoDiagramChildAuto
	DISP_FUNCTION(CProMoDiagramChildAuto, "Diagram", Diagram, VT_DISPATCH, VTS_NONE)
	//Common to CProMoAppChildAuto
	DISP_FUNCTION(CProMoAppChildAuto, "Application", Application, VT_DISPATCH, VTS_NONE)
	//}}AFX_DISPATCH_MAP
END_DISPATCH_MAP()

// Note: we add support for IID_IProMoLabelAuto to support typesafe binding
//  from VBA.  This IID must match the GUID that is attached to the 
//  dispinterface in the .ODL file.

// {38EA3767-08C3-11F1-9744-000C2976A615}
static const IID IID_IProMoLabelAuto =
{ 0x38ea3767, 0x8c3, 0x11f1, { 0x97, 0x44, 0x0, 0xc, 0x29, 0x76, 0xa6, 0x15 } };

BEGIN_INTERFACE_MAP(CProMoLabelAuto, CProMoElementChildAuto)
	INTERFACE_PART(CProMoLabelAuto, IID_IProMoLabelAuto, Dispatch)
END_INTERFACE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CProMoLabelAuto message handlers

double CProMoLabelAuto::GetTop() 
/* ============================================================
	Function :		CProMoLabelAuto::GetTop
	Description :	Returns the top coordinate of this label.
	Access :		Public

	Return :		double	-	The top coordinate of this label.
	Parameters :	none
	============================================================ */
{
	if (GetLabel()) {
		return GetLabel()->GetTop();
	}

	return 0.0;
}

void CProMoLabelAuto::SetTop(double newValue) 
/* ============================================================
	Function :		CProMoBlockAuto::SetTop
	Description :	Sets the top coordinate of this label to the
					given value. The width and height of the label
					remain unchanged, so the bottom and right
					coordinates of the label are adjusted accordingly.
	Access :		Public

	Return :		void
	Parameters :	double newValue	-	the new top coordinate of
										this label.
   ============================================================*/
{
	if (GetLabel()) {
		GetContainer()->Snapshot();
		GetLabel()->SetRect(GetLabel()->GetLeft(), newValue, GetLabel()->GetRight(), GetLabel()->GetBottom() - GetLabel()->GetTop() + newValue);
		GetDiagramAutoObject()->NotifyChange();

	}

}

double CProMoLabelAuto::GetBottom() 
/* ============================================================
	Function :		CProMoLabelAuto::GetBottom
	Description :	Returns the bottom coordinate of this label.
	Access :		Public

	Return :		double	-	The bottom coordinate of this label.
	Parameters :	none
	============================================================ */
{
	if (GetLabel()) {
		return GetLabel()->GetBottom();
	}

	return 0.0;
}

void CProMoLabelAuto::SetBottom(double newValue)
/* ============================================================
	Function :		CProMoBlockAuto::SetBottom
	Description :	Sets the bottom coordinate of this label to the
					given value. The width and height of the label
					remain unchanged, so the top and right
					coordinates of the label are adjusted accordingly.
	Access :		Public

	Return :		void
	Parameters :	double newValue	-	the new bottom coordinate of
										this label.
   ============================================================*/
{
	if (GetLabel()) {
		GetContainer()->Snapshot();
		GetLabel()->SetRect(GetLabel()->GetLeft(), GetLabel()->GetTop() - GetLabel()->GetBottom() + newValue, GetLabel()->GetRight(), newValue);
		GetDiagramAutoObject()->NotifyChange();

	}

}

double CProMoLabelAuto::GetLeft() 
/* ============================================================
	Function :		CProMoLabelAuto::GetLeft
	Description :	Returns the left coordinate of this label.
	Access :		Public

	Return :		double	-	The left coordinate of this label.
	Parameters :	none
	============================================================ */
{
	if (GetLabel()) {
		return GetLabel()->GetLeft();
	}

	return 0.0;
}

void CProMoLabelAuto::SetLeft(double newValue) 
/* ============================================================
	Function :		CProMoBlockAuto::SetLeft
	Description :	Sets the left coordinate of this label to the
					given value. The width and height of the label
					remain unchanged, so the top and bottom
					coordinates of the label are adjusted accordingly.
	Access :		Public

	Return :		void
	Parameters :	double newValue	-	the new left coordinate of
										this label.
   ============================================================*/
{
	if (GetLabel()) {
		GetContainer()->Snapshot();
		GetLabel()->SetRect(newValue, GetLabel()->GetTop(), GetLabel()->GetRight() - GetLabel()->GetLeft() + newValue, GetLabel()->GetBottom());
		GetDiagramAutoObject()->NotifyChange();

	}

}

double CProMoLabelAuto::GetRight() 
/* ============================================================
	Function :		CProMoLabelAuto::GetRight
	Description :	Returns the right coordinate of this label.
	Access :		Public

	Return :		double	-	The right coordinate of this label.
	Parameters :	none
	============================================================ */
{
	if (GetLabel()) {
		return GetLabel()->GetRight();
	}

	return 0.0;
}

void CProMoLabelAuto::SetRight(double newValue) 
/* ============================================================
	Function :		CProMoBlockAuto::SetRight
	Description :	Sets the right coordinate of this label to the
					given value. The width and height of the label
					remain unchanged, so the top and bottom
					coordinates of the label are adjusted accordingly.
	Access :		Public

	Return :		void
	Parameters :	double newValue	-	the new right coordinate of
										this label.
   ============================================================*/
{
	if (GetLabel()) {
		GetContainer()->Snapshot();
		GetLabel()->SetRect(GetLabel()->GetLeft() - GetLabel()->GetRight() + newValue, GetLabel()->GetTop(), newValue, GetLabel()->GetBottom());
		GetDiagramAutoObject()->NotifyChange();

	}

}

double CProMoLabelAuto::GetWidth() 
/* ============================================================
	Function :		CProMoLabelAuto::GetWidth
	Description :	Returns the width of this label.
	Access :		Public

	Return :		double	-	The width of this label.
	Parameters :	none
	============================================================ */
{
	if (GetLabel()) {
		return GetLabel()->GetRect().Width();
	}

	return 0.0;
}

void CProMoLabelAuto::SetWidth(double newValue) 
/* ============================================================
	Function :		CProMoBlockAuto::SetWidth
	Description :	Sets the width of this label to the given value.
					The left coordinate of the label remains unchanged,
					so the right coordinate is adjusted accordingly.
	Access :		Public

	Return :		void
	Parameters :	double newValue	-	the new width of this label.
   ============================================================*/
{
	if (GetLabel()) {

		CDoubleRect oldRect(GetLabel()->GetLeft(), GetLabel()->GetTop(), GetLabel()->GetRight(), GetLabel()->GetBottom());
		CDoubleRect newRect(GetLabel()->GetLeft(), GetLabel()->GetTop(), GetLabel()->GetLeft() + newValue, GetLabel()->GetBottom());

		GetContainer()->Snapshot();
		GetLabel()->SetRect(newRect.ToCRect());
		GetLabel()->AutoResize();
		GetDiagramAutoObject()->NotifyChange();

	}

}

double CProMoLabelAuto::GetHeight() 
/* ============================================================
	Function :		CProMoLabelAuto::GetHeight
	Description :	Returns the height of this label.
	Access :		Public

	Return :		double	-	The height of this label.
	Parameters :	none
	============================================================ */
{
	if (GetLabel()) {
		return GetLabel()->GetRect().Height();
	}

	return 0.0;
}

void CProMoLabelAuto::SetHeight(double newValue) 
/* ============================================================
	Function :		CProMoLabelAuto::SetHeight
	Description :	Sets the height of this label to the given value.
					The top coordinate of the label remains unchanged,
					so the bottom coordinate is adjusted accordingly.
	Access :		Public

	Return :		void
	Parameters :	double newValue	-	the new height of this label.
   ============================================================*/
{
	if (GetLabel()) {
		CDoubleRect oldRect(GetLabel()->GetLeft(), GetLabel()->GetTop(), GetLabel()->GetRight(), GetLabel()->GetBottom());
		CDoubleRect newRect(GetLabel()->GetLeft(), GetLabel()->GetTop(), GetLabel()->GetRight(), GetLabel()->GetTop() + newValue);

		GetContainer()->Snapshot();
		GetLabel()->SetRect(newRect.ToCRect());
		GetLabel()->AutoResize();
		GetDiagramAutoObject()->NotifyChange();

	}

}

BSTR CProMoLabelAuto::GetFontName() 
/* ============================================================
	Function :		CProMoLabelAuto::GetFontName
	Description :	Returns the name of the font used to display the
					text of this label.
	Access :		Public
	Return :		BSTR	-	The name of the font used to display the
								text of this label.
	Parameters :	none
   ============================================================*/
{
	CString strResult;
	
	if (GetLabel()) {
		strResult = GetLabel()->GetFontName();
	}

	return strResult.AllocSysString();
}

void CProMoLabelAuto::SetFontName(LPCTSTR lpszNewValue) 
/* ============================================================
	Function :		CProMoLabelAuto::SetFontName
	Description :	Sets the name of the font used to display the
					text of this label to the given value.
	Access :		Public

	Return :		void
	Parameters :	LPCTSTR lpszNewValue	-	the new name of 
												the font used
												to display the text
												of this label.
   ============================================================*/
{
	if (GetLabel()) {
		if (!GetLabel()->IsLocked(LOCK_FONTNAME)) {
			GetContainer()->Snapshot();
			GetLabel()->SetFontName(lpszNewValue);
			GetDiagramAutoObject()->NotifyChange();
		}
	}

}

short CProMoLabelAuto::GetFontSize() 
/* ============================================================
	Function :		CProMoLabelAuto::GetFontSize
	Description :	Returns the size of the font used to display the
					text of this label.
	Access :		Public

	Return :		short	-	The size of the font used to display
								the text of this label.
	Parameters :	none
   ============================================================*/
{
	if (GetLabel()) {
		return GetLabel()->GetFontSize();
	}

	return 0;
}

void CProMoLabelAuto::SetFontSize(short nNewValue) 
/* ============================================================
	Function :		CProMoLabelAuto::SetFontSize
	Description :	Sets the size of the font used to display the
					text of this label to the given value.
	Access :		Public

	Return :		void
	Parameters :	short nNewValue	-	the new size of the font used
										to display the text of this label.
   ============================================================*/
{
	if (GetLabel()) {
		if (!GetLabel()->IsLocked(LOCK_FONTSIZE)) {
			GetContainer()->Snapshot();
			GetLabel()->SetFontSize(nNewValue);
			GetDiagramAutoObject()->NotifyChange();
		}
	}
}

short CProMoLabelAuto::GetFontWeight() 
/* ============================================================
	Function :		CProMoLabelAuto::GetFontWeight
	Description :	Returns the weight of the font used to display the
					text of this label.
	Access :		Public

	Return :		short	-	The weight of the font used to display
								the text of this label.
	Parameters :	none
   ============================================================*/
{
	if (GetLabel()) {
		return GetLabel()->GetFontWeight();
	}

	return 0;
}

void CProMoLabelAuto::SetFontWeight(short nNewValue) 
/* ============================================================
	Function :		CProMoLabelAuto::SetFontWeight
	Description :	Sets the weight of the font used to display the
					text of this label to the given value.
	Access :		Public

	Return :		void
	Parameters :	short nNewValue	-	the new weight of the font used
										to display the text of this label.
   ============================================================*/
{
	if (GetLabel()) {
		if (!GetLabel()->IsLocked(LOCK_FONTWEIGHT)) {
			GetContainer()->Snapshot();
			GetLabel()->SetFontWeight(nNewValue);
			GetDiagramAutoObject()->NotifyChange();
		}
	}
}

BOOL CProMoLabelAuto::GetFontItalic() 
/* ============================================================
	Function :		CProMoLabelAuto::GetFontItalic
	Description :	Returns whether the font used to display the text
					of this label is italic.
	Access :		Public

	Return :		BOOL	-	"TRUE" if the font used to display the
								text of this label is italic, "FALSE"
								otherwise.
	Parameters :	none
   ============================================================*/
{
	if (GetLabel()) {
		return GetLabel()->IsFontItalic();
	}

	return TRUE;
}

void CProMoLabelAuto::SetFontItalic(BOOL bNewValue) 
/* ============================================================
	Function :		CProMoLabelAuto::SetFontItalic
	Description :	Sets whether the font used to display the text
					of this label is italic to the given value.
	Access :		Public

	Return :		void
	Parameters :	BOOL bNewValue	-	"TRUE" if the font used 
										to display the text of 
										this label must be italic,
										"FALSE"	otherwise.
   ============================================================*/
{
	if (GetLabel()) {
		if (!GetLabel()->IsLocked(LOCK_FONTITALIC)) {
			GetContainer()->Snapshot();
			GetLabel()->SetFontItalic(bNewValue);
			GetDiagramAutoObject()->NotifyChange();
		}
	}
}

BOOL CProMoLabelAuto::GetFontUnderline() 
/* ============================================================
	Function :		CProMoLabelAuto::GetFontUnderline
	Description :	Returns whether the font used to display the text
					of this label is underlined.
	Access :		Public

	Return :		BOOL	-	"TRUE" if the font used to display the
								text of this label is underlined, "FALSE"
								otherwise.
	Parameters :	none
   ============================================================*/
{
	if (GetLabel()) {
		return GetLabel()->IsFontUnderline();
	}

	return TRUE;
}

void CProMoLabelAuto::SetFontUnderline(BOOL bNewValue) 
/* ============================================================
	Function :		CProMoLabelAuto::SetFontUnderline
	Description :	Sets whether the font used to display the text
					of this label is underlined to the given value.
	Access :		Public

	Return :		void
	Parameters :	BOOL bNewValue	-	"TRUE" if the font used 
										to display the text of 
										this label must be 
										underlined, "FALSE"
										otherwise.
   ============================================================*/
{
	if (GetLabel()) {
		if (!GetLabel()->IsLocked(LOCK_FONTUNDERLINE)) {
			GetContainer()->Snapshot();
			GetLabel()->SetFontUnderline(bNewValue);
			GetDiagramAutoObject()->NotifyChange();
		}
	}
}

BOOL CProMoLabelAuto::GetFontStrikeOut() 
/* ============================================================
	Function :		CProMoLabelAuto::GetFontStrikeOut
	Description :	Returns whether the font used to display the text
					of this label is strikeout.
	Access :		Public

	Return :		BOOL	-	"TRUE" if the font used to display the
								text of this label is strikeout, "FALSE"
								otherwise.
	Parameters :	none
   ============================================================*/
{
	if (GetLabel()) {
		return GetLabel()->IsFontStrikeOut();
	}

	return TRUE;
}

void CProMoLabelAuto::SetFontStrikeOut(BOOL bNewValue) 
/* ============================================================
	Function :		CProMoLabelAuto::SetFontStrikeOut
	Description :	Sets whether the font used to display the text
					of this label is strikeout to the given value.
	Access :		Public

	Return :		void
	Parameters :	BOOL bNewValue	-	"TRUE" if the font used 
										to display the text of 
										this label must be 
										strikeout, "FALSE"
										otherwise.
   ============================================================*/
{
	if (GetLabel()) {
		if (!GetLabel()->IsLocked(LOCK_FONTSTRIKEOUT)) {
			GetContainer()->Snapshot();
			GetLabel()->SetFontStrikeOut(bNewValue);
			GetDiagramAutoObject()->NotifyChange();
		}
	}
}

OLE_COLOR CProMoLabelAuto::GetTextColor() 
/* ============================================================
	Function :		CProMoLabelAuto::GetTextColor
	Description :	Returns the color used to display the text of this
					label.
	Access :		Public

	Return :		OLE_COLOR	-	The color used to display the text of
									this label.
	Parameters :	none
   ============================================================*/
{
	if (GetLabel()) {
		COLORREF color = GetLabel()->GetTextColor();
		return RGB(GetRValue(color), GetGValue(color), GetBValue(color));
	}

	return RGB(0,0,0);
}

void CProMoLabelAuto::SetTextColor(OLE_COLOR nNewValue) 
/* ============================================================
	Function :		CProMoLabelAuto::SetTextColor
	Description :	Sets the color used to display the text of this
					label to the given value.
	Access :		Public

	Return :		void
	Parameters :	OLE_COLOR nNewValue	-	the new color used 
											to display the text of
											this label.
   ============================================================*/
{
	COLORREF color;
	HRESULT hr = OleTranslateColor(nNewValue, NULL, &color);
	if (FAILED(hr))
		AfxThrowOleException(hr);
	if (GetLabel()) {
		if (!GetLabel()->IsLocked(LOCK_TEXTCOLOR)) {
			GetContainer()->Snapshot();
			GetLabel()->SetTextColor(color);
			GetDiagramAutoObject()->NotifyChange();
		}
	}
}

OLE_COLOR CProMoLabelAuto::GetBkColor() 
/* ============================================================
	Function :		CProMoLabelAuto::GetBkColor
	Description :	Returns the background color of this label.
	Access :		Public

	Return :		OLE_COLOR	-	The background color of this label.
	Parameters :	none
   ============================================================*/
{
	if (GetLabel()) {
		COLORREF color = GetLabel()->GetBkColor();
		return RGB(GetRValue(color), GetGValue(color), GetBValue(color));
	}

	return RGB(0,0,0);
}

void CProMoLabelAuto::SetBkColor(OLE_COLOR nNewValue) 
/* ============================================================
	Function :		CProMoLabelAuto::SetBkColor
	Description :	Sets the background color of this label to the given
					value.
	Access :		Public

	Return :		void
	Parameters :	OLE_COLOR nNewValue	-	the new background color of
											this label.
   ============================================================*/
{
	COLORREF color;
	HRESULT hr = OleTranslateColor(nNewValue, NULL, &color);
	if (FAILED(hr))
		AfxThrowOleException(hr);
	if (GetLabel()) {
		if (!GetLabel()->IsLocked(LOCK_BKCOLOR)) {
			GetContainer()->Snapshot();
			GetLabel()->SetBkColor(color);
			GetDiagramAutoObject()->NotifyChange();
		}
	}
}

long CProMoLabelAuto::GetBkMode() 
/* ============================================================
	Function :		CProMoLabelAuto::GetBkMode
	Description :	Returns the background mode of this label.
	Access :		Public

	Return :		long	-	The background mode of this label.
								Possible values are:
								"1" (transparent background) and
								"2" (opaque background).
	Parameters :	none
   ============================================================*/
{
	if (GetLabel()) {
		return GetLabel()->GetBkMode();
	}

	return 0;
}

void CProMoLabelAuto::SetBkMode(long nNewValue) 
/* ============================================================
	Function :		CProMoLabelAuto::SetBkMode
	Description :	Sets the background mode of this label to the given
					value.
	Access :		Public

	Return :		void
	Parameters :	long nNewValue	-	the new background mode of this
										label. 
   ============================================================*/
{
	if (GetLabel()) {
		if (!GetLabel()->IsLocked(LOCK_BKMODE)) {
			GetContainer()->Snapshot();
			GetLabel()->SetBkMode(nNewValue);
			GetDiagramAutoObject()->NotifyChange();
		}
	}
}

long CProMoLabelAuto::GetTextHorizontalAlignment() 
/* ============================================================
	Function :		CProMoLabelAuto::GetTextHorizontalAlignment
	Description :	Returns the horizontal alignment of the text of this
					label.
	Access :		Public

	Return :		long	-	The horizontal alignment of the 
								text of this label. 
	Parameters :	none
   ============================================================*/
{
	if (GetLabel()) {
		return GetLabel()->GetTextHorizontalAlignment();
	}

	return 0;
}

void CProMoLabelAuto::SetTextHorizontalAlignment(long nNewValue) 
/* ============================================================
	Function :		CProMoLabelAuto::SetTextHorizontalAlignment
	Description :	Sets the horizontal alignment of the text of this
					label to the given value.
	Access :		Public
	Return :		void
	Parameters :	long nNewValue	-	the new horizontal alignment of the
										text of this label. 
   ============================================================*/
{
	if (GetLabel()) {
		if (!GetLabel()->IsLocked(LOCK_ALIGNMENT)) {
			GetContainer()->Snapshot();
			GetLabel()->SetTextHorizontalAlignment(nNewValue);
			GetDiagramAutoObject()->NotifyChange();
		}
	}
}

long CProMoLabelAuto::GetTextVerticalAlignment() 
/* ============================================================
	Function :		CProMoLabelAuto::GetTextVerticalAlignment
	Description :	Returns the vertical alignment of the text of this
					label.
	Access :		Public
	Return :		long	-	The vertical alignment of the text 
								of this	label. 
	Parameters :	none
   ============================================================*/
{
	if (GetLabel()) {
		return GetLabel()->GetTextVerticalAlignment();
	}

	return 0;
}

void CProMoLabelAuto::SetTextVerticalAlignment(long nNewValue) 
/* ============================================================
	Function :		CProMoLabelAuto::SetTextVerticalAlignment
	Description :	Sets the vertical alignment of the text of this
					label to the given value.
	Access :		Public

	Return :		void
	Parameters :	long nNewValue	-	the new vertical alignment of the
										text of this label. 
   ============================================================*/
{
	if (GetLabel()) {
		if (!GetLabel()->IsLocked(LOCK_ALIGNMENT)) {
			GetContainer()->Snapshot();
			GetLabel()->SetTextVerticalAlignment(nNewValue);
			GetDiagramAutoObject()->NotifyChange();
		}
	}
}

void CProMoLabelAuto::Cut() 
/* ============================================================
	Function :		CProMoLabelAuto::Cut
	Description :	Cuts this label. The label is removed from the
					diagram and copied to the clipboard.
	Access :		Public

	Return :		void
	Parameters :	none
   ============================================================*/
{
	if (GetLabel()) {
		GetContainer()->Snapshot();
		Copy();
		GetDiagramAutoObject()->NotifyChange();
	}
}

void CProMoLabelAuto::Copy() 
/* ============================================================
	Function :		CProMoLabelAuto::Copy
	Description :	Copies this label to the clipboard.
	Access :		Public

	Return :		void
	Parameters :	none
   ============================================================*/
{
	if (GetLabel()) {
		GetContainer()->UnselectAll();
		GetLabel()->Select(TRUE);
		GetContainer()->CopyAllSelected();
	}
}

void CProMoLabelAuto::Delete() 
/* ============================================================
	Function :		CProMoLabelAuto::Delete
	Description :	Deletes this label from the diagram.
	Access :		Public

	Return :		void
	Parameters :	none
   ============================================================*/
{
	if (GetLabel() && GetContainer()) {
		GetContainer()->Snapshot();
		GetContainer()->Remove(GetLabel());
		GetDiagramAutoObject()->NotifyChange();
	}

}

LPDISPATCH CProMoLabelAuto::Duplicate() 
/* ============================================================
	Function :		CProMoLabelAuto::Duplicate
	Description :	Duplicates this label. A new label is created as a
					copy of this label and added to the same container
					as this label.
	Access :		Public

	Return :		LPDISPATCH	-	The automation object representing the
									newly created label.
	Parameters :	none
   ============================================================*/
{
	if (GetLabel()) {

		GetContainer()->Snapshot();
		IProMoEntity* newView = dynamic_cast<IProMoEntity*>(GetContainer()->CloneEntity(GetLabel()));
		GetDiagramAutoObject()->NotifyChange();

		if (newView) {
			CProMoLabelAuto* pLabelAuto = dynamic_cast<CProMoLabelAuto*>(newView->GetAutomationObject());
			if (pLabelAuto) {
				pLabelAuto->SetDiagramAutoObject(GetDiagramAutoObject());
				return pLabelAuto->GetIDispatch(TRUE);
			}
		}
	}

	return NULL;
}

LPDISPATCH CProMoLabelAuto::Property() 
/* ============================================================
	Function :		CProMoLabelAuto::Property
	Description :	Returns the property whose value is displayed by this
					label, if any.
	Access :		Public

	Return :		LPDISPATCH	-	The automation object representing the
									property whose value is displayed by
									this label, or NULL if this label is
									not associated to any property.
	Parameters :	none
   ============================================================*/
{
	if (GetLabel()) {
		CProMoProperty* pProperty = GetLabel()->GetProperty();
		if (pProperty) {
			CProMoPropertyAuto* pPropertyAuto = dynamic_cast<CProMoPropertyAuto*>(pProperty->GetAutomationObject());
			if (pPropertyAuto) {
				pPropertyAuto->SetElementAutoObject(GetElementAutoObject());
				return pPropertyAuto->GetIDispatch(TRUE);
			}
		}
	}

	return NULL;
}

BSTR CProMoLabelAuto::GetText()
/* ============================================================
	Function :		CProMoLabelAuto::GetText
	Description :	Returns the text displayed by this label.
	Access :		Public

	Return :		BSTR	-	The text of this label.
	Parameters :	none
   ============================================================*/
{
	CString strResult;

	if (GetLabel()) {
		strResult = GetLabel()->GetTitle();
	}

	return strResult.AllocSysString();
}

void CProMoLabelAuto::SetText(LPCTSTR lpszNewValue)
/* ============================================================
	Function :		CProMoLabelAuto::SetText
	Description :	Sets the text displayed by this label to the given
					value.
	Access :		Public

	Return :		void
	Parameters :	LPCTSTR lpszNewValue	-	the new text of this label.
   ============================================================*/
{
	if (GetLabel()) {
		if (!GetLabel()->GetModel()) {
			// Label is not associated to any property, so text can be changed
			GetContainer()->Snapshot();
			GetLabel()->SetTitle(lpszNewValue);
			GetDiagramAutoObject()->NotifyChange();
		}
		else {
			// Label is associated to a property, so text is read-only
			SetNotSupported();
		}
	}
}

BSTR CProMoLabelAuto::GetName() 
/* ============================================================
	Function :		CProMoLabelAuto::GetName
	Description :	Returns the name of this label.
	Access :		Public

	Return :		BSTR	-	The name of this label.
	Parameters :	none
   ============================================================*/
{
	CString strResult;
	
	if (GetLabel()) {
		strResult = GetLabel()->GetName();
	}

	return strResult.AllocSysString();
}

void CProMoLabelAuto::SetName(LPCTSTR lpszNewValue) 
/* ============================================================
	Function :		CProMoLabelAuto::SetName
	Description :	Sets the name of this label to the given value.
					This property is read-only, so this function simply
					raises an exception.
	Access :		Public

	Return :		void
	Parameters :	LPCTSTR lpszNewValue	-	the new name of this label.
   ============================================================*/
{
	SetNotSupported();
}

BOOL CProMoLabelAuto::GetTextMultiLine() 
/* ============================================================
	Function :		CProMoLabelAuto::GetTextMultiLine
	Description :	Check if the text of this label is multiline
	Access :		Public

	Return :		BOOL	-	"TRUE" if the text of this label
								is multiline, "FALSE" otherwise
	Parameters :	none
   ============================================================ */
{
	if (GetLabel()) {
		return GetLabel()->IsTextMultiline();
	}

	return FALSE;
}

void CProMoLabelAuto::SetTextMultiLine(BOOL bNewValue) 
/* ============================================================
	Function :		CProMoLabelAuto::SetTextMultiLine
	Description :	Set the text of this label as multiline or
					single line
	Access :		Public

	Return :		void
	Parameters :	BOOL bNewValue	-	"TRUE" if the text of this
										label must be multiline,
										"FALSE" otherwise
   ============================================================ */
{
	if (GetLabel()) {
		if (!GetLabel()->IsLocked(LOCK_ALIGNMENT)) {
			GetContainer()->Snapshot();
			GetLabel()->SetTextMultiline(bNewValue);
			GetDiagramAutoObject()->NotifyChange();
		}
	}
}

short CProMoLabelAuto::GetLockFlags()
/* ============================================================
	Function :		CProMoLabelAuto::GetLockFlags
	Description :	Get the lock flags for this label
	Access :		Public

	Return :		short	-	the lock flags for this label
	Parameters :	none
   ============================================================ */
{
	if (GetLabel()) {
		return GetLabel()->GetLock();
	}

	return 0;
}

void CProMoLabelAuto::SetLockFlags(short nNewValue)
/* ============================================================
	Function :		CProMoLabelAuto::SetLockFlags
	Description :	Set the lock flags for this label. This
					property is read-only, so this function simply
					raises an exception.
	Access :		Public
	Return :		void
	Parameters :	short nNewValue	-	the new lock flags for this
										label
   ============================================================ */
{
	SetNotSupported();
}
