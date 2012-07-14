/*
*	IGame.cpp - Regan Russell
*
*	Engine interface, wraps up all other game systems.
*/

#include "kopengi.h"

IGame::IGame() {}

IGame::~IGame()
{
	delete m_RenderSystem;
	delete m_InputSystem;
	delete m_SceneManager;
	delete m_ContentSystem;
	delete m_LuaInterface;
}

bool IGame::Init(int w, int h, std::string title)
{
	if (!glfwInit())
	{
		log(LOG_TYPE_ERROR, "Failed to initialize GLFW!");
		return false;
	}

	// Set our initialization parameters
	//glfwOpenWindowHint(GLFW_OPENGL_VERSION_MAJOR, 3);
	//glfwOpenWindowHint(GLFW_OPENGL_VERSION_MINOR, 1);
	//glfwOpenWindowHint(GLFW_OPENGL_PROFILE, 0);

	m_WindowWidth = w;
	m_WindowHeight = h;
	
	if (!glfwOpenWindow(m_WindowWidth, m_WindowHeight, 0, 0, 0, 0, 24, 0, GLFW_WINDOW))
	{
		log(LOG_TYPE_ERROR, "Failed to create window!");
		glfwTerminate();
		return false;
	}

	if (glewInit() != GLEW_OK)
	{
		log(LOG_TYPE_ERROR, "Failed to initialize GLEW!");
		return false;
	}

	glfwSetWindowTitle(title.c_str());
	glfwDisable(GLFW_MOUSE_CURSOR);

	// Clear log.txt
	std::ofstream logFile("log.txt");
	logFile << " " << std::endl;
	logFile.close();

	log(LOG_TYPE_DEFAULT, "OpenGL successfully initialized..");
		
	DetectHardware();

	m_LuaInterface = new ILuaInterface();
	m_SceneManager = new ISceneManager();
	m_RenderSystem = new IRenderSystem();
	m_InputSystem = new IInputSystem();
	m_ContentSystem = new IContentSystem();

	//temp
	//m_LuaInterface->LoadScript("lua/lib/kopengi.lua");

	m_bRun = true;

	return true;
}

void IGame::SetRenderSystem(IRenderSystem* rs)
{
	m_RenderSystem = rs;
}

IRenderSystem* IGame::GetRenderSystem()
{
	return m_RenderSystem;
}

void IGame::SetInputSystem(IInputSystem* is)
{
	m_InputSystem = is;
}

IInputSystem* IGame::GetInputSystem()
{
	return m_InputSystem;
}

void IGame::SetSceneManager(ISceneManager* sm)
{
	m_SceneManager = sm;
}

ISceneManager* IGame::GetSceneManager()
{
	return m_SceneManager;
}

void IGame::SetContentSystem(IContentSystem* cs)
{
	m_ContentSystem = cs;
}

IContentSystem* IGame::GetContentSystem()
{
	return m_ContentSystem;
}

void IGame::SetLuaInterface(ILuaInterface* lua)
{
	m_LuaInterface = lua;
}

ILuaInterface* IGame::GetLuaInterface()
{
	return m_LuaInterface;
}

void IGame::SetRun(bool b)
{
	m_bRun = b;
}

bool IGame::Running()
{
	return m_bRun;
}

int IGame::GetWindowWidth()
{
	return m_WindowWidth;
}

int IGame::GetWindowHeight()
{
	return m_WindowHeight;
}

void IGame::UpdateWindow()
{
	if (!glfwGetWindowParam(GLFW_OPENED))
	{
		log(LOG_TYPE_DEFAULT, "\n");
		log(LOG_TYPE_DEFAULT, "Window closed, engine shutting down..");
		SetRun(false);
		return;
	}
}

void IGame::SetConfig(CConfig config)
{
	m_Config = config;
}

CConfig* IGame::GetConfig()
{
	return &m_Config;
}

void IGame::DetectHardware()
{
	// Output OpenGL / GLSL information
	std::string glVersion = std::string((char*)glGetString(GL_VERSION));
	std::string glslVersion = std::string((char*)glGetString(GL_SHADING_LANGUAGE_VERSION));
	log(LOG_TYPE_DEFAULT, "OpenGL Version: " + glVersion);
	log(LOG_TYPE_DEFAULT, "GLSL Version: " + glslVersion);

	m_Config.OpenGLVersion = atof((glVersion.substr(0, 3)).c_str());
	m_Config.GLSLVersion = atof((glslVersion.substr(0, 3)).c_str());
}

float IGame::GetGLVersion()
{
	return m_Config.OpenGLVersion;
}

float IGame::GetGLSLVersion()
{
	return m_Config.GLSLVersion;
}

float IGame::GetMinGLVersion()
{
	return 3.0;
}

float IGame::GetMinGLSLVersion()
{
	return 1.3;
}
