#pragma once

#include <iostream>
#include <fstream>
#include <string>

#include <GL/glew.h>


class Shader
{
public:
	Shader();
	~Shader();

	void CreateFromString(const char* vertexCode, const char* fragmentCode);
	void CreateFromFiles(const char* vertexFilePath, const char* fragmentFilePaht);

	std::string ReadFile(const char* filename);

	GLuint GetProjectionLocation();
	GLuint GetModelLocation();
	void UseShader();
	void ClearShader();

private:
	GLuint ShaderID, uniformProjection, uniformModel;

	void CompileShader(const char* vertexCode, const char* fragmentCode);
	void AddShader(GLuint program, const char* shaderCode, GLenum shaderType);
};

