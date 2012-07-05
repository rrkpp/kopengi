/*
*	CShader_Raster.h - Regan Russell
*
*	Rasterizes post-processing FBOs and renders to screen.
*/

#include "kopengi.h"

CShader_Raster::CShader_Raster(std::string vs_path, std::string ps_path)
	: CShader(vs_path, ps_path) {}

CShader_Raster::~CShader_Raster() {}

void CShader_Raster::PreLink(GLuint ID) {}

void CShader_Raster::Activate()
{
	glUseProgram(m_Id);

	// Bind the GBuffer
	GLuint diffuseID = glGetUniformLocation(m_Id, "fbo_diffuse");
	if (diffuseID != -1)
	{
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, GetGame()->GetRenderSystem()->GetReadBuffer()->m_Textures[0]);
		glUniform1i(diffuseID, 0);
		glActiveTexture(GL_TEXTURE0);
	}
}

void CShader_Raster::Update() {}

void CShader_Raster::Render()
{
	glEnable(GL_BLEND);
	glDisable(GL_CULL_FACE);
	glDisable(GL_DEPTH_TEST);

	// Set shader
	GetGame()->GetRenderSystem()->SetShader(GetGame()->GetRenderSystem()->GetShader("raster"));

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

	GetGame()->GetRenderSystem()->GetCurShader()->Update();
	glDrawArrays(GL_TRIANGLES, 0, 8);

	// Clean up
	glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(1);

	glEnable(GL_CULL_FACE);
	glEnable(GL_DEPTH_TEST);
	glDisable(GL_BLEND);
}