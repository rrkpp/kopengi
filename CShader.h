/*
*	CShader.h - Regan Russell
*
*	Shader wrapper, helps in indexing loaded shaders
*	so that shaders aren't loaded more than once.
*/

#ifndef _CSHADER_H_
#define _CSHADER_H_

class CShader
{
public:
	CShader();
	CShader(std::string vs_path, std::string ps_path);
	~CShader();

	virtual void Activate();
	virtual void Update();
	virtual void Render();

	GLuint GetID();

protected:
	GLuint m_Id;
};

#endif