#include <CppUtil/RTX/GenData.h>
#include <CppUtil/RTX/ConstTexture.h>
#include <CppUtil/RTX/Dielectric.h>
#include <CppUtil/RTX/Metal.h>
#include <CppUtil/RTX/Lambertian.h>
#include <CppUtil/RTX/Sphere.h>
#include <CppUtil/RTX/Group.h>
#include <CppUtil/RTX/TexWindow.h>
#include <CppUtil/RTX/TRayCamera.h>
#include <CppUtil/RTX/Scene.h>
#include <CppUtil/RTX/Group.h>
#include <CppUtil/RTX/Sky.h>
#include <CppUtil/RTX/Skybox.h>
#include <CppUtil/RTX/Light.h>
#include <CppUtil/RTX/Sphere.h>
#include <CppUtil/RTX/TriMesh.h>
#include <CppUtil/RTX/Transform.h>
#include <CppUtil/RTX/ImgTexture.h>

#include <CppUtil/OpenGL/Shader.h>
#include <CppUtil/OpenGL/Camera.h>
#include <CppUtil/OpenGL/Texture.h>
#include <CppUtil/OpenGL/VAO.h>
#include <CppUtil/OpenGL/FBO.h>

#include <CppUtil/Basic/EventManager.h>
#include <CppUtil/Basic/GStorage.h>
#include <CppUtil/Basic/OpQueue.h>
#include <CppUtil/Basic/LambdaOp.h>
#include <CppUtil/Basic/Timer.h>
#include <CppUtil/Basic/Math.h>
#include <CppUtil/Basic/File.h>

#include <GLFW/Glfw.h>
#include <glm/glm.hpp>


#include"CommonDefine.h"

using namespace RTX;
using namespace CppUtil;
using namespace CppUtil::OpenGL;
using namespace CppUtil::Basic;
using namespace glm;
using namespace std;

string rootPath;
string texturePath;
string modelPath;
string shaderPath;

Scene::CPtr CreateScene0(float ratioWH);
size_t Fit2Square(vector<float>& data);

