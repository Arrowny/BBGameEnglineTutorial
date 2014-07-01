#ifndef GAME_H
#define GAME_H

#include "Input.h"
#include <iostream>
#include "Mesh.h"
#include "Shader.h"
#include "Camera.h"

class Game
{
public:
	Game(Mesh* mesh, Shader* shader, Camera* camera);
	~Game();

	void input(const Input& input);
	void update();
	void render();

protected:
private:

	Mesh*		m_mesh;
	Shader*		m_shader;
	Transform	transform;
	Camera*		m_camera;

};

#endif // GAME_H

