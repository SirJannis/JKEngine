#include "MiniginPCH.h"
#include "Minigin.h"
#include <chrono>
#include <thread>
#include "../Managers/InputManager.h"
#include "../Managers/SceneManager.h"
#include "../Graphics/Renderer.h"
#include "../Managers/ResourceManager.h"
#include <SDL.h>
#include "../Scene/GameObject.h"
#include "../Scene/Scene.h"
#include "../Components/Components.h"

using namespace std;
using namespace std::chrono;

const float JKEngine::Minigin::MsPerUpdate = .016f;

void JKEngine::Minigin::Initialize()
{
	if (SDL_Init(SDL_INIT_VIDEO) != 0) 
	{
		throw std::runtime_error(std::string("SDL_Init Error: ") + SDL_GetError());
	}

	m_Window = SDL_CreateWindow(
		"Programming 4 assignment",
		SDL_WINDOWPOS_CENTERED,
		SDL_WINDOWPOS_CENTERED,
		640,
		480,
		SDL_WINDOW_OPENGL
	);
	if (m_Window == nullptr) 
	{
		throw std::runtime_error(std::string("SDL_CreateWindow Error: ") + SDL_GetError());
	}

	Renderer::GetInstance()->Init(m_Window);
}

/**
 * Code constructing the scene world starts here
 */
void JKEngine::Minigin::LoadGame() const
{
	Scene& scene = SceneManager::GetInstance()->CreateScene("Demo");

	GameObject* go = new GameObject();
	go->AddComponent(new TransformComponent({ 320.f , 240.f , 0.f}));
	go->AddComponent(new RenderComponent());
	go->GetComponent<RenderComponent>()->AddTexture(ResourceManager::GetInstance()->LoadTexture("background.jpg"));
	scene.Add(go);

	go = new GameObject();
	go->AddComponent(new TransformComponent({ 320.f, 240.f, 0.f }));
	RenderComponent* pRenderComp = new RenderComponent();
	pRenderComp->AddTexture(ResourceManager::GetInstance()->LoadTexture("logo.png"));
	go->AddComponent(pRenderComp);
	scene.Add(go);

	go = new GameObject();
	go->AddComponent(new TransformComponent({ 320.f, 460.f, 0.f }));
	go->AddComponent(new RenderComponent());
	go->AddComponent(new TextComponent("Programming 4 Assignment", ResourceManager::GetInstance()->LoadFont("Lingua.otf", 36), { 255,255,255 }));
	go->GetComponent<RenderComponent>()->AddTexture(go->GetComponent<TextComponent>()->GetTexture());
	scene.Add(go);

	go = new GameObject();
	go->AddComponent(new TransformComponent({ 40.f, 460.f, 0.f }));
	go->AddComponent(new RenderComponent());
	go->AddComponent(new TextComponent(" ", ResourceManager::GetInstance()->LoadFont("Lingua.otf", 24), { 255, 255,0 }));
	go->GetComponent<RenderComponent>()->AddTexture(go->GetComponent<TextComponent>()->GetTexture());
	go->AddComponent(new FPSComponent());
	scene.Add(go);
}

void JKEngine::Minigin::Cleanup()
{
	Renderer::GetInstance()->Destroy();
	SceneManager::Release();
	InputManager::Release();
	SDL_DestroyWindow(m_Window);
	m_Window = nullptr;
	SDL_Quit();
}

void JKEngine::Minigin::Run()
{
	Initialize();

	// tell the resource manager where he can find the game data
	ResourceManager::GetInstance()->Init("../Data/");

	LoadGame();

	{
		Renderer* renderer = Renderer::GetInstance();
		SceneManager* sceneManager = SceneManager::GetInstance();
		InputManager* input = InputManager::GetInstance();

		bool doContinue = true;
		auto lastTime = high_resolution_clock::now();
		float lag = 0.f;
		while (doContinue)
		{
			const auto currentTime = high_resolution_clock::now();
			float deltaTime = duration<float>(currentTime - lastTime).count();
			lastTime = currentTime;
			lag += deltaTime;
			doContinue = input->ProcessInput();
			while(lag >= MsPerUpdate)
			{
				sceneManager->Update(MsPerUpdate);
				lag -= MsPerUpdate;
			}
			renderer->Render();
		}
	}

	Cleanup();
}
