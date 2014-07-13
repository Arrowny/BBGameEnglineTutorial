#pragma once
#include "gameObject.h"
#include <string>
#include <GL\glew.h>
#include "shader.h"

class RenderingEngine
{
public:
	RenderingEngine();
	virtual ~RenderingEngine();

	void RenderGameObject(GameObject* gameObject, Shader* shader);
	void Clear() { glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); }
	void setTextures(bool enabled);
	std::string getOpenGLVersion();

private:
	RenderingEngine(const RenderingEngine& other) {}
	void operator=(const RenderingEngine& other) {}
};

