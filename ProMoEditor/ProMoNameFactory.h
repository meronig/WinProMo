#if !defined(_PROMONAMEFACTORY_H_)
#define _PROMONAMEFACTORY_H_

class CProMoNameFactory
{

public:
// Implementation
	static CString GetID();

private:
// Private data
	static int s_currentID;

};


#endif // _PROMONAMEFACTORY_H_
