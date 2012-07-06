/*
*	IGame.h - Regan Russell
*
*	Engine interface, wraps up all other game systems.
*/

#ifndef _IGAME_H_
#define _IGAME_H_

class IGame
{
public:
	IGame();
	~IGame();

	bool Init(int w, int h, std::string title);

	void SetRenderSystem(IRenderSystem* rs);
	IRenderSystem* GetRenderSystem();

	void SetInputSystem(IInputSystem* is);
	IInputSystem* GetInputSystem();

	void SetSceneManager(ISceneManager* sm);
	ISceneManager* GetSceneManager();

	void SetContentSystem(IContentSystem* cs);
	IContentSystem* GetContentSystem();

	void SetRun(bool b);
	bool Running();

	int GetWindowWidth();
	int GetWindowHeight();

	void UpdateWindow();

private:
	// Engine interfaces
	IRenderSystem* m_RenderSystem;
	IInputSystem* m_InputSystem;
	ISceneManager* m_SceneManager;
	IContentSystem* m_ContentSystem;

	bool m_bRun;
	int m_WindowWidth;
	int m_WindowHeight;
};

#endif
