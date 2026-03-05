#include "stdafx.h"
#include "ProMoLabel.h"
#include "ProMoNameFactory.h"
#include "../DiagramEditor/Tokenizer.h"
#include "../FileUtils/FileParser.h"
#include "../resource.h"
#include "ProMoBlockModel.h"
#include "ProMoEdgeModel.h"
#include "../Automation/ProMoLabelAuto.h"

CProMoLabel::CProMoLabel()
/* ============================================================
	Function :		CProMoLabel::CProMoLabel
	Description :	constructor

	Return :		void
	Parameters :	none

	Usage :

   ============================================================*/
{
	m_model = NULL;
	
	m_lockFlags = 0;

	m_bkColor = CLR_NONE;

	m_fontName = CString("Courier New");
	m_fontSize = 12;
	m_fontWeight = FW_NORMAL;
	m_fontItalic = FALSE;
	m_fontUnderline = FALSE;
	m_fontStrikeOut = FALSE;
	m_textAlignment = DT_NOPREFIX | DT_SINGLELINE | DT_VCENTER | DT_CENTER;
	m_textColor = RGB(0, 0, 0);
	m_bkMode = TRANSPARENT;
	
	m_noOffset = FALSE;
	m_labelAnchorPoint = DEHT_CENTER;
	m_viewAnchorPoint = DEHT_CENTER;
	m_anchorView = VIEW_FIRST;

	m_offset = CPoint(0, 0);
	m_fitTitle = FALSE;
	m_fitView = FALSE;
	m_titleRect = CRect(0, 0, 0, 0); 

	m_rotation = 0;
	m_topMargin = 0;
	m_leftMargin = 0;
	m_bottomMargin = 0;
	m_rightMargin = 0;
	
	m_visible = TRUE;

	m_autoObject = NULL;

	SetConstraints(CSize(5, 5), CSize(-1, -1));
	SetType(_T("promo_label"));

	SetZoom(1.0);

	CVariantWrapper wrapper;
	m_titleProperty = new CProMoProperty(_T("Title"), PROPTYPE_STRING, wrapper, FALSE, TRUE, TRUE, this);

	CString title;
	BOOL result;
	result = title.LoadString(IDS_PROMO_NODE);
	if (result) {
		SetTitle(title);
	}
	
	SetName(CProMoNameFactory::GetID());	
}

CProMoLabel::~CProMoLabel()
/* ============================================================
	Function :		CProMoLabel::~CProMoLabel
	Description :	destructor

	Return :		void
	Parameters :	none

	Usage :

   ============================================================*/
{
	if (m_model) {
		m_model->UnlinkLabel(this);
	}
	delete m_titleProperty;

	ReleaseAutomationObject();
}

CDiagramEntity* CProMoLabel::Clone()
/* ============================================================
	Function :		CProMoLabel::Clone
	Description :	Clone this object to a new object.

	Return :		CDiagramEntity*	-	The new object.
	Parameters :	none

	Usage :			Call to create a clone of the object. The
					caller will have to delete the object.

   ============================================================*/
{

	CProMoLabel* obj = new CProMoLabel;
	obj->Copy(this);
	obj->SetName(CProMoNameFactory::GetID());
	return obj;

}

void CProMoLabel::Copy(CDiagramEntity* obj)
/* ============================================================
	Function :		CProMoLabel::Copy
	Description :	Copy the information in "obj" to this object.
	Access :		Public

	Return :		void
	Parameters :	CDiagramEntity* obj	-	The object to copy
												from.

	Usage :			Copies basic information. from "obj" to this.
					"GetType" can be used to check for the correct
					object type in overridden versions.
   ============================================================*/
{
	CDiagramEntity::Copy(obj);
	CProMoLabel* objView = dynamic_cast<CProMoLabel*>(obj);
	if (objView) {
		m_property = objView->m_property;
		m_fontName = objView->m_fontName;
		m_fontSize = objView->m_fontSize;
		m_fontWeight = objView->m_fontWeight;
		m_fontItalic = objView->m_fontItalic;
		m_fontUnderline = objView->m_fontUnderline;
		m_fontStrikeOut = objView->m_fontStrikeOut;
		m_textColor = objView->m_textColor;
		m_bkColor = objView->m_bkColor;
		m_bkMode = objView->m_bkMode;
		m_textAlignment = objView->m_textAlignment;
		m_labelAnchorPoint = objView->m_labelAnchorPoint;
		m_viewAnchorPoint = objView->m_viewAnchorPoint;
		m_anchorView = objView->m_anchorView;
		m_offset = objView->m_offset;

		m_rotation = objView->m_rotation;
		m_topMargin = objView->m_topMargin;
		m_leftMargin = objView->m_leftMargin;
		m_bottomMargin = objView->m_bottomMargin;
		m_rightMargin = objView->m_rightMargin;

		/*Lock flags are deliberately not copied, as they depend
		on the attached model*/

		m_fitTitle = objView->m_fitTitle;
		m_titleRect = objView->m_titleRect;
	}
}

void CProMoLabel::Draw(CDC* dc, CRect rect)
/* ============================================================
	Function :		CProMoLabel::Draw
	Description :	Draws the object.

	Return :		void
	Parameters :	CDC* dc		-	The CDC to draw to.
					CRect rect	-	The real rectangle of the
									object.

	Usage :			The function should clean up all selected
					objects. Note that the CDC is a memory CDC,
					so creating a memory CDC in this function
					will probably not speed up the function.

   ============================================================*/
{
	if (m_visible) {

		BOOL rasterizeText = FALSE;

		if (dc)
		{
			if (!dc->IsPrinting() && !dc->IsKindOf(RUNTIME_CLASS(CMetaFileDC)))  // printers always use vector fonts
			{
				int tech = dc->GetDeviceCaps(TECHNOLOGY);
				if (tech == DT_RASDISPLAY && GetZoom() != 1.0)
					rasterizeText = TRUE;
			}
		}

		int fontHeight = -round(m_fontSize * GetZoom());

		CFont font;
		font.CreateFont(fontHeight, 0, 0, 0, m_fontWeight, m_fontItalic, m_fontUnderline, m_fontStrikeOut, 0, 0, 0, 0, 0, m_fontName);

		CFont* pOldFont = dc->SelectObject(&font);
		COLORREF oldTextColor = dc->SetTextColor(m_textColor);
		COLORREF oldBkColor = dc->SetBkColor(m_bkColor);
		int oldBkMode = dc->SetBkMode(m_bkMode);

		CDoubleRect actualRect = rect;
		actualRect.top += m_topMargin * GetZoom();
		actualRect.left += m_leftMargin * GetZoom();
		actualRect.bottom -= m_bottomMargin * GetZoom();
		actualRect.right -= m_rightMargin * GetZoom();

		if (!rasterizeText)
		{
			if (m_textAlignment & DT_WORDBREAK) {
				unsigned int lineCount = 0;
				DrawMultiLineText(dc, actualRect, lineCount, TRUE);
				DrawMultiLineText(dc, actualRect, lineCount, FALSE);
			}
			else {
				double hPos = actualRect.left;
				double vPos = actualRect.top;
				
				if (m_textAlignment & DT_CENTER)
					hPos += (actualRect.Width() - m_titleRect.Width() * GetZoom()) / 2;
				if (m_textAlignment & DT_RIGHT)
					hPos += (actualRect.Width() - m_titleRect.Width() * GetZoom());
				if (m_textAlignment & DT_VCENTER)
					vPos += (actualRect.Height() - m_titleRect.Height() * GetZoom()) / 2;
				if (m_textAlignment & DT_BOTTOM)
					vPos += (actualRect.Height() - m_titleRect.Height() * GetZoom());
				
				dc->ExtTextOut((int)hPos, (int)vPos, (m_bkMode & OPAQUE) ? ETO_OPAQUE : 0, NULL, GetTitle(), NULL);
			}

		}
		else {
			CDC memDC, maskDC, nullDC;
			memDC.CreateCompatibleDC(dc);
			maskDC.CreateCompatibleDC(dc);
			nullDC.CreateCompatibleDC(NULL);

			CRect textBounds(0, 0, 0, 0);
			textBounds = ComputeTextRect(&nullDC, GetZoom()).ToCRect();

			CRect bmpRect = rect;
			bmpRect.OffsetRect(-rect.left, -rect.top);

			if (rect.Width() < textBounds.Width()) {
				bmpRect.right = bmpRect.left + textBounds.Width();
			}
			if (rect.Height() < textBounds.Height()) {
				bmpRect.bottom = bmpRect.top + textBounds.Height();
			}

			CDoubleRect fontRect = bmpRect;
			fontRect.top += m_topMargin * GetZoom();
			fontRect.left += m_leftMargin * GetZoom();
			fontRect.bottom -= m_bottomMargin * GetZoom();
			fontRect.right -= m_rightMargin * GetZoom();

			//prepare maskDC
			CBitmap maskBmp;
			maskBmp.CreateCompatibleBitmap(dc, bmpRect.Width(), bmpRect.Height());
			CBitmap* pOldMaskBmp = maskDC.SelectObject(&maskBmp);

			// Fill background
			CBrush bgBrush(RGB(255, 255, 255));
			maskDC.SetBkMode(OPAQUE);
			if (m_bkMode & TRANSPARENT) {
				maskDC.SetBkColor(RGB(255, 255, 255));
			}
			else {
				maskDC.SetBkColor(RGB(0, 0, 0));
			}
			maskDC.FillRect(&CRect(0, 0, bmpRect.Width(), bmpRect.Height()), &bgBrush);
			maskDC.SetTextColor(RGB(0, 0, 0));
			maskDC.SelectObject(&font);
			
			//prepare memDC
			CBitmap bmp;
			bmp.CreateCompatibleBitmap(dc, bmpRect.Width(), bmpRect.Height());
			CBitmap* pOldBmp = memDC.SelectObject(&bmp);

			memDC.SetBkMode(m_bkMode);
			memDC.SetBkColor(m_bkColor);
			memDC.SetTextColor(m_textColor);
			memDC.SelectObject(&font);

			if (m_textAlignment & DT_WORDBREAK) {
				unsigned int lineCount = 0;
				DrawMultiLineText(&maskDC, fontRect, lineCount, TRUE);
				DrawMultiLineText(&maskDC, fontRect, lineCount, FALSE);
				DrawMultiLineText(&memDC, fontRect, lineCount, FALSE);
			}
			else {
				maskDC.DrawText(GetTitle(), &fontRect.ToCRect(), m_textAlignment);
				memDC.DrawText(GetTitle(), &fontRect.ToCRect(), m_textAlignment);
			}
			// Copy bitmap to screen
			dc->StretchBlt(rect.left, rect.top, rect.Width(), rect.Height(),
				&maskDC, 0, 0, bmpRect.Width(), bmpRect.Height(), SRCAND);
			dc->StretchBlt(rect.left, rect.top, rect.Width(), rect.Height(),
				&memDC, 0, 0, bmpRect.Width(), bmpRect.Height(), SRCPAINT);

			memDC.SelectObject(pOldBmp);
			maskDC.SelectObject(pOldMaskBmp);
		}

		dc->SetTextColor(oldTextColor);
		dc->SetBkColor(oldBkColor);
		dc->SetBkMode(oldBkMode);
		dc->SelectObject(pOldFont);
	}
}

