#pragma once
#include <string>
#include <SDL\SDL.h>

class Window
{
public:
	Window(int width, int height, std::string title);
	virtual ~Window();

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

