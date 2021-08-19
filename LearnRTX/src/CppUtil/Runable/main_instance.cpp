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
//    Shader asteroidShader("instance.vert", "instance.frag");
//    Shader planetShader("test.vert", "test.frag");
//    #pragma endregion
//
//    #pragma region Init Models
//    std::string exePath = argv[0];
//    Model rock(exePath.substr(0, exePath.find_last_of('\\')) + "\\model\\space\\rock.obj");
//    Model planet(exePath.substr(0, exePath.find_last_of('\\')) + "\\model\\space\\planet.obj");
//    #pragma endregion
//
//    #pragma region Prepare MVP matrices
//    /* Calculate our transformation matrix here*/
//    glm::mat4 modelMat = glm::mat4(1.0f);
//    glm::mat4 viewMat;// Tick
//    glm::mat4 projMat = glm::perspective(glm::radians(45.0f), (GLfloat)SCR_WIDTH / (GLfloat)SCR_HEIGHT, 0.1f, 100.0f);
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
//    // generate a large list of semi-random model transformation matrices
//    // ------------------------------------------------------------------
//    unsigned int amount = 100000;
//    glm::mat4* modelMatrices;
//    modelMatrices = new glm::mat4[amount];
//    srand(glfwGetTime()); // initialize random seed	
//    float radius = 75.0;
//    float offset = 25.0f;
//    for (unsigned int i = 0; i < amount; i++)
//    {
//        glm::mat4 model = glm::mat4(1.0f);
//        // 1. translation: displace along circle with 'radius' in range [-offset, offset]
//        float angle = (float)i / (float)amount * 360.0f;
//        float displacement = (rand() % (int)(2 * offset * 100)) / 100.0f - offset;
//        float x = sin(angle) * radius + displacement;
//        displacement = (rand() % (int)(2 * offset * 100)) / 100.0f - offset;
//        float y = displacement * 0.4f; // keep height of asteroid field smaller compared to width of x and z
//        displacement = (rand() % (int)(2 * offset * 100)) / 100.0f - offset;
//        float z = cos(angle) * radius + displacement;
//        model = glm::translate(model, glm::vec3(x, y, z));
//
//        // 2. scale: Scale between 0.05 and 0.25f
//        float scale = (rand() % 20) / 100.0f + 0.05;
//        model = glm::scale(model, glm::vec3(scale));
//
//        // 3. rotation: add random rotation around a (semi)randomly picked rotation axis vector
//        float rotAngle = (rand() % 360);
//        model = glm::rotate(model, rotAngle, glm::vec3(0.4f, 0.6f, 0.8f));
//
//        // 4. now add to list of matrices
//        modelMatrices[i] = model;
//    }
//
//    // configure instanced array
//    // -------------------------
//    unsigned int buffer;
//    glGenBuffers(1, &buffer);
//    glBindBuffer(GL_ARRAY_BUFFER, buffer);
//    glBufferData(GL_ARRAY_BUFFER, amount * sizeof(glm::mat4), &modelMatrices[0], GL_STATIC_DRAW);
//
//    // set transformation matrices as an instance vertex attribute (with divisor 1)
//    // note: we're cheating a little by taking the, now publicly declared, VAO of the model's mesh(es) and adding new vertexAttribPointers
//    // normally you'd want to do this in a more organized fashion, but for learning purposes this will do.
//    // -----------------------------------------------------------------------------------------------------------------------------------
//    for (unsigned int i = 0; i < rock.meshes.size(); i++)
//    {
//        unsigned int VAO = rock.meshes[i].GetVAO();
//        glBindVertexArray(VAO);
//        // set attribute pointers for matrix (4 times vec4)
//        glEnableVertexAttribArray(3);
//        glVertexAttribPointer(3, 4, GL_FLOAT, GL_FALSE, sizeof(glm::mat4), (void*)0);
//        glEnableVertexAttribArray(4);
//        glVertexAttribPointer(4, 4, GL_FLOAT, GL_FALSE, sizeof(glm::mat4), (void*)(sizeof(glm::vec4)));
//        glEnableVertexAttribArray(5);
//        glVertexAttribPointer(5, 4, GL_FLOAT, GL_FALSE, sizeof(glm::mat4), (void*)(2 * sizeof(glm::vec4)));
//        glEnableVertexAttribArray(6);
//        glVertexAttribPointer(6, 4, GL_FLOAT, GL_FALSE, sizeof(glm::mat4), (void*)(3 * sizeof(glm::vec4)));
//
//        glVertexAttribDivisor(3, 1);
//        glVertexAttribDivisor(4, 1);
//        glVertexAttribDivisor(5, 1);
//        glVertexAttribDivisor(6, 1);
//
//        glBindVertexArray(0);
//    }
//
//    while (!glfwWindowShouldClose(window)) {
//        float currentFrame = glfwGetTime();
//        deltaTime = currentFrame - lastFrame;
//        lastFrame = currentFrame;
//        cout << 1/deltaTime << endl;// Print fps
//
//        camera.processInput(window, deltaTime);// Process Input linsenter
//        viewMat = camera.GetViewMarix();
//
//        // Clear buffers
//        glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
//        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
//
//        /* Do your Tick here*/
//        // configure transformation matrices
//        asteroidShader.use();
//        asteroidShader.setMat4("projMat", projMat);
//        asteroidShader.setMat4("viewMat", viewMat);
//
//        // draw planet
//        modelMat = glm::mat4(1.0f);
//        modelMat = glm::translate(modelMat, glm::vec3(0.0f, -3.0f, 0.0f));
//        modelMat = glm::scale(modelMat, glm::vec3(4.0f, 4.0f, 4.0f));
//        planet.Draw(&planetShader,modelMat,viewMat,projMat);
//
//        // draw meteorites
//        asteroidShader.use();
//        asteroidShader.setInt("texture_diffuse1", 0);
//        glBindTexture(GL_TEXTURE_2D, rock.textures_loaded[0].id); // note: we also made the textures_loaded vector public (instead of private) from the model class.
//        for (unsigned int i = 0; i < rock.meshes.size(); i++)
//        {
//            glBindVertexArray(rock.meshes[i].GetVAO());
//            glDrawElementsInstanced(GL_TRIANGLES, rock.meshes[i].indices.size(), GL_UNSIGNED_INT, 0, amount);
//            glBindVertexArray(0);
//        }
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