#pragma once

/**
* Shader file
* -----------
* 
*/

#include <GL/glew.h>
#include <string>
#include <glm/glm.hpp>
#include "../utility/nonCopyable.h"

class Shader: public NonCopyable
{
public:
	Shader(
		const std::string& vertexShader,
		const std::string& fragmentShader
	);
	~Shader();
	void setBool(
		const std::string& uniformPropName,
		bool val
	);
	void setInt(
		const std::string& uniformPropName,
		int val
	);
	void setFloat(
		const std::string& uniformPropName,
		int val
	);
	void setVec2(
		const std::string& uniformPropName,
		const glm::vec2& val
	);
	void setVec3(
		const std::string& uniformPropName,
		const glm::vec3& val
	);
	void setVec4(
		const std::string& uniformPropName,
		const glm::vec4& val
	);
	void setMat2(
		const std::string& uniformPropName,
		const glm::mat2& val
	);
	void setMat3(
		const std::string& uniformPropName,
		const glm::mat3& val
	);
	void setMat4(
		const std::string& uniformPropName,
		const glm::mat4& val
	);
protected:
	void useShader();
	virtual void getUniform() = 0;
private:
	unsigned int compileShader(
		const char* source, 
		GLenum shaderType
	);
	unsigned int linkShader(
		unsigned int vertexShaderId, 
		unsigned int fragmentShaderId
	);
	void loadShader(
		const std::string& vertexShader,
		const std::string& fragmentShader
	);
	unsigned int m_shaderId;
};

