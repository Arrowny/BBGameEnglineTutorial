#pragma once
#include <string>
#include <GL\glew.h>
#include <glm\glm.hpp>
#include "gameComponent.h"
#define MAX_PARTICLES 1000
#define BASE_PARTICLE 0

class Material;
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
	ParticleSystem(std::string physicsProgramName, Material* material);
	~ParticleSystem();

	void InitParticleSystem(const glm::vec3& Pos);

	virtual void updatePhysics(Shader* shader, PhysicsEngine* physicsEngine, float delta);
	virtual void render(Shader* shader, RenderingEngine* renderingEngine);


private:

	bool m_isFirst;
	unsigned int m_currVB;
	unsigned int m_currTFB;
	GLuint m_particleBuffer[2];
	GLuint m_transformFeedback[2];
	Material* m_material;
	Shader* m_physicsProgram;
	int m_time;
};

