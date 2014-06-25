#ifndef COREENGINE_H
#define COREENGINE_H

#include <string>
#include "Window.h"
#include "Game.h"
#include "Input.h"

class coreEngine
{
public:
	coreEngine(Game* game, Window* window, double frameRate);
	~coreEngine();

	void Start(); //Starts running the game; contains central game loop.
	void Stop();  //Stops running the game, and disables all subsystems.
	void cleanUp();
	void Run();
	void Render();

protected:
private:
	bool		m_isRunning;
	Game*		m_game;
	Window*		m_window;
	double		m_frameTime;
	

};

#endif // COREENGINE_H
