#include "testGame.h"

//directionalLight TestGame::dirLight1 = directionalLight(baseLight(glm::fvec3(1.0f, 0.0f, 0.0f), 0.2f), glm::fvec3(0.5f, 0.0f, -0.5f));

TestGame::~TestGame()
{
	if (m_texture) delete m_texture;
	if (m_mesh) delete m_mesh;
	if (m_meshRenderer) delete m_meshRenderer;
}

void TestGame::init(){

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

	m_planeObject = gameObject();
	m_dirLightObj1 = gameObject();
	//m_mesh = new Mesh(vertices, sizeof(vertices) / sizeof(vertices[0]), indices, sizeof(indices) / sizeof(indices[0]));
	m_mesh = new Mesh("./res/triforce.obj");
	m_texture = new Texture("./res/colour.jpg");
	m_material = Material(m_texture, baseColor, 1, 36);

	m_meshRenderer = new meshRenderer(*m_mesh, m_material);
	m_planeObject.AddComponent(m_meshRenderer);

	dirLight1 = directionalLight(baseLight(glm::fvec3(1.0f, 0.0f, 0.0f), 0.2f), glm::fvec3(0.1f, 0.0f, -0.5f));
	dirLight2 = directionalLight(baseLight(glm::fvec3(0.0f, 0.0f, 1.0f), 0.2f), glm::fvec3(-0.1f, 0.0f, -0.5f));
	dirLight3 = directionalLight(baseLight(glm::fvec3(0.0f, 1.0f, 0.0f), 0.2f), glm::fvec3(0.0f, 0.1f, -0.5f));
	m_dirLightObj1.AddComponent(&dirLight1);
	m_dirLightObj1.AddComponent(&dirLight2);
	m_dirLightObj1.AddComponent(&dirLight3);

	m_root.AddChild(m_planeObject);
	m_root.AddChild(m_dirLightObj1);

}
