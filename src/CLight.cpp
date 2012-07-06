/*
*	CLight.h - Regan Russell
*
*	Base light node, not to be used directly.
*/

#include "kopengi.h"

CLight::CLight()
	: ISceneNode(false)
{
	m_Diffuse = glm::vec3(1.0, 1.0, 1.0);
	m_Ambient = glm::vec3(0.0, 0.0, 0.0);
	m_Specular = glm::vec3(0.0, 0.0, 0.0);
	m_LightPower = 1.0f;
	m_Enabled = true;
	m_Distance = 512.0f;

	GetGame()->GetSceneManager()->AddLight(this);
}

CLight::~CLight() {}

void CLight::Enable()
{
	m_Enabled = true;
}

void CLight::Disable()
{
	m_Enabled = false;
}

bool CLight::Enabled()
{
	return m_Enabled;
}

void CLight::SetDiffuse(glm::vec3 color)
{
	m_Diffuse = color;
}

glm::vec3 CLight::GetDiffuse()
{
	return m_Diffuse;
}

void CLight::SetAmbient(glm::vec3 color)
{
	m_Ambient = color;
}

glm::vec3 CLight::GetAmbient()
{
	return m_Ambient;
}

void CLight::SetSpecular(glm::vec3 color)
{
	m_Specular = color;
}

glm::vec3 CLight::GetSpecular()
{
	return m_Specular;
}

void CLight::SetPower(float power)
{
	m_LightPower = power;
}

float CLight::GetPower()
{
	return m_LightPower;
}

void CLight::SetDistance(float dist)
{
	m_Distance = dist;
}

float CLight::GetDistance()
{
	return m_Distance;
}