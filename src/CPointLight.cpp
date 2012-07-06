/*
*	CPointLight.cpp - Regan Russell
*
*	Directional light node, casts from everywhere in one direction.
*/

#include "kopengi.h"

CPointLight::CPointLight()
{
	m_ConstantAtt = 1.0f;
	m_LinearAtt = 0.2f;
	m_QuadraticAtt = 0.08f;
}

CPointLight::~CPointLight() {}

void CPointLight::SetAttenuation(float c, float l, float q)
{
	m_ConstantAtt = c;
	m_LinearAtt = l;
	m_QuadraticAtt = q;
}

void CPointLight::SetConstantAtt(float c)
{
	m_ConstantAtt = c;
}

float CPointLight::GetConstantAtt()
{
	return m_ConstantAtt;
}

void CPointLight::SetLinearAtt(float l)
{
	m_LinearAtt = l;
}

float CPointLight::GetLinearAtt()
{
	return m_LinearAtt;
}

void CPointLight::SetQuadraticAtt(float q)
{
	m_QuadraticAtt = q;
}

float CPointLight::GetQuadraticAtt()
{
	return m_QuadraticAtt;
}

float CPointLight::GetType()
{
	return LIGHT_TYPE_POINT;
}