#pragma once

#include "../../model/model.h"
#include "../../texture/cubeTexture/cubeTexture.h"
#include "../../shaders/skyboxShader/skyboxShader.h"

class Camera;
class SkyboxRenderer
{
public:
	SkyboxRenderer();
	void renderSkyBox(const Camera& camera);
private:
	Model        m_skyboxModel;
	CubeTexture  m_skyboxTexture;
	SkyboxShader m_skyboxShader;
};

