#include "Game.h"
#include "main.h"

Game::Game(Mesh* mesh, Shader* shader, Camera* camera):
m_mesh(mesh),
m_shader(shader),
m_camera(camera)
{
}


Game::~Game()
{
}

void Game::input(const Input& input){

	m_camera->input(input);

}

float counter = 0.0f;


void Game::update(){

	float sinCounter = sinf(counter);
	float cosCounter = cosf(counter);

	transform.GetPos().z = -3.0;
	transform.GetRot().y = counter * 50;
	//transform.SetScale(glm::vec3(0.1f , 0.1f, 0.1f));

	m_shader->Update(transform, *m_camera);
	counter += 0.0003f;

}

void Game::render(){

	m_shader->Bind();
	m_mesh->Draw();

}