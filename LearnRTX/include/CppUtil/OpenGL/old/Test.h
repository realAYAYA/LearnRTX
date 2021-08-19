#pragma once
#include"Shader.h"
#include"Camera.h"
#include"Material.h"
#include"LightDirectional.h"
#include"LightPoint.h"
#include"LightSpot.h"
#include"Mesh.h"
#include"Model.h"
#include"Skybox.h"
#include"DeferredRender.h"
#include"ModelManager.h"
#include"LightManager.h"
#include"World.h"
#include"SimpleMesh.h"

#include<iostream>
#include<random>
#define GLEW_STATIC
#include<GL/glew.h>
#include<GLFW/glfw3.h>

#include <glm.hpp>
#include <gtc/matrix_transform.hpp>
#include <gtc/type_ptr.hpp>

using std::cout;
using std::endl;

const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

int DeferredShading(int argc, char* argv[]);
int SSAO(int argc, char* argv[]);

int SSAO(int argc, char* argv[]) {
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    //glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);// Open it in MAC OS X

    // Open GLFW Window
    GLFWwindow* window = glfwCreateWindow(800, 600, "My OpenGL Game", NULL, NULL);
    if (window == NULL) {
        printf("Open window failed.\n");
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);

    //Init GLEW
    glewExperimental = true;
    if (glewInit() != GLEW_OK) {
        printf("Init GLEW failed.\n");
        return -1;
    }

    glViewport(0, 0, 800, 600);
    cout << "Hello OpenGL!\n";

    // configure global opengl state
    // -----------------------------
    //glEnable(GL_CULL_FACE);// Face culling
    //glCullFace(GL_BACK);// GL_FRONT  
    //glEnable(GL_STENCIL_TEST);
    //glStencilFunc(GL_NOTEQUAL, 1, 0xFF);
    //glStencilOp(GL_KEEP, GL_KEEP, GL_REPLACE);
    glEnable(GL_DEPTH_TEST);
    //glDepthFunc(GL_LESS);
    //glEnable(GL_BLEND);
    //glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    //glEnable(GL_FRAMEBUFFER_SRGB);// OpenGL auto Gamma Correction
    //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);// Tell GLFW we want to call this function on every window resize by registering it
    glfwSetCursorPosCallback(window, mouse_callback);// Set the required callback functions
    glfwSetScrollCallback(window, scroll_callback);

    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);// tell GLFW to capture our mouse

    // Load Model and Textures
    // -------------------------
    std::string exePath = argv[0];


    // New Code
    // build and compile shaders
    // -------------------------
    Shader shaderGeometryPass("gBuffer.vert", "gBuffer.frag");
    Shader shaderLightingPass("deferredShader.vert", "deferredShader.frag");
    Shader shaderSSAO("ssao.vert", "ssao.frag");
    Shader shaderSSAOBlur("ssao.vert", "ssao_blur.frag");
    Shader shaderLightBox("DeferredLightBox.vert", "DeferredLightBox.frag");

    // load models
    // -----------
    Model backpack(exePath.substr(0, exePath.find_last_of('\\')) + "\\Assets\\model\\nanosuit\\nanosuit.obj");
    
    ModelManager modelManager;
    modelManager.push_back(&backpack);
    // lighting info
    // -------------
    LightManager myLightManager;

    const unsigned int NR_LIGHTS = 32;
    std::vector<glm::vec3> lightPositions;
    std::vector<glm::vec3> lightColors;
    srand(13);
    for (unsigned int i = 0; i < NR_LIGHTS; i++)
    {
        // calculate slightly random offsets
        float xPos = ((rand() % 100) / 100.0) * 6.0 - 3.0;
        float yPos = ((rand() % 100) / 100.0) * 6.0 - 4.0;
        float zPos = ((rand() % 100) / 100.0) * 6.0 - 3.0;

        // also calculate random color
        float rColor = ((rand() % 100) / 200.0f) + 0.5; // between 0.5 and 1.0
        float gColor = ((rand() % 100) / 200.0f) + 0.5; // between 0.5 and 1.0
        float bColor = ((rand() % 100) / 200.0f) + 0.5; // between 0.5 and 1.0

        LightPoint* plight = new LightPoint(glm::vec3(xPos, yPos, zPos), glm::vec3(rColor, gColor, bColor));
        myLightManager.PointLightPool.push_back(plight);
    }


    DeferredRender MyDeferredRender;
    MyDeferredRender.SCR_WIDTH = SCR_WIDTH;
    MyDeferredRender.SCR_HEIGHT = SCR_HEIGHT;

    MyDeferredRender.shaderGeometryPass = &shaderGeometryPass;
    MyDeferredRender.shaderLightingPass = &shaderLightingPass;
    MyDeferredRender.shaderSSAO = &shaderSSAO;
    MyDeferredRender.shaderSSAOBlur = &shaderSSAOBlur;

    MyDeferredRender.modelManager = &modelManager;
    MyDeferredRender.lightManager = &myLightManager;
    MyDeferredRender.Initialize();
    MyDeferredRender.InitSSAO();
    
    // New End

