#ifndef GAMECOMPONENT_H_INCLUDED
#define GAMECOMPONENT_H_INCLUDED

#include "Transform.h"
#include "Shader.h"
class renderingEngine;
class Shader;

class gameComponent
{
public:
	virtual void input(const Transform& transform) {}
	virtual void update(const Transform& transform) {}
	virtual void render(const Transform& transform, Shader* shader, renderingEngine* renderingEngine) {}
};

#endif // GAMECOMPONENT_H_INCLUDED
