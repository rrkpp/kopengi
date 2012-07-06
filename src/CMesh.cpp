/*
*	CMesh.cpp - Regan Russell
*
*	Holds mesh data as well as material data related to the mesh.
*	A mesh is a 3D shape which contains it's own unique material data.
*	Multiple meshes are stitched together along with their material data
*	to create one coherent model.
*/

#include "kopengi.h"

CMesh::CMesh()
{
	m_VertexBuffer = 0;
	m_UVBuffer = 0;
	m_NormalBuffer = 0;
	m_IndexBuffer = 0;
}

CMesh::~CMesh() {}

void CMesh::SetMaterial(CMaterial material)
{
	m_Material = material;
}

CMaterial CMesh::GetMaterial()
{
	return m_Material;
}