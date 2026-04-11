/* ==========================================================================

	Copyright © 2026 Technical University of Denmark

	CProMoElementAuto

	Author :		Giovanni Meroni

	Purpose :		"CProMoElementAuto" is an automation object that
					represents an element in a diagram. It provides methods
					to access the properties and the labels of the element, 
					to copy, cut, delete, and duplicate the element, and to 
					change its visual appearance (line color, line width, etc.).

	Description :	"CProMoElementAuto" provides the implementation of the
					methods and properties that are common to all diagram 
					elements.

   ========================================================================*/
#include "stdafx.h"
#include "ProMoElementAuto.h"
#include "..\ProMoEditor\ProMoModel.h"
#include "ProMoLabelsAuto.h"
#include "ProMoPropertiesAuto.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CProMoElementAuto

IMPLEMENT_DYNCREATE(CProMoElementAuto, CProMoDiagramChildAuto)

CProMoElementAuto::CProMoElementAuto()
/* ============================================================
	Function :		CProMoElementAuto::CProMoElementAuto
	Description :	Constructor
	Access :		Public

	Return :		void
	Parameters :	none
   ============================================================ */
{
	m_pLabels = NULL;
	m_pProperties = NULL;
}

CProMoModel* CProMoElementAuto::GetModel()
/* ============================================================
	Function :		CProMoElementAuto::GetModel
	Description :	Get the model associated with this element
	Access :		Public

	Return :		CProMoModel*	-	the model associated with 
										this element
	Parameters :	none
   ============================================================ */
{
	ThrowIfDetached();
	ThrowIfNoDiagramAutoObject();

	return dynamic_cast<CProMoModel*>(m_pInternalObject);
}

void CProMoElementAuto::GetViews(CObArray& viewList)
/* ============================================================
	Function :		CProMoElementAuto::GetViews
	Description :	Get the views associated with this element
	Access :		Public

	Return :		void
	Parameters :	CObArray& viewList	-	the list to fill with 
											the views associated 
											with this element
   ============================================================ */
{
	viewList.RemoveAll();

	if (GetModel()) {
		GetModel()->GetViews(viewList);
	}
}

IProMoView* CProMoElementAuto::GetMainView()
/* ============================================================
	Function :		CProMoElementAuto::GetMainView
	Description :	Get the main view associated with this element
	Access :		Public

	Return :		IProMoView*	-	the main view associated 
									with this element, or 
									"NULL" if there is no
									main view
	Parameters :	none
   ============================================================ */
{
	CObArray viewList;
	GetViews(viewList);
	if (viewList.GetSize() > 0) {
		return dynamic_cast<IProMoView*>(viewList.GetAt(0));
	}
	return NULL;
}

void CProMoElementAuto::GetAttachedLabels(CObArray& labelList)
/* ============================================================
	Function :		CProMoElementAuto::GetAttachedLabels
	Description :	Get the labels attached to this element
	Access :		Public

	Return :		void
	Parameters :	CObArray& labelList	-	the list to fill with 
											the labels attached 
											to this element
   ============================================================ */
{
	labelList.RemoveAll();
	if (GetModel()) {
		GetModel()->GetLabels(labelList);
	}
}

CProMoElementAuto::~CProMoElementAuto()
/* ============================================================
	Function :		CProMoElementAuto::~CProMoElementAuto
	Description :	Destructor
	Access :		Protected

	Return :		void
	Parameters :	none
   ============================================================ */
{
}

CProMoLabelsAuto* CProMoElementAuto::GetLabelsAutoObject()
/* ============================================================
	Function :		CProMoElementAuto::GetLabelsAutoObject
	Description :	Returns a pointer to the automation object that 
					represents the collection of labels associated
					to this element. If the automation object does not
					exist, it is created.
	Access :		Public

	Return :		CProMoLabelsAuto*	-	a pointer to the 
											automation object 
											that represents the 
											collection of 
											labels associated to 
											this element.
	Parameters :	none
   ============================================================ */
{
	ThrowIfDetached();
	ThrowIfNoDiagramAutoObject();

	if (!m_pLabels) {
		m_pLabels = new CProMoLabelsAuto();
		if (m_pLabels) {
			m_pLabels->SetElementAutoObject(this);
		}
	}
	return m_pLabels;
}

