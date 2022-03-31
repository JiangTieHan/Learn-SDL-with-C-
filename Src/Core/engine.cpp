#include <iostream>
#include "engine.h"
#include "../Graphic/textureManager.h"
#include "../Physics/vector2D.h"
#include "../Charactors/warrior.h"
#include "../Inputs/input.h"

using std::cout;
using std::endl;

Engine* Engine::s_Instance = nullptr;
Warrior* Player = nullptr;

bool Engine::Init()
{
	if (SDL_Init(SDL_INIT_VIDEO) != 0 && IMG_Init(IMG_INIT_JPG | IMG_INIT_PNG) != 0)
	{
		SDL_Log("Failed to initialize SDL: %s", SDL_GetError());
		return false;
	}

	m_Window = SDL_CreateWindow("2D Engine", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HIGHT, 0);
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

	TextureManager::GetInstance()->Load("player", "assets/Idle.png");
	TextureManager::GetInstance()->Load("player_run", "assets/run.png");

	Player = new Warrior("player", 100, 200, 136, 96);

	return (m_IsRunning = true);
}

bool Engine::Clean()
{
	TextureManager::GetInstance()->Clean();
	Player->Clean();
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
	//cout << "Updating..." << endl;
	
	Player->Update(0);
}

void Engine::Render()
{
	SDL_SetRenderDrawColor(m_Renderer, 124, 218, 254, 255);
	SDL_RenderClear(m_Renderer);

	Player->Draw();
	SDL_RenderPresent(m_Renderer);
}

void Engine::Events()
{
	Input::GetInstance()->Listen();
}
