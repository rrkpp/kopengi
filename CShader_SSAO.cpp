/*
*	CShader_SSAO.cpp - Regan Russell
*
*	SSAO shader based on Crytek implementation.
*/

#include "kopengi.h"

CShader_SSAO::CShader_SSAO(std::string vs_path, std::string ps_path)
	: CShader(vs_path, ps_path)
{
	m_KernelSize = 32;
	m_NoiseSize = 4;

	// Generate kernel
	m_Kernel = new GLfloat[m_KernelSize * 3];
	for (unsigned int i = 0; i < m_KernelSize * 3; i += 3)
	{
		glm::vec3 kern = glm::vec3(random(-1.0f, 1.0f), random(-1.0f, 1.0f), random(0.0f, 1.0f));
		glm::normalize(kern);
		kern *= random(0.0f, 1.0f);

		float scale = float(i) / float(m_KernelSize * 3);
		scale = lerp(0.1f, 1.0f, scale * scale);
		kern *= scale;

		m_Kernel[i] = kern.x;
		m_Kernel[i + 1] = kern.y;
		m_Kernel[i + 2] = kern.z;
		//std::cout << "Kernel: " << kern.x << ", " << kern.y << ", " << kern.z << std::endl;
	}

	// Generate noise
	glm::vec3* noise = new glm::vec3[m_NoiseSize * m_NoiseSize]; 
	for (unsigned int i = 0; i < m_NoiseSize * m_NoiseSize; i++)
	{
		noise[i] = glm::vec3(random(-1.0f, 1.0f), random(-1.0f, 1.0f), 0.0f);
		glm::normalize(noise[i]);
		//std::cout << "Noise: " << noise[i].x << ", " << noise[i].y << ", " << noise[i].z << std::endl;
	}

	// Create noise texture
	glGenTextures(1, &m_NoiseTexture);
	glBindTexture(GL_TEXTURE_2D, m_NoiseTexture);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB8, m_NoiseSize, m_NoiseSize, 0, GL_RGB, GL_FLOAT, noise);

	// Create our extra buffer
	m_SSAO_Buffer.Init(GetGame()->GetWindowWidth(), GetGame()->GetWindowHeight(), 1);

	m_ReadBuffer = 0;
	m_WriteBuffer = 0;
}

CShader_SSAO::~CShader_SSAO() {}

void CShader_SSAO::PreLink(GLuint ID) {}

void CShader_SSAO::Activate()
{
	glUseProgram(m_Id);

	GLuint normalID = glGetUniformLocation(m_Id, "fbo_normal");
	if (normalID != -1)
	{
		glActiveTexture(GL_TEXTURE2);
		glBindTexture(GL_TEXTURE_2D, GetGame()->GetRenderSystem()->GetGBuffer()->m_Textures[GBuffer::GBUFFER_TEXTURE_TYPE_NORMAL]);
		glUniform1i(normalID, 2);
		glActiveTexture(GL_TEXTURE0);
	}

	GLuint depthID = glGetUniformLocation(m_Id, "fbo_depth");
	if (depthID != -1)
	{
		glActiveTexture(GL_TEXTURE3);
		glBindTexture(GL_TEXTURE_2D, GetGame()->GetRenderSystem()->GetGBuffer()->m_Textures[GBuffer::GBUFFER_TEXTURE_TYPE_DEPTH]);
		glUniform1i(depthID, 3);
		glActiveTexture(GL_TEXTURE0);
	}

	// Send matrices
	GLuint invProjID = glGetUniformLocation(m_Id, "InverseProjectionMatrix");
	if (invProjID != -1)
		glUniformMatrix4fv(invProjID, 1, GL_FALSE, &glm::inverse(GetGame()->GetRenderSystem()->GetProjectionMatrix())[0][0]);

	GLuint projectionMatrixID = glGetUniformLocation(m_Id, "ProjectionMatrix");
	if (projectionMatrixID != -1)
		glUniformMatrix4fv(projectionMatrixID, 1, GL_FALSE, &GetGame()->GetRenderSystem()->GetProjectionMatrix()[0][0]);

	// Send camdata
	GLuint camFarZ = glGetUniformLocation(m_Id, "camFarZ");
	if (camFarZ != -1)
		glUniform1f(camFarZ, GetGame()->GetRenderSystem()->GetCamera()->GetFarZ());

	// Pass kernel/noise to shader
	GLuint noiseScaleID = glGetUniformLocation(m_Id, "noiseScale");
	if (noiseScaleID != -1)
		glUniform2f(noiseScaleID, GetGame()->GetWindowWidth() / m_NoiseSize, GetGame()->GetWindowHeight() / m_NoiseSize);

	GLuint kernelID = glGetUniformLocation(m_Id, "kernel");
	if (kernelID != -1)
		glUniform3fv(kernelID, m_KernelSize, m_Kernel);

	GLuint noiseID = glGetUniformLocation(m_Id, "noiseTexture");
	if (noiseID != -1)
	{
		glActiveTexture(GL_TEXTURE4);
		glBindTexture(GL_TEXTURE_2D, m_NoiseTexture);
		glUniform1i(noiseID, 4);
		glActiveTexture(GL_TEXTURE0);
	}

	// Store PP buffers
	m_WriteBuffer = GetGame()->GetRenderSystem()->GetWriteBuffer();
	m_ReadBuffer = GetGame()->GetRenderSystem()->GetReadBuffer();
}

