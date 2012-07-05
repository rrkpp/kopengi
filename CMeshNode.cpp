/*
*	CMeshNode.cpp - Regan Russell
*
*	Node that holds static mesh data.
*/

#include "kopengi.h"

CMeshNode::CMeshNode()
{
	m_Shader = GetGame()->GetRenderSystem()->GetShader("unlit");
	m_Model = 0;
	m_Material = 0;
}

CMeshNode::~CMeshNode() {}

void CMeshNode::Draw(bool useShader)
{
	if (m_ShouldDraw && m_Model != 0)
	{
		// Pass matrix data to the shader
		GLuint modelMatrixID = glGetUniformLocation(GetGame()->GetRenderSystem()->GetCurShader()->GetID(), "ModelMatrix");
		if (modelMatrixID != -1)
			glUniformMatrix4fv(modelMatrixID, 1, GL_FALSE, &GetTransform()[0][0]);

		GLuint normalMatrixID = glGetUniformLocation(GetGame()->GetRenderSystem()->GetCurShader()->GetID(), "NormalMatrix");
		if (normalMatrixID != -1)
			glUniformMatrix3fv(normalMatrixID, 1, GL_FALSE, &GetGame()->GetRenderSystem()->GetViewRotMatrix()[0][0]);

		// Render a pass
		for (unsigned int i = 0; i < m_Model->GetMeshCount(); i++)
		{
			CMesh* mesh = m_Model->GetMesh(i);
			GetGame()->GetRenderSystem()->SetCurMesh(mesh);
			GetGame()->GetRenderSystem()->GetCurShader()->Update();
			GetGame()->GetRenderSystem()->GetCurShader()->Render();
		}
	}
}
	
void CMeshNode::SetModel(CModel* model)
{
	m_Model = model;
	m_ShouldDraw = true;
}

CModel* CMeshNode::GetModel()
{
	return m_Model;
}

void CMeshNode::SetShader(CShader* shader)
{
	m_Shader = shader;
}

CShader* CMeshNode::GetShader()
{
	return m_Shader;
}

void CMeshNode::SetMaterial(CMaterial* mat)
{
	m_Material = mat;
}

CMaterial* CMeshNode::GetMaterial()
{
	return m_Material;
}

void CMeshNode::ClearMaterial()
{
	m_Material = 0;
}