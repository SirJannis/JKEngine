#pragma once
struct SDL_Window;
namespace JKEngine
{
	class Minigin
	{
	public:
		void Initialize();
		void LoadGame() const;
		void Cleanup();
		void Run();
	private:
		static const float SPerUpdate; //16 / 1000 for 60 fps, 33 / 1000 for 30 fps
		SDL_Window* m_Window{};
	};
}