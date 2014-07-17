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
#include "gameObject.h"
#include "meshRenderer.h"
#include "camera.h"


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

	MeshRenderer* meshComponent; GameObject pyrimidGameObject;
	MeshRenderer* meshComponent2; GameObject pyrimidGameObject2;
	DirectionalLight* dLight; GameObject dLightObj;
	PointLight* pLight1; GameObject pLight1Obj;
	PointLight* pLight2; GameObject pLight2Obj;
	SpotLight* sLight; GameObject sLightObj;
	Camera* camera; GameObject cameraObj;
	
	

};

