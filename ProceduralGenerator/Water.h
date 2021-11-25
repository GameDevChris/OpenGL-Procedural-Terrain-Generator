#pragma once
#include <glad.h> ;
#include <glfw3.h>;
#include "stb_image.h";

#include <glm.hpp>;
#include <gtc/matrix_transform.hpp>;
#include <gtc/type_ptr.hpp>;

#include "Shader.h";
#include <iostream>;
#include <vector>;
#include <time.h>
#include "Vertex.h"

class Water
{
private:
	float oldTimeSinceStart = 0;
	float timeSinceStart = 0;
	float deltaTime = 0;

	int spacing = 2;

	const static int vertexCount = 1025;

	float heights[vertexCount][vertexCount];
	int indices[6 * (vertexCount - 1) * (vertexCount - 1)];

	Vertex waterVertices[vertexCount * vertexCount];

	unsigned int waterIndices[vertexCount - 1][2 * vertexCount];

	float normals[(vertexCount * vertexCount) * 3];
	float textureCoords[(vertexCount * vertexCount) * 2];

	float xPos;
	float zPos;

	std::string texturePath = "./Water/waterTex.jpg";
	unsigned int textureID;

	//Buffer
	unsigned int VBO, VAO;

	float flowValue = 0.0f;

	void Generate();

public:
	Shader* myShader;
	Water(int XGrid, int ZGrid);
	void CreateTextures();
	void CreateBuffers();
	void BindTexturesOnUnits();
	void SetShaderProperties();
	void Draw();
};

