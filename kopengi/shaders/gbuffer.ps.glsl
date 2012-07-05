#version 330

// _MS = Model Space
// _WS = World Space
// _VS = View Space

// vertex shader input
in vec2 texCoords;
in vec3 normal;
in vec3 fragPos_VS;

// output
out vec4 out_diffuse;
out vec4 out_normal;
out float out_depth;

// camera data
uniform float camFarZ;

// texture sampler
uniform sampler2D texSampler;

// material data
uniform float matTextureCount;
uniform vec4 matDiffuse;

void main()
{
	// diffuse
	if (matTextureCount != 0) // if textured
	{
		out_diffuse = texture2D(texSampler, texCoords) * matDiffuse;
	}
	else
	{
		out_diffuse = matDiffuse;
	}

	// normals
	out_normal = vec4(normalize(normal) / 2 + 0.5, 0.0);
	
	// depth
	out_depth = -fragPos_VS.z;
}