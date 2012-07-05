/*
*	ISceneManager.cpp - Regan Russell
*
*	The scene manager takes care of node graph
*	heirarchy within a given scene.
*/

#include "kopengi.h"

ISceneManager::ISceneManager() {}

ISceneManager::~ISceneManager() {}

void ISceneManager::Tick()
{
	for (unsigned int i = 0; i < m_NodeList.size(); i++)
	{
		m_NodeList[i]->Tick();
	}

	for (unsigned int i = 0; i < m_LightList.size(); i++)
	{
		m_LightList[i]->Tick();
	}
}

void ISceneManager::Draw(bool useShader)
{
	for (unsigned int i = 0; i < m_NodeList.size(); i++)
	{
		m_NodeList[i]->Draw(useShader);
	}
}

void ISceneManager::Empty()
{
	m_NodeList.empty();
}

void ISceneManager::AddNode(ISceneNode* node)
{
	m_NodeList.push_back(node);
}

unsigned int ISceneManager::GetNodeCount()
{
	return m_NodeList.size();
}

ISceneNode* ISceneManager::GetNode(unsigned int id)
{
	return m_NodeList[id];
}

void ISceneManager::AddLight(CLight* light)
{
	m_LightList.push_back(light);
}

unsigned int ISceneManager::GetLightCount()
{
	return m_LightList.size();
}

CLight* ISceneManager::GetLight(unsigned int id)
{
	return m_LightList[id];
}