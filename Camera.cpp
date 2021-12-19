#include "Camera.h"
Camera::Camera(glm::vec3 position, glm::vec3 target, glm::vec3 worldUp){
	Position = position;
	WorldUp = worldUp;
	Forward = glm::normalize(target - position);
	Right = glm::normalize(glm::cross(Forward, WorldUp));
	Up = glm::normalize(glm::cross(Forward, Right));

}
Camera::Camera(glm::vec3 position, float pitch, float yaw, glm::vec3 worldUp){
	Position = position;
	WorldUp = worldUp;
	Pitch = pitch;
	Yaw = yaw;
	Forward.x = cos(Pitch) * sin(Yaw);
	Forward.y = sin(Pitch);
	Forward.z = cos(Pitch) * cos(Yaw);
	Right = glm::normalize(glm::cross(Forward, WorldUp));
	Up = glm::normalize(glm::cross(Right, Forward));
}
glm::mat4 Camera::GetViewMatrix() {
	return glm::lookAt(Position, Position + Forward, WorldUp);
}
void Camera::ProcessMouseMovement(float xoffset, float yoffset){
	

	Yaw += xoffset*MouseSensitivity;
	Pitch += yoffset*MouseSensitivity;
	updateCameraVectors();
}
void Camera:: updateCameraVectors(){
		// calculate the new Front vector
	Forward.x = cos(Pitch) * sin(Yaw);
	Forward.y = sin(Pitch);
	Forward.z = cos(Pitch) * cos(Yaw);
	Right = glm::normalize(glm::cross(Forward, WorldUp));
	Up = glm::normalize(glm::cross( Right,Forward));
}
void Camera::updateCameraPos() {
	Position += (Forward * speedZ+Right*speedX+Up*speedY )* 0.1f;
	
}
