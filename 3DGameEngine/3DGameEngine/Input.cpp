#include "Input.h"
#include "Window.h"
#include <SDL/SDL.h>
#include <cstring>

//Input::Input(Window* window) :
//m_mouseX(0),
//m_mouseY(0),
//m_window(window)
//{
//	memset(m_inputs, 0, NUM_KEYS * sizeof(bool));
//	memset(m_downKeys, 0, NUM_KEYS * sizeof(bool));
//	memset(m_upKeys, 0, NUM_KEYS * sizeof(bool));
//
//	memset(m_mouseInput, 0, NUM_MOUSEBUTTONS * sizeof(bool));
//	memset(m_downMouse, 0, NUM_MOUSEBUTTONS * sizeof(bool));
//	memset(m_upMouse, 0, NUM_MOUSEBUTTONS * sizeof(bool));
//}

Input::Input() :
m_mouseX(0),
m_mouseY(0)
{
	memset(m_inputs, 0, NUM_KEYS * sizeof(bool));
	memset(m_downKeys, 0, NUM_KEYS * sizeof(bool));
	memset(m_upKeys, 0, NUM_KEYS * sizeof(bool));

	memset(m_mouseInput, 0, NUM_MOUSEBUTTONS * sizeof(bool));
	memset(m_downMouse, 0, NUM_MOUSEBUTTONS * sizeof(bool));
	memset(m_upMouse, 0, NUM_MOUSEBUTTONS * sizeof(bool));
}

void Input::Update()
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

	SDL_Event e;
	while (SDL_PollEvent(&e))
	{
		if (e.type == SDL_QUIT)
		{
			m_window->m_isClosed = true;
		}

		if (e.type == SDL_MOUSEMOTION)
		{
			SetMouseX(e.motion.x);
			SetMouseY(e.motion.y);
		}

		if (e.type == SDL_KEYDOWN)
		{
			int value = e.key.keysym.scancode;
			std::cout << "Down:" << value << std::endl;

			SetKey(value, true);
			SetKeyDown(value, true);


		}
		if (e.type == SDL_KEYUP)
		{
			int value = e.key.keysym.scancode;
			std::cout << "Up:" << value << std::endl;

			SetKey(value, false);
			SetKeyUp(value, true);


		}
		if (e.type == SDL_MOUSEBUTTONDOWN)
		{
			int value = e.button.button;
			std::cout << "MDown:" << value << std::endl;

			SetMouse(value, true);
			SetMouseDown(value, true);
		}
		if (e.type == SDL_MOUSEBUTTONUP)
		{
			int value = e.button.button;
			std::cout << "MUp:" << value << std::endl;

			SetMouse(value, false);
			SetMouseUp(value, true);
		}
	}
}

void Input::SetCursor(bool visible) const
{
	if (visible)
		SDL_ShowCursor(1);
	else
		SDL_ShowCursor(0);
}

void Input::SetMousePosition(const glm::fvec2& pos) const
{
	SDL_WarpMouseInWindow(m_window->GetSDLWindow(), (int)pos.x, (int)pos.y);
	//	SDLSetMousePosition((int)pos.GetX(), (int)pos.GetY());
}
