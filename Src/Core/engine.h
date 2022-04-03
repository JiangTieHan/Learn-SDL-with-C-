#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include "../Map/gameMap.h"
#include "../Object/gameObject.h"

class Engine {

public:

	static Engine* GetInstance()
	{
		return s_Instance = (s_Instance != nullptr) ? s_Instance : new Engine();
	}

	bool Init();
	bool Clean();
	void Quit();

	void Update();
	void Render();
	void Events();

	inline bool IsRunning() const { return m_IsRunning; };
	inline SDL_Renderer* GetRenderer() const { return m_Renderer; }
	inline GameMap* GetGameMap() const { return m_LevelMap; }

private:

	Engine() {};
	bool m_IsRunning;

	GameMap* m_LevelMap;
	SDL_Window* m_Window;
	SDL_Renderer* m_Renderer;
	static Engine* s_Instance;
	std::vector<GameObject*> m_GameObjects;
};