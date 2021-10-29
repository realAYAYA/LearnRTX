#include"CommonDefine.h"

#include<CppUtil/Basic/HeapObj.h>
#include<CppUtil/Basic/Math.h>
#include<CppUtil/OpenGL/Model.h>
#include<CppUtil/OpenGL/Transform.h>
using namespace CppUtil::Basic;

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <vector>
using std::vector;

unsigned int cubeVAO = 0;
unsigned int quadVAO = 0;
unsigned int VAO_Screen = 0;

//CppUtil::OpenGL::SceneRA* CreateScene_CornellBox()
//{
//	// Mesh
//	/*vector<RTX::Vertex> squareVertexs;
//	for (size_t i = 0; i < sizeof(squareData) / sizeof(float); i += 6) {
//		vec3 pos(squareData[i], squareData[i + 1], squareData[i + 2]);
//		vec3 normal(squareData[i + 3], squareData[i + 4], squareData[i + 5]);
//		squareVertexs.push_back(RTX::Vertex(pos, normal));
//	}
//
//	vector<RTX::Vertex> cubeVertexs;
//	for (size_t i = 0; i < sizeof(cubeData_PN) / sizeof(float); i += 6) {
//		vec3 pos(cubeData_PN[i], cubeData_PN[i + 1], cubeData_PN[i + 2]);
//		vec3 normal(cubeData_PN[i + 3], cubeData_PN[i + 4], cubeData_PN[i + 5]);
//		cubeVertexs.push_back(RTX::Vertex(pos, normal));
//	}*/
//    SimpleMesh* Cube= new SimpleMesh(cubeData_PT, sizeof(cubeData_PT) / sizeof(float), SimpleMesh::ENUM_FORMAT_PT);
//    SimpleMesh* Wall= new SimpleMesh(squareData, sizeof(squareData) / sizeof(float), SimpleMesh::ENUM_FORMAT_PN);
//
//    // Transform
//    glm::mat4 tfmRight(1.0f);
//    tfmRight = glm::translate(tfmRight, glm::vec3(3, 0, 0));
//    tfmRight = glm::scale(tfmRight, glm::vec3(6));
//    tfmRight = glm::rotate(tfmRight, -CppUtil::Basic::Math::PI / 2, glm::vec3(0, 1, 0));
//    glm::mat4 tfmLeft(1.0f);
//    tfmLeft = translate(tfmLeft, glm::vec3(-3, 0, 0));
//    tfmLeft = glm::scale(tfmLeft, glm::vec3(6));
//    tfmLeft = glm::rotate(tfmLeft, CppUtil::Basic::Math::PI / 2, glm::vec3(0, 1, 0));
//    glm::mat4 tfmBottom(1.0f);
//    tfmBottom = glm::translate(tfmBottom, glm::vec3(0, -3, 0));
//    tfmBottom = glm::scale(tfmBottom, glm::vec3(6));
//    tfmBottom = glm::rotate(tfmBottom, -CppUtil::Basic::Math::PI / 2, glm::vec3(1, 0, 0));
//    glm::mat4 tfmTop(1.0f);
//    tfmTop = glm::translate(tfmTop, glm::vec3(0, 3, 0));
//    tfmTop = glm::scale(tfmTop, glm::vec3(6));
//    tfmTop = glm::rotate(tfmTop, CppUtil::Basic::Math::PI / 2, glm::vec3(1, 0, 0));
//    glm::mat4 tfmBack(1.0f);
//    tfmBack = glm::translate(tfmBack, glm::vec3(0, 0, -3));
//    tfmBack = glm::scale(tfmBack, glm::vec3(6));
//
//    glm::mat4 tfmCube1(1.0f);
//    tfmCube1 = glm::translate(tfmCube1, glm::vec3(1.1, -2.2, 1));
//    tfmCube1 = glm::scale(tfmCube1, glm::vec3(1.6));
//    tfmCube1 = glm::rotate(tfmCube1, -CppUtil::Basic::Math::PI / 12, glm::vec3(0, 1, 0));
//    glm::mat4 tfmCube2(1.0f);
//    tfmCube2 = glm::translate(tfmCube2, glm::vec3(-1.1, -1.5, -0.5));
//    tfmCube2 = glm::scale(tfmCube2, glm::vec3(1.6, 3, 1.6));
//    tfmCube2 = glm::rotate(tfmCube2, CppUtil::Basic::Math::PI / 9, glm::vec3(0, 1, 0));
//
//    CppUtil::OpenGL::Transform* RightWall = new CppUtil::OpenGL::Transform(Wall, tfmRight);
//    CppUtil::OpenGL::Transform* LeftWall = new CppUtil::OpenGL::Transform(Wall, tfmLeft);
//    CppUtil::OpenGL::Transform* BottomWall = new CppUtil::OpenGL::Transform(Wall, tfmBottom);
//    CppUtil::OpenGL::Transform* TopWall = new CppUtil::OpenGL::Transform(Wall, tfmTop);
//    CppUtil::OpenGL::Transform* BackWall = new CppUtil::OpenGL::Transform(Wall, tfmBack);
//    CppUtil::OpenGL::Transform* Cube1 = new CppUtil::OpenGL::Transform(Cube, tfmCube1);
//    CppUtil::OpenGL::Transform* Cube2 = new CppUtil::OpenGL::Transform(Cube, tfmCube2);
//
//    CppUtil::OpenGL::SceneRA* scene=new CppUtil::OpenGL::SceneRA();
//    scene->Push(RightWall);
//    scene->Push(LeftWall);
//    scene->Push(BottomWall);
//    scene->Push(TopWall);
//    scene->Push(BackWall);
//    scene->Push(Cube1);
//    scene->Push(Cube2);
//
//    return scene;
//}

