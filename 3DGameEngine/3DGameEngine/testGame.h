#pragma once

#include "Game.h"

class TestGame : public Game
{
public:
	TestGame() {}

	virtual void init();

	virtual ~TestGame();
protected:
private:
	TestGame(const TestGame& other) {}
	void operator=(const TestGame& other) {}

	gameObject m_planeObject;
	gameObject m_dirLightObj1;
	directionalLight dirLight1;

	Mesh* m_mesh;
	Material m_material;
	Texture* m_texture;
	meshRenderer* m_meshRenderer;
};

