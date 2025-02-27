#ifndef _PROCESSMODEL_H_
#define _PROCESSMODEL_H_

#include "../StdAfx.h"
#include "../DiagramEditor/DiagramEntity.h"

class CProcessModel : public CObject
{
public:
	virtual void linkView(CDiagramEntity* view);
	virtual void unlinkView(CDiagramEntity* view);
	virtual void unlinkViews();
	virtual CObArray* getViews();

	virtual BOOL	FromString(const CString& str);
	virtual CString	Export(UINT format = 0) const;
	virtual CString	GetString() const;
	static	CProcessModel* CreateFromString(const CString& str);

	BOOL			LoadFromString(CString& data);

	CString			GetType() const;
	void			SetType(CString type);

	virtual CString	GetName() const;
	virtual void	SetName(CString name);


protected:
	CObArray m_views;

	virtual CString				GetDefaultGetString() const;
	virtual CString				GetHeaderFromString(CString& str);
	virtual BOOL				GetDefaultFromString(CString& str);

private:
	CString m_type;
	CString m_name;


};

#endif //_PROCESSMODEL_H_