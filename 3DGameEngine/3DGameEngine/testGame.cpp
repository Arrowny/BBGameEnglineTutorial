#include "testGame.h"
#include <iostream>
#include <vector>


TestGame::~TestGame()
{
}

void TestGame::Init(Window* window)
{

	std::vector<glm::vec3> vertices;
	std::vector<unsigned int> indices;
	std::vector<glm::vec2> textCoords;

	m_camera = new Camera();
	m_camera->reinitPerspectiveMatrix(.01f, 1000.0f, 70.0f, window->GetWidth(), window->GetHeight());

	vertices.push_back(glm::vec3(-1.0, -1.0, -1.0));
	vertices.push_back(glm::vec3(0.0, 1.0, 0.0));
	vertices.push_back(glm::vec3(1.0, -1.0, 0.0));
	vertices.push_back(glm::vec3(0.0, -1.0, 1.0));

	indices.push_back(3); indices.push_back(1); indices.push_back(0);
	indices.push_back(2); indices.push_back(1); indices.push_back(3);
	indices.push_back(0); indices.push_back(1); indices.push_back(2);
	indices.push_back(0); indices.push_back(2); indices.push_back(3);

	textCoords.push_back(glm::vec2(0.0, 0.0));
	textCoords.push_back(glm::vec2(0.5, 1.0));
	textCoords.push_back(glm::vec2(1.0, 0.0));
	textCoords.push_back(glm::vec2(0.5, 1.0));

	m_worldTransform = new Transform();

	//Set up mesh information.
	//TestMesh = new Mesh("./res/object_files/box.obj");
	meshComponent = new MeshRenderer(new Mesh(vertices, indices, textCoords),
										 Material("./res/texture_files/bricks.jpg",glm::vec3(1.0, 1.0, 1.0), 1, 8));

	pyrimidGameObject.m_camera = m_camera;
	pyrimidGameObject.m_transform = m_worldTransform;
	pyrimidGameObject.m_components.push_back(meshComponent);

	m_root.m_children.push_back(&pyrimidGameObject);
	m_worldTransform->setTranslationExplicit(0.0, 0.0, 5.0);
}

//void TestGame::ProcessInput(Input* &input)
//{
//	m_camera->input(*input);
//}
//
//void TestGame::Update()
//{
//	float tmpUpdate = std::sin(Time::GetTime());
//	m_worldTransform->setTranslationExplicit(0.0, 0.0, 5.0);
//	//m_worldTransform->setRotationExplicit(0.0, tmpUpdate*360.0, 0.0);
//	//m_worldTransform->setScaleExplicit(tmpUpdate, tmpUpdate, tmpUpdate);
//
//	//m_shader->m_pointLights[0].m_position = glm::vec3(3.0 + tmpUpdate * 4, 0.0, 0.0);
//	//m_shader->m_pointLights[1].m_position = glm::vec3(-3.0 + -tmpUpdate * 4, 0.0, 0.0);
//
//	m_shader->m_spotLights[0].m_pLight.m_position = m_camera->m_pos;
//	m_shader->m_spotLights[0].m_direction = m_camera->getCenter();
//
//	m_shader->m_spotLights[1].m_pLight.m_position = glm::vec3(-3.0 + -tmpUpdate * 4, 0.0, 0.0);
//}
//
//void TestGame::Render()
//{
//	m_root.Render();
//}
