#include "Camera.h"
float Camera::mouseLastXPosition;
float Camera::mouseLastYPosition;
float Camera::yaw;
float Camera::pitch;
float Camera::fov;
bool Camera::firstInput;
vec3 Camera::cameraFront;

Camera::Camera()
{
	mouseLastXPosition = 400;
	mouseLastYPosition = 300;

	yaw = -90.0f;
	pitch = 0.0f;
	fov = 60.0f;

	cameraPosition = vec3(0.0f, 500.0f, 0.0f);
	cameraFront = vec3(0.0f, 0.0f, -1.0f);
	cameraUp = vec3(0.0f, 1.0f, 0.0f);

	firstInput = true;
}

void Camera::Mouse(GLFWwindow* window, double xpos, double ypos)
{
	if (firstInput)
	{
		mouseLastXPosition = xpos;
		mouseLastYPosition = ypos;
		firstInput = false;
	}

	float DeltaX = xpos - mouseLastXPosition;
	float DeltaY = -ypos + mouseLastYPosition;
	mouseLastXPosition = xpos;
	mouseLastYPosition = ypos;

	const float sensitivity = 0.2f;
	DeltaX *= sensitivity;
	DeltaY *= sensitivity;

	yaw += DeltaX;

	pitch += DeltaY;
	if (pitch > 89.0f) { pitch = 89.0f; }
	if (pitch < -89.0f) { pitch = -89.0f; }

	vec3 direction;
	direction.x = cos(radians(yaw)) * cos(radians(pitch));
	direction.y = sin(radians(pitch));
	direction.z = sin(radians(yaw)) * cos(radians(pitch));
	cameraFront = normalize(direction);
}

void Camera::Scroll(GLFWwindow* window, double xoffset, double yoffset)
{
	if (fov > 1.0f && fov < 45.0f)
	{
		fov -= yoffset;
	}
		
	else if (fov <= 1.0f)
	{
		fov = 2.0f;
	}
		
	else if (fov >= 45.0f)
	{
		fov = 44.0f;
	}	
}
