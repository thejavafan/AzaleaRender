#pragma once

#include <string>
#include <GL/glew.h>
#include <GL/gl.h>
#include "glm/glm.hpp"
using namespace std;

class Shader
{
	unsigned int ID;

	Shader(const string vert, const string frag, const string geometry = "");
	~Shader();
	void Use() const;
	void SetBool(const string& key, bool value) const;
	void SetInt(const string& key, int value) const;
	void SetFloat(const string& key, float value) const;
	void SetMat4(const std::string& key, const glm::mat4& value) const;
	void SetVec3(const std::string& key, const glm::vec3& value) const;

private:
	string ReadShader(const string path);
};

