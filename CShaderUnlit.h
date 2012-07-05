/*
*	CShaderUnlit.h - Regan Russell
*
*	Unlit diffuse shader, renders based either on
*	material diffuse or texture diffuse if available.
*/

#ifndef _CSHADERUNLIT_H_
#define _CSHADERUNLIT_H_

class CMesh;

class CShaderUnlit : CShader
{
public:
	CShaderUnlit(std::string vs_path, std::string ps_path);
	~CShaderUnlit();

	virtual void Init(glm::mat4* modelMatrix, glm::mat4* viewMatrix, glm::mat4* projMatrix);
	virtual void Update(glm::mat4* modelMatrix, glm::mat4* viewMatrix, glm::mat4* projMatrix, CMesh &mesh);

private:
	glm::mat4* m_ModelMatrix;
	glm::mat4* m_ViewMatrix;
	glm::mat4* m_ProjectionMatrix;

	GLuint m_ModelMatrixID;
	GLuint m_ViewMatrixID;
	GLuint m_ProjectionMatrixID;
};

#endif