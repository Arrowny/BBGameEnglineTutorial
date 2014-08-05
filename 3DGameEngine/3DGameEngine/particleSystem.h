#pragma once
#include <string>
#include <GL\glew.h>
#include <glm\glm.hpp>
#include "gameComponent.h"
#define MAX_PARTICLES 10000
#define BASE_PARTICLE 0

class Material;
class CoreEngine;
class PhysicsEngine;
class RenderingEngine;
class Shader;

struct Particle
{
	int Type;
	glm::vec3 Pos;
	glm::vec3 Vel;
	float Age;
};

class ParticleSystem : public GameComponent
{
public:
	ParticleSystem(std::string physicsProgramName, Material* material, glm::vec3 BasePosition = glm::vec3(0.0, 0.0, 0.0));
	~ParticleSystem();

	void InitParticleSystem(const glm::vec3& Pos);

	virtual void updatePhysics(Shader* shader, PhysicsEngine* physicsEngine);
	virtual void renderParticles(Shader* shader, RenderingEngine* renderingEngine);

	virtual void AddToEngine(CoreEngine* engine);

private:

	void drawParticles();

	bool m_isFirst;
	unsigned int m_currVB;
	unsigned int m_currTFB;
	GLuint m_particleBuffer[2];
	GLuint m_transformFeedback[2];
	GLuint m_query;
	int m_numParticles;
	Material* m_material;
	Shader* m_physicsProgram;
	Shader* m_rendererProgram;
	int m_time;
};

