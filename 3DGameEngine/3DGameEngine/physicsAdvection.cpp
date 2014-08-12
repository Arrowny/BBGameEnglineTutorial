#include "physicsAdvection.h"
#include "noise.h"
#include "texture3d.h"

static const glm::vec3 SphereCenter(0, 0, 0);
static const float SphereRadius = 1.0f;
static const float Epsilon = 1e-10f;
static const float NoiseLengthScale[] = { 0.4f, 0.23f, 0.11f };
static const float NoiseGain[] = { 1.0f, 0.5f, 0.25f };
static const float PlumeCeiling(3);
static const float PlumeBase(-3);
static const float PlumeHeight(8);
static const float RingRadius(1.25f);
static const float RingSpeed(0.3f);
static const float RingsPerSecond(0.125f);
static const float RingMagnitude(10);
static const float RingFalloff(0.7f);

static float Time = 0;

static FlowNoise3 noise;

inline float noise0(glm::vec3 s) { return noise(s.x, s.y, s.z); }
inline float noise1(glm::vec3 s) { return noise(s.y + 31.416f, s.z - 47.853f, s.x + 12.793f); }
inline float noise2(glm::vec3 s) { return noise(s.z - 233.145f, s.x - 113.408f, s.y - 185.31f); }
inline glm::vec3 noise3d(glm::vec3 s) { return glm::vec3(noise0(s), noise1(s), noise2(s)); };


PhysicsAdvection::PhysicsAdvection()
{
}


PhysicsAdvection::~PhysicsAdvection()
{
}


float PhysicsAdvection::SampleDistance(glm::vec3 p)
{
	float phi = p.y;
	glm::vec3 u = p - SphereCenter;
	float d = u.length();
	return d - SphereRadius;
}

glm::vec3 PhysicsAdvection::ComputeGradient(glm::vec3 p)
{
	const float e = 0.01f;
	glm::vec3 dx(e, 0, 0);
	glm::vec3 dy(0, e, 0);
	glm::vec3 dz(0, 0, e);

	float d = SampleDistance(p);
	float dfdx = SampleDistance(p + dx) - d;
	float dfdy = SampleDistance(p + dy) - d;
	float dfdz = SampleDistance(p + dz) - d;

	return glm::normalize(glm::vec3(dfdx, dfdy, dfdz));
}

glm::vec3 PhysicsAdvection::BlendVectors(glm::vec3 potential, float alpha, glm::vec3 distanceGradient)
{
	float dp = glm::dot(potential, distanceGradient);
	return alpha * potential + (1 - alpha) * dp * distanceGradient;
}

glm::vec3 PhysicsAdvection::SamplePotential(glm::vec3 p)
{
	glm::vec3 psi(0, 0, 0);
	glm::vec3 gradient = ComputeGradient(p);

	float obstacleDistance = SampleDistance(p);

	// add turbulence octaves that respect boundaries, increasing upwards
	float height_factor = ramp((p.y - PlumeBase) / PlumeHeight);
	for (unsigned int i = 0; i < countof(NoiseLengthScale); ++i) {
		glm::vec3 s = glm::vec3(p) / NoiseLengthScale[i];
		float d = ramp(std::fabs(obstacleDistance) / NoiseLengthScale[i]);
		glm::vec3 psi_i = BlendVectors(noise3d(s), d, gradient);
		psi += height_factor*NoiseGain[i] * psi_i;
	}

	glm::vec3 risingForce = glm::vec3(0, 0, 0) - p;
	risingForce = glm::vec3(-risingForce[2], 0, risingForce[0]);

	// add rising vortex rings
	float ring_y = PlumeCeiling;
	float d = ramp(std::fabs(obstacleDistance) / RingRadius);
	while (ring_y > PlumeBase) {
		float ry = p.y - ring_y;
		float rr = std::sqrt(p.x*p.x + p.z*p.z);
		float rmag = RingMagnitude / (sqr(rr - RingRadius) + sqr(rr + RingRadius) + sqr(ry) + RingFalloff);
		glm::vec3 rpsi = rmag * risingForce;
		psi += BlendVectors(rpsi, d, gradient);
		ring_y -= RingSpeed / RingsPerSecond;
	}

	return psi;
}

glm::vec3 PhysicsAdvection::ComputeCurl(glm::vec3 p)
{
	const float e = 1e-4f;
	glm::vec3 dx(e, 0, 0);
	glm::vec3 dy(0, e, 0);
	glm::vec3 dz(0, 0, e);

	float x = SamplePotential(p + dy)[2] - SamplePotential(p - dy)[2]
		- SamplePotential(p + dz)[1] + SamplePotential(p - dz)[1];

	float y = SamplePotential(p + dz)[0] - SamplePotential(p - dz)[0]
		- SamplePotential(p + dx)[2] + SamplePotential(p - dx)[2];

	float z = SamplePotential(p + dx)[1] - SamplePotential(p - dx)[1]
		- SamplePotential(p + dy)[0] + SamplePotential(p - dy)[0];

	return glm::vec3(x, y, z) / (2 * e);
}

void PhysicsAdvection::CreateVelocityTexture(GLsizei texWidth, GLsizei texHeight, GLsizei texDepth)
{
	VelocityCache.Data.resize(texWidth * texHeight * texDepth * 3);

	const float W = 2.0f;
	const float H = W * texHeight / texWidth;
	const float D = W;

	size_t requiredBytes = VelocityCache.Data.size() * sizeof(float);
	FILE* voxelsFile = fopen("Velocity.dat", "rb");
	if (voxelsFile) {
		size_t bytesRead = fread(&VelocityCache.Data[0], 1, requiredBytes, voxelsFile);
		Util::CheckCondition(bytesRead == requiredBytes);
	}
	else {
		std::vector<float>::iterator pData = VelocityCache.Data.begin();
		for (GLsizei slice = 0; slice < texDepth; ++slice) {
			for (GLsizei row = 0; row < texHeight; ++row) {
				for (GLsizei col = 0; col < texWidth; ++col) {
					glm::vec3 p;
					p.x = -W + 2 * W * col / texWidth;
					p.y = -H + 2 * H * row / texHeight;
					p.z = -D + 2 * D * slice / texDepth;
					glm::vec3 v = ComputeCurl(p);
					*pData++ = v.x;
					*pData++ = v.y;
					*pData++ = v.z;
				}
			}
		}

		voxelsFile = fopen("Velocity.dat", "wb");
		size_t bytesWritten = fwrite(&VelocityCache.Data[0], 1, requiredBytes, voxelsFile);
		Util::CheckCondition(bytesWritten == requiredBytes);
	}
	fclose(voxelsFile);

	m_texture3d = new Texture3D(texWidth, texHeight, texDepth, VelocityCache.Data);

	//GLuint handle;
	//glGenTextures(1, &handle);
	//glBindTexture(GL_TEXTURE_3D, handle);
	//glTexImage3D(GL_TEXTURE_3D, 0, GL_RGB16F, texWidth, texHeight, texDepth, 0, GL_RGB, GL_FLOAT, &VelocityCache.Data[0]);
	//glTexParameteri(GL_TEXTURE_3D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	//glTexParameteri(GL_TEXTURE_3D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	//glTexParameteri(GL_TEXTURE_3D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	//glTexParameteri(GL_TEXTURE_3D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	//glTexParameteri(GL_TEXTURE_3D, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);

	VelocityCache.Description.Handle = m_texture3d->GetHandle();
	VelocityCache.Description.Width = texWidth;
	VelocityCache.Description.Height = texHeight;
	VelocityCache.Description.Depth = texDepth;

	//return VelocityCache.Description;
}

