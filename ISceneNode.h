/*
*	ISceneNode.h - Regan Russell
*
*	Base node which all objects in the 3D world
*	will derive from.
*/

// TODO: Consider removing matrix data and abstracting it to
// another class. Lights don't need matrix data and they derive
// from this class!

#ifndef _ISCENENODE_H_
#define _ISCENENODE_H_

class ISceneNode
{
public:
	ISceneNode(bool addToSceneGraph = true);
	~ISceneNode();

	virtual void Tick();
	virtual void Draw(bool useShader = true);

	virtual bool ShouldDraw();
	virtual void SetShouldDraw(bool b);

	virtual void AddChild(ISceneNode* node);
	virtual void RemoveChild(ISceneNode* node);

	virtual void SetParent(ISceneNode* node);
	virtual ISceneNode* GetParent();

	virtual void SetPos(glm::vec3 pos);
	virtual glm::vec3 GetPos();
	virtual glm::vec3 GetPosAbsolute();

	virtual void SetAngles(glm::vec3 ang);
	virtual glm::vec3 GetAngles();
	virtual glm::vec3 GetAnglesAbsolute();

	virtual void SetScale(glm::vec3 scale);
	virtual glm::vec3 GetScale();

	virtual void UpdateMatrix();
	virtual glm::mat4 GetTransform();
	virtual glm::mat4 GetParentMatrix();

	virtual glm::vec4 GetViewSpacePos();
	virtual glm::vec4 GetViewSpaceAngles();

protected:
	ISceneNode* m_Parent;
	std::vector<ISceneNode*> m_Children;
	bool m_ShouldDraw;
	glm::vec3 m_Pos;
	glm::vec3 m_Angles;
	glm::vec3 m_Scale;
	glm::mat4 m_ModelMatrix;
	glm::mat4 m_NormalMatrix;
	glm::mat4 m_ParentMatrix;
};

#endif