#ifndef _PROMOMODEL_H_
#define _PROMOMODEL_H_

#include "../StdAfx.h"
#include "../DiagramEditor/DiagramEntity.h"

class CProMoModel : public CObject
{
public:
	
	CProMoModel();
	virtual ~CProMoModel();
	virtual CProMoModel* Clone();

	virtual void LinkView(CDiagramEntity* view);
	virtual void UnlinkView(CDiagramEntity* view);
	virtual void UnlinkAllViews();
	virtual CObArray* GetViews();

	virtual BOOL	FromString(const CString& str);
	virtual CString	Export(UINT format = 0) const;
	virtual CString	GetString() const;
	static	CProMoModel* CreateFromString(const CString& str);

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

#endif //_PROMOMODEL_H_