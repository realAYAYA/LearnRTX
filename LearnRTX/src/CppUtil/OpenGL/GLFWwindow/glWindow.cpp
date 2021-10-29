#include<CppUtil/OpenGL/Window.h>
#include<CppUtil/OpenGL/Camera.h>

CppUtil::OpenGL::Window::Window(const unsigned int width, const unsigned int height, const char* _name, Camera* _camera)
{
	src_width = width;
	src_height = height;

    if (_name != nullptr) {
        this->name = _name;
    }else{
        this->name = "Hello OpenGL";
    }
    this->IsValid = true;
    this->camera = _camera;

    this->Load();
}

void CppUtil::OpenGL::Window::Load()
{
    if (this->IsValid) {
        glfwInit();
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
        //glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);// Open it in MAC OS X

        // Open GLFW Window
        this->window = glfwCreateWindow(this->src_width, this->src_height, this->name.c_str(), NULL, NULL);
        if (this->window == NULL) {
            this->IsValid = false;
            glfwTerminate();
            return;
        }
    }    
}

void CppUtil::OpenGL::Window::MakeContextCurrent()
{
    if (this->IsValid) {
        glfwMakeContextCurrent(window);

        //Init GLEW
        glewExperimental = true;
        if (glewInit() != GLEW_OK) {
            printf("Init GLEW failed.\n");
            return;
        }

        glViewport(0, 0, this->src_width, src_height);
    }
}

void CppUtil::OpenGL::Window::SetInputMode(int mode, int value)
{
    if (this->IsValid) {
        glfwSetInputMode(this->window, mode, value);// tell GLFW to capture our mouse
    }
}

void CppUtil::OpenGL::Window::ProcessKeyboard(float deltaTime)
{
    if (!this->camera && !this->IsValid) {
        return;
    }
    if (glfwGetKey(this->window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
        glfwSetWindowShouldClose(window, true);
    }
    if (glfwGetKey(this->window, GLFW_KEY_W) == GLFW_PRESS) {
        this->camera->ProcessKeyboard(Camera::MOVE_FORWARD, deltaTime);
    }
    if (glfwGetKey(this->window, GLFW_KEY_S)) {
        this->camera->ProcessKeyboard(Camera::MOVE_BACKWARD, deltaTime);
    }
    if (glfwGetKey(this->window, GLFW_KEY_A) == GLFW_PRESS) {
        this->camera->ProcessKeyboard(Camera::MOVE_LEFT, deltaTime);
    }
    if (glfwGetKey(this->window, GLFW_KEY_D)) {
        this->camera->ProcessKeyboard(Camera::MOVE_RIGHT, deltaTime);
    }
    if (glfwGetKey(this->window, GLFW_KEY_SPACE) == GLFW_PRESS) {
        this->camera->ProcessKeyboard(Camera::MOVE_UP, deltaTime);
    }
    if (glfwGetKey(this->window, GLFW_KEY_X)) {
        this->camera->ProcessKeyboard(Camera::MOVE_DOWN, deltaTime);
    }
}

void CppUtil::OpenGL::Window::SetFramebufferSizeCallback(GLFWframebuffersizefun callback)
{
    if (this->IsValid) {
        glfwSetFramebufferSizeCallback(this->window, callback);
    }
}

void CppUtil::OpenGL::Window::SetCursorPosCallback(GLFWcursorposfun callback)
{
    if (this->IsValid) {
        glfwSetCursorPosCallback(this->window, callback);
    }
}

void CppUtil::OpenGL::Window::SetScrollCallback(GLFWscrollfun callback)
{
    if (this->IsValid) {
        glfwSetScrollCallback(this->window, callback);
    }
}

void CppUtil::OpenGL::Window::SetKeyCallback(GLFWkeyfun key_callback)
{
    if (this->IsValid) {
        glfwSetKeyCallback(this->window, key_callback);
    }
}
