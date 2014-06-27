#ifndef GAME_H
#define GAME_H

#include "Input.h"
#include <iostream>
#include "Mesh.h"
#include "Shader.h"

class Game
{
public:
	Game(Mesh* mesh, Shader* shader);
	~Game();

	void input();
	void update();
	void render();

protected:
private:

	Mesh*		m_mesh;
	Shader*		m_shader;
	
};

#endif // GAME_H

