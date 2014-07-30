#pragma once
#include "gameComponent.h"
#include "Material.h"

class Mesh;
class Shader;
class coreEngine;

class SkyBoxRenderer : public gameComponent
{
public:
	SkyBoxRenderer(Material material);
	virtual ~SkyBoxRenderer();

	virtual void renderSkyBox(renderingEngine* renderingEngine);
	virtual void AddToEngine(coreEngine* engine);

private:
private:
	Mesh*	  m_meshCube;
	Material m_material;
	Shader* m_skyShader;
};

