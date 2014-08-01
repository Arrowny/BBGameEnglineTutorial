#include "skyBoxRenderer.h"
#include "Mesh.h"
#include "Material.h"
#include "Shader.h"
#include "Transform.h"
#include "coreEngine.h"

SkyBoxRenderer::SkyBoxRenderer(Material material)
{
	m_material = material;
	m_meshCube = new Mesh("./res/ball2.obj");
	m_skyShader = new Shader("./res/skyShader");
}


SkyBoxRenderer::~SkyBoxRenderer()
{
}

void SkyBoxRenderer::renderSkyBox(RenderingEngine* renderingEngine)
{
	m_skyShader->Bind();

	GLint OldCullFaceMode;
	glGetIntegerv(GL_CULL_FACE_MODE, &OldCullFaceMode);
	GLint OldDepthFuncMode;
	glGetIntegerv(GL_DEPTH_FUNC, &OldDepthFuncMode);

	glCullFace(GL_FRONT);
	glDepthFunc(GL_LEQUAL);

	Transform t;
	t.SetScale(glm::vec3(20.0f, 20.0f, 20.0f));
	t.SetRot(glm::normalize(glm::quat(glm::radians(0.0f), 0, 0, 0)));
	t.SetPos(glm::vec3(renderingEngine->GetMainCamera().GetTransform().GetPos()));
	//glm::mat4 skyTransform = t.GetModel();
	//glm::mat4 cameraProjection = renderingEngine->GetMainCamera().GetViewProjection();
	//t.SetPerspectiveProj(m_persProjInfo);
	//m_pSkyboxTechnique->SetWVP(p.GetWVPTrans());
	//m_pCubemapTex->Bind(GL_TEXTURE0);

	m_skyShader->UpdateUniforms(t, m_material, renderingEngine);
	m_meshCube->Draw();

	glCullFace(OldCullFaceMode);
	glDepthFunc(OldDepthFuncMode);

}

void SkyBoxRenderer::AddToEngine(CoreEngine* engine)
{
	engine->GetRenderingEngine()->AddSkyBox(this);
}
