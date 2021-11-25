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
			"./trance/left.jpg",
			"./trance/right.jpg",	
			"./trance/top.jpg",
			"./trance/bot.jpg",
			"./trance/front.jpg",
			"./trance/back.jpg",
	};

	//Buffer
	unsigned int VBO, VAO;

	unsigned int diffuseTexture;

	void CreateTextures();
	void CreateBuffers();
	void Draw();
	Skybox();
};

