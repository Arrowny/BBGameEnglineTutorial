#include "Game.h"
#include "main.h"

pointLight pLight1 = pointLight(baseLight(glm::fvec3(1.0f, 0.0f, 0.0f), 0.8f), Attenuation(0, 0, 1), glm::fvec3(-2.0f, 0.0f, -0.5f), 10);
pointLight pLight2 = pointLight(baseLight(glm::fvec3(0.0f, 0.0f, 1.0f), 0.8f), Attenuation(0, 0, 1), glm::fvec3(2.0f, 0.0f, -0.5f), 10);
spotLight sLight1 = spotLight(pointLight(baseLight(glm::fvec3(0, 1, 0), 0.8f), Attenuation(0, 0, 0.5f), glm::fvec3(-2, 0, 5), 30), glm::normalize(glm::fvec3(1, 1, 1)), 0.8f);

Game::~Game()
{
	if (m_texture) delete m_texture;
	if (m_mesh) delete m_mesh;
	if (m_meshRenderer) delete m_meshRenderer;
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

	planeObject = gameObject();
	//m_mesh = new Mesh(vertices, sizeof(vertices) / sizeof(vertices[0]), indices, sizeof(indices) / sizeof(indices[0]));
	m_mesh = new Mesh("./res/triforce.obj");
	m_texture = new Texture("./res/colour.jpg");
	m_material = Material(m_texture, baseColor, 1, 36);
	m_shader = new Shader("./res/phongShader");
	//Shader shader("./res/basicShader");

	m_meshRenderer = new meshRenderer(*m_mesh, m_material, *m_camera);
	planeObject.AddComponent(m_meshRenderer);

	m_root.AddChild(planeObject);

	m_pLights = new pointLight[2];
	m_pLights[0] = pLight1;
	m_pLights[1] = pLight2;

	m_sLights = new spotLight[1];
	m_sLights[0] = sLight1;

	Shader::SetPointLights(m_pLights, 2);
	Shader::SetSpotLights(m_sLights, 1);

}

void Game::input(const Input& input){
	
	m_camera->input(input);
	m_root.input();

}

float tem = 0.0f;

void Game::update(){

	tem += Time::getDelta();

	float sinCounter = sinf(counter);
	float cosCounter = cosf(counter);

	//transform.GetPos().z = -10.0;
	//transform.GetPos().x = sinCounter * 2;
	//transform.GetRot().y = counter * 10;
	//transform.SetScale(glm::vec3(0.1f , 0.1f, 0.1f));

	m_pLights[0].position = (glm::fvec3(sinCounter * 2.5, 0, -0.5));
	m_pLights[1].position = (glm::fvec3(0.0, sinCounter * 2.5, -0.5));

	m_sLights[0].pointL.position = m_camera->getPos();
	m_sLights[0].direction = m_camera->getForward();

	m_root.update();

	counter += 0.0003f;

}