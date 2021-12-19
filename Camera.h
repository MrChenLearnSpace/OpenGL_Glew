#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
class Camera
{
public:
	Camera(glm::vec3 position, glm::vec3 target, glm::vec3 worldUp);
	Camera(glm::vec3 position, float pitch,float yaw, glm::vec3 worldUp);
	glm::vec3 Position;
	glm::vec3 Forward;
	glm::vec3 Right;
	glm::vec3 Up;
	glm::vec3 WorldUp;
	float Pitch;
	float Yaw;
	float MouseSensitivity=0.01f;
	float speedZ = 0, speedY = 0, speedX = 0;
	glm::mat4 GetViewMatrix();
	void ProcessMouseMovement(float xoffset, float yoffset);
	void updateCameraPos();
private:
    // calculates the front vector from the Camera's (updated) Euler Angles
    void updateCameraVectors();
    
};

