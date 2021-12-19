#include "LightSpot.h"

LightSpot::LightSpot(glm::vec3 _position, glm::vec3 _angles, glm::vec3 _color, float _constant, float _linear, float _quadratic) :
	position(_position),
	angles(_angles),
	color(_color),
	constant(_constant),
	linear(_linear),
	quadratic(_quadratic)
{
	UpdateDirection();
}

void LightSpot::UpdateDirection() {
	direction = glm::vec3(0.0f, 0.0f, 1.0f);
	direction = glm::rotateZ(direction, angles.z);
	direction = glm::rotateX(direction, angles.x);
	direction = glm::rotateY(direction, angles.y);
	direction *= -1.0f;
}
