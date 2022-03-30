#include "engine.h"
#include <iostream>

using std::cout;
using std::endl;

Engine* Engine::s_Instance = nullptr;

bool Engine::Init()
{
	m_IsRunning = true;
	return false;
}

bool Engine::Clean()
{
	return false;
}

void Engine::Quit()
{
}

void Engine::Update()
{
	cout << "Updating..." << endl;
}

void Engine::Render()
{
}

void Engine::Events()
{
}
