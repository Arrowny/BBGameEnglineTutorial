#include "Game.h"
#include "main.h"

void Game::input(float delta){
	
	m_root.input(delta);

}

float tem = 0.0f;

void Game::update(float delta){

	tem += delta;

	float sinCounter = sinf(counter);
	float cosCounter = cosf(counter);

	//transform.GetPos().z = -10.0;
	//transform.GetPos().x = sinCounter * 2;
	//transform.GetRot().y = counter * 10;
	//transform.SetScale(glm::vec3(0.1f , 0.1f, 0.1f));

	/*m_pLights[0].position = (glm::fvec3(sinCounter * 2.5, 0, -0.5));
	m_pLights[1].position = (glm::fvec3(0.0, sinCounter * 2.5, -0.5));*/

	/*m_sLights[0].pointL.position = m_camera->getPos();
	m_sLights[0].direction = m_camera->getForward();*/

	//planeObject.GetTransform().GetRot().y = sinCounter * 30;
	m_root.update(delta);

	counter += 0.0003f;
}

void Game::render(renderingEngine* renderingEngine)
{
	renderingEngine->Render(&m_root);
}