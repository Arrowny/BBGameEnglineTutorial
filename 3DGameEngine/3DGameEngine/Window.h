#pragma once
#include <iostream>
#include <string>
#include <SDL\SDL.h>
#include "Input.h" 

namespace WindowSize
{
	extern float W_width;
	extern float W_height;
};

class Window
{
public:
	Window(int width, int height, const std::string& title);
	~Window();

	void Color(float r, float g, float b, float a);

	//Swap buffers to show latest image
	void Update();
	bool isClosed();
	void Render();
	void Dispose();
	void SwapBuffers();
	inline SDL_Window* GetSDLWindow() { return m_window; }
	inline Input GetInput() { return m_input; }
	inline float GetWidth() const { return WIDTH; }
	inline float GetHeight() const { return HEIGHT; }

	bool m_isClosed;

private:
	SDL_Window*		m_window;
	SDL_GLContext	m_glContext;
	Input			m_input;

	float WIDTH;
	float HEIGHT;

	//bool m_isClosed;
};


