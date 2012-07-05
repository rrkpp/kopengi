#version 330

// _MS = Model Space
// _WS = World Space
// _VS = View Space

// vertex data
out vec4 color;
in vec2 texCoords;

// texture samplers
uniform sampler2D fbo_diffuse;
uniform sampler2D fbo_ssao;
uniform vec2 texelSize;

void main()
{
	vec4 f_diffuse = texture2D(fbo_diffuse, texCoords);
	
	float result = 0.0;
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			vec2 offset = vec2(texelSize.x * float(j), texelSize.y * float(i));
			result += texture2D(fbo_ssao, texCoords + offset).r;
		}
	}
	
	result = result * 0.0625;
	color = texture2D(fbo_ssao, texCoords);
}