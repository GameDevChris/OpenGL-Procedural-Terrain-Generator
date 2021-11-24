#pragma once
#include <glad.h> ;
#include <glfw3.h>;
#include "stb_image.h";

#include <glm.hpp>;
#include <gtc/matrix_transform.hpp>;
#include <gtc/type_ptr.hpp>;

#include <iostream>;
#include <vector>;

using namespace std;

class Skybox
{
public:
	float skyboxVertices[108] = 
	{
		-500.0f,  500.0f, -500.0f,
		-500.0f, -500.0f, -500.0f,
		 500.0f, -500.0f, -500.0f,
		 500.0f, -500.0f, -500.0f,
		 500.0f,  500.0f, -500.0f,
		-500.0f,  500.0f, -500.0f,
		
		-500.0f, -500.0f,  500.0f,
		-500.0f, -500.0f, -500.0f,
		-500.0f,  500.0f, -500.0f,
		-500.0f,  500.0f, -500.0f,
		-500.0f,  500.0f,  500.0f,
		-500.0f, -500.0f,  500.0f,
		
		 500.0f, -500.0f, -500.0f,
		 500.0f, -500.0f,  500.0f,
		 500.0f,  500.0f,  500.0f,
		 500.0f,  500.0f,  500.0f,
		 500.0f,  500.0f, -500.0f,
		 500.0f, -500.0f, -500.0f,
	
		-500.0f, -500.0f,  500.0f,
		-500.0f,  500.0f,  500.0f,
		 500.0f,  500.0f,  500.0f,
		 500.0f,  500.0f,  500.0f,
		 500.0f, -500.0f,  500.0f,
		-500.0f, -500.0f,  500.0f,
	
		-500.0f,  500.0f, -500.0f,
		 500.0f,  500.0f, -500.0f,
		 500.0f,  500.0f,  500.0f,
		 500.0f,  500.0f,  500.0f,
		-500.0f,  500.0f,  500.0f,
		-500.0f,  500.0f, -500.0f,
		
		-500.0f, -500.0f, -500.0f,
		-500.0f, -500.0f,  500.0f,
		 500.0f, -500.0f, -500.0f,
		 500.0f, -500.0f, -500.0f,
		-500.0f, -500.0f,  500.0f,
		 500.0f, -500.0f,  500.0f
	};

	vector<string> faces
	{
			"./lightblue/right.png",
			"./lightblue/left.png",
			"./lightblue/top.png",
			"./lightblue/bot.png",
			"./lightblue/front.png",
			"./lightblue/back.png",
	};

	//Buffer
	unsigned int VBO, VAO;

	unsigned int diffuseTexture;

	void CreateTextures();
	void CreateBuffers();
	void Draw();
	Skybox();
};