void CProMoElementAuto::ReleaseLabelsAutoObject()
/* ============================================================
	Function :		CProMoElementAuto::ReleaseLabelsAutoObject
	Description :	Releases the automation object that represents 
					the collection of labels associated to this
					element, if it exists.
	Access :		Public

	Return :		void
	Parameters :	none
   ============================================================ */
{
	if (m_pLabels) {
		m_pLabels->SetElementAutoObject(NULL);
		m_pLabels->GetIDispatch(FALSE)->Release();
		m_pLabels = NULL;
	}
}

CProMoPropertiesAuto* CProMoElementAuto::GetPropertiesAutoObject()
/* ============================================================
	Function :		CProMoElementAuto::GetPropertiesAutoObject
	Description :	Returns a pointer to the automation object that 
					represents the collection of properties of
					this element. If the automation object does not
					exist, it is created.
	Access :		Public

	Return :		CProMoPropertiesAuto*	-	a pointer to the 
												automation object 
												that represents the 
												collection of 
												properties of
												this element.
	Parameters :	none
   ============================================================ */
{
	ThrowIfDetached();
	ThrowIfNoDiagramAutoObject();

	if (!m_pProperties) {
		m_pProperties = new CProMoPropertiesAuto();
		if (m_pProperties) {
			m_pProperties->SetElementAutoObject(this);
		}
	}
	return m_pProperties;
}

void CProMoElementAuto::ReleasePropertiesAutoObject()
/* ============================================================
	Function :		CProMoElementAuto::ReleasePropertiesAutoObject
	Description :	Releases the automation object that represents 
					the collection of properties of this 
					element, if it exists.
	Access :		Public

	Return :		void
	Parameters :	none
   ============================================================ */
{
	if (m_pProperties) {
		m_pProperties->SetElementAutoObject(NULL);
		m_pProperties->GetIDispatch(FALSE)->Release();
		m_pProperties = NULL;
	}
}

void CProMoElementAuto::DeleteViewsAndLabels()
/* ============================================================
	Function :		CProMoElementAuto::DeleteViewsAndLabels
	Description :	Delete all the views and labels associated with 
					this element
	Access :		Protected

	Return :		void
	Parameters :	none
   ============================================================ */
{
	CObArray elements;
	CObArray labels;
	GetViews(elements);
	GetAttachedLabels(labels);
	elements.Append(labels);

	if (GetContainer() && GetModel()) {

		GetContainer()->Snapshot();

		for (int i = elements.GetSize() - 1; i >= 0; --i) {
			CDiagramEntity* element = dynamic_cast<CDiagramEntity*>(elements.GetAt(i));
			GetContainer()->Remove(element);
		}

		GetDiagramAutoObject()->NotifyChange();

	}
}

BOOL CProMoElementAuto::HasLockFlag(unsigned int lockFlag)
/* ============================================================
	Function :		CProMoElementAuto::HasLockFlag
	Description :	Check if the specified lock flag is set for all 
					the views of this element
	Access :		Protected
	Return :		BOOL					-	"TRUE" if the 
												specified lock 
												flag is set 
												for all the views 
												of this element, 
												"FALSE"	otherwise
	Parameters :	unsigned int lockFlag	-	the lock flag to check
   ============================================================ */
{
	CObArray views;
	GetViews(views);
	
	// return false if at least one view has not the specified flag locked
	for (int i = 0; i < views.GetSize(); i++) {
		IProMoView* view = dynamic_cast<IProMoView*>(views.GetAt(i));
		if (view) {
			if (!view->IsLocked(lockFlag)) {
				return FALSE;
			}
		}
	}
	return TRUE;
}

void CProMoElementAuto::Select()
/* ============================================================
	Function :		CProMoElementAuto::Select
	Description :	Select all the views and labels associated with 
					this element
	Access :		Protected

	Return :		void
	Parameters :	none
   ============================================================ */
{
	GetContainer()->UnselectAll();
	CObArray elements;
	GetViews(elements);
	CObArray labels;
	GetAttachedLabels(labels);
	elements.Append(labels);
	for (int i = 0; i < elements.GetSize(); i++) {
		CDiagramEntity* view = dynamic_cast<CDiagramEntity*>(elements.GetAt(i));
		if (view) {
			view->Select(TRUE);
		}
	}
}

void CProMoElementAuto::OnFinalRelease()
/* ============================================================
	Function :		CProMoElementAuto::OnFinalRelease
	Description :	Release the automation object. Called when
					the last reference for an automation object
					is released. The base class will
					automatically delete the object.
	Access :		Public

	Return :		void
	Parameters :	none

	Usage:			Overridden to release the automation object
					for the labels and properties of this element,
					if they exists. The base class implementation 
					will delete the object when the application
					automation object is released.

   ============================================================*/
{
	ReleasePropertiesAutoObject();
	ReleaseLabelsAutoObject();
	CProMoDiagramChildAuto::OnFinalRelease();
}