int main(int argc, char** argv) {
	//------------ Init
	Timer timer;
	TexWindow texWindow("RTX GAME");
	if (!texWindow.IsValid()) {
		printf("ERROR: Texture Window Create Fail.\n");
		return 1;
	}	
	const int width = texWindow.GetWidth();
	const int height = texWindow.GetHeight();
	const float ratioWH = width / (float)height;
	Glfw::GetInstance()->LockCursor();

	std::string exePath = argv[0];
	rootPath = exePath.substr(0, exePath.find_last_of('\\')) + "\\..\\LearnRTX\\assets\\";
	shaderPath = exePath.substr(0, exePath.find_last_of('\\')) + "\\..\\LearnRTX\\assets\\shaders\\";
	texturePath = exePath.substr(0, exePath.find_last_of('\\')) + "\\..\\LearnRTX\\assets\\textures\\";
	modelPath = exePath.substr(0, exePath.find_last_of('\\')) + "\\..\\LearnRTX\\assets\\model\\";

	//------------ Scene
	Scene::CPtr scene = CreateScene0(ratioWH);

	//------------ Move
	vec3 front = normalize(scene->camera->GetFront());
	float pitch = asin(front.y) / Math::PI * 180;
	float yaw = acos(front.x / cos(pitch / 180 * Math::PI)) / Math::PI * 180;
	Camera roamCamera(scene->camera->GetPos(), yaw, pitch, ratioWH, 1, 100);

	size_t moveKey[] = { GLFW_KEY_S, GLFW_KEY_W, GLFW_KEY_D, GLFW_KEY_A, GLFW_KEY_E, GLFW_KEY_Q };
	size_t arrowKey[] = { GLFW_KEY_DOWN, GLFW_KEY_UP, GLFW_KEY_RIGHT, GLFW_KEY_LEFT, GLFW_KEY_PAGE_DOWN, GLFW_KEY_PAGE_UP };
	for (size_t i = 0; i < 6; i++) {
		LambdaOp::Ptr op = ToPtr(new LambdaOp([=, &roamCamera, &timer]() {
			roamCamera.ProcessKeyboard(Camera::ENUM_Movement(Camera::MOVE_FORWARD + i), timer.GetLog(1));
			}));

		EventManager::GetInstance()->Register(EventManager::KEYBOARD | moveKey[i],
			op);
		EventManager::GetInstance()->Register(EventManager::KEYBOARD | arrowKey[i],
			op);
	}
	EventManager::GetInstance()->Register(EventManager::MOUSE_MOUVE, [&]() {
		auto xOffset = **GStorage<float*>::GetInstance()->GetPtr("mousePos_XOffset");
		auto yOffset = **GStorage<float*>::GetInstance()->GetPtr("mousePos_YOffset");
		roamCamera.ProcessMouseMovement(xOffset, -yOffset);
		});

	//------------ ģ�� . Screen
	VAO VAO_Screen(&(data_ScreenVertices[0]), sizeof(data_ScreenVertices), { 2,2 });


	//------------ Fragment Shader Generator
	GenData genData(scene->obj);

	auto sceneData = genData.GetSceneData();
	auto sceneDataSize = Fit2Square(sceneData);
	OpenGL::Texture sceneDataTex(sceneDataSize, sceneDataSize, sceneData.data(), GL_FLOAT, GL_RED, GL_R32F);

	auto matData = genData.GetMatData();
	auto matDataSize = Fit2Square(matData);
	OpenGL::Texture matDataTex(matDataSize, matDataSize, matData.data(), GL_FLOAT, GL_RED, GL_R32F);

	auto texData = genData.GetTexData();
	auto texDataSize = Fit2Square(texData);
	OpenGL::Texture texDataTex(texDataSize, texDataSize, texData.data(), GL_FLOAT, GL_RED, GL_R32F);

	auto packData = genData.GetPackData();
	auto packDataSize = Fit2Square(packData);
	OpenGL::Texture packDataTex((packDataSize + 1) / 2, (packDataSize + 1) / 2, packData.data(), GL_FLOAT, GL_RGBA, GL_RGBA32F);

	OpenGL::Texture skyboxTex(genData.GetSkyboxImgs());

	auto img2idx = genData.GetImgIdxMap();
	const size_t texArrSize = 16;
	OpenGL::Texture texArr[texArrSize];
	for (auto const& pair : img2idx) {
		auto img = pair.first;
		texArr[pair.second] = OpenGL::Texture(OpenGL::Texture::ENUM_TYPE_2D_DYNAMIC);
		texArr[pair.second].SetImg(*img);
		//printf("Set TexArr[%d]\n", pair.second);
	}	

	//------------ RTX Basic Shader
	Shader RTX_Shader(shaderPath+"RTX\\P2T2.vs", shaderPath+"RTX\\RTX.fs");
	if (!RTX_Shader.IsValid()) {
		printf("ERROR: RTX_Shader load fail.\n");
		return 1;
	}
	auto camera = scene->camera;
	TRayCamera::CPtr tCamera = std::dynamic_pointer_cast<const TRayCamera>(camera);

	RTX_Shader.SetInt("SumColor", 0);
	RTX_Shader.SetInt("RayData0", 1);
	RTX_Shader.SetInt("RayData1", 2);
	RTX_Shader.SetInt("RayData2", 3);

	RTX_Shader.SetInt("SceneData", 4);
	RTX_Shader.SetInt("MatData", 5);
	RTX_Shader.SetInt("TexData", 6);
	RTX_Shader.SetInt("PackData", 7);

	RTX_Shader.SetInt("skybox", 8);

	for (size_t i = 0; i < texArrSize; i++) {
		string TexArr = "TexArr[" + std::to_string(i) + "]";
		RTX_Shader.SetInt(TexArr.c_str(), 9 + i);
	}

	RTX_Shader.SetVec3f("camera.pos", camera->GetPos());
	RTX_Shader.SetVec3f("camera.BL_Corner", camera->GetBL_Corner());
	RTX_Shader.SetVec3f("camera.horizontal", camera->GetHorizontal());
	RTX_Shader.SetVec3f("camera.vertical", camera->GetVertical());
	RTX_Shader.SetVec3f("camera.right", camera->GetRight());
	RTX_Shader.SetVec3f("camera.up", camera->GetUp());
	RTX_Shader.SetVec3f("camera.front", camera->GetFront());
	RTX_Shader.SetFloat("camera.lenR", camera->GetLenR());
	RTX_Shader.SetFloat("camera.t0", tCamera ? tCamera->GetT0() : 0);
	RTX_Shader.SetFloat("camera.t1", tCamera ? tCamera->GetT1() : 0);

	//------------ Average Shader
	Shader average_Shader(shaderPath + "RTX\\P2T2.vs", shaderPath + "RTX\\average.fs");
	if (!average_Shader.IsValid()) {
		printf("ERROR: RTX_Shader load fail.\n");
		return 1;
	}
	average_Shader.SetInt("texture0", 0);

	//------------ RTX FBO
	bool curReadFBO = false;
	FBO FBO_RayTracing[2] = { FBO(width, height, FBO::ENUM_TYPE_RAYTRACING),FBO(width, height, FBO::ENUM_TYPE_RAYTRACING) };
	FBO FBO_Average(width, height, FBO::ENUM_TYPE_COLOR);


	//------------ ����

	size_t allLoopNum = 0;
	size_t frameLoop = 0;

	LambdaOp::Ptr cameraUpdateOp = ToPtr(new LambdaOp([&]() {
		timer.Log();
		static vec3 lastPos(0);
		static vec3 lastViewPoint(0);
		static mat4 viewProjectMat = roamCamera.GetProjectionMatrix() * roamCamera.GetViewMatrix();


		if (lastPos == roamCamera.GetPos() && lastViewPoint == roamCamera.GetPos() - roamCamera.GetFront())
			return;

		lastPos = roamCamera.GetPos();
		lastViewPoint = roamCamera.GetPos() - roamCamera.GetFront();
		TRayCamera::CPtr camera = ToCPtr(new TRayCamera(lastPos, lastViewPoint, ratioWH));
		RTX_Shader.SetVec3f("camera.pos", camera->GetPos());
		RTX_Shader.SetVec3f("camera.BL_Corner", camera->GetBL_Corner());
		RTX_Shader.SetVec3f("camera.horizontal", camera->GetHorizontal());
		RTX_Shader.SetVec3f("camera.vertical", camera->GetVertical());
		RTX_Shader.SetVec3f("camera.right", camera->GetRight());
		RTX_Shader.SetVec3f("camera.up", camera->GetUp());
		RTX_Shader.SetVec3f("camera.front", camera->GetFront());
		RTX_Shader.SetFloat("camera.lenR", camera->GetLenR());
		RTX_Shader.SetFloat("camera.t0", camera->GetT0());
		RTX_Shader.SetFloat("camera.t1", camera->GetT1());
		RTX_Shader.SetMat4f("oldViewProjectMat", viewProjectMat);

		viewProjectMat = roamCamera.GetProjectionMatrix() * roamCamera.GetViewMatrix();

		RTX_Shader.SetFloat("clear", 1.0);
		frameLoop = 0;
		}));

	LambdaOp::Ptr RTX_Op = ToPtr(new LambdaOp([&]() {
		size_t loopNum = 6;// static_cast<size_t>(glm::max(texWindow.GetScale(), 2.0));
		for (size_t i = 0; i < loopNum; i++) {
			FBO_RayTracing[!curReadFBO].Use();
			FBO_RayTracing[curReadFBO].GetColorTexture(0).Use(0);
			FBO_RayTracing[curReadFBO].GetColorTexture(1).Use(1);
			FBO_RayTracing[curReadFBO].GetColorTexture(2).Use(2);
			FBO_RayTracing[curReadFBO].GetColorTexture(3).Use(3);
			sceneDataTex.Use(4);
			matDataTex.Use(5);
			texDataTex.Use(6);
			packDataTex.Use(7);
			skyboxTex.Use(8);
			for (size_t i = 0; i < texArrSize; i++)
				texArr[i].Use(9 + i);
			RTX_Shader.SetFloat("rdSeed[0]", Math::Rand_F());
			RTX_Shader.SetFloat("rdSeed[1]", Math::Rand_F());
			RTX_Shader.SetFloat("rdSeed[2]", Math::Rand_F());
			RTX_Shader.SetFloat("rdSeed[3]", Math::Rand_F());
			VAO_Screen.Draw(RTX_Shader);
			RTX_Shader.SetFloat("clear", 0.0);
			curReadFBO = !curReadFBO;
		}
		allLoopNum += loopNum;
		double wholeTime = timer.GetWholeTime();
		double speed = allLoopNum / wholeTime;
		printf("\rINFO: %.2f spps, speed %.2f loop / s, used time: %.2f s     ",
			allLoopNum / wholeTime, speed, wholeTime);
		}));

	auto averageOp = ToPtr(new LambdaOp([&]() {
		FBO_Average.Use();
		FBO_RayTracing[curReadFBO].GetColorTexture(0).Use(0);
		VAO_Screen.Draw(average_Shader);

		texWindow.SetTex(FBO_Average.GetColorTexture(0));
		}));

	auto texUpdateOp = ToPtr(new OpQueue);
	(*texUpdateOp) << cameraUpdateOp << RTX_Op << averageOp;

	timer.Start();
	bool success = texWindow.Run(texUpdateOp);

	return success ? 0 : 1;
}

