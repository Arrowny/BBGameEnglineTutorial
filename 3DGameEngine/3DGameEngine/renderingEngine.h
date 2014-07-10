#pragma once

#include "gameObject.h"

class renderingEngine
{
public:
	renderingEngine();

	void Render(gameObject* object);

	virtual ~renderingEngine();
protected:
private:
	renderingEngine(const renderingEngine& other) {}
	void operator=(const renderingEngine& other) {}
};

