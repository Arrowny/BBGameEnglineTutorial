#pragma once
#include "transform.h"
class GameComponent
{
public:
	GameComponent();
	//virtual void init();
	virtual void input(Transform transform) { ; }
	virtual void update(Transform transform) {; }
	virtual void render(Transform transform) = 0;// {; }
	//void input(Transform transform);
	//void update(Transform transform);
	//void render(Transform transform);
	virtual ~GameComponent() {};
};

