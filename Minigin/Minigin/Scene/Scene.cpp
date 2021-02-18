#include "MiniginPCH.h"
#include "Scene.h"
#include "GameObject.h"

using namespace JKEngine;

Scene::Scene(const std::string& name) : m_Name(name) {}

Scene::~Scene()
{
	for(GameObject* pObject : m_Objects)
	{
		SafeDelete(pObject);
	}
}

void Scene::Add(GameObject* pObject)
{
	m_Objects.push_back(pObject);
}

void Scene::Update(float SPerUpdate)
{
	for(GameObject* pObject : m_Objects)
	{
		pObject->Update(SPerUpdate);
	}
}

void Scene::Render() const
{
	for (const GameObject* pObject : m_Objects)
	{
		pObject->Render();
	}
}

