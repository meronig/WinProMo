#include "stdafx.h"
#include "ProMoLabel.h"
#include "ProMoNameFactory.h"
#include "../DiagramEditor/Tokenizer.h"
#include "../FileUtils/FileParser.h"
#include "../resource.h"
#include "ProMoBlockModel.h"
#include "ProMoEdgeModel.h"

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
	
	m_fontName = CString("Courier New");
	m_fontSize = 12;
	m_fontWeight = FW_NORMAL;
	m_fontItalic = FALSE;
	m_fontUnderline = FALSE;
	m_textAlignment = DT_NOPREFIX | DT_SINGLELINE | DT_VCENTER | DT_CENTER;
	m_textColor = RGB(0, 0, 0);
	m_bkColor = CLR_NONE;
	m_bkMode = TRANSPARENT;
	m_lockFlags = 0;
	m_noOffset = FALSE;
	m_labelAnchorPoint = DEHT_CENTER;
	m_viewAnchorPoint = DEHT_CENTER;
	m_anchorView = PROMO_VIEW_FIRST;

	m_offset = CPoint(0, 0);
	m_fitTitle = TRUE;
	m_fitView = FALSE;
	m_titleRect = CRect(0, 0, 0, 0); 

	m_rotation = 0;
	m_topMargin = 0;
	m_leftMargin = 0;
	m_bottomMargin = 0;
	m_rightMargin = 0;

	SetConstraints(CSize(5, 5), CSize(-1, -1));
	SetType(_T("promo_label"));

	SetZoom(1.0);

	CString title;
	BOOL result;
	result = title.LoadString(IDS_PROMO_BLOCK);
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
	CFont font;
	font.CreateFont(-round(m_fontSize * GetZoom()), 0, 0, 0, m_fontWeight, m_fontItalic, m_fontUnderline, 0, 0, 0, 0, 0, 0, m_fontName);
	
	CFont* pOldFont = dc->SelectObject(&font);
	COLORREF oldTextColor = dc->SetTextColor(m_textColor);
	COLORREF oldBkColor = dc->SetBkColor(m_bkColor);
	int oldBkMode = dc->SetBkMode(m_bkMode);

	dc->DrawText(GetTitle(), rect, m_textAlignment);

	dc->SetTextColor(oldTextColor);
	dc->SetBkColor(oldBkColor);
	dc->SetBkMode(oldBkMode);
	dc->SelectObject(pOldFont);
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

