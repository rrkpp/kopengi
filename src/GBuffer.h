/*
*	GBuffer.h - Regan Russell
*
*	GBuffer class, contains all G-Buffer data for
*	use in deferred rendering.
*/

#ifndef _GBUFFER_H_
#define _GBUFFER_H_

class GBuffer
{
public:
	enum GBUFFER_TEXTURE_TYPE
	{
		GBUFFER_TEXTURE_TYPE_DIFFUSE,
		GBUFFER_TEXTURE_TYPE_NORMAL,
		GBUFFER_TEXTURE_TYPE_DEPTH,
		GBUFFER_NUM_TEXTURES
	};

	GBuffer();
	~GBuffer();

	bool Init(unsigned int w, unsigned int h);
	void BindForWriting();
	void BindForReading();
	void Unbind();
	
	GLuint m_Textures[GBUFFER_NUM_TEXTURES];

private:
	GLuint m_FBO;
	GLuint m_DepthTexture;
	bool m_Status;
};

#endif