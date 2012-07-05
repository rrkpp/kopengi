/*
*	CMaterial.h - Regan Russell
*
*	Holds material data to be used by a mesh.
*/

#ifndef _CMATERIAL_H_
#define _CMATERIAL_H_

struct CMaterial
{
	int m_TextureCount;
	glm::vec4 m_Diffuse;
	glm::vec4 m_Ambient;
	glm::vec4 m_Specular;
	glm::vec4 m_Emissive;
	float m_Shininess;
};

#endif