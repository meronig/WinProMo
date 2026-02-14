/* ==========================================================================

	Copyright © 2026 Technical University of Denmark

	Author :		Giovanni Meroni

   ========================================================================*/
#ifndef _PROMOAUTOMATIONHOST_H_
#define _PROMOAUTOMATIONHOST_H_

class CProMoAppChildAuto;

class IProMoAutomationHost
{
protected:
    virtual ~IProMoAutomationHost() {}

public:
    virtual CProMoAppChildAuto* GetAutomationObject() = 0;
	virtual void ReleaseAutomationObject() = 0;
};

#endif // _PROMOAUTOMATIONHOST_H_