BEGIN_MESSAGE_MAP(CProMoElementAuto, CProMoDiagramChildAuto)
	//{{AFX_MSG_MAP(CProMoElementAuto)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

BEGIN_DISPATCH_MAP(CProMoElementAuto, CProMoDiagramChildAuto)
	//{{AFX_DISPATCH_MAP(CProMoElementAuto)
	//}}AFX_DISPATCH_MAP
END_DISPATCH_MAP()

BEGIN_INTERFACE_MAP(CProMoElementAuto, CProMoDiagramChildAuto)
END_INTERFACE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CProMoElementAuto message handlers

void CProMoElementAuto::Copy() 
/* ============================================================
	Function :		CProMoElementAuto::Copy
	Description :	Copy this element to the clipboard
	Access :		Public

	Return :		void
	Parameters :	none
   ============================================================ */
{
	if (GetModel()) {
		Select();
		GetContainer()->CopyAllSelected();
	}
}

void CProMoElementAuto::Cut() 
/* ============================================================
	Function :		CProMoElementAuto::Cut
	Description :	Cut this element to the clipboard
	Access :		Public

	Return :		void
	Parameters :	none
   ============================================================ */
{
	if (GetModel()) {
		GetContainer()->Snapshot();
		Copy();
		GetContainer()->RemoveAllSelected();
		GetDiagramAutoObject()->NotifyChange();
	}
}

void CProMoElementAuto::Delete() 
/* ============================================================
	Function :		CProMoElementAuto::Delete
	Description :	Delete this element
	Access :		Public

	Return :		void
	Parameters :	none
   ============================================================ */
{
	DeleteViewsAndLabels();
}

LPDISPATCH CProMoElementAuto::Duplicate() 
/* ============================================================
	Function :		CProMoElementAuto::Duplicate
	Description :	Duplicate this element
	Access :		Public

	Return :		LPDISPATCH	-	the duplicated element, or 
									"NULL" if the duplication 
									failed
	Parameters :	none
   ============================================================ */
{
	if (!GetModel()) {
		return NULL;
	}

	GetContainer()->Snapshot();
	IProMoEntity* view = dynamic_cast<IProMoEntity*>(GetMainView());
	IProMoEntity* newView = dynamic_cast<IProMoEntity*>(GetContainer()->CloneEntity(view));
	GetDiagramAutoObject()->NotifyChange();

	if (newView) {
		if (newView->GetModel()) {
			CProMoElementAuto* pElementAuto = dynamic_cast<CProMoElementAuto*>(newView->GetModel()->GetAutomationObject());
			if (pElementAuto) {
				pElementAuto->SetDiagramAutoObject(GetDiagramAutoObject());
				return pElementAuto->GetIDispatch(TRUE);
			}
		}
	}
	
	return NULL;
}

OLE_COLOR CProMoElementAuto::GetLineColor() 
/* ============================================================
	Function :		CProMoElementAuto::GetLineColor
	Description :	Get the line color of this element
	Access :		Public

	Return :		OLE_COLOR	-	the line color of this element
	Parameters :	none
   ============================================================ */
{
	if (GetMainView()) {
		COLORREF color = GetMainView()->GetLineColor();
		return RGB(GetRValue(color), GetGValue(color), GetBValue(color));
	}

	return RGB(0,0,0);
}

void CProMoElementAuto::SetLineColor(OLE_COLOR nNewValue) 
/* ============================================================
	Function :		CProMoElementAuto::SetLineColor
	Description :	Set the line color of this element
	Access :		Public

	Return :		void
	Parameters :	OLE_COLOR nNewValue	-	the new line color of 
											this element
   ============================================================ */
{
	COLORREF color;
	HRESULT hr = OleTranslateColor(nNewValue, NULL, &color);
	if (FAILED(hr))
		AfxThrowOleException(hr);

	CObArray views;
	GetViews(views);

	if (HasLockFlag(LOCK_LINECOLOR) || !GetModel()) {
		return;
	}
	
	GetContainer()->Snapshot();
	
	for (int i = 0; i < views.GetSize(); i++) {
		IProMoView* view = dynamic_cast<IProMoView*>(views.GetAt(i));
		if (view) {
			view->SetLineColor(color);
		}
	}
	
	GetDiagramAutoObject()->NotifyChange();

}

