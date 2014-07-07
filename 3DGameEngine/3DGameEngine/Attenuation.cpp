#include "Attenuation.h"


Attenuation::Attenuation(float constant, float linear, float exponent) :
m_constant(constant),
m_linear(linear),
m_exponent(exponent)
{

}


Attenuation::~Attenuation()
{
}
