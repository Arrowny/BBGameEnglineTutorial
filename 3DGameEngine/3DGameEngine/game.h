#ifndef GAME_H
#define GAME_H

#include "Input.h"
#include <iostream>
#include "Mesh.h"
#include "Shader.h"
#include "Transform.h"
//#include "Texture.h"
#include "Material.h"
#include "Timing.h"

class Game
{
public:
	//Game();
	Game(Mesh* mesh, Shader* shader, Transform transform, Camera camera, Texture* m_texture);
	~Game();

	void input(Input& input);
	void update();
	void render();

protected:
private:
	Mesh* m_mesh;
	Shader* m_shader;
	Transform m_transform;
	Camera m_camera;
	Texture* m_texture;
};

#endif // GAME_H

