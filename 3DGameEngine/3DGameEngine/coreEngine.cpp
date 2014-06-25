#include "coreEngine.h"
#include "timing.h"


CoreEngine::CoreEngine(Window* window):
m_window(window)
{
	isRunning = false;
}

void CoreEngine::start()
{
	if (isRunning) { return; }

	isRunning = true;
	while (isRunning)
	{
		if (m_window->isClosed())
		{
			stop();
		}

		m_window->Render();
	}
}

void CoreEngine::stop()
{
	if (!isRunning){ return; }

	isRunning = false;
}


