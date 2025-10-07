/* ==========================================================================

	Copyright © 2025 Technical University of Denmark

	Author :		Giovanni Meroni

   ========================================================================*/
#ifndef _PROMOMODEL_H_
#define _PROMOMODEL_H_

#include "../StdAfx.h"
#include "../DiagramEditor/DiagramEntity.h"
//#include "ProMoLabel.h"

class AFX_EXT_CLASS CProMoLabel;

class AFX_EXT_CLASS CProMoModel : public CObject
{
public:
	friend class CProMoLabel;

	// Creation/initialization
	CProMoModel();
	virtual ~CProMoModel();
	
	virtual CProMoModel* Clone();
	virtual void	Copy(CProMoModel* obj);


	// Model-view links
	virtual CObArray* GetViews();

	virtual BOOL	FromString(const CString& str);
	virtual CString	Export(UINT format = 0) const;
	virtual CString	GetString() const;
	static	CProMoModel* CreateFromString(const CString& str);

	BOOL			LoadFromString(CString& data);

	// Properties
	CString			GetType() const;
	void			SetType(CString type);

	virtual CString	GetName() const;
	virtual void	SetName(CString name);

	static CString GetNameFromString(const CString& str);

	virtual CObArray* GetLabels();
	virtual CProMoLabel* GetLabel(CString property);
	virtual CObArray* RecreateLabels();
	

protected:
	CObArray m_views;
	CObArray m_labels;

	virtual CString				GetDefaultGetString() const;
	virtual CString				GetHeaderFromString(CString& str);
	virtual BOOL				GetDefaultFromString(CString& str);

	virtual void LinkView(CDiagramEntity* view);
	virtual void UnlinkView(CDiagramEntity* view);
	virtual void UnlinkAllViews();
	virtual void LinkLabel(CProMoLabel* label);
	virtual void UnlinkLabel(CProMoLabel* label);
	virtual void UnlinkAllLabels();

	

private:
	CString m_type;
	CString m_name;


};

#endif //_PROMOMODEL_H_