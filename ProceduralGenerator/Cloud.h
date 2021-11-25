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

#include "FastNoiseLite.h"

class Cloud
{
private:

	int cloudSeed = 100;
	FastNoiseLite noise;

	int spacing = 2;

	const static int vertexCount = 1025;

	float heights[vertexCount][vertexCount];
	int indices[6 * (vertexCount - 1) * (vertexCount - 1)];

	Vertex cloudVertices[vertexCount * vertexCount];

	unsigned int cloudIndices[vertexCount - 1][2 * vertexCount];

	float normals[(vertexCount * vertexCount) * 3];
	float textureCoords[(vertexCount * vertexCount) * 2];

	float xPos;
	float zPos;

	std::string texturePath = "./Cloud/cloudTex.png";
	unsigned int textureID;

	//Buffer
	unsigned int VBO, VAO;

	void Generate();

public:
	Shader* myShader;
	Cloud(int XGrid, int ZGrid);
	void CreateTextures();
	void CreateBuffers();
	void BindTexturesOnUnits();
	void SetShaderProperties();
	void Draw();
};

