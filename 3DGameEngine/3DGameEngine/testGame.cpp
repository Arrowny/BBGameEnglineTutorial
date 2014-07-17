#include "testGame.h"
#include <iostream>
#include <vector>
#include <glm\glm.hpp>
#include <glm\gtx\transform.hpp>
#include <glm\gtx\quaternion.hpp>



TestGame::~TestGame()
{
}

void TestGame::Init(Window* window)
{

	std::vector<glm::vec3> vertices;
	std::vector<unsigned int> indices;
	std::vector<glm::vec2> textCoords;

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

	//Set up mesh information.
	//TestMesh = new Mesh("./res/object_files/box.obj");
	meshComponent = new MeshRenderer(new Mesh(vertices, indices, textCoords),
										 Material("./res/texture_files/bricks.jpg",glm::vec3(1.0, 1.0, 1.0), 1, 8));
	meshComponent2 = new MeshRenderer(new Mesh(vertices, indices, textCoords),
										Material("./res/texture_files/bricks.jpg", glm::vec3(1.0, 1.0, 1.0), 1, 8));

	pyrimidGameObject.m_transform = new Transform(glm::vec3(0, 0, 5));
	pyrimidGameObject.m_transform->m_rot = glm::normalize(glm::quat(glm::radians(90.0f), glm::vec3(1, 0, 0)));

	pyrimidGameObject.addComponent(meshComponent);

	pyrimidGameObject2.m_transform = new Transform(glm::vec3(0, 3, 0));
	pyrimidGameObject2.addComponent(meshComponent2);


	dLight = new DirectionalLight(glm::vec3(1, 1, 1), 0.8);
	dLightObj.addComponent(dLight);
	dLightObj.m_transform = new Transform();
	dLightObj.m_transform->m_rot = glm::angleAxis(90.0f, glm::vec3(1.0, 1.0, 1.0));

	pLight1 = new PointLight(glm::vec3(0, 1, 0), .8, Attenuation(0, 0, 0.01));
	pLight1Obj.addComponent(pLight1);
	pLight1Obj.m_transform = new Transform(glm::vec3(3.0, 0.0, -3.0));

	pLight2 = new PointLight(glm::vec3(1, 0, 0), .8, Attenuation(0, 0, 0.01));
	pLight2Obj.addComponent(pLight2);
	pLight2Obj.m_transform = new Transform(glm::vec3(-3.0, 0.0, 0.0));

	sLight = new SpotLight(glm::vec3(0, 0.0, 5.0), .8, Attenuation(0, 0, 0.01), 0.7);
	sLightObj.addComponent(sLight);
	sLightObj.m_transform = new Transform();
	//sLightObj.m_transform->m_rot = glm::angleAxis(90.0f, glm::vec3(0.0, 1.0, 0.0));
	sLightObj.m_transform->m_trans = glm::vec3(0.0, 0.0, 0.0);

	camera = new Camera();
	camera->reinitPerspectiveMatrix(.01f, 1000.0f, 70.0f, window->GetWidth(), window->GetHeight());
	cameraObj.addComponent(camera);
	cameraObj.m_transform = new Transform();
	
	//pyrimidGameObject.addChild(&dLightObj);
	//m_root.addChild(&cameraObj);
	m_root.addChild(&pLight1Obj);
	m_root.addChild(&pLight2Obj);
	m_root.addChild(&sLightObj);
	pyrimidGameObject2.addChild(&cameraObj);
	pyrimidGameObject.addChild(&pyrimidGameObject2);
	m_root.addChild(&pyrimidGameObject);
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
