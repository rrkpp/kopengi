/*
*	CShader_GBuffer.h - Regan Russell
*
*	GBuffer shader for deferred rendering. Fills GBuffer.
*/

#ifndef _CSHADER_GBUFFER_H_
#define _CSHADER_GBUFFER_H_

class CShader_GBuffer : public CShader
{
public:
	CShader_GBuffer(std::string vs_path, std::string ps_path);
	~CShader_GBuffer();

	virtual void PreLink(GLuint ID);
	virtual void Activate();
	virtual void Update();
	virtual void Render();
};

#endif
