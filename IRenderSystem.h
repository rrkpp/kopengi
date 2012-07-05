/*
*	IRenderSystem.h - Regan Russell
*
*	Rendering subsystem, handles rendering. What else would it do?
*/

#ifndef _IRENDERSYSTEM_H_
#define _IRENDERSYSTEM_H_

class IRenderSystem
{
public:
	IRenderSystem();
	~IRenderSystem();

	void Draw();

	void LoadShaders();
	CShader* GetShader(std::string path);

	void SetShader(CShader* shader);
	CShader* GetCurShader();

	void SetCamera(CCameraNode* cam);
	CCameraNode* GetCamera();

	void SetAmbientLight(glm::vec3 color);
	glm::vec3 GetAmbientLight();

	glm::mat4 GetProjectionMatrix();
	glm::mat4 GetViewMatrix();
	glm::mat3 GetViewRotMatrix();

	void SetCurLight(CLight* light);
	CLight* GetCurLight();

	void SetCurMesh(CMesh* mesh);
	CMesh* GetCurMesh();

	void SetCurMaterial(CMaterial* mat);
	CMaterial* GetCurMaterial();

	GBuffer* GetGBuffer();

	GLuint GetScreenQuad();
	GLuint GetScreenUVs();

	void RenderPostEffects();
	void RenderSkybox();

	CFrameBuffer* GetFrameBuffer(unsigned int id);

	void SetReadBuffer(CFrameBuffer* buffer);
	CFrameBuffer* GetReadBuffer();

	void SetWriteBuffer(CFrameBuffer* buffer);
	CFrameBuffer* GetWriteBuffer();

private:
	glm::mat4 m_ProjectionMatrix;
	glm::mat4 m_ViewMatrix;
	glm::mat3 m_ViewRotMatrix;
	CCameraNode* m_Camera;
	std::map<std::string, CShader*> m_Shaders;
	CLightEnvironment m_LightEnv;
	CShader* m_CurShader;
	GBuffer m_GBuffer;
	GLuint m_ScreenQuad;
	GLuint m_ScreenUVs;
	CLight* m_CurLight;
	CMesh* m_CurMesh;
	CMaterial* m_CurMaterial;
	CPostProcessChain m_PPChain;
	CFrameBuffer m_FBO[2];
	CFrameBuffer* m_ReadBuffer;
	CFrameBuffer* m_WriteBuffer;
	GLuint m_SkyboxVerts;
};

#endif