#ifndef COREENGINE_H
#define COREENGINE_H

#include <string>
#include "Window.h"
#include "TestGame.h"
#include "Input.h"
#include "RenderUtil.h"

class coreEngine
{
public:
	coreEngine(Game* game, int width, int height, double frameRate);
	~coreEngine();

	void Start(); //Starts running the game; contains central game loop.
	void Stop();  //Stops running the game, and disables all subsystems.
	void cleanUp();
	void Run();
	void Render();

	void CreateWindow(std::string title);
protected:
private:

	void InitializeRenderingSystem();

	bool		m_isRunning;
	Game*		m_game;
	Window*		m_window;
	RenderUtil*	m_renderUtil;
	double		m_frameTime;

	int width;
	int height;
	

};

#endif // COREENGINE_H
