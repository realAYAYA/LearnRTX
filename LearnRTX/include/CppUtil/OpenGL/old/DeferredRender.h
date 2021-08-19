#pragma once
#include<vector>

class Shader;
class ModelManager;
class LightManager;
class Camera;

class DeferredRender
{
public:
	DeferredRender();
	~DeferredRender();	

	/** Forward shading*/
	virtual void ForwardDraw(const glm::mat4& projection, Camera* camera);

	/** Deferred shading*/
	virtual void Draw(const glm::mat4& projection, Camera* camera);

	void FillgBuffer(const glm::mat4& projection, Camera* camera);
	void SendLights(Camera* camera);
	void RenderQuad();// Draw gBuffer on a quad

	void Initialize();
	void CreateTextureBuffers();
	void InitDeferredShader();

	unsigned int quadVAO = 0;
	unsigned int quadVBO;

	unsigned int gBuffer;
	unsigned int gPosition, gNormal, gAlbedoSpec;

	unsigned int SCR_WIDTH;
	unsigned int SCR_HEIGHT;

	Shader* shaderGeometryPass;
	Shader* shaderLightingPass;

	ModelManager* modelManager;
	LightManager* lightManager;

	/** SSAO*/
	void DrawWithSSAO(const glm::mat4& projection, Camera* camera);
	void FillSSAOBuffer(const glm::mat4& projection);
	void InitSSAO();
	void InitSSAOShader();
	float lerp(float a, float b, float f);
	unsigned int ssaoFBO, ssaoBlurFBO;
	unsigned int ssaoColorBuffer, ssaoColorBufferBlur;
	unsigned int noiseTexture;
	std::vector<glm::vec3> ssaoKernel;
	std::vector<glm::vec3> ssaoNoise;
	Shader* shaderSSAO;
	Shader* shaderSSAOBlur;

};

