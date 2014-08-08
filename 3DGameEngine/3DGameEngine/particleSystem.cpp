#include "particleSystem.h"
#include "Util.h"
#include "Shader.h"
#include "coreEngine.h"
#include "physicsComponents.h"
#include <vector>


ParticleSystem::ParticleSystem(std::string physicsProgramName, Material* material, PhysicsComponents* components, glm::vec3 BasePosition, const int& maxParticles, const int& rendSpecification)
{
	m_renderingSpecification = rendSpecification;
	m_currVB = 0;
	m_currTFB = 1;
	m_isFirst = true;
	m_time = 0;
	m_material = material;
	m_components = components;
	m_physicsPrograms.push_back(new Shader(physicsProgramName, Shader::PHYSICS_SHADER));
	m_rendererProgram = new Shader("particleRenderer", Shader::FULL_SHADER_PIPELINE);
	InitParticleSystem(BasePosition, maxParticles);
}

ParticleSystem::ParticleSystem(std::vector<std::string> physicsProgramNames, Material* material, glm::vec3 BasePosition, const int& maxParticles, const int& rendSpecification)
{
	m_renderingSpecification = rendSpecification;
	m_currVB = 0;
	m_currTFB = 1;
	m_isFirst = true;
	m_time = 0;
	m_material = material;
	for (int ii = 0; ii < physicsProgramNames.size(); ii++)
	{
		m_physicsPrograms.push_back(new Shader(physicsProgramNames[ii], Shader::PHYSICS_SHADER));
	}
	m_rendererProgram = new Shader("particleRenderer", Shader::FULL_SHADER_PIPELINE);
	InitParticleSystem(BasePosition, maxParticles);
}

ParticleSystem::~ParticleSystem()
{
}

void ParticleSystem::InitParticleSystem(const glm::vec3& Pos, const int& maxParticles)
{

	int sizep = sizeof(Particle)*maxParticles;
	std::vector<Particle> particles;
	particles.resize(maxParticles);
	ZERO_MEM2(&particles[0], sizeof(Particle)*maxParticles);
	particles[0].Type = BASE_PARTICLE;
	particles[0].Pos = Pos;
	particles[0].Vel = glm::vec3(0.0f, 0.0f, 0.0f);
	particles[0].Age = 0.0f;

	
	//old version using default max particles
	//Particle Particles[DEFAULT_MAX_PARTICLES];
	//int sizeP = sizeof(Particles);
	//ZERO_MEM(Particles);
	//Particles[0].Type = BASE_PARTICLE;
	//Particles[0].Pos = Pos;
	//Particles[0].Vel = glm::vec3(0.0f, 0.0f, 0.0f);
	//Particles[0].Age = 0.0f;

	glGenTransformFeedbacks(2, m_transformFeedback);
	glGenBuffers(2, m_particleBuffer);

	glBindTransformFeedback(GL_TRANSFORM_FEEDBACK, m_transformFeedback[0]);
	glBindBuffer(GL_ARRAY_BUFFER, m_particleBuffer[0]);
	//glBufferData(GL_ARRAY_BUFFER, sizeof(Particles), &Particles[0], GL_STREAM_DRAW); //use with old version
	glBufferData(GL_ARRAY_BUFFER, sizep, &particles[0], GL_STREAM_DRAW);
	glBindBufferBase(GL_TRANSFORM_FEEDBACK_BUFFER, 0, m_particleBuffer[0]);
	glBindTransformFeedback(GL_TRANSFORM_FEEDBACK, 0);

	glBindTransformFeedback(GL_TRANSFORM_FEEDBACK, m_transformFeedback[1]);
	glBindBuffer(GL_ARRAY_BUFFER, m_particleBuffer[1]);
	//glBufferData(GL_ARRAY_BUFFER, sizeof(Particles), &Particles[0], GL_STREAM_DRAW); //use with old version
	glBufferData(GL_ARRAY_BUFFER, sizep, 0, GL_STREAM_DRAW);
	glBindBufferBase(GL_TRANSFORM_FEEDBACK_BUFFER, 0, m_particleBuffer[1]);
	glBindTransformFeedback(GL_TRANSFORM_FEEDBACK, 0);

	glGenQueries(1, &m_query);
	m_numParticles = 1;
}