#pragma region Prepare MVP matrices
/* Calculate our transformation matrix here.
|Due to perspective the lines seem to coincide at a far enough distance.
|This is exactly the effect perspective projection tries to mimic and it does so using a perspective projection matrix.
|The projection matrix maps a given frustum range to clip space, but also manipulates the w value of each vertex coordinate
|in such a way that the further away a vertex coordinate is from the viewer, the higher this w component becomes.
|Its first parameter defines the fov value, that stands for field of view and sets how large the viewspace is.
|The second parameter sets the aspect ratio which is calculated by dividing the viewport's width by its height.
|The third and fourth parameter set the near and far plane of the frustum. Usually set 0.1 and 100.0.
*/
    glm::mat4 modelMat = glm::mat4(1.0f);
    glm::mat4 viewMat;
    glm::mat4 projMat = glm::perspective(glm::radians(45.0f), 800.0f / 600.0f, 0.1f, 100.0f);
#pragma endregion

    while (!glfwWindowShouldClose(window)) {
        float currentFrame = glfwGetTime();
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;

        camera.processInput(window, deltaTime);// Process Input linsenter
        //cout << 1/deltaTime << endl;// Print fps

        // render
        // ------
        glClearColor(0.1f, 0.1f, 0.1f, 1.0f);// Clear Screen
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        viewMat = camera.GetViewMarix();

        /* Draw most things as normal, we only care about the Outline things.
        |The others should NOT fill the stencil buffer so we set its mask to 0x00*/
        //glStencilMask(0x00);

        // ���ǽ�ģ�ͱ任�����ó���
        glm::mat4 model = glm::mat4(1.0f);
        model = glm::mat4(1.0f);
        model = glm::translate(model, glm::vec3(0.0f, 0.5f, 0.0));
        model = glm::rotate(model, glm::radians(-90.0f), glm::vec3(1.0, 0.0, 0.0));
        model = glm::scale(model, glm::vec3(1.0f));

        backpack.SetWorldLocation(model);

        for (int i = 0; i < 1; i++) {

            MyDeferredRender.FillgBuffer(projMat, &camera);

            //// room cube
            //model = glm::mat4(1.0f);
            //model = glm::translate(model, glm::vec3(0.0, 7.0f, 0.0f));
            //model = glm::scale(model, glm::vec3(7.5f, 7.5f, 7.5f));
            //shaderGeometryPass.setMat4("model", model);
            ////shaderGeometryPass.setInt("invertedNormals", 1);// invert normals as we're inside the cube
            //renderCube();
            //shaderGeometryPass.setInt("invertedNormals", 0);// ��������Ϊ�ڷ����ڲ�����������������ǳ����ʱ�Ķ�
            
            MyDeferredRender.FillSSAOBuffer(projMat);
            
            MyDeferredRender.SendLights(&camera);

            MyDeferredRender.RenderQuad();

            //MyDeferredRender.Draw(projMat, &camera);


            // Copy content of geometry's depth buffer to default framebuffer's depth buffer
            // ���ﲻ�ٻ��ƹ��պ��ӣ��������ǳ�������������Ŀ��
            // ----------------------------------------------------------------------------------
            //glBindFramebuffer(GL_READ_FRAMEBUFFER, MyDeferredRender.gBuffer);
            //glBindFramebuffer(GL_DRAW_FRAMEBUFFER, 0);// write to default framebuffer
            //// blit to default framebuffer. Note that this may or may not work as the internal formats of both the FBO and default framebuffer have to match.
            //// the internal formats are implementation defined. This works on all of my systems, but if it doesn't on yours you'll likely have to write to the 		
            //// depth buffer in another shader stage (or somehow see to match the default framebuffer's internal format with the FBO's internal format).
            //glBlitFramebuffer(0, 0, SCR_WIDTH, SCR_HEIGHT, 0, 0, SCR_WIDTH, SCR_HEIGHT, GL_DEPTH_BUFFER_BIT, GL_NEAREST);
            //glBindFramebuffer(GL_FRAMEBUFFER, 0);
            //// 3. render lights on top of scene
            //// --------------------------------
            //shaderLightBox.use();
            //shaderLightBox.setMat4("projection", projMat);
            //shaderLightBox.setMat4("view", viewMat);
            //for (unsigned int i = 0; i < myLightManager.PointLightPool.size(); i++)
            //{
            //    model = glm::mat4(1.0f);
            //    model = glm::translate(model, myLightManager.PointLightPool[i]->position);
            //    model = glm::scale(model, glm::vec3(0.125f));
            //    shaderLightBox.setMat4("model", model);
            //    shaderLightBox.setVec3("lightColor", myLightManager.PointLightPool[i]->color);
            //    renderCube();
            //}
            
        }

        /* Clean up,prepare for next render loop*/
        glfwPollEvents();
        glfwSwapBuffers(window);// Update window
    }

    // Exit Program
    glfwTerminate();// End

    return 0;
}

