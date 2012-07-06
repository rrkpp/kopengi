/*
*	CShader_Deferred.h - Regan Russell
*
*	Shader for per-pixel lighting in Deferred Shading.
*/

#ifndef _CSHADER_DEFERRED_H_
#define _CSHADER_DEFERRED_H_

class CShader_Deferred : public CShader
{
public:
	CShader_Deferred(std::string vs_path, std::string ps_path);
	~CShader_Deferred();

	virtual void PreLink(GLuint ID);
	virtual void Activate();
	virtual void Update();
	virtual void Render();
};

#endif