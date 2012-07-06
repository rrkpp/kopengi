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
}

bool IGame::Init(int w, int h, std::string title)
{
	if (!glfwInit())
	{
		std::cout << "ERROR: Failed to initialize GLFW!" << std::endl;
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
		std::cout << "ERROR: Failed to create window!" << std::endl;
		glfwTerminate();
		return false;
	}

	if (glewInit() != GLEW_OK)
	{
		std::cout << "ERROR: Failed to initialize GLEW!" << std::endl;
		return false;
	}

	glfwSetWindowTitle(title.c_str());
	glfwDisable(GLFW_MOUSE_CURSOR);
	
	srand(time(NULL));

	m_SceneManager = new ISceneManager();
	m_RenderSystem = new IRenderSystem();
	m_InputSystem = new IInputSystem();
	m_ContentSystem = new IContentSystem();

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
		std::cout << "Window closed, terminating.." << std::endl;
		SetRun(false);
		return;
	}
}