void CProMoLabel::DrawMultiLineText(CDC* dc, CDoubleRect& rect, unsigned int& lineCount, BOOL measureOnly)
/* ============================================================
	Function :		CProMoLabel::DrawMultiLineText
	Description :	Splits and draws text into multiple lines.
	Access :		Protected

	Return :		void
	Parameters :	CDC* dc					-	The CDC to draw
												to.
					CRect rect				-	The rectangle to 
												draw in.
					unsigned int& lineCount -	Number of lines 
												drawn/measured.
					BOOL measureOnly		-	If "TRUE", the 
												function counts
												the number of 
												lines to split 
												the text into 
												without drawing
												the text in dc,
												and stores it
												in "lineCount".

   ============================================================*/
{
	CDC nullDC;
	nullDC.CreateCompatibleDC(NULL);

	int fontHeight = -round(m_fontSize * GetZoom());

	CFont font;
	font.CreateFont(fontHeight, 0, 0, 0, m_fontWeight, m_fontItalic, m_fontUnderline, m_fontStrikeOut, 0, 0, 0, 0, 0, m_fontName);

	CFont* pOldFont = nullDC.SelectObject(&font);

	double hPos = rect.left;
	double vPos = rect.top;
	double x = hPos;
	double y = vPos;

	int drawnLines = 0;

	CString text = GetTitle();

	// Normalize line breaks if needed
	CFileParser::CStringReplace(text, _T("\r\n"), _T("\n"));
	CFileParser::CStringReplace(text, _T("\r"), _T("\n"));

	int pos = 0;
	const int len = text.GetLength();

	TEXTMETRIC tm;
	nullDC.GetTextMetrics(&tm);

	const int lineHeight = tm.tmHeight + tm.tmExternalLeading;
	const double maxWidth = rect.Width();

	double totalHeight =
		lineCount * lineHeight;

	if (m_textAlignment & DT_VCENTER)
		y += (rect.Height() - totalHeight) / 2;
	if (m_textAlignment & DT_BOTTOM)
		y += (rect.Height() - totalHeight);

	while (pos < len)
	{
		// Explicit newline?
		if (text[pos] == _T('\n'))
		{
			y += lineHeight;
			++pos;
			continue;
		}

		int end = FindTextWrapPosition(&nullDC, text, pos, (int)maxWidth);

		int lineLen = end - pos;

		// Skip trailing spaces
		while (lineLen > 0 && _istspace(text[pos + lineLen - 1]))
			--lineLen;

		CSize lineSize = nullDC.GetTextExtent(text.Mid(pos, lineLen));

		if (m_textAlignment & DT_CENTER)
			x = hPos + (rect.Width() - lineSize.cx) / 2;
		if (m_textAlignment & DT_RIGHT)
			x = hPos + (rect.Width() - lineSize.cx);

		if (lineLen > 0 && !measureOnly)
		{
			dc->ExtTextOut(
				(int)x,
				(int)y,
				(m_bkMode & OPAQUE) ? ETO_OPAQUE : 0,
				NULL,
				text.Mid(pos, lineLen),
				NULL
			);
		}

		drawnLines++;

		// Advance pos
		pos = end;

		// Skip leading spaces on next line
		while (pos < len && _istspace(text[pos]) && text[pos] != _T('\n'))
			++pos;

		y += lineHeight;
	}

	if (measureOnly)
		lineCount = drawnLines;
	
	nullDC.SelectObject(pOldFont);
}

void CProMoLabel::ShowPopup(CPoint point, CWnd* parent)
/* ============================================================
	Function :		CProMoLabel::ShowPopup
	Description :	Shows the popup menu for the object.
	Access :		Public

	Return :		void
	Parameters :	CPoint point	-	The point to track.
					CWnd* parent	-	The parent "CWnd" of the
										menu (should be the
										"CDiagramEditor")

   ============================================================*/
{

	CMenu menu;
	if (menu.CreatePopupMenu())
	{

		menu.AppendMenu(MF_STRING, ID_EDIT_CUT, _T("Cut"));
		menu.AppendMenu(MF_STRING, ID_EDIT_COPY, _T("Copy"));
		menu.TrackPopupMenu(TPM_LEFTALIGN | TPM_RIGHTBUTTON, point.x, point.y, parent);

	}

}

CDiagramEntity* CProMoLabel::Create(const CString& str)
/* ============================================================
	Function :		CProMoLabel::Create
	Description :	Creates an object of this type if the type
					matches.
	Return :		CDiagramEntity*	-	The created object, or
										NULL if the type did
										not match.
	Parameters :	const CString& str	-	The type to create.
	Usage :			Static function used by the
					"CProMoControlFactory" to create objects
					of this type.
   ============================================================*/
{
	CProMoLabel* obj = new CProMoLabel;
	if (!obj->HasType(str))
	{
		delete obj;
		obj = NULL;
	}
	
	return obj;
}

BOOL CProMoLabel::HasType(const CString& type) const
/* ============================================================
	Function :		CProMoLabel::HasType
	Description :	Returns if the object is of the specified
					type.
	Access :		Public
	Return :		BOOL	-	"TRUE" if the object is of the
								specified type.
	Parameters :	const CString& type	-	The type to check.
   ============================================================*/
{
	if (type == GetType()) {
		return TRUE;
	}
	return FALSE;
}

