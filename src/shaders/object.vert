#version 330 core
layout(location = 0) in vec3 vPos; // Position of each vertex (XYZ)
layout(location = 1) in vec3 vNormal; // Direction of normal vectors for each vertex (XYZ)
layout(location = 2) in vec2 vTextCoord; // Texture coordinates of each vertex (UV)
layout(location = 3) in vec3 vColor; // Color of each vertex (RGB)

out vec3 color; // Output color for the fragment shader
out vec2 textCoord; // Output texture coordinates for the fragment shader
out vec3 normal; // Out normals for the the fragment shader

out vec3 objPos; // The global position of the object

uniform vec3 objColor; // The color of all the object

uniform mat4 model; // Model matrix (LOCAL COORDS -> WORLD COORDS)
uniform mat4 view; // View matrix (WORLD COORDS -> VIEW COORDS)
uniform mat4 projection; // Projection matrix (VIEW COORDS -> CLIP COORDS)
// CLIP COORDS -> SCREEN COORDS transformation is done automatically

void main()
{
	gl_Position = projection * view * model * vec4(vPos, 1.0); // 3D position of each vertex
	
	color = objColor; // Send the uniform object color to the fragment shader
	//color = vColor; // Send each vertex color to the fragment shader
	textCoord = vTextCoord; // Send texture coordinates to the fragment shader
	normal = mat3(transpose(inverse(model))) * vNormal; // Transform normals into world space

	// Calculate the global position of the object with the use of the model matrix and the local position
	objPos = vec3(model * vec4(vPos, 1.0));
}