/*
*	CPostProcessChain.h - Regan Russell
*
*	Holds an ordered list of post-processing effects
*	to be applied to the current frame.
*/

#ifndef _CPOSTPROCESSCHAIN_H_
#define _CPOSTPROCESSCHAIN_H_

class CPostProcessChain
{
public:
	CPostProcessChain();
	~CPostProcessChain();

	void AddShader(CShader* shader);

	void Render();

private:
	std::vector<CShader*> m_Shaders;
};

#endif