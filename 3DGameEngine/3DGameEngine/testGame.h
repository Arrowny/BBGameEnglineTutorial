#pragma once
#include "game.h"
#include "shader.h"
#include "transform.h"
#include "mesh.h"
#include "material.h"
#include "texture.h"
#include "vertex.h"
#include "timing.h"
#include "resourceLoader.h"
#include "camera.h"
#include "gameObject.h"
#include "meshRenderer.h"

class TestGame :
	public Game
{
public:
	TestGame() {}
	virtual ~TestGame();

	virtual void Init(Window* window) override;

private:
	TestGame(const TestGame& other) {}
	void operator=(const TestGame& other) {}

	Transform* m_worldTransform;

	GameObject pyrimidGameObject;
	DirectionalLight* dLight;
	GameObject dLightObj;
	PointLight* pLight1;
	GameObject pLight1Obj;
	PointLight* pLight2;
	GameObject pLight2Obj;
	SpotLight* sLight;
	GameObject sLightObj;
	MeshRenderer* meshComponent;

};

