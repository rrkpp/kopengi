/*
*	kopengi.cpp - Regan Russell
*
*	Global engine code
*/

#include "kopengi.h"

IGame* GetGame()
{
	return g_Game;
}

double CurTime()
{
	return glfwGetTime();
}

// credit: John @ stackoverflow.com
float random(float a, float b)
{
	return ((b - a) * ((float)rand() / RAND_MAX)) + a;
}

// credit: Hermit @ forums.codeguru.com
double lerp(double a, double b, double coefficient)
{
    return a + coefficient * (b - a);
}