short CProMoElementAuto::GetLineWidth() 
/* ============================================================
	Function :		CProMoElementAuto::GetLineWidth
	Description :	Get the line width of this element
	Access :		Public

	Return :		short	-	the line width of this element
	Parameters :	none
   ============================================================ */
{
	if (GetMainView()) {
		return GetMainView()->GetLineWidth();
	}

	return 0;
}

void CProMoElementAuto::SetLineWidth(short nNewValue) 
/* ============================================================
	Function :		CProMoElementAuto::SetLineWidth
	Description :	Set the line width of this element
	Access :		Public

	Return :		void
	Parameters :	short nNewValue	-	the new line width of 
										this element
   ============================================================ */
{
	CObArray views;
	GetViews(views);

	if (HasLockFlag(LOCK_LINEWIDTH) || !GetModel()) {
		return;
	}

	GetContainer()->Snapshot();

	for (int i = 0; i < views.GetSize(); i++) {
		IProMoView* view = dynamic_cast<IProMoView*>(views.GetAt(i));
		if (view) {
			view->SetLineWidth(nNewValue);
		}
	}
	GetDiagramAutoObject()->NotifyChange();

}

long CProMoElementAuto::GetLineStyle() 
/* ============================================================
	Function :		CProMoElementAuto::GetLineStyle
	Description :	Get the line style of this element
	Access :		Public

	Return :		short	-	the line style of this element
	Parameters :	none
   ============================================================ */
{
	if (GetMainView()) {
		return GetMainView()->GetLineStyle();
	}

	return 0;
}

void CProMoElementAuto::SetLineStyle(long nNewValue) 
/* ============================================================
	Function :		CProMoElementAuto::SetLineStyle
	Description :	Set the line style of this element
	Access :		Public

	Return :		void
	Parameters :	short nNewValue	-	the new line style of 
										this element
   ============================================================ */
{
	CObArray views;
	GetViews(views);
	
	if (HasLockFlag(LOCK_LINESTYLE) || !GetModel()) {
		return;
	}

	GetContainer()->Snapshot();

	for (int i = 0; i < views.GetSize(); i++) {
		IProMoView* view = dynamic_cast<IProMoView*>(views.GetAt(i));
		if (view) {
			view->SetLineStyle(nNewValue);
		}
	}
	GetDiagramAutoObject()->NotifyChange();

}

BSTR CProMoElementAuto::GetFontName() 
/* ============================================================
	Function :		CProMoElementAuto::GetFontName
	Description :	Get the font name of this element
	Access :		Public

	Return :		BSTR	-	the font name of this element
	Parameters :	none
   ============================================================ */
{
	CString strResult;

	if (GetMainView()) {
		strResult = GetMainView()->GetFontName();
	}

	return strResult.AllocSysString();
}

void CProMoElementAuto::SetFontName(LPCTSTR lpszNewValue) 
/* ============================================================
	Function :		CProMoElementAuto::SetFontName
	Description :	Set the font name of this element
	Access :		Public

	Return :		void
	Parameters :	LPCTSTR lpszNewValue	-	the new font name of 
											this element
   ============================================================ */
{
	CObArray views;
	GetViews(views);
	
	if (HasLockFlag(LOCK_FONTNAME) || !GetModel()) {
		return;
	}

	GetContainer()->Snapshot();

	for (int i = 0; i < views.GetSize(); i++) {
		IProMoView* view = dynamic_cast<IProMoView*>(views.GetAt(i));
		if (view) {
			view->SetFontName(lpszNewValue);
		}
	}
	GetDiagramAutoObject()->NotifyChange();

}

short CProMoElementAuto::GetFontSize() 
/* ============================================================
	Function :		CProMoElementAuto::GetFontSize
	Description :	Get the font size of this element
	Access :		Public

	Return :		short	-	the font size of this element
	Parameters :	none
   ============================================================ */
{
	if (GetMainView()) {
		return GetMainView()->GetFontSize();
	}

	return 0;
}

void CProMoElementAuto::SetFontSize(short nNewValue) 
/* ============================================================
	Function :		CProMoElementAuto::SetFontSize
	Description :	Set the font size of this element
	Access :		Public

	Return :		void
	Parameters :	short nNewValue	-	the new font size of 
										this element
   ============================================================ */
{
	CObArray views;
	GetViews(views);
	
	if (HasLockFlag(LOCK_FONTSIZE) || !GetModel()) {
		return;
	}

	GetContainer()->Snapshot();

	for (int i = 0; i < views.GetSize(); i++) {
		IProMoView* view = dynamic_cast<IProMoView*>(views.GetAt(i));
		if (view) {
			view->SetFontSize(nNewValue);
		}
	}
	GetDiagramAutoObject()->NotifyChange();

}

