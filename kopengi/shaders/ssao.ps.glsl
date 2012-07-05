#version 330

// _MS = Model Space
// _WS = World Space
// _VS = View Space

// vertex data
out vec4 color;
in vec2 texCoords;
in vec3 fragPos_VS;

// texture samplers
uniform sampler2D fbo_diffuse;
uniform sampler2D fbo_normal;
uniform sampler2D fbo_depth;
uniform sampler2D noiseTexture;

// camera data
uniform float camFarZ;

// kernel / noise data
uniform vec2 noiseScale;
uniform vec3 kernel[32];

// matrix data
uniform mat4 ProjectionMatrix;

void main()
{
	float depth = texture2D(fbo_depth, texCoords).r;
	vec3 f_pos = fragPos_VS * depth;
	vec3 f_normal = texture2D(fbo_normal, texCoords).xyz * 2.0 - 1.0;
	
	vec3 random = texture2D(noiseTexture, texCoords * noiseScale).xyz * 2.0 - 1.0;
	vec3 tangent = normalize(random - f_normal * dot(random, f_normal));
	vec3 biTangent = cross(f_normal, tangent);
	mat3 tbn = mat3(tangent, biTangent, f_normal);
	
	// TEMP
	float radius = 0.5;
	// TEMP
	
	float occlusion = 0.0;
	for (int i = 0; i < 32; i++)
	{
		vec3 sample = tbn * kernel[i];
		sample = sample * radius + f_pos;
		
		vec4 offset = vec4(sample, 1.0);
		offset = ProjectionMatrix * offset;
		offset.xy = offset.xy / offset.w;
		offset.xy = offset.xy * 0.5 + 0.5;
		
		float weight = 1.0; // remove screen-edge AO
		if (offset.x > 1 || offset.x < 0 || offset.y > 1 || offset.y < 0)
			weight = 0.0;
		
		float sample_depth = texture2D(fbo_depth, offset.xy).r;
		float diff = abs(-f_pos.z - sample_depth);
		float fade = radius * radius / (diff * diff + radius * radius);
		
		occlusion += (sample_depth <= -sample.z ? 1.0 : 0.0) * fade * weight;
	}
	
	occlusion = 1.0 - (occlusion / 32);
	
	color = vec4(vec3(occlusion), 1.0);
}