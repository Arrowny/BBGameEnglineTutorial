#ifndef GAME_H
#define GAME_H

#include "Input.h"
#include <iostream>
#include "Mesh.h"
#include "Shader.h"
#include "Transform.h"
#include "Timing.h"
#include "Material.h"

class Game
{
public:
	Game(){};
	virtual ~Game(){};

	virtual void init() = 0;

	virtual void input(Input& input) = 0;
	virtual void update() = 0;
	virtual void render() = 0;

protected:
private:
	//Mesh* m_mesh;
	//Shader* m_shader;
	//Transform* m_transform;
	//Camera* m_camera;
	//Material* m_material;
};

#endif // GAME_H

