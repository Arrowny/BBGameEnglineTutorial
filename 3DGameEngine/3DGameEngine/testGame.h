#pragma once

#include "Game.h"

class TestGame : public Game
{
public:
	TestGame() {}

	virtual void init();
	virtual void update(float delta);

	virtual ~TestGame();
protected:
private:
	TestGame(const TestGame& other) {}
	void operator=(const TestGame& other) {}

	gameObject* m_planeObject;
	gameObject* m_planeObject2;
	gameObject* m_planeObject3;
	gameObject* m_dirLightObj1;
	directionalLight* dirLight1;
	directionalLight* dirLight2;
	directionalLight* dirLight3;
	gameObject* m_pLightObj1;
	pointLight* pLight1;
	pointLight* pLight2;
	pointLight* pLight3;
	gameObject* m_sLightObj1;
	gameObject* m_sLightObj2;
	spotLight* sLight1;
	spotLight* sLight2;

	Mesh* m_mesh;
	Mesh* m_mesh2;
	Mesh* m_mesh3;
	Material m_material;
	Material m_material2;
	Material m_material3;
	Texture* m_texture;
	Texture* m_texture2;
	Texture* m_texture3;
	meshRenderer* m_meshRenderer;
	meshRenderer* m_meshRenderer2;
	meshRenderer* m_meshRenderer3;
};

