//#define GLEW_STATIC
//#include<iostream>
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
//#include"Framebuffers.h"
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
//    Shader* shader = new Shader("test.vert", "test.frag");
//    Shader* screenShader = new Shader("framebuffers_screen.vert", "framebuffers_screen.frag");
//    #pragma endregion
//
//    #pragma region Init Models
//    float cubeVertices[] = {
//        // positions          // texture Coords
//        -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
//         0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
//         0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
//         0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
//        -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
//        -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
//
//        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
//         0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
//         0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
//         0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
//        -0.5f,  0.5f,  0.5f,  0.0f, 1.0f,
//        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
//
//        -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
//        -0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
//        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
//        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
//        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
//        -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
//
//         0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
//         0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
//         0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
//         0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
//         0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
//         0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
//
//        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
//         0.5f, -0.5f, -0.5f,  1.0f, 1.0f,
//         0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
//         0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
//        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
//        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
//
//        -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
//         0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
//         0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
//         0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
//        -0.5f,  0.5f,  0.5f,  0.0f, 0.0f,
//        -0.5f,  0.5f, -0.5f,  0.0f, 1.0f
//    };
//    float planeVertices[] = {
//        // positions          // texture Coords 
//         5.0f, -0.5f,  5.0f,  2.0f, 0.0f,
//        -5.0f, -0.5f,  5.0f,  0.0f, 0.0f,
//        -5.0f, -0.5f, -5.0f,  0.0f, 2.0f,
//
//         5.0f, -0.5f,  5.0f,  2.0f, 0.0f,
//        -5.0f, -0.5f, -5.0f,  0.0f, 2.0f,
//         5.0f, -0.5f, -5.0f,  2.0f, 2.0f
//    };
//    float quadVertices[] = { // vertex attributes for a quad that fills the entire screen in Normalized Device Coordinates.
//        // positions   // texCoords
//        -1.0f,  1.0f,  0.0f, 1.0f,
//        -1.0f, -1.0f,  0.0f, 0.0f,
//         1.0f, -1.0f,  1.0f, 0.0f,
//
//        -1.0f,  1.0f,  0.0f, 1.0f,
//         1.0f, -1.0f,  1.0f, 0.0f,
//         1.0f,  1.0f,  1.0f, 1.0f
//    };
//
//    unsigned int cubeVAO, cubeVBO;
//    glGenVertexArrays(1, &cubeVAO);
//    glGenBuffers(1, &cubeVBO);
//    glBindVertexArray(cubeVAO);
//    glBindBuffer(GL_ARRAY_BUFFER, cubeVBO);
//    glBufferData(GL_ARRAY_BUFFER, sizeof(cubeVertices), &cubeVertices, GL_STATIC_DRAW);
//    glEnableVertexAttribArray(0);
//    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
//    glEnableVertexAttribArray(2);
//    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
//    // plane VAO
//    unsigned int planeVAO, planeVBO;
//    glGenVertexArrays(1, &planeVAO);
//    glGenBuffers(1, &planeVBO);
//    glBindVertexArray(planeVAO);
//    glBindBuffer(GL_ARRAY_BUFFER, planeVBO);
//    glBufferData(GL_ARRAY_BUFFER, sizeof(planeVertices), &planeVertices, GL_STATIC_DRAW);
//    glEnableVertexAttribArray(0);
//    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
//    glEnableVertexAttribArray(2);
//    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
//    // screen quad VAO
//    unsigned int quadVAO, quadVBO;
//    glGenVertexArrays(1, &quadVAO);
//    glGenBuffers(1, &quadVBO);
//    glBindVertexArray(quadVAO);
//    glBindBuffer(GL_ARRAY_BUFFER, quadVBO);
//    glBufferData(GL_ARRAY_BUFFER, sizeof(quadVertices), &quadVertices, GL_STATIC_DRAW);
//    glEnableVertexAttribArray(0);
//    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)0);
//    glEnableVertexAttribArray(2);
//    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)(2 * sizeof(float)));
//
//    std::string exePath = argv[0];
//    unsigned int cubeTexture = LoadImageToGPU((exePath.substr(0, exePath.find_last_of('\\')) + "\\textures\\container.jpg").c_str());
//    unsigned int floorTexture = LoadImageToGPU((exePath.substr(0, exePath.find_last_of('\\')) + "\\textures\\metal.png").c_str());
//    #pragma endregion
//
//    shader->use();
//    shader->setInt("texture1", 0);
//
//    screenShader->use();
//    screenShader->setInt("screenTexture", 0);
//
//    //glBindFramebuffer(GL_FRAMEBUFFER, 0);
//    Framebuffer fbo(SCR_WIDTH, SCR_HEIGHT);
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
//#pragma endregion
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
//        // render
//        // ------
//        // bind to framebuffer and draw scene as we normally would to color texture 
//        fbo.bind();     
//
//        shader->use();
//        shader->setMat4("viewMat", viewMat);
//        shader->setMat4("projMat", projMat);
//
//        glBindVertexArray(cubeVAO);
//        glActiveTexture(GL_TEXTURE0);
//        glBindTexture(GL_TEXTURE_2D, cubeTexture);
//        modelMat = glm::translate(modelMat, glm::vec3(-1.0f, 0.0f, -1.0f));
//        shader->setMat4("modelMat", modelMat);
//        glDrawArrays(GL_TRIANGLES, 0, 36);
//        modelMat = glm::mat4(1.0f);
//        modelMat = glm::translate(modelMat, glm::vec3(2.0f, 0.0f, 0.0f));
//        shader->setMat4("modelMat", modelMat);
//        glDrawArrays(GL_TRIANGLES, 0, 36);
//
//        glBindVertexArray(planeVAO);
//        glBindTexture(GL_TEXTURE_2D, floorTexture);
//        shader->setMat4("modelMat", glm::mat4(1.0f));
//        glDrawArrays(GL_TRIANGLES, 0, 6);
//        glBindVertexArray(0);
//
//        // now bind back to default framebuffer and draw a quad plane with the attached framebuffer color texture
//        fbo.unbind();
//        glDisable(GL_DEPTH_TEST); // disable depth test so screen-space quad isn't discarded due to depth test.
//        // clear all relevant buffers
//        glClearColor(0.2f, 0.3f, 0.3f, 1.0f); // set clear color to white (not really necessary actually, since we won't be able to see behind the quad anyways)
//        glClear(GL_COLOR_BUFFER_BIT);
//
//        screenShader->use();
//        glBindVertexArray(quadVAO);
//        glBindTexture(GL_TEXTURE_2D, fbo.GetTexture());	// use the color attachment texture as the texture of the quad plane
//        glDrawArrays(GL_TRIANGLES, 0, 6);
//
//
//        /* Clean up,prepare for next render loop*/
//        glfwPollEvents();
//        glfwSwapBuffers(window);// Update window
//    }
//
//    glDeleteVertexArrays(1, &cubeVAO);
//    glDeleteVertexArrays(1, &planeVAO);
//    glDeleteVertexArrays(1, &quadVAO);
//    glDeleteBuffers(1, &cubeVBO);
//    glDeleteBuffers(1, &planeVBO);
//    glDeleteBuffers(1, &quadVBO);
//    //glDeleteFramebuffers(1, &framebuffer);
//
//    // Exit Program
//    glfwTerminate();// End
//
//    delete shader;
//    delete screenShader;
//    return 0;
//}