#pragma once
#include <glad.h> 
#include <glfw3.h>

#include <glm.hpp>
#include <gtc/matrix_transform.hpp>
#include <gtc/type_ptr.hpp>

#include <iostream>
#include <vector>

#include "Camera.h"
#include "Shader.h"
#include "Skybox.h"
#include "Terrain.h"
#include "Cloud.h"
#include "Water.h"

using namespace std;

class Generator
{
private:
	static Camera mainCamera;
	static float cameraSpeed;

	int screenWidth = 1920;
	int screenHeight = 1080;

	Shader skyboxShader;
	Shader terrainShader;
	Shader waterShader;
	Shader cloudShader;

	GLFWwindow* ProjectWindow;

	static void ResizeWindow(GLFWwindow* window, int width, int height);
	static void processInput(GLFWwindow* window);

public:
	mat3 normalMat = mat3(1.0);
	mat4 viewMatrix = mat4(1.0);
	mat4 projectionMatrix = mat4(1.0f);

	static Skybox* mainSkybox;

	vector<Cloud*> CloudGrid;
	vector<Water*> WaterGrid;
	vector<Terrain*> Grid;

	void Awake();
	void Generate();
	void Start();
	void Update();
	void CreateTransforms();
	void AddTerrain(Terrain* terrain);
};

