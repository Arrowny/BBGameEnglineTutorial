#ifndef GAME_H
#define GAME_H

#include "Input.h"
#include <iostream>
#include "Mesh.h"
#include "Shader.h"
#include "Camera.h"
#include "Texture.h"

class Game
{
public:
	/*Game(Mesh* mesh, Shader* shader, Camera* camera, Texture* texture, glm::vec4* color);*/
	Game() {}
	~Game();

	void init();
	void input(const Input& input);
	void update();
	void render();

	float counter = 0.0f;

protected:
private:

	Mesh*		m_mesh;
	Shader*		m_shader;
	Transform	transform;
	Camera*		m_camera;
	Texture*	m_texture;
	glm::vec4*	m_color;
	Material	m_material;

};

#endif // GAME_H

