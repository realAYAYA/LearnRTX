//#include"Shader.h"
//#include"Camera.h"
//#include"Material.h"
//#include"LightDirectional.h"
//#include"LightPoint.h"
//#include"LightSpot.h"
//#include"Mesh.h"
//#include"Model.h"
//#include"Skybox.h"
//#include"World.h"
//#include"SimpleMesh.h"
//
//#include<iostream>
//#define GLEW_STATIC
//#include<GL/glew.h>
//#include<GLFW/glfw3.h>
//
//#include <glm.hpp>
//#include <gtc/matrix_transform.hpp>
//#include <gtc/type_ptr.hpp>
//
//using std::cout;
//using std::endl;
//
//#pragma region Model Data
//#pragma endregion
//
//#pragma region Light Declare
//#pragma endregion
//
//const unsigned int SCR_WIDTH = 800;
//const unsigned int SCR_HEIGHT = 600;
//
//int main(int argc, char* argv[]) {
//    glfwInit();
//    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
//    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
//    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
//    //glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);// Open it in MAC OS X
//
//    // Open GLFW Window
//    GLFWwindow* window = glfwCreateWindow(800, 600, "My OpenGL Game", NULL, NULL);
//    if (window == NULL) {
//        printf("Open window failed.\n");
//        glfwTerminate();
//        return -1;
//    }
//    glfwMakeContextCurrent(window);
//
//    //Init GLEW
//    glewExperimental = true;
//    if (glewInit() != GLEW_OK) {
//        printf("Init GLEW failed.\n");
//        return -1;
//    }
//
//    glViewport(0, 0, 800, 600);
//    cout << "Hello OpenGL!\n";
//
//    // configure global opengl state
//    // -----------------------------
//    glEnable(GL_CULL_FACE);// Face culling
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
//    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);// Tell GLFW we want to call this function on every window resize by registering it
//    glfwSetCursorPosCallback(window, mouse_callback);// Set the required callback functions
//    glfwSetScrollCallback(window, scroll_callback);
//
//    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);// tell GLFW to capture our mouse
//
//
//    // build and compile shaders
//    // -------------------------
//    Shader shader("PointShadow.vert", "PointShadow.frag");
//    Shader simpleDepthShader("PointShadowDepth.vert", "PointShadowDepth.frag", "PointShadowDepth.geom");
//
//    // Load Model and Textures
//    // -------------------------
//    std::string exePath = argv[0];
//
//
//    // New Code
//    unsigned int woodTexture = LoadImageToGPU((exePath.substr(0, exePath.find_last_of('\\')) + "\\textures\\wood.png").c_str());
//
//    // configure depth map FBO
//    // -----------------------
//    const unsigned int SHADOW_WIDTH = 1024, SHADOW_HEIGHT = 1024;
//    unsigned int depthMapFBO;
//    glGenFramebuffers(1, &depthMapFBO);
//    // create depth cubemap texture
//    unsigned int depthCubemap;
//    glGenTextures(1, &depthCubemap);
//    glBindTexture(GL_TEXTURE_CUBE_MAP, depthCubemap);
//    for (unsigned int i = 0; i < 6; ++i)
//        glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_DEPTH_COMPONENT, SHADOW_WIDTH, SHADOW_HEIGHT, 0, GL_DEPTH_COMPONENT, GL_FLOAT, NULL);
//    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
//    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
//    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
//    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
//    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
//    // attach depth texture as FBO's depth buffer
//    glBindFramebuffer(GL_FRAMEBUFFER, depthMapFBO);
//    glFramebufferTexture(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, depthCubemap, 0);// Not 2D
//    glDrawBuffer(GL_NONE);
//    glReadBuffer(GL_NONE);
//    glBindFramebuffer(GL_FRAMEBUFFER, 0);
//
//    // shader configuration
//    // --------------------
//    shader.use();
//    shader.setInt("diffuseTexture", 0);
//    shader.setInt("depthMap", 1);
//
//    // lighting info
//    // -------------
//    glm::vec3 lightPos(0.0f, 0.0f, 0.0f);
//    // New End
//
//#pragma region Prepare MVP matrices
///* Calculate our transformation matrix here.
//|Due to perspective the lines seem to coincide at a far enough distance.
//|This is exactly the effect perspective projection tries to mimic and it does so using a perspective projection matrix.
//|The projection matrix maps a given frustum range to clip space, but also manipulates the w value of each vertex coordinate
//|in such a way that the further away a vertex coordinate is from the viewer, the higher this w component becomes.
//|Its first parameter defines the fov value, that stands for field of view and sets how large the viewspace is.
//|The second parameter sets the aspect ratio which is calculated by dividing the viewport's width by its height.
//|The third and fourth parameter set the near and far plane of the frustum. Usually set 0.1 and 100.0.
//*/
//    glm::mat4 modelMat = glm::mat4(1.0f);
//    glm::mat4 viewMat;
//    glm::mat4 projMat = glm::perspective(glm::radians(45.0f), 800.0f / 600.0f, 0.1f, 100.0f);
//#pragma endregion
//
//    while (!glfwWindowShouldClose(window)) {
//        float currentFrame = glfwGetTime();
//        deltaTime = currentFrame - lastFrame;
//        lastFrame = currentFrame;
//
//        camera.processInput(window, deltaTime);// Process Input linsenter
//        //cout << 1/deltaTime << endl;// Print fps
//
//        // render
//        // ------
//        glClearColor(0.1f, 0.1f, 0.1f, 1.0f);// Clear Screen
//        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
//
//        viewMat = camera.GetViewMarix();
//
//        /* Draw most things as normal, we only care about the Outline things.
//        |The others should NOT fill the stencil buffer so we set its mask to 0x00*/
//        //glStencilMask(0x00);
//
//        for (int i = 0; i < 1; i++) {
//            // move light position over time
//            lightPos.z = sin(glfwGetTime() * 0.5) * 3.0;
//
//            // 0. create depth cubemap transformation matrices
//            // -----------------------------------------------
//            float near_plane = 1.0f;
//            float far_plane = 25.0f;
//            /**
//            |Important to note here is the field of view parameter of glm::perspective that 
//            |we set to 90 degrees. By setting this to 90 degrees we make sure the viewing field 
//            |is exactly large enough to fill a single face of the cubemap such that 
//            |all faces align correctly to each other at the edges.
//            |------------------------------------------------------------------------------------------
//            |The light source represents a point in space so perspective projection makes most sense.
//            */
//            glm::mat4 shadowProj = glm::perspective(glm::radians(90.0f), (float)SHADOW_WIDTH / (float)SHADOW_HEIGHT, near_plane, far_plane);
//            std::vector<glm::mat4> shadowTransforms;
//            shadowTransforms.push_back(shadowProj * glm::lookAt(lightPos, lightPos + glm::vec3(1.0f, 0.0f, 0.0f), glm::vec3(0.0f, -1.0f, 0.0f)));
//            shadowTransforms.push_back(shadowProj * glm::lookAt(lightPos, lightPos + glm::vec3(-1.0f, 0.0f, 0.0f), glm::vec3(0.0f, -1.0f, 0.0f)));
//            shadowTransforms.push_back(shadowProj * glm::lookAt(lightPos, lightPos + glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(0.0f, 0.0f, 1.0f)));
//            shadowTransforms.push_back(shadowProj * glm::lookAt(lightPos, lightPos + glm::vec3(0.0f, -1.0f, 0.0f), glm::vec3(0.0f, 0.0f, -1.0f)));
//            shadowTransforms.push_back(shadowProj * glm::lookAt(lightPos, lightPos + glm::vec3(0.0f, 0.0f, 1.0f), glm::vec3(0.0f, -1.0f, 0.0f)));
//            shadowTransforms.push_back(shadowProj * glm::lookAt(lightPos, lightPos + glm::vec3(0.0f, 0.0f, -1.0f), glm::vec3(0.0f, -1.0f, 0.0f)));
//            
//            // 1. render scene to depth cubemap
//            // --------------------------------
//            glViewport(0, 0, SHADOW_WIDTH, SHADOW_HEIGHT);
//            glBindFramebuffer(GL_FRAMEBUFFER, depthMapFBO);
//            glClear(GL_DEPTH_BUFFER_BIT);
//            simpleDepthShader.use();
//            for (unsigned int i = 0; i < 6; ++i) {
//                string shadowMat = "shadowMatrices[" + std::to_string(i) + "]";
//                simpleDepthShader.setMat4(shadowMat.c_str(), shadowTransforms[i]);
//            }
//            simpleDepthShader.setFloat("far_plane", far_plane);
//            simpleDepthShader.setVec3("lightPos", lightPos);
//            renderScene2(simpleDepthShader);
//            glBindFramebuffer(GL_FRAMEBUFFER, 0);
//
//            // 2. render scene as normal 
//            // -------------------------
//            glViewport(0, 0, SCR_WIDTH, SCR_HEIGHT);
//            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
//            shader.use();
//            shader.setMat4("projection", projMat);
//            shader.setMat4("view", viewMat);
//            // set lighting uniforms
//            shader.setVec3("lightPos", lightPos);
//            shader.setVec3("viewPos", camera.Position);
//            shader.setBool("shadows", true); // enable/disable shadows by 1 | 0
//            shader.setFloat("far_plane", far_plane);
//            glActiveTexture(GL_TEXTURE0);
//            glBindTexture(GL_TEXTURE_2D, woodTexture);
//            glActiveTexture(GL_TEXTURE1);
//            glBindTexture(GL_TEXTURE_CUBE_MAP, depthCubemap);
//            renderScene2(shader);
//        }
//
//        /* Clean up,prepare for next render loop*/
//        glfwPollEvents();
//        glfwSwapBuffers(window);// Update window
//    }
//
//    // Exit Program
//    glfwTerminate();// End
//
//    return 0;
//}
