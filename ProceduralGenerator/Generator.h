#pragma once
#include <glad.h> 
#include <glfw3.h>
#include <KHR/khrplatform.h>

#include <glm.hpp>
#include <gtc/matrix_transform.hpp>
#include <gtc/type_ptr.hpp>

#include <iostream>
#include <vector>

#include "Camera.h"
#include "Shader.h"
#include "Skybox.h"
#include "Terrain.h"

using namespace std;

class Generator
{
private:
	static Camera mainCamera;
	static float cameraSpeed;
	static float deltaTime;
	static float lastFrame;

	Shader generatorShader;
	Shader skyboxShader;
	Shader terrainShader;
	GLFWwindow* ProjectWindow;

	static void ResizeWindow(GLFWwindow* window, int width, int height);
	static void processInput(GLFWwindow* window);

public:
	mat4 viewMatrix = mat4(1.0f);
	mat4 projectionMatrix = mat4(1.0f);
	static Skybox* mainSkybox;

	Terrain* mainTerrain;
	vector<Terrain*> Grid;

	void Awake();
	void Generate();
	void Start();
	void Update();
	void CreateTransforms();
	void AddTerrain(Terrain* terrain);
};

