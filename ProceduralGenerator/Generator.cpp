#include "Generator.h"

Camera Generator::mainCamera;
Skybox* Generator::mainSkybox;

float Generator::cameraSpeed = 10.0f;

void Generator::ResizeWindow(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}

void Generator::processInput(GLFWwindow* window)
{
	//Exit Game
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
	{
		glfwTerminate();
	}

	//Camera controls
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
	{
		mainCamera.cameraPosition += cameraSpeed * mainCamera.cameraFront;

	}

	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
	{
		mainCamera.cameraPosition -= cameraSpeed * mainCamera.cameraFront;
	}

	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
	{
		mainCamera.cameraPosition -= glm::normalize(glm::cross(mainCamera.cameraFront, mainCamera.cameraUp)) * cameraSpeed;
	}

	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
	{
		mainCamera.cameraPosition += glm::normalize(glm::cross(mainCamera.cameraFront, mainCamera.cameraUp)) * cameraSpeed;
	}

	if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)
	{
		mainCamera.cameraPosition += vec3(0, cameraSpeed, 0);
	}

	if (glfwGetKey(window, GLFW_KEY_LEFT_CONTROL) == GLFW_PRESS)
	{
		mainCamera.cameraPosition += vec3(0, -cameraSpeed, 0);
	}
}

void Generator::Awake()
{
	Grid.clear();
	WaterGrid.clear();

	//Initialise GLFW
	glfwInit();

	//OpenGL version
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	//Set multisampling to 4 samples per fragment
	glfwWindowHint(GLFW_SAMPLES, 4);

	//Create window
	ProjectWindow = glfwCreateWindow(screenWidth, screenHeight, "Chris Bodsworth - 322 - CW2", NULL, NULL);

	if (ProjectWindow == NULL)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
	}
	glfwMakeContextCurrent(ProjectWindow);

	//Set Callbacks for window resize, mouse and scroll wheel
	glfwSetFramebufferSizeCallback(ProjectWindow, ResizeWindow);
	glfwSetCursorPosCallback(ProjectWindow, mainCamera.Mouse);
	glfwSetScrollCallback(ProjectWindow, mainCamera.Scroll);

	//Capture mouse
	glfwSetInputMode(ProjectWindow, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

	//Load GLAD function pointers
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
	}

	//Enable multisampling and depth test
	glEnable(GL_MULTISAMPLE);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);


	//Build & Compile shader programs

	//Skybox shader
	skyboxShader = Shader("ShaderVertex.vs", "ShaderFragment.fs");
	skyboxShader.Start();

	//Terrain shader
	terrainShader = Shader("TerrainVS.vs", "TerrainFS.fs");
	terrainShader.Start();

	//Water shader
	waterShader = Shader("WaterVS.vs", "WaterFS.fs");
	waterShader.Start();

	//Cloud shader
	cloudShader = Shader("CloudVS.vs", "CloudFS.fs");
	cloudShader.Start();
}

void Generator::Generate()
{
	mainSkybox->CreateBuffers();
	mainSkybox->CreateTextures();

	for (int i = 0; i < WaterGrid.size(); i++)
	{
		WaterGrid[i]->myShader = &waterShader;
		WaterGrid[i]->CreateBuffers();
		WaterGrid[i]->CreateTextures();
	}

	for (int i = 0; i < CloudGrid.size(); i++)
	{
		CloudGrid[i]->myShader = &cloudShader;
		CloudGrid[i]->CreateBuffers();
		CloudGrid[i]->CreateTextures();
	}

	for(int i = 0; i<Grid.size(); i++)
	{
		Grid[i]->myShader = &terrainShader;
		Grid[i]->CreateBuffers();
		Grid[i]->CreateTextures();
	}
}

void Generator::Start()
{
	while (!glfwWindowShouldClose(ProjectWindow))
	{
		Update();
	}
}

void Generator::Update()
{
	//Inputs
	processInput(ProjectWindow);

	//Render
	glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	//Setup view and projection matrix
	CreateTransforms();

	//Skybox
	glDepthFunc(GL_LEQUAL);
	skyboxShader.Use();
	skyboxShader.setMat4("view", viewMatrix);
	skyboxShader.setMat4("projection", projectionMatrix);
	mainSkybox->Draw();
	glDepthFunc(GL_LESS);

	//Terrain
	for(int i = 0; i<Grid.size(); i++)
	{
		glDepthFunc(GL_LEQUAL);
		Grid[i]->myShader->Use();
		Grid[i]->myShader->setMat4("view", viewMatrix);
		Grid[i]->myShader->setMat3("normalMat", normalMat);
		Grid[i]->myShader->setMat4("projection", projectionMatrix);
		Grid[i]->SetShaderProperties();
		Grid[i]->Draw();
		glDepthFunc(GL_LESS);
	}

	//Water
	for (int i = 0; i < WaterGrid.size(); i++)
	{
		glDepthFunc(GL_LEQUAL);
		WaterGrid[i]->myShader->Use();
		WaterGrid[i]->myShader->setMat4("view", viewMatrix);
		WaterGrid[i]->myShader->setMat3("normalMat", normalMat);
		WaterGrid[i]->myShader->setMat4("projection", projectionMatrix);
		WaterGrid[i]->SetShaderProperties();
		WaterGrid[i]->Draw();
		glDepthFunc(GL_LESS);
	}
	
	//Cloud
	for (int i = 0; i < CloudGrid.size(); i++)
	{
		glDepthFunc(GL_LEQUAL);
		CloudGrid[i]->myShader->Use();
		CloudGrid[i]->myShader->setMat4("view", viewMatrix);
		CloudGrid[i]->myShader->setMat3("normalMat", normalMat);
		CloudGrid[i]->myShader->setMat4("projection", projectionMatrix);
		CloudGrid[i]->SetShaderProperties();
		CloudGrid[i]->Draw();
		glDepthFunc(GL_LESS);
	}

	//Swap buffers & poll IO events
	glfwSwapBuffers(ProjectWindow);
	glfwPollEvents();
}

void Generator::CreateTransforms()
{
	viewMatrix = mat4(1.0);
	viewMatrix = lookAt(mainCamera.cameraPosition, vec3(mainCamera.cameraPosition + mainCamera.cameraFront), vec3(mainCamera.cameraUp));
	
	projectionMatrix = glm::perspective(glm::radians(mainCamera.fov), (float)screenWidth / (float)screenHeight, 0.1f, 4000.0f);
	normalMat = transpose(inverse(mat3(viewMatrix)));
}

void Generator::AddTerrain(Terrain* terrain)
{
	Water* water = new Water(terrain->parentXPos, terrain->parentZPos);
	Cloud* cloud = new Cloud(terrain->parentXPos, terrain->parentZPos);

	CloudGrid.push_back(cloud);
	WaterGrid.push_back(water);
	Grid.push_back(terrain);
}
