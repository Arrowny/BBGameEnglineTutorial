#ifndef MAIN_H
#define MAIN_H

#include <string>
#include "Window.h"

class MainComponent
{
public:
	MainComponent();
	~MainComponent();

	void start();
	void stop();
	void run();
	void render();
	void cleanUp();

protected:
private:
	bool				m_isRunning;
	const Window*		m_window;

};

#endif // COREENGINE_H