short CProMoElementAuto::GetFontWeight() 
/* ============================================================
	Function :		CProMoElementAuto::GetFontWeight
	Description :	Get the font weight of this element
	Access :		Public

	Return :		short	-	the font weight of this element
	Parameters :	none
   ============================================================ */
{
	if (GetMainView()) {
		return GetMainView()->GetFontWeight();
	}

	return 0;
}

void CProMoElementAuto::SetFontWeight(short nNewValue) 
/* ============================================================
	Function :		CProMoElementAuto::SetFontWeight
	Description :	Set the font weight of this element
	Access :		Public

	Return :		void
	Parameters :	short nNewValue	-	the new font weight of 
										this element
   ============================================================ */
{
	CObArray views;
	GetViews(views);
	
	if (HasLockFlag(LOCK_FONTWEIGHT) || !GetModel()) {
		return;
	}

	GetContainer()->Snapshot();

	for (int i = 0; i < views.GetSize(); i++) {
		IProMoView* view = dynamic_cast<IProMoView*>(views.GetAt(i));
		if (view) {
			view->SetFontWeight(nNewValue);
		}
	}
	GetDiagramAutoObject()->NotifyChange();

}

BOOL CProMoElementAuto::GetFontItalic() 
/* ============================================================
	Function :		CProMoElementAuto::GetFontItalic
	Description :	Get the font italic attribute of this element
	Access :		Public

	Return :		BOOL	-	"TRUE" if the font of this 
								element is italic, "FALSE" 
								otherwise
	Parameters :	none
   ============================================================ */
{
	if (GetMainView()) {
		return GetMainView()->IsFontItalic();
	}

	return TRUE;
}

void CProMoElementAuto::SetFontItalic(BOOL bNewValue) 
/* ============================================================
	Function :		CProMoElementAuto::SetFontItalic
	Description :	Set the font italic attribute of this element
	Access :		Public

	Return :		void
	Parameters :	BOOL bNewValue	-	"TRUE" if the font of 
										this element must be 
										italic, "FALSE" 
										otherwise
   ============================================================ */
{
	CObArray views;
	GetViews(views);
	
	if (HasLockFlag(LOCK_FONTITALIC) || !GetModel()) {
		return;
	}

	GetContainer()->Snapshot();

	for (int i = 0; i < views.GetSize(); i++) {
		IProMoView* view = dynamic_cast<IProMoView*>(views.GetAt(i));
		if (view) {
			view->SetFontItalic(bNewValue);
		}
	}
	GetDiagramAutoObject()->NotifyChange();

}

BOOL CProMoElementAuto::GetFontUnderline() 
/* ============================================================
	Function :		CProMoElementAuto::GetFontUnderline
	Description :	Get the font underline attribute of this element
	Access :		Public

	Return :		BOOL	-	"TRUE" if the font of this 
								element is underlined, "FALSE" 
								otherwise
	Parameters :	none
   ============================================================ */
{
	if (GetMainView()) {
		return GetMainView()->IsFontUnderline();
	}

	return TRUE;
}

void CProMoElementAuto::SetFontUnderline(BOOL bNewValue) 
/* ============================================================
	Function :		CProMoElementAuto::SetFontUnderline
	Description :	Set the font underline attribute of this element
	Access :		Public

	Return :		void
	Parameters :	BOOL bNewValue	-	"TRUE" if the font of 
										this element must be 
										underlined, "FALSE" 
										otherwise
   ============================================================ */
{
	CObArray views;
	GetViews(views);
	
	if (HasLockFlag(LOCK_FONTUNDERLINE) || !GetModel()) {
		return;
	}

	GetContainer()->Snapshot();

	for (int i = 0; i < views.GetSize(); i++) {
		IProMoView* view = dynamic_cast<IProMoView*>(views.GetAt(i));
		if (view) {
			view->SetFontUnderline(bNewValue);
		}
	}
	GetDiagramAutoObject()->NotifyChange();

}

BOOL CProMoElementAuto::GetFontStrikeOut() 
/* ============================================================
	Function :		CProMoElementAuto::GetFontStrikeOut
	Description :	Get the font strikeout attribute of this element
	Access :		Public

	Return :		BOOL	-	"TRUE" if the font of this 
								element is strikeout, "FALSE" 
								otherwise
	Parameters :	none
   ============================================================ */
{
	if (GetMainView()) {
		return GetMainView()->IsFontStrikeOut();
	}

	return TRUE;
}

