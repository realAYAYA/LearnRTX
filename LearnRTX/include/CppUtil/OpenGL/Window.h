#include<string>

#define GLEW_STATIC
#include<GL/glew.h>
#include<GLFW/glfw3.h>



using std::string;
namespace CppUtil {
	namespace OpenGL {
		const unsigned int DEFAULT_SCR_WIDTH = 800;
		const unsigned int DEFAULT_SCR_HEIGHT = 600;

		class Camera;
		class Window {
		public:
			Window(const unsigned int width, const unsigned int height, const char* _name, Camera* _camera);
			
			void MakeContextCurrent();

			// Window Settings
			void ProcessKeyboard(float deltaTime);
			void SetFramebufferSizeCallback(GLFWframebuffersizefun callback);// Tell GLFW we want to call this function on every window resize by registering it
			void SetInputMode(int mode, int value);
			void SetCursorPosCallback(GLFWcursorposfun callback);// Set the required callback functions
			void SetScrollCallback(GLFWscrollfun callback);
			void SetKeyCallback(GLFWkeyfun key_callback);

			GLFWwindow* GetGLFWwindow() { return this->window; }
			unsigned int GetWidth() { return this->src_width; }
			unsigned int GetHeight() { return this->src_height; }
		private:
			void Load();

			bool IsValid;
			string name;
			unsigned int src_width;
			unsigned int src_height;

			Camera* camera;
			GLFWwindow* window;
			/*GLFWwindow* share;
			GLFWmonitor* monitor;*/
		};
	}
}