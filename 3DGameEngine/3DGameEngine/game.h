#ifndef GAME_H
#define GAME_H

#include "Input.h"
#include "Window.h"
#include "Mesh.h"
#include "BasicShader.h"
#include "Transform.h"
#include "Camera.h"
#include "GameObject.h"
#include "MeshRenderer.h"

class Game
{
public:

	virtual void init() = 0;

	void input(float delta)  //Input& input,,,,,, use m_window to get input in the coreEngine
	{
		GetRootObject().input(delta);
	}
	void update(float delta)
	{
		GetRootObject().update(delta);
	}
	void render(RenderingEngine* renderingEngine)
	{
		renderingEngine->render(&GetRootObject());
	}

	void AddObject(GameObject* root)
	{
		GetRootObject().AddChild(root);
	}

	void SetEngine(coreEngine* engine) {GetRootObject().SetEngine(engine); }
protected:

private:
	inline GameObject& GetRootObject()
	{
		return m_root;
	}
	GameObject m_root;
	Mesh* m_mesh;
	Shader* m_shader;
	Transform* m_transform;
	Camera* m_camera;
	Material* m_material;
};

#endif // GAME_H

