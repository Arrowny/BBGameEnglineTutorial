#pragma once

#include <glm\glm.hpp>
#include <glm\gtx\transform.hpp>
#include "Timing.h"
#include "Input.h"
#include "Window.h"
#include "gameComponent.h"

struct FreeMove : public gameComponent
{
	virtual void AddToEngine(coreEngine* engine);

	virtual void input(const Input& input, float delta)
	{
		float movAmt = (float)(10 * delta);

		if (input.GetKey(input.KEY_W))
		{
			if (input.GetKey(input.KEY_LSHIFT))
			{
				move(GetTransform().GetTransformedForward(), movAmt * 3);
			}

			move(GetTransform().GetTransformedForward(), movAmt);
		}
		if (input.GetKey(input.KEY_S))
		{
			if (input.GetKey(input.KEY_LSHIFT))
			{
				move(GetTransform().GetTransformedForward(), -movAmt * 3);
			}

			move(GetTransform().GetTransformedForward(), -movAmt);
		}
		if (input.GetKey(input.KEY_A))
		{
			if (input.GetKey(input.KEY_LSHIFT))
			{
				move(GetTransform().GetTransformedLeft(), -movAmt * 3);
			}

			move(GetTransform().GetTransformedLeft(), -movAmt);
		}
		if (input.GetKey(input.KEY_D))
		{
			if (input.GetKey(input.KEY_LSHIFT))
			{
				move(GetTransform().GetTransformedRight(), -movAmt * 3);
			}

			move(GetTransform().GetTransformedRight(), -movAmt);
		}
		if (input.GetKey(input.KEY_SPACE))
			move(GetTransform().GetTransformedUp(), movAmt);
		if (input.GetKey(input.KEY_LCTRL))
			move(GetTransform().GetTransformedUp(), -movAmt);
	}

	virtual void move(glm::fvec3 dir, float amt)
	{
		GetTransform().SetPos(GetTransform().GetPos() + (dir * amt));
	}

};