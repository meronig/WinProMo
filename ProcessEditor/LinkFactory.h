#if !defined(_LINKFACTORY_H_)
#define _LINKFACTORY_H_

class CLinkFactory
{

public:
// Implementation
	static CString GetID();

private:
// Private data
	static int s_currentID;

};


#endif // !defined(_LINKFACTORY_H_)
