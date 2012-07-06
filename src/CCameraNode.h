/*
*	CCameraNode.h - Regan Russell
*
*	Base camera class for the engine.
*/

#ifndef _CCAMERANODE_H_
#define _CCAMERANODE_H_

class CCameraNode : public ISceneNode
{
public:
	CCameraNode();
	~CCameraNode();

	void Tick();

	void SetDirection(glm::vec3 ang);
	glm::vec3 GetDirection();

	glm::vec3 GetUp();
	glm::vec3 GetRight();

	void SetFOV(float fov);
	float GetFOV();

	void SetNearZ(float z);
	float GetNearZ();

	void SetFarZ(float z);
	float GetFarZ();

private:
	float m_LastTick;
	glm::vec3 m_Forward; // Directional vector
	glm::vec3 m_Right;
	glm::vec3 m_Up;
	float m_XAngle;
	float m_YAngle;
	float m_FOV;
	float m_NearZ;
	float m_FarZ;
};

#endif