CString CProMoLabel::GetProperty() const
/* ============================================================
	Function :		CProMoLabel::GetProperty()
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

BOOL CProMoLabel::HasFitTitle()
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

BOOL CProMoLabel::HasFitView()
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
	Access :		Public

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
		property = GetProperty();
		CFileParser::EncodeString(property);
	}
	else {
		title = GetTitle();
		CFileParser::EncodeString(title);
	}
		
	CString name = GetName();
	CFileParser::EncodeString(name);

	str.Format(_T("%s:%s,%f,%f,%f,%f,%s,%i,%s,%s,%i,%s,%i,%i,%i,%i,%i,%i,%i,%i,%i,%i,%i,%f,%f"), 
		(LPCTSTR)GetType(), (LPCTSTR)name, GetLeft(), GetTop(), GetRight(), GetBottom(), (LPCTSTR)title, GetGroup(), (LPCTSTR)model, (LPCTSTR)property, m_lockFlags,
		(LPCTSTR)m_fontName,	m_fontSize,	m_fontWeight, m_fontItalic, m_fontUnderline, m_textColor, m_bkColor, m_bkMode, m_textAlignment, m_labelAnchorPoint, m_viewAnchorPoint,
		m_anchorView, m_offset.x, m_offset.y);

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
			if (size >= 23) {
				CString fontName;
				int fontSize;
				int fontWeight;
				BOOL fontItalic;
				BOOL fontUnderline;
				COLORREF textColor;
				COLORREF bkColor;
				int bkMode;
				int textAlignment;
				int labelPosition;
				int viewPosition;
				int view;
				double offsetX;
				double offsetY;

				BOOL lockFlags;
				
				tok->GetAt(count++, lockFlags);
				tok->GetAt(count++, fontName);
				tok->GetAt(count++, fontSize);
				tok->GetAt(count++, fontWeight);
				tok->GetAt(count++, fontItalic);
				tok->GetAt(count++, fontUnderline);
				tok->GetAt(count++, textColor);
				tok->GetAt(count++, bkColor);
				tok->GetAt(count++, bkMode);
				tok->GetAt(count++, textAlignment);
				tok->GetAt(count++, labelPosition);
				tok->GetAt(count++, viewPosition);
				tok->GetAt(count++, view);
				tok->GetAt(count++, offsetX);
				tok->GetAt(count++, offsetY);

				m_fontName = fontName;
				m_fontSize = fontSize;
				m_fontWeight = fontWeight;
				m_fontItalic = fontItalic;
				m_fontUnderline = fontUnderline;
				m_textColor = textColor;
				m_bkColor = bkColor;
				m_bkMode = bkMode;
				m_textAlignment = textAlignment;
				m_labelAnchorPoint = labelPosition;
				m_viewAnchorPoint = viewPosition;
				m_anchorView = view;
				m_offset = CDoublePoint(offsetX, offsetY);

				m_lockFlags = lockFlags;
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
		if (!IsLocked(PROMO_LOCK_REPOSITIONING)) {
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

void CProMoLabel::ComputeTextRect()
/* ============================================================
	Function :		CProMoLabel::ComputeTextRect
	Description :	Computes a CRect that fully contains the
					input string, using the default font.
	Access :		Protected

	Return :		void
	Parameters :	none
	Usage :			Call to determine (without drawing on
					display) the size of the input text. Can be
					used to resize the block and/or to set the
					minimum size such that the text can fit in
					it.

   ============================================================*/
{
	CFont font;
	CDC dc;
	double zoom = GetZoom();
	if (zoom == 0) {
		zoom = 1.0;
	}
	font.CreateFont(-round(m_fontSize * GetZoom()), 0, 0, 0, m_fontWeight, m_fontItalic, m_fontUnderline, 0, 0, 0, 0, 0, 0, m_fontName);

	dc.CreateCompatibleDC(NULL);
	dc.SelectObject(font);
	int mode = dc.SetBkMode(TRANSPARENT);

	CRect textBounds(0, 0, 0, 0);
	dc.DrawText(GetTitle(), &textBounds, m_textAlignment | DT_CALCRECT);

	if (m_fontUnderline)
	{
		//textBounds.bottom += textBounds.Height() * 1.1 * GetZoom();
	}
	if (m_fontItalic) {
		//textBounds.right += textBounds.Width() * 0.05 * GetZoom();
	}

	textBounds.right = textBounds.right + (4 * GetZoom());
	textBounds.bottom = textBounds.bottom + (4 * GetZoom());

	m_titleRect = textBounds;
	
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
	if (IsLocked(PROMO_LOCK_FONTNAME)) 
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
	if (IsLocked(PROMO_LOCK_FONTSIZE))
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
	if (IsLocked(PROMO_LOCK_FONTWEIGHT))
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
	Parameters :	BOOL& italic				-	"TRUE" if the
												font should be
												in italic

   ============================================================*/
{
	if (IsLocked(PROMO_LOCK_FONTITALIC))
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
	if (IsLocked(PROMO_LOCK_FONTUNDERLINE))
		return FALSE;
	m_fontUnderline = underline;
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
	if (IsLocked(PROMO_LOCK_TEXTCOLOR))
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
	if (IsLocked(PROMO_LOCK_BKCOLOR))
		return FALSE;
	m_bkColor = color;
	return TRUE;
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
	if (IsLocked(PROMO_LOCK_ALIGNMENT))
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
	if (IsLocked(PROMO_LOCK_ANCHORING))
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
	if (IsLocked(PROMO_LOCK_ANCHORING))
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
	if (IsLocked(PROMO_LOCK_ANCHORING))
		return FALSE;
	m_anchorView = position;
	AutoResize();
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
	if (IsLocked(PROMO_LOCK_BKMODE))
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
		if (blockModel->GetMainView()) {
			view = (CDiagramEntity*)blockModel->GetMainView();
		}
	}
	CProMoEdgeModel* edgeModel = dynamic_cast<CProMoEdgeModel*>(m_model);
	if (edgeModel) {
		if (m_anchorView == PROMO_VIEW_FIRST) {
			if (edgeModel->GetFirstSegment()) {
				view = (CDiagramEntity*)edgeModel->GetFirstSegment();
			}
		}
		else if (m_anchorView == PROMO_VIEW_LAST) {
			if (edgeModel->GetLastSegment()) {
				view = (CDiagramEntity*)edgeModel->GetLastSegment();
			}
		}
	}
	return view;
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
	if (IsLocked(PROMO_LOCK_SELECTION)) {
		return DEHT_NONE;
	}

	if (IsLocked(PROMO_LOCK_REPOSITIONING)) {
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
	
	ComputeTextRect();

	Reposition();

	CProMoBlockModel* blockModel = dynamic_cast<CProMoBlockModel*>(m_model);
	if (blockModel) {
		CProMoBlockView* blockView = blockModel->GetMainView();
		if (blockView) {
			blockView->OnLabelChanged(this);
		}
	}
}

