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
	m_rendererProgram = new Shader("particleRenderer", Shader::FULL_SHADER_PIPELINE);
	InitParticleSystem(glm::vec3(0.0, 0.0, 0.0)); //TODO: update constructor to allow for multiple BASE_PARTICLES and SECONDARY_PARTICLES
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

	//for (unsigned int i = 0; i < 2; i++) {
	//	glBindTransformFeedback(GL_TRANSFORM_FEEDBACK, m_transformFeedback[i]);
	//	glBindBuffer(GL_ARRAY_BUFFER, m_particleBuffer[i]);
	//	glBufferData(GL_ARRAY_BUFFER, sizeof(Particles), Particles, GL_DYNAMIC_DRAW);
	//	glBindBufferBase(GL_TRANSFORM_FEEDBACK_BUFFER, 0, m_particleBuffer[i]);
	//}
}

void ParticleSystem::updatePhysics(Shader* shader, PhysicsEngine* physicsEngine)
{
	m_physicsProgram->Bind();
	m_physicsProgram->UpdateUniforms(physicsEngine);

	glEnable(GL_RASTERIZER_DISCARD);
	glBindBuffer(GL_ARRAY_BUFFER, m_particleBuffer[m_currVB]);
	
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glEnableVertexAttribArray(2);
	glEnableVertexAttribArray(3);

	glVertexAttribPointer(0, 1, GL_FLOAT, GL_FALSE, sizeof(Particle), 0);					// type
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Particle), (const GLvoid*)4);	// position
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, sizeof(Particle), (const GLvoid*)16);	// velocity
	glVertexAttribPointer(3, 1, GL_FLOAT, GL_FALSE, sizeof(Particle), (const GLvoid*)28);	// age

	glBindBufferBase(GL_TRANSFORM_FEEDBACK_BUFFER, 0, m_particleBuffer[m_currTFB]);
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

	glDisable(GL_RASTERIZER_DISCARD);
	
}

void ParticleSystem::render(Shader* shader, RenderingEngine* renderingEngine)
{

	m_rendererProgram->Bind();
	m_rendererProgram->UpdateUniforms(GetTransform(), *m_material, renderingEngine);
	drawParticles();

	//swap current TFB setup
	m_currVB = m_currTFB;
	m_currTFB = (m_currTFB + 1) & 0x1;
}


void ParticleSystem::drawParticles()
{
	if (!m_isFirst)
	{
		glBindBuffer(GL_ARRAY_BUFFER, m_particleBuffer[m_currVB]);
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Particle), (const GLvoid*)4);  // position
		glDrawArrays(GL_POINTS, 0, 100);
		//glDrawTransformFeedback(GL_POINTS, m_transformFeedback[m_currTFB]);
		glDisableVertexAttribArray(0);

	}
}


