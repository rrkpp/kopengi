/*
*	CMesh.h - Regan Russell
*
*	Holds mesh data as well as material data related to the mesh.
*	A mesh is a 3D shape which contains it's own unique material data.
*	Multiple meshes are stitched together along with their material data
*	to create one coherent model.
*/

#ifndef _CMESH_H_
#define _CMESH_H_

class CMesh
{
public:
	CMesh();
	~CMesh();

	void SetMaterial(CMaterial material);
	CMaterial GetMaterial();
	
	unsigned int m_NumFaces;
	GLuint m_UniformBlockIndex;
	GLuint m_TextureIndex;
	GLuint m_VertexBuffer;
	GLuint m_UVBuffer;
	GLuint m_NormalBuffer;
	GLuint m_IndexBuffer;

private:
	CMaterial m_Material;
};

#endif