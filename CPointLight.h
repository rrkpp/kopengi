/*
*	CPointLight.h - Regan Russell
*
*	Directional light node, casts from everywhere in one direction.
*/

#ifndef _CPOINTLIGHT_H_
#define _CPOINTLIGHT_H_

class CPointLight : public CLight
{
public:
	CPointLight();
	~CPointLight();

	void SetAttenuation(float c, float l, float q);
	void SetConstantAtt(float c);
	float GetConstantAtt();
	void SetLinearAtt(float l);
	float GetLinearAtt();
	void SetQuadraticAtt(float q);
	float GetQuadraticAtt();

	float GetType();

private:
	float m_ConstantAtt;
	float m_LinearAtt;
	float m_QuadraticAtt;
};

#endif