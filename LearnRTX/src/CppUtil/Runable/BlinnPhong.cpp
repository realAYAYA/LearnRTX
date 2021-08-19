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
//float planeVertices[] = 
//{
//    // positions            // normals         // texcoords
//     10.0f, -0.5f,  10.0f,  0.0f, 1.0f, 0.0f,  10.0f,  0.0f,
//    -10.0f, -0.5f,  10.0f,  0.0f, 1.0f, 0.0f,   0.0f,  0.0f,
//    -10.0f, -0.5f, -10.0f,  0.0f, 1.0f, 0.0f,   0.0f, 10.0f,
//
//     10.0f, -0.5f,  10.0f,  0.0f, 1.0f, 0.0f,  10.0f,  0.0f,
//    -10.0f, -0.5f, -10.0f,  0.0f, 1.0f, 0.0f,   0.0f, 10.0f,
//     10.0f, -0.5f, -10.0f,  0.0f, 1.0f, 0.0f,  10.0f, 10.0f
//};
//#pragma endregion
//
//#pragma region Light Declare
//#pragma endregion
//
//const unsigned int SCR_WIDTH = 800;
//const unsigned int SCR_HEIGHT = 600;
//
//int main(int argc, char* argv[]) {
//    #pragma region Open a Window and configure
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
//    glEnable(GL_STENCIL_TEST);
//    glStencilFunc(GL_NOTEQUAL, 1, 0xFF);
//    glStencilOp(GL_KEEP, GL_KEEP, GL_REPLACE);
//    glEnable(GL_DEPTH_TEST);
//    //glDepthFunc(GL_LESS);
//    glEnable(GL_BLEND);
//    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
//    //glEnable(GL_FRAMEBUFFER_SRGB);// OpenGL auto Gamma Correction
//    //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
//
//    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);// Tell GLFW we want to call this function on every window resize by registering it
//    glfwSetCursorPosCallback(window, mouse_callback);// Set the required callback functions
//    glfwSetScrollCallback(window, scroll_callback);
//
//    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);// tell GLFW to capture our mouse
//    #pragma endregion
//
//    #pragma region Init Shader Program
//    Shader* ModelShader = new Shader("BlinnPhong.vert", "BlinnPhong.frag");
//    #pragma endregion
//
//    #pragma region Init Material
//    #pragma endregion
//
//    #pragma region Init Models
//    std::string exePath = argv[0];
//    //Model model(exePath.substr(0, exePath.find_last_of('\\')) + "\\model\\nanosuit\\nanosuit.obj");
//    
//    #pragma endregion
//
//    // New Code
//    bool blinn = true;
//    bool blinnKeyPressed = false;
//
//    // plane VAO
//    unsigned int planeVAO, planeVBO;
//    glGenVertexArrays(1, &planeVAO);
//    glGenBuffers(1, &planeVBO);
//    glBindVertexArray(planeVAO);
//    glBindBuffer(GL_ARRAY_BUFFER, planeVBO);
//    glBufferData(GL_ARRAY_BUFFER, sizeof(planeVertices), planeVertices, GL_STATIC_DRAW);
//    glEnableVertexAttribArray(0);
//    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
//    glEnableVertexAttribArray(1);
//    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
//    glEnableVertexAttribArray(2);
//    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
//    glBindVertexArray(0);
//
//    unsigned int floorTexture = LoadImageToGPU((exePath.substr(0, exePath.find_last_of('\\')) + "\\textures\\wood.png").c_str());
//    
//    ModelShader->use();
//    ModelShader->setInt("floorTexture", 0);
//
//    glm::vec3 lightPos(0.0f, 0.0f, 0.0f);
//    // New End
//
//    #pragma region Prepare MVP matrices
//    /* Calculate our transformation matrix here.
//    |Due to perspective the lines seem to coincide at a far enough distance.
//    |This is exactly the effect perspective projection tries to mimic and it does so using a perspective projection matrix.
//    |The projection matrix maps a given frustum range to clip space, but also manipulates the w value of each vertex coordinate
//    |in such a way that the further away a vertex coordinate is from the viewer, the higher this w component becomes.
//    |Its first parameter defines the fov value, that stands for field of view and sets how large the viewspace is.
//    |The second parameter sets the aspect ratio which is calculated by dividing the viewport's width by its height.
//    |The third and fourth parameter set the near and far plane of the frustum. Usually set 0.1 and 100.0.
//    */
//    glm::mat4 modelMat = glm::mat4(1.0f);
//    glm::mat4 viewMat;
//    glm::mat4 projMat = glm::perspective(glm::radians(45.0f), 800.0f / 600.0f, 0.1f, 100.0f);
//    #pragma endregion
//
//    while (!glfwWindowShouldClose(window)) {
//        float currentFrame = glfwGetTime();
//        deltaTime = currentFrame - lastFrame;
//        lastFrame = currentFrame;
//
//        camera.processInput(window, deltaTime);// Process Input linsenter
//        //cout << 1/deltaTime << endl;// Print fps
//        
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
//        glStencilMask(0x00);
//
//        for (int i = 0; i < 1; i++) {
//            //modelMat = glm::translate(glm::mat4(1.0f), cubePositions[i]);// Set Model matrix
//
//            #pragma region Lights
//            // draw objects
//            ModelShader->use();
//            ModelShader->setMat4("projection", projMat);
//            ModelShader->setMat4("view", viewMat);
//
//            ModelShader->setVec3("viewPos", camera.Position);
//            ModelShader->setVec3("lightPos", lightPos);
//            ModelShader->setInt("blinn", blinn);
//
//            // floor
//            glBindVertexArray(planeVAO);
//            glActiveTexture(GL_TEXTURE0);
//            glBindTexture(GL_TEXTURE_2D, floorTexture);
//            glDrawArrays(GL_TRIANGLES, 0, 6);
//
//            std::cout << (blinn ? "Blinn-Phong" : "Phong") << std::endl;
//            #pragma endregion
//
//            //model.Draw(ModelShader, modelMat, viewMat, projMat);
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
//    delete ModelShader;
//    return 0;
//}