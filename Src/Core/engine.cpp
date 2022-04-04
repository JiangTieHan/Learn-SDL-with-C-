#include <iostream>
#include "engine.h"
#include "../Graphic/textureManager.h"
#include "../Physics/vector2D.h"
#include "../Charactors/warrior.h"
#include "../Charactors/enemy.h"
#include "../Inputs/input.h"
#include "../Timer/timer.h"
#include "../Map/mapParser.h"
#include "../Camera/camera.h"
#include "../Factory/objFactory.h"

using std::cout;
using std::endl;

Engine* Engine::s_Instance = nullptr;

bool Engine::Init()
{
	if (SDL_Init(SDL_INIT_VIDEO) != 0 && IMG_Init(IMG_INIT_JPG | IMG_INIT_PNG) != 0)
	{
		SDL_Log("Failed to initialize SDL: %s", SDL_GetError());
		return false;
	}

	SDL_WindowFlags window_flags = (SDL_WindowFlags)(SDL_WINDOW_RESIZABLE | SDL_WINDOW_ALLOW_HIGHDPI);
	m_Window = SDL_CreateWindow("2D Engine", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HIGHT, window_flags);
	if (!m_Window)
	{
		SDL_Log("Failed to create window SDL: %s", SDL_GetError());
		return false;
	}

	m_Renderer = SDL_CreateRenderer(m_Window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	if (!m_Renderer)
	{
		SDL_Log("Failed to create renderer SDL: %s", SDL_GetError());
		return false;
	}

	if (!MapParser::GetInstance()->Load())
	{
		SDL_Log("Failed to load map SDL: %s", SDL_GetError());
		return false;
	}

	m_LevelMap = MapParser::GetInstance()->GetMap("MAP");

	TextureManager::GetInstance()->ParseTextures("assets/textures.tml");

	Properties* props = new Properties("player", 250, 400, 136, 96);
	GameObject* Player = ObjectFactory::GetInstance()->CreateObject("PLAYER", props);

	Enemy* Boss = new Enemy(new Properties("boss_idle", 820, 240, 460, 352));

	m_GameObjects.push_back(Player);
	m_GameObjects.push_back(Boss);

	Camera::GetInstance(SCREEN_WIDTH, SCREEN_HIGHT)->SetTarget(Player->GetOrigin());
	return (m_IsRunning = true);
}

bool Engine::Clean()
{
	for (auto m : m_GameObjects)
	{
		delete m;
	}

 	TextureManager::GetInstance()->Clean();
	SDL_DestroyRenderer(m_Renderer);
	SDL_DestroyWindow(m_Window);
	SDL_Quit();
	IMG_Quit();
	return false;
}

void Engine::Quit()
{
	m_IsRunning = false;
}

void Engine::Update()
{
	float dt = Timer::GetInstance()->GetDeltaTime();
	m_LevelMap->Update();
	for (auto& m : m_GameObjects)
	{
		m->Update(dt);
	}
	Camera::GetInstance(SCREEN_WIDTH, SCREEN_HIGHT)->Update(dt);
}

void Engine::Render()
{
	SDL_SetRenderDrawColor(m_Renderer, 124, 218, 254, 255);
	SDL_RenderClear(m_Renderer);

	//TextureManager::GetInstance()->Draw("bg", 0, 0, 2100, 1050);
	m_LevelMap->Render();

	for (auto& m : m_GameObjects)
	{
		m->Draw();
	}

	SDL_RenderPresent(m_Renderer);
}

void Engine::Events()
{
	Input::GetInstance()->Listen();
}
