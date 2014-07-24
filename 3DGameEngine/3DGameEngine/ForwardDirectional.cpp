#include "ForwardDirectional.h"


ForwardDirectional::ForwardDirectional() :Shader("./res/shader/fowardDirectional")
{

}


ForwardDirectional::~ForwardDirectional()
{

}



void ForwardDirectional::Update(Transform& transform, RenderingEngine& renderingEngine, Material& material)
{


	Shader::Update(transform, renderingEngine, material);

}