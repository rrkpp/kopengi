/*
*	CLight.h - Regan Russell
*
*	Base light node, not to be used directly.
*/

#ifndef _CLIGHT_H_
#define _CLIGHT_H_

class CLight : public ISceneNode
{
public:
	CLight();
	~CLight();

	enum LIGHT_TYPE
	{
		LIGHT_TYPE_ENVIRONMENTAL,
		LIGHT_TYPE_DIRECTIONAL,
		LIGHT_TYPE_POINT,
		LIGHT_TYPE_SPOT
	};

	bool Enabled();

	void Enable();
	void Disable();

	void SetDiffuse(glm::vec3 color);
	glm::vec3 GetDiffuse();

	void SetAmbient(glm::vec3 color);
	glm::vec3 GetAmbient();

	void SetSpecular(glm::vec3 color);
	glm::vec3 GetSpecular();

	void SetPower(float power);
	float GetPower();

	void SetDistance(float dist);
	float GetDistance();

	virtual float GetType()
	{
		return LIGHT_TYPE_DIRECTIONAL;
	}

	virtual float GetConstantAtt() {return 0;};
	virtual float GetLinearAtt() {return 0;};
	virtual float GetQuadraticAtt() {return 0;};
	virtual float GetSpotCutoff() {return 0;};
	virtual float GetSpotExponent() {return 0;};

protected:
	glm::vec3 m_Diffuse;
	glm::vec3 m_Ambient;
	glm::vec3 m_Specular;
	float m_LightPower;
	bool m_Enabled;
	float m_Distance;
};

#endif