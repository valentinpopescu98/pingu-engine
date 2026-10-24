#include "Engine.h"

GLint Engine::resX, Engine::resY;
float Engine::aspectRatio;

double Engine::previousTime = 0.0;
double Engine::elapsedTime = 0.0;
double Engine::deltaTime = 0.0;

int Engine::Init() 
{
	// Initialize GLFW
	if (!glfwInit())
	{
		return -1;
	}

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3); // GLFW version 3
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3); // GLFW version 3.3
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); // GLFW uses CORE profile
	return 0;
}

void Engine::End(GLFWwindow* window) 
{
	glfwDestroyWindow(window);
	glfwTerminate();
}

bool Engine::CheckWindowCreatedSuccessfully(GLFWwindow* window)
{
	if (window == NULL)
	{
		std::cout << "Failed to create GLFW window." << std::endl;
		glfwTerminate();
		return false;
	}

	return true;
}

bool Engine::LoadGlad()
{
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		return false;
	}

	return true;
}

GLFWwindow* Engine::CreateWindow(int resX, int resY, bool fullscreen) 
{
	GLFWmonitor* primaryMonitor = fullscreen ? glfwGetPrimaryMonitor() : NULL;
	GLFWwindow* window = glfwCreateWindow(resX, resY, "Pingu Engine", primaryMonitor, NULL); // Create window

	if (!CheckWindowCreatedSuccessfully(window)) return nullptr;
	glfwMakeContextCurrent(window); // Make window's context current

	if (!LoadGlad()) { glfwDestroyWindow(window); glfwTerminate(); return nullptr; }

	/* TODO: resX, resYand aspectRatio are computed after each frame
	*  If I remove next lines program will crash because it needs these variables for camera I think.
	*/
	// Set resolution variables for further use
	Engine::resX = resX;
	Engine::resY = resY;
	Engine::aspectRatio = (float)resX / resY; // Set aspect ratio variable for further use
	
	return window;
}

void Engine::SetTimeValues()
{
	elapsedTime = glfwGetTime();
	deltaTime = elapsedTime - previousTime;
	previousTime = elapsedTime;
}

void Engine::EnableVsync(bool isEnabled)
{
	glfwSwapInterval(isEnabled);
}

void Engine::CheckErrorCodes()
{
	GLenum errCode;

	if ((errCode = glGetError()) != GL_NO_ERROR)
	{
		std::cout << errCode << std::endl;
	}
}