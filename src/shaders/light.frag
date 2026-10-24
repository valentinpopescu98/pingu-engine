#version 330 core
in vec3 normal; // Input normals from the vertex shader
in vec2 textCoord; // Input texture coordinates from the vertex shader
in vec3 color; // Input color from the vertex shader

layout(location = 0) out vec4 outColor; // Fragment color

uniform bool hasTexture; // Variable that determines if textures are to be used or not
uniform sampler2D texture_diffuse1; // Value coresponding to the used texture slot

void main()
{
	if (hasTexture)
	{
		outColor = texture(texture_diffuse1, textCoord) * vec4(color, 1.0f); // Output color of each fragment
	}
	else
	{
		outColor = vec4(color, 1.0f); // Output color of each fragment
	}
}