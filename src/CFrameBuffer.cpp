/*
*	CFrameBuffer.cpp - Regan Russell
*
*	Frame buffer wrapper class
*/

#include "kopengi.h"

CFrameBuffer::CFrameBuffer() {}

CFrameBuffer::~CFrameBuffer()
{
	Unbind();

	if (m_FBO != 0)
		glDeleteFramebuffers(1, &m_FBO);

	if (m_Textures[0] != 0)
		glDeleteTextures(ARRAY_SIZE_IN_ELEMENTS(m_Textures), m_Textures);

	delete m_Textures;
}

bool CFrameBuffer::Init(unsigned int w, unsigned int h, int numTextures)
{
	// Create FBO
	glGenFramebuffers(1, &m_FBO);
	glBindFramebuffer(GL_DRAW_FRAMEBUFFER, m_FBO);

	// Generate GBuffer textures
	m_Textures = new GLuint[numTextures];
	glGenTextures(numTextures, m_Textures);

	for (unsigned int i = 0; i < numTextures; i++)
	{
		glBindTexture(GL_TEXTURE_2D, m_Textures[i]);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB32F, w, h, 0, GL_RGB, GL_FLOAT, NULL);
		glFramebufferTexture2D(GL_DRAW_FRAMEBUFFER, GL_COLOR_ATTACHMENT0 + i, GL_TEXTURE_2D, m_Textures[i], 0);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	}

	// Set draw buffers
	GLenum* DrawBuffers = new GLenum[numTextures];
	for (unsigned int i = 0; i < numTextures; i++)
	{
		DrawBuffers[i] = GL_NONE;
	}

	glDrawBuffers(numTextures, DrawBuffers);

	GLenum status = glCheckFramebufferStatus(GL_FRAMEBUFFER);
	if (status != GL_FRAMEBUFFER_COMPLETE)
	{
		log(LOG_TYPE_ERROR, "Error creating frame-buffer: " +  status);
		m_Status = false;
		return false;
	}

	// Reset frame buffer
	glBindFramebuffer(GL_DRAW_FRAMEBUFFER, 0);
	
	m_Status = true;
	return true;
}

void CFrameBuffer::BindForWriting()
{
	glBindFramebuffer(GL_DRAW_FRAMEBUFFER, m_FBO);
}

void CFrameBuffer::BindForReading()
{
	glBindFramebuffer(GL_READ_FRAMEBUFFER, m_FBO);
}

void CFrameBuffer::Unbind()
{
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
}
