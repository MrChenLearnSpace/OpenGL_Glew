#include "LightPoint.h"

LightPoint::LightPoint(glm::vec3 _position, glm::vec3 _angles, glm::vec3 _color ,float _constant,float _linear,float _quadratic) :
	position(_position),
	angles(_angles),
	color(_color) ,
	constant(_constant),
	linear(_linear),
	quadratic(_quadratic){
	
}
