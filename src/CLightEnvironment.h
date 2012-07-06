/*
*	CLightEnvironment.h - Regan Russell
*
*	Environmental light, contributes environmental ambient.
*/

#ifndef _CLIGHTENVIRONMENT_H_
#define _CLIGHTENVIRONMENT_H_

class CLightEnvironment : public CLight
{
public:
	CLightEnvironment();
	~CLightEnvironment();

	virtual float GetType()
	{
		return LIGHT_TYPE_ENVIRONMENTAL;
	}
};

#endif