CProMoModel* CProMoLabel::GetModel() const
/* ============================================================
	Function :		CProMoLabel::GetModel()
	Description :	Returns a pointer to the model associated
					to this label
	Access :		Public

	Return :		CProMoModel*	-	A pointer to the
										model
	Parameters :	none

   ============================================================*/
{
	return m_model;
}

void CProMoLabel::SetModel(CProMoModel* model)
/* ============================================================
	Function :		CProMoLabel::SetModel
	Description :	Makes the object being passed as input
					parameter the model for this label
	Access :		Protected

	Return :		void
	Parameters :	CProMoModel* block	-	the object that
											should be the
											model

   ============================================================*/
{
	if (model) {
		if (m_model) {
			m_model->UnlinkLabel(this);
		}
		model->LinkLabel(this);
	}
}

CString CProMoLabel::GetPropertyName() const
/* ============================================================
	Function :		CProMoLabel::GetPropertyName()
	Description :	Returns the name of the property being
					displayed
	Access :		Public

	Return :		CString	-	The name of the property being
								displayed
	Parameters :	none

   ============================================================*/
{
	return m_property;
}

CProMoProperty* CProMoLabel::GetProperty() const
/* ============================================================
	Function :		CProMoLabel::GetPropertyName()
	Description :	Returns the property being displayed
	Access :		Public

	Return :		CProMoProperty*	-	The property being displayed
	Parameters :	none

   ============================================================*/
{
	if (m_model) {
		return m_model->FindProperty(m_property);
	}
	CVariantWrapper wrapper;
	wrapper.SetString(GetTitle());
	m_titleProperty->SetValue(wrapper);
	return m_titleProperty;
}

void CProMoLabel::SetFitTitle(BOOL hasFitTitle)
/* ============================================================
	Function :		CProMoLabel::SetFitTitle
	Description :	Sets whether the label should fit the title
	Access :		Public

	Return :		void
	Parameters :	BOOL hasFitTitle	-	"TRUE" if the label
											must fit the title

   ============================================================*/
{
	m_fitTitle = hasFitTitle;
}

BOOL CProMoLabel::HasFitTitle() const
/* ============================================================
	Function :		CProMoLabel::HasFitTitle
	Description :	Returns if the label must fit the title
	Access :		Public

	Return :		BOOL	-	"TRUE" if the label must fit the
								title
	Parameters :	none

   ============================================================*/
{
	return m_fitTitle;
}

void CProMoLabel::SetFitView(BOOL hasFitView)
/* ============================================================
	Function :		CProMoLabel::SetFitView
	Description :	Sets whether the view for the object 
					associated with the label must fit the 
					title
	Access :		Public

	Return :		void
	Parameters :	BOOL hasFitView	-	"TRUE" if the view
										must fit the title

   ============================================================*/
{
	m_fitView = hasFitView;
}

BOOL CProMoLabel::HasFitView() const
/* ============================================================
	Function :		CProMoLabel::SetFitView
	Description :	Returns if the view for the object 
					associated with the label must fit the 
					title

	Return :		BOOL	-	"TRUE" if the label must fit the
								view
	Parameters :	none

   ============================================================*/
{
	return m_fitView;
}

BOOL CProMoLabel::IsLocked(const unsigned int& flag) const
/* ============================================================
	Function :		CProMoLabel::IsLocked
	Description :	Returns if the specified property (or 
					combination of properties) is locked
				
	Access :		Public

	Return :		BOOL				-	"TRUE" if the
											property specified
											is locked
	Parameters :	unsigned int& flag	-	The property (or
											combination) to
											check

   ============================================================*/
{
	return (m_lockFlags & flag) != 0;
}

unsigned int CProMoLabel::GetLock() const
/* ============================================================
	Function :		CProMoLabel::IsLocked
	Description :	Returns the specified property (or
					combination of properties)

	Access :		Public

	Return :		unsigned int& flag	-	The property (or
											combination) being
											locked
	Parameters :	none

   ============================================================*/
{
	return m_lockFlags;
}

void CProMoLabel::SetLock(const unsigned int& flag)
/* ============================================================
	Function :		CProMoLabel::SetLock
	Description :	Locks the specified property (or combination
					of properties)

	Access :		Public

	Return :		void
	Parameters :	unsigned int& flag	-	The property (or
											combination) to
											lock

   ============================================================*/
{
	m_lockFlags = flag;
}

CDoubleRect CProMoLabel::GetTitleRect() const
/* ============================================================
	Function :		CProMoLabel::GetTitleRect()
	Description :	Returns the rectangle inscribing the label
	Access :		Public

	Return :		CDoubleRect	-	"CRect" representing the
									rectangle inscribing label
	Parameters :	none

   ============================================================*/
{
	return m_titleRect;
}

void CProMoLabel::SetProperty(const CString& property)
/* ============================================================
	Function :		CProMoLabel::SetProperty
	Description :	Sets the property displayed by the label
	Access :		Protected

	Return :		void
	Parameters :	CString title	-	The name of the 
										property

   ============================================================*/
{
	m_property = property;
}

CDiagramEntity* CProMoLabel::CreateFromString(const CString& str, CProMoModel* model)
/* ============================================================
	Function :		CProMoLabel::CreateFromString
	Description :	Static factory function that creates and
					returns an instance of this class if str
					is a valid representation.

	Return :		CDiagramEntity*			-	The object, or
												NULL if str is
												not a
												representation 
												of this type.
	Parameters :	const CString& str		-	The string to 
												create from.
					CProMoModel* model		-	A model to be
												associated to 
												the object 
												being created.
					

	Usage :			Can be used as a factory for text file loads.
					Each object type should have its own
					version - the default one is a model
					implementation.

   ============================================================*/
{

	CProMoLabel* obj = new CProMoLabel;
	if (!obj->FromString(str))
	{
		delete obj;
		obj = NULL;
	}
	else {
		if (model) {
			model->LinkLabel(obj);
		}
	}

	return obj;

}

CString CProMoLabel::GetModelFromString(const CString& str)
/* ============================================================
	Function :		CProMoLabel::GetModelFromString
	Description :	Static factory function that
					parses a formatted string and extracts the
					name of the associated model object
	Access :		Public

	Return :		CString			-	The name of the model
	Parameters :	CString& str	-	The string to be parsed

   ============================================================*/
{
	CTokenizer* tok = CFileParser::Tokenize(str);
	CString entityName;
	if (tok) {
		tok->GetAt(7, entityName);
		delete tok;
	}
	return entityName;
}

CString CProMoLabel::GetNameFromString(const CString& str)
/* ============================================================
	Function :		CProMoLabel::GetNameFromString
	Description :	Static factory function that
					parses a formatted string and extracts the
					name of the object
	Access :		Public

	Return :		CString			-	The name of the object
	Parameters :	CString& str	-	The string to be parsed

   ============================================================*/
{
	CTokenizer* tok = CFileParser::Tokenize(str);
	CString name;
	if (tok) {
		tok->GetAt(0, name);
		delete tok;
	}
	return name;
}

CDiagramEntity* CProMoLabel::CreateFromString(const CString& str)
/* ============================================================
	Function :		CProMoLabel::CreateFromString
	Description :	Static factory function that creates and
					returns an instance of this class if str
					is a valid representation.

	Return :		CDiagramEntity*		-	The object, or NULL
											if str is not a
											representation of
											this type.
	Parameters :	const CString& str	-	The string to create
											from.

	Usage :			Can be used as a factory for text file loads.
					Each object type should have its own
					version - the default one is a model
					implementation.

   ============================================================*/
{

	CProMoLabel* obj = new CProMoLabel;
	if (!obj->FromString(str))
	{
		delete obj;
		obj = NULL;
	}

	return obj;

}

