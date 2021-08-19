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
//    #pragma endregion
//
//    #pragma region Init Shader Program
//    Shader shader("gs.vert", "gs.frag", "gs.geom");
//    #pragma endregion
//
//    #pragma region Init Models
//    // set up vertex data (and buffer(s)) and configure vertex attributes
//    // ------------------------------------------------------------------
//    float points[] = {
//        -0.5f,  0.5f, 1.0f, 0.0f, 0.0f, // top-left
//         0.5f,  0.5f, 0.0f, 1.0f, 0.0f, // top-right
//         0.5f, -0.5f, 0.0f, 0.0f, 1.0f, // bottom-right
//        -0.5f, -0.5f, 1.0f, 1.0f, 0.0f  // bottom-left
//    };
//    unsigned int VBO, VAO;
//    glGenBuffers(1, &VBO);
//    glGenVertexArrays(1, &VAO);
//    glBindVertexArray(VAO);
//    glBindBuffer(GL_ARRAY_BUFFER, VBO);
//    glBufferData(GL_ARRAY_BUFFER, sizeof(points), &points, GL_STATIC_DRAW);
//    glEnableVertexAttribArray(0);
//    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), 0);
//    glEnableVertexAttribArray(1);
//    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(2 * sizeof(float)));
//    glBindVertexArray(0);
//    #pragma endregion
//
//    #pragma region Prepare MVP matrices
//    /* Calculate our transformation matrix here*/
//    glm::mat4 modelMat = glm::mat4(1.0f);
//    glm::mat4 viewMat;
//    glm::mat4 projMat = glm::perspective(glm::radians(45.0f), 800.0f / 600.0f, 0.1f, 100.0f);
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
//        // draw points
//        shader.use();
//        glBindVertexArray(VAO);
//        glDrawArrays(GL_POINTS, 0, 4);
//
//        /* Clean up,prepare for next render loop*/
//        glfwPollEvents();
//        glfwSwapBuffers(window);// Update window
//    }
//    glDeleteVertexArrays(1, &VAO);
//    glDeleteBuffers(1, &VBO);
//    // Exit Program
//    glfwTerminate();// End
//    return 0;
//}