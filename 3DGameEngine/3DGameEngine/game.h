#ifndef GAME_H
#define GAME_H

#include "Input.h"
#include <iostream>
#include "Mesh.h"
#include "Shader.h"
#include "Transform.h"
#include "Timing.h"
#include "Material.h"
#include "GameObject.h"

class Game
{
public:

	virtual void init() = 0;

	void input(Input& input)  // use m_window to get input in the coreEngine
	{
		//m_camera->Input(input);
		GetRootObject().input();
	}
	void update()
	{
		GetRootObject().update();
	}
	//void render()
	//{
	//	GetRootObject().render(m_camera);
	//}

	inline GameObject& GetRootObject()
	{ 
		return m_root;
	}
protected:
private:

	GameObject m_root;
	Mesh* m_mesh;
	Shader* m_shader;
	Transform* m_transform;
	Camera* m_camera;
	Material* m_material;
};

#endif // GAME_H

