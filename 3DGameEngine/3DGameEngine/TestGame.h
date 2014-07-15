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

	void input(Input& input);
	void update();
	void render();

protected:
private:
	Mesh* m_mesh;
	//Shader* m_shader;
	//Transform m_transform;
	Camera m_camera;
	Material m_material;
	MeshRenderer* m_meshRenderer;

	GameObject m_root;
};

#endif // TestGame_H

