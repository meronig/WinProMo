/* ==========================================================================

	Copyright © 2025 Technical University of Denmark

	Author :		Giovanni Meroni

   ========================================================================*/
#if !defined(_PROMONAMEFACTORY_H_)
#define _PROMONAMEFACTORY_H_

class AFX_EXT_CLASS CProMoNameFactory
{

public:
// Implementation
	static CString GetID();

private:
// Private data
	static int s_currentID;

};


#endif // _PROMONAMEFACTORY_H_
