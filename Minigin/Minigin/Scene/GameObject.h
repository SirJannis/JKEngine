#pragma once

namespace JKEngine
{
	class BaseComponent;
	class GameObject final
	{
	public:
		void Update(float deltaTime);
		void FixedUpdate(float SPerUpdate);
		void Render() const;

		GameObject() = default;
		virtual ~GameObject();
		GameObject(const GameObject& other) = delete;
		GameObject(GameObject&& other) = delete;
		GameObject& operator=(const GameObject& other) = delete;
		GameObject& operator=(GameObject&& other) = delete;

		void AddComponent(BaseComponent* component);

		template <class T>
		T* GetComponent()
		{
			for (BaseComponent* pComp : m_Components)
			{
				if (dynamic_cast<T*>(pComp))
					return static_cast<T*>(pComp);
			}
			return nullptr;
		}
	
	private:
		std::vector<BaseComponent*> m_Components;
	};
}
