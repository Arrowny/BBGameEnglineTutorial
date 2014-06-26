#include "input.h"
#include "window.h"
#include <SDL/SDL.h>
#include <cstring>

Input::Input(Window* window) :
	m_mouseX(0),
	m_mouseY(0),
	m_window(window)
{
	memset(m_inputs, 0, NUM_KEYS * sizeof(bool));
	memset(m_downKeys, 0, NUM_KEYS * sizeof(bool));
	memset(m_upKeys, 0, NUM_KEYS * sizeof(bool));
	
	memset(m_mouseInput, 0, NUM_MOUSEBUTTONS * sizeof(bool));
	memset(m_downMouse, 0, NUM_MOUSEBUTTONS * sizeof(bool));
	memset(m_upMouse, 0, NUM_MOUSEBUTTONS * sizeof(bool));
}

void Input::Clear()
{
	for (int i = 0; i < Input::NUM_MOUSEBUTTONS; i++)
	{
		SetMouseDown(i, false);
		SetMouseUp(i, false);
	}

	for (int i = 0; i < Input::NUM_KEYS; i++)
	{
		SetKeyDown(i, false);
		SetKeyUp(i, false);
	}
}

void Input::Update(SDL_Event e)
{

	switch (e.type) 
	{
		case SDL_MOUSEMOTION:
		{
			SetMouseX(e.motion.x);
			SetMouseY(e.motion.y);
			break;
		}

		case SDL_KEYDOWN:
		{
			int value = e.key.keysym.scancode;

			SetKey(value, true);
			SetKeyDown(value, true);
			break;
		}

		case SDL_KEYUP:
		{
			int value = e.key.keysym.scancode;

			SetKey(value, false);
			SetKeyUp(value, true);
			break;
		}

		case SDL_MOUSEBUTTONDOWN:
		{
			int value = e.button.button;

			SetMouse(value, true);
			SetMouseDown(value, true);
			break;
		}

		case SDL_MOUSEBUTTONUP:
		{
			int value = e.button.button;

			SetMouse(value, false);
			SetMouseUp(value, true);
			break;
		}
	}
}

void Input::SetCursor(bool visible) const
{
	if(visible)
		SDL_ShowCursor(1);
	else
		SDL_ShowCursor(0);
}

void Input::SetMousePosition(const glm::vec2& pos) const
{
	SDL_WarpMouseInWindow(m_window->GetSDLWindow(), (int)pos.x, (int)pos.y);
}
