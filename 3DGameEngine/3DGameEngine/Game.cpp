#include "Game.h"
#include "main.h"

Game::Game(Mesh* mesh, Shader* shader, Camera* camera, Texture* texture, glm::vec4* color):
m_mesh(mesh),
m_shader(shader),
m_camera(camera),
m_texture(texture),
m_color(color)
{
}


Game::~Game()
{
}

void Game::input(const Input& input){

	m_camera->input(input);

}

void Game::update(){

	float sinCounter = sinf(counter);
	float cosCounter = cosf(counter);

	//transform.GetPos().z = -10.0;
	//transform.GetPos().x = sinCounter * 2;
	transform.GetRot().y = counter * 50;
	//transform.SetScale(glm::vec3(0.1f , 0.1f, 0.1f));

	m_shader->Update(transform, *m_camera, *m_color);
	counter += 0.0003f;

}

void Game::render(){

	m_shader->Bind();
	m_texture->Bind(0);
	m_mesh->Draw();

}