void CShader_SSAO::Update()
{
	// Bind the GBuffer
	GLuint diffuseID = glGetUniformLocation(GetGame()->GetRenderSystem()->GetCurShader()->GetID(), "fbo_diffuse");
	if (diffuseID != -1)
	{
		glActiveTexture(GL_TEXTURE1);
		glBindTexture(GL_TEXTURE_2D, GetGame()->GetRenderSystem()->GetReadBuffer()->m_Textures[0]);
		glUniform1i(diffuseID, 1);
		glActiveTexture(GL_TEXTURE0);
	}

	GLuint ssaoID = glGetUniformLocation(GetGame()->GetRenderSystem()->GetCurShader()->GetID(), "fbo_ssao");
	if (ssaoID != -1)
	{
		glActiveTexture(GL_TEXTURE2);
		glBindTexture(GL_TEXTURE_2D, m_SSAO_Buffer.m_Textures[0]);
		glUniform1i(ssaoID, 2);
		glActiveTexture(GL_TEXTURE0);
	}

	// Pass kernel/noise to shader
	GLuint texelSizeID = glGetUniformLocation(GetGame()->GetRenderSystem()->GetCurShader()->GetID(), "texelSize");
	if (texelSizeID != -1)
		glUniform2f(texelSizeID, 1.0f / (float)GetGame()->GetWindowWidth(), 1.0f / (float)GetGame()->GetWindowHeight());
}

void CShader_SSAO::Render()
{
	glDisable(GL_CULL_FACE);
	glDisable(GL_DEPTH_TEST);

	// Enable positions
	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, GetGame()->GetRenderSystem()->GetScreenQuad());
	glVertexAttribPointer(
		0,
		2,
		GL_FLOAT,
		GL_FALSE,
		0,
		(void*)0
	);

	// Enable UVs
	glEnableVertexAttribArray(1);
	glBindBuffer(GL_ARRAY_BUFFER, GetGame()->GetRenderSystem()->GetScreenUVs());
	glVertexAttribPointer(
		1,
		2,
		GL_FLOAT,
		GL_FALSE,
		0,
		(void*)0
	);

	// Pass 1 - SSAO
	GetGame()->GetRenderSystem()->SetShader(GetGame()->GetRenderSystem()->GetShader("ssao"));
	GetGame()->GetRenderSystem()->SetWriteBuffer(&m_SSAO_Buffer);

	Update();
	glDrawArrays(GL_TRIANGLES, 0, 8);

	// Pass 2 - Blur
	GetGame()->GetRenderSystem()->SetShader(GetGame()->GetRenderSystem()->GetShader("ssao_blur"));

	if (m_WriteBuffer != 0)
	{
		GetGame()->GetRenderSystem()->SetWriteBuffer(m_WriteBuffer);
	}
	else
	{
		glBindFramebuffer(GL_FRAMEBUFFER, 0);
	}

	Update();
	glDrawArrays(GL_TRIANGLES, 0, 8);

	// Clean up
	glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(1);

	glEnable(GL_CULL_FACE);
	glEnable(GL_DEPTH_TEST);
}