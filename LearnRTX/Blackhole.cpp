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
//#include<CppUtil/OpenGL/Skybox.h>
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
//    // Init workspace path
//    // -------------------------
//    std::string exePath = argv[0];
//    rootPath = exePath.substr(0, exePath.find_last_of('\\')) + "\\..\\assets\\";
//    shaderPath = exePath.substr(0, exePath.find_last_of('\\')) + "\\..\\assets\\shaders\\";
//    texturePath = exePath.substr(0, exePath.find_last_of('\\')) + "\\..\\assets\\textures\\";
//    modelPath = exePath.substr(0, exePath.find_last_of('\\')) + "\\..\\assets\\model\\";
//
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
//    VAO VAO_Screen(&(data_ScreenVertices[0]), sizeof(data_ScreenVertices), { 2,2 });// Screen
//
//    Shader shaderGeometryPass(shaderPath + "Blackhole\\P3T2.vs", shaderPath + "Blackhole\\P3T2.fs");
//    Shader skyboxShader(shaderPath + "Blackhole\\skybox.vs", shaderPath + "Blackhole\\skybox.fs");
//    if (!skyboxShader.IsValid()) {
//        printf("ERROR: Shader load fail.\n");
//        exit(1);
//    }
//    // shader configuration
//    // --------------------
//    // 
//    // 
//    // CreateScene
//    // -----------
//    unsigned int cubeTexture = LoadImageToGPU((texturePath + "container2.png").c_str());
//    shaderGeometryPass.SetInt("texture1", 0);
//    std::vector<string> faces = {
//        rootPath + "\\skybox\\skybox_nebula_dark\\right.png",
//        rootPath + "\\skybox\\skybox_nebula_dark\\left.png",
//        rootPath + "\\skybox\\skybox_nebula_dark\\top.png",
//        rootPath + "\\skybox\\skybox_nebula_dark\\bottom.png",
//        rootPath + "\\skybox\\skybox_nebula_dark\\front.png",
//        rootPath + "\\skybox\\skybox_nebula_dark\\back.png"
//    };
//    CppUtil::OpenGL::Skybox skybox(faces);
//
//    // cube VAO
//    unsigned int cubeVAO, cubeVBO;
//    glGenVertexArrays(1, &cubeVAO);
//    glGenBuffers(1, &cubeVBO);
//    glBindVertexArray(cubeVAO);
//    glBindBuffer(GL_ARRAY_BUFFER, cubeVBO);
//    glBufferData(GL_ARRAY_BUFFER, sizeof(cubeData_PT), &cubeData_PT, GL_STATIC_DRAW);
//    glEnableVertexAttribArray(0);
//    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
//    glEnableVertexAttribArray(1);
//    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
//
//    while (!glfwWindowShouldClose(myWindow.GetGLFWwindow())) {
//        float currentFrame = glfwGetTime();
//        deltaTime = currentFrame - lastFrame;
//        lastFrame = currentFrame;
//
//        myWindow.ProcessKeyboard(deltaTime);
//        printf("\rfps: %.2f     ", 1 / deltaTime);
//
//        glm::mat4 model = glm::mat4(1.0f);
//        glm::mat4 view = mainCamera.GetViewMatrix();
//        glm::mat4 projection = mainCamera.GetProjectionMatrix();
//
//        // render
//        // ------
//        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);// Clear Screen0.1f, 0.1f, 0.1f, 1.0f
//        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
//
//        // Set Mat4
//        // ----
//        shaderGeometryPass.Use();
//        shaderGeometryPass.SetMat4f("model", model);
//        shaderGeometryPass.SetMat4f("view", view);
//        shaderGeometryPass.SetMat4f("projection", projection);
//        
//        // draw cube
//        glActiveTexture(GL_TEXTURE0);
//        glBindTexture(GL_TEXTURE_2D, cubeTexture);
//        glBindVertexArray(cubeVAO);       
//        glDrawArrays(GL_TRIANGLES, 0, 36);
//        glBindVertexArray(0);
//
//        skybox.Draw(&skyboxShader, view, projection);
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