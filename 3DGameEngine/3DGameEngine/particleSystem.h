#pragma once
#include <string>
#include <GL\glew.h>
#include <glm\glm.hpp>
#include "gameComponent.h"
#include "physicsComponents.h"
#define DEFAULT_MAX_PARTICLES 10000
#define BASE_PARTICLE 1.0

class Material;
class PhysicsComponents;
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

enum 
{
	TEXTURE_ONLY,
	LUMINOUS_BLEND,

	NUM_RENDERING_TYPES
};

class ParticleSystem : public GameComponent
{
public:
	ParticleSystem(std::string physicsProgramName, Material* material, PhysicsComponents* components, glm::vec3 BasePosition = glm::vec3(0.0, 0.0, 0.0), const int& maxParticles = DEFAULT_MAX_PARTICLES, const int& rendSpecification = TEXTURE_ONLY);
	ParticleSystem(std::vector<std::string> physicsProgramNames, Material* material, glm::vec3 BasePosition = glm::vec3(0.0, 0.0, 0.0), const int& maxParticles = DEFAULT_MAX_PARTICLES, const int& rendSpecification = TEXTURE_ONLY);
	~ParticleSystem();

	void InitParticleSystem(const glm::vec3& Pos, const int& maxParticles);

	virtual void updatePhysics(Shader* shader, PhysicsEngine* physicsEngine);
	virtual void renderParticles(Shader* shader, RenderingEngine* renderingEngine);

	virtual void AddToEngine(CoreEngine* engine);

	void EnableGLRenderingSpecs();
	void DisableGLRenderingSpecs();

private:

	inline void SWAP_TFB()
	{
		m_currVB = m_currTFB;
		m_currTFB = (m_currTFB + 1) & 0x1;
	}

	inline void EnableVertexAttribs();
	inline void DisableVertexAttribs();
	inline void updateTransformFeedBack();
	inline void drawParticles();

	bool m_isFirst;
	unsigned int m_currVB;
	unsigned int m_currTFB;
	GLuint m_particleBuffer[2];
	GLuint m_transformFeedback[2];
	GLuint m_query;
	int m_numParticles;
	Material* m_material;
	PhysicsComponents* m_components;
	std::vector<Shader*> m_physicsPrograms;
	Shader* m_rendererProgram;
	int m_time;
	int m_renderingSpecification;
};

