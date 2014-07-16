#ifndef COREENGINE_H
#define COREENGINE_H

#include <string>
#include "Window.h"
#include "TestGame.h"
#include "Input.h"
#include "RenderingEngine.h"

class coreEngine
{
public:
	coreEngine(Game* game, int width, int height, double frameRate);
	~coreEngine();

	void Start(); //Starts running the game; contains central game loop.
	void Stop();  //Stops running the game, and disables all subsystems.
	void cleanUp();

	void CreateWindow(std::string title);

protected:
private:
	void Run();
	coreEngine(const coreEngine& other) {}
	void operator=(const coreEngine& other) {}

	bool		m_isRunning;
	Game*		m_game;
	Window*		m_window;
	double		m_frameTime;

	int width;
	int height;
	
	RenderingEngine* renderingEngine;

};

#endif // COREENGINE_H
