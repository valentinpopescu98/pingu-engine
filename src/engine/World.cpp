#include "World.h"

void World::Init(GLFWwindow* window)
{
	//ScriptingSystem::CallFunctionByName("src/scripts/hello.lua", "Init");

	// Set origin
	origin.position = glm::vec3(0.0f, 0.0f, 0.0f);
	origin.rotation = glm::vec3(0.0f, 0.0f, 0.0f);
	origin.scale = glm::vec3(1.0f, 1.0f, 1.0f);

	// Supports: texture_diffuse, texture_specular, texture_normal, texture_height
	std::vector<TextureStruct> defaultTexture
	{
		{ "texture_diffuse", "resources/textures/default.png" }
	};

	std::vector<TextureStruct> noiseTexture
	{
		{ "texture_diffuse", "resources/textures/noise.png" }
	};

	// Create shaders
	lightShader.Create("src/shaders/light.vert", "src/shaders/light.frag");
	objectShader.Create("src/shaders/object.vert", "src/shaders/object.frag");

	// Initialize camera
	camera.Init(Engine::resX, Engine::resY, glm::vec3(0.0f, 0.0f, 0.0f), 70.0f, 0.1f, 20.0f);

	// Initialize 1000 particles
	particleSystem.Init(1000);

	// Create meshes
	meshObjects.push_back(Mesh());
	meshObjects[0].CreateBuffers(Utils::cubeVertices, Utils::cubeIndices, defaultTexture,
		origin, glm::vec3(0.0f, 0.0f, -2.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec3(0.0f, 1.0f, 0.0f));
	meshObjects.push_back(Mesh());
	meshObjects[1].CreateBuffers(Utils::pyramidVertices, Utils::pyramidIndices, noiseTexture,
		meshObjects[0], glm::vec3(2.0f, 0.0f, -2.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec3(0.0f, 1.0f, 1.0f));

	// Create mesh textures
	meshObjects[0].CreateTextures(objectShader.id, 0, GL_TEXTURE_2D, GL_LINEAR, GL_REPEAT);
	meshObjects[1].CreateTextures(objectShader.id, meshObjects[0].textures.size(), GL_TEXTURE_2D, GL_LINEAR, GL_REPEAT);

	// Create models
	parser.Init("src/xml/scene.xml", meshObjects[0].textures.size() + meshObjects[1].textures.size()); // Parse XML
	parser.CreateModels(parser.scene, modelLights, modelObjects); // Initialize models from the XML

	// Initialize GUI
	GuiDrawer::Init(window);

	// Enable backface culling
	Culler::BackFaceCulling();
}

void World::End()
{
	GuiDrawer::End();
	//particleSystem.End();

	for (Mesh& meshObject : meshObjects)
	{
		meshObject.DeleteBuffers(); // Delete buffers
		meshObject.DeleteTextures(); // Delete textures
	}

	for (Model& modelLight : modelLights)
	{
		modelLight.DeleteBuffers(); // Delete buffers
		modelLight.DeleteTextures(); // Delete textures
	}
	for (Model& modelObject : modelObjects)
	{
		modelObject.DeleteBuffers(); // Delete buffers
		modelObject.DeleteTextures(); // Delete textures
	}

	// Delete shaders
	lightShader.Delete();
	objectShader.Delete();
}

void World::BeforeUpdate(GLFWwindow* window)
{
	glfwPollEvents(); // Take care of GLFW events
	glClearColor(0.05f, 0.1f, 0.2f, 1.0f); // Wipe drawing from previous frame with a black color
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // Clear color buffer and depth buffer

	// Treat camera inputs (WASD - move on X/Z axis, LEFT CTRL/SPACE - move on Y axis, SHIFT - speed modifier)
	camera.TreatInputs(window, Engine::deltaTime);
}

void World::Update(GLFWwindow* window)
{
	//ScriptingSystem::CallFunctionByName("src/scripts/hello.lua", "Update");

	/* DEMO COLLISIONS:
	*  Code block to be removed from the framework after demo.
	*  Add WASD to control the cube and make it not clip through the pyramid
	*/
	if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS)
	{
		meshObjects[0].position += 5.0f * camera.forward * (float)Engine::deltaTime;
	}
	else if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS)
	{
		meshObjects[0].position += 5.0f * -camera.forward * (float)Engine::deltaTime;
	}
	if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS)
	{
		meshObjects[0].position += 5.0f * -camera.right * (float)Engine::deltaTime;
	}
	else if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS)
	{
		meshObjects[0].position += 5.0f * camera.right * (float)Engine::deltaTime;
	}
	if (glfwGetKey(window, GLFW_KEY_LEFT_CONTROL) == GLFW_PRESS)
	{
		meshObjects[0].position += 5.0f * -camera.up * (float)Engine::deltaTime;
	}
	else if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS)
	{
		meshObjects[0].position += 5.0f * camera.up * (float)Engine::deltaTime;
	}

	//if (glfwGetKey(window, GLFW_KEY_R) == GLFW_PRESS)
	//{
	//	ReloadModels(); // LAGGY AF
	//}

	// Create particles when pressing P
	if (glfwGetKey(window, GLFW_KEY_P) == GLFW_PRESS)
	{
		for (int i = 0; i < 5; i++)
		{
			particleSystem.CreateParticle(GuiDrawer::particlePosition, GuiDrawer::particleColorBirth, GuiDrawer::particleColorDeath,
				GuiDrawer::particleSpeed, GuiDrawer::particleScaleBirth, GuiDrawer::particleScaleDeath, GuiDrawer::particleLifeTime);
		}
	}
	particleSystem.UpdateParticleData(Engine::deltaTime); // Update particle data

	camera.UpdateMatrices(view, projection); // Compute view and projection matrices

	// RENDER LIGHT SOURCES SECTION
	lightShader.Use(); // Use light source's shaders
	lightShader.InitMatrices(view, projection); // Send view and projection matrix to light source's shaders

	// Draw all lights of type MODEL from the XML
	for (Model modelLight : modelLights)
	{
			modelLight.Draw(lightShader.id);
		/*if (Culler::ModelInFrustum(camera, modelLight))
		{
		}*/
	}

	// RENDER NORMAL OBJECTS SECTION
	objectShader.Use(); // Use object's shader
	// Send material data to object's shaders
	objectShader.InitMaterial(modelLights[0].position, modelLights[0].color, camera.position,
		glm::vec3(0.2f, 0.2f, 0.2f), glm::vec3(1.0f, 0.5f, 0.31f), glm::vec3(0.5f, 0.5f, 0.5f), 32.0f);
	objectShader.InitMatrices(view, projection); // Send view and projection matrix to object's shaders

	// Draw all objects of type MESH from the local buffers
	for (Mesh meshObject : meshObjects)
	{
			meshObject.Draw(objectShader.id);
		/*if (Culler::MeshInFrustum(camera, meshObject))
		{
		}*/
	}

	// Draw all objects of type MODEL from the XML
	for (Model modelObject : modelObjects)
	{
			modelObject.Draw(objectShader.id);
		/*if (Culler::ModelInFrustum(camera, modelObject))
		{
		}*/
	}

	// Draw all objects of type MESH from the local buffers created in the particle system
	particleSystem.DrawParticle(objectShader.id, origin);

	// Draw GUI
	GuiDrawer::Draw();
}

void World::AfterUpdate(GLFWwindow* window)
{
	// Set resolution variables
	glfwGetFramebufferSize(window, &Engine::resX, &Engine::resY); // Get window sizes
	glViewport(0, 0, Engine::resX, Engine::resY); // Set viewport between bottom left and top right corner of the window
	Engine::aspectRatio = (float)Engine::resX / Engine::resY; // Set aspect ratio

	glfwSwapBuffers(window); // Swap front and back buffer
	glFlush(); // Empties buffers - improves performance
}

void World::Run(GLFWwindow* window)
{
	glEnable(GL_DEPTH_TEST); // Enable depth

	// Loop until window is closed
	while (!glfwWindowShouldClose(window))
	{
		BeforeUpdate(window);
		Update(window);
		AfterUpdate(window);

		CollisionManager::Uncollide(meshObjects, modelObjects);
		Engine::SetTimeValues(); // Compute deltaTime
		Engine::CheckErrorCodes(); // Check for GLAD error codes
	}
}

void World::ReloadModels()
{
	parser.Init("src/xml/scene.xml", meshObjects[0].textures.size() + meshObjects[1].textures.size()); // Parse XML
	parser.CreateModels(parser.scene, modelLights, modelObjects); // Initialize models from the XML
}