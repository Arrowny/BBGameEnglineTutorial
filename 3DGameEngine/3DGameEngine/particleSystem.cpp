#include "particleSystem.h"
#include "Util.h"
#include "Shader.h"


ParticleSystem::ParticleSystem(std::string physicsProgramName, Material* material)
{
	m_currVB = 0;
	m_currTFB = 1;
	m_isFirst = true;
	m_time = 0;
	m_material = material;
	m_physicsProgram = new Shader(physicsProgramName, Shader::PHYSICS_SHADER);
}


ParticleSystem::~ParticleSystem()
{
}

void ParticleSystem::InitParticleSystem(const glm::vec3& Pos)
{
	Particle Particles[MAX_PARTICLES];
	ZERO_MEM(Particles);

	Particles[0].Type = BASE_PARTICLE;
	Particles[0].Pos = Pos;
	Particles[0].Vel = glm::vec3(0.0f, 0.0000f, 0.0f);
	Particles[0].Age = 0.0f;

	glGenTransformFeedbacks(2, m_transformFeedback);
	glGenBuffers(2, m_particleBuffer);

	glBindTransformFeedback(GL_TRANSFORM_FEEDBACK, m_transformFeedback[0]);
	glBindBuffer(GL_ARRAY_BUFFER, m_particleBuffer[0]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(Particles), &Particles[0], GL_DYNAMIC_DRAW);
	glBindBufferBase(GL_TRANSFORM_FEEDBACK_BUFFER, 0, m_particleBuffer[0]);

	glBindTransformFeedback(GL_TRANSFORM_FEEDBACK, m_transformFeedback[1]);
	glBindBuffer(GL_ARRAY_BUFFER, m_particleBuffer[1]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(Particles), 0, GL_DYNAMIC_DRAW);
	glBindBufferBase(GL_TRANSFORM_FEEDBACK_BUFFER, 0, m_particleBuffer[1]);
}

void ParticleSystem::updatePhysics(Shader* shader, PhysicsEngine* physicsEngine, float delta)
{
	m_physicsProgram->Bind();
	m_physicsProgram->UpdateUniforms(physicsEngine);

	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glEnableVertexAttribArray(2);
	glEnableVertexAttribArray(3);

	glVertexAttribPointer(0, 1, GL_FLOAT, GL_FALSE, sizeof(Particle), 0);					// type
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Particle), (const GLvoid*)4);	// position
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, sizeof(Particle), (const GLvoid*)16);	// velocity
	glVertexAttribPointer(3, 1, GL_FLOAT, GL_FALSE, sizeof(Particle), (const GLvoid*)28);	// age

	glBeginTransformFeedback(GL_POINTS);
	if (m_isFirst) {
		glDrawArrays(GL_POINTS, 0, 1);
		m_isFirst = false;
	}
	else 
	{
		glDrawTransformFeedback(GL_POINTS, m_transformFeedback[m_currVB]);
	}
	glEndTransformFeedback();

	glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(1);
	glDisableVertexAttribArray(2);
	glDisableVertexAttribArray(3);
}

void ParticleSystem::render(Shader* shader, RenderingEngine* renderingEngine)
{
	shader->Bind();
	shader->UpdateUniforms(GetTransform(), *m_material, renderingEngine);
	glBeginTransformFeedback(GL_POINTS);

}
