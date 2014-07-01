#pragma once
class Shader
{
public:
	Shader();
	virtual ~Shader();

private:
	Shader(const Shader& other) {}
	void operator=(const Shader& other) {}
};

