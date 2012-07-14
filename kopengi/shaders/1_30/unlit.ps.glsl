#version 130

// _MS = Model Space
// _WS = World Space
// _CS = Camera Space

// vertex data
in vec2 texCoords;
out vec4 color;

// texture sampler
uniform sampler2D texSampler;

// material data
uniform float matTextureCount;
uniform vec4 matDiffuse;

void main()
{
	if (matTextureCount != 0) // if not textured
	{
		color = texture2D(texSampler, texCoords);
	}
	else
	{
		color = matDiffuse;
	}
	
	color = vec4(1.0, 1.0, 1.0, 1.0);
}
