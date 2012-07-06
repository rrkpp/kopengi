/*
*	IRenderSystem.cpp - Regan Russell
*
*	Rendering subsystem, handles rendering. What else would it do?
*/

#include "kopengi.h"

IRenderSystem::IRenderSystem()
{
	// Set up OpenGL
	glEnable(GL_CULL_FACE);

	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);
	glBlendFunc(GL_ONE, GL_ONE);

	m_ViewMatrix = glm::mat4(1.0f);
	m_ViewRotMatrix = glm::mat3(1.0f);
	m_ProjectionMatrix = glm::mat4(1.0f);

	m_CurLight = 0;
	m_CurMesh = 0;
	m_CurMaterial = 0;
	m_ReadBuffer = 0;

	// Set up screen quad
	GLfloat fbo_verts[] = {
		-1, -1,
		1, -1,
		1, 1,
		-1, 1,
		-1, -1,
		1, 1
	};

	GLfloat fbo_uvs[] = {
		0, 0,
		1, 0,
		1, 1,
		0, 1,
		0, 0,
		1, 1
	};

	glGenBuffers(1, &m_ScreenQuad);
	glBindBuffer(GL_ARRAY_BUFFER, m_ScreenQuad);
	glBufferData(GL_ARRAY_BUFFER, sizeof(fbo_verts), fbo_verts, GL_STATIC_DRAW);

	glGenBuffers(1, &m_ScreenUVs);
	glBindBuffer(GL_ARRAY_BUFFER, m_ScreenUVs);
	glBufferData(GL_ARRAY_BUFFER, sizeof(fbo_uvs), fbo_uvs, GL_STATIC_DRAW);

	// Set up skybox
	GLfloat sky_verts[] = {
		0.5f, -0.5f, -0.5f,
		-0.5f, -0.5f, -0.5f,
		-0.5f,  0.5f, -0.5f,
		0.5f,  0.5f, -0.5f,
		0.5f, -0.5f,  0.5f,
		0.5f, -0.5f, -0.5f,
		0.5f,  0.5f, -0.5f,
		0.5f,  0.5f,  0.5f,
		-0.5f, -0.5f,  0.5f,
		0.5f, -0.5f,  0.5f,
		0.5f,  0.5f,  0.5f,
		-0.5f,  0.5f,  0.5f,
		-0.5f, -0.5f, -0.5f,
		-0.5f, -0.5f,  0.5f,
		-0.5f,  0.5f,  0.5f,
		-0.5f,  0.5f, -0.5f,
		-0.5f,  0.5f, -0.5f,
		-0.5f,  0.5f,  0.5f,
		0.5f,  0.5f,  0.5f,
		0.5f,  0.5f, -0.5f,
		-0.5f, -0.5f, -0.5f,
		-0.5f, -0.5f,  0.5f,
		0.5f, -0.5f,  0.5f,
		0.5f, -0.5f, -0.5f,
	};

	glGenBuffers(1, &m_SkyboxVerts);
	glBindBuffer(GL_ARRAY_BUFFER, m_SkyboxVerts);
	glBufferData(GL_ARRAY_BUFFER, sizeof(sky_verts), sky_verts, GL_STATIC_DRAW);

	m_GBuffer.Init(GetGame()->GetWindowWidth(), GetGame()->GetWindowHeight());
	m_FBO[0].Init(GetGame()->GetWindowWidth(), GetGame()->GetWindowHeight(), 1);
	m_FBO[1].Init(GetGame()->GetWindowWidth(), GetGame()->GetWindowHeight(), 1);

	LoadShaders();

	m_LightEnv.SetAmbient(glm::vec3(0.3f, 0.3f, 0.3f));
}

IRenderSystem::~IRenderSystem() {}

void IRenderSystem::Draw()
{
	// Set clear color
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	
	// Calculate matrices
	m_ProjectionMatrix = glm::perspective(m_Camera->GetFOV(), float(GetGame()->GetWindowWidth()) / float(GetGame()->GetWindowHeight()), GetCamera()->GetNearZ(), GetCamera()->GetFarZ());
	m_ViewMatrix = glm::lookAt(m_Camera->GetPos(), m_Camera->GetPos() + m_Camera->GetDirection(), m_Camera->GetUp());
	m_ViewRotMatrix = glm::mat3(m_ViewMatrix);

	// Geometry Pass
	SetShader(GetShader("gbuffer"));
	m_GBuffer.BindForWriting();
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	GetGame()->GetSceneManager()->Draw(false);
	m_GBuffer.Unbind();

	// Light Pass
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	RenderPostEffects();

	// Skybox
	//RenderSkybox();

	// Present the frame
	glfwSwapBuffers();
}

