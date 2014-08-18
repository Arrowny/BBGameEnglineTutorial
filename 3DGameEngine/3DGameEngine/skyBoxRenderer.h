#pragma once
#include "gameComponent.h"
#include "Material.h"

class Mesh;
class Shader;
class CoreEngine;

class SkyBoxRenderer : public GameComponent
{
public:
	SkyBoxRenderer(Material material);
	virtual ~SkyBoxRenderer();

	virtual void renderSkyBox(RenderingEngine* renderingEngine);
	virtual void AddToEngine(CoreEngine* engine);

private:
private:
	Mesh*	  m_meshCube;
	Material  m_material;
	Shader*   m_skyShader;
};

