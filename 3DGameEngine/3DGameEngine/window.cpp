#include "window.h"
#include <GL\glew.h>
#include <iostream>



Window::Window(int width, int height, std::string title)
{
	SDL_Init(SDL_INIT_EVERYTHING);

	SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_ALPHA_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_BUFFER_SIZE, 32);
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);


	m_window = SDL_CreateWindow(title.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, SDL_WINDOW_OPENGL);
	m_glContext = SDL_GL_CreateContext(m_window);

	GLenum status = glewInit();

	if (status != GLEW_OK)
	{
		std::cerr << "Error: GLEW failed to initialize" << std::endl;
	}

	m_isClosed = false;

	InitGraphics();
}


Window::~Window()
{
	SDL_GL_DeleteContext(m_glContext);
	SDL_DestroyWindow(m_window);
	SDL_Quit();
}

void Window::Render()
{
	Clear();
	SwapBuffers();
}

int Window::GetWidth()
{
	int* width;
	int* height;

	SDL_GetWindowSize(m_window, width, height);

	return *width;
}

int Window::GetHeight()
{
	int* width;
	int* height;

	SDL_GetWindowSize(m_window, width, height);

	return *height;
}

void Window::InitGraphics()
{
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);

	glFrontFace(GL_CCW);
	glCullFace(GL_BACK);
	glEnable(GL_CULL_FACE);
	glEnable(GL_DEPTH_TEST);

	//TODO: Initialize depth clamp

	glEnable(GL_FRAMEBUFFER_SRGB);
}

void Window::SwapBuffers()
{
	SDL_GL_SwapWindow(m_window);
}

void Window::Update(SDL_Event e)
{
	if (e.type == SDL_QUIT)
	{
		m_isClosed = true;
	}
}