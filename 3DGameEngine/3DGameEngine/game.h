#ifndef GAME_H
#define GAME_H

#include "Input.h"
#include <iostream>

class Game
{
public:
	Game();
	~Game();

	void input();
	void update();
	void render();

protected:
private:

};

#endif // GAME_H

