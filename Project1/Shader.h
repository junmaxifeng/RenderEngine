#pragma once
#include <glad/glad.h>
#include <iostream>
#include <glm/glm.hpp>

class Shader
{
public:
	Shader();
	virtual ~Shader();
	Shader(const Shader& other);

	void setVertexShaderPath(const std::string &path);
	void setTessConShaderPath(const std::string &path);
	void setTessEvalShaderPath(const std::string &path);
	void setGeometryShaderPath(const std::string &path);
	void setFragShaderPath(const std::string &path);

	void InitProgram();
	void use();

	// utility uniform functions
	void setBool(const std::string &name, bool value) const;
	void setInt(const std::string &name, int value) const;
	void setFloat(const std::string &name, float value) const;
	void setVec2(const std::string &name, const glm::vec2 &value) const;
	void setVec2(const std::string &name, float x, float y) const;
	void setVec3(const std::string &name, const glm::vec3 &value) const;
	void setVec3(const std::string &name, float x, float y, float z) const;
	void setVec4(const std::string &name, const glm::vec4 &value) const;
	void setVec4(const std::string &name, float x, float y, float z, float w);
	void setMat2(const std::string &name, const glm::mat2 &mat) const;
	void setMat3(const std::string &name, const glm::mat3 &mat) const;
	void setMat4(const std::string &name, const glm::mat4 &mat) const;
protected:
private:
	std::string readShaderFile(const std::string &path);
	GLuint createShdader(const std::string &code, const GLenum &type);
	void checkCompileErrors(const GLuint &shader, const std::string &type);
private:
	GLuint mProgram;
	GLuint mVertexShader;
	GLuint mTessConShader;
	GLuint mTessEvalShader;
	GLuint mGeometryShader;
	GLuint mFragShader;
	std::string mVertexShaderPath;
	std::string mTessConShaderPath;
	std::string mTessEvalShaderPath;
	std::string mGeometryShaderPath;
	std::string mFragShaderPath;
};

