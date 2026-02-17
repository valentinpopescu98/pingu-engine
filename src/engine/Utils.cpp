#include "Utils.h"

// Data for a triangle
std::vector<VertexStruct> Utils::triangleVertices =
{
	//	             COORDS		                   NORMALS                 TEXT COORDS                  COLORS
	{glm::vec3(-0.5f, -0.5f,  0.5f), glm::vec3( 0.0f,  1.0f,  1.0f), glm::vec2(0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f)}, // front left
	{glm::vec3( 0.5f, -0.5f,  0.5f), glm::vec3( 0.0f,  1.0f,  1.0f), glm::vec2(1.0f, 0.0f), glm::vec3(0.0f, 0.0f, 1.0f)}, // front right
	{glm::vec3( 0.0f,  0.5f,  0.0f), glm::vec3( 0.0f,  1.0f,  1.0f), glm::vec2(0.5f, 1.0f), glm::vec3(0.0f, 1.0f, 1.0f)}  // top
};

std::vector<GLuint> Utils::triangleIndices
{
	0, 1, 2
};

// Data for a quad
std::vector<VertexStruct> Utils::quadVertices =
{
	//	             COORDS		                   NORMALS                 TEXT COORDS                  COLORS
	{glm::vec3(-0.5f, -0.5f,  0.5f), glm::vec3( 0.0f,  0.0f,  1.0f), glm::vec2(0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f)}, // bottom left
	{glm::vec3( 0.5f, -0.5f,  0.5f), glm::vec3( 0.0f,  0.0f,  1.0f), glm::vec2(1.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f)}, // bottom right
	{glm::vec3( 0.5f,  0.5f,  0.5f), glm::vec3( 0.0f,  0.0f,  1.0f), glm::vec2(1.0f, 1.0f), glm::vec3(1.0f, 1.0f, 1.0f)}, // top right
	{glm::vec3(-0.5f,  0.5f,  0.5f), glm::vec3( 0.0f,  0.0f,  1.0f), glm::vec2(0.0f, 1.0f), glm::vec3(0.0f, 1.0f, 0.0f)}  // top left
};

std::vector<GLuint> Utils::quadIndices
{
	0, 1, 2,		// bottom right triangle
	2, 3, 0			// top left triangle
};

