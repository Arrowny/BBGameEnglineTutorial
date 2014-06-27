#ifndef COREENGINE_H
#define COREENGINE_H

#include <string>
#include "Window.h"
#include "Game.h"
#include "Input.h"
#include "RenderUtil.h"
#include "Mesh.h"
#include "Shader.h"

class coreEngine
{
public:
	coreEngine(Game* game, RenderUtil* renderUtil, Window* window, Mesh* mesh, Shader* shader, double frameRate);
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
	RenderUtil*	m_renderUtil;
	double		m_frameTime;
	Mesh*		m_mesh;
	Shader*		m_shader;
	

};

#endif // COREENGINE_H
