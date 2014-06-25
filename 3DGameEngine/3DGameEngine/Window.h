#pragma once
#include <iostream>
#include <string>
#include <SDL\SDL.h>

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
	inline SDL_Window* GetSDLWindow() { return m_window; }

	bool m_isClosed;

private:
	SDL_Window* m_window;
	SDL_GLContext m_glContext;

	//Check if window is 'X'ed
	//bool m_isClosed;
};


