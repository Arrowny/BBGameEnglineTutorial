#include "ForwardPoint.h"


ForwardPoint::ForwardPoint() : Shader("./res/shader/forwardPointLight")
{
}


ForwardPoint::~ForwardPoint()
{

}



void ForwardPoint::Update(Transform& transform, RenderingEngine& renderingEngine, Material& material)
{

	Shader::Update(transform, renderingEngine, material);

 }