CString CProMoLabel::GetDefaultGetString() const
{
	/* ============================================================
	Function :		CProMoLabel::GetDefaultString
	Description :	Gets the default properties of the object
					as a string.
	Access :		Protected

	Return :		CString	-	Resulting string
	Parameters :	none

	Usage :			Call as a part of the saving of objects
					to disk.

   ============================================================*/
	
	CString str;

	CString model;
	CString title;
	CString property;
	if (m_model) {
		model = GetModel()->GetName();
		CFileParser::EncodeString(model);
		property = GetPropertyName();
		CFileParser::EncodeString(property);
	}
	else {
		title = GetTitle();
		CFileParser::EncodeString(title);
	}
		
	CString name = GetName();
	CFileParser::EncodeString(name);

	str.Format(_T("%s:%s,%f,%f,%f,%f,%s,%i,%s,%s,%i,%s,%i,%i,%i,%i,%i,%i,%i,%i,%i,%i,%i,%i,%f,%f,%f,%f,%f,%f,%i"), 
		(LPCTSTR)GetType(), (LPCTSTR)name, GetLeft(), GetTop(), GetRight(), GetBottom(), (LPCTSTR)title, GetGroup(), (LPCTSTR)model, (LPCTSTR)property, m_lockFlags,
		(LPCTSTR)m_fontName,	m_fontSize,	m_fontWeight, m_fontItalic, m_fontUnderline, m_fontStrikeOut, m_textColor, m_bkColor, m_bkMode, m_textAlignment, 
		m_labelAnchorPoint, m_viewAnchorPoint, m_anchorView, m_offset.x, m_offset.y, m_topMargin, m_leftMargin, m_bottomMargin, m_rightMargin, m_fitTitle);

	return str;

}

CString CProMoLabel::GetHeaderFromString(CString& str)
/* ============================================================
	Function :		CProMoLabel::GetHeaderFromString
	Description :	Gets the header from "str".
	Access :		Protected

	Return :		CString			-	The type of "str".
	Parameters :	CString& str	-	"CString" to get type from.

	Usage :			Call as a part of loading the object. "str"
					will have the type removed after the call.

   ============================================================*/
{
	CString header;

	CFileParser::GetHeaderFromString(str, header);

	return header;
}

BOOL CProMoLabel::GetDefaultFromString(CString& str)
/* ============================================================
	Function :		CProMoLabel::GetDefaultFromString
	Description :	Gets the default properties from "str"
	Access :		Protected

	Return :		BOOL			-	"TRUE" if the default
										properties could be loaded ok.
	Parameters :	CString& str	-	"CString" to get the
										default properties from.

	Usage :			Call as a part of loading the object from
					disk. The default object properties will
					be stripped from "str" and the object
					properties set from the data.

   ============================================================*/
{
	BOOL result = FALSE;

	CTokenizer* tok = CFileParser::Tokenize(str);
	if (tok) {

		int size = tok->GetSize();
		if (size >= 8)
		{
			CString name;
			double left;
			double top;
			double right;
			double bottom;
			CString title;
			int group;
			int count = 0;
			CString model;
			CString property;

			tok->GetAt(count++, name);
			tok->GetAt(count++, left);
			tok->GetAt(count++, top);
			tok->GetAt(count++, right);
			tok->GetAt(count++, bottom);
			tok->GetAt(count++, title);
			tok->GetAt(count++, group);
			tok->GetAt(count++, model);
			tok->GetAt(count++, property);

			BOOL fitTitleTemp = m_fitTitle;
			m_fitTitle = FALSE;

			CScopedUpdate guard(m_noOffset);
			SetRect(left, top, right, bottom);
			
			CFileParser::DecodeString(title);
			CFileParser::DecodeString(name);
			CFileParser::DecodeString(property);

			SetTitle(title);
			SetName(name);
			SetGroup(group);
			SetProperty(property);

			// missing style attributes should not prevent the label from loading
			if (size >= 29) {
				CString fontName;
				int fontSize;
				int fontWeight;
				BOOL fontItalic;
				BOOL fontUnderline;
				BOOL fontStrikeOut;
				COLORREF textColor;
				COLORREF bkColor;
				int bkMode;
				int textAlignment;
				int labelPosition;
				int viewPosition;
				int view;
				double offsetX;
				double offsetY;
				double topMargin;
				double leftMargin;
				double bottomMargin;
				double rightMargin;

				int lockFlags;
				BOOL fitTitle;
				
				tok->GetAt(count++, lockFlags);
				tok->GetAt(count++, fontName);
				tok->GetAt(count++, fontSize);
				tok->GetAt(count++, fontWeight);
				tok->GetAt(count++, fontItalic);
				tok->GetAt(count++, fontUnderline);
				tok->GetAt(count++, fontStrikeOut);
				tok->GetAt(count++, textColor);
				tok->GetAt(count++, bkColor);
				tok->GetAt(count++, bkMode);
				tok->GetAt(count++, textAlignment);
				tok->GetAt(count++, labelPosition);
				tok->GetAt(count++, viewPosition);
				tok->GetAt(count++, view);
				tok->GetAt(count++, offsetX);
				tok->GetAt(count++, offsetY);
				tok->GetAt(count++, topMargin);
				tok->GetAt(count++, leftMargin);
				tok->GetAt(count++, bottomMargin);
				tok->GetAt(count++, rightMargin);
				tok->GetAt(count++, fitTitle);

				m_fitTitle = fitTitle;
				m_fontName = fontName;
				m_fontSize = fontSize;
				m_fontWeight = fontWeight;
				m_fontItalic = fontItalic;
				m_fontUnderline = fontUnderline;
				m_fontStrikeOut = fontStrikeOut;
				m_textColor = textColor;
				m_bkColor = bkColor;
				m_bkMode = bkMode;
				m_textAlignment = textAlignment;
				m_labelAnchorPoint = labelPosition;
				m_viewAnchorPoint = viewPosition;
				m_anchorView = view;
				m_offset = CDoublePoint(offsetX, offsetY);
				m_topMargin = topMargin;
				m_leftMargin = leftMargin;
				m_bottomMargin = bottomMargin;
				m_rightMargin = rightMargin;

				m_lockFlags = lockFlags;
			}
			else {
				m_fitTitle = fitTitleTemp;
			}

			result = TRUE;
		}
		delete tok;
	}

	return result;

}

void CProMoLabel::SetRect(CRect rect)
/* ============================================================
	Function :		CProMoLabel::SetRect
	Description :	Sets the object rectangle, normalized.
	Access :		Public

	Return :		void
	Parameters :	CRect rect	-	The rectangle to set.

	Usage :			Call to place the object.
					Overridden to avoid name hiding for SetRect
					overloaded methods in derived classes.
					DO NOT DELETE.

   ============================================================*/
{

	CDiagramEntity::SetRect(rect);
}

void CProMoLabel::SetRect(double left, double top, double right, double bottom)
/* ============================================================
	Function :		CProMoLabel::SetRect
	Description :	Sets the object rectangle.
	Access :		Public

	Return :		void
	Parameters :	double left		-	Left edge
					double top		-	Top edge
					double right	-	Right edge
					double bottom	-	Bottom edge

	Usage :			Call to place the object.
					Overridden to resize the block to fit the
					title if fitTitle is "TRUE"

   ============================================================*/
{
	if (m_fitTitle) {

		if (m_titleRect.Width() > right - left) {
			if (GetLeft() - left != 0) {
				left = (right - m_titleRect.Width());
			}
			else {
				right = (left + m_titleRect.Width());
			}
		}

		if (m_titleRect.Height() > bottom - top) {
			if (GetTop() - top != 0) {
				top = (bottom - m_titleRect.Height());
			}
			else {
				bottom = (top + m_titleRect.Height());
			}
		}
	}

	if (!m_noOffset) {
		// The user is manually moving the label
		if (!IsLocked(LOCK_REPOSITIONING)) {
			UpdateOffset();
			CDiagramEntity::SetRect(left, top, right, bottom);
		}
	}
	else {
		CDiagramEntity::SetRect(left, top, right, bottom);
	}

}

void CProMoLabel::SetTitle(CString title)
/* ============================================================
	Function :		CProMoLabel::SetTitle
	Description :	Sets the Title property
	Access :		Public

	Return :		void
	Parameters :	CString title	-	The new title

	Usage :			Call to set the title of the label.
					Overridden to resize the label to fit the
					title if fitTitle is "TRUE"

   ============================================================*/
{
	
	CDiagramEntity::SetTitle(title);

	AutoResize();
}

