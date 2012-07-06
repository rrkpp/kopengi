/*
*	CPostProcessChain.cpp - Regan Russell
*
*	Holds an ordered list of post-processing effects
*	to be applied to the current frame.
*/

#include "kopengi.h"

CPostProcessChain::CPostProcessChain() {}

CPostProcessChain::~CPostProcessChain() {}

void CPostProcessChain::AddShader(CShader* shader)
{
	m_Shaders.push_back(shader);
}

void CPostProcessChain::Render()
{
	// Load FBOs
	bool fbo_switch = true;
	CFrameBuffer* readBuffer = GetGame()->GetRenderSystem()->GetFrameBuffer(0);
	CFrameBuffer* writeBuffer = GetGame()->GetRenderSystem()->GetFrameBuffer(1);
	GBuffer* gBuffer = 0;

	for (unsigned int i = 0; i < m_Shaders.size(); i++)
	{
		CShader* shader = m_Shaders[i];

		if (i != m_Shaders.size() - 1)
			GetGame()->GetRenderSystem()->SetWriteBuffer(writeBuffer);

		if (shader == GetGame()->GetRenderSystem()->GetShader("deferred"))
		{
			gBuffer = GetGame()->GetRenderSystem()->GetGBuffer();
			gBuffer->BindForReading();
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
			shader->Render();
		}
		else
		{
			GetGame()->GetRenderSystem()->SetReadBuffer(readBuffer);
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
			shader->Render();
		}

		// Swap buffers (Ping-Pong PP Technique)
		if (fbo_switch)
		{
			readBuffer = GetGame()->GetRenderSystem()->GetFrameBuffer(1);
			writeBuffer = GetGame()->GetRenderSystem()->GetFrameBuffer(0);
		}
		else
		{
			readBuffer = GetGame()->GetRenderSystem()->GetFrameBuffer(0);
			writeBuffer = GetGame()->GetRenderSystem()->GetFrameBuffer(1);
		}

		glBindFramebuffer(GL_FRAMEBUFFER, 0);
		GetGame()->GetRenderSystem()->SetReadBuffer(0);
		GetGame()->GetRenderSystem()->SetWriteBuffer(0);

		fbo_switch = !fbo_switch;
	}
}