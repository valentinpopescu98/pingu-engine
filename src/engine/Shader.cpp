#include "Shader.h"

void Shader::Create(const char* vertexShaderPath, const char* fragmentShaderPath)
{
	this->vertexShaderPath = vertexShaderPath;
	this->fragmentShaderPath = fragmentShaderPath;

	std::string vertexCode = Utils::GetFileContents(vertexShaderPath); // Store VS source code in a string
	std::string fragmentCode = Utils::GetFileContents(fragmentShaderPath); // Store FS source code in a string

	const char* vertexSource = vertexCode.c_str(); // Convert the VS code into a recognizable format by GLAD (zero-terminated array of characters)
	const char* fragmentSource = fragmentCode.c_str(); // Convert the FS code into a recognizable format by GLAD (zero-terminated array of characters)

	GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER); // Create VS object
	glShaderSource(vertexShader, 1, &vertexSource, NULL); // Attach VS source code to VS object
	glCompileShader(vertexShader); // Compile VS into machine code
	// Check for errors for VS
	if (CheckErrors(vertexShader, "VERTEX"))
	{
		return;
	}

	GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER); // Create FS object
	glShaderSource(fragmentShader, 1, &fragmentSource, NULL); // Attach FS source code to VS object
	glCompileShader(fragmentShader); // Compile FS into machine code
	// Check for errors for FS
	if (CheckErrors(fragmentShader, "FRAGMENT"))
	{
		return;
	}

	id = glCreateProgram(); // Create final object shader
	glAttachShader(id, vertexShader); // Attach VS to the new shader
	glAttachShader(id, fragmentShader); // Attach FS to the new shader
	glLinkProgram(id); // Link final shader into the shading program
	// Check for error for the main shader
	if (CheckErrors(id, "PROGRAM"))
	{
		return;
	}

	glDeleteShader(vertexShader); // Delete VS object
	glDeleteShader(fragmentShader); // Delete FS object
}

void Shader::Delete()
{
	glDeleteProgram(id);
}

void Shader::Use()
{
	glUseProgram(id); // Use shader
}

void Shader::InitMatrices(glm::mat4 view, glm::mat4 projection)
{
	Utils::SendMatrix4x4_Uniform(id, "view", view); // Send view matrix as uniform to the GPU
	Utils::SendMatrix4x4_Uniform(id, "projection", projection); // Send projection matrix as uniform to the GPU
}

void Shader::InitMaterial(glm::vec3 lightSrcPosition, glm::vec3 lightSrcColor, glm::vec3 cameraPosition,
	glm::vec3 ambient, glm::vec3 diffuse, glm::vec3 specular, float shininess)
{
	Utils::Send3f_Uniform(id, "material.ambient", ambient); // Send material ambient color to the GPU
	Utils::Send3f_Uniform(id, "material.diffuse", diffuse); // Send material diffuse color to the GPU
	Utils::Send3f_Uniform(id, "material.specular", specular); // Send material specular color to the GPU
	Utils::Send1f_Uniform(id, "material.shininess", shininess); // Send material shininess value to the GPU
	Utils::Send3f_Uniform(id, "lightPos", lightSrcPosition); // Send light position as uniform to the GPU
	Utils::Send3f_Uniform(id, "lightColor", lightSrcColor); // Send light color as uniform to the GPU
	Utils::Send3f_Uniform(id, "camPos", cameraPosition); // Send camera position as uniform to the GPU
}

int Shader::CheckErrors(GLuint shader, const char* type)
{
	GLint hasCompiled;
	char infoLog[1024];

	if (type != "PROGRAM")
	{
		glGetShaderiv(shader, GL_COMPILE_STATUS, &hasCompiled);
		if (hasCompiled == GL_FALSE)
		{
			glGetShaderInfoLog(shader, 1024, NULL, infoLog);
			std::cout << "SHADER_COMPILATION_ERROR for: " << type << std::endl;

			if (type == "VERTEX")
			{
				std::cout << "FAULTY SHADER AT: " << vertexShaderPath << std::endl << std::endl;
				return -1;
			}
			else if (type == "FRAGMENT")
			{
				std::cout << "FAULTY SHADER AT: " << fragmentShaderPath << std::endl << std::endl;
				return -2;
			}
		}
	}
	else
	{
		glGetShaderiv(shader, GL_COMPILE_STATUS, &hasCompiled);
		if (hasCompiled == GL_FALSE)
		{
			glGetShaderInfoLog(shader, 1024, NULL, infoLog);
			std::cout << "SHADER_LINKING_ERROR for: " << type << std::endl << std::endl;
			return -3;
		}
	}

	return 0;
}