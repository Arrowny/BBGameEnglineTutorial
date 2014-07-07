#pragma once
struct Attenuation
{
	float m_constant;
	float m_linear;
	float m_exponent;

	Attenuation(float constant = 0, float linear = 0, float exponent = 1) :
		m_constant(constant),
		m_linear(linear),
		m_exponent(exponent) {}
	
};

