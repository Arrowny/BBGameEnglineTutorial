#include "ForwardAmbient.h"


ForwardAmbient::ForwardAmbient() : Shader("./res/shader/forwardAmbient")
{
}


ForwardAmbient::~ForwardAmbient()
{

}



void ForwardAmbient::Update(Transform& transform, RenderingEngine& renderingEngine, Material& material)
{

	Shader::Update(transform, renderingEngine, material);

}