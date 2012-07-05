#version 330

// _MS = Model Space
// _WS = World Space
// _VS = View Space

// vertex data
layout(location = 0) in vec3 vertexPos_MS;
layout(location = 1) in vec2 vertexTexCoords;
layout(location = 2) in vec3 vertexNormal_MS;

// output
out vec2 texCoords;
out vec3 normal;
out vec3 fragPos_VS;

// matrices
uniform mat4 ModelMatrix;
uniform mat4 ViewMatrix;
uniform mat4 ProjectionMatrix;
uniform mat3 NormalMatrix;

void main()
{
	mat4 MVP = ProjectionMatrix * ViewMatrix * ModelMatrix;
	
	// Bring vertex normals to view space to compare with light data
	normal = NormalMatrix * vertexNormal_MS;
	
	// Get fragment position in View Space
	fragPos_VS = (ViewMatrix * ModelMatrix * vec4(vertexPos_MS, 1.0)).xyz;
	
	gl_Position = MVP * vec4(vertexPos_MS, 1.0);
	texCoords = vertexTexCoords;
}