void ParticleSystem::updatePhysics(Shader* shader, PhysicsEngine* physicsEngine)
{
	glEnable(GL_RASTERIZER_DISCARD);
	for (int ii = 0; ii < m_physicsPrograms.size(); ii++)
	{
		m_physicsPrograms[ii]->Bind();
		m_physicsPrograms[ii]->UpdateUniforms(GetTransform(), *m_components, physicsEngine);
		EnableVertexAttribs();

		glBeginQuery(GL_TRANSFORM_FEEDBACK_PRIMITIVES_WRITTEN, m_query);
		updateTransformFeedBack();
		glEndQuery(GL_TRANSFORM_FEEDBACK_PRIMITIVES_WRITTEN);
		glGetQueryObjectiv(m_query, GL_QUERY_RESULT, &m_numParticles);

		DisableVertexAttribs();
		if (ii + 1 < m_physicsPrograms.size()){ SWAP_TFB(); }
	}
	glDisable(GL_RASTERIZER_DISCARD);
}

void ParticleSystem::EnableVertexAttribs()
{
	glBindTransformFeedback(GL_TRANSFORM_FEEDBACK, m_transformFeedback[m_currTFB]);
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
}

void ParticleSystem::DisableVertexAttribs()
{
	glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(1);
	glDisableVertexAttribArray(2);
	glDisableVertexAttribArray(3);

	glBindTransformFeedback(GL_TRANSFORM_FEEDBACK, 0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void ParticleSystem::updateTransformFeedBack()
{
	glBeginTransformFeedback(GL_POINTS);
	if (m_isFirst)
	{
		glDrawArrays(GL_POINTS, 0, m_numParticles);
		m_isFirst = false;
	}
	else
	{
		glDrawArrays(GL_POINTS, 0, m_numParticles);
	}
	glEndTransformFeedback();
}

void ParticleSystem::renderParticles(Shader* shader, RenderingEngine* renderingEngine)
{
	m_rendererProgram->Bind();
	m_rendererProgram->UpdateUniforms(GetTransform(), *m_material, renderingEngine);
	drawParticles();
	SWAP_TFB();
}


void ParticleSystem::drawParticles()
{
	if (!m_isFirst)
	{
		int numNewParticles = m_components->GetInt("numEmit");
		glBindBuffer(GL_ARRAY_BUFFER, m_particleBuffer[m_currVB]);
		glEnableVertexAttribArray(0);
		glEnableVertexAttribArray(1);
		glVertexAttribPointer(0, 1, GL_FLOAT, GL_FALSE, sizeof(Particle), 0);					// type
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Particle), (const GLvoid*)4);	// position
		glDrawArrays(GL_POINTS, 0, m_numParticles - (numNewParticles)); //David's Note: do not render last # newParticles. For some reason this data is junk data.
		glDisableVertexAttribArray(0);
		glDisableVertexAttribArray(1);
	}
}

void ParticleSystem::AddToEngine(CoreEngine* engine)
{
	engine->GetRenderingEngine()->AddParticleSystem(this);
}

void ParticleSystem::EnableGLRenderingSpecs()
{

	switch (m_renderingSpecification)
	{
	case TEXTURE_ONLY:
		break;
	case LUMINIOUS_BLEND:
		glEnable(GL_BLEND);
		glEnable(GL_DEPTH_TEST);
		glDepthMask(GL_FALSE);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE);
		break;
	default:
		break;
	}

}

void ParticleSystem::DisableGLRenderingSpecs()
{
	switch (m_renderingSpecification)
	{
	case TEXTURE_ONLY:
		break;
	case LUMINIOUS_BLEND:
		glDisable(GL_BLEND);
		glDepthMask(GL_TRUE);
		break;
	default:
		break;
	}
}


