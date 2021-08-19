//#define GLEW_STATIC
//#include<iostream>
//#include<map>
//
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
//#include"AdvancedGLSL.h"
//
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
//
//#pragma endregion
//
//const unsigned int SCR_WIDTH = 800;
//const unsigned int SCR_HEIGHT = 600;
//
//int main(int argc, char* argv[]) {
//#pragma region Open a Window and configure
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
//    glEnable(GL_DEPTH_TEST);
//    glEnable(GL_BLEND);
//    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
//
//    /* this time rendered on a simple quad. If we render the scene in wireframe it's obvious
//    |we've only drawn a single quad in the default framebuffer.*/
//    //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
//
//
//    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);// Tell GLFW we want to call this function on every window resize by registering it
//    glfwSetCursorPosCallback(window, mouse_callback);// Set the required callback functions
//    glfwSetScrollCallback(window, scroll_callback);
//
//    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);// tell GLFW to capture our mouse
//#pragma endregion
//
//    #pragma region Init Shader Program
//    Shader shaderRed("ubo.vert", "ubo_red.frag");
//    Shader shaderGreen("ubo.vert", "ubo_green.frag");
//    Shader shaderBlue("ubo.vert", "ubo_blue.frag");
//    Shader shaderYellow("ubo.vert", "ubo_yellow.frag");
//    #pragma endregion
//
//    #pragma region Init Models
//    GLfloat cubeVertices[] = {
//            -0.5f, -0.5f, -0.5f,
//             0.5f,  0.5f, -0.5f,
//             0.5f, -0.5f, -0.5f,
//             0.5f,  0.5f, -0.5f,
//            -0.5f, -0.5f, -0.5f,
//            -0.5f,  0.5f, -0.5f,
//
//            -0.5f, -0.5f,  0.5f,
//             0.5f, -0.5f,  0.5f,
//             0.5f,  0.5f,  0.5f,
//             0.5f,  0.5f,  0.5f,
//            -0.5f,  0.5f,  0.5f,
//            -0.5f, -0.5f,  0.5f,
//
//            -0.5f,  0.5f,  0.5f,
//            -0.5f,  0.5f, -0.5f,
//            -0.5f, -0.5f, -0.5f,
//            -0.5f, -0.5f, -0.5f,
//            -0.5f, -0.5f,  0.5f,
//            -0.5f,  0.5f,  0.5f,
//
//             0.5f,  0.5f,  0.5f,
//             0.5f, -0.5f, -0.5f,
//             0.5f,  0.5f, -0.5f,
//             0.5f, -0.5f, -0.5f,
//             0.5f,  0.5f,  0.5f,
//             0.5f, -0.5f,  0.5f,
//
//            -0.5f, -0.5f, -0.5f,
//             0.5f, -0.5f, -0.5f,
//             0.5f, -0.5f,  0.5f,
//             0.5f, -0.5f,  0.5f,
//            -0.5f, -0.5f,  0.5f,
//            -0.5f, -0.5f, -0.5f,
//
//            -0.5f,  0.5f, -0.5f,
//             0.5f,  0.5f,  0.5f,
//             0.5f,  0.5f, -0.5f,
//             0.5f,  0.5f,  0.5f,
//            -0.5f,  0.5f, -0.5f,
//            -0.5f,  0.5f,  0.5f
//    };
//
//    // Setup cube VAO
//    GLuint cubeVAO, cubeVBO;
//    glGenVertexArrays(1, &cubeVAO);
//    glGenBuffers(1, &cubeVBO);
//    glBindVertexArray(cubeVAO);
//    glBindBuffer(GL_ARRAY_BUFFER, cubeVBO);
//    glBufferData(GL_ARRAY_BUFFER, sizeof(cubeVertices), &cubeVertices, GL_STATIC_DRAW);
//    glEnableVertexAttribArray(0);
//    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid*)0);
//    glBindVertexArray(0);
//    #pragma endregion
//
//    // Using uniform buffer
//    shaderRed.UniformBlockBinding("Matrices", 0);
//    shaderGreen.UniformBlockBinding("Matrices", 0);
//    shaderBlue.UniformBlockBinding("Matrices", 0);
//    shaderYellow.UniformBlockBinding("Matrices", 0);
//
//    GLuint uboMatrices = CreateUniformBufferObject(0, 2 * sizeof(glm::mat4), 0);
//
//    #pragma region Prepare MVP matrices
//    /* Calculate our transformation matrix here*/
//    glm::mat4 modelMat = glm::mat4(1.0f);
//    glm::mat4 viewMat;
//    glm::mat4 projMat = glm::perspective(glm::radians(45.0f), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);
//    /*
//    |Due to perspective the lines seem to coincide at a far enough distance.
//    |This is exactly the effect perspective projection tries to mimic and it does so using a perspective projection matrix.
//    |The projection matrix maps a given frustum range to clip space, but also manipulates the w value of each vertex coordinate
//    |in such a way that the further away a vertex coordinate is from the viewer, the higher this w component becomes.
//    |Its first parameter defines the fov value, that stands for field of view and sets how large the viewspace is.
//    |The second parameter sets the aspect ratio which is calculated by dividing the viewport's width by its height.
//    |The third and fourth parameter set the near and far plane of the frustum. Usually set 0.1 and 100.0.
//    */
//    #pragma endregion
//
//    // By Uniform buffer, we only need set variables once.
//    BufferSubData(uboMatrices, 0, sizeof(glm::mat4), projMat);
//
//    while (!glfwWindowShouldClose(window)) {
//        float currentFrame = glfwGetTime();
//        deltaTime = currentFrame - lastFrame;
//        lastFrame = currentFrame;
//        //cout << 1/deltaTime << endl;// Print fps
//
//        camera.processInput(window, deltaTime);// Process Input linsenter
//        viewMat = camera.GetViewMarix();
//
//        // Clear buffers
//        glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
//        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
//
//        /* Do your Tick here*/
//        glBindBuffer(GL_UNIFORM_BUFFER, uboMatrices);
//        glBufferSubData(GL_UNIFORM_BUFFER, sizeof(glm::mat4), sizeof(glm::mat4), glm::value_ptr(viewMat));
//        glBindBuffer(GL_UNIFORM_BUFFER, 0);
//
//        // Draw 4 cubes 
//        // RED
//        glBindVertexArray(cubeVAO);
//        shaderRed.use();
//        glm::mat4 model;
//        model = glm::translate(model, glm::vec3(-0.75f, 0.75f, 0.0f));	// Move top-left
//        glUniformMatrix4fv(glGetUniformLocation(shaderRed.GetID(), "model"), 1, GL_FALSE, glm::value_ptr(model));
//        glDrawArrays(GL_TRIANGLES, 0, 36);
//        // GREEN
//        shaderGreen.use();
//        model = glm::mat4();
//        model = glm::translate(model, glm::vec3(0.75f, 0.75f, 0.0f));		// Move top-right
//        glUniformMatrix4fv(glGetUniformLocation(shaderGreen.GetID(), "model"), 1, GL_FALSE, glm::value_ptr(model));
//        glDrawArrays(GL_TRIANGLES, 0, 36);
//        // BLUE
//        shaderBlue.use();
//        model = glm::mat4();
//        model = glm::translate(model, glm::vec3(-0.75f, -0.75f, 0.0f));	// Move bottom-left
//        glUniformMatrix4fv(glGetUniformLocation(shaderBlue.GetID(), "model"), 1, GL_FALSE, glm::value_ptr(model));
//        glDrawArrays(GL_TRIANGLES, 0, 36);
//        // YELLOW
//        shaderYellow.use();
//        model = glm::mat4();
//        model = glm::translate(model, glm::vec3(0.75f, -0.75f, 0.0f));	// Move bottom-right
//        glUniformMatrix4fv(glGetUniformLocation(shaderYellow.GetID(), "model"), 1, GL_FALSE, glm::value_ptr(model));
//        glDrawArrays(GL_TRIANGLES, 0, 36);
//        glBindVertexArray(0);
//
//
//        /* Clean up,prepare for next render loop*/
//        glfwPollEvents();
//        glfwSwapBuffers(window);// Update window
//    }
//
//    // Exit Program
//    glfwTerminate();// End
//    return 0;
//}