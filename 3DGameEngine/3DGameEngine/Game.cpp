#include "Game.h"
#include "main.h"

Game::~Game()
{
	if (m_texture) delete m_texture;
	if (m_mesh) delete m_mesh;
}

void Game::init(){

	Vertex vertices[] = { Vertex(glm::vec3(-0.8, -0.8, 0.0), glm::vec2(1.0f, 0.0), glm::vec3(0, 0, -1)),
						  Vertex(glm::vec3(0.0, 0.8, 0.0), glm::vec2(0.5f, 0.0), glm::vec3(0, 0, -1)),
						  Vertex(glm::vec3(0.8, -0.8, 0.0), glm::vec2(1.0f, 0.0), glm::vec3(0, 0, -1)),
						  Vertex(glm::vec3(0.0, -0.8, 0.8), glm::vec2(0.0, 0.5f), glm::vec3(0, 0, -1)),
						  Vertex(glm::vec3(0.0, -0.8, -0.8), glm::vec2(0.0, 0.5f), glm::vec3(0, 0, -1)) };

	unsigned int indices[] = { 3, 1, 0,
							   2, 1, 3,
							   0, 2, 3,
							   4, 1, 2,
							   1, 4, 0,
							   2, 0, 4 };

	glm::fvec4 baseColor(1.0f, 1.0f, 1.0f, 1.0f);

	m_camera = new Camera(glm::vec3(0.0f, 0.0f, -10.0f), 70.0f, (float)Window::getWidth() / (float)Window::getHeight(), 0.1f, 1000.0f);

	//m_mesh = new Mesh(vertices, sizeof(vertices) / sizeof(vertices[0]), indices, sizeof(indices) / sizeof(indices[0]));
	m_mesh = new Mesh("./res/triforce.obj");
	//Shader shader("./res/basicShader");
	m_shader = new Shader("./res/phongShader");
	m_texture = new Texture("./res/colour.jpg");
	m_material = Material(m_texture, baseColor, 2, 32);

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

	m_shader->Update(transform, *m_camera, m_material.color, m_material.specularIntensity, m_material.specularPower);
	counter += 0.0003f;

}

void Game::render(){

	m_shader->Bind();
	m_material.texture->Bind(0);
	m_mesh->Draw();

}