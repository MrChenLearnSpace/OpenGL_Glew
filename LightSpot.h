#pragma once
#include <glm/glm.hpp>
#include<glm/gtx/rotate_vector.hpp>
class LightSpot {
public:
	glm::vec3 position;
	glm::vec3 angles;
	glm::vec3 direction;
	glm::vec3 color;
	
	void UpdateDirection();
	float constant;
	float linear;
	float quadratic;
	float cosPhyInner = 0.9;
	float cosPhyOutter = 0.85;
	LightSpot(glm::vec3 _position, glm::vec3 _angles, glm::vec3 _color, float _constant = 1.0f, float _linear = 0.09f, float _quadratic = 0.032f);
};

