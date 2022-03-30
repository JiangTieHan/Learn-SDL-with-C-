#pragma once

class Engine {

public:

	static Engine* GetInstance()
	{
		return s_Instance = (s_Instance != nullptr) ? s_Instance : new Engine();
	}

	bool Init();
	bool Clean();
	void Quit();

	void Update(float dt);

	void Render();

	void Events();

private:

	Engine() {};

	static Engine* s_Instance;
};