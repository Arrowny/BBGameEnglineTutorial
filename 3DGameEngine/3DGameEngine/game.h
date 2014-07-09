#ifndef GAME_H
#define GAME_H

#include "Input.h"
#include <iostream>
#include "Mesh.h"
#include "Shader.h"
#include "Camera.h"
#include "Texture.h"
#include "pointLight.h"

class Game
{
public:
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
	pointLight* m_pLights;
	spotLight*  m_sLights;

};

#endif // GAME_H