CDoubleRect CProMoLabel::ComputeTextRect(CDC* dc, double zoom)
/* ============================================================
	Function :		CProMoLabel::ComputeTextRect
	Description :	Computes a CRect that fully contains the
					input string.
	Access :		Protected

	Return :		CDoubleRect	-	CRect that fully contains the
									input string
					double zoom	-	The zoom factor to be applied
	Parameters :	CDC* dc		-	The CDC to compute the rect.
	Usage :			Call to determine (without drawing on
					display) the size of the input text. Can be
					used to resize the block and/or to set the
					minimum size such that the text can fit in
					it.

   ============================================================*/
{
	CFont font;
	
	int fontHeight = -round(m_fontSize * zoom);
	
	font.CreateFont(fontHeight, 0, 0, 0, m_fontWeight, m_fontItalic, m_fontUnderline, m_fontStrikeOut, 0, 0, 0, 0, 0, m_fontName);

	CFont* pOldFont = dc->SelectObject(&font);
	int oldBk = dc->SetBkMode(TRANSPARENT);

	CRect textBounds(0, 0, 0, 0);
	CSize textSize(0, 0);

	int hPadding = 0;
	int vPadding = 0;

	BOOL isMultiline = (m_textAlignment & DT_WORDBREAK);

	if (!isMultiline)
	{
		textSize = dc->GetTextExtent(GetTitle());
		textBounds.right = textSize.cx;
		textBounds.bottom = textSize.cy;
	}
	else
	{
		textBounds.right = GetRect().Width();
		UINT format = m_textAlignment;
		format &= (DT_VCENTER | DT_BOTTOM | DT_WORDBREAK | DT_CENTER | DT_RIGHT | DT_LEFT);
		format |= DT_CALCRECT | DT_TOP;

		dc->DrawText(GetTitle(), &textBounds, format);
	}

	textBounds.right += (long)((m_leftMargin + m_rightMargin + hPadding) * zoom);
	textBounds.bottom += (long)((m_topMargin + m_bottomMargin + vPadding) * zoom);

	dc->SetBkMode(oldBk);
	dc->SelectObject(pOldFont);

	return textBounds;
}

CString CProMoLabel::GetFontName() const
/* ============================================================
	Function :		CProMoLabel::GetFontName()
	Description :	Returns the name of the font used to 
					display the label
	Access :		Public

	Return :		CString		-	The name of the font used
									to display the label
	Parameters :	none

   ============================================================*/
{
	return m_fontName;
}

unsigned int CProMoLabel::GetFontSize() const
/* ============================================================
	Function :		CProMoLabel::GetFontSize()
	Description :	Returns the size of the font used to
					display the label
	Access :		Public

	Return :		unsigned int	-	The size of the font used
										to display the label
	Parameters :	none

   ============================================================*/
{
	return m_fontSize;
}

unsigned int CProMoLabel::GetFontWeight() const
/* ============================================================
	Function :		CProMoLabel::GetFontWeight()
	Description :	Returns the weight of the font used to
					display the label
	Access :		Public

	Return :		unsigned int	-	The weight of the font used
										to display the label
	Parameters :	none

   ============================================================*/
{
	return m_fontWeight;
}

BOOL CProMoLabel::IsFontItalic() const
/* ============================================================
	Function :		CProMoLabel::IsFontItalic()
	Description :	Returns if the font used to display the 
					label is in italic
	Access :		Public

	Return :		BOOL		-	"TRUE" if the font used
									to display the label is in
									italic
	Parameters :	none

   ============================================================*/
{
	return m_fontItalic;
}

BOOL CProMoLabel::IsFontUnderline() const
/* ============================================================
	Function :		CProMoLabel::IsFontUnderline()
	Description :	Returns if the font used to display the
					label is underlined
	Access :		Public

	Return :		BOOL		-	"TRUE" if the font used
									to display the label is
									underlined
	Parameters :	none

   ============================================================*/
{
	return m_fontUnderline;
}

BOOL CProMoLabel::IsFontStrikeOut() const
/* ============================================================
	Function :		CProMoLabel::IsFontStrikeOut()
	Description :	Returns if the font used to display the
					label is stroken out
	Access :		Public

	Return :		BOOL		-	"TRUE" if the font used
									to display the label is
									stroken out
	Parameters :	none

   ============================================================*/
{
	return m_fontStrikeOut;
}

COLORREF CProMoLabel::GetTextColor() const
/* ============================================================
	Function :		CProMoLabel::GetTextColor()
	Description :	Returns the color of the text in the label
	Access :		Public

	Return :		COLORREF	-	The color of the text in 
									the label
	Parameters :	none

   ============================================================*/
{
	return m_textColor;
}

COLORREF CProMoLabel::GetBkColor() const
/* ============================================================
	Function :		CProMoLabel::GetBkColor()
	Description :	Returns the background color of the label
	Access :		Public

	Return :		COLORREF	-	The background color of the 
									label
	Parameters :	none

   ============================================================*/
{
	return m_bkColor;
}

unsigned int CProMoLabel::GetTextHorizontalAlignment() const
/* ============================================================
	Function :		CProMoLabel::GetTextHorizontalAlignment()
	Description :	Returns the horizontal alignment of the text 
					in the label
	Access :		Public

	Return :		unsigned int	-	The alignment of the
										text in the label
	Parameters :	none

   ============================================================*/
{
	return m_textAlignment & H_GROUP;
}

unsigned int CProMoLabel::GetTextVerticalAlignment() const
/* ============================================================
	Function :		CProMoLabel::GetTextVerticalAlignment()
	Description :	Returns the vertical alignment of the text
					in the label
	Access :		Public

	Return :		unsigned int	-	The alignment of the
										text in the label
	Parameters :	none

   ============================================================*/
{
	return m_textAlignment & V_GROUP;
}

BOOL CProMoLabel::HasTextAlignmentFlag(unsigned int flag) const
/* ============================================================
	Function :		CProMoLabel::HasTextAlignmentFlag()
	Description :	Returns if the alignment flag is set for 
					the text in the label
	Access :		Public

	Return :		BOOL				-	"TRUE" if the alignment
											flag is set for the text
											in the label
	Parameters :	unsigned int flag	-	The alignment flag 
											for the	text in the
											label

   ============================================================*/
{
	return (m_textAlignment & flag) != 0;
}

unsigned int CProMoLabel::GetTextAlignment() const
/* ============================================================
	Function :		CProMoLabel::GetTextAlignment()
	Description :	Returns the alignment of the text in the
					label
	Access :		Public

	Return :		unsigned int	-	The alignment of the
										text in the label
	Parameters :	none

   ============================================================*/
{
	return m_textAlignment;
}

unsigned int CProMoLabel::GetLabelAnchorPoint() const
/* ============================================================
	Function :		CProMoLabel::GetLabelAnchorPoint()
	Description :	Returns the anchor point of the label
					being used to align it with the view object
	Access :		Public

	Return :		unsigned int	-	The anchor point of the
										label
	Parameters :	none

   ============================================================*/
{
	return m_labelAnchorPoint;
}

unsigned int CProMoLabel::GetViewAnchorPoint() const
/* ============================================================
	Function :		CProMoLabel::GetViewAnchorPoint()
	Description :	Returns the anchor point of the view object
					being used to align it with the view object
	Access :		Public

	Return :		unsigned int	-	The anchor point of the
										view object
	Parameters :	none

   ============================================================*/
{
	return m_viewAnchorPoint;
}

unsigned int CProMoLabel::GetAnchorView() const
/* ============================================================
	Function :		CProMoLabel::GetAnchorView()
	Description :	Returns to which view object the label 
					should be anchored. Applicable only for 
					labels linked to edge views.
	Access :		Public

	Return :		unsigned int	-	The anchor view object
	Parameters :	none

   ============================================================*/
{
	return m_anchorView;
}

BOOL CProMoLabel::IsTextMultiline() const
/* ============================================================
	Function :		CProMoLabel::IsTextMultiline()
	Description :	Returns whether the text is split into
					multiple lines
	Access :		Public

	Return :		BOOL	-	"TRUE" if the text is split into
								multiple lines
	Parameters :	none

   ============================================================*/
{
	return HasTextAlignmentFlag(DT_WORDBREAK);
}

