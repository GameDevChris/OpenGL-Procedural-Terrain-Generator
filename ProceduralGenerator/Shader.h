#pragma once
#include <glad.h> 
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <vector>

#include <glm.hpp>
#include <gtc/matrix_transform.hpp>
#include <gtc/type_ptr.hpp>

class Shader
{
public:
	unsigned int ID;
	const char* vertexPath;
	const char* fragmentPath;

	Shader();
	Shader(const char* vPath, const char* fPath);

	void Start();
	void Use();
	void ShaderTest(unsigned int shader);

	void SetBool(const std::string& name, bool value) const;
	void SetInt(const std::string& name, int value) const;
	void SetFloat(const std::string& name, float value) const;
	void setVec2(const std::string& name, float x, float y) const;
	void setVec3(const std::string& name, float x, float y, float z) const;
	void setVec4(const std::string& name, float x, float y, float z, float w) const;
	void setMat2(const std::string& name, const glm::mat2& mat) const;
	void setMat3(const std::string& name, const glm::mat3& mat) const;
	void setMat4(const std::string& name, const glm::mat4& mat) const;
};
