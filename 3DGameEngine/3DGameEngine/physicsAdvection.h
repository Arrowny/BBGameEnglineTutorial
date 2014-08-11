#pragma once

#include <glm/glm.hpp>
#include <glm/detail/func_noise.hpp>
#include <GL/glew.h>
#include <cmath>
#include <vector>
#include "Util.h"

class Texture3D;

struct TexturePod {
	GLuint Handle;
	GLsizei Width;
	GLsizei Height;
	GLsizei Depth;
};

static struct
{
	std::vector<float> Data;
	TexturePod Description;
} VelocityCache;


class PhysicsAdvection
{
public:
	PhysicsAdvection();
	~PhysicsAdvection();

	static glm::vec3 SamplePotential(glm::vec3 p);
	static float SampleDistance(glm::vec3 p);
	static glm::vec3 SampleCachedCurl(glm::vec3 p);
	static glm::vec3 ComputeGradient(glm::vec3 p);
	static glm::vec3 BlendVectors(glm::vec3 potential, float alpha, glm::vec3 distanceGradient);

	static glm::vec3 ComputeCurl(glm::vec3 p);
	TexturePod CreateVelocityTexture(GLsizei texWidth, GLsizei texHeight, GLsizei texDepth);
	
protected:
	
private:
	Texture3D* m_texture3d;
};

