/* ==========================================================================

	Copyright © 2025 Technical University of Denmark

	Author :		Giovanni Meroni

   ========================================================================*/
#ifndef _PROMOPROPERTYOWNER_H_
#define _PROMOPROPERTYOWNER_H_

class CProMoProperty;

class IProMoPropertyOwner
{
public:
	virtual void OnPropertyChanged(CProMoProperty* prop) = 0;
};

#endif // _PROMOPROPERTYOWNER_H_