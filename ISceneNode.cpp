/*
*	ISceneNode.cpp - Regan Russell
*
*	Base node which all objects in the 3D world
*	will derive from.
*/

#include "kopengi.h"

ISceneNode::ISceneNode(bool addToSceneGraph)
{
	m_Pos = glm::vec3(0, 0, 0);
	m_Angles = glm::vec3(0, 0, 0);
	m_Scale = glm::vec3(1, 1, 1);

	m_Parent = NULL;

	m_ModelMatrix = glm::mat4(1.0f);
	m_NormalMatrix = glm::mat4(1.0f);

	m_ShouldDraw = false;
	
	if (addToSceneGraph)
		GetGame()->GetSceneManager()->AddNode(this);
}

ISceneNode::~ISceneNode() {}

void ISceneNode::Tick() {}

void ISceneNode::Draw(bool useShader) {}

bool ISceneNode::ShouldDraw()
{
	return m_ShouldDraw;
}

void ISceneNode::SetShouldDraw(bool b)
{
	m_ShouldDraw = b;
}

void ISceneNode::AddChild(ISceneNode* node)
{
	m_Children.push_back(node);
}

void ISceneNode::RemoveChild(ISceneNode* node)
{
	for (unsigned int i = 0; i < m_Children.size(); i++)
	{
		if (m_Children[i] == node)
		{
			m_Children[i]->SetParent(NULL);
			m_Children.erase(m_Children.begin() + i);
		}
	}
}

void ISceneNode::SetParent(ISceneNode* node)
{
	if (m_Parent != NULL)
	{
		m_Parent->RemoveChild(this);
	}

	m_Parent = node;

	m_Pos = m_Pos - m_Parent->GetPos();
	m_Angles = m_Angles - m_Parent->GetAngles();

	m_Parent->AddChild(this);
}

ISceneNode* ISceneNode::GetParent()
{
	return m_Parent;
}

void ISceneNode::SetPos(glm::vec3 pos)
{
	m_Pos = pos;
	UpdateMatrix();
}

glm::vec3 ISceneNode::GetPos()
{
	return m_Pos;
}

glm::vec3 ISceneNode::GetPosAbsolute()
{
	if (m_Parent != NULL)
	{
		return glm::vec3(m_ModelMatrix[3].r, m_ModelMatrix[3].g, m_ModelMatrix[3].b);
	}
	else
	{
		return m_Pos;
	}
}

void ISceneNode::SetAngles(glm::vec3 ang)
{
	m_Angles = ang;
	UpdateMatrix();
}

glm::vec3 ISceneNode::GetAnglesAbsolute()
{
	if (m_Parent != NULL)
	{
		return m_Parent->GetAnglesAbsolute() + m_Angles;
	}
	else
	{
		return m_Angles;
	}
}

glm::vec3 ISceneNode::GetAngles()
{
	return m_Angles;
}

void ISceneNode::SetScale(glm::vec3 scale)
{
	m_Scale = scale;
	UpdateMatrix();
}

glm::vec3 ISceneNode::GetScale()
{
	return m_Scale;
}

void ISceneNode::UpdateMatrix()
{
	glm::mat4 translate;
	glm::mat4 rotate;
	glm::mat4 scale, voidScale;

	scale = glm::scale(glm::mat4(1.0f), m_Scale);
	voidScale = glm::scale(glm::mat4(1.0f), glm::vec3(1.0f, 1.0f, 1.0f));
	rotate = glm::rotate(glm::mat4(1.0f), m_Angles.x, glm::vec3(1.0f, 0.0f, 0.0f));
	rotate = glm::rotate(rotate, m_Angles.y, glm::vec3(0.0f, 1.0f, 0.0f));
	rotate = glm::rotate(rotate, m_Angles.z, glm::vec3(0.0f, 0.0f, 1.0f));
	translate = glm::translate(glm::mat4(1.0f), m_Pos);
	
	m_ModelMatrix = translate * rotate * scale;
	m_NormalMatrix = rotate;
	m_ParentMatrix = translate * rotate * voidScale;

	if (m_Parent != NULL)
	{
		m_ModelMatrix = m_Parent->GetParentMatrix() * m_ModelMatrix;
		m_ParentMatrix = m_Parent->GetParentMatrix() * m_ParentMatrix;
	}

	for (unsigned int i = 0; i < m_Children.size(); i++)
	{
		m_Children[i]->UpdateMatrix();
	}
}

glm::mat4 ISceneNode::GetTransform()
{
	return m_ModelMatrix;
}

glm::mat4 ISceneNode::GetParentMatrix()
{
	return m_ParentMatrix;
}

glm::vec4 ISceneNode::GetViewSpacePos()
{
	return GetGame()->GetRenderSystem()->GetViewMatrix() * glm::vec4(GetPosAbsolute().x, GetPosAbsolute().y, GetPosAbsolute().z, 1.0);
}

glm::vec4 ISceneNode::GetViewSpaceAngles()
{
	return GetGame()->GetRenderSystem()->GetViewMatrix() * glm::vec4(GetAnglesAbsolute().x, GetAnglesAbsolute().y, GetAnglesAbsolute().z, 0.0);
}