/*
*	CShader_GBuffer.cpp - Regan Russell
*
*	GBuffer shader for deferred rendering. Fills GBuffer.
*/

#include "kopengi.h"

CShader_GBuffer::CShader_GBuffer(std::string vs_path, std::string ps_path)
{
	GLuint vsID = glCreateShader(GL_VERTEX_SHADER);
	GLuint psID = glCreateShader(GL_FRAGMENT_SHADER);

	std::string vsCode;
	std::ifstream vsStream(vs_path.c_str(), std::ios::in);
	if (vsStream.is_open())
	{
		std::string line = "";
		while (getline(vsStream, line))
		{
			vsCode += "\n" + line;
		}

		vsStream.close();
	}

	std::string psCode;
	std::ifstream psStream(ps_path.c_str(), std::ios::in);
	if (psStream.is_open())
	{
		std::string line = "";
		while (getline(psStream, line))
		{
			psCode += "\n" + line;
		}

		psStream.close();
	}

	GLint result = GL_FALSE;
	int logLength;

	// Compile vertex shader
	log(LOG_TYPE_DEFAULT, "Compiling Shader: " +  vs_path + "..");
	const char* vsPointer = vsCode.c_str();
	glShaderSource(vsID, 1, &vsPointer, NULL);
	glCompileShader(vsID);

	// Check shader status
	glGetShaderiv(vsID, GL_COMPILE_STATUS, &result);
	if (!result)
	{
		glGetShaderiv(vsID, GL_INFO_LOG_LENGTH, &logLength);
		std::vector<char> vsError(logLength);
		glGetShaderInfoLog(vsID, logLength, NULL, &vsError[0]);
		
		if (vsError.size() - 1 >= 0)
		{
			vsError[vsError.size() - 1] = '\0';
		}

		log(LOG_TYPE_ERROR, std::string((char*)&vsError[0]));
	}

	// Compile pixel shader
	log(LOG_TYPE_DEFAULT, "Compiling Shader: " +  ps_path +  "..");
	const char* psPointer = psCode.c_str();
	glShaderSource(psID, 1, &psPointer, NULL);
	glCompileShader(psID);

	// Check shader status
	glGetShaderiv(psID, GL_COMPILE_STATUS, &result);
	if (!result)
	{
		glGetShaderiv(psID, GL_INFO_LOG_LENGTH, &logLength);
		std::vector<char> psError(logLength);
		glGetShaderInfoLog(psID, logLength, NULL, &psError[0]);
		
		if (psError.size() - 1 >= 0)
		{
			psError[psError.size() - 1] = '\0';
		}

		log(LOG_TYPE_ERROR, std::string((char*)&psError[0]));
	}

	// Link shader
	log(LOG_TYPE_DEFAULT, "Linking shader ..");
	GLuint shaderID = glCreateProgram();
	glAttachShader(shaderID, vsID);
	glAttachShader(shaderID, psID);
	glLinkProgram(shaderID);

	// Check final shader
	glGetProgramiv(shaderID, GL_LINK_STATUS, &result);
	if (!result)
	{
		glGetProgramiv(shaderID, GL_INFO_LOG_LENGTH, &logLength);
		std::vector<char> shaderError(logLength);
		glGetProgramInfoLog(shaderID, logLength, NULL, &shaderError[0]);
		
		if (shaderError.size() - 1 >= 0)
		{
			shaderError[shaderError.size() - 1] = '\0';
		}

		log(LOG_TYPE_ERROR, std::string((char*)&shaderError[0]));
	}

	// Clean up
	glDeleteShader(vsID);
	glDeleteShader(psID);

	// Save the ID
	m_Id = shaderID;}

CShader_GBuffer::~CShader_GBuffer() {}

void CShader_GBuffer::PreLink(GLuint ID)
{
	glBindFragDataLocation(ID, 0, "out_diffuse");
	glBindFragDataLocation(ID, 1, "out_normal");
	glBindFragDataLocation(ID, 2, "out_depth");
}

void CShader_GBuffer::Activate()
{
	glUseProgram(m_Id);

	// Send Matrices
	GLuint viewMatrixID = glGetUniformLocation(m_Id, "ViewMatrix");
	if (viewMatrixID != -1)
		glUniformMatrix4fv(viewMatrixID, 1, GL_FALSE, &GetGame()->GetRenderSystem()->GetViewMatrix()[0][0]);

	GLuint projectionMatrixID = glGetUniformLocation(m_Id, "ProjectionMatrix");
	if (projectionMatrixID != -1)
		glUniformMatrix4fv(projectionMatrixID, 1, GL_FALSE, &GetGame()->GetRenderSystem()->GetProjectionMatrix()[0][0]);

	GLuint camFarZ = glGetUniformLocation(m_Id, "camFarZ");
	if (camFarZ != -1)
		glUniform1f(camFarZ, GetGame()->GetRenderSystem()->GetCamera()->GetFarZ());
}

void CShader_GBuffer::Update()
{
	CMesh* mesh = GetGame()->GetRenderSystem()->GetCurMesh();
	CMaterial mat = mesh->GetMaterial();

	if (GetGame()->GetRenderSystem()->GetCurMaterial() != 0)
		mat = *GetGame()->GetRenderSystem()->GetCurMaterial();

	// Pass material data to shader
	GLuint textureCountID = glGetUniformLocation(GetGame()->GetRenderSystem()->GetCurShader()->GetID(), "matTextureCount");
	if (textureCountID != -1)
		glUniform1f(textureCountID, (float)mat.m_TextureCount);

	GLuint diffuseID = glGetUniformLocation(GetGame()->GetRenderSystem()->GetCurShader()->GetID(), "matDiffuse");
	if (diffuseID != -1)
		glUniform4f(diffuseID, mat.m_Diffuse.r, mat.m_Diffuse.g, mat.m_Diffuse.b, mat.m_Diffuse.a);
}

void CShader_GBuffer::Render()
{
	CMesh* mesh = GetGame()->GetRenderSystem()->GetCurMesh();

	if (GetGame()->GetGLSLVersion() == GLSL_VERSION_130)
	{
		glBindAttribLocation(GetID(), 0, "vertexPos_MS");
		glBindAttribLocation(GetID(), 1, "vertexTexCoords");
		glBindAttribLocation(GetID(), 2, "vertexNormal_MS");
	}

	// Enable positions
	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, mesh->m_VertexBuffer);
	glVertexAttribPointer(
		0,
		3,
		GL_FLOAT,
		GL_FALSE,
		0,
		(void*)0
	);

	// Enable UVs
	glEnableVertexAttribArray(1);
	glBindBuffer(GL_ARRAY_BUFFER, mesh->m_UVBuffer);
	glVertexAttribPointer(
		1,
		2,
		GL_FLOAT,
		GL_FALSE,
		0,
		(void*)0
	);

	// Enable normals
	glEnableVertexAttribArray(2);
	glBindBuffer(GL_ARRAY_BUFFER, mesh->m_NormalBuffer);
	glVertexAttribPointer(
		2,
		3,
		GL_FLOAT,
		GL_FALSE,
		0,
		(void*)0
	);

	// Set texture
	glBindTexture(GL_TEXTURE_2D, mesh->m_TextureIndex);

	// Bind index buffer
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh->m_IndexBuffer);

	// Render
	glDrawElements(
		GL_TRIANGLES,
		sizeof(unsigned int) * mesh->m_NumFaces * 3,
		GL_UNSIGNED_INT,
		(void*)0
	);

	// Clean up
	glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(1);
	glDisableVertexAttribArray(2);
}