// Data for a pyramid
std::vector<VertexStruct> Utils::pyramidVertices
{
	//	             COORDS		                    NORMALS                  TEXT COORDS                  COLORS
	// Base face
	{glm::vec3(-0.5f, -0.5f, -0.5f), glm::vec3( 0.0f, -1.0f,  0.0f), glm::vec2(0.0f, 1.0f), glm::vec3(1.0f, 0.0f, 0.0f)}, // back left
	{glm::vec3( 0.5f, -0.5f, -0.5f), glm::vec3( 0.0f, -1.0f,  0.0f), glm::vec2(1.0f, 1.0f), glm::vec3(1.0f, 1.0f, 0.0f)}, // back right
	{glm::vec3( 0.5f, -0.5f,  0.5f), glm::vec3( 0.0f, -1.0f,  0.0f), glm::vec2(1.0f, 0.0f), glm::vec3(0.0f, 0.0f, 1.0f)}, // front right
	{glm::vec3(-0.5f, -0.5f,  0.5f), glm::vec3( 0.0f, -1.0f,  0.0f), glm::vec2(0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f)}, // front left

	// Front face	    
	{glm::vec3(-0.5f, -0.5f,  0.5f), glm::vec3( 0.0f,  1.0f,  1.0f), glm::vec2(0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f)}, // front left
	{glm::vec3( 0.5f, -0.5f,  0.5f), glm::vec3( 0.0f,  1.0f,  1.0f), glm::vec2(1.0f, 0.0f), glm::vec3(0.0f, 0.0f, 1.0f)}, // front right
	{glm::vec3( 0.0f,  0.5f,  0.0f), glm::vec3( 0.0f,  1.0f,  1.0f), glm::vec2(0.5f, 1.0f), glm::vec3(0.0f, 1.0f, 1.0f)}, // top

	// Right face	    
	{glm::vec3( 0.5f, -0.5f,  0.5f), glm::vec3( 1.0f,  1.0f,  0.0f), glm::vec2(1.0f, 0.0f), glm::vec3(0.0f, 0.0f, 1.0f)}, // front right
	{glm::vec3( 0.5f, -0.5f, -0.5f), glm::vec3( 1.0f,  1.0f,  0.0f), glm::vec2(0.0f, 0.0f), glm::vec3(1.0f, 1.0f, 0.0f)}, // back right
	{glm::vec3( 0.0f,  0.5f,  0.0f), glm::vec3( 1.0f,  1.0f,  0.0f), glm::vec2(0.5f, 1.0f), glm::vec3(0.0f, 1.0f, 1.0f)}, // top

	// Back face	    
	{glm::vec3( 0.5f, -0.5f, -0.5f), glm::vec3( 0.0f,  1.0f, -1.0f), glm::vec2(0.0f, 0.0f), glm::vec3(1.0f, 1.0f, 0.0f)}, // back right
	{glm::vec3(-0.5f, -0.5f, -0.5f), glm::vec3( 0.0f,  1.0f, -1.0f), glm::vec2(1.0f, 0.0f), glm::vec3(1.0f, 0.0f, 0.0f)}, // back left
	{glm::vec3( 0.0f,  0.5f,  0.0f), glm::vec3( 0.0f,  1.0f, -1.0f), glm::vec2(0.5f, 1.0f), glm::vec3(0.0f, 1.0f, 1.0f)}, // top

	// Left face	    
	{glm::vec3(-0.5f, -0.5f, -0.5f), glm::vec3(-1.0f,  1.0f,  0.0f), glm::vec2(1.0f, 0.0f), glm::vec3(1.0f, 0.0f, 0.0f)}, // back left
	{glm::vec3(-0.5f, -0.5f,  0.5f), glm::vec3(-1.0f,  1.0f,  0.0f), glm::vec2(0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f)}, // front left
	{glm::vec3( 0.0f,  0.5f,  0.0f), glm::vec3(-1.0f,  1.0f,  0.0f), glm::vec2(0.5f, 1.0f), glm::vec3(0.0f, 1.0f, 1.0f)}  // top
};

std::vector<GLuint> Utils::pyramidIndices
{
	0, 1, 2,		// bottom right base triangle
	2, 3, 0,		// top left base triangle
	4, 5, 6,		// front face triangle
	7, 8, 9,		// right face triangle
	10, 11, 12,		// back face triangle
	13, 14, 15		// left face triangle
};

