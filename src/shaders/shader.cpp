#include "shader.h"
#include "../utility/fileUtil.h"
#include <GL/glew.h>
Shader::Shader(
	const std::string& vertexShader,
	const std::string& fragmentShader
) {
	loadShader(
		vertexShader,
		fragmentShader
	);
	useShader();
}
Shader::~Shader() {
	glDeleteProgram(m_shaderId);
}
void Shader::useShader() {
	glUseProgram(m_shaderId);
}
void Shader::setBool(
	const std::string& uniformPropName,
	bool val
) {
	glUniform1i(
		glGetUniformLocation(
			m_shaderId, 
			uniformPropName.c_str()
		), 
		val
	);
}
void Shader::setInt(
	const std::string& uniformPropName,
	int val
) {
	glUniform1i(
		glGetUniformLocation(
			m_shaderId,
			uniformPropName.c_str()
		),
		val
	);
}
void Shader::setFloat(
	const std::string& uniformPropName,
	int val
) {
	glUniform1f(
		glGetUniformLocation(
			m_shaderId,
			uniformPropName.c_str()
		),
		val
	);
}
void Shader::setVec2(
	const std::string& uniformPropName,
	const glm::vec2& val
) {
	glUniform2fv(
		glGetUniformLocation(
			m_shaderId,
			uniformPropName.c_str()
		),
		1,
		&val[0]
	);
}
void Shader::setVec3(
	const std::string& uniformPropName,
	const glm::vec3& val
) {
	glUniform3fv(
		glGetUniformLocation(
			m_shaderId,
			uniformPropName.c_str()
		),
		1,
		&val[0]
	);
}
void Shader::setVec4(
	const std::string& uniformPropName,
	const glm::vec4& val
) {
	glUniform4fv(
		glGetUniformLocation(
			m_shaderId,
			uniformPropName.c_str()
		),
		1,
		&val[0]
	);
}
void Shader::setMat2(
	const std::string& uniformPropName,
	const glm::mat2& val
) {
	glUniformMatrix2fv(
		glGetUniformLocation(
			m_shaderId,
			uniformPropName.c_str()
		),
		1,
		GL_FALSE,
		&val[0][0]
	);
}
void Shader::setMat3(
	const std::string& uniformPropName,
	const glm::mat3& val
) {
	glUniformMatrix3fv(
		glGetUniformLocation(
			m_shaderId,
			uniformPropName.c_str()
		),
		1,
		GL_FALSE,
		&val[0][0]
	);
}
void Shader::setMat4(
	const std::string& uniformPropName,
	const glm::mat4& val
) {
	glUniformMatrix4fv(
		glGetUniformLocation(
			m_shaderId,
			uniformPropName.c_str()
		),
		1,
		GL_FALSE,
		&val[0][0]
	);
}
unsigned int Shader::compileShader(
	const char* source,
	GLenum shaderType
) {
	unsigned int shaderId = glCreateShader(shaderType);
	glShaderSource(
		shaderId,
		1,
		&source,
		nullptr
	);
	glCompileShader(shaderId);
	int isSuccess = 0;
	char infoLog[512];
	glGetShaderiv(
		shaderId, 
		GL_COMPILE_STATUS, 
		&isSuccess
	);
	if (!isSuccess) {
		glGetShaderInfoLog(
			shaderId,
			512,
			nullptr,
			infoLog
		);
		std::cout << "Failed to compile shader::"<< infoLog << std::endl;
	}
	return shaderId;
}
unsigned int Shader::linkShader(
	unsigned int vertexShaderId,
	unsigned int fragmentShaderId
) {
	unsigned int linkerId = glCreateProgram();
	glAttachShader(
		linkerId, 
		vertexShaderId
	);
	glAttachShader(
		linkerId,
		fragmentShaderId
	);
	glLinkProgram(linkerId);
	return linkerId;
}
void Shader::loadShader(
	const std::string& vertexShader,
	const std::string& fragmentShader
) {
	unsigned int vertexShaderId = compileShader(
		getFileContent("src/shaders/glsl/" + vertexShader + ".vert").c_str(),
		GL_VERTEX_SHADER
	);
	unsigned int fragmentShaderId = compileShader(
		getFileContent("src/shaders/glsl/" + fragmentShader + ".frag").c_str(),
		GL_FRAGMENT_SHADER
	);
	m_shaderId = linkShader(
		vertexShaderId,
		fragmentShaderId
	);
	glDeleteShader(vertexShaderId);
	glDeleteShader(fragmentShaderId);
}
