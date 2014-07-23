#ifndef TESTGAME_H
#define TESTGAME_H

#include "Game.h"
#include "MeshRenderer.h"
#include "GameObject.h"

class GameObject;
class TestGame : public Game
{
public:
	TestGame();
	~TestGame();

	void init();
	//void input(Input& input);
	//void update();
	//void render();

protected:
private:
	Mesh* m_mesh;
	Material m_material;
	Material m_material2;
	MeshRenderer* m_meshRenderer;
};

#endif // TestGame_H

