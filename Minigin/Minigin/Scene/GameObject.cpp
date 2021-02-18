#include "MiniginPCH.h"
#include "GameObject.h"
#include "../Components/BaseComponent.h"

#include <exception>

JKEngine::GameObject::~GameObject()
{
	for (BaseComponent* pComp : m_Components)
	{
		SafeDelete(pComp);
	}
}

void JKEngine::GameObject::Update(float deltaTime)
{
	for (BaseComponent* pComp : m_Components)
	{
		pComp->Update(deltaTime);
	}
}

void JKEngine::GameObject::FixedUpdate(const float SPerUpdate)
{
	for (BaseComponent* pComp : m_Components)
	{
		pComp->FixedUpdate(SPerUpdate);
	}
}

void JKEngine::GameObject::Render() const
{
	for (BaseComponent* pComp : m_Components)
	{
		pComp->Render();
	}
}

void JKEngine::GameObject::AddComponent(BaseComponent* pComponent)
{
	for (BaseComponent* pComp : m_Components)
	{
		if (typeid(*pComp) == typeid(*pComponent))
		{
			throw std::exception("The Gameobject already has a component of this type.");
			return;
		}
	}
	m_Components.push_back(pComponent);
	pComponent->SetGameObject(this);
	pComponent->Init();
}