void IRenderSystem::LoadShaders()
{
	log(LOG_TYPE_DEFAULT, "--\n");

	CShader* shader = new CShader("shaders/unlit.vs.glsl", "shaders/unlit.ps.glsl");
	m_Shaders["unlit"] = shader;

	shader = new CShader_GBuffer("shaders/gbuffer.vs.glsl", "shaders/gbuffer.ps.glsl");
	m_Shaders["gbuffer"] = shader;

	shader = new CShader_Deferred("shaders/deferred.vs.glsl", "shaders/deferred.ps.glsl");
	m_Shaders["deferred"] = shader;

	shader = new CShader_SSAO("shaders/ssao.vs.glsl", "shaders/ssao.ps.glsl");
	m_Shaders["ssao"] = shader;

	shader = new CShader_SSAO("shaders/ssao_blur.vs.glsl", "shaders/ssao_blur.ps.glsl");
	m_Shaders["ssao_blur"] = shader;

	m_PPChain.AddShader(m_Shaders["deferred"]);
	m_PPChain.AddShader(m_Shaders["ssao"]);
}

CShader* IRenderSystem::GetShader(std::string name)
{
	if (m_Shaders[name] != 0)
	{
		return m_Shaders[name];
	}

	return 0;
}

void IRenderSystem::SetShader(CShader* shader)
{
	m_CurShader = shader;
	shader->Activate();
}

CShader* IRenderSystem::GetCurShader()
{
	return m_CurShader;
}

void IRenderSystem::SetCamera(CCameraNode* cam)
{
	m_Camera = cam;
}

CCameraNode* IRenderSystem::GetCamera()
{
	return m_Camera;
}

void IRenderSystem::SetAmbientLight(glm::vec3 color)
{
	m_LightEnv.SetAmbient(color);
}

glm::vec3 IRenderSystem::GetAmbientLight()
{
	return m_LightEnv.GetAmbient();
}

glm::mat4 IRenderSystem::GetProjectionMatrix()
{
	return m_ProjectionMatrix;
}

glm::mat4 IRenderSystem::GetViewMatrix()
{
	return m_ViewMatrix;
}

glm::mat3 IRenderSystem::GetViewRotMatrix()
{
	return m_ViewRotMatrix;
}

void IRenderSystem::SetCurLight(CLight* light)
{
	m_CurLight = light;
}

CLight* IRenderSystem::GetCurLight()
{
	return m_CurLight;
}

void IRenderSystem::SetCurMesh(CMesh* mesh)
{
	m_CurMesh = mesh;
}

CMesh* IRenderSystem::GetCurMesh()
{
	return m_CurMesh;
}

void IRenderSystem::SetCurMaterial(CMaterial* mat)
{
	m_CurMaterial = mat;
}

CMaterial* IRenderSystem::GetCurMaterial()
{
	return m_CurMaterial;
}

GBuffer* IRenderSystem::GetGBuffer()
{
	return &m_GBuffer;
}

GLuint IRenderSystem::GetScreenQuad()
{
	return m_ScreenQuad;
}

GLuint IRenderSystem::GetScreenUVs()
{
	return m_ScreenUVs;
}

void IRenderSystem::RenderPostEffects()
{
	m_PPChain.Render();
}

void IRenderSystem::RenderSkybox()
{
	// better do this later..
}

CFrameBuffer* IRenderSystem::GetFrameBuffer(unsigned int id)
{
	return &m_FBO[id];
}

void IRenderSystem::SetReadBuffer(CFrameBuffer* buffer)
{
	m_ReadBuffer = buffer;

	if (buffer != 0)
		m_ReadBuffer->BindForReading();
}

CFrameBuffer* IRenderSystem::GetReadBuffer()
{
	return m_ReadBuffer;
}

void IRenderSystem::SetWriteBuffer(CFrameBuffer* buffer)
{
	m_WriteBuffer = buffer;

	if (buffer != 0)
		m_WriteBuffer->BindForWriting();
}

CFrameBuffer* IRenderSystem::GetWriteBuffer()
{
	return m_WriteBuffer;
}