BOOL CProMoLabel::IsVisible() const
/* ============================================================
	Function :		CProMoLabel::IsVisible()
	Description :	Returns if the label is visible
	Access :		Public

	Return :		BOOL		-	"TRUE" if the label is
									visible
	Parameters :	none

   ============================================================*/
{
	return m_visible;
}

unsigned int CProMoLabel::GetBkMode() const
/* ============================================================
	Function :		CProMoLabel::GetBkMode()
	Description :	Returns the background style of the label
	Access :		Public

	Return :		unsigned int	-	The background style of
										the label
	Parameters :	none

   ============================================================*/
{
	return m_bkMode;
}

// Setters
BOOL CProMoLabel::SetFontName(const CString& name)
/* ============================================================
	Function :		CProMoLabel::SetFontName()
	Description :	Sets the name of the font used to display
					the label
	Access :		Public

	Return :		BOOL					-	"TRUE" if the
												operation
												succeeded
	Parameters :	CString& name		-	The name of
												the font

   ============================================================*/
{
	if (IsLocked(LOCK_FONTNAME)) 
		return FALSE;
	m_fontName = name;
	AutoResize();
	return TRUE;
}

BOOL CProMoLabel::SetFontSize(const unsigned int& size)
/* ============================================================
	Function :		CProMoLabel::SetFontSize()
	Description :	Sets the size of the font used to display
					the label
	Access :		Public

	Return :		BOOL					-	"TRUE" if the
												operation
												succeeded
	Parameters :	unsigned int& size		-	The size of
												the font

   ============================================================*/
{
	if (IsLocked(LOCK_FONTSIZE))
		return FALSE;
	if (size == 0)
		return FALSE;
	m_fontSize = size;
	AutoResize();
	return TRUE;
}

BOOL CProMoLabel::SetFontWeight(const unsigned int& weight)
/* ============================================================
	Function :		CProMoLabel::SetFontWeight()
	Description :	Sets the weight of the font used to display 
					the label
	Access :		Public

	Return :		BOOL					-	"TRUE" if the
												operation
												succeeded
	Parameters :	unsigned int& weight		-	The weight of
												the font
												
   ============================================================*/
{
	if (IsLocked(LOCK_FONTWEIGHT))
		return FALSE;
	m_fontWeight = weight;
	AutoResize();
	return TRUE;
}

BOOL CProMoLabel::SetFontItalic(const BOOL& italic)
/* ============================================================
	Function :		CProMoLabel::SetFontItalic()
	Description :	Sets the font used to display the label as 
					italic
	Access :		Public

	Return :		BOOL					-	"TRUE" if the
												operation
												succeeded
	Parameters :	BOOL& italic			-	"TRUE" if the
												font should be
												in italic

   ============================================================*/
{
	if (IsLocked(LOCK_FONTITALIC))
		return FALSE;
	m_fontItalic = italic;
	AutoResize();
	return TRUE;
}

BOOL CProMoLabel::SetFontUnderline(const BOOL& underline)
/* ============================================================
	Function :		CProMoLabel::SetFontUnderline()
	Description :	Sets the font used to display the label as 
					underlined
	Access :		Public

	Return :		BOOL					-	"TRUE" if the
												operation
												succeeded
	Parameters :	BOOL& underline			-	"TRUE" if the
												font should be
												underlined

   ============================================================*/
{
	if (IsLocked(LOCK_FONTUNDERLINE))
		return FALSE;
	m_fontUnderline = underline;
	AutoResize();
	return TRUE;
}

BOOL CProMoLabel::SetFontStrikeOut(const BOOL& strikeOut)
/* ============================================================
	Function :		CProMoLabel::SetFontStrikeOut()
	Description :	Sets the font used to display the label as
					stroken out
	Access :		Public

	Return :		BOOL					-	"TRUE" if the
												operation
												succeeded
	Parameters :	BOOL& strikeOut			-	"TRUE" if the
												font should be
												stroken out

   ============================================================*/
{
	if (IsLocked(LOCK_FONTSTRIKEOUT))
		return FALSE;
	m_fontStrikeOut = strikeOut;
	AutoResize();
	return TRUE;
}

BOOL CProMoLabel::SetTextColor(const COLORREF& color)
/* ============================================================
	Function :		CProMoLabel::SetTextColor()
	Description :	Sets the color of the text in the label
	Access :		Public

	Return :		BOOL					-	"TRUE" if the
												operation
												succeeded
	Parameters :	COLORREF& color			-	The color of
												the text in
												the label

   ============================================================*/
{
	if (IsLocked(LOCK_TEXTCOLOR))
		return FALSE;
	m_textColor = color;
	return TRUE;
}

BOOL CProMoLabel::SetBkColor(const COLORREF& color)
/* ============================================================
	Function :		CProMoLabel::SetBkColor()
	Description :	Sets the background color of the label
	Access :		Public

	Return :		BOOL					-	"TRUE" if the
												operation
												succeeded
	Parameters :	COLORREF& color			-	The background
												color of the
												label

   ============================================================*/
{
	if (IsLocked(LOCK_BKCOLOR))
		return FALSE;
	m_bkColor = color;
	return TRUE;
}

BOOL CProMoLabel::SetTextHorizontalAlignment(const unsigned int& flag)
/* ============================================================
	Function :		CProMoLabel::SetTextHorizontalAlignment()
	Description :	Sets the horizontal alignment flag of the 
					text in the label
	Access :		Public

	Return :		BOOL				-	"TRUE" if the
											operation
											succeeded
	Parameters :	unsigned int& flag	-	The alignment flag
											of the text in
											the label

   ============================================================*/
{
	unsigned int alignment = m_textAlignment;
	unsigned int newFlag = flag & H_GROUP;
	alignment &= ~H_GROUP; // clear horizontal group

	alignment |= newFlag; // set new flag if not default

	return SetTextAlignment(alignment);
}

BOOL CProMoLabel::SetTextVerticalAlignment(const unsigned int& flag)
/* ============================================================
	Function :		CProMoLabel::SetTextVerticalAlignment()
	Description :	Sets the vertical alignment flag of the
					text in the label
	Access :		Public

	Return :		BOOL				-	"TRUE" if the
											operation
											succeeded
	Parameters :	unsigned int& flag	-	The alignment flag
											of the text in
											the label

   ============================================================*/
{
	unsigned int alignment = m_textAlignment;
	unsigned int newFlag = flag & V_GROUP;
	alignment &= ~V_GROUP; // clear vertical group

	alignment |= newFlag; // set new flag if not default

	return SetTextAlignment(alignment);
}



BOOL CProMoLabel::SetTextAlignmentFlag(const unsigned int& flag, const BOOL& enabled) 
/* ============================================================
	Function :		CProMoLabel::SetTextAlignmentFlag()
	Description :	Sets the alignment flag of the text in the label
	Access :		Public

	Return :		BOOL				-	"TRUE" if the
											operation
											succeeded
	Parameters :	unsigned int& flag	-	The alignment flag
											of the text in
											the label
					BOOL& enabled		-	"TRUE" to enable

   ============================================================*/
{
	unsigned int alignment = m_textAlignment;

	if (flag & H_GROUP)
	{
		alignment &= ~H_GROUP;
		if (enabled)
			alignment |= flag;
	}
	else if (flag & V_GROUP)
	{
		alignment &= ~V_GROUP;
		if (enabled)
			alignment |= flag;
	}
	else if (flag & LINE_GROUP)
	{
		alignment &= ~LINE_GROUP;
		if (enabled)
			alignment |= flag;
	}
	else
	{
		if (enabled)
			alignment |= flag;
		else
			alignment &= ~flag;
	}

	return SetTextAlignment(alignment);
}


BOOL CProMoLabel::SetTextAlignment(const unsigned int& alignment)
/* ============================================================
	Function :		CProMoLabel::SetTextAlignment()
	Description :	Sets the alignment of the text in the label
	Access :		Public

	Return :		BOOL					-	"TRUE" if the 
												operation
												succeeded
	Parameters :	unsigned int& alignment	-	The alignment of
												the text in
												the label

   ============================================================*/
{
	if (IsLocked(LOCK_ALIGNMENT))
		return FALSE;
	m_textAlignment = alignment;
	AutoResize();
	return TRUE;
}

