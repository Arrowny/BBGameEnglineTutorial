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
	directionalLight* dirLight1;
	directionalLight* dirLight2;
	directionalLight* dirLight3;
	gameObject m_pLightObj1;
	pointLight* pLight1;
	pointLight* pLight2;
	pointLight* pLight3;
	gameObject m_sLightObj1;
	spotLight* sLight1;
	spotLight* sLight2;

	Mesh* m_mesh;
	Material m_material;
	Texture* m_texture;
	meshRenderer* m_meshRenderer;
};

