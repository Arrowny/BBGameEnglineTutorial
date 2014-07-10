#include "Game.h"
#include "Input.h"

Game::Game() 
{
	Vertex vertices[] = { Vertex(glm::vec3(-1.0, -1.0, 0.0), glm::vec2(0.0, 0.5)),
		Vertex(glm::vec3(0.0, 1.0, 0.0), glm::vec2(0.5, 0.5)),
		Vertex(glm::vec3(1.0, -1.0, 0.0), glm::vec2(1.0, 0.5)),
		Vertex(glm::vec3(0.0, -1.0, 1.0), glm::vec2(0.0, 1.0)),
		Vertex(glm::vec3(0.0, -1.0, -1.0), glm::vec2(0.5, 0.0)) };

	unsigned int indices[] = { 0, 3, 1,
		3, 2, 1,
		0, 2, 3,
		0, 4, 2,
		0, 1, 4,
		4, 1, 2 };


	//m_mesh = new Mesh(vertices, sizeof(vertices) / sizeof(vertices[0]), indices, sizeof(indices) / sizeof(indices[0]));
	m_mesh = new Mesh("./res/cube.obj");
	m_shader = new Shader("./res/phongShader");
	m_transform = new Transform();
	m_camera = new Camera(glm::vec3(0, 0, -4), 70.0f, (float)WindowParameter::width/ (float)WindowParameter::height, 1.0f, 1000.0f);
	m_material = new Material( new Texture("./res/bricks.jpg"), glm::fvec3(0.0,1.0,1.0));

	m_shader->SetAmbient(glm::fvec3(0.3, 0.3, 0.3));
	m_shader->SetDirectionalLight(DirectionalLight(BaseLight(glm::vec3(1, 1, 1), 0.8f), glm::vec3(0, 0, -1)));
}

Game::~Game()
{
}

void Game::input(Input& input){
	m_camera->Input(input);
}

float temp = 0.0f;

void Game::update(){
	temp += Time::getDelta();

	//m_shader->Update(glm::abs(sin(temp))+0.5);

	m_transform->SetPos(glm::vec3(sin(temp), 0, cos(temp)));
	m_transform->SetRot(glm::vec3(temp * 100, temp * 100, temp * 100));

}

void Game::render(){
	m_shader->Bind();
	m_shader->Update(*m_transform, *m_camera, *m_material);
	m_material->m_texture->Bind(0);
	m_mesh->Draw();
}