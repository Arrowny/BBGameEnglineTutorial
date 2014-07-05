#include "directionalLight.h"


directionalLight::directionalLight(baseLight base, glm::fvec3 direction):
m_base(base),
m_direction(direction)
{
}


directionalLight::~directionalLight()
{
}

