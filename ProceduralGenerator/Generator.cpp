#include "Generator.h"



Camera Generator::mainCamera;
Light Generator::mainLight(0,10,0);
Skybox* Generator::mainSkybox;

float Generator::deltaTime = 0.0f;
float Generator::lastFrame = 0.0f;
float Generator::cameraSpeed = 100.0f * deltaTime;
//float Generator::cameraSpeed = 10.0f;

void Generator::ResizeWindow(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}

void Generator::processInput(GLFWwindow* window)
{
	//Exit Game
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
	{
		glDeleteVertexArrays(1, &(mainSkybox->VAO));
		glDeleteBuffers(1, &(mainSkybox->VBO));
		delete mainSkybox;

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
}


void Generator::Awake()
{
	Grid.clear();

	cout << "Initialising generator" << endl;

	//Initialise GLFW
	glfwInit();

	//OpenGL version
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	//Set multisampling to 4 samples per fragment
	glfwWindowHint(GLFW_SAMPLES, 4);

	//Create window
	ProjectWindow = glfwCreateWindow(960, 540, "Epic Gamer Generator", NULL, NULL);

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

	//Build & Compile shader programs

	//Main engine shader
	//generatorShader = Shader("GeneratorVertex.vs", "GeneratorFragment.fs");
	//generatorShader.Start();

	//Skybox shader
	skyboxShader = Shader("ShaderVertex.vs", "ShaderFragment.fs");
	skyboxShader.Start();

	//Terrain shader
	terrainShader = Shader("TerrainVS.vs", "TerrainFS.fs");
	//terrainShader = Shader("ShaderVertex.vs", "ShaderFragment.fs");
	terrainShader.Start();
}

void Generator::Generate()
{

	//Create buffers, textures and model for skybox
	mainSkybox->CreateBuffers();
	mainSkybox->CreateTextures();

	for(int i = 0; i<Grid.size(); i++)
	{
		Grid[i]->CreateBuffers();
		Grid[i]->CreateTextures();
		Grid[i]->myShader = &terrainShader;

		Grid[i]->RandomizeColour();
	}

	//Set material properties in shader
	//generatorShader.SetInt("material.texture_diffuse", GL_TEXTURE0);
	//generatorShader.SetInt("material.texture_specular", GL_TEXTURE1);

}

void Generator::Start()
{
	cout << "Starting generator" << endl;

	while (!glfwWindowShouldClose(ProjectWindow))
	{
		Update();
	}
}

void Generator::Update()
{
	//generatorShader.Use();

	//Inputs
	processInput(ProjectWindow);

	//Time
	float currentFrame = glfwGetTime();
	deltaTime = currentFrame - lastFrame;
	lastFrame = currentFrame;

	//Render
	glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	//Setup view and projection matrix
	//generatorShader.Use();

	CreateTransforms();

	////Skybox
	glDepthFunc(GL_LEQUAL);
	skyboxShader.Use();
	viewMatrix = glm::mat4(glm::mat3(viewMatrix));
	skyboxShader.setMat4("view", viewMatrix);
	skyboxShader.setMat4("projection", projectionMatrix);
	mainSkybox->Draw();
	glDepthFunc(GL_LESS);

	//Terrain
	
	for(int i = 0; i<Grid.size(); i++)
	{
		glDepthFunc(GL_LEQUAL);
		Grid[i]->myShader->Use();
		viewMatrix = glm::mat4(glm::mat3(viewMatrix));
		Grid[i]->myShader->setMat4("view", viewMatrix);
		Grid[i]->myShader->setMat4("projection", projectionMatrix);
		Grid[i]->Draw();
		glDepthFunc(GL_LESS);
	}

	//Swap buffers & poll IO events
	glfwSwapBuffers(ProjectWindow);
	glfwPollEvents();
}

void Generator::CreateTransforms()
{
	terrainShader.Use();
	skyboxShader.Use();

	viewMatrix = lookAt(vec3(mainCamera.cameraPosition), vec3(mainCamera.cameraPosition + mainCamera.cameraFront), vec3(mainCamera.cameraUp));
	
	mat3 normalMat = mat3(1.0);
	normalMat = transpose(inverse(mat3(viewMatrix)));

	//mat3 test = mat3(vec3(1, 1, 1), vec3(0, 0, 0), vec3(0, 0, 0));

	//View Matrix
	terrainShader.setMat4("view", viewMatrix);
	terrainShader.setVec3("viewPos", mainCamera.cameraPosition.x, mainCamera.cameraPosition.y, mainCamera.cameraPosition.z);

	//generatorShader.setMat4("view", viewMatrix);
	//generatorShader.setVec3("viewPos", mainCamera.cameraPosition.x, mainCamera.cameraPosition.y, mainCamera.cameraPosition.z);

	skyboxShader.setMat4("view", viewMatrix);
	skyboxShader.setVec3("viewPos", mainCamera.cameraPosition.x, mainCamera.cameraPosition.y, mainCamera.cameraPosition.z);

	//Create Projection Matrix
	projectionMatrix = perspective(radians(mainCamera.fov), 960.0f / 540.0f, 0.1f, 200.0f);
	terrainShader.setMat4("projection", projectionMatrix);
	//generatorShader.setMat4("projection", projectionMatrix);
	skyboxShader.setMat4("projection", projectionMatrix);


	//Terrain Data
	terrainShader.setVec4("terrainFandB.ambRefl", 1.0, 1.0, 1.0, 1.0);
	terrainShader.setVec4("terrainFandB.difRefl", 1.0, 1.0, 1.0, 1.0);
	terrainShader.setVec4("terrainFandB.specRefl", 1.0, 1.0, 1.0, 1.0);
	terrainShader.setVec4("terrainFandB.emitCols", 0.0, 0.0, 0.0, 1.0);
	terrainShader.SetFloat("terrainFandB.shininess", 50.0f);

	terrainShader.setVec4("light0.ambCols", 0.0, 0.0, 0.0, 1.0);
	terrainShader.setVec4("light0.difCols", 1.0, 1.0, 1.0, 1.0);
	terrainShader.setVec4("light0.specCols", 1.0, 1.0, 1.0, 1.0);
	terrainShader.setVec4("light0.coords", 1.0, 10.0, 0.0, 0.0);

	terrainShader.setMat3("normalMat", normalMat);
	terrainShader.setVec4("globAmb", 0.2, 0.2, 0.2, 1.0);

	//terrainShader.setVec4("overrideColour", 1, 1, 0, 1);

	ColorHolder holder;
	holder.color = vec4(1, 1, 0, 1);

	glUniform4fv(glGetUniformLocation(terrainShader.ID, "overrideColour"), 1, &holder.color[0]);
}




void Generator::AddTerrain(Terrain* terrain)
{
	Grid.push_back(terrain);
}
