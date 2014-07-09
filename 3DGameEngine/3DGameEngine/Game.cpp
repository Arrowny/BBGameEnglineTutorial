#include "Game.h"
#include "Input.h"

Game::Game(Mesh* mesh, Shader* shader, Transform transform, Camera camera, Texture* texture) :
m_mesh(mesh),
m_shader(shader),
m_transform(transform),
m_camera(camera),
m_texture(texture)
{}

Game::~Game()
{
}

void Game::input(Input& input){
	m_camera.Input(input);
}

float temp = 0.0f;

void Game::update(){
	temp += Time::getDelta();

	//m_shader->Update(glm::abs(sin(temp))+0.5);

	//m_transform.SetPos(glm::vec3(sin(temp), 0, 0));
	m_transform.SetRot(glm::vec3(0, sin(temp) * 300, 0));
}

void Game::render(){
	m_shader->Bind();
	m_shader->Update(m_transform, m_camera);
	m_texture->Bind(0);
	m_mesh->Draw();
}