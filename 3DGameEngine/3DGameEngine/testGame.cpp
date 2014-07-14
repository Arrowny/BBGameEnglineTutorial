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
	m_pLightObj1 = gameObject();
	m_sLightObj1 = gameObject();
	//m_mesh = new Mesh(vertices, sizeof(vertices) / sizeof(vertices[0]), indices, sizeof(indices) / sizeof(indices[0]));
	m_mesh = new Mesh("./res/triforce.obj");
	m_texture = new Texture("./res/colour.jpg");
	m_material = Material(m_texture, baseColor, 1, 36);

	m_meshRenderer = new meshRenderer(*m_mesh, m_material);
	m_planeObject.AddComponent(m_meshRenderer);

	dirLight1 = new directionalLight(glm::fvec3(1.0f, 0.0f, 0.0f), 0.2f, glm::fvec3(0.1f, 0.0f, -0.5f));
	dirLight2 = new directionalLight(glm::fvec3(0.0f, 0.0f, 1.0f), 0.2f, glm::fvec3(-0.1f, 0.0f, -0.5f));
	dirLight3 = new directionalLight(glm::fvec3(0.0f, 1.0f, 0.0f), 0.2f, glm::fvec3(0.0f, 0.1f, -0.5f));
	m_dirLightObj1.AddComponent(dirLight1);
	m_dirLightObj1.AddComponent(dirLight2);
	m_dirLightObj1.AddComponent(dirLight3);

	pLight1 = new pointLight(glm::fvec3(1.0f, 0.0f, 0.0f), 0.4f, Attenuation(0, 0, 1), glm::fvec3(0.0f, 1.0f, -0.5f), 10);
	pLight2 = new pointLight(glm::fvec3(0.0f, 1.0f, 0.0f), 0.4f, Attenuation(0, 0, 1), glm::fvec3(0.5f, 0.0f, -0.5f), 10);
	pLight3 = new pointLight(glm::fvec3(0.0f, 0.0f, 1.0f), 0.4f, Attenuation(0, 0, 1), glm::fvec3(-0.5f, 0.0f, -0.5f), 10);
	m_pLightObj1.AddComponent(pLight1);
	m_pLightObj1.AddComponent(pLight2);
	m_pLightObj1.AddComponent(pLight3);

	sLight1 = new spotLight(glm::fvec3(1, 1, 1), 0.8f, Attenuation(0, 0, 0.5f), glm::fvec3(-1.0, -1.2, -0.5), 30, glm::normalize(glm::fvec3(0, 1, 0)), 0.8f);
	sLight2 = new spotLight(glm::fvec3(1, 1, 1), 0.8f, Attenuation(0, 0, 0.5f), glm::fvec3(1.0, -1.2, -0.5), 30, glm::normalize(glm::fvec3(0, 1, 0)), 0.8f);
	m_pLightObj1.AddComponent(sLight1);
	m_pLightObj1.AddComponent(sLight2);

	m_root.AddChild(m_planeObject);
	m_root.AddChild(m_dirLightObj1);
	m_root.AddChild(m_pLightObj1);
	m_root.AddChild(m_sLightObj1);

}