BOOL CProMoLabel::SetLabelAnchorPoint(const unsigned int& position)
/* ============================================================
	Function :		CProMoLabel::SetLabelAnchorPoint()
	Description :	Sets the anchor point of the label
					being used to align it with the view object
	Access :		Public

	Return :		BOOL					-	"TRUE" if the operation
												succeeded
	Parameters :	unsigned int& position	-	The anchor point of
												the label

   ============================================================*/
{
	if (IsLocked(LOCK_ANCHORING))
		return FALSE;
	m_labelAnchorPoint = position;
	AutoResize();
	return TRUE;
}

BOOL CProMoLabel::SetViewAnchorPoint(const unsigned int& position)
/* ============================================================
	Function :		CProMoLabel::SetViewAnchorPoint()
	Description :	Sets the anchor point of the view object
					being used to align the label
	Access :		Public

	Return :		BOOL					-	"TRUE" if the operation
												succeeded
	Parameters :	unsigned int& position	-	The anchor point of
												the view object

   ============================================================*/
{
	if (IsLocked(LOCK_ANCHORING))
		return FALSE;
	m_viewAnchorPoint = position;
	AutoResize();
	return TRUE;
}

BOOL CProMoLabel::SetAnchorView(const unsigned int& position)
/* ============================================================
	Function :		CProMoLabel::SetAnchorView()
	Description :	Sets the anchor view being used to align 
					the label.
					Applicable only for labels linked to
					edge views.
	Access :		Public

	Return :		BOOL					-	"TRUE" if the operation
												succeeded
	Parameters :	unsigned int& position	-	The anchor view

   ============================================================*/
{
	if (IsLocked(LOCK_ANCHORING))
		return FALSE;
	m_anchorView = position;
	AutoResize();
	return TRUE;
}

BOOL CProMoLabel::SetTextMultiline(const BOOL& multiline)
/* ============================================================
	Function :		CProMoLabel::SetTextMultiline()
	Description :	Sets whether the text in the label should
					be split into multiple lines
	Access :		Public

	Return :		BOOL					-	"TRUE" if the
												operation
												succeeded
	Parameters :	BOOL& multiline			-	"TRUE" if the
												text in	the 
												label should
												be split into
												multiple lines

   ============================================================*/
{
	unsigned int alignment = m_textAlignment;
	
	alignment &= ~LINE_GROUP; // clear vertical group

	if (multiline) {
		alignment |= DT_WORDBREAK;
	}
	else {
		alignment |= DT_SINGLELINE;
	}

	return SetTextAlignment(alignment);
}

BOOL CProMoLabel::SetVisible(const BOOL& visible)
/* ============================================================
	Function :		CProMoLabel::SetVisible()
	Description :	Sets whether the label should be visible
	Access :		Public

	Return :		BOOL					-	"TRUE" if the
												operation
												succeeded
	Parameters :	BOOL& underline			-	"TRUE" if the
												label should be
												visible
	Usage:			The function should be used to hide labels
					that are not relevant. Note that an 
					invisible label can still be selected and
					moved by the user. To prevent that, invoke
					SetLock with PROMO_LOCK_SELECTION

   ============================================================*/
{
	m_visible = visible;
	return TRUE;
}

BOOL CProMoLabel::SetBkMode(const unsigned int& mode)
/* ============================================================
	Function :		CProMoLabel::SetBkMode()
	Description :	Sets the background style of the label
	Access :		Public

	Return :		BOOL				-	"TRUE" if the operation
											succeeded
	Parameters :	unsigned int& model	-	The background style of
											the label

   ============================================================*/
{
	if (IsLocked(LOCK_BKMODE))
		return FALSE;
	m_bkMode = mode;
	return TRUE;
}

CDoublePoint CProMoLabel::GetSelectionMarkerPoint(UINT marker, CDoubleRect rect) const
/* ============================================================
	Function :		CProMoLabel::GetSelectionMarkerPoint
	Description :	Gets the selection point for
					marker, given the true object rectangle
					"rect".
	Access :		Protected


	Return :		CDoublePointRect	-	The marker point
	Parameters :	UINT marker			-	The marker type 
											("DEHT_"-constants 
											defined in
											DiargramEntity.h)
					CDoubleRect rect	-	The object rectangle

	Usage :			"marker" can be one of the following:
						"DEHT_NONE" No hit-point
						"DEHT_BODY" Inside object body
						"DEHT_TOPLEFT" Top-left corner
						"DEHT_TOPMIDDLE" Middle top-side
						"DEHT_TOPRIGHT" Top-right corner
						"DEHT_BOTTOMLEFT" Bottom-left corner
						"DEHT_BOTTOMMIDDLE" Middle bottom-side
						"DEHT_BOTTOMRIGHT" Bottom-right corner
						"DEHT_LEFTMIDDLE" Middle left-side
						"DEHT_RIGHTMIDDLE" Middle right-side
						"DEHT_CENTER" Center of the object body

   ============================================================*/
{
	CDoublePoint markerPoint;
	
	switch (marker)
	{
	case DEHT_TOPLEFT:
		markerPoint.SetPoint(rect.left,rect.top);
		break;

	case DEHT_TOPMIDDLE:
		markerPoint.SetPoint(rect.left + (rect.Width() / 2), rect.top);
		break;

	case DEHT_TOPRIGHT:
		markerPoint.SetPoint(rect.right, rect.top);
		break;

	case DEHT_BOTTOMLEFT:
		markerPoint.SetPoint(rect.left, rect.bottom);
		break;

	case DEHT_BOTTOMMIDDLE:
		markerPoint.SetPoint(rect.left + (rect.Width() / 2), rect.bottom);
		break;

	case DEHT_BOTTOMRIGHT:
		markerPoint.SetPoint(rect.right, rect.bottom);
		break;

	case DEHT_LEFTMIDDLE:
		markerPoint.SetPoint(rect.left, rect.top + (rect.Height() / 2));
		break;

	case DEHT_RIGHTMIDDLE:
		markerPoint.SetPoint(rect.right, rect.top + (rect.Height() / 2));
		break;
	
	case DEHT_CENTER:
		markerPoint.SetPoint(rect.left + (rect.Width() / 2), rect.top + (rect.Height() / 2));
		break;
	}

	return markerPoint;
}

CDoublePoint CProMoLabel::ComputeAnchoredPosition() const
/* ============================================================
	Function :		CProMoLabel::ComputeAnchoredPosition()
	Description :	Computes the the top-left position of the
					label, such that it fulfills the anchoring
					constraints
	Access :		Public

	Return :		CDoublePoint	-	The top-left position
										for the label
	Parameters :	none

   ============================================================*/
{
	CDoublePoint topLeft(m_offset);
	CDiagramEntity* view = GetView();
	if (view) {
		
		CDoubleRect viewRect = view->GetRect();

		CDoublePoint viewAnchorPt = GetSelectionMarkerPoint(m_viewAnchorPoint, viewRect);

		CDoublePoint labelAnchorPt;

		if (m_fitTitle) {
			labelAnchorPt = GetSelectionMarkerPoint(m_labelAnchorPoint, m_titleRect);
		}
		else {
			labelAnchorPt = GetSelectionMarkerPoint(m_labelAnchorPoint, CDoubleRect(0,0,GetRight()-GetLeft(),GetBottom()-GetTop()));
		}
		topLeft.SetPoint(
			viewAnchorPt.x - labelAnchorPt.x + m_offset.x,
			viewAnchorPt.y - labelAnchorPt.y + m_offset.y
		);
		
	}
	else {
		topLeft.SetPoint(GetLeft(), GetTop());
	}
	return topLeft;
}

void CProMoLabel::Reposition() 
/* ============================================================
	Function :		CProMoLabel::Reposition()
	Description :	Repositions the label, such that it 
					fulfills the anchoring constraints
	Access :		Public

	Return :		void
	Parameters :	none

   ============================================================*/
{
	CScopedUpdate offsetGuard(m_noOffset);
	
	CRect labelRect;
	
	CDoublePoint newTopLeft = ComputeAnchoredPosition();
	if (!(newTopLeft.x == -1 && newTopLeft.y == -1)) {
		if (m_fitTitle) {
			labelRect = m_titleRect.ToCRect();
		}
		else {
			labelRect = GetRect();
		}
		CSize size = labelRect.Size();

		SetRect(
			newTopLeft.x,
			newTopLeft.y,
			newTopLeft.x + size.cx,
			newTopLeft.y + size.cy
		);
	}

}

