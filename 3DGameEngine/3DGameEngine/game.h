#ifndef GAME_H
#define GAME_H

#include "Input.h"
#include <iostream>
#include "Mesh.h"
#include "Shader.h"

class Game
{
public:
	Game(Vertex* vertices);
	~Game();

	void input();
	void update();
	void render();

protected:
private:

};

#endif // GAME_H

