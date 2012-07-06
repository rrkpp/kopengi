/*
*	CLightDirectional.cpp - Regan Russell
*
*	Directional light node, casts from everywhere in one direction.
*/

#include "kopengi.h"

CLightDirectional::CLightDirectional() {}

CLightDirectional::~CLightDirectional() {}

void CLightDirectional::SetDirection(glm::vec3 direction)
{
	m_Pos = direction;
}

glm::vec3 CLightDirectional::GetDirection()
{
	return m_Pos;
}

float CLightDirectional::GetType()
{
	return LIGHT_TYPE_DIRECTIONAL;
}

glm::vec4 CLightDirectional::GetViewSpacePos()
{
	return GetGame()->GetRenderSystem()->GetViewMatrix() * glm::vec4(GetPosAbsolute().x, GetPosAbsolute().y, GetPosAbsolute().z, 0.0);
}