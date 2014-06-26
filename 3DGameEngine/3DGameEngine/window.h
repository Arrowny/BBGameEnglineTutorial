#pragma once
#include <string>
#include <SDL\SDL.h>
#include <GL\glew.h>

class Window
{
public:
	Window(int width, int height, std::string title);
	virtual ~Window();

	void Render();
	int GetWidth();
	int GetHeight();
	std::string GetTitle() { return SDL_GetWindowTitle(m_window); }
	SDL_Window* GetSDLWindow() { return m_window; }

	void Clear() { glClear(GL_COLOR_BUFFER_BIT); }
	void SwapBuffers();
	void Update();

	bool isClosed() { return m_isClosed; }
protected:
private:
	Window(const Window& other) {}
	void operator=(const Window& other){}

	SDL_Window* m_window;
	SDL_GLContext m_glContext;
	bool m_isClosed;
};

