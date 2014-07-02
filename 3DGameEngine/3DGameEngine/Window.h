#pragma once
#include <iostream>
#include <string>
#include <SDL\SDL.h>
#include "Input.h" 

class Window
{
public:
	Window(int width, int height, const std::string& title);
	~Window();

	void ClearColor(float r, float g, float b, float a);

	//Swap buffers to show latest image
	void Update();
	bool isClosed();
	void Render();
	void Dispose();
	void swapBuffers();
	inline SDL_Window* GetSDLWindow() { return m_window; }
	inline const Input& GetInput()	const { return m_input; }

	bool m_isClosed;
	static int getWidth();
	static int getHeight();

private:
	SDL_Window*		m_window;
	SDL_GLContext	m_glContext;
	Input			m_input;
	static int		m_width;
	static int		m_height;

	//Check if window is 'X'ed
	//bool m_isClosed;
};


