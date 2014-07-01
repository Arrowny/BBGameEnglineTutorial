#ifndef GAME_H
#define GAME_H

#include "Input.h"
#include <iostream>
#include "Mesh.h"
#include "Shader.h"

class Game
{
public:
	Game();
	//Game(Mesh* vertices, Shader* shader);
	~Game();

	void input();
	void update();
	void render();

protected:
private:

};

#endif // GAME_H

