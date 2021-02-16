#pragma once
namespace JKEngine
{
	class GameObject;
	class BaseComponent
	{
	public:
		virtual ~BaseComponent() = default;
		virtual void Init() = 0;
		virtual void Update(const float msPerFrame) = 0;
		virtual void Render() const = 0;
		void SetGameObject(GameObject* pParent) { m_pGameObject = pParent; }
	protected:

		GameObject* m_pGameObject = nullptr;
	};
}