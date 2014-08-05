#pragma once
#include <string>
#include <GL\glew.h>
#include <glm\glm.hpp>
#include "gameComponent.h"
#define MAX_PARTICLES 1000
#define BASE_PARTICLE 1
#define SECONDARY_PARTICLE 0

class Material;
class CoreEngine;
class PhysicsEngine;
class RenderingEngine;
class Shader;

struct Particle
{
	float Type;
	glm::vec3 Pos;
	glm::vec3 Vel;
	float Age;
};

class ParticleSystem : public GameComponent
{
public:
	ParticleSystem(std::string physicsProgramName, Material* material);
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
	GLuint query;
	int numberofparticles;
	Material* m_material;
	Shader* m_physicsProgram;
	Shader* m_rendererProgram;
	int m_time;
};

