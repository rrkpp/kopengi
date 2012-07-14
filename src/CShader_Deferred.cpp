/*
*	CShader_Deferred.cpp - Regan Russell
*
*	Shader for per-pixel lighting in Deferred Shading.
*/

#include "kopengi.h"

CShader_Deferred::CShader_Deferred(std::string vs_path, std::string ps_path)
	: CShader(vs_path, ps_path) {}

CShader_Deferred::~CShader_Deferred() {}

void CShader_Deferred::PreLink(GLuint ID) {}

void CShader_Deferred::Activate()
{
	glUseProgram(m_Id);

	// Bind the GBuffer
	GLuint diffuseID = glGetUniformLocation(m_Id, "fbo_diffuse");
	if (diffuseID != -1)
	{
		glActiveTexture(GL_TEXTURE1);
		glBindTexture(GL_TEXTURE_2D, GetGame()->GetRenderSystem()->GetGBuffer()->m_Textures[GBuffer::GBUFFER_TEXTURE_TYPE_DIFFUSE]);
		glUniform1i(diffuseID, 1);
		glActiveTexture(GL_TEXTURE0);
	}

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

	GLuint invProjID = glGetUniformLocation(m_Id, "InverseProjectionMatrix");
	if (invProjID != -1)
		glUniformMatrix4fv(invProjID, 1, GL_FALSE, &glm::inverse(GetGame()->GetRenderSystem()->GetProjectionMatrix())[0][0]);

	GLuint camFarZ = glGetUniformLocation(m_Id, "camFarZ");
	if (camFarZ != -1)
		glUniform1f(camFarZ, GetGame()->GetRenderSystem()->GetCamera()->GetFarZ());
}

void CShader_Deferred::Update()
{
	CLight* light = GetGame()->GetRenderSystem()->GetCurLight();

	// Pass light data to shader
	GLuint lightTypeID = glGetUniformLocation(GetGame()->GetRenderSystem()->GetCurShader()->GetID(), "lightType");
	if (lightTypeID != -1)
		glUniform1i(lightTypeID, light->GetType());

	GLuint lightDiffuseID = glGetUniformLocation(GetGame()->GetRenderSystem()->GetCurShader()->GetID(), "lightDiffuse");
	if (lightDiffuseID != -1)
		glUniform3f(lightDiffuseID, light->GetDiffuse().x, light->GetDiffuse().y, light->GetDiffuse().z);

	GLuint lightAmbientID = glGetUniformLocation(GetGame()->GetRenderSystem()->GetCurShader()->GetID(), "lightAmbient");
	if (lightAmbientID != -1)
		glUniform3f(lightAmbientID, light->GetAmbient().x, light->GetAmbient().y, light->GetAmbient().z);

	GLuint lightSpecularID = glGetUniformLocation(GetGame()->GetRenderSystem()->GetCurShader()->GetID(), "lightSpecular");
	if (lightSpecularID != -1)
		glUniform3f(lightSpecularID, light->GetSpecular().x, light->GetSpecular().y, light->GetSpecular().z);

	GLuint lightPowerID = glGetUniformLocation(GetGame()->GetRenderSystem()->GetCurShader()->GetID(), "lightPower");
	if (lightPowerID != -1)
		glUniform1f(lightPowerID, light->GetPower());

	GLuint lightPosID = glGetUniformLocation(GetGame()->GetRenderSystem()->GetCurShader()->GetID(), "lightPos");
	if (lightPosID != -1)
		glUniform3f(lightPosID, light->GetViewSpacePos().x, light->GetViewSpacePos().y, light->GetViewSpacePos().z);

	GLuint lightAngleID = glGetUniformLocation(GetGame()->GetRenderSystem()->GetCurShader()->GetID(), "lightAngle");
	if (lightAngleID != -1)
		glUniform3f(lightAngleID, light->GetViewSpaceAngles().x, light->GetViewSpaceAngles().y, light->GetViewSpaceAngles().z);

	// Point light data
	GLuint cAttID = glGetUniformLocation(GetGame()->GetRenderSystem()->GetCurShader()->GetID(), "constAtt");
	if (cAttID != -1)
		glUniform1f(cAttID, light->GetConstantAtt());

	GLuint lAttID = glGetUniformLocation(GetGame()->GetRenderSystem()->GetCurShader()->GetID(), "linAtt");
	if (lAttID != -1)
		glUniform1f(lAttID, light->GetLinearAtt());

	GLuint qAttID = glGetUniformLocation(GetGame()->GetRenderSystem()->GetCurShader()->GetID(), "quadAtt");
	if (qAttID != -1)
		glUniform1f(qAttID, light->GetQuadraticAtt());

	GLuint spotCutoffID = glGetUniformLocation(GetGame()->GetRenderSystem()->GetCurShader()->GetID(), "spotCosCutoff");
	if (qAttID != -1)
		glUniform1f(spotCutoffID, light->GetSpotCutoff());

	GLuint spotExpID = glGetUniformLocation(GetGame()->GetRenderSystem()->GetCurShader()->GetID(), "spotExp");
	if (qAttID != -1)
		glUniform1f(spotExpID, light->GetSpotExponent());
}

void CShader_Deferred::Render()
{
	glEnable(GL_BLEND);
	glDisable(GL_CULL_FACE);
	glDisable(GL_DEPTH_TEST);

	// Set shader
	GetGame()->GetRenderSystem()->SetShader(GetGame()->GetRenderSystem()->GetShader("deferred"));

	// Enable positions
	glEnableVertexAttribArray(0);
	
	if (GetGame()->GetGLSLVersion() == GLSL_VERSION_130)
	{
		glBindAttribLocation(GetID(), 0, "vertexPos_MS");
		glBindAttribLocation(GetID(), 1, "vertexTexCoords");
	}

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

	for (unsigned int i = 0; i < GetGame()->GetSceneManager()->GetLightCount(); i++)
	{
		CLight* light = GetGame()->GetSceneManager()->GetLight(i);
		if (light->Enabled())
		{
			GetGame()->GetRenderSystem()->SetCurLight(light);
			Update();

			glDrawArrays(GL_TRIANGLES, 0, 8);
		}
	}

	// Clean up
	glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(1);

	glEnable(GL_CULL_FACE);
	glEnable(GL_DEPTH_TEST);
	glDisable(GL_BLEND);
}
