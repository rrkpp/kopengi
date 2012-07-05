#version 330

// _MS = Model Space
// _WS = World Space
// _VS = View Space

// vertex data
layout(location = 0) in vec2 vertexPos_MS;
layout(location = 1) in vec2 vertexTexCoords;

// output
out vec2 texCoords;
out vec3 fragPos;

void main()
{
	gl_Position = vec4(vertexPos_MS, 0.0, 1.0);
	texCoords = vertexTexCoords;
}