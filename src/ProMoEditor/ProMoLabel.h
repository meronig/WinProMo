/* ==========================================================================

	Copyright © 2025 Technical University of Denmark

	Author :		Giovanni Meroni

   ========================================================================*/
#ifndef _PROMOLABEL_H_
#define _PROMOLABEL_H_

#include "../DiagramEditor/DiagramEntity.h"
#include "ProMoModel.h"

class AFX_EXT_CLASS CProMoLabel :
    public CDiagramEntity
{
public:
	friend class CProMoModel;
	
	CProMoLabel();
	virtual ~CProMoLabel();

	virtual CDiagramEntity* Clone();
	virtual void	Copy(CDiagramEntity* obj);

	static	CDiagramEntity* CreateFromString(const CString& str, CProMoModel* model);

	static CString GetModelFromString(const CString& str);
	static CString GetNameFromString(const CString& str);

	virtual CProMoModel* GetModel() const;
	virtual CString GetProperty() const;
	virtual BOOL IsSelectable() const;

protected:
	CProMoModel* m_model;
	CString m_property;
	BOOL m_selectable;

	virtual void SetProperty(const CString& property);
	virtual void Selectable(const BOOL& select);

// Overrides

public:
	static	CDiagramEntity* CreateFromString(const CString& str);

	virtual void Draw(CDC* dc, CRect rect);

	virtual void	ShowPopup(CPoint point, CWnd* parent);

protected:
	virtual CString				GetDefaultGetString() const;
	virtual CString				GetHeaderFromString(CString& str);
	virtual BOOL				GetDefaultFromString(CString& str);

};

#endif //_PROMOBLOCKVIEW_H_