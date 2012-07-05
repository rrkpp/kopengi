/*
*	CCameraNode.cpp - Regan Russell
*
*	Base camera class for the engine.
*/

#include "kopengi.h"

CCameraNode::CCameraNode()
{
	m_XAngle = 0;
	m_YAngle = 0;
	m_Forward = glm::vec3(0, 0, 0);
	m_Right = glm::vec3(0, 0, 0);
	m_Up = glm::vec3(0, 0, 0);
	m_LastTick = 0;
	m_FOV = 45.0f;
	m_NearZ = 0.1f;
	m_FarZ = 100.0f;
}

CCameraNode::~CCameraNode() {}

void CCameraNode::Tick()
{
	float deltaTime = float(CurTime() - m_LastTick);
	
	m_XAngle += GetGame()->GetInputSystem()->GetMouseSpeed() * GetGame()->GetInputSystem()->GetMouseDX();
	m_YAngle += GetGame()->GetInputSystem()->GetMouseSpeed() * GetGame()->GetInputSystem()->GetMouseDY();
	SetAngles(glm::vec3(m_XAngle, m_YAngle, m_Angles.z));
	
	m_Forward = glm::vec3(cos(m_YAngle) * sin(m_XAngle), sin(m_YAngle), cos(m_YAngle) * cos(m_XAngle));
	m_Right = glm::vec3(sin(m_XAngle - 3.14f / 2.0f), 0, cos(m_XAngle - 3.14f / 2.0f));
	m_Up = glm::cross(m_Right, m_Forward);

	if (GetGame()->GetInputSystem()->GetKey(GLFW_KEY_SPACE) == GLFW_PRESS)
	{
		m_XAngle = 0.0f;
		m_YAngle = 0.0f;
		SetAngles(glm::vec3(0.0f, 0.0f, 0.0f));
	}

	if (GetGame()->GetInputSystem()->GetKey('W') == GLFW_PRESS)
	{
		m_Pos += m_Forward * deltaTime * glm::vec3(5, 5, 5);
	}

	if (GetGame()->GetInputSystem()->GetKey('S') == GLFW_PRESS)
	{
		m_Pos -= m_Forward * deltaTime * glm::vec3(5, 5, 5);
	}

	if (GetGame()->GetInputSystem()->GetKey('D') == GLFW_PRESS)
	{
		m_Pos += m_Right * deltaTime * glm::vec3(5, 5, 5);
	}

	if (GetGame()->GetInputSystem()->GetKey('A') == GLFW_PRESS)
	{
		m_Pos -= m_Right * deltaTime * glm::vec3(5, 5, 5);
	}

	m_LastTick = (float)CurTime();
}

void CCameraNode::SetDirection(glm::vec3 ang)
{
	m_Forward = ang;
	m_Right = glm::vec3(sin(m_XAngle - 3.14f / 2.0f), 0, cos(m_XAngle - 3.14f / 2.0f));
	m_Up = glm::cross(m_Right, m_Forward);
}

glm::vec3 CCameraNode::GetDirection()
{
	return m_Forward;
}

glm::vec3 CCameraNode::GetUp()
{
	return m_Up;
}

glm::vec3 CCameraNode::GetRight()
{
	return m_Right;
}

void CCameraNode::SetFOV(float fov)
{
	m_FOV = fov;
}

float CCameraNode::GetFOV()
{
	return m_FOV;
}

void CCameraNode::SetNearZ(float z)
{
	m_NearZ = z;
}

float CCameraNode::GetNearZ()
{
	return m_NearZ;
}


void CCameraNode::SetFarZ(float z)
{
	m_FarZ = z;
}

float CCameraNode::GetFarZ()
{
	return m_FarZ;
}
