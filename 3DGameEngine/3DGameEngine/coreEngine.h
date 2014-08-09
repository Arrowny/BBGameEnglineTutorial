#ifndef COREENGINE_H
#define COREENGINE_H

#include <string>
#include "Window.h"
#include "Input.h"
#include "renderingEngine.h"
#include "physicsEngine.h"

class Game;

class CoreEngine
{
public:
	CoreEngine(Game* game, RenderingEngine* renderingEngine, PhysicsEngine* physicsEngine, Window* window, double frameRate);
	~CoreEngine(); 

	void Start(); //Starts running the game; contains central game loop.
	void Stop();  //Stops running the game, and disables all subsystems.
	void cleanUp();
	void Run();
	void Render();

	inline RenderingEngine* GetRenderingEngine() { return m_renderingEngine; }

	char* getOpenGLVersion();

protected:
private:
	bool				m_isRunning;
	Game*				m_game;
	Window*				m_window;
	double				m_frameTime;
	RenderingEngine*	m_renderingEngine;
	PhysicsEngine*		m_physicsEngine;


};

#endif // COREENGINE_H