int DeferredShading(int argc, char* argv[]) {
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    //glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);// Open it in MAC OS X

    // Open GLFW Window
    GLFWwindow* window = glfwCreateWindow(800, 600, "My OpenGL Game", NULL, NULL);
    if (window == NULL) {
        printf("Open window failed.\n");
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);

    //Init GLEW
    glewExperimental = true;
    if (glewInit() != GLEW_OK) {
        printf("Init GLEW failed.\n");
        return -1;
    }

    glViewport(0, 0, 800, 600);
    cout << "Hello OpenGL!\n";

    // configure global opengl state
    // -----------------------------
    //glEnable(GL_CULL_FACE);// Face culling
    //glCullFace(GL_BACK);// GL_FRONT  
    //glEnable(GL_STENCIL_TEST);
    //glStencilFunc(GL_NOTEQUAL, 1, 0xFF);
    //glStencilOp(GL_KEEP, GL_KEEP, GL_REPLACE);
    glEnable(GL_DEPTH_TEST);
    //glDepthFunc(GL_LESS);
    //glEnable(GL_BLEND);
    //glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    //glEnable(GL_FRAMEBUFFER_SRGB);// OpenGL auto Gamma Correction
    //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);// Tell GLFW we want to call this function on every window resize by registering it
    glfwSetCursorPosCallback(window, mouse_callback);// Set the required callback functions
    glfwSetScrollCallback(window, scroll_callback);

    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);// tell GLFW to capture our mouse

    // Load Model and Textures
    // -------------------------
    std::string exePath = argv[0];


    // New Code
    // build and compile shaders
    // -------------------------
    Shader shaderGeometryPass("gBuffer.vert", "gBuffer.frag");
    Shader shaderLightingPass("deferredShader.vert", "deferredShader.frag");
    Shader shaderLightBox("DeferredLightBox.vert", "DeferredLightBox.frag");// ����������Ⱦ���պ���

    // load models
    // -----------
    Model backpack(exePath.substr(0, exePath.find_last_of('\\')) + "\\Assets\\model\\nanosuit\\nanosuit.obj");
    Model nanosuit(exePath.substr(0, exePath.find_last_of('\\')) + "\\Assets\\model\\nanosuit\\nanosuit.obj");

    ModelManager modelManager;
    modelManager.push_back(&backpack);
    modelManager.push_back(&nanosuit);

    // lighting info
    // -------------
    LightManager myLightManager;

    const unsigned int NR_LIGHTS = 32;
    std::vector<glm::vec3> lightPositions;
    std::vector<glm::vec3> lightColors;
    srand(13);
    for (unsigned int i = 0; i < NR_LIGHTS; i++)
    {
        // calculate slightly random offsets
        float xPos = ((rand() % 100) / 100.0) * 6.0 - 3.0;
        float yPos = ((rand() % 100) / 100.0) * 6.0 - 4.0;
        float zPos = ((rand() % 100) / 100.0) * 6.0 - 3.0;

        // also calculate random color
        float rColor = ((rand() % 100) / 200.0f) + 0.5; // between 0.5 and 1.0
        float gColor = ((rand() % 100) / 200.0f) + 0.5; // between 0.5 and 1.0
        float bColor = ((rand() % 100) / 200.0f) + 0.5; // between 0.5 and 1.0

        LightPoint* plight = new LightPoint(glm::vec3(xPos, yPos, zPos), glm::vec3(rColor, gColor, bColor));
        myLightManager.PointLightPool.push_back(plight);
    }

    DeferredRender MyDeferredRender;
    MyDeferredRender.SCR_WIDTH = SCR_WIDTH;
    MyDeferredRender.SCR_HEIGHT = SCR_HEIGHT;
    MyDeferredRender.shaderGeometryPass = &shaderGeometryPass;
    MyDeferredRender.shaderLightingPass = &shaderLightingPass;
    MyDeferredRender.Initialize();
    MyDeferredRender.modelManager = &modelManager;
    MyDeferredRender.lightManager = &myLightManager;
    // New End

