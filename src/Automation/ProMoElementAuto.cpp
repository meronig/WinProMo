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
{
	m_pLabels = NULL;
	m_pProperties = NULL;
}

CProMoModel* CProMoElementAuto::GetModel()
{
	ThrowIfDetached();
	ThrowIfNoDiagramAutoObject();

	return dynamic_cast<CProMoModel*>(m_pInternalObject);
}

void CProMoElementAuto::GetViews(CObArray& viewList)
{
	viewList.RemoveAll();

	if (GetModel()) {
		GetModel()->GetViews(viewList);
	}
}

IProMoView* CProMoElementAuto::GetMainView()
{
	CObArray viewList;
	GetViews(viewList);
	if (viewList.GetSize() > 0) {
		return dynamic_cast<IProMoView*>(viewList.GetAt(0));
	}
	return NULL;
}

void CProMoElementAuto::GetAttachedLabels(CObArray& labelList)
{
	labelList.RemoveAll();
	if (GetModel()) {
		GetModel()->GetLabels(labelList);
	}
}

CProMoElementAuto::~CProMoElementAuto()
{
}

CProMoLabelsAuto* CProMoElementAuto::GetLabelsAutoObject()
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
{
	if (m_pLabels) {
		m_pLabels->SetElementAutoObject(NULL);
		m_pLabels->GetIDispatch(FALSE)->Release();
		m_pLabels = NULL;
	}
}

CProMoPropertiesAuto* CProMoElementAuto::GetPropertiesAutoObject()
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
{
	if (m_pProperties) {
		m_pProperties->SetElementAutoObject(NULL);
		m_pProperties->GetIDispatch(FALSE)->Release();
		m_pProperties = NULL;
	}
}

void CProMoElementAuto::DeleteViewsAndLabels()
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
{
	// When the last reference for an automation object is released
	// OnFinalRelease is called.  The base class will automatically
	// deletes the object.  Add additional cleanup required for your
	// object before calling the base class.
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
{
	if (GetModel()) {
		Select();
		GetContainer()->CopyAllSelected();
	}
}

void CProMoElementAuto::Cut() 
{
	if (GetModel()) {
		GetContainer()->Snapshot();
		Copy();
		GetContainer()->RemoveAllSelected();
		GetDiagramAutoObject()->NotifyChange();
	}
}

void CProMoElementAuto::Delete() 
{
	DeleteViewsAndLabels();
}

LPDISPATCH CProMoElementAuto::Duplicate() 
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
{
	if (GetMainView()) {
		COLORREF color = GetMainView()->GetLineColor();
		return RGB(GetRValue(color), GetGValue(color), GetBValue(color));
	}

	return RGB(0,0,0);
}

void CProMoElementAuto::SetLineColor(OLE_COLOR nNewValue) 
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
{
	if (GetMainView()) {
		return GetMainView()->GetLineWidth();
	}

	return 0;
}

void CProMoElementAuto::SetLineWidth(short nNewValue) 
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

short CProMoElementAuto::GetLineStyle() 
{
	if (GetMainView()) {
		return GetMainView()->GetLineStyle();
	}

	return 0;
}

void CProMoElementAuto::SetLineStyle(short nNewValue) 
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
{
	CString strResult;

	if (GetMainView()) {
		strResult = GetMainView()->GetFontName();
	}

	return strResult.AllocSysString();
}

void CProMoElementAuto::SetFontName(LPCTSTR lpszNewValue) 
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
{
	if (GetMainView()) {
		return GetMainView()->GetFontSize();
	}

	return 0;
}

void CProMoElementAuto::SetFontSize(short nNewValue) 
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
{
	if (GetMainView()) {
		return GetMainView()->GetFontWeight();
	}

	return 0;
}

void CProMoElementAuto::SetFontWeight(short nNewValue) 
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
{
	if (GetMainView()) {
		return GetMainView()->IsFontItalic();
	}

	return TRUE;
}

void CProMoElementAuto::SetFontItalic(BOOL bNewValue) 
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
{
	if (GetMainView()) {
		return GetMainView()->IsFontUnderline();
	}

	return TRUE;
}

void CProMoElementAuto::SetFontUnderline(BOOL bNewValue) 
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
{
	if (GetMainView()) {
		return GetMainView()->IsFontStrikeOut();
	}

	return TRUE;
}

void CProMoElementAuto::SetFontStrikeOut(BOOL bNewValue) 
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
{
	if (GetMainView()) {
		COLORREF color = GetMainView()->GetTextColor();
		return RGB(GetRValue(color), GetGValue(color), GetBValue(color));
	}

	return RGB(0,0,0);
}

void CProMoElementAuto::SetTextColor(OLE_COLOR nNewValue) 
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
{
	if (GetMainView()) {
		COLORREF color = GetMainView()->GetBkColor();
		return RGB(GetRValue(color), GetGValue(color), GetBValue(color));
	}

	return RGB(0,0,0);
}

void CProMoElementAuto::SetBkColor(OLE_COLOR nNewValue) 
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

short CProMoElementAuto::GetBkMode() 
{
	if (GetMainView()) {
		return GetMainView()->GetBkMode();
	}

	return 0;
}

void CProMoElementAuto::SetBkMode(short nNewValue) 
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
{
	if (GetMainView()) {
		return GetMainView()->IsTextMultiline();
	}

	return FALSE;
}

void CProMoElementAuto::SetTextMultiLine(BOOL bNewValue)
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

short CProMoElementAuto::GetTextHorizontalAlignment() 
{
	if (GetMainView()) {
		return GetMainView()->GetTextHorizontalAlignment();
	}

	return 0;
}

void CProMoElementAuto::SetTextHorizontalAlignment(short nNewValue) 
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

short CProMoElementAuto::GetTextVerticalAlignment() 
{
	if (GetMainView()) {
		return GetMainView()->GetTextVerticalAlignment();
	}

	return 0;
}

void CProMoElementAuto::SetTextVerticalAlignment(short nNewValue) 
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
{
	CString strResult;
	
	if (GetModel()) {
		strResult = GetModel()->GetName();
	}

	return strResult.AllocSysString();
}

void CProMoElementAuto::SetName(LPCTSTR lpszNewValue) 
{
	SetNotSupported();

}

LPDISPATCH CProMoElementAuto::GetLabels() 
{
	if (GetLabelsAutoObject())
	{
		return GetLabelsAutoObject()->GetIDispatch(TRUE);
	}

	return NULL;
}

void CProMoElementAuto::SetLabels(LPDISPATCH newValue) 
{
	SetNotSupported();

}

LPDISPATCH CProMoElementAuto::GetProperties() 
{
	if (GetPropertiesAutoObject())
	{
		return GetPropertiesAutoObject()->GetIDispatch(TRUE);
	}

	return NULL;
}

void CProMoElementAuto::SetProperties(LPDISPATCH newValue) 
{
	SetNotSupported();

}

BSTR CProMoElementAuto::GetType() 
{
	CString strResult;

	CDiagramEntity* pEntity = dynamic_cast<CDiagramEntity*>(GetMainView());

	if (pEntity) {
		strResult = pEntity->GetType();
	}
	
	return strResult.AllocSysString();
}

void CProMoElementAuto::SetType(LPCTSTR lpszNewValue) 
{
	SetNotSupported();

}

short CProMoElementAuto::GetLockFlags()
{
	if (GetMainView()) {
		return GetMainView()->GetLock();
	}

	return 0;
}

void CProMoElementAuto::SetLockFlags(short nNewValue)
{
	SetNotSupported();
}