// Data for a cube
std::vector<VertexStruct> Utils::cubeVertices
{
	//	             COORDS		                    NORMALS                  TEXT COORDS                  COLORS
	// Bottom face
	{glm::vec3(-0.5f, -0.5f, -0.5f), glm::vec3( 0.0f, -1.0f,  0.0f), glm::vec2(0.0f, 1.0f), glm::vec3(1.0f, 0.0f, 0.0f)}, // back bottom left
	{glm::vec3( 0.5f, -0.5f, -0.5f), glm::vec3( 0.0f, -1.0f,  0.0f), glm::vec2(1.0f, 1.0f), glm::vec3(1.0f, 1.0f, 0.0f)}, // back bottom right
	{glm::vec3( 0.5f, -0.5f,  0.5f), glm::vec3( 0.0f, -1.0f,  0.0f), glm::vec2(1.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f)}, // front bottom right
	{glm::vec3(-0.5f, -0.5f,  0.5f), glm::vec3( 0.0f, -1.0f,  0.0f), glm::vec2(0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f)}, // front bottom left

	// Top face
	{glm::vec3(-0.5f,  0.5f,  0.5f), glm::vec3( 0.0f,  1.0f,  0.0f), glm::vec2(0.0f, 1.0f), glm::vec3(0.0f, 1.0f, 0.0f)}, // front top left
	{glm::vec3( 0.5f,  0.5f,  0.5f), glm::vec3( 0.0f,  1.0f,  0.0f), glm::vec2(1.0f, 1.0f), glm::vec3(1.0f, 1.0f, 1.0f)}, // front top right
	{glm::vec3( 0.5f,  0.5f, -0.5f), glm::vec3( 0.0f,  1.0f,  0.0f), glm::vec2(1.0f, 0.0f), glm::vec3(1.0f, 1.0f, 0.0f)}, // back top right
	{glm::vec3(-0.5f,  0.5f, -0.5f), glm::vec3( 0.0f,  1.0f,  0.0f), glm::vec2(0.0f, 0.0f), glm::vec3(1.0f, 0.0f, 0.0f)}, // back top left

	// Front face
	{glm::vec3(-0.5f, -0.5f,  0.5f), glm::vec3( 0.0f,  0.0f,  1.0f), glm::vec2(0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f)}, // front bottom left
	{glm::vec3( 0.5f, -0.5f,  0.5f), glm::vec3( 0.0f,  0.0f,  1.0f), glm::vec2(1.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f)}, // front bottom right
	{glm::vec3( 0.5f,  0.5f,  0.5f), glm::vec3( 0.0f,  0.0f,  1.0f), glm::vec2(1.0f, 1.0f), glm::vec3(1.0f, 1.0f, 1.0f)}, // front top right
	{glm::vec3(-0.5f,  0.5f,  0.5f), glm::vec3( 0.0f,  0.0f,  1.0f), glm::vec2(0.0f, 1.0f), glm::vec3(0.0f, 1.0f, 0.0f)}, // front top left

	// Right face
	{glm::vec3( 0.5f, -0.5f,  0.5f), glm::vec3( 1.0f,  0.0f,  0.0f), glm::vec2(1.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f)}, // front bottom right
	{glm::vec3( 0.5f, -0.5f, -0.5f), glm::vec3( 1.0f,  0.0f,  0.0f), glm::vec2(0.0f, 0.0f), glm::vec3(1.0f, 1.0f, 0.0f)}, // back bottom right
	{glm::vec3( 0.5f,  0.5f, -0.5f), glm::vec3( 1.0f,  0.0f,  0.0f), glm::vec2(0.0f, 1.0f), glm::vec3(1.0f, 1.0f, 0.0f)}, // back top right
	{glm::vec3( 0.5f,  0.5f,  0.5f), glm::vec3( 1.0f,  0.0f,  0.0f), glm::vec2(1.0f, 1.0f), glm::vec3(1.0f, 1.0f, 1.0f)}, // front top right

	// Back face
	{glm::vec3( 0.5f, -0.5f, -0.5f), glm::vec3( 0.0f,  0.0f, -1.0f), glm::vec2(0.0f, 0.0f), glm::vec3(1.0f, 1.0f, 0.0f)}, // back bottom right
	{glm::vec3(-0.5f, -0.5f, -0.5f), glm::vec3( 0.0f,  0.0f, -1.0f), glm::vec2(1.0f, 0.0f), glm::vec3(1.0f, 0.0f, 0.0f)}, // back bottom left
	{glm::vec3(-0.5f,  0.5f, -0.5f), glm::vec3( 0.0f,  0.0f, -1.0f), glm::vec2(1.0f, 1.0f), glm::vec3(1.0f, 0.0f, 0.0f)}, // back top left
	{glm::vec3( 0.5f,  0.5f, -0.5f), glm::vec3( 0.0f,  0.0f, -1.0f), glm::vec2(0.0f, 1.0f), glm::vec3(1.0f, 1.0f, 0.0f)}, // back top right

	// Left face
	{glm::vec3(-0.5f, -0.5f, -0.5f), glm::vec3(-1.0f,  0.0f,  0.0f), glm::vec2(1.0f, 0.0f), glm::vec3(1.0f, 0.0f, 0.0f)}, // back bottom left
	{glm::vec3(-0.5f, -0.5f,  0.5f), glm::vec3(-1.0f,  0.0f,  0.0f), glm::vec2(0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f)}, // front bottom left
	{glm::vec3(-0.5f,  0.5f,  0.5f), glm::vec3(-1.0f,  0.0f,  0.0f), glm::vec2(0.0f, 1.0f), glm::vec3(0.0f, 1.0f, 0.0f)}, // front top left
	{glm::vec3(-0.5f,  0.5f, -0.5f), glm::vec3(-1.0f,  0.0f,  0.0f), glm::vec2(1.0f, 1.0f), glm::vec3(1.0f, 0.0f, 0.0f)}  // back top left
};