#pragma region Prepare MVP matrices
/* Calculate our transformation matrix here.
|Due to perspective the lines seem to coincide at a far enough distance.
|This is exactly the effect perspective projection tries to mimic and it does so using a perspective projection matrix.
|The projection matrix maps a given frustum range to clip space, but also manipulates the w value of each vertex coordinate
|in such a way that the further away a vertex coordinate is from the viewer, the higher this w component becomes.
|Its first parameter defines the fov value, that stands for field of view and sets how large the viewspace is.
|The second parameter sets the aspect ratio which is calculated by dividing the viewport's width by its height.
|The third and fourth parameter set the near and far plane of the frustum. Usually set 0.1 and 100.0.
*/
    glm::mat4 modelMat = glm::mat4(1.0f);
    glm::mat4 viewMat;
    glm::mat4 projMat = glm::perspective(glm::radians(45.0f), 800.0f / 600.0f, 0.1f, 100.0f);
#pragma endregion

    while (!glfwWindowShouldClose(window)) {
        float currentFrame = glfwGetTime();
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;

        camera.processInput(window, deltaTime);// Process Input linsenter
        //cout << 1/deltaTime << endl;// Print fps

        // render
        // ------
        glClearColor(0.1f, 0.1f, 0.1f, 1.0f);// Clear Screen
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        viewMat = camera.GetViewMarix();

        /* Draw most things as normal, we only care about the Outline things.
        |The others should NOT fill the stencil buffer so we set its mask to 0x00*/
        //glStencilMask(0x00);

        // ���ǽ�ģ�͵�λ�ñ任���������ͻ�������ֿ�
        glm::mat4 model = glm::mat4(1.0f);
        model = glm::translate(model, glm::vec3(-3.0, -0.5, -3.0));
        model = glm::scale(model, glm::vec3(0.25f));
        backpack.SetWorldLocation(model);

        model = glm::mat4(1.0f);
        model = glm::translate(model, glm::vec3(0.0, -0.5, -3.0));
        model = glm::scale(model, glm::vec3(0.25f));
        nanosuit.SetWorldLocation(model);

        for (int i = 0; i < 1; i++) {

            MyDeferredRender.Draw(projMat, &camera);// Deferred shading.

            // Copy content of geometry's depth buffer to default framebuffer's depth buffer
            // ----------------------------------------------------------------------------------
            glBindFramebuffer(GL_READ_FRAMEBUFFER, MyDeferredRender.gBuffer);
            glBindFramebuffer(GL_DRAW_FRAMEBUFFER, 0);// write to default framebuffer
            // blit to default framebuffer. Note that this may or may not work as the internal formats of both the FBO and default framebuffer have to match.
            // the internal formats are implementation defined. This works on all of my systems, but if it doesn't on yours you'll likely have to write to the 		
            // depth buffer in another shader stage (or somehow see to match the default framebuffer's internal format with the FBO's internal format).
            glBlitFramebuffer(0, 0, SCR_WIDTH, SCR_HEIGHT, 0, 0, SCR_WIDTH, SCR_HEIGHT, GL_DEPTH_BUFFER_BIT, GL_NEAREST);
            glBindFramebuffer(GL_FRAMEBUFFER, 0);

            // 3. render lights on top of scene
            // --------------------------------
            shaderLightBox.use();
            shaderLightBox.setMat4("projection", projMat);
            shaderLightBox.setMat4("view", viewMat);
            for (unsigned int i = 0; i < myLightManager.PointLightPool.size(); i++)
            {
                model = glm::mat4(1.0f);
                model = glm::translate(model, myLightManager.PointLightPool[i]->position);
                model = glm::scale(model, glm::vec3(0.125f));
                shaderLightBox.setMat4("model", model);
                shaderLightBox.setVec3("lightColor", myLightManager.PointLightPool[i]->color);
                renderCube();
            }

        }

        /* Clean up,prepare for next render loop*/
        glfwPollEvents();
        glfwSwapBuffers(window);// Update window
    }

    // Exit Program
    glfwTerminate();// End

    return 0;
}