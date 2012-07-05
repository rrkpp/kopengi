/*
*	CShader_SSAO.h - Regan Russell
*
*	SSAO shader based on Crytek implementation.
*/

#ifndef _CSHADER_SSAO_H_
#define _CSHADER_SSAO_H_

class CShader_SSAO : public CShader
{
public:
	CShader_SSAO(std::string vs_path, std::string ps_path);
	~CShader_SSAO();

	virtual void PreLink(GLuint ID);
	virtual void Activate();
	virtual void Update();
	virtual void Render();

	void ActivateBlurPass();

private:
	unsigned int m_KernelSize;
	unsigned int m_NoiseSize;
	GLuint m_NoiseTexture;
	GLfloat* m_Kernel;
	CFrameBuffer m_SSAO_Buffer;
	CFrameBuffer* m_ReadBuffer;
	CFrameBuffer* m_WriteBuffer;
};

#endif