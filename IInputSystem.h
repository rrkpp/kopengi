/*
*	IInputSystem.h - Regan Russell
*
*	Handles player input and stores relevant data.
*/

#ifndef _IINPUTSYSTEM_H_
#define _IINPUTSYSTEM_H_

class IInputSystem
{
public:
	IInputSystem();
	~IInputSystem();

	void Poll();

	int GetMouseX();
	int GetMouseY();

	float GetMouseDX();
	float GetMouseDY();

	void SetMouseSpeed(float speed);
	float GetMouseSpeed();

	int GetKey(int key);

private:
	float m_MouseSpeed;
	int m_MouseX;
	int m_MouseY;
	float m_MouseDX;
	float m_MouseDY;
};

#endif