void CProMoElementAuto::SetFontStrikeOut(BOOL bNewValue) 
/* ============================================================
	Function :		CProMoElementAuto::SetFontStrikeOut
	Description :	Set the font strikeout attribute of this element
	Access :		Public

	Return :		void
	Parameters :	BOOL bNewValue	-	"TRUE" if the font of 
										this element must be 
										strikeout, "FALSE" 
										otherwise
   ============================================================ */
{
	CObArray views;
	GetViews(views);
	
	if (HasLockFlag(LOCK_FONTSTRIKEOUT) || !GetModel()) {
		return;
	}

	GetContainer()->Snapshot();

	for (int i = 0; i < views.GetSize(); i++) {
		IProMoView* view = dynamic_cast<IProMoView*>(views.GetAt(i));
		if (view) {
			view->SetFontStrikeOut(bNewValue);
		}
	}
	GetDiagramAutoObject()->NotifyChange();

}

OLE_COLOR CProMoElementAuto::GetTextColor() 
/* ============================================================
	Function :		CProMoElementAuto::GetTextColor
	Description :	Get the text color of this element
	Access :		Public

	Return :		OLE_COLOR	-	the text color of this element
	Parameters :	none
   ============================================================ */
{
	if (GetMainView()) {
		COLORREF color = GetMainView()->GetTextColor();
		return RGB(GetRValue(color), GetGValue(color), GetBValue(color));
	}

	return RGB(0,0,0);
}

void CProMoElementAuto::SetTextColor(OLE_COLOR nNewValue) 
/* ============================================================
	Function :		CProMoElementAuto::SetTextColor
	Description :	Set the text color of this element
	Access :		Public

	Return :		void
	Parameters :	OLE_COLOR nNewValue	-	the new text color of 
											this element
   ============================================================ */
{
	COLORREF color;
	HRESULT hr = OleTranslateColor(nNewValue, NULL, &color);
	if (FAILED(hr))
		AfxThrowOleException(hr);
	CObArray views;
	GetViews(views);
	
	if (HasLockFlag(LOCK_TEXTCOLOR) || !GetModel()) {
		return;
	}

	GetContainer()->Snapshot();

	for (int i = 0; i < views.GetSize(); i++) {
		IProMoView* view = dynamic_cast<IProMoView*>(views.GetAt(i));
		if (view) {
			view->SetTextColor(nNewValue);
		}
	}
	GetDiagramAutoObject()->NotifyChange();

}

OLE_COLOR CProMoElementAuto::GetBkColor() 
/* ============================================================
	Function :		CProMoElementAuto::GetBkColor
	Description :	Get the background color of this element
	Access :		Public

	Return :		OLE_COLOR	-	the background color of this 
								element
	Parameters :	none
   ============================================================ */
{
	if (GetMainView()) {
		COLORREF color = GetMainView()->GetBkColor();
		return RGB(GetRValue(color), GetGValue(color), GetBValue(color));
	}

	return RGB(0,0,0);
}

void CProMoElementAuto::SetBkColor(OLE_COLOR nNewValue) 
/* ============================================================
	Function :		CProMoElementAuto::SetBkColor
	Description :	Set the background color of this element
	Access :		Public

	Return :		void
	Parameters :	OLE_COLOR nNewValue	-	the new background 
											color of this element
   ============================================================ */
{
	COLORREF color;
	HRESULT hr = OleTranslateColor(nNewValue, NULL, &color);
	CObArray views;
	GetViews(views);
	
	if (HasLockFlag(LOCK_BKCOLOR) || !GetModel()) {
		return;
	}

	GetContainer()->Snapshot();

	for (int i = 0; i < views.GetSize(); i++) {
		IProMoView* view = dynamic_cast<IProMoView*>(views.GetAt(i));
		if (view) {
			view->SetBkColor(nNewValue);
		}
	}
	GetDiagramAutoObject()->NotifyChange();

}

long CProMoElementAuto::GetBkMode() 
/* ============================================================
	Function :		CProMoElementAuto::GetBkMode
	Description :	Get the background mode of this element
	Access :		Public

	Return :		long	-	the background mode of this element
	Parameters :	none
   ============================================================ */
{
	if (GetMainView()) {
		return GetMainView()->GetBkMode();
	}

	return 0;
}

