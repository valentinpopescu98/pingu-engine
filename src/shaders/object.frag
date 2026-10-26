#version 330 core
struct Material 
{
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
    float shininess;
};

in vec3 normal; // Input normals from the vertex shader
in vec2 textCoord; // Input texture coordinates from the vertex shader
in vec3 color; // Input color from the vertex shader
in vec3 objPos; // The global position of the object

layout(location = 0) out vec4 outColor; // Fragment color

uniform bool hasTexture; // Variable that determines if textures are to be used or not
uniform vec3 lightColor; // Color of the light source (TODO: implement a combined color from many light sources)
uniform vec3 lightPos; // Color of the light position (TODO: implement an array of many light sources)
uniform vec3 camPos; // Position of the camera
uniform sampler2D texture_diffuse1; // Value coresponding to the used diffuse texture slot
//uniform sampler2D texture_specular1; // Value coresponding to the used specular texture slot
//uniform sampler2D texture_normal1; // Value coresponding to the used normal texture slot
uniform Material material;

void main()
{
	vec4 textDiff, textSpec, textNorm;

	if (!hasTexture)
	{
		textDiff = vec4(1.0f);
		//textSpec = vec4(1.0f);
		//textNorm = vec4(1.0f);
	}
	else
	{
		textDiff = texture(texture_diffuse1, textCoord);
		//textSpec = texture(texture_specular1, textCoord);
		//textNorm = texture(texture_normal1, textCoord);
	}

	vec3 outNormal = normalize(normal); // Normalize the interpolated world-space normal to unit length

	vec3 ambient = material.ambient; // Ambient light value

	vec3 lightDirection = normalize(lightPos - objPos); // Calculate light direction and normalize it
	/* Calculate cos between normal and light direction.
	   Take the maximum between this and 0 because the higher the cos,
	   the lower the angle is, so at higher angles take a lower value
	   and diffuse lesser light. */
	float diff = max(dot(outNormal, lightDirection), 0.0f);
	vec3 diffuse = diff * material.diffuse;

	vec3 viewDirection = normalize(camPos - objPos); // Calculate vector of view direction
	// Reflection direction is tangent to light direction and is calculated depending on the direction of normal vector
	vec3 reflectionDirection = reflect(-lightDirection, outNormal);
	/* Calculate cos between view direction and light reflection.
	   Take the maximum between this and 0.
	   Raise the result to the power of 8 (or choose any other constant),
	   the higher the power is the more focused the specular light is. */
	float spec = pow(max(dot(viewDirection, reflectionDirection), 0.0f), material.shininess);
	vec3 specular = spec * material.specular;

	vec3 phong = ambient + diffuse + specular;

	outColor =  textDiff * vec4(color * lightColor * phong, 1.0f); // Output color of each fragment
	//outColor =  mix(textDiff, textSpec, textNorm) *	vec4(color * lightColor * phong, 1.0f); // Output color of each fragment
	
}