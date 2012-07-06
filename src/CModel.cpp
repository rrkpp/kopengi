/*
*	CModel.h - Regan Russell
*
*	Stores related meshes (Which contain their own material data),
*	as well as texture data, and coordinates the rendering of meshes.
*/

#include "kopengi.h"

CModel::CModel() {}

CModel::~CModel()
{
	for (unsigned int i = 0; i < m_Meshes.size(); i++)
	{
		delete m_Meshes[i];
	}
}

void CModel::AddMesh(CMesh* mesh)
{
	m_Meshes.push_back(mesh);
}

CMesh* CModel::GetMesh(unsigned int index)
{
	return m_Meshes[index];
}

unsigned int CModel::GetMeshCount()
{
	return m_Meshes.size();
}