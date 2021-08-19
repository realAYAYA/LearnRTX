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
#include<iostream>
//#define GLEW_STATIC
//#include<GL/glew.h>
//#include<GLFW/glfw3.h>
//
//#include <glm.hpp>
//#include <gtc/matrix_transform.hpp>
//#include <gtc/type_ptr.hpp>
//
using std::cout;
using std::endl;
//
//#pragma region Model Data
//GLfloat skyboxVertices[] = {
//    // Positions          
//    -1.0f,  1.0f, -1.0f,
//    -1.0f, -1.0f, -1.0f,
//     1.0f, -1.0f, -1.0f,
//     1.0f, -1.0f, -1.0f,
//     1.0f,  1.0f, -1.0f,
//    -1.0f,  1.0f, -1.0f,
//
//    -1.0f, -1.0f,  1.0f,
//    -1.0f, -1.0f, -1.0f,
//    -1.0f,  1.0f, -1.0f,
//    -1.0f,  1.0f, -1.0f,
//    -1.0f,  1.0f,  1.0f,
//    -1.0f, -1.0f,  1.0f,
//
//     1.0f, -1.0f, -1.0f,
//     1.0f, -1.0f,  1.0f,
//     1.0f,  1.0f,  1.0f,
//     1.0f,  1.0f,  1.0f,
//     1.0f,  1.0f, -1.0f,
//     1.0f, -1.0f, -1.0f,
//
//    -1.0f, -1.0f,  1.0f,
//    -1.0f,  1.0f,  1.0f,
//     1.0f,  1.0f,  1.0f,
//     1.0f,  1.0f,  1.0f,
//     1.0f, -1.0f,  1.0f,
//    -1.0f, -1.0f,  1.0f,
//
//    -1.0f,  1.0f, -1.0f,
//     1.0f,  1.0f, -1.0f,
//     1.0f,  1.0f,  1.0f,
//     1.0f,  1.0f,  1.0f,
//    -1.0f,  1.0f,  1.0f,
//    -1.0f,  1.0f, -1.0f,
//
//    -1.0f, -1.0f, -1.0f,
//    -1.0f, -1.0f,  1.0f,
//     1.0f, -1.0f, -1.0f,
//     1.0f, -1.0f, -1.0f,
//    -1.0f, -1.0f,  1.0f,
//     1.0f, -1.0f,  1.0f
//};
//#pragma endregion
//
//#pragma region Light Declare
//LightDirectional lightD(std::string("lightD"), glm::vec3(1.0f, 1.0f, -1.0f),
//    glm::vec3(glm::radians(90.0f), glm::radians(0.0f), 0),
//    glm::vec3(1.0f, 1.0, 1.0f));
//LightPoint lightP0(std::string("lightP0"),glm::vec3(1.0f, 0, 0), 
//    glm::vec3(glm::radians(45.0f), glm::radians(45.0f), 0),
//    glm::vec3(1.0f, 0, 0));
//LightPoint lightP1(std::string("lightP1"), glm::vec3(0, 1.0f, 0),
//    glm::vec3(glm::radians(45.0f), glm::radians(45.0f), 0),
//    glm::vec3(0, 1.0f, 0));
//LightPoint lightP2(std::string("lightP2"), glm::vec3(0, 0, 1.0f),
//    glm::vec3(glm::radians(45.0f), glm::radians(45.0f), 0),
//    glm::vec3(0, 0, 1.0f));
//LightPoint lightP3(std::string("lightP3"), glm::vec3(1.0f, 1.0f, 1.0f),
//    glm::vec3(glm::radians(45.0f), glm::radians(45.0f), 0),
//    glm::vec3(1.0f, 1.0f, 1.0f));
//LightSpot lightS(std::string("lightS"), glm::vec3(0, 5.0f, 0),
//    glm::vec3(glm::radians(90.0f), glm::radians(0.0f), 0),
//    glm::vec3(10.0f, 10.0f, 10.0f));
//#pragma endregion
//
//const unsigned int SCR_WIDTH = 800;
//const unsigned int SCR_HEIGHT = 600;
//
//int main(int argc,char *argv[]) {
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
//    //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
//
//    glEnable(GL_CULL_FACE);// Face culling
//    glCullFace(GL_BACK);// GL_FRONT
//    glEnable(GL_DEPTH_TEST);
//    glDepthFunc(GL_LESS);
//    glEnable(GL_STENCIL_TEST);
//    glStencilFunc(GL_NOTEQUAL, 1, 0xFF);
//    glStencilOp(GL_KEEP, GL_KEEP, GL_REPLACE);
//
//    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);// Tell GLFW we want to call this function on every window resize by registering it
//    glfwSetCursorPosCallback(window, mouse_callback);// Set the required callback functions
//    glfwSetScrollCallback(window, scroll_callback);
//
//    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);// tell GLFW to capture our mouse
//    #pragma endregion
//
//    #pragma region Init Shader Program
//    Shader* ModelShader = new Shader("model.vert", "model.frag");
//    Shader* skyboxShader = new Shader("skybox.vert", "skybox.frag");
//    Shader* shaderSingleColor = new Shader("model.vert", "shaderSingleColor.frag");
//    #pragma endregion
//
//    #pragma region Init Material
//    #pragma endregion
//
//    #pragma region Init Models
//    std::string exePath = argv[0];
//    Model model(exePath.substr(0, exePath.find_last_of('\\')) + "\\model\\nanosuit\\nanosuit.obj");
//    std::vector<string> faces;
//    faces.push_back(exePath.substr(0, exePath.find_last_of('\\')) + "\\skybox\\right.jpg");
//    faces.push_back(exePath.substr(0, exePath.find_last_of('\\')) + "\\skybox\\left.jpg");
//    faces.push_back(exePath.substr(0, exePath.find_last_of('\\')) + "\\skybox\\top.jpg");
//    faces.push_back(exePath.substr(0, exePath.find_last_of('\\')) + "\\skybox\\bottom.jpg");
//    faces.push_back(exePath.substr(0, exePath.find_last_of('\\')) + "\\skybox\\back.jpg");
//    faces.push_back(exePath.substr(0, exePath.find_last_of('\\')) + "\\skybox\\front.jpg");
//    std::vector<GLfloat> _vertices;
//    for (int i = 0; i < 108; i++) {
//        _vertices.push_back(skyboxVertices[i]);
//    }
//    Skybox skybox(_vertices, faces);
//    #pragma endregion
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
//    glm::mat4 modelMat=glm::mat4(1.0f);
//    glm::mat4 viewMat;
//    glm::mat4 projMat = glm::perspective(glm::radians(45.0f), 800.0f / 600.0f, 0.1f, 100.0f);    
//    #pragma endregion
//
//    while (!glfwWindowShouldClose(window)) {
//        float currentFrame = glfwGetTime();
//        deltaTime = currentFrame - lastFrame;
//        lastFrame = currentFrame;
//
//        camera.processInput(window,deltaTime);// Process Input linsenter
//        //cout << 1/deltaTime << endl;// Print fps
//        glfwPollEvents();
//        /* Clear Screen*/
//        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
//        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
//
//        viewMat = camera.GetViewMarix();
//
//        /* Draw most things as normal, we only care about the Outline things. The others should NOT fill the stencil buffer 
//        |so we set its mask to 0x00*/
//        glStencilMask(0x00);
//
//        for (int i = 0; i < 1; i++) {
//            //modelMat = glm::translate(glm::mat4(1.0f), cubePositions[i]);// Set Model matrix
//
//            #pragma region Lights
//            ModelShader->use();
//            glUniform3f(glGetUniformLocation(ModelShader->GetID(), "objColor"), 1.0f, 1.0f, 1.0f);
//            glUniform3f(glGetUniformLocation(ModelShader->GetID(), "ambienColor"), 0.1f, 0.1f, 0.1f);
//            
//            lightD.active(ModelShader);
//            lightP0.active(ModelShader);
//            lightP1.active(ModelShader);
//            lightP2.active(ModelShader);
//            lightP3.active(ModelShader);
//            lightS.active(ModelShader);
//            #pragma endregion
//
//            /* Camera position*/
//            ModelShader->setVec3("cameraPos", camera.Position);
//
//            { /* 环境贴图技术 反射(reflection)和折射(refraction)*/
//                glActiveTexture(GL_TEXTURE3);
//                glUniform1i(glGetUniformLocation(ModelShader->GetID(), "skybox"), 3);
//                glBindTexture(GL_TEXTURE_CUBE_MAP, skybox.GettextureID());
//            }
//
//            model.Draw(ModelShader, modelMat, viewMat, projMat);
//            //model.DrawOutlining(shaderSingleColor, modelMat, viewMat, projMat);// 未能解决描边（模板测试）与天空盒的冲突
//            // 混合策略还未实现
//            // 帧缓封装冲未能实现
//            skybox.Draw(skyboxShader, viewMat, projMat);
//        }
//
//        /* Clean up,prepare for next render loop*/
//        glfwSwapBuffers(window);// Update window
//    }
//
//    // Exit Program
//    glfwTerminate();// End
//
//    delete ModelShader;
//    delete skyboxShader;
//    delete shaderSingleColor;
//    return 0;
//}