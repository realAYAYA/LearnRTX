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
//    bool bloom = true;
//    bool bloomKeyPressed = true;
//    float exposure = 1.0f;
//
//    // load textures
//    // -------------
//    unsigned int woodTexture = LoadImageToGPU((exePath.substr(0, exePath.find_last_of('\\')) + "\\Assets\\textures\\wood.png").c_str());
//    unsigned int containerTexture = LoadImageToGPU((exePath.substr(0, exePath.find_last_of('\\')) + "\\Assets\\textures\\container2.png").c_str());
//    
//    // build and compile shaders
//    // -------------------------
//    Shader shader("Bloom.vert", "Bloom.frag");
//    Shader shaderLight("Bloom.vert", "LightBox.frag");
//    Shader shaderBlur("Blur.vert", "Blur.frag");
//    Shader shaderBloomFinal("BloomFinal.vert", "BloomFinal.frag");
//
//    // configure (floating point) framebuffers
//    // ---------------------------------------
//    unsigned int hdrFBO;
//    glGenFramebuffers(1, &hdrFBO);
//    glBindFramebuffer(GL_FRAMEBUFFER, hdrFBO);
//    // create 2 floating point color buffers (1 for normal rendering, other for brightness threshold values)
//    unsigned int colorBuffers[2];
//    glGenTextures(2, colorBuffers);
//    for (unsigned int i = 0; i < 2; i++)
//    {
//        glBindTexture(GL_TEXTURE_2D, colorBuffers[i]);
//        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA16F, SCR_WIDTH, SCR_HEIGHT, 0, GL_RGBA, GL_FLOAT, NULL);
//        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
//        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
//        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);  // we clamp to the edge as the blur filter would otherwise sample repeated texture values!
//        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
//        // attach texture to framebuffer
//        glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0 + i, GL_TEXTURE_2D, colorBuffers[i], 0);
//    }
//    // create and attach depth buffer (renderbuffer)
//    unsigned int rboDepth;
//    glGenRenderbuffers(1, &rboDepth);
//    glBindRenderbuffer(GL_RENDERBUFFER, rboDepth);
//    glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT, SCR_WIDTH, SCR_HEIGHT);
//    glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, rboDepth);
//    // tell OpenGL which color attachments we'll use (of this framebuffer) for rendering 
//    unsigned int attachments[2] = { GL_COLOR_ATTACHMENT0, GL_COLOR_ATTACHMENT1 };
//    glDrawBuffers(2, attachments);
//    // finally check if framebuffer is complete
//    if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
//        std::cout << "Framebuffer not complete!" << std::endl;
//    glBindFramebuffer(GL_FRAMEBUFFER, 0);
//
//    // ping-pong-framebuffer for blurring
//    unsigned int pingpongFBO[2];
//    unsigned int pingpongColorbuffers[2];
//    glGenFramebuffers(2, pingpongFBO);
//    glGenTextures(2, pingpongColorbuffers);
//    for (unsigned int i = 0; i < 2; i++)
//    {
//        glBindFramebuffer(GL_FRAMEBUFFER, pingpongFBO[i]);
//        glBindTexture(GL_TEXTURE_2D, pingpongColorbuffers[i]);
//        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA16F, SCR_WIDTH, SCR_HEIGHT, 0, GL_RGBA, GL_FLOAT, NULL);
//        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
//        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
//        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE); // we clamp to the edge as the blur filter would otherwise sample repeated texture values!
//        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
//        glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, pingpongColorbuffers[i], 0);
//        // also check if framebuffers are complete (no need for depth buffer)
//        if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
//            std::cout << "Framebuffer not complete!" << std::endl;
//    }
//
//    // lighting info
//    // -------------
//    // positions
//    std::vector<glm::vec3> lightPositions;
//    lightPositions.push_back(glm::vec3(0.0f, 0.5f, 1.5f));
//    lightPositions.push_back(glm::vec3(-4.0f, 0.5f, -3.0f));
//    lightPositions.push_back(glm::vec3(3.0f, 0.5f, 1.0f));
//    lightPositions.push_back(glm::vec3(-.8f, 2.4f, -1.0f));
//    // colors
//    std::vector<glm::vec3> lightColors;
//    lightColors.push_back(glm::vec3(5.0f, 5.0f, 5.0f));
//    lightColors.push_back(glm::vec3(10.0f, 0.0f, 0.0f));
//    lightColors.push_back(glm::vec3(0.0f, 0.0f, 15.0f));
//    lightColors.push_back(glm::vec3(0.0f, 5.0f, 0.0f));
//
//
//    // shader configuration
//    // --------------------
//    shader.use();
//    shader.setInt("diffuseTexture", 0);
//    shaderBlur.use();
//    shaderBlur.setInt("image", 0);
//    shaderBloomFinal.use();
//    shaderBloomFinal.setInt("scene", 0);
//    shaderBloomFinal.setInt("bloomBlur", 1);
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
//            // 1. render scene into floating point framebuffer
//            // -----------------------------------------------
//            glBindFramebuffer(GL_FRAMEBUFFER, hdrFBO);
//            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
//
//            // 1. render scene into floating point framebuffer
//        // -----------------------------------------------
//            glBindFramebuffer(GL_FRAMEBUFFER, hdrFBO);
//            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
//            
//            glm::mat4 model = glm::mat4(1.0f);
//            shader.use();
//            shader.setMat4("projection", projMat);
//            shader.setMat4("view", viewMat);
//            glActiveTexture(GL_TEXTURE0);
//            glBindTexture(GL_TEXTURE_2D, woodTexture);
//            // set lighting uniforms
//            for (unsigned int i = 0; i < lightPositions.size(); i++)
//            {
//                string tempVec3 = "lights[" + std::to_string(i) + "].Position";
//                shader.setVec3(tempVec3.c_str(), lightPositions[i]);
//                tempVec3 = "lights[" + std::to_string(i) + "].Color";
//                shader.setVec3(tempVec3.c_str(), lightColors[i]);
//            }
//            shader.setVec3("viewPos", camera.Position);
//            // create one large cube that acts as the floor
//            model = glm::mat4(1.0f);
//            model = glm::translate(model, glm::vec3(0.0f, -1.0f, 0.0));
//            model = glm::scale(model, glm::vec3(12.5f, 0.5f, 12.5f));
//            shader.setMat4("model", model);
//            renderCube();
//            // then create multiple cubes as the scenery
//            glBindTexture(GL_TEXTURE_2D, containerTexture);
//            model = glm::mat4(1.0f);
//            model = glm::translate(model, glm::vec3(0.0f, 1.5f, 0.0));
//            model = glm::scale(model, glm::vec3(0.5f));
//            shader.setMat4("model", model);
//            renderCube();
//
//            model = glm::mat4(1.0f);
//            model = glm::translate(model, glm::vec3(2.0f, 0.0f, 1.0));
//            model = glm::scale(model, glm::vec3(0.5f));
//            shader.setMat4("model", model);
//            renderCube();
//
//            model = glm::mat4(1.0f);
//            model = glm::translate(model, glm::vec3(-1.0f, -1.0f, 2.0));
//            model = glm::rotate(model, glm::radians(60.0f), glm::normalize(glm::vec3(1.0, 0.0, 1.0)));
//            shader.setMat4("model", model);
//            renderCube();
//
//            model = glm::mat4(1.0f);
//            model = glm::translate(model, glm::vec3(0.0f, 2.7f, 4.0));
//            model = glm::rotate(model, glm::radians(23.0f), glm::normalize(glm::vec3(1.0, 0.0, 1.0)));
//            model = glm::scale(model, glm::vec3(1.25));
//            shader.setMat4("model", model);
//            renderCube();
//
//            model = glm::mat4(1.0f);
//            model = glm::translate(model, glm::vec3(-2.0f, 1.0f, -3.0));
//            model = glm::rotate(model, glm::radians(124.0f), glm::normalize(glm::vec3(1.0, 0.0, 1.0)));
//            shader.setMat4("model", model);
//            renderCube();
//
//            model = glm::mat4(1.0f);
//            model = glm::translate(model, glm::vec3(-3.0f, 0.0f, 0.0));
//            model = glm::scale(model, glm::vec3(0.5f));
//            shader.setMat4("model", model);
//            renderCube();
//
//            // finally show all the light sources as bright cubes
//            shaderLight.use();
//            shaderLight.setMat4("projection", projMat);
//            shaderLight.setMat4("view", viewMat);
//
//            for (unsigned int i = 0; i < lightPositions.size(); i++)
//            {
//                model = glm::mat4(1.0f);
//                model = glm::translate(model, glm::vec3(lightPositions[i]));
//                model = glm::scale(model, glm::vec3(0.25f));
//                shaderLight.setMat4("model", model);
//                shaderLight.setVec3("lightColor", lightColors[i]);
//                renderCube();
//            }
//            glBindFramebuffer(GL_FRAMEBUFFER, 0);
//
//            // 2. blur bright fragments with two-pass Gaussian Blur 
//            // --------------------------------------------------
//            bool horizontal = true, first_iteration = true;
//            unsigned int amount = 10;
//            shaderBlur.use();
//            for (unsigned int i = 0; i < amount; i++)
//            {
//                glBindFramebuffer(GL_FRAMEBUFFER, pingpongFBO[horizontal]);
//                shaderBlur.setInt("horizontal", horizontal);
//                glBindTexture(GL_TEXTURE_2D, first_iteration ? colorBuffers[1] : pingpongColorbuffers[!horizontal]);  // bind texture of other framebuffer (or scene if first iteration)
//                renderQuad();
//                horizontal = !horizontal;
//                if (first_iteration)
//                    first_iteration = false;
//            }
//            glBindFramebuffer(GL_FRAMEBUFFER, 0);
//
//            // 3. now render floating point color buffer to 2D quad and tonemap HDR colors to default framebuffer's (clamped) color range
//            // --------------------------------------------------------------------------------------------------------------------------
//            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
//            shaderBloomFinal.use();
//            glActiveTexture(GL_TEXTURE0);
//            glBindTexture(GL_TEXTURE_2D, colorBuffers[0]);
//            glActiveTexture(GL_TEXTURE1);
//            glBindTexture(GL_TEXTURE_2D, pingpongColorbuffers[!horizontal]);
//            shaderBloomFinal.setInt("bloom", bloom);
//            shaderBloomFinal.setFloat("exposure", exposure);
//            renderQuad();
//
//            //std::cout << "bloom: " << (bloom ? "on" : "off") << "| exposure: " << exposure << std::endl;
//
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
