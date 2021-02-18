#pragma once
#include "../Helpers/Singleton.h"

namespace JKEngine
{
	class Scene;
	class SceneManager final : public Singleton<SceneManager>
	{
	public:
		SceneManager() = default;
		~SceneManager();
		Scene& CreateScene(const std::string& name, bool setactive = true);
		void AddScene(Scene* pScene, bool setactive = true);
		void SetActiveScene(const std::string& name);
		void SetActiveScene(const Scene* pScene);
		void RemoveScene(const std::string& name);
		void RemoveScene(const Scene* pScene);


		void Update(float deltaTime);
		void FixedUpdate(const float SPerUpdate);
		void Render();
	private:
		std::vector<Scene*> m_Scenes;
		Scene* m_pActiveScene;
	};
}
