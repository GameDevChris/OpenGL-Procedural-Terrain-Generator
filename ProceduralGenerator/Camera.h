#pragma once
#include <glfw3.h>
#include <glm.hpp>

using namespace glm;

class Camera
{
private:
	static float mouseLastXPosition;
	static float mouseLastYPosition;
	static float yaw;
	static float pitch;

	static bool firstInput;

public:
	GLFWwindow* projectWindow;
	vec3 cameraPosition;
	vec3 cameraUp;

	static vec3 cameraFront;
	static float fov;

	Camera();

	static void Mouse(GLFWwindow* window, double xpos, double ypos);
	static void Scroll(GLFWwindow* window, double xoffset, double yoffset);
};

