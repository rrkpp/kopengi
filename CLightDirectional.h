/*
*	CLightDirectional.h - Regan Russell
*
*	Directional light node, casts from everywhere in one direction.
*/

#ifndef _CLIGHTDIRECTIONAL_H_
#define _CLIGHTDIRECTIONAL_H_

class CLightDirectional : public CLight
{
public:
	CLightDirectional();
	~CLightDirectional();

	void SetDirection(glm::vec3 direction);
	glm::vec3 GetDirection();

	float GetType();

	virtual glm::vec4 GetViewSpacePos();
};

#endif