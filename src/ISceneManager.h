/*
*	ISceneManager.h - Regan Russell
*
*	The scene manager takes care of node graph
*	heirarchy within a given scene.
*/

#ifndef _ISCENEMANAGER_H_
#define _ISCENEMANAGER_H_

class ISceneManager
{
public:
	ISceneManager();
	~ISceneManager();

	void Tick();
	void Draw(bool useShader = true);

	void Empty();

	void AddNode(ISceneNode* node);
	unsigned int GetNodeCount();
	ISceneNode* GetNode(unsigned int id);

	void AddLight(CLight* light);
	unsigned int GetLightCount();
	CLight* GetLight(unsigned int id);

private:
	std::vector<ISceneNode*> m_NodeList;
	std::vector<CLight*> m_LightList;
};

#endif