//#include<iostream>
//
//#include<CppUtil/Basic/Math.h>
//#include<CppUtil/OpenGL/Window.h>
//#include <CppUtil/OpenGL/Camera.h>
//#include<CppUtil/OpenGL/Shader.h>
//#include<CppUtil/OpenGL/Model.h>
//#include<CppUtil/OpenGL/Transform.h>
//#include<CppUtil/OpenGL/Scene.h>
//#include<CppUtil/OpenGL/VAO.h>
//#include<CppUtil/OpenGL/FBO.h>
//#include<CppUtil/OpenGL/Texture.h>
//#include<CppUtil/OpenGL/GlobalDefines.h>
//
//#include <CppUtil/RTX/GenData.h>
//#include <CppUtil/RTX/Scene.h>
//#include <CppUtil/RTX/Group.h>
//#include <CppUtil/RTX/Sky.h>
//#include <CppUtil/RTX/Skybox.h>
//#include <CppUtil/RTX/Light.h>
//#include <CppUtil/RTX/Sphere.h>
//#include <CppUtil/RTX/TriMesh.h>
//#include <CppUtil/RTX/Transform.h>
//#include <CppUtil/RTX/TRayCamera.h>
//#include <CppUtil/RTX/ImgTexture.h>
//#include <CppUtil/RTX/ConstTexture.h>
//#include <CppUtil/RTX/Dielectric.h>
//#include <CppUtil/RTX/Metal.h>
//#include <CppUtil/RTX/Lambertian.h>
//
//#include"CommonDefine.h"
//
//using std::cout;
//using std::endl;
//using CppUtil::OpenGL::Window;
//using CppUtil::OpenGL::Shader;
//using CppUtil::OpenGL::FBO;
//using CppUtil::OpenGL::VAO;
//using CppUtil::OpenGL::SceneRA;
//using namespace CppUtil::Basic::Math;
//using namespace RTX;
//
//RTX::Scene::CPtr CreateScene0(float ratioWH);
//
//int main(int argc, char* argv[]) {
//    Window myWindow(SCR_WIDTH, SCR_HEIGHT, "My RTX Game", &mainCamera);
//
//    myWindow.MakeContextCurrent();
//    cout << "Hello OpenGL!\n";
//
//    // configure global opengl state
//    // -----------------------------
//    //glEnable(GL_CULL_FACE);// Face culling
//    //glCullFace(GL_BACK);// GL_FRONT  
//    //glEnable(GL_STENCIL_TEST);
//    //glStencilFunc(GL_NOTEQUAL, 1, 0xFF);
//    //glStencilOp(GL_KEEP, GL_KEEP, GL_REPLACE);
//    //glEnable(GL_DEPTH_TEST);
//    //glDepthFunc(GL_LESS);
//    //glEnable(GL_BLEND);
//    //glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
//    //glEnable(GL_FRAMEBUFFER_SRGB);// OpenGL auto Gamma Correction
//    //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
//
//    myWindow.SetInputMode(GLFW_CURSOR, GLFW_CURSOR_DISABLED);
//    myWindow.SetFramebufferSizeCallback(framebuffer_size_callback);
//    myWindow.SetCursorPosCallback(mouse_callback);
//    myWindow.SetScrollCallback(scroll_callback);
//    //myWindow.SetKeyCallback(key_callback);
//
//    // Init workspace path
//    // -------------------------
//    std::string exePath = argv[0];
//    rootPath = exePath.substr(0, exePath.find_last_of('\\')) + "\\..\\LearnRTX\\assets\\";
//    shaderPath = exePath.substr(0, exePath.find_last_of('\\')) + "\\..\\LearnRTX\\assets\\shaders\\RTX\\";
//    texturePath = exePath.substr(0, exePath.find_last_of('\\')) + "\\..\\LearnRTX\\assets\\textures\\";
//    modelPath = exePath.substr(0, exePath.find_last_of('\\')) + "\\..\\LearnRTX\\assets\\model\\";
//
//    VAO VAO_Screen(&(data_ScreenVertices[0]), sizeof(data_ScreenVertices), { 2,2 });// Screen
//    FBO gBuffer(SCR_WIDTH, SCR_HEIGHT, FBO::ENUM_TYPE_GBUFFER);
//
//    // CreateScene
//    // -----------
//    RTX::Scene::CPtr scene = CreateScene0(myWindow.GetRatioWH());
//    glm::vec3 front = normalize(scene->camera->GetFront());
//    float pitch = asin(front.y) / PI * 180;
//    float yaw = acos(front.x / cos(pitch / 180 * PI)) / PI * 180;
//    CppUtil::OpenGL::Camera roamCamera(scene->camera->GetPos(), yaw, pitch, myWindow.GetRatioWH(), 1, 100);
//    // Trans Scenes'data to texture
//    // ------------
//    GenData genData(scene->obj);
//    auto sceneData = genData.GetSceneData();
//    auto sceneDataSize = DataToMap(sceneData);
//    CppUtil::OpenGL::Texture sceneDataTex(sceneDataSize, sceneDataSize, sceneData.data(), GL_FLOAT, GL_RED, GL_R32F);
//
//    auto matData = genData.GetMatData();
//    auto matDataSize = DataToMap(matData);
//    CppUtil::OpenGL::Texture matDataTex(matDataSize, matDataSize, matData.data(), GL_FLOAT, GL_RED, GL_R32F);
//
//    auto texData = genData.GetTexData();
//    auto texDataSize = DataToMap(texData);
//    CppUtil::OpenGL::Texture texDataTex(texDataSize, texDataSize, texData.data(), GL_FLOAT, GL_RED, GL_R32F);
//
//    auto packData = genData.GetPackData();
//    auto packDataSize = DataToMap(packData);
//    CppUtil::OpenGL::Texture packDataTex((packDataSize + 1) / 2, (packDataSize + 1) / 2, packData.data(), GL_FLOAT, GL_RGBA, GL_RGBA32F);
//
//    CppUtil::OpenGL::Texture skyboxTex(genData.GetSkyboxImgs());
//
//    auto img2idx = genData.GetImgIdxMap();
//    const size_t texArrSize = 16;   
//    CppUtil::OpenGL::Texture texArr[texArrSize];
//    for (auto const& pair : img2idx) {
//        auto img = pair.first;
//        texArr[pair.second] = CppUtil::OpenGL::Texture(CppUtil::OpenGL::Texture::ENUM_TYPE_2D_DYNAMIC);
//        texArr[pair.second].SetImg(*img);
//        //printf("Set TexArr[%d]\n", pair.second);
//    }
//
//    Shader RTX_Shader(shaderPath + "RTX.vs", shaderPath + "RTX.fs");
//    Shader average_Shader(shaderPath +"RTX.vs", shaderPath +"average.fs");
//
//    if (!RTX_Shader.IsValid()|| !average_Shader.IsValid()) {
//        printf("ERROR: Shader load fail.\n");
//        return 1;
//    }
//
//    // shader configuration
//    // --------------------
//    auto camera = scene->camera;
//    TRayCamera::CPtr tCamera = std::dynamic_pointer_cast<const TRayCamera>(camera);
//
//    RTX_Shader.SetInt("SumColor", 0);
//    RTX_Shader.SetInt("RayData0", 1);
//    RTX_Shader.SetInt("RayData1", 2);
//    RTX_Shader.SetInt("RayData2", 3);
//
//    RTX_Shader.SetInt("SceneData", 4);
//    RTX_Shader.SetInt("MatData", 5);
//    RTX_Shader.SetInt("TexData", 6);
//    RTX_Shader.SetInt("PackData", 7);
//
//    RTX_Shader.SetInt("skybox", 8);
//
//    for (size_t i = 0; i < texArrSize; i++) {
//        string TexArr = "TexArr[" + std::to_string(i) + "]";
//        RTX_Shader.SetInt(TexArr.c_str(), 9 + i);
//    }
//
//    RTX_Shader.SetVec3f("camera.pos", camera->GetPos());
//    RTX_Shader.SetVec3f("camera.BL_Corner", camera->GetBL_Corner());
//    RTX_Shader.SetVec3f("camera.horizontal", camera->GetHorizontal());
//    RTX_Shader.SetVec3f("camera.vertical", camera->GetVertical());
//    RTX_Shader.SetVec3f("camera.right", camera->GetRight());
//    RTX_Shader.SetVec3f("camera.up", camera->GetUp());
//    RTX_Shader.SetVec3f("camera.front", camera->GetFront());
//    RTX_Shader.SetFloat("camera.lenR", camera->GetLenR());
//    RTX_Shader.SetFloat("camera.t0", tCamera ? tCamera->GetT0() : 0);
//    RTX_Shader.SetFloat("camera.t1", tCamera ? tCamera->GetT1() : 0);
//
//    //------------ Average Shader
//    average_Shader.SetInt("texture0", 0);
//
//    //------------ RTX FBO
//    bool curReadFBO = false;
//    FBO FBO_RayTracing[2] = { FBO(myWindow.GetWidth(), myWindow.GetHeight(), FBO::ENUM_TYPE_RAYTRACING),FBO(myWindow.GetWidth(), myWindow.GetHeight(), FBO::ENUM_TYPE_RAYTRACING) };
//    FBO FBO_Average(myWindow.GetWidth(), myWindow.GetHeight(), FBO::ENUM_TYPE_COLOR);
//
//    while (!glfwWindowShouldClose(myWindow.GetGLFWwindow())) {
//        float currentFrame = glfwGetTime();
//        deltaTime = currentFrame - lastFrame;
//        lastFrame = currentFrame;
//
//        myWindow.ProcessKeyboard(deltaTime);
//        printf("\rfps: %.2f     ", 1 / deltaTime);
//
//        // render
//        // ------
//        //glClearColor(0.2f, 0.3f, 0.3f, 1.0f);// Clear Screen0.1f, 0.1f, 0.1f, 1.0f
//        //glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
//
//        // cameraUpdate
//        for (int i = 0; i < 1; i++) {
//            static glm::vec3 lastPos(0);
//            static glm::vec3 lastViewPoint(0);
//            static glm::mat4 viewProjectMat = roamCamera.GetProjectionMatrix() * roamCamera.GetViewMatrix();
//
//            if (lastPos == roamCamera.GetPos() && lastViewPoint == roamCamera.GetPos() - roamCamera.GetFront())
//                break;
//
//            lastPos = roamCamera.GetPos();
//            lastViewPoint = roamCamera.GetPos() - roamCamera.GetFront();
//            TRayCamera::CPtr camera = ToCPtr(new TRayCamera(lastPos, lastViewPoint, myWindow.GetRatioWH()));
//            RTX_Shader.SetVec3f("camera.pos", camera->GetPos());
//            RTX_Shader.SetVec3f("camera.BL_Corner", camera->GetBL_Corner());
//            RTX_Shader.SetVec3f("camera.horizontal", camera->GetHorizontal());
//            RTX_Shader.SetVec3f("camera.vertical", camera->GetVertical());
//            RTX_Shader.SetVec3f("camera.right", camera->GetRight());
//            RTX_Shader.SetVec3f("camera.up", camera->GetUp());
//            RTX_Shader.SetVec3f("camera.front", camera->GetFront());
//            RTX_Shader.SetFloat("camera.lenR", camera->GetLenR());
//            RTX_Shader.SetFloat("camera.t0", camera->GetT0());
//            RTX_Shader.SetFloat("camera.t1", camera->GetT1());
//            RTX_Shader.SetMat4f("oldViewProjectMat", viewProjectMat);
//
//            viewProjectMat = roamCamera.GetProjectionMatrix() * roamCamera.GetViewMatrix();
//
//            RTX_Shader.SetFloat("clear", 1.0);           
//        }
//
//        // RTX
//        size_t loopNum = 6;// static_cast<size_t>(glm::max(texWindow.GetScale(), 2.0));
//        for (size_t i = 0; i < loopNum; i++) {
//            FBO_RayTracing[!curReadFBO].Use();
//            FBO_RayTracing[curReadFBO].GetColorTexture(0).Use(0);
//            FBO_RayTracing[curReadFBO].GetColorTexture(1).Use(1);
//            FBO_RayTracing[curReadFBO].GetColorTexture(2).Use(2);
//            FBO_RayTracing[curReadFBO].GetColorTexture(3).Use(3);
//            sceneDataTex.Use(4);
//            matDataTex.Use(5);
//            texDataTex.Use(6);
//            packDataTex.Use(7);
//            skyboxTex.Use(8);
//            for (size_t i = 0; i < texArrSize; i++)
//                texArr[i].Use(9 + i);
//            RTX_Shader.SetFloat("rdSeed[0]", Rand_F());
//            RTX_Shader.SetFloat("rdSeed[1]", Rand_F());
//            RTX_Shader.SetFloat("rdSeed[2]", Rand_F());
//            RTX_Shader.SetFloat("rdSeed[3]", Rand_F());
//            VAO_Screen.Draw(RTX_Shader);
//            RTX_Shader.SetFloat("clear", 0.0);
//            curReadFBO = !curReadFBO;
//        }
//        // average
//        FBO_Average.Use();
//        FBO_RayTracing[curReadFBO].GetColorTexture(0).Use(0);
//        VAO_Screen.Draw(average_Shader);
//
//        /* Clean up,prepare for next render loop*/
//        glfwPollEvents();
//        glfwSwapBuffers(myWindow.GetGLFWwindow());// Update window
//    }
//
//    // Exit Program
//    glfwTerminate();// End
//    return 0;
//}
//
//RTX::Scene::CPtr CreateScene0(float ratioWH) {
//    const std::vector<std::string> str_Vec_Img_Skybox = {
//        rootPath + "skybox/right.jpg",
//        rootPath + "skybox/left.jpg",
//        rootPath + "skybox/top.jpg",
//        rootPath + "skybox/bottom.jpg",
//        rootPath + "skybox/front.jpg",
//        rootPath + "skybox/back.jpg"
//    };
//
//    vector<string> skyboxImgPath(6);
//    for (size_t i = 0; i < 6; i++)
//        skyboxImgPath[i] = str_Vec_Img_Skybox[i];
//    auto sky = ToPtr(new Sky(ToCPtr(new Light(ToCPtr(new Skybox(skyboxImgPath))))));
//
//    auto earthTex = ToCPtr(new ImgTexture(rootPath + "textures\\earth.jpg", true));
//    if (!earthTex->IsValid()) {
//        printf("ERROR: earthTex[%s] is invalid.\n", (rootPath + "textures\\earth.jpg").c_str());
//        exit(1);
//    }
//
//    auto constTex = ToCPtr(new ConstTexture(glm::vec3(0.5, 0.5, 0.5)));
//
//    // Mesh
//    // Mesh Square
//    vector<Vertex> squareVertexs;
//    const float data_SquareVertexPos[48] = {
//        -0.5, -0.5,  0,  0,  0,  1, 0, 0,
//         0.5, -0.5,  0,  0,  0,  1, 1, 0,
//        -0.5,  0.5,  0,  0,  0,  1, 0, 1,
//         0.5,  0.5,  0,  0,  0,  1, 1, 1,
//        -0.5,  0.5,  0,  0,  0,  1, 0, 1,
//         0.5, -0.5,  0,  0,  0,  1, 1, 0,
//    };
//    for (size_t i = 0; i < sizeof(data_SquareVertexPos) / sizeof(float); i += 8) {
//        glm::vec3 pos(data_SquareVertexPos[i], data_SquareVertexPos[i + 1], data_SquareVertexPos[i + 2]);
//        glm::vec3 normal(data_SquareVertexPos[i + 3], data_SquareVertexPos[i + 4], data_SquareVertexPos[i + 5]);
//        glm::vec2 uv(data_SquareVertexPos[i + 6], data_SquareVertexPos[i + 7]);
//        squareVertexs.push_back(Vertex(pos, normal, uv.x, uv.y));
//    }
//    auto square = ToPtr(new TriMesh(squareVertexs));
//    if (!square->IsValid()) {
//        printf("ERROR: square is invalid.\n");
//        exit(1);
//    }
//    glm::mat4 tfmBottom(1.0f);
//    tfmBottom = glm::translate(tfmBottom, glm::vec3(0, -0.5, 0));
//    tfmBottom = glm::rotate(tfmBottom, -PI / 2, glm::vec3(1, 0, 0));
//    tfmBottom = glm::scale(tfmBottom, glm::vec3(8));
//    auto woodMat = ToCPtr(new Lambertian(ToPtr(new ImgTexture(rootPath + "textures\\wood.jpg"))));
//    auto bottomWood = ToPtr(new Transform(tfmBottom, square, woodMat));
//
//    Sphere::CPtr sphereTop = ToCPtr(new Sphere(glm::vec3(0, 0.5, 0), 0.25, ToCPtr(new Metal(constTex, 0.2f))));
//    Sphere::CPtr sphereBottom = ToCPtr(new Sphere(glm::vec3(0, -100.5, -1), 100, ToCPtr(new Lambertian(constTex))));
//
//    Sphere::CPtr sphereMid = ToCPtr(new Sphere(glm::vec3(0, 0, 0), 0.5, ToCPtr(new Metal(glm::vec3(1.0), 0.2))));
//
//    auto dielectric = ToCPtr(new Dielectric(1.5));
//    Sphere::CPtr sphereLeftOut = ToCPtr(new Sphere(glm::vec3(-1.1, 0.01, 1.0), 0.5, dielectric));
//    Sphere::CPtr sphereLeftIn = ToCPtr(new Sphere(glm::vec3(-1.1, 0.01, 1.0), -0.45, dielectric));
//    Group::Ptr group0 = ToPtr(new Group);
//    (*group0) << sphereLeftOut << sphereLeftIn;
//
//    Sphere::CPtr sphereRight = ToCPtr(new Sphere(glm::vec3(1.1, 0, -1.0), 0.5, ToCPtr(new Lambertian(earthTex))));
//    Group::Ptr group1 = ToPtr(new Group);
//
//    const glm::vec3 pos(0, 0, 2.5);
//    const glm::vec3 viewPoint(0, 0, 0);
//    const float fov = 45.0f;
//    auto camera = ToCPtr(new TRayCamera(pos, viewPoint, ratioWH, 0, 0, 90.0f));
//    (*group1) << bottomWood << sphereMid << group0 << sphereRight << sky;
//
//    return ToCPtr(new Scene(group1, camera));
//}