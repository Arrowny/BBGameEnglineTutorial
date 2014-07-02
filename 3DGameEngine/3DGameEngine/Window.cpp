#include "Window.h"
#include <GL\glew.h>
#include <iostream>

int Window::m_width = 0;
int Window::m_height = 0;

Window::Window(int width, int height, const std::string& title):
m_input(this)
{
	Window::m_width = width;
	Window::m_height = height;

	SDL_Init(SDL_INIT_EVERYTHING);

	SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_ALPHA_SIZE, 8); //How transparent
	SDL_GL_SetAttribute(SDL_GL_BUFFER_SIZE, 32);
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);

	m_window = SDL_CreateWindow(title.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, SDL_WINDOW_OPENGL);
	m_glContext = SDL_GL_CreateContext(m_window);

	GLenum status = glewInit();

	if (status != GLEW_OK){

		std::cerr << "GLEW failed" << std::endl;

	}

	m_isClosed = false;
}


Window::~Window(){

	SDL_GL_DeleteContext(m_glContext);
	SDL_GL_DeleteContext(m_window);
	SDL_Quit();
}

void Window::ClearColor(float r, float g, float b, float a){

	glClearColor(r, g, b, a);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

bool Window::isClosed(){

	return m_isClosed;
}

void Window::Update()
{
	
	for (int i = 0; i < Input::NUM_MOUSEBUTTONS; i++)
	{
		m_input.SetMouseDown(i, false);
		m_input.SetMouseUp(i, false);
	}

	for (int i = 0; i < Input::NUM_KEYS; i++)
	{
		m_input.SetKeyDown(i, false);
		m_input.SetKeyUp(i, false);
	}

	SDL_Event e;

	while (SDL_PollEvent(&e))
	{
		if (e.type == SDL_QUIT)
		{
			m_isClosed = true;
		}

		if (e.type == SDL_MOUSEMOTION)
		{
			m_input.SetMouseX(e.motion.x);
			m_input.SetMouseY(e.motion.y);
		}

		if (e.type == SDL_KEYDOWN)
		{
			int value = e.key.keysym.scancode;
			std::cout << "Down:" << value << std::endl;

			m_input.SetKey(value, true);
			m_input.SetKeyDown(value, true);
		}
		if (e.type == SDL_KEYUP)
		{
			int value = e.key.keysym.scancode;
			std::cout << "Up:" << value << std::endl;

			m_input.SetKey(value, false);
			m_input.SetKeyUp(value, true);
		}
		if (e.type == SDL_MOUSEBUTTONDOWN)
		{
			int value = e.button.button;
			std::cout << "MDown:" << value << std::endl;

			m_input.SetMouse(value, true);
			m_input.SetMouseDown(value, true);
		}
		if (e.type == SDL_MOUSEBUTTONUP)
		{
			int value = e.button.button;
			std::cout << "MUp:" << value << std::endl;

			m_input.SetMouse(value, false);
			m_input.SetMouseUp(value, true);
		}
	}
}

void Window::Render(){

	//Color(1.0f, 0.5f, 0.3f, 0.5f);
	Update();

}

void Window::Dispose(){

	SDL_GL_DeleteContext(m_window);

}

void Window::swapBuffers(){

	SDL_GL_SwapWindow(m_window);

}

int Window::getWidth(){

	return m_width;
}

int Window::getHeight(){

	return m_height;
}