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
//
//    // build and compile shaders
//    // -------------------------
//    Shader shader("ParallaxMapping.vert", "ParallaxMapping.frag");
//
//    // Load Model and Textures
//    // -------------------------
//    std::string exePath = argv[0];
//
//
//    // New Code
//    float heightScale = 0.1;
//
//    /*unsigned int diffuseMap = LoadImageToGPU((exePath.substr(0, exePath.find_last_of('\\')) + "\\Assets\\textures\\bricks2.jpg").c_str());
//    unsigned int normalMap = LoadImageToGPU((exePath.substr(0, exePath.find_last_of('\\')) + "\\Assets\\textures\\bricks2_normal.jpg").c_str());
//    unsigned int heightMap = LoadImageToGPU((exePath.substr(0, exePath.find_last_of('\\')) + "\\Assets\\textures\\bricks2_disp.jpg").c_str());
//    */unsigned int diffuseMap = LoadImageToGPU((exePath.substr(0, exePath.find_last_of('\\')) + "\\Assets\\textures\\wood.png").c_str());
//    unsigned int normalMap = LoadImageToGPU((exePath.substr(0, exePath.find_last_of('\\')) + "\\Assets\\textures\\toy_box_normal.png").c_str());
//    unsigned int heightMap = LoadImageToGPU((exePath.substr(0, exePath.find_last_of('\\')) + "\\Assets\\textures\\toy_box_disp.png").c_str());
//
//
//    // shader configuration
//    // --------------------
//    shader.use();
//    shader.setInt("diffuseMap", 0);
//    shader.setInt("normalMap", 1);
//    shader.setInt("depthMap", 2);
//
//    // lighting info
//    // -------------
//    glm::vec3 lightPos(0.5f, 1.0f, 0.3f);
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
//            shader.use();
//            shader.setMat4("projection", projMat);
//            shader.setMat4("view", viewMat);
//            // render parallax-mapped quad
//            glm::mat4 model = glm::mat4(1.0f);
//            model = glm::rotate(model, glm::radians((float)glfwGetTime() * -10.0f), glm::normalize(glm::vec3(1.0, 0.0, 1.0))); // rotate the quad to show parallax mapping from multiple directions
//            shader.setMat4("model", model);
//            shader.setVec3("viewPos", camera.Position);
//            shader.setVec3("lightPos", lightPos);
//            shader.setFloat("heightScale", heightScale); // adjust with Q and E keys
//            std::cout << heightScale << std::endl;
//            glActiveTexture(GL_TEXTURE0);
//            glBindTexture(GL_TEXTURE_2D, diffuseMap);
//            glActiveTexture(GL_TEXTURE1);
//            glBindTexture(GL_TEXTURE_2D, normalMap);
//            glActiveTexture(GL_TEXTURE2);
//            glBindTexture(GL_TEXTURE_2D, heightMap);
//            renderQuad3();
//
//            // render light source (simply re-renders a smaller plane at the light's position for debugging/visualization)
//            model = glm::mat4(1.0f);
//            model = glm::translate(model, lightPos);
//            model = glm::scale(model, glm::vec3(0.1f));
//            shader.setMat4("model", model);
//            renderQuad3();
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
