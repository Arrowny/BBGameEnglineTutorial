#pragma once
#include "gameComponent.h"
class FreeLook : public GameComponent 
{
public:
	FreeLook();
	virtual ~FreeLook();

	void FreeLook::ProcessInput(Input* input, double delta);
};

