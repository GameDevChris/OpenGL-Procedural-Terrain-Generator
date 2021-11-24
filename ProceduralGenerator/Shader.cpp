#include "Shader.h"
using namespace std;

Shader::Shader()
{
}

Shader::Shader(const char* vPath, const char* fPath)
{
	vertexPath = vPath;
	fragmentPath = fPath;
}

void Shader::Start()
{
	//Step 1: Retrieve source code
	string vertexCode;
	string fragmentCode;
	ifstream vertexShaderFile;
	ifstream fragmentShaderFile;

	//Open files 
	vertexShaderFile.open(vertexPath);
	fragmentShaderFile.open(fragmentPath);

	//Read file buffer content into streams
	stringstream vertexShaderStream, fragmentShaderStream;
	vertexShaderStream << vertexShaderFile.rdbuf();
	fragmentShaderStream << fragmentShaderFile.rdbuf();

	//Close file handlers
	vertexShaderFile.close();
	fragmentShaderFile.close();

	//Convert stream to string
	vertexCode = vertexShaderStream.str();
	fragmentCode = fragmentShaderStream.str();

	const char* vertexShaderCode = vertexCode.c_str();
	const char* fragmentShaderCode = fragmentCode.c_str();

	//Step 2: Compile shaders

	//Vertex Shader
	unsigned int vertex = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertex, 1, &vertexShaderCode, NULL);
	glCompileShader(vertex);
	ShaderTest(vertex);

	//Fragment Shader
	unsigned int fragment = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragment, 1, &fragmentShaderCode, NULL);
	glCompileShader(fragment);
	ShaderTest(fragment);

	//Link Shaders
	ID = glCreateProgram();
	glAttachShader(ID, vertex);
	glAttachShader(ID, fragment);
	glLinkProgram(ID);

	glDeleteShader(vertex);
	glDeleteShader(fragment);
}

void Shader::Use()
{
	glUseProgram(ID);
}

void Shader::SetBool(const std::string& name, bool value) const
{
	glUniform1i(glGetUniformLocation(ID, name.c_str()), (int)value);
}

void Shader::SetInt(const std::string& name, int value) const
{
	glUniform1i(glGetUniformLocation(ID, name.c_str()), value);
}

void Shader::SetFloat(const std::string& name, float value) const
{
	glUniform1f(glGetUniformLocation(ID, name.c_str()), value);
}

void Shader::setVec2(const std::string& name, float x, float y) const
{
	glUniform2f(glGetUniformLocation(ID, name.c_str()), x, y);
}

void Shader::setVec3(const std::string& name, float x, float y, float z) const
{
	glUniform3f(glGetUniformLocation(ID, name.c_str()), x, y, z);
}

void Shader::setVec4(const std::string& name, float x, float y, float z, float w) const
{
	glUniform4f(glGetUniformLocation(ID, name.c_str()), x, y, z, w);
}

void Shader::setMat2(const std::string& name, const glm::mat2& mat) const
{
	glUniformMatrix2fv(glGetUniformLocation(ID, name.c_str()), 1, GL_FALSE, &mat[0][0]);
}

void Shader::setMat3(const std::string& name, const glm::mat3& mat) const
{
	glUniformMatrix3fv(glGetUniformLocation(ID, name.c_str()), 1, GL_FALSE, &mat[0][0]);
}

void Shader::setMat4(const std::string& name, const glm::mat4& mat) const
{
	glUniformMatrix4fv(glGetUniformLocation(ID, name.c_str()), 1, GL_FALSE, &mat[0][0]);
}

void Shader::ShaderTest(unsigned int shader)
{
	GLint result = GL_FALSE;
	int logLength; glGetShaderiv(shader, GL_COMPILE_STATUS, &result);
	glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &logLength);
	std::vector<GLchar> vertShaderError((logLength > 1) ? logLength : 1);
	glGetShaderInfoLog(shader, logLength, NULL, &vertShaderError[0]);
	std::cout << &vertShaderError[0] << std::endl;
}
