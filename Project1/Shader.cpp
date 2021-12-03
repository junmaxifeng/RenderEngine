#include "Shader.h"
#include <fstream>
#include <sstream>
Shader::Shader() :
	mProgram(0),
	mVertexShaderPath(),
	mTessConShaderPath(),
	mTessEvalShaderPath(),
	mGeometryShaderPath(),
	mFragShaderPath()
{

}

Shader::Shader(const Shader & other)
{
	setVertexShaderPath(other.mVertexShaderPath);
	setTessConShaderPath(other.mTessConShaderPath);
	setTessEvalShaderPath(other.mTessEvalShaderPath);
	setGeometryShaderPath(other.mGeometryShaderPath);
	setFragShaderPath(other.mFragShaderPath);
	InitProgram();
}


Shader::~Shader()
{
	glDeleteProgram(mProgram);
}

void Shader::checkCompileErrors(const GLuint &shader, const std::string &type)
{
	GLint success;
	GLchar infoLog[1024];
	if (type != "PROGRAM")
	{
		glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
		if (!success)
		{
			glGetShaderInfoLog(shader, 1024, NULL, infoLog);
			std::cout << "ERROR::SHADER_COMPILATION_ERROR of type: " << type << "\n" << infoLog << "\n -- --------------------------------------------------- -- " << std::endl;
		}
	}
	else
	{
		glGetProgramiv(shader, GL_LINK_STATUS, &success);
		if (!success)
		{
			glGetProgramInfoLog(shader, 1024, NULL, infoLog);
			std::cout << "ERROR::PROGRAM_LINKING_ERROR of type: " << type << "\n" << infoLog << "\n -- --------------------------------------------------- -- " << std::endl;
		}
	}
}

std::string Shader::readShaderFile(const std::string &path)
{
	std::string shaderCode;
	std::ifstream shaderFile;
	shaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
	try
	{
		shaderFile.open(path);
		std::stringstream shaderStream;
		shaderStream << shaderFile.rdbuf();

		shaderFile.close();
		shaderCode = shaderStream.str();
	}
	catch (std::ifstream::failure& e)
	{
		std::cout << "can not read shader file : " << path << std::endl;
	}
	return shaderCode;
}

GLuint Shader::createShdader(const std::string &code, const GLenum &type)
{
	const char* pCode = code.c_str();
	GLuint shader = glCreateShader(type);
	glShaderSource(shader, 1, &pCode, nullptr);
	glCompileShader(shader);
	switch (type)
	{
	case  GL_VERTEX_SHADER:
		checkCompileErrors(shader, "VERTEX");
		break;
	case GL_TESS_CONTROL_SHADER:
		checkCompileErrors(shader, "TESS_CONTROL");
		break;
	case GL_TESS_EVALUATION_SHADER:
		checkCompileErrors(shader, "TESS_EVALUATION");
		break;
	case GL_GEOMETRY_SHADER:
		checkCompileErrors(shader, "GEOMETRY");
		break;
	case GL_FRAGMENT_SHADER:
		checkCompileErrors(shader, "FRAGMENT");
		break;
	default:
		break;
	}
	return shader;
}

void Shader::setVertexShaderPath(const std::string &path)
{
	mVertexShaderPath = path;
	std::string shaderCode = readShaderFile(path);
	mVertexShader = createShdader(shaderCode, GL_VERTEX_SHADER);
}
void Shader::setTessConShaderPath(const std::string &path)
{
	mTessConShaderPath = path;
	std::string shaderCode = readShaderFile(path);
	mTessConShader = createShdader(shaderCode, GL_TESS_CONTROL_SHADER);
}
void Shader::setTessEvalShaderPath(const std::string &path)
{
	mTessEvalShaderPath = path;
	std::string shaderCode = readShaderFile(path);
	mTessEvalShader = createShdader(shaderCode, GL_TESS_EVALUATION_SHADER);
}
void Shader::setGeometryShaderPath(const std::string &path)
{
	mGeometryShaderPath = path;
	std::string shaderCode = readShaderFile(path);
	mGeometryShader = createShdader(shaderCode, GL_GEOMETRY_SHADER);
}
void Shader::setFragShaderPath(const std::string &path)
{
	mFragShaderPath = path;
	std::string shaderCode = readShaderFile(path);
	mFragShader = createShdader(shaderCode, GL_FRAGMENT_SHADER);
}

