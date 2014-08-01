#ifndef GAME_H
#define GAME_H

#include "gameObject.h"
#include "coreEngine.h"

class Game
{
public:
	Game() {}

	virtual void init() {};
	void input(const Input& input, float delta);
	virtual void update(float delta);
	void render(RenderingEngine* renderingEngine);
	
	inline GameObject& GetRoot() { return m_root; }
	inline void SetEngine(CoreEngine* engine) { m_root.SetEngine(engine); }

	float counter = 0.0f;

protected:
	void AddToScene(GameObject* child) { m_root.AddChild(child); }

	GameObject m_root;

private:

	

};

#endif // GAME_H

