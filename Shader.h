#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include<string>
class Shader
{
public:
	Shader(const char* vertexPath,const char* fragmentPath);
	std::string vertexString;
	std::string fragmentString;
	const char* vertexSource;
	const char* fragmentSource;
	unsigned int ID;
	enum Slot {
		DIFFUSE,
		SPECULAR,
		EMISSION
	};
	void use();
	void SetUniform3f(const char* paramNameString, glm::vec3 param);
	void SetUniform1f(const char* paramNameString, float param);
	void SetUniform1i(const char* paramNameString, unsigned int slot);

private:
	void checkCompileErrors(unsigned int ID, std::string type);
};

