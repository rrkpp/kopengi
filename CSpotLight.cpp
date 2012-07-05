/*
*	CSpotLight.cpp - Regan Russell
*
*	Spot light node.
*/

#include "kopengi.h"

CSpotLight::CSpotLight()
{
	m_Cutoff = 0.9;
	m_Exponent = 1.0;
	m_ConstantAtt = 1.0f;
	m_LinearAtt = 0.2f;
	m_QuadraticAtt = 0.08f;
}

CSpotLight::~CSpotLight() {}

void CSpotLight::SetSpotCutoff(float cutoff)
{
	m_Cutoff = cutoff;
}

float CSpotLight::GetSpotCutoff()
{
	return m_Cutoff;
}

void CSpotLight::SetSpotExponent(float exponent)
{
	m_Exponent = exponent;
}

float CSpotLight::GetSpotExponent()
{
	return m_Exponent;
}

void CSpotLight::SetAttenuation(float c, float l, float q)
{
	m_ConstantAtt = c;
	m_LinearAtt = l;
	m_QuadraticAtt = q;
}

void CSpotLight::SetConstantAtt(float c)
{
	m_ConstantAtt = c;
}

float CSpotLight::GetConstantAtt()
{
	return m_ConstantAtt;
}

void CSpotLight::SetLinearAtt(float l)
{
	m_LinearAtt = l;
}

float CSpotLight::GetLinearAtt()
{
	return m_LinearAtt;
}

void CSpotLight::SetQuadraticAtt(float q)
{
	m_QuadraticAtt = q;
}

float CSpotLight::GetQuadraticAtt()
{
	return m_QuadraticAtt;
}

float CSpotLight::GetType()
{
	return LIGHT_TYPE_SPOT;
}