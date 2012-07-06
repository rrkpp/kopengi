/*
*	kopengi.h - Regan Russell
*
*	Global engine header file, includes everything
*	necessary to run the engine.
*/

#ifndef _KOPENGI_H_
#define _KOPENGI_H_

// External Includes
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <vector>
#include <map>
#include <fstream>
#include <iostream>
#include <time.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/matrix_inverse.hpp>
#include <GL/glew.h>
#include <GL/glfw.h>
#include <SOIL.h>
#include <assimp/assimp.hpp>
#include <assimp/aiScene.h>
#include <assimp/aiPostProcess.h>

// Engine Include
#include "CFrameBuffer.h"
#include "GBuffer.h"
#include "ISceneNode.h"
#include "CLight.h"
#include "CLightEnvironment.h"
#include "CPointLight.h"
#include "CLightDirectional.h"
#include "CSpotLight.h"
#include "CShader.h"
#include "CShader_Deferred.h"
#include "CShader_GBuffer.h"
#include "CShader_SSAO.h"
#include "CPostProcessChain.h"
#include "CMaterial.h"
#include "CMesh.h"
#include "CModel.h"
#include "CMeshNode.h"
#include "CCameraNode.h"
#include "IContentSystem.h"
#include "ISceneManager.h"
#include "IRenderSystem.h"
#include "IInputSystem.h"
#include "IGame.h"

// Libraries
#pragma comment(lib, "glew32.lib")
#pragma comment(lib, "GLFW.lib")
#pragma comment(lib, "opengl32.lib")
#pragma comment(lib, "SOIL.lib")
#pragma comment(lib, "assimp.lib")

#define ARRAY_SIZE_IN_ELEMENTS(a) (sizeof(a)/sizeof(a[0]))

static IGame* g_Game = new IGame();

IGame* GetGame(); // Returns pointer to the game object
double CurTime(); // Gets the current game time
float random(float a, float b);
double lerp(double a, double b, double coefficient);

#endif
