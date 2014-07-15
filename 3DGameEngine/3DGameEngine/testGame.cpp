#include "testGame.h"

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

	m_planeObject = new gameObject();
	m_dirLightObj1 = new gameObject();
	m_pLightObj1 = new gameObject();
	m_sLightObj1 = new gameObject();
	//m_mesh = new Mesh(vertices, sizeof(vertices) / sizeof(vertices[0]), indices, sizeof(indices) / sizeof(indices[0]));
	m_mesh = new Mesh("./res/triforce.obj");
	m_texture = new Texture("./res/colour.jpg");
	m_material = Material(m_texture, baseColor, 1, 36);

	m_meshRenderer = new meshRenderer(*m_mesh, m_material);
	m_planeObject->AddComponent(m_meshRenderer);
	m_planeObject->GetTransform().SetPos(glm::fvec3(0, 0, -0.4));
	m_planeObject->GetTransform().SetRot(glm::quat(0, 0, 1, 0));

	dirLight1 = new directionalLight(glm::fvec3(1.0f, 0.0f, 0.0f), 0.2f, glm::fvec3(0.1f, 0.0f, -0.5f));
	dirLight2 = new directionalLight(glm::fvec3(0.0f, 0.0f, 1.0f), 0.2f, glm::fvec3(-0.1f, 0.0f, -0.5f));
	dirLight3 = new directionalLight(glm::fvec3(0.0f, 1.0f, 0.0f), 0.2f, glm::fvec3(0.0f, 0.1f, -0.5f));
	m_dirLightObj1->AddComponent(dirLight1);
	m_dirLightObj1->AddComponent(dirLight2);
	m_dirLightObj1->AddComponent(dirLight3);

	pLight1 = new pointLight(glm::fvec3(1.0f, 0.0f, 0.0f), 0.4f, Attenuation(0, 0, 1));
	pLight2 = new pointLight(glm::fvec3(0.0f, 1.0f, 0.0f), 0.4f, Attenuation(0, 0, 1));
	pLight3 = new pointLight(glm::fvec3(0.0f, 0.0f, 1.0f), 0.4f, Attenuation(0, 0, 1));
	m_pLightObj1->AddComponent(pLight1);
	m_pLightObj1->AddComponent(pLight2);
	m_pLightObj1->AddComponent(pLight3);
	m_pLightObj1->GetTransform().SetPos(glm::fvec3(0, 1.5, -0.5));

	sLight1 = new spotLight(glm::fvec3(1, 1, 1), 0.8f, Attenuation(0, 0, 0.5f), 0.8f);
	sLight2 = new spotLight(glm::fvec3(1, 1, 1), 0.8f, Attenuation(0, 0, 0.5f), 0.8f);
	m_sLightObj1->AddComponent(sLight1);
	m_sLightObj1->AddComponent(sLight2);
	m_sLightObj1->GetTransform().SetPos(glm::fvec3(1, -1.0, -1.5));
	m_sLightObj1->GetTransform().SetRot(glm::quat(0, 0, -0.3, glm::radians(-90.0f)));

	GetRoot().AddChild(m_planeObject);
	GetRoot().AddChild(m_dirLightObj1);
	GetRoot().AddChild(m_pLightObj1);
	GetRoot().AddChild(m_sLightObj1);

}