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

	virtual void init() {};
	void input(float delta);
	void update(float delta);
	void render(renderingEngine* renderingEngine);
	
	inline gameObject& GetRoot() { return m_root; }

	float counter = 0.0f;

protected:
	void AddToScene(gameObject* child) { m_root.AddChild(child); }

	Mesh*			m_mesh;
	Shader*			m_shader;
	Transform		transform;
	Camera*			m_camera;
	Texture*		m_texture;
	glm::vec4*		m_color;
	Material		m_material;
	pointLight*		m_pLights;
	spotLight*		m_sLights;
	gameObject		m_root;

private:

	

};

#endif // GAME_H