void CProMoElementAuto::SetBkMode(long nNewValue) 
/* ============================================================
	Function :		CProMoElementAuto::SetBkMode
	Description :	Set the background mode of this element
	Access :		Public

	Return :		void
	Parameters :	long nNewValue	-	the new background mode 
										of this element
   ============================================================ */
{
	CObArray views;
	GetViews(views);
	
	if (HasLockFlag(LOCK_BKMODE) || !GetModel()) {
		return;
	}

	GetContainer()->Snapshot();

	for (int i = 0; i < views.GetSize(); i++) {
		IProMoView* view = dynamic_cast<IProMoView*>(views.GetAt(i));
		if (view) {
			view->SetBkMode(nNewValue);
		}
	}
	GetDiagramAutoObject()->NotifyChange();

}

BOOL CProMoElementAuto::GetTextMultiLine()
/* ============================================================
	Function :		CProMoElementAuto::GetTextMultiLine
	Description :	Check if the text of this element is multiline
	Access :		Public

	Return :		BOOL	-	"TRUE" if the text of this element 
								is multiline, "FALSE" otherwise
	Parameters :	none
   ============================================================ */
{
	if (GetMainView()) {
		return GetMainView()->IsTextMultiline();
	}

	return FALSE;
}

void CProMoElementAuto::SetTextMultiLine(BOOL bNewValue)
/* ============================================================
	Function :		CProMoElementAuto::SetTextMultiLine
	Description :	Set the text of this element as multiline or 
					single line
	Access :		Public

	Return :		void
	Parameters :	BOOL bNewValue	-	"TRUE" if the text of this 
										element must be multiline, 
										"FALSE" otherwise
   ============================================================ */
{
	CObArray views;
	GetViews(views);
	
	if (HasLockFlag(LOCK_ALIGNMENT) || !GetModel()) {
		return;
	}

	GetContainer()->Snapshot();

	for (int i = 0; i < views.GetSize(); i++) {
		IProMoView* view = dynamic_cast<IProMoView*>(views.GetAt(i));
		if (view) {
			view->SetTextMultiline(bNewValue);
		}
	}
	GetDiagramAutoObject()->NotifyChange();
}

long CProMoElementAuto::GetTextHorizontalAlignment() 
/* ============================================================
	Function :		CProMoElementAuto::GetTextHorizontalAlignment
	Description :	Get the horizontal alignment of the text of this 
					element
	Access :		Public

	Return :		long	-	the horizontal alignment of the text 
								of this element
	Parameters :	none
   ============================================================ */
{
	if (GetMainView()) {
		return GetMainView()->GetTextHorizontalAlignment();
	}

	return 0;
}

void CProMoElementAuto::SetTextHorizontalAlignment(long nNewValue) 
/* ============================================================
	Function :		CProMoElementAuto::SetTextHorizontalAlignment
	Description :	Set the horizontal alignment of the text of this 
					element
	Access :		Public

	Return :		void
	Parameters :	long nNewValue	-	the new horizontal alignment 
										of the text of this element
   ============================================================ */
{
	CObArray views;
	GetViews(views);
	
	if (HasLockFlag(LOCK_ALIGNMENT) || !GetModel()) {
		return;
	}

	for (int i = 0; i < views.GetSize(); i++) {
		IProMoView* view = dynamic_cast<IProMoView*>(views.GetAt(i));
		if (view) {
			view->SetTextHorizontalAlignment(nNewValue);
		}
	}
	GetDiagramAutoObject()->NotifyChange();

}

long CProMoElementAuto::GetTextVerticalAlignment() 
/* ============================================================
	Function :		CProMoElementAuto::GetTextVerticalAlignment
	Description :	Get the vertical alignment of the text of this 
					element
	Access :		Public

	Return :		long	-	the vertical alignment of the text 
								of this element
	Parameters :	none
   ============================================================ */
{
	if (GetMainView()) {
		return GetMainView()->GetTextVerticalAlignment();
	}

	return 0;
}

void CProMoElementAuto::SetTextVerticalAlignment(long nNewValue) 
/* ============================================================
	Function :		CProMoElementAuto::SetTextVerticalAlignment
	Description :	Set the vertical alignment of the text of this 
					element
	Access :		Public

	Return :		void
	Parameters :	long nNewValue	-	the new vertical alignment 
										of the text of this element
   ============================================================ */
{
	CObArray views;
	GetViews(views);
	
	if (HasLockFlag(LOCK_ALIGNMENT) || !GetModel()) {
		return;
	}

	for (int i = 0; i < views.GetSize(); i++) {
		IProMoView* view = dynamic_cast<IProMoView*>(views.GetAt(i));
		if (view) {
			view->SetTextVerticalAlignment(nNewValue);
		}
	}
	GetDiagramAutoObject()->NotifyChange();

}

