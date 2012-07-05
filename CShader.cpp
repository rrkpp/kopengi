/*
*	CShader.cpp - Regan Russell
*
*	Shader wrapper, helps in indexing loaded shaders
*	so that shaders aren't loaded more than once.
*/

#include "kopengi.h"

CShader::CShader() {}

CShader::CShader(std::string vs_path, std::string ps_path)
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
	std::cout << "Compiling Shader: " << vs_path << ".." << std::endl;
	const char* vsPointer = vsCode.c_str();
	glShaderSource(vsID, 1, &vsPointer, NULL);
	glCompileShader(vsID);

	// Check shader status
	glGetShaderiv(vsID, GL_COMPILE_STATUS, &result);
	glGetShaderiv(vsID, GL_INFO_LOG_LENGTH, &logLength);
	std::vector<char> vsError(logLength);
	glGetShaderInfoLog(vsID, logLength, NULL, &vsError[0]);
	std::cout << &vsError[0] << std::endl;

	// Compile pixel shader
	std::cout << "Compiling Shader: " << ps_path << ".." << std::endl;
	const char* psPointer = psCode.c_str();
	glShaderSource(psID, 1, &psPointer, NULL);
	glCompileShader(psID);

	// Check shader status
	glGetShaderiv(psID, GL_COMPILE_STATUS, &result);
	glGetShaderiv(psID, GL_INFO_LOG_LENGTH, &logLength);
	std::vector<char> psError(logLength);
	glGetShaderInfoLog(psID, logLength, NULL, &psError[0]);
	std::cout << &psError[0] << std::endl;

	// Link shader
	std::cout << "Linking shader .." << std::endl;
	GLuint shaderID = glCreateProgram();
	glAttachShader(shaderID, vsID);
	glAttachShader(shaderID, psID);
	glLinkProgram(shaderID);

	// Check final shader
	glGetProgramiv(shaderID, GL_LINK_STATUS, &result);
	glGetProgramiv(shaderID, GL_INFO_LOG_LENGTH, &logLength);
	std::vector<char> shaderError(std::max(logLength, int(1)));
	glGetProgramInfoLog(shaderID, logLength, NULL, &shaderError[0]);
	std::cout << &shaderError[0] << std::endl;

	// Clean up
	glDeleteShader(vsID);
	glDeleteShader(psID);

	// Save the ID
	m_Id = shaderID;
}

CShader::~CShader() {}

void CShader::Update() {}

void CShader::Activate()
{
	glUseProgram(m_Id);
}

void CShader::Render() {}

GLuint CShader::GetID()
{
	return m_Id;
}