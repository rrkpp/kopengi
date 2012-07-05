/*
*	CFrameBuffer.h - Regan Russell
*
*	Frame buffer wrapper class
*/

#ifndef _CFRAMEBUFFER_H_
#define _CFRAMEBUFFER_H_

class CFrameBuffer
{
public:
	CFrameBuffer();
	~CFrameBuffer();

	bool Init(unsigned int w, unsigned int h, int numTextures);
	void BindForWriting();
	void BindForReading();
	void Unbind();

	GLuint* m_Textures;

protected:
	GLuint m_FBO;
	bool m_Status;
};

#endif