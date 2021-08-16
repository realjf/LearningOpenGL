#include "Shader.h"

Shader::Shader()
{
	ShaderID = 0;
	uniformProjection = 0;
	uniformModel = 0;
}

Shader::~Shader()
{
	ClearShader();
}

void Shader::CreateFromString(const char* vertexCode, const char* fragmentCode)
{
	CompileShader(vertexCode, fragmentCode);
}

void Shader::CreateFromFiles(const char* vertexFilePath, const char* fragmentFilePaht)
{
	std::string vertexCode = ReadFile(vertexFilePath);
	std::string fragmentCode = ReadFile(fragmentFilePaht);
	CompileShader(vertexCode.c_str(), fragmentCode.c_str());
}

std::string Shader::ReadFile(const char* filename)
{
	std::string content;

	std::ifstream file(filename, std::ios::in);

	if (!file.is_open()) {
		std::cout << "failed to read " << filename << ", file doesn't exist." << std::endl;
		return "";
	}

	std::string line = "";
	while (!file.eof())
	{
		std::getline(file, line);
		content.append(line + "\n");
	}

	return content;
}

GLuint Shader::GetProjectionLocation()
{
	return uniformProjection;
}

GLuint Shader::GetModelLocation()
{
	return uniformModel;
}

GLuint Shader::GetViewLocation()
{
	return uniformView;
}

GLuint Shader::GetAmbientIntensityLocation()
{
	return uniformAmbientIntensity;
}

GLuint Shader::GetAmbientColorLocation()
{
	return uniformAmbientColor;
}

GLuint Shader::GetDiffuseIntensityLocation()
{
	return uniformDiffuseIntensity;
}

GLuint Shader::GetDirectionLocation()
{
	return uniformDirection;
}

GLuint Shader::GetSpecularIntensityLocation()
{
	return uniformSpecularIntensity;
}

GLuint Shader::GetShininessLocation()
{
	return uniformShininess;
}

GLuint Shader::GetEyePositionLocation()
{
	return uniformEyePosition;
}

void Shader::UseShader()
{
	glUseProgram(ShaderID);
}

void Shader::ClearShader()
{
	if (ShaderID != 0)
	{
		glDeleteProgram(ShaderID);
		ShaderID = 0;
	}

	uniformProjection = 0;
	uniformModel = 0;
}

void Shader::CompileShader(const char* vertexCode, const char* fragmentCode)
{
	ShaderID = glCreateProgram();
	if (!ShaderID) {
		std::cout << "Create shader program failed!" << std::endl;
		return;
	}

	AddShader(ShaderID, vertexCode, GL_VERTEX_SHADER);
	AddShader(ShaderID, fragmentCode, GL_FRAGMENT_SHADER);

	GLint result = 0;
	GLchar eLog[1024] = { 0 };

	glLinkProgram(ShaderID);
	glGetProgramiv(ShaderID, GL_LINK_STATUS, &result);
	if (!result) {
		glGetProgramInfoLog(ShaderID, sizeof(eLog), nullptr, eLog);
		std::cout << "linking program faild: " << eLog << std::endl;
		return;
	}

	glValidateProgram(ShaderID);
	glGetProgramiv(ShaderID, GL_VALIDATE_STATUS, &result);
	if (!result) {
		glGetProgramInfoLog(ShaderID, sizeof(eLog), nullptr, eLog);
		std::cout << "validate program faild: " << eLog << std::endl;
		return;
	}

	uniformModel = glGetUniformLocation(ShaderID, "model");
	uniformProjection = glGetUniformLocation(ShaderID, "projection");
	uniformView = glGetUniformLocation(ShaderID, "view");
	uniformAmbientColor = glGetUniformLocation(ShaderID, "directionalLight.color");
	uniformAmbientIntensity = glGetUniformLocation(ShaderID, "directionalLight.ambientIntensity");
	uniformDiffuseIntensity = glGetUniformLocation(ShaderID, "directionalLight.diffuseIntensity");
	uniformDirection = glGetUniformLocation(ShaderID, "directionalLight.direction");
	uniformSpecularIntensity = glGetUniformLocation(ShaderID, "material.specularIntensity");
	uniformShininess = glGetUniformLocation(ShaderID, "material.shininess");
	uniformEyePosition = glGetUniformLocation(ShaderID, "eyePosition");
}

void Shader::AddShader(GLuint program, const char* shaderCode, GLenum shaderType)
{
	GLuint shader = glCreateShader(shaderType);

	const GLchar* code[1];
	code[0] = shaderCode;

	GLint codeLength[1];
	codeLength[0] = strlen(shaderCode);

	glShaderSource(shader, 1, code, codeLength);
	glCompileShader(shader);

	GLint result = 0;
	GLchar eLog[1024] = { 0 };

	glGetShaderiv(shader, GL_COMPILE_STATUS, &result);
	if (!result) {
		glGetShaderInfoLog(shader, sizeof(eLog), nullptr, eLog);
		std::cout << "compile shader " << shaderType << " faild: " << eLog << std::endl;
		return;
	}

	glAttachShader(program, shader);
	return;
}