void CProMoLabel::UpdateOffset()
/* ============================================================
	Function :		CProMoLabel::UpdateOffset()
	Description :	Computes the offset between the current
					position of the label and the one
					fulfilling the anchoring constraints
	Access :		Public

	Return :		void
	Parameters :	none

   ============================================================*/
{
	CDiagramEntity* view = GetView();
	CDoublePoint topLeft(m_offset);
	if (view) {
		CDoubleRect viewRect = view->GetRect();

		CDoublePoint viewAnchorPt = GetSelectionMarkerPoint(m_viewAnchorPoint, viewRect);
		CDoublePoint labelAnchorPt = GetSelectionMarkerPoint(m_labelAnchorPoint, GetRect());

		m_offset.x = labelAnchorPt.x - viewAnchorPt.x;
		m_offset.y = labelAnchorPt.y - viewAnchorPt.y;
	}
}

CDiagramEntity* CProMoLabel::GetView() const
/* ============================================================
	Function :		CProMoLabel::GetView()
	Description :	Returns a reference to the view, based on 
					the label anchoring preference.
	Access :		Public

	Return :		CDiagramEntity*	-	The view reference
	Parameters :	none

   ============================================================*/
{
	CDiagramEntity* view = NULL;
	CProMoBlockModel* blockModel = dynamic_cast<CProMoBlockModel*>(m_model);
	if (blockModel) {
		if (blockModel->GetMainBlockView()) {
			view = (CDiagramEntity*)blockModel->GetMainBlockView();
		}
	}
	CProMoEdgeModel* edgeModel = dynamic_cast<CProMoEdgeModel*>(m_model);
	if (edgeModel) {
		if (m_anchorView == VIEW_FIRST) {
			if (edgeModel->GetFirstSegment()) {
				view = (CDiagramEntity*)edgeModel->GetFirstSegment();
			}
		}
		else if (m_anchorView == VIEW_LAST) {
			if (edgeModel->GetLastSegment()) {
				view = (CDiagramEntity*)edgeModel->GetLastSegment();
			}
		}
	}
	return view;
}

int CProMoLabel::FindTextWrapPosition(CDC* dc, const CString& text, int start, int maxWidth) const
/* ============================================================
	Function :		CProMoLabel::FindTextWrapPosition
	Description :	Identifies the position to wrap text at.
	Access :		Protected

	Return :		void
	Parameters :	CDC* dc					-	The CDC to draw
												to.
					CString& text			-	The text to
												wrap.
					int start				-	Where to start
												measuring from
												in "text".
					int maxWidth			-	The maximum width
												allowed before
												wrapping.

   ============================================================*/
{
	
	const int len = text.GetLength();
	int lastSpace = -1;

	for (int i = start + 1; i <= len; ++i)
	{
		CSize sz = dc->GetTextExtent(text.Mid(start, i - start));

		if (sz.cx > maxWidth)
		{
			if (lastSpace >= 0)
				return lastSpace + 1;

			return max(start + 1, i - 1);
		}

		if (_istspace(text[i - 1]))
			lastSpace = i - 1;
	}

	return len;
}

int CProMoLabel::GetHitCode(const CPoint& point, const CRect& rect) const
/* ============================================================
	Function :		CProMoLabel::GetHitCode
	Description :	Returns the hit point constant for "point"
					assuming the object rectangle "rect".
	Access :		Public

	Return :		int				-	The hit point,
										"DEHT_NONE" if none.
	Parameters :	CPoint point	-	The point to check
					CRect rect		-	The rect to check

	Usage :			Call to see in what part of the object point
					lies. Overridden to disable perimeter hit 
					points for unselectable labels.

   ============================================================*/
{
	if (IsLocked(LOCK_SELECTION)) {
		return DEHT_NONE;
	}

	if (IsLocked(LOCK_REPOSITIONING)) {
		if (rect.PtInRect(point)) {
			return DEHT_BODY;
		}
		return DEHT_NONE;
	}

	return CDiagramEntity::GetHitCode(point, rect);
	
}

void CProMoLabel::AutoResize() 
/* ============================================================
	Function :		CProMoLabel::AutoResize
	Description :	Automatically resizes the label to fit the 
					text, and notify the corresponding block 
					view (if it exists) so that it can react.
	Access :		Public

	Return :		void
	Parameters :	none

   ============================================================*/
{
	CDC dc;
	dc.CreateCompatibleDC(NULL);

	// Compute the title rect always at 100% zoom factor
	CDoubleRect textRect = ComputeTextRect(&dc, 1.0);
	m_titleRect = textRect;

	Reposition();

	CProMoBlockModel* blockModel = dynamic_cast<CProMoBlockModel*>(m_model);
	if (blockModel) {
		CProMoBlockView* blockView = blockModel->GetMainBlockView();
		if (blockView) {
			blockView->OnLabelChanged(this);
		}
	}
}

void CProMoLabel::Select(BOOL selected)
/* ============================================================
	Function :		CProMoLabel::Select
	Description :	Sets the object select state.
	Access :		Public

	Return :		void
	Parameters :	BOOL selected	-	"TRUE" to select, "FALSE"
										to unselect.

	Usage :			Call to select/deselect the object.
					Overridden to prevent selection from
					happening if the label is locked

   ============================================================*/
{
	if (IsLocked(LOCK_SELECTION))
		return;

	CDiagramEntity::Select(selected);

}

void CProMoLabel::SetMargins(double left, double top, double right, double bottom)
/* ============================================================
	Function :		CProMoLabel::SetMargins
	Description :	Sets text margins.
	Access :		Public

	Return :		void
	Parameters :	double left		-	New left margin.
					double top		-	New top margin.
					double right	-	New right margin.
					double bottom	-	New bottom margin.

	Usage :			Call to set new margins for the label.

   ============================================================*/
{

	m_leftMargin = left;
	m_topMargin = top;
	m_rightMargin = right;
	m_bottomMargin = bottom;

}

void CProMoLabel::GetMargins(double& left, double& top, double& right, double& bottom) const
/* ============================================================
	Function :		CProMoLabel::GetMargins
	Description :	Return text margins.
	Access :		Public

	Return :		void
	Parameters :	double& left	-	Current left margin.
					double& top		-	Current top margin.
					double& right	-	Current right margin.
					double& bottom	-	Current bottom margin.

	Usage :			Call to get the margins of the label.

   ============================================================*/
{

	left = m_leftMargin;
	top = m_topMargin;
	right = m_rightMargin;
	bottom = m_bottomMargin;

}

void CProMoLabel::OnPropertyChanged(CProMoProperty* prop)
/* ============================================================
	Function :		CProMoLabel::OnPropertyChanged
	Description :	Notification that a property has changed.
	Access :		Public

	Return :		void
	Parameters :	CProMoProperty* prop	-	Property that
												changed.

	Usage :			Can be called by a property to notify the
					model that it changed, and to trigger UI
					updates.

   ============================================================*/
{
	SetTitle(prop->GetValue().GetString());	
}

CProMoAppChildAuto* CProMoLabel::GetAutomationObject()
/* ============================================================
	Function :		CProMoLabel::GetAutomationObject
	Description :	Returns a pointer to the automation object
					associated with this container, creating it
					if it does not already exist.
	Access :		Public
	Return :		CProMoAutomationObject*	-	The pointer.
	Parameters :	none
   ============================================================*/
{
	if (!m_autoObject) {
		m_autoObject = new CProMoLabelAuto();
		m_autoObject->Initialize(this);
	}
	return m_autoObject;
}

void CProMoLabel::ReleaseAutomationObject()
/* ============================================================
	Function :		CProMoLabel::ReleaseAutomationObject
	Description :	Releases the pointer to the automation object
					associated with this container.
	Access :		Public
	Return :		void
	Parameters :	none
   ============================================================*/
{
	if (m_autoObject) {
		CProMoAppChildAuto* autoObject = m_autoObject;
		m_autoObject = NULL;
		autoObject->Detach();
	}
}