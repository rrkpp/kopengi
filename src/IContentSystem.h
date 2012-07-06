/*
*	IContentSystem.h - Regan Russell
*
*	Content interface, handles content loading and memory
*	management associated with assets.
*/

#ifndef _ICONTENTSYSTEM_H_
#define _ICONTENTSYSTEM_H_

class IContentSystem
{
public:
	IContentSystem();
	~IContentSystem();

	CModel* GetModel(std::string path);
	CModel* LoadModel(std::string path);
	
	GLuint GetTexture(std::string path);

	GLuint GetErrorTexture();

private:
	Assimp::Importer m_Importer;
	std::map<std::string, CModel*> m_ModelCache;
	std::map<std::string, GLuint> m_TextureCache;
	GLuint m_ErrorTexture;
};

#endif