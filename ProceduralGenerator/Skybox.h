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
		-2000.0f,  2000.0f, -2000.0f,
		-2000.0f, -2000.0f, -2000.0f,
		 2000.0f, -2000.0f, -2000.0f,
		 2000.0f, -2000.0f, -2000.0f,
		 2000.0f,  2000.0f, -2000.0f,
		-2000.0f,  2000.0f, -2000.0f,
		
		-2000.0f, -2000.0f,  2000.0f,
		-2000.0f, -2000.0f, -2000.0f,
		-2000.0f,  2000.0f, -2000.0f,
		-2000.0f,  2000.0f, -2000.0f,
		-2000.0f,  2000.0f,  2000.0f,
		-2000.0f, -2000.0f,  2000.0f,
		
		 2000.0f, -2000.0f, -2000.0f,
		 2000.0f, -2000.0f,  2000.0f,
		 2000.0f,  2000.0f,  2000.0f,
		 2000.0f,  2000.0f,  2000.0f,
		 2000.0f,  2000.0f, -2000.0f,
		 2000.0f, -2000.0f, -2000.0f,
		
		-2000.0f, -2000.0f,  2000.0f,
		-2000.0f,  2000.0f,  2000.0f,
		 2000.0f,  2000.0f,  2000.0f,
		 2000.0f,  2000.0f,  2000.0f,
		 2000.0f, -2000.0f,  2000.0f,
		-2000.0f, -2000.0f,  2000.0f,
		
		-2000.0f,  2000.0f, -2000.0f,
		 2000.0f,  2000.0f, -2000.0f,
		 2000.0f,  2000.0f,  2000.0f,
		 2000.0f,  2000.0f,  2000.0f,
		-2000.0f,  2000.0f,  2000.0f,
		-2000.0f,  2000.0f, -2000.0f,
	
		-2000.0f, -2000.0f, -2000.0f,
		-2000.0f, -2000.0f,  2000.0f,
		 2000.0f, -2000.0f, -2000.0f,
		 2000.0f, -2000.0f, -2000.0f,
		-2000.0f, -2000.0f,  2000.0f,
		 2000.0f, -2000.0f,  2000.0f
	};

	vector<string> faces
	{
			"./Skybox/left.jpg",
			"./Skybox/right.jpg",	
			"./Skybox/top.jpg",
			"./Skybox/bot.jpg",
			"./Skybox/front.jpg",
			"./Skybox/back.jpg",
	};

	//Buffer
	unsigned int VBO, VAO;

	unsigned int diffuseTexture;

	void CreateTextures();
	void CreateBuffers();
	void Draw();
	Skybox();
};

