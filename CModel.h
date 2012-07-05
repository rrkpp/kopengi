/*
*	CModel.h - Regan Russell
*
*	Stores related meshes (Which contain their own material data),
*	as well as texture data, and coordinates the rendering of meshes.
*/

#ifndef _CMODEL_H_
#define _CMODEL_H_

class CModel
{
public:
	CModel();
	~CModel();

	void AddMesh(CMesh* mesh);
	CMesh* GetMesh(unsigned int index);
	unsigned int GetMeshCount();

private:
	std::vector<CMesh*> m_Meshes;
};

#endif