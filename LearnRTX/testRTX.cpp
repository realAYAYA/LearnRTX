//#include<iostream>
//
//#include<CppUtil/Basic/Math.h>
//#include<CppUtil/OpenGL/Window.h>
//#include<CppUtil/OpenGL/Shader.h>
//#include<CppUtil/OpenGL/Model.h>
//#include<CppUtil/OpenGL/Transform.h>
//#include<CppUtil/OpenGL/Scene.h>
//#include<CppUtil/OpenGL/VAO.h>
//#include<CppUtil/OpenGL/FBO.h>
//#include<CppUtil/OpenGL/Texture.h>
//#include<CppUtil/OpenGL/GlobalDefines.h>
//
//#include"CommonDefine.h"
//
//using std::cout;
//using std::endl;
//using CppUtil::OpenGL::Transform;
//using CppUtil::OpenGL::Window;
//using CppUtil::OpenGL::Shader;
//using CppUtil::OpenGL::FBO;
//using CppUtil::OpenGL::VAO;
//using CppUtil::OpenGL::SceneRA;
//using namespace CppUtil::Basic::Math;
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
//    glEnable(GL_DEPTH_TEST);
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
//    shaderPath = exePath.substr(0, exePath.find_last_of('\\')) + "\\..\\LearnRTX\\assets\\shaders\\";
//    texturePath = exePath.substr(0, exePath.find_last_of('\\')) + "\\..\\LearnRTX\\assets\\textures\\";
//    modelPath = exePath.substr(0, exePath.find_last_of('\\')) + "\\..\\LearnRTX\\assets\\model\\";
//
//    VAO VAO_Screen(&(data_ScreenVertices[0]), sizeof(data_ScreenVertices), { 2,2 });// Screen
//    FBO gBuffer(SCR_WIDTH, SCR_HEIGHT, FBO::ENUM_TYPE_GBUFFER);
//
//    Shader shaderGeometryPass(shaderPath + "Advenced\\gBuffer.vs", shaderPath + "Advenced\\gBuffer.fs");
//    //Shader shaderLightingPass(shaderPath + "deferredShading.vs", shaderPath + "deferredShading.fs");
//    Shader shaderRTX(shaderPath + "Advenced\\deferredShading.vs", "Blur.frag");// temp test
//    Shader shaderLightBox(shaderPath + "Advenced\\deferredLightBox.vs", shaderPath + "Advenced\\deferredLightBox.fs");
//    if (!shaderGeometryPass.IsValid() && !shaderRTX.IsValid() && !shaderLightBox.IsValid()) {
//        printf("ERROR: Shader load fail.\n");
//        return 1;
//    }
//    // shader configuration
//    // --------------------
//    shaderRTX.Use();
//    shaderRTX.SetInt("gPosition", 0);
//    shaderRTX.SetInt("gNormal", 1);
//    shaderRTX.SetInt("gAlbedoSpec", 2);
//
//    // CreateScene
//    // -----------
//    SceneRA* scene = CreateScene_CornellBox();
//
//    // Test texture
//    // ------------
//    float _data[16] = { 0.0f,1.0f,2.0f,3.0f,4.0f,5.0f,6.0f,7.0f,8.0f,9.0f,10.0f,11.0f,12.0f,13.0f,14.0f,15.0f };
//    vector<float> data; for (int i = 0; i < 16; i++) { data.push_back(_data[i]); }
//    int sceneDataSize = DataToMap(data);
//    CppUtil::OpenGL::Texture sceneDataTex((sceneDataSize + 1) / 2, (sceneDataSize + 1) / 2, data.data(), GL_FLOAT, GL_RGBA, GL_RGBA32F);// So important
//
//    shaderRTX.SetInt("PackData", 3);// Test
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
//        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);// Clear Screen0.1f, 0.1f, 0.1f, 1.0f
//        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
//
//        // 1. geometry pass: render scene's geometry/color data into gbuffer
//        // -----------------------------------------------------------------
//        glBindFramebuffer(GL_FRAMEBUFFER, gBuffer.GetID());
//        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
//
//        glm::mat4 model = glm::mat4(1.0f);
//        shaderGeometryPass.Use();
//        shaderGeometryPass.SetMat4f("view", mainCamera.GetViewMatrix());
//        shaderGeometryPass.SetMat4f("projection", mainCamera.GetProjectionMatrix());
//
//        /* Draw scene*/
//        scene->Draw(shaderGeometryPass);
//
//        glBindFramebuffer(GL_FRAMEBUFFER, 0);
//
//        // 2.lighting pass: calculate lighting by iterating over a screen filled quad pixel-by-pixel using the gbuffer's content.
//        // ---------------------------------------------------------------------------------------------------------------------
//        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
//        shaderRTX.Use();
//        glActiveTexture(GL_TEXTURE0);
//        glBindTexture(GL_TEXTURE_2D, gBuffer.GetColorTexture(0).GetID());
//        glActiveTexture(GL_TEXTURE1);
//        glBindTexture(GL_TEXTURE_2D, gBuffer.GetColorTexture(1).GetID());
//        glActiveTexture(GL_TEXTURE2);
//        glBindTexture(GL_TEXTURE_2D, gBuffer.GetColorTexture(2).GetID());
//        glActiveTexture(GL_TEXTURE3);
//        glBindTexture(GL_TEXTURE_2D, sceneDataTex.GetID());// Test
//
//        VAO_Screen.Draw(shaderRTX);// Draw Screen-gBuffer
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