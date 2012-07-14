#version 130

// _MS = Model Space
// _WS = World Space
// _CS = Camera Space

// vertex data
attribute vec3 vertexPos_MS;
attribute vec2 vertexTexCoords;

// output
out vec2 texCoords;

// matrices
uniform mat4 ModelMatrix;
uniform mat4 ViewMatrix;
uniform mat4 ProjectionMatrix;

void main()
{
	gl_Position = vec4(vertexPos_MS, 1.0);
	texCoords = vertexTexCoords;
}
