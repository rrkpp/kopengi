/*
*	CShaderUnlit.cpp - Regan Russell
*
*	Unlit diffuse shader, renders based either on
*	material diffuse or texture diffuse if available.
*/

#include "kopengi.h"

CShaderUnlit::CShaderUnlit(std::string vs_path, std::string ps_path)
	: CShader(vs_path, ps_path) {}

CShaderUnlit::~CShaderUnlit() {}

void CShaderUnlit::Init(glm::mat4* modelMatrix, glm::mat4* viewMatrix, glm::mat4* projMatrix)
{
	m_ModelMatrix = modelMatrix;
	m_ViewMatrix = viewMatrix;
	m_ProjectionMatrix = projMatrix;

	// Set active shader
	glUseProgram(m_Id);

	// Pass matrix data to the shader
	GLuint m_ModelMatrixID = glGetUniformLocation(m_Id, "ModelMatrix");
	glUniformMatrix4fv(m_ModelMatrixID, 1, GL_FALSE, &(*m_ModelMatrix)[0][0]);

	GLuint m_ViewMatrixID = glGetUniformLocation(m_Id, "ViewMatrix");
	glUniformMatrix4fv(m_ViewMatrixID, 1, GL_FALSE, &(*m_ViewMatrix)[0][0]);

	GLuint m_ProjectionMatrixID = glGetUniformLocation(m_Id, "ProjectionMatrix");
	glUniformMatrix4fv(m_ProjectionMatrixID, 1, GL_FALSE, &(*m_ProjectionMatrix)[0][0]);
}

void CShaderUnlit::Update(glm::mat4* modelMatrix, glm::mat4* viewMatrix, glm::mat4* projMatrix, CMesh &mesh)
{
	m_ModelMatrix = modelMatrix;
	m_ViewMatrix = viewMatrix;
	m_ProjectionMatrix = projMatrix;

	GLint curShader;
	glGetIntegerv(GL_CURRENT_PROGRAM, &curShader);
	
	if (m_Id == curShader)
	{
		// Pass matrix data to the shader
		GLuint m_ModelMatrixID = glGetUniformLocation(m_Id, "ModelMatrix");
		glUniformMatrix4fv(m_ModelMatrixID, 1, GL_FALSE, &(*m_ModelMatrix)[0][0]);

		GLuint m_ViewMatrixID = glGetUniformLocation(m_Id, "ViewMatrix");
		glUniformMatrix4fv(m_ViewMatrixID, 1, GL_FALSE, &(*m_ViewMatrix)[0][0]);

		GLuint m_ProjectionMatrixID = glGetUniformLocation(m_Id, "ProjectionMatrix");
		glUniformMatrix4fv(m_ProjectionMatrixID, 1, GL_FALSE, &(*m_ProjectionMatrix)[0][0]);
	}
}