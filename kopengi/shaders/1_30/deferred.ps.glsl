#version 130

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

// camera data
uniform float camFarZ;

// light data
uniform int lightType; // 0 = environment | 1 = directional | 2 = point | 3 = spot
uniform vec3 lightPos;
uniform vec3 lightAngle;
uniform vec3 lightDiffuse;
uniform vec3 lightAmbient;
uniform vec3 lightSpecular;
uniform float lightPower;
uniform float spotCosCutoff;
uniform float spotExp;
uniform float constAtt, linAtt, quadAtt;

void main()
{
	color = vec4(0.0, 0.0, 0.0, 1.0);

	if (lightType == 0) // environment
	{
		vec4 f_diffuse = texture2D(fbo_diffuse, texCoords);
		color = f_diffuse * vec4(lightAmbient, 1.0);
	}
	else if (lightType == 1) // directional
	{
		float depth = texture2D(fbo_depth, texCoords).r;
		vec3 f_pos = fragPos_VS * depth;
		vec4 f_diffuse = texture2D(fbo_diffuse, texCoords);
		vec3 f_normal = (texture2D(fbo_normal, texCoords) * 2.0 - 1.0).xyz;
		
		// Calculate half-vector
		vec3 L = normalize(normalize(lightPos));
		vec3 V = normalize(-normalize(f_pos));
		vec3 halfVector = normalize(L + V);
		
		float NdotL = max(dot(f_normal, normalize(lightPos)), 0.0);
		if (NdotL > 0.0)
		{
			color += f_diffuse * NdotL * vec4(lightDiffuse, 1.0);
			
			float NdotHV = max(dot(normalize(f_normal), halfVector), 0.0);
			color += vec4(lightSpecular, 1.0) * pow(NdotHV, 32.0);
		}
	}
	else if (lightType == 2) // point
	{
		float depth = texture2D(fbo_depth, texCoords).r;
		vec3 f_pos = fragPos_VS * depth;
		vec4 f_diffuse = texture2D(fbo_diffuse, texCoords);
		vec3 f_normal = (texture2D(fbo_normal, texCoords) * 2.0 - 1.0).xyz;
		
		vec3 lightDir = normalize(lightPos - f_pos);
		float NdotL = max(dot(f_normal, lightDir), 0.0);
		float dist = length(lightPos - f_pos);
		float att = (1.0 / (constAtt + linAtt * dist + quadAtt * dist * dist) * lightPower);
		
		// Calculate half-vector
		vec3 L = normalize(lightPos - normalize(f_pos));
		vec3 V = normalize(-normalize(f_pos));
		vec3 halfVector = normalize(L + V);
		
		if (att > 0.004)
		{
			color += att * (vec4(lightDiffuse, 1.0) * NdotL + vec4(lightAmbient, 1.0)) * f_diffuse;
			
			float NdotHV = max(dot(f_normal, halfVector), 0.0);
			color += att * vec4(lightSpecular, 1.0) * pow(NdotHV, 32.0);
		}
	}
	else if (lightType == 3) // spot
	{
		float depth = texture2D(fbo_depth, texCoords).r;
		vec3 f_pos = fragPos_VS * depth;
		vec4 f_diffuse = texture2D(fbo_diffuse, texCoords);
		vec3 f_normal = (texture2D(fbo_normal, texCoords) * 2.0 - 1.0).xyz;
		
		vec3 lightDir = normalize(lightPos - f_pos);
		float NdotL = max(dot(f_normal, lightDir), 0.0);
		
		// Calculate half-vector
		vec3 L = normalize(lightPos - f_pos);
		vec3 V = normalize(-f_pos);
		vec3 halfVector = normalize(L + V);
		
		if (NdotL > 0.0)
		{
			float spotEffect = dot(normalize(lightAngle), normalize(-lightDir));
			
			if (spotEffect > spotCosCutoff)
			{
				spotEffect = pow(spotEffect, spotExp);
			
				float dist = length(lightPos - f_pos);
				float att = (spotEffect / (constAtt + linAtt * dist + quadAtt * dist * dist) * lightPower);
				color += att * (vec4(lightDiffuse, 1.0) * NdotL + vec4(lightAmbient, 1.0)) * f_diffuse;
				
				float NdotHV = max(dot(f_normal, normalize(halfVector)), 0.0);
				color += att * vec4(lightSpecular, 1.0) * pow(NdotHV, 32.0);
			}
		}
	}
}
