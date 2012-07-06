/*
*	IInputSystem.cpp - Regan Russell
*
*	Handles player input and stores relevant data.
*/

#include "kopengi.h"

IInputSystem::IInputSystem()
{
	m_MouseSpeed = 0.005f;
	m_MouseX = 0;
	m_MouseY = 0;
	m_MouseDX = 0;
	m_MouseDY = 0;
}

IInputSystem::~IInputSystem() {}

void IInputSystem::Poll()
{
	int mouseX, mouseY;
	glfwGetMousePos(&mouseX, &mouseY);

	m_MouseDX = float(GetGame()->GetWindowWidth() / 2 - mouseX);
	m_MouseDY = float(GetGame()->GetWindowHeight() / 2 - mouseY);

	m_MouseX = mouseX;
	m_MouseY = mouseY;

	mouseX = GetGame()->GetWindowWidth() / 2;
	mouseY = GetGame()->GetWindowHeight() / 2;
	glfwSetMousePos(mouseX, mouseY);
}

int IInputSystem::GetMouseX()
{
	return m_MouseX;
}

int IInputSystem::GetMouseY()
{
	return m_MouseY;
}

float IInputSystem::GetMouseDX()
{
	return m_MouseDX;
}

float IInputSystem::GetMouseDY()
{
	return m_MouseDY;
}

void IInputSystem::SetMouseSpeed(float speed)
{
	m_MouseSpeed = speed;
}

float IInputSystem::GetMouseSpeed()
{
	return m_MouseSpeed;
}

int IInputSystem::GetKey(int key)
{
	return glfwGetKey(key);
}