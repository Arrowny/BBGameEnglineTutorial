#pragma once
#include <string>
#include <SDL\SDL.h>
#include <GL\glew.h>
#include <glm\common.hpp>

class Window
{
public:
	Window(int width, int height, std::string title);
	virtual ~Window();

	int GetWidth();
	int GetHeight();
	glm::vec2 GetCenter();
	std::string GetTitle() { return SDL_GetWindowTitle(m_window); }
	SDL_Window* GetSDLWindow() { return m_window; }

	void Render();
	void Update(SDL_Event e);
	bool isClosed() { return m_isClosed; }

protected:
private:
	Window(const Window& other) {}
	void operator=(const Window& other){}

	SDL_Window* m_window;
	SDL_GLContext m_glContext;
	bool m_isClosed;
};