BSTR CProMoElementAuto::GetName() 
/* ============================================================
	Function :		CProMoElementAuto::GetName
	Description :	Get the ID of this element
	Access :		Public

	Return :		BSTR	-	the ID of this element
	Parameters :	none
   ============================================================ */
{
	CString strResult;
	
	if (GetModel()) {
		strResult = GetModel()->GetName();
	}

	return strResult.AllocSysString();
}

void CProMoElementAuto::SetName(LPCTSTR lpszNewValue) 
/* ============================================================
	Function :		CProMoElementAuto::SetName
	Description :	Set the ID of this element. This property 
					is read-only, so this function simply raises 
					an exception.
	Access :		Public
	Return :		void
	Parameters :	LPCTSTR lpszNewValue	-	the new name of this 
												element
   ============================================================ */
{
	SetNotSupported();

}

LPDISPATCH CProMoElementAuto::GetLabels()
/* ============================================================
	Function :		CProMoElementAuto::GetLabels
	Description :	Returns the labels collection automation object.
	Access :		Public
	Return :		LPDISPATCH	-	A dispatch interface to the
									collection of labels in the
									element.
	Parameters :	none
   ============================================================ */
{
	if (GetLabelsAutoObject())
	{
		return GetLabelsAutoObject()->GetIDispatch(TRUE);
	}

	return NULL;
}

void CProMoElementAuto::SetLabels(LPDISPATCH newValue) 
/* ============================================================
	Function :		CProMoElementAuto::SetLabels
	Description :	Sets the labels collection automation object.
					This property is read-only, so this function
					simply raises an exception.
	Access :		Public
	Return :		void
	Parameters :	LPDISPATCH newValue	-	A dispatch interface to the
											new collection of labels in
											the element (not supported).
   ============================================================ */
{
	SetNotSupported();

}

LPDISPATCH CProMoElementAuto::GetProperties() 
/* ============================================================
	Function :		CProMoElementAuto::GetProperties
	Description :	Returns the properties collection automation object.
	Access :		Public
	Return :		LPDISPATCH	-	A dispatch interface to the
									collection of properties in the
									element.
	Parameters :	none
   ============================================================ */
{
	if (GetPropertiesAutoObject())
	{
		return GetPropertiesAutoObject()->GetIDispatch(TRUE);
	}

	return NULL;
}

void CProMoElementAuto::SetProperties(LPDISPATCH newValue) 
/* ============================================================
	Function :		CProMoElementAuto::SetProperties
	Description :	Sets the properties collection automation object.
					This property is read-only, so this function
					simply raises an exception.
	Access :		Public
	Return :		void
	Parameters :	LPDISPATCH newValue	-	A dispatch interface to the
											new collection of properties in
											the element (not supported).
   ============================================================ */
{
	SetNotSupported();

}

BSTR CProMoElementAuto::GetType()
/****************************************************
	Function :		CProMoElementAuto::GetType
	Description :	Get the type of this element
	Access :		Public

	Return :		BSTR	-	the type of this element
	Parameters :	none
   ============================================================ */
{
	CString strResult;

	CDiagramEntity* pEntity = dynamic_cast<CDiagramEntity*>(GetMainView());

	if (pEntity) {
		strResult = pEntity->GetType();
	}
	
	return strResult.AllocSysString();
}

void CProMoElementAuto::SetType(LPCTSTR lpszNewValue) 
/* ============================================================
	Function :		CProMoElementAuto::SetType
	Description :	Set the type of this element. This property is 
					read-only, so this function simply raises an 
					exception.
	Access :		Public
	Return :		void
	Parameters :	LPCTSTR lpszNewValue	-	the new type of this 
												element
   ============================================================ */
{
	SetNotSupported();

}

short CProMoElementAuto::GetLockFlags()
/* ============================================================
	Function :		CProMoElementAuto::GetLockFlags
	Description :	Get the lock flags for this element
	Access :		Public

	Return :		short	-	the lock flags for this element
	Parameters :	none
   ============================================================ */
{
	if (GetMainView()) {
		return GetMainView()->GetLock();
	}

	return 0;
}

void CProMoElementAuto::SetLockFlags(short nNewValue)
/* ============================================================
	Function :		CProMoElementAuto::SetLockFlags
	Description :	Set the lock flags for this element. This 
					property is read-only, so this function simply 
					raises an exception.
	Access :		Public
	Return :		void
	Parameters :	short nNewValue	-	the new lock flags for this 
										element
   ============================================================ */
{
	SetNotSupported();
}
