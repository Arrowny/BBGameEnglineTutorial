#pragma once

#include "Game.h"
#include "Mesh.h"
#include "Shader.h"
#include "Camera.h"
#include "Texture.h"
#include "textureCube.h"
#include "meshRenderer.h"
#include "skyBoxRenderer.h"
#include "particleSystem.h"
#include "Input.h"
#include <iostream>
#include "freeLook.h"
#include "freeMove.h"
#include "physicsAdvection.h"

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

	GameObject* m_planeObject;
	GameObject* m_planeObject2;
	GameObject* m_planeObject3;
	GameObject* m_camera;
	GameObject* m_dirLightObj1;
	GameObject* m_skyBoxObject;
	GameObject* m_pLightObj1;
	GameObject* m_sLightObj1;
	GameObject* m_sLightObj2;
	GameObject* m_basicPSObj;

	DirectionalLight* dirLight1;
	DirectionalLight* dirLight2;
	DirectionalLight* dirLight3;

	PointLight* pLight1;
	PointLight* pLight2;
	PointLight* pLight3;

	SpotLight* sLight1;
	SpotLight* sLight2;

	Mesh* m_mesh;
	Mesh* m_mesh2;
	Mesh* m_mesh3;
	Material m_material;
	Material m_material2;
	Material m_material3;
	Material m_particleMaterial;
	Material m_particleMaterial2;
	Material m_particleMaterial3;
	Material m_sky;
	Texture* m_texture;
	Texture* m_texture2;
	Texture* m_texture3;
	Texture* m_particleTexture;
	Texture* m_skyTexture;
	MeshRenderer* m_meshRenderer;
	MeshRenderer* m_meshRenderer2;
	MeshRenderer* m_meshRenderer3;
	SkyBoxRenderer* m_skyBoxrenderer;
	ParticleSystem* m_basicPS;
	ParticleSystem* m_luminousPS;
	ParticleSystem* m_luminousPS2;
	ParticleSystem* m_luminousPS3;

	PhysicsAdvection* m_phyAdvect;
	Texture3D* m_advectTexture;
	ParticleSystem* m_advectPS;
};

