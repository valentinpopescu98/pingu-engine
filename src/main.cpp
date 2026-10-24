#include <iostream>
#include <string>
#include "engine/Engine.h"
#include "engine/World.h"

int main(int argc, char** argv)
{
	// CI smoke test: exercise GLFW, context creation and GLAD without entering the game loop.
	if (argc == 2 && std::string(argv[1]) == "--smoke-test")
	{
		if (Engine::Init() != 0) return 1;
		GLFWwindow* testWindow = Engine::CreateWindow(320, 240, false);
		if (!testWindow) return 2;
		const GLubyte* version = glGetString(GL_VERSION);
		if (!version) { Engine::End(testWindow); return 3; }
		std::cout << "OpenGL initialized: " << version << std::endl;
		Engine::End(testWindow);
		return 0;
	}

	if (Engine::Init() != 0) return 1; // Initialize GLFW
	// Create window of given resolution and choose if using fullscreen
	GLFWwindow* window = Engine::CreateWindow(800, 600, false);
	if (!window) return 2;
	Engine::EnableVsync(true); // Enable vertical synchronization

	World world; // Create world object
	world.Init(window); // Create prerequisites
	world.Run(window); // Run main loop
	world.End(); // Terminate prerequisites

	Engine::End(window); // Destroy window and terminate GLFW
	return 0;
}