std::vector<GLuint> Utils::cubeIndices
{
	0, 1, 2,		// bottom right, front face triangle
	2, 3, 0,		// top left, front face triangle

	4, 5, 6,		// bottom right, back face triangle
	6, 7, 4,		// top left, back face triangle

	8, 9, 10,		// bottom right, left face triangle
	10, 11, 8,		// top left, left face triangle

	12, 13, 14,		// bottom right, right face triangle
	14, 15, 12,		// top left, right face triangle

	16, 17, 18,		// bottom right, top face triangle
	18, 19, 16,		// top left, top face triangle

	20, 21, 22,		// bottom right, bottom face triangle
	22, 23, 20		// top right, bottom face triangle
};

std::string Utils::GetFileContents(const char* filePath)
{
	std::ifstream in(filePath, std::ios::binary);

	if (in)
	{
		std::string contents;
		in.seekg(0, std::ios::end);
		contents.resize(in.tellg());
		in.seekg(0, std::ios::beg);
		in.read(&contents[0], contents.size());
		in.close();
		return(contents);
	}

	throw(errno + " ERROR: Could not open file.");
}

std::vector<std::string> Utils::GetFileLines(const char* filePath)
{
	std::ifstream in(filePath);
	std::string line;
	std::vector<std::string> lines;

	if (in)
	{
		while (std::getline(in, line))
		{
			lines.push_back(line);
		}

		return lines;
	}

	throw(errno + " ERROR: Could not open file.");
}

void Utils::SendMatrix4x4_Uniform(GLuint shaderID, const char* uniform, glm::mat4 matrix)
{
	GLuint location = glGetUniformLocation(shaderID, uniform); // Create uniform variable
	glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(matrix)); // Set matrix value for the uniform
}

void Utils::Send1i_Uniform(GLuint shaderID, const char* uniform, int value)
{
	GLuint location = glGetUniformLocation(shaderID, uniform); // Create uniform variable
	glUniform1i(location, value); // Set value for the uniform
}

void Utils::Send1f_Uniform(GLuint shaderID, const char* uniform, float value)
{
	GLuint location = glGetUniformLocation(shaderID, uniform); // Create uniform variable
	glUniform1f(location, value); // Set value for the uniform
}

void Utils::Send3f_Uniform(GLuint shaderID, const char* uniform, glm::vec3 values)
{
	GLuint location = glGetUniformLocation(shaderID, uniform); // Create uniform variable
	glUniform3f(location, values.x, values.y, values.z); // Set values for the uniform
}

float Utils::Get3DObjectLongestSide(float x, float y, float z)
{
	float longestSide = x;
	longestSide = y > x ? y : x;
	longestSide = z > longestSide ? z : longestSide;

	return longestSide;
}

float Utils::GetRandomFloat(float left, float right)
{
	static bool seeded = false;
	if (!seeded)
	{
		srand(static_cast<unsigned>(time(0)));
		seeded = true;
	}
	return left + static_cast<float>(rand()) / (static_cast<float>(RAND_MAX / (right - left)));
}