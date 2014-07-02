#ifndef GAME_H
#define GAME_H

#include "Input.h"
#include <iostream>
#include "Mesh.h"
#include "Shader.h"
#include "Transform.h"
#include "Timing.h"

class Game
{
public:
	//Game();
	Game(Mesh* mesh, Shader* shader, Transform transform);
	~Game();

	void input();
	void update();
	void render();

protected:
private:
	Mesh* m_mesh;
	Shader* m_shader;
	Transform m_transform;
};

#endif // GAME_H

