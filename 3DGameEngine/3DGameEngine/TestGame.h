#ifndef TESTGAME_H
#define TESTGAME_H

#include "Game.h"
//#include "MeshRenderer.h"

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
	Shader* m_shader;
	Transform* m_transform;
	Camera* m_camera;
	Material* m_material;
};

#endif // TestGame_H

