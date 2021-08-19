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
//#include <random>
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
//const unsigned int SCR_WIDTH = 800;
//const unsigned int SCR_HEIGHT = 600;
//
//int mainSSAO(int argc, char* argv[]) {
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
//    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);// Tell GLFW we want to call this function on every window resize by registering it
//    glfwSetCursorPosCallback(window, mouse_callback);// Set the required callback functions
//    glfwSetScrollCallback(window, scroll_callback);
//
//    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);// tell GLFW to capture our mouse
//
//    // Load Model and Textures
//    // -------------------------
//    std::string exePath = argv[0];
//
//
//    // New Code
//    // build and compile shaders
//    // -------------------------
//    Shader shaderGeometryPass("ssao_geometry.vert", "ssao_geometry.frag");
//    Shader shaderLightingPass("ssao.vert", "ssao_lighting.frag");
//    Shader shaderSSAO("ssao.vert", "ssao.frag");
//    Shader shaderSSAOBlur("ssao.vert", "ssao_blur.frag");
//
//    // load models
//    // -----------
//    Model backpack(exePath.substr(0, exePath.find_last_of('\\')) + "\\Assets\\model\\nanosuit\\nanosuit.obj");
//    // configure g-buffer framebuffer
//    // ------------------------------
//    unsigned int gBuffer;
//    glGenFramebuffers(1, &gBuffer);
//    glBindFramebuffer(GL_FRAMEBUFFER, gBuffer);
//    unsigned int gPosition, gNormal, gAlbedo;
//    // position color buffer
//    glGenTextures(1, &gPosition);
//    glBindTexture(GL_TEXTURE_2D, gPosition);
//    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA16F, SCR_WIDTH, SCR_HEIGHT, 0, GL_RGBA, GL_FLOAT, NULL);
//    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
//    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
//    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);// 
//    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);// 保证了我们不会不小心采样到在屏幕空间中纹理默认坐标区域之外的深度值
//    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, gPosition, 0);
//    // normal color buffer
//    glGenTextures(1, &gNormal);
//    glBindTexture(GL_TEXTURE_2D, gNormal);
//    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA16F, SCR_WIDTH, SCR_HEIGHT, 0, GL_RGBA, GL_FLOAT, NULL);
//    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
//    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
//    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT1, GL_TEXTURE_2D, gNormal, 0);
//    // color + specular color buffer
//    glGenTextures(1, &gAlbedo);
//    glBindTexture(GL_TEXTURE_2D, gAlbedo);
//    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, SCR_WIDTH, SCR_HEIGHT, 0, GL_RGBA, GL_UNSIGNED_BYTE, NULL);
//    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
//    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
//    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT2, GL_TEXTURE_2D, gAlbedo, 0);
//    // tell OpenGL which color attachments we'll use (of this framebuffer) for rendering 
//    unsigned int attachments[3] = { GL_COLOR_ATTACHMENT0, GL_COLOR_ATTACHMENT1, GL_COLOR_ATTACHMENT2 };
//    glDrawBuffers(3, attachments);
//    // create and attach depth buffer (renderbuffer)
//    unsigned int rboDepth;
//    glGenRenderbuffers(1, &rboDepth);
//    glBindRenderbuffer(GL_RENDERBUFFER, rboDepth);
//    glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT, SCR_WIDTH, SCR_HEIGHT);
//    glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, rboDepth);
//    // finally check if framebuffer is complete
//    if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
//        std::cout << "Framebuffer not complete!" << std::endl;
//    glBindFramebuffer(GL_FRAMEBUFFER, 0);
//
//    // also create framebuffer to hold SSAO processing stage 
//    // -----------------------------------------------------
//    unsigned int ssaoFBO, ssaoBlurFBO;
//    glGenFramebuffers(1, &ssaoFBO);  glGenFramebuffers(1, &ssaoBlurFBO);
//    glBindFramebuffer(GL_FRAMEBUFFER, ssaoFBO);
//    unsigned int ssaoColorBuffer, ssaoColorBufferBlur;
//    // SSAO color buffer
//    glGenTextures(1, &ssaoColorBuffer);
//    glBindTexture(GL_TEXTURE_2D, ssaoColorBuffer);
//    glTexImage2D(GL_TEXTURE_2D, 0, GL_RED, SCR_WIDTH, SCR_HEIGHT, 0, GL_RED, GL_FLOAT, NULL);
//    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
//    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
//    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, ssaoColorBuffer, 0);
//    if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
//        std::cout << "SSAO Framebuffer not complete!" << std::endl;
//    // and blur stage
//    glBindFramebuffer(GL_FRAMEBUFFER, ssaoBlurFBO);
//    glGenTextures(1, &ssaoColorBufferBlur);
//    glBindTexture(GL_TEXTURE_2D, ssaoColorBufferBlur);
//    glTexImage2D(GL_TEXTURE_2D, 0, GL_RED, SCR_WIDTH, SCR_HEIGHT, 0, GL_RED, GL_FLOAT, NULL);
//    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
//    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
//    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, ssaoColorBufferBlur, 0);
//    if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
//        std::cout << "SSAO Blur Framebuffer not complete!" << std::endl;
//    glBindFramebuffer(GL_FRAMEBUFFER, 0);
//
//    // generate sample kernel
//    // ----------------------
//    std::uniform_real_distribution<GLfloat> randomFloats(0.0, 1.0); // generates random floats between 0.0 and 1.0
//    std::default_random_engine generator;
//    std::vector<glm::vec3> ssaoKernel;
//    for (unsigned int i = 0; i < 64; ++i)
//    {
//        glm::vec3 sample(randomFloats(generator) * 2.0 - 1.0, randomFloats(generator) * 2.0 - 1.0, randomFloats(generator));
//        sample = glm::normalize(sample);
//        sample *= randomFloats(generator);
//        float scale = float(i) / 64.0;
//
//        // scale samples s.t. they're more aligned to center of kernel
//        scale = lerp(0.1f, 1.0f, scale * scale);
//        sample *= scale;
//        ssaoKernel.push_back(sample);
//    }
//
//    // generate noise texture
//    // ----------------------
//    std::vector<glm::vec3> ssaoNoise;
//    for (unsigned int i = 0; i < 16; i++)
//    {
//        glm::vec3 noise(randomFloats(generator) * 2.0 - 1.0, randomFloats(generator) * 2.0 - 1.0, 0.0f); // rotate around z-axis (in tangent space)
//        ssaoNoise.push_back(noise);
//    }
//    unsigned int noiseTexture; glGenTextures(1, &noiseTexture);
//    glBindTexture(GL_TEXTURE_2D, noiseTexture);
//    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA32F, 4, 4, 0, GL_RGB, GL_FLOAT, &ssaoNoise[0]);
//    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
//    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
//    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
//    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);// make sure to set its wrapping method to GL_REPEAT so it properly tiles over the screen
//
//    // lighting info
//    // -------------
//    glm::vec3 lightPos = glm::vec3(2.0, 4.0, -2.0);
//    glm::vec3 lightColor = glm::vec3(0.2, 0.2, 0.7);
//
//    // shader configuration
//    // --------------------
//    shaderLightingPass.use();
//    shaderLightingPass.setInt("gPosition", 0);
//    shaderLightingPass.setInt("gNormal", 1);
//    shaderLightingPass.setInt("gAlbedo", 2);
//    shaderLightingPass.setInt("ssao", 3);
//    shaderSSAO.use();
//    shaderSSAO.setInt("gPosition", 0);
//    shaderSSAO.setInt("gNormal", 1);
//    shaderSSAO.setInt("texNoise", 2);
//    shaderSSAOBlur.use();
//    shaderSSAOBlur.setInt("ssaoInput", 0);
//
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
//            // 1. geometry pass: render scene's geometry/color data into gbuffer
//        // -----------------------------------------------------------------
//            glBindFramebuffer(GL_FRAMEBUFFER, gBuffer);
//            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
//
//            glm::mat4 model = glm::mat4(1.0f);
//            shaderGeometryPass.use();
//            shaderGeometryPass.setMat4("projection", projMat);
//            shaderGeometryPass.setMat4("view", viewMat);
//            // room cube
//            model = glm::mat4(1.0f);
//            model = glm::translate(model, glm::vec3(0.0, 7.0f, 0.0f));
//            model = glm::scale(model, glm::vec3(7.5f, 7.5f, 7.5f));
//            shaderGeometryPass.setMat4("model", model);
//            shaderGeometryPass.setInt("invertedNormals", 1); // invert normals as we're inside the cube
//            renderCube();
//            shaderGeometryPass.setInt("invertedNormals", 0);
//            // backpack model on the floor
//            model = glm::mat4(1.0f);
//            model = glm::translate(model, glm::vec3(0.0f, 0.5f, 0.0));
//            model = glm::rotate(model, glm::radians(-90.0f), glm::vec3(1.0, 0.0, 0.0));
//            model = glm::scale(model, glm::vec3(1.0f));
//            
//            backpack.Draw(&shaderGeometryPass);
//            glBindFramebuffer(GL_FRAMEBUFFER, 0);
//
//
//            // 2. generate SSAO texture
//            // ------------------------
//            glBindFramebuffer(GL_FRAMEBUFFER, ssaoFBO);
//            glClear(GL_COLOR_BUFFER_BIT);
//            shaderSSAO.use();
//            // Send kernel + rotation 
//            string tempVec3 = "samples[" + std::to_string(i) + "]";
//
//            for (unsigned int i = 0; i < 64; ++i)
//                shaderSSAO.setVec3(tempVec3.c_str(), ssaoKernel[i]);
//            shaderSSAO.setMat4("projection", projMat);
//            glActiveTexture(GL_TEXTURE0);
//            glBindTexture(GL_TEXTURE_2D, gPosition);
//            glActiveTexture(GL_TEXTURE1);
//            glBindTexture(GL_TEXTURE_2D, gNormal);
//            glActiveTexture(GL_TEXTURE2);
//            glBindTexture(GL_TEXTURE_2D, noiseTexture);
//            renderQuad5();
//            glBindFramebuffer(GL_FRAMEBUFFER, 0);
//
//
//            // 3. blur SSAO texture to remove noise
//            // ------------------------------------
//            glBindFramebuffer(GL_FRAMEBUFFER, ssaoBlurFBO);
//            glClear(GL_COLOR_BUFFER_BIT);
//            shaderSSAOBlur.use();
//            glActiveTexture(GL_TEXTURE0);
//            glBindTexture(GL_TEXTURE_2D, ssaoColorBuffer);
//            renderQuad5();
//            glBindFramebuffer(GL_FRAMEBUFFER, 0);
//
//
//            // 4. lighting pass: traditional deferred Blinn-Phong lighting with added screen-space ambient occlusion
//            // -----------------------------------------------------------------------------------------------------
//            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
//            shaderLightingPass.use();
//            // send light relevant uniforms
//            glm::vec3 lightPosView = glm::vec3(camera.GetViewMarix() * glm::vec4(lightPos, 1.0));
//            shaderLightingPass.setVec3("light.Position", lightPosView);
//            shaderLightingPass.setVec3("light.Color", lightColor);
//            // Update attenuation parameters
//            const float linear = 0.09;
//            const float quadratic = 0.032;
//            shaderLightingPass.setFloat("light.Linear", linear);
//            shaderLightingPass.setFloat("light.Quadratic", quadratic);
//            glActiveTexture(GL_TEXTURE0);
//            glBindTexture(GL_TEXTURE_2D, gPosition);
//            glActiveTexture(GL_TEXTURE1);
//            glBindTexture(GL_TEXTURE_2D, gNormal);
//            glActiveTexture(GL_TEXTURE2);
//            glBindTexture(GL_TEXTURE_2D, gAlbedo);
//            glActiveTexture(GL_TEXTURE3); // add extra SSAO texture to lighting pass
//            glBindTexture(GL_TEXTURE_2D, ssaoColorBufferBlur);
//            renderQuad5();
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