Scene::CPtr CreateScene0(float ratioWH) {
	const std::vector<std::string> str_Vec_Img_Skybox = {
		texturePath + "../skybox/right.jpg",
		texturePath + "../skybox/left.jpg",
		texturePath + "../skybox/top.jpg",
		texturePath + "../skybox/bottom.jpg",
		texturePath + "../skybox/front.jpg",
		texturePath + "../skybox/back.jpg"
	};

	vector<string> skyboxImgPath(6);
	for (size_t i = 0; i < 6; i++)
		skyboxImgPath[i] = str_Vec_Img_Skybox[i];
	auto sky = ToPtr(new Sky(ToCPtr(new Light(ToCPtr(new Skybox(skyboxImgPath))))));

	auto earthTex = ToCPtr(new ImgTexture(texturePath + "earth.jpg", true));
	if (!earthTex->IsValid()) {
		printf("ERROR: earthTex[%s] is invalid.\n", texturePath);
		exit(1);
	}

	auto constTex = ToCPtr(new ConstTexture(rgb(0.5, 0.5, 0.5)));

	// Mesh
	// Mesh Square
	const float data_SquareVertexPos[48] = {
	    -0.5, -0.5,  0,  0,  0,  1, 0, 0,
	     0.5, -0.5,  0,  0,  0,  1, 1, 0,
	    -0.5,  0.5,  0,  0,  0,  1, 0, 1,
	     0.5,  0.5,  0,  0,  0,  1, 1, 1,
	    -0.5,  0.5,  0,  0,  0,  1, 0, 1,
	     0.5, -0.5,  0,  0,  0,  1, 1, 0,
	};

	vector<Vertex> squareVertexs;
	for (size_t i = 0; i < sizeof(data_SquareVertexPos) / sizeof(float); i += 8) {
		vec3 pos(data_SquareVertexPos[i], data_SquareVertexPos[i + 1], data_SquareVertexPos[i + 2]);
		vec3 normal(data_SquareVertexPos[i + 3], data_SquareVertexPos[i + 4], data_SquareVertexPos[i + 5]);
		vec2 uv(data_SquareVertexPos[i + 6], data_SquareVertexPos[i + 7]);
		squareVertexs.push_back(Vertex(pos, normal, uv.x, uv.y));
	}
	auto square = ToPtr(new TriMesh(squareVertexs));
	if (!square->IsValid()) {
		printf("ERROR: square is invalid.\n");
		exit(1);
	}
	mat4 tfmBottom(1.0f);
	tfmBottom = translate(tfmBottom, vec3(0, -0.5, 0));
	tfmBottom = rotate(tfmBottom, -Math::PI / 2, vec3(1, 0, 0));
	tfmBottom = scale(tfmBottom, vec3(8));
	auto woodMat = ToCPtr(new Lambertian(ToPtr(new ImgTexture(texturePath + "wood.jpg"))));
	auto bottomWood = ToPtr(new RTX::Transform(tfmBottom, square, woodMat));

	Sphere::CPtr sphereTop = ToCPtr(new Sphere(vec3(0, 0.5, 0), 0.25, ToCPtr(new Metal(constTex, 0.2f))));
	Sphere::CPtr sphereBottom = ToCPtr(new Sphere(vec3(0, -100.5, -1), 100, ToCPtr(new Lambertian(constTex))));

	Sphere::CPtr sphereMid = ToCPtr(new Sphere(vec3(0, 0, 0), 0.5, ToCPtr(new Metal(vec3(1.0), 0.2))));

	auto dielectric = ToCPtr(new Dielectric(1.5));
	Sphere::CPtr sphereLeftOut = ToCPtr(new Sphere(vec3(-1.1, 0.01, 1.0), 0.5, dielectric));
	Sphere::CPtr sphereLeftIn = ToCPtr(new Sphere(vec3(-1.1, 0.01, 1.0), -0.45, dielectric));
	Group::Ptr group0 = ToPtr(new Group);
	(*group0) << sphereLeftOut << sphereLeftIn;

	Sphere::CPtr sphereRight = ToCPtr(new Sphere(vec3(1.1, 0, -1.0), 0.5, ToCPtr(new Lambertian(earthTex))));
	Group::Ptr group1 = ToPtr(new Group);

	const vec3 pos(0, 0, 2.5);
	const vec3 viewPoint(0, 0, 0);
	const float fov = 45.0f;
	auto camera = ToCPtr(new TRayCamera(pos, viewPoint, ratioWH, 0, 0, 90.0f));
	(*group1) << bottomWood << sphereMid << group0 << sphereRight << sky;

	return ToCPtr(new Scene(group1, camera));
}

size_t Fit2Square(vector<float>& data) {
	size_t n = static_cast<size_t>(sqrt(data.size()));
	if (n * n < data.size())
		n++;
	data.resize(n * n);
	return n;
}