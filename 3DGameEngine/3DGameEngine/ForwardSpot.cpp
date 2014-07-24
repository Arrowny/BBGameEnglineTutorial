#include "ForwardSpot.h"


ForwardSpot::ForwardSpot() :Shader("./res/shader/forwardSpotLight")
{
}


ForwardSpot::~ForwardSpot()
{

}



void ForwardSpot::Update(Transform& transform, RenderingEngine& renderingEngine, Material& material)
{

	Shader::Update(transform, renderingEngine, material);
 }