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
//    // build and compile shaders
//    // -------------------------
//    Shader shaderGeometryPass("GBuffers.vert", "GBuffers.frag");
//    Shader shaderLightingPass("DeferredShading.vert", "DeferredShading.frag");
//    Shader shaderLightBox("DeferredLightBox.vert", "DeferredLightBox.frag");
//
//    // load models
//    // -----------
//    Model backpack(exePath.substr(0, exePath.find_last_of('\\')) + "\\Assets\\model\\nanosuit\\nanosuit.obj");
//    std::vector<glm::vec3> objectPositions;
//    objectPositions.push_back(glm::vec3(-3.0, -0.5, -3.0));
//    objectPositions.push_back(glm::vec3(0.0, -0.5, -3.0));
//    objectPositions.push_back(glm::vec3(3.0, -0.5, -3.0));
//    objectPositions.push_back(glm::vec3(-3.0, -0.5, 0.0));
//    objectPositions.push_back(glm::vec3(0.0, -0.5, 0.0));
//    objectPositions.push_back(glm::vec3(3.0, -0.5, 0.0));
//    objectPositions.push_back(glm::vec3(-3.0, -0.5, 3.0));
//    objectPositions.push_back(glm::vec3(0.0, -0.5, 3.0));
//    objectPositions.push_back(glm::vec3(3.0, -0.5, 3.0));
//
//    // configure g-buffer framebuffer
//    // ------------------------------
//    unsigned int gBuffer;
//    glGenFramebuffers(1, &gBuffer);
//    glBindFramebuffer(GL_FRAMEBUFFER, gBuffer);
//    unsigned int gPosition, gNormal, gAlbedoSpec;
//    // position color buffer
//    glGenTextures(1, &gPosition);
//    glBindTexture(GL_TEXTURE_2D, gPosition);
//    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA16F, SCR_WIDTH, SCR_HEIGHT, 0, GL_RGBA, GL_FLOAT, NULL);
//    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
//    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
//    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, gPosition, 0);
//    // normal color buffer
//    glGenTextures(1, &gNormal);
//    glBindTexture(GL_TEXTURE_2D, gNormal);
//    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA16F, SCR_WIDTH, SCR_HEIGHT, 0, GL_RGBA, GL_FLOAT, NULL);
//    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
//    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
//    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT1, GL_TEXTURE_2D, gNormal, 0);
//    // color + specular color buffer
//    glGenTextures(1, &gAlbedoSpec);
//    glBindTexture(GL_TEXTURE_2D, gAlbedoSpec);
//    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, SCR_WIDTH, SCR_HEIGHT, 0, GL_RGBA, GL_UNSIGNED_BYTE, NULL);
//    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
//    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
//    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT2, GL_TEXTURE_2D, gAlbedoSpec, 0);
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
//    // lighting info
//    // -------------
//    const unsigned int NR_LIGHTS = 32;
//    std::vector<glm::vec3> lightPositions;
//    std::vector<glm::vec3> lightColors;
//    srand(13);
//    for (unsigned int i = 0; i < NR_LIGHTS; i++)
//    {
//        // calculate slightly random offsets
//        float xPos = ((rand() % 100) / 100.0) * 6.0 - 3.0;
//        float yPos = ((rand() % 100) / 100.0) * 6.0 - 4.0;
//        float zPos = ((rand() % 100) / 100.0) * 6.0 - 3.0;
//        lightPositions.push_back(glm::vec3(xPos, yPos, zPos));
//        // also calculate random color
//        float rColor = ((rand() % 100) / 200.0f) + 0.5; // between 0.5 and 1.0
//        float gColor = ((rand() % 100) / 200.0f) + 0.5; // between 0.5 and 1.0
//        float bColor = ((rand() % 100) / 200.0f) + 0.5; // between 0.5 and 1.0
//        lightColors.push_back(glm::vec3(rColor, gColor, bColor));
//    }
//
//    // shader configuration
//    // --------------------
//    shaderLightingPass.use();
//    shaderLightingPass.setInt("gPosition", 0);
//    shaderLightingPass.setInt("gNormal", 1);
//    shaderLightingPass.setInt("gAlbedoSpec", 2);
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
//            
//            // 1. geometry pass: render scene's geometry/color data into gbuffer
//            // -----------------------------------------------------------------
//            glBindFramebuffer(GL_FRAMEBUFFER, gBuffer);
//            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
//            
//            glm::mat4 model = glm::mat4(1.0f);
//            shaderGeometryPass.use();
//            for (unsigned int i = 0; i < objectPositions.size(); i++)
//            {
//                model = glm::mat4(1.0f);
//                model = glm::translate(model, objectPositions[i]);
//                model = glm::scale(model, glm::vec3(0.25f));
//                shaderGeometryPass.setMat4("model", model);
//                backpack.Draw(&shaderGeometryPass, model, viewMat, projMat);
//            }
//            glBindFramebuffer(GL_FRAMEBUFFER, 0);
//
//            // 2. lighting pass: calculate lighting by iterating over a screen filled quad pixel-by-pixel using the gbuffer's content.
//            // -----------------------------------------------------------------------------------------------------------------------
//            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
//            shaderLightingPass.use();
//            glActiveTexture(GL_TEXTURE0);
//            glBindTexture(GL_TEXTURE_2D, gPosition);
//            glActiveTexture(GL_TEXTURE1);
//            glBindTexture(GL_TEXTURE_2D, gNormal);
//            glActiveTexture(GL_TEXTURE2);
//            glBindTexture(GL_TEXTURE_2D, gAlbedoSpec);
//            // send light relevant uniforms
//            for (unsigned int i = 0; i < lightPositions.size(); i++)
//            {
//                string tempVec3 = "lights[" + std::to_string(i) + "].Position";
//                shaderLightingPass.setVec3(tempVec3.c_str(), lightPositions[i]);
//                tempVec3 = "lights[" + std::to_string(i) + "].Color";
//                shaderLightingPass.setVec3(tempVec3.c_str(), lightColors[i]);
//                // update attenuation parameters and calculate radius
//                const float constant = 1.0; // note that we don't send this to the shader, we assume it is always 1.0 (in our case)
//                const float linear = 0.7;
//                const float quadratic = 1.8;
//                tempVec3 = "lights[" + std::to_string(i) + "].Linear";
//                shaderLightingPass.setFloat(tempVec3.c_str(), linear);
//                tempVec3 = "lights[" + std::to_string(i) + "].Quadratic";
//                shaderLightingPass.setFloat(tempVec3.c_str(), quadratic);
//                // then calculate radius of light volume/sphere
//                const float maxBrightness = std::fmaxf(std::fmaxf(lightColors[i].r, lightColors[i].g), lightColors[i].b);
//                float radius = (-linear + std::sqrt(linear * linear - 4 * quadratic * (constant - (256.0f / 5.0f) * maxBrightness))) / (2.0f * quadratic);
//                tempVec3 = "lights[" + std::to_string(i) + "].Radius";
//                shaderLightingPass.setFloat(tempVec3.c_str(), radius);
//            }
//            shaderLightingPass.setVec3("viewPos", camera.Position);
//            // finally render quad
//            renderQuad5();
//
//            // Copy content of geometry's depth buffer to default framebuffer's depth buffer
//            // ----------------------------------------------------------------------------------
//            glBindFramebuffer(GL_READ_FRAMEBUFFER, gBuffer);
//            glBindFramebuffer(GL_DRAW_FRAMEBUFFER, 0);// write to default framebuffer
//            // blit to default framebuffer. Note that this may or may not work as the internal formats of both the FBO and default framebuffer have to match.
//            // the internal formats are implementation defined. This works on all of my systems, but if it doesn't on yours you'll likely have to write to the 		
//            // depth buffer in another shader stage (or somehow see to match the default framebuffer's internal format with the FBO's internal format).
//            glBlitFramebuffer(0, 0, SCR_WIDTH, SCR_HEIGHT, 0, 0, SCR_WIDTH, SCR_HEIGHT, GL_DEPTH_BUFFER_BIT, GL_NEAREST);
//            glBindFramebuffer(GL_FRAMEBUFFER, 0);
//
//            // 3. render lights on top of scene
//            // --------------------------------
//            shaderLightBox.use();
//            shaderLightBox.setMat4("projection", projMat);
//            shaderLightBox.setMat4("view", viewMat);
//            for (unsigned int i = 0; i < lightPositions.size(); i++)
//            {
//                model = glm::mat4(1.0f);
//                model = glm::translate(model, lightPositions[i]);
//                model = glm::scale(model, glm::vec3(0.125f));
//                shaderLightBox.setMat4("model", model);
//                shaderLightBox.setVec3("lightColor", lightColors[i]);
//                renderCube();
//            }
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
