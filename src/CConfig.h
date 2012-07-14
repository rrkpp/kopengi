/*
*	CConfig.h - Regan Russell
*
*	Config struct for holding game configuration data.
*/

#ifndef _CCONFIG_H_
#define _CCONFIG_H_

struct CConfig
{
	CConfig ()
	{
		WindowWidth = 800;
		WindowHeight = 600;
		WindowTitle = "kopengi";
		OpenGLVersion = 0;
		GLSLVersion = 0;
	}

	int WindowWidth;
	int WindowHeight;
	std::string WindowTitle;
	float OpenGLVersion;
	float GLSLVersion;
};

#endif
