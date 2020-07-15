#include "Shader.h"
#include <string>
#include <fstream>
#include <iterator>


Shader::Shader(const string vert, const string frag, const string geometry)
{
	string vertexCode = ReadShader(vert);
	string fragmentCode = ReadShader(frag);
	bool needGeometry = geometry != "";
	string geometryCode;
	if (needGeometry)
	{
		geometryCode = ReadShader(geometry);
	}

	int vertexShader = glCreateShader(GL_VERTEX_SHADER);
	const char* vShaderCode = vertexCode.c_str();
	glShaderSource(vertexShader, 1, &vShaderCode, NULL);
	glCompileShader(vertexShader);
	int success;
	char infoLog[512];
	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
		printf("顶点着色器编译失败：%s\n", infoLog);
		return;
	}

	const char* fShaderCode = fragmentCode.c_str();
	int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fShaderCode, NULL);
	glCompileShader(fragmentShader);
	glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
		printf("片段着色器编译失败：%s\n", infoLog);
		return;
	}

	int geometryShader;
	if (needGeometry)
	{
		const char* gShaderCode = geometryCode.c_str();
		geometryShader = glCreateShader(GL_GEOMETRY_SHADER);
		glShaderSource(geometryShader, 1, &gShaderCode, NULL);
		glCompileShader(geometryShader);
		glGetShaderiv(geometryShader, GL_COMPILE_STATUS, &success);
		if (!success)
		{
			glGetShaderInfoLog(geometryShader, 512, NULL, infoLog);
			printf("几何着色器初始化失败：%s\n", infoLog);
			return;
		}
	}

	ID = glCreateProgram();

	glAttachShader(ID, vertexShader);
	glAttachShader(ID, fragmentShader);

	if (needGeometry)
	{
		glAttachShader(ID, geometryShader); 
	}
	glLinkProgram(ID);

	glGetProgramiv(ID, GL_LINK_STATUS, &success);
	if (!success)
	{
		glGetProgramInfoLog(ID, 512, NULL, infoLog);
		printf("着色器链接失败：%s\n", infoLog);
		return;
	}

	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);
	if (needGeometry)
	{
		glDeleteShader(geometryShader);
	}
}

Shader::~Shader()
{

}

void Shader::Use() const
{
	glUseProgram(ID);
}

void Shader::SetBool(const std::string& key, bool value) const
{
	glUniform1i(glGetUniformLocation(ID, key.c_str()), (int)value);
}

void Shader::SetInt(const string& key, int value) const
{
	glUniform1i(glGetUniformLocation(ID, key.c_str()), value);
}

void Shader::SetFloat(const string& key, float value) const
{
	glUniform1f(glGetUniformLocation(ID, key.c_str()), value);
}

void Shader::SetVec2(const std::string& key, const glm::vec2& value) const
{
	glUniform2fv(glGetUniformLocation(ID, key.c_str()), 1, &value[0]);
}
void Shader::SetVec2(const std::string& key, float x, float y) const
{
	glUniform2f(glGetUniformLocation(ID, key.c_str()), x, y);
}

void Shader::SetMat4(const std::string& key, const glm::mat4& value) const
{
	glUniformMatrix4fv(glGetUniformLocation(ID, key.c_str()), 1, GL_FALSE, &value[0][0]);
}

void Shader::SetVec3(const std::string& key, const glm::vec3& value) const
{
	glUniform3fv(glGetUniformLocation(ID, key.c_str()), 1, &value[0]);
}

void Shader::SetVec3(const std::string& key, float x, float y, float z) const
{
	glUniform3f(glGetUniformLocation(ID, key.c_str()), x, y, z);
}

std::string Shader::ReadShader(const string path)
{
	fstream in(path);
	string content((istreambuf_iterator<char>(in)), istreambuf_iterator<char>());
	in.close(); // 及时关闭fstream是个好习惯
	return content;
}