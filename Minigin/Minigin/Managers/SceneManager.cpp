#include "MiniginPCH.h"
#include "SceneManager.h"
#include "../Scene/Scene.h"
#include "InputManager.h"
#include "../Helpers/Logger.h"

void JKEngine::SceneManager::FixedUpdate(const float SPerUpdate)
{
	m_pActiveScene->FixedUpdate(SPerUpdate);
}

void JKEngine::SceneManager::Render()
{
	m_pActiveScene->Render();
}

JKEngine::SceneManager::~SceneManager()
{
	for (Scene* pScene : m_Scenes)
	{
		SafeDelete(pScene);
	}
}

JKEngine::Scene& JKEngine::SceneManager::CreateScene(const std::string& name, bool setactive)
{
	Scene* pScene = new Scene(name);
	m_Scenes.push_back(pScene);
	if (setactive)
	{
		m_pActiveScene = m_Scenes.back();
	}
	return *pScene;
}

void JKEngine::SceneManager::AddScene(Scene* pScene, bool setactive)
{
	m_Scenes.push_back(pScene);
	if (setactive)
	{
		m_pActiveScene = m_Scenes.back();
	}
}

void JKEngine::SceneManager::SetActiveScene(const std::string& name)
{
	for (Scene* pScene : m_Scenes)
	{
		if (pScene->GetName() == name)
		{
			m_pActiveScene = pScene;
			return;
		}
		
	}
	Logger::LogError("Scene you wanted to set active is not a valid Scene, please add it to the Manager first\n");
}

void JKEngine::SceneManager::SetActiveScene(const Scene* pScene)
{
	for (Scene* pSceneMember : m_Scenes)
	{
		if (pSceneMember == pScene)
		{
			m_pActiveScene = pSceneMember;
			return;
		}
	}
	Logger::LogError("Scene you wanted to set active is not a valid Scene, please add it to the Manager first\n");
}

void JKEngine::SceneManager::RemoveScene(const std::string& name)
{
	for (size_t idx{}; idx < m_Scenes.size(); idx++)
	{
		if (m_Scenes[idx]->GetName() == name)
		{
			if (m_pActiveScene == m_Scenes[idx])
			{
				m_pActiveScene = m_Scenes[(idx + 1) % m_Scenes.size()];
			}
			//Think about this in input Manager
			//InputManager::GetInstance()->RemoveCommandsByScene(name);
			SafeDelete(m_Scenes[idx]);
			m_Scenes[idx] = m_Scenes.back();
			m_Scenes.pop_back();
			idx--;
		}
	}
}

void JKEngine::SceneManager::RemoveScene(const Scene* pScene)
{
	for (size_t idx{}; idx < m_Scenes.size(); idx++)
	{
		if (m_Scenes[idx] == pScene)
		{
			if (m_pActiveScene == m_Scenes[idx])
			{
				m_pActiveScene = m_Scenes[(idx + 1) % m_Scenes.size()];
			}
			//Think about this in input Manager
			//InputManager::GetInstance()->RemoveCommandsByScene(m_Scenes[idx]->GetName());
			SafeDelete(m_Scenes[idx]);
			m_Scenes[idx] = m_Scenes.back();
			m_Scenes.pop_back();
			idx--;
		}
	}
}

void JKEngine::SceneManager::Update(float deltaTime)
{
	m_pActiveScene->Update(deltaTime);
}
