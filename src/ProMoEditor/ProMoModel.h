/* ==========================================================================

	Copyright © 2025 Technical University of Denmark

	Author :		Giovanni Meroni

   ========================================================================*/
#ifndef _PROMOMODEL_H_
#define _PROMOMODEL_H_

#include "../StdAfx.h"
#include "../DiagramEditor/DiagramEntity.h"

class AFX_EXT_CLASS CProMoModel : public CObject
{
public:
	
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


protected:
	CObArray m_views;

	virtual CString				GetDefaultGetString() const;
	virtual CString				GetHeaderFromString(CString& str);
	virtual BOOL				GetDefaultFromString(CString& str);

	virtual void LinkView(CDiagramEntity* view);
	virtual void UnlinkView(CDiagramEntity* view);
	virtual void UnlinkAllViews();


private:
	CString m_type;
	CString m_name;


};

#endif //_PROMOMODEL_H_