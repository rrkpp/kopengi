/*
*	CSpotLight.h - Regan Russell
*
*	Spot light node.
*/

#ifndef _CSPOTLIGHT_H_
#define _CSPOTLIGHT_H_

class CSpotLight : public CLight
{
public:
	CSpotLight();
	~CSpotLight();

	void SetSpotCutoff(float cutoff);
	float GetSpotCutoff();
	void SetSpotExponent(float exponent);
	float GetSpotExponent();
	void SetAttenuation(float c, float l, float q);
	void SetConstantAtt(float c);
	float GetConstantAtt();
	void SetLinearAtt(float l);
	float GetLinearAtt();
	void SetQuadraticAtt(float q);
	float GetQuadraticAtt();

	float GetType();

private:
	float m_Cutoff;
	float m_Exponent;
	float m_ConstantAtt;
	float m_LinearAtt;
	float m_QuadraticAtt;
};

#endif