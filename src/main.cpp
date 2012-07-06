/*
*	main.cpp - Regan Russell
*
*	Entry point for the application
*/

#include "kopengi.h"

int main(int argc, char **argv)
{
	if (GetGame()->Init(1280, 720, "kopengi"))
	{
		CCameraNode cam;
		cam.SetPos(glm::vec3(0, 0, -5));
		GetGame()->GetRenderSystem()->SetCamera(&cam);
		
		CModel* sceneMesh;
		sceneMesh = GetGame()->GetContentSystem()->GetModel("mirrorsedge.obj");
		
		CMeshNode scene;
		scene.SetModel(sceneMesh);
		scene.SetScale(glm::vec3(0.01f, 0.01f, 0.01f));

		CLightDirectional dir1;
		dir1.SetDirection(glm::vec3(0.0f, 1.0f, 1.0f));
		dir1.SetDiffuse(glm::vec3(1.0f, 1.0f, 1.0f));

		// Main loop
		while (GetGame()->Running())
		{
			GetGame()->UpdateWindow();
			GetGame()->GetInputSystem()->Poll();
			GetGame()->GetSceneManager()->Tick();
			GetGame()->GetRenderSystem()->Draw();
		}
	}
	else
	{
		log(LOG_TYPE_ERROR, "Engine initialization failed!");
	}

	return 0;
}
