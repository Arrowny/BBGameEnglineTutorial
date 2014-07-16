#pragma once
class Attenuation
{
public:
	float constant;
	float linear;
	float exponent;
	Attenuation()
	{
		constant = 0.0;
		linear = 0.0;
		exponent = 1.0;
	}
	Attenuation(float constant, float linear, float exponent)
	{
		this->constant = constant;
		this->linear = linear;
		this->exponent = exponent;
	}

	//inline float GetConstant() { return constant; }
	//inline float GetLinear() { return linear; }
	//inline float GetExponent() { return exponent; }

	//inline void SetConstant(float cons) { constant = cons; }
	//inline void SetLinear(float linear) { this->linear = linear; }
	//inline void SetExponent(float exponent) { this->exponent = exponent; }
	
private:

};