void renderScreen()
{
	if (VAO_Screen == 0)
	{
		float quadVertices[] = {
			// positions        // texture Coords
			-1.0f,  1.0f, 0.0f, 0.0f, 1.0f,
			-1.0f, -1.0f, 0.0f, 0.0f, 0.0f,
			 1.0f,  1.0f, 0.0f, 1.0f, 1.0f,
			 1.0f, -1.0f, 0.0f, 1.0f, 0.0f,
		};
		// setup plane VAO
		GLuint VBO;
		glGenVertexArrays(1, &quadVAO);
		glGenBuffers(1, &VBO);
		glBindVertexArray(quadVAO);
		glBindBuffer(GL_ARRAY_BUFFER, VBO);
		glBufferData(GL_ARRAY_BUFFER, sizeof(quadVertices), &quadVertices, GL_STATIC_DRAW);
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
		glEnableVertexAttribArray(1);
		glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
	}
	glBindVertexArray(quadVAO);
	glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
	glBindVertexArray(0);
}

void renderCube()
{
    // initialize (if necessary)
    if (cubeVAO == 0)
    {
        float vertices[] = {
            // back face
            -1.0f, -1.0f, -1.0f,  0.0f,  0.0f, -1.0f, 0.0f, 0.0f, // bottom-left
             1.0f,  1.0f, -1.0f,  0.0f,  0.0f, -1.0f, 1.0f, 1.0f, // top-right
             1.0f, -1.0f, -1.0f,  0.0f,  0.0f, -1.0f, 1.0f, 0.0f, // bottom-right         
             1.0f,  1.0f, -1.0f,  0.0f,  0.0f, -1.0f, 1.0f, 1.0f, // top-right
            -1.0f, -1.0f, -1.0f,  0.0f,  0.0f, -1.0f, 0.0f, 0.0f, // bottom-left
            -1.0f,  1.0f, -1.0f,  0.0f,  0.0f, -1.0f, 0.0f, 1.0f, // top-left
            // front face
            -1.0f, -1.0f,  1.0f,  0.0f,  0.0f,  1.0f, 0.0f, 0.0f, // bottom-left
             1.0f, -1.0f,  1.0f,  0.0f,  0.0f,  1.0f, 1.0f, 0.0f, // bottom-right
             1.0f,  1.0f,  1.0f,  0.0f,  0.0f,  1.0f, 1.0f, 1.0f, // top-right
             1.0f,  1.0f,  1.0f,  0.0f,  0.0f,  1.0f, 1.0f, 1.0f, // top-right
            -1.0f,  1.0f,  1.0f,  0.0f,  0.0f,  1.0f, 0.0f, 1.0f, // top-left
            -1.0f, -1.0f,  1.0f,  0.0f,  0.0f,  1.0f, 0.0f, 0.0f, // bottom-left
            // left face
            -1.0f,  1.0f,  1.0f, -1.0f,  0.0f,  0.0f, 1.0f, 0.0f, // top-right
            -1.0f,  1.0f, -1.0f, -1.0f,  0.0f,  0.0f, 1.0f, 1.0f, // top-left
            -1.0f, -1.0f, -1.0f, -1.0f,  0.0f,  0.0f, 0.0f, 1.0f, // bottom-left
            -1.0f, -1.0f, -1.0f, -1.0f,  0.0f,  0.0f, 0.0f, 1.0f, // bottom-left
            -1.0f, -1.0f,  1.0f, -1.0f,  0.0f,  0.0f, 0.0f, 0.0f, // bottom-right
            -1.0f,  1.0f,  1.0f, -1.0f,  0.0f,  0.0f, 1.0f, 0.0f, // top-right
            // right face
             1.0f,  1.0f,  1.0f,  1.0f,  0.0f,  0.0f, 1.0f, 0.0f, // top-left
             1.0f, -1.0f, -1.0f,  1.0f,  0.0f,  0.0f, 0.0f, 1.0f, // bottom-right
             1.0f,  1.0f, -1.0f,  1.0f,  0.0f,  0.0f, 1.0f, 1.0f, // top-right         
             1.0f, -1.0f, -1.0f,  1.0f,  0.0f,  0.0f, 0.0f, 1.0f, // bottom-right
             1.0f,  1.0f,  1.0f,  1.0f,  0.0f,  0.0f, 1.0f, 0.0f, // top-left
             1.0f, -1.0f,  1.0f,  1.0f,  0.0f,  0.0f, 0.0f, 0.0f, // bottom-left     
            // bottom face
            -1.0f, -1.0f, -1.0f,  0.0f, -1.0f,  0.0f, 0.0f, 1.0f, // top-right
             1.0f, -1.0f, -1.0f,  0.0f, -1.0f,  0.0f, 1.0f, 1.0f, // top-left
             1.0f, -1.0f,  1.0f,  0.0f, -1.0f,  0.0f, 1.0f, 0.0f, // bottom-left
             1.0f, -1.0f,  1.0f,  0.0f, -1.0f,  0.0f, 1.0f, 0.0f, // bottom-left
            -1.0f, -1.0f,  1.0f,  0.0f, -1.0f,  0.0f, 0.0f, 0.0f, // bottom-right
            -1.0f, -1.0f, -1.0f,  0.0f, -1.0f,  0.0f, 0.0f, 1.0f, // top-right
            // top face
            -1.0f,  1.0f, -1.0f,  0.0f,  1.0f,  0.0f, 0.0f, 1.0f, // top-left
             1.0f,  1.0f , 1.0f,  0.0f,  1.0f,  0.0f, 1.0f, 0.0f, // bottom-right
             1.0f,  1.0f, -1.0f,  0.0f,  1.0f,  0.0f, 1.0f, 1.0f, // top-right     
             1.0f,  1.0f,  1.0f,  0.0f,  1.0f,  0.0f, 1.0f, 0.0f, // bottom-right
            -1.0f,  1.0f, -1.0f,  0.0f,  1.0f,  0.0f, 0.0f, 1.0f, // top-left
            -1.0f,  1.0f,  1.0f,  0.0f,  1.0f,  0.0f, 0.0f, 0.0f  // bottom-left        
        };
        GLuint VBO;
        glGenVertexArrays(1, &cubeVAO);
        glGenBuffers(1, &VBO);
        // fill buffer
        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
        // link vertex attributes
        glBindVertexArray(cubeVAO);
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
        glEnableVertexAttribArray(1);
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
        glEnableVertexAttribArray(2);
        glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glBindVertexArray(0);
    }
    // render Cube
    glBindVertexArray(cubeVAO);
    glDrawArrays(GL_TRIANGLES, 0, 36);
    glBindVertexArray(0);
}