#ifndef GAME_H
#define GAME_H

#include "Input.h"
#include <iostream>
#include "Mesh.h"
#include "Shader.h"
#include "Camera.h"
#include "Texture.h"
#include "pointLight.h"
#include "meshRenderer.h"
#include "gameObject.h"

class Game
{
public:
	Game() {}
	~Game();

	void init();
	void input(const Input& input);
	void update();
	void render();

	inline gameObject& GetRoot() { return m_root; }

	float counter = 0.0f;

protected:
private:

	Mesh*			m_mesh;
	Shader*			m_shader;
	Transform		transform;
	Camera*			m_camera;
	Texture*		m_texture;
	glm::vec4*		m_color;
	Material		m_material;
	pointLight*		m_pLights;
	spotLight*		m_sLights;
	meshRenderer*	m_meshRenderer;
	gameObject		m_root;

};

#endif // GAME_H

