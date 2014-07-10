#pragma once

#include "gameObject.h"

class renderingEngine
{
public:
	renderingEngine();

	void Render(gameObject* object);
	char* getOpenGLVersion();

	virtual ~renderingEngine();
protected:
private:
	renderingEngine(const renderingEngine& other) {}
	void operator=(const renderingEngine& other) {}
};

