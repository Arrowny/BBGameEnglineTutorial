#ifndef GAME_H
#define GAME_H

#include "gameObject.h"
#include "coreEngine.h"

class Game
{
public:
	Game() {}

	virtual void init() {};
	void input(float delta);
	virtual void update(float delta);
	void render(renderingEngine* renderingEngine);
	
	inline gameObject& GetRoot() { return m_root; }
	inline void SetEngine(coreEngine* engine) { m_root.SetEngine(engine); }

	float counter = 0.0f;

protected:
	void AddToScene(gameObject* child) { m_root.AddChild(child); }

	gameObject m_root;

private:

	

};

#endif // GAME_H