void Shader::InitProgram()
{
	if (!mVertexShaderPath.empty() && !mFragShaderPath.empty())
	{
		mProgram = glCreateProgram();
		glAttachShader(mProgram, mVertexShader);
		glAttachShader(mProgram, mFragShader);
		if (!mTessConShaderPath.empty())
		{
			glAttachShader(mProgram, mTessConShader);
		}
		if (!mTessEvalShaderPath.empty())
		{
			glAttachShader(mProgram, mTessEvalShader);
		}
		if (!mGeometryShaderPath.empty())
		{
			glAttachShader(mProgram, mGeometryShader);
		}
		glLinkProgram(mProgram);
		checkCompileErrors(mProgram, "PROGRAM");
		glDeleteShader(mVertexShader);
		glDeleteShader(mFragShader);
		if (!mTessConShaderPath.empty())
		{
			glDeleteShader(mTessConShader);
		}
		if (!mTessEvalShaderPath.empty())
		{
			glDeleteShader(mTessEvalShader);
		}
		if (!mGeometryShaderPath.empty())
		{
			glDeleteShader(mGeometryShader);
		}
	}
}

void Shader::use()
{
	glUseProgram(mProgram);
}


void Shader::setBool(const std::string &name, bool value) const
{
	glUniform1i(glGetUniformLocation(mProgram, name.c_str()), (int)value);
}

void Shader::setInt(const std::string &name, int value) const
{
	glUniform1i(glGetUniformLocation(mProgram, name.c_str()), value);
}

void Shader::setFloat(const std::string &name, float value) const
{
	glUniform1f(glGetUniformLocation(mProgram, name.c_str()), value);
}

void Shader::setVec2(const std::string &name, const glm::vec2 &value) const
{
	glUniform2fv(glGetUniformLocation(mProgram, name.c_str()), 1, &value[0]);
}
void Shader::setVec2(const std::string &name, float x, float y) const
{
	glUniform2f(glGetUniformLocation(mProgram, name.c_str()), x, y);
}

void Shader::setVec3(const std::string &name, const glm::vec3 &value) const
{
	glUniform3fv(glGetUniformLocation(mProgram, name.c_str()), 1, &value[0]);
}
void Shader::setVec3(const std::string &name, float x, float y, float z) const
{
	glUniform3f(glGetUniformLocation(mProgram, name.c_str()), x, y, z);
}

void Shader::setVec4(const std::string &name, const glm::vec4 &value) const
{
	glUniform4fv(glGetUniformLocation(mProgram, name.c_str()), 1, &value[0]);
}
void Shader::setVec4(const std::string &name, float x, float y, float z, float w)
{
	glUniform4f(glGetUniformLocation(mProgram, name.c_str()), x, y, z, w);
}

void Shader::setMat2(const std::string &name, const glm::mat2 &mat) const
{
	glUniformMatrix2fv(glGetUniformLocation(mProgram, name.c_str()), 1, GL_FALSE, &mat[0][0]);
}

void Shader::setMat3(const std::string &name, const glm::mat3 &mat) const
{
	glUniformMatrix3fv(glGetUniformLocation(mProgram, name.c_str()), 1, GL_FALSE, &mat[0][0]);
}

void Shader::setMat4(const std::string &name, const glm::mat4 &mat) const
{
	glUniformMatrix4fv(glGetUniformLocation(mProgram, name.c_str()), 1, GL_FALSE, &mat[0][0]);
}