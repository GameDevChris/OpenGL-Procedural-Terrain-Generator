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

using namespace std;

class Terrain
{
private:
	int heightDisplace = -5;
	const static int vertexCount = 20;

	float heights[vertexCount][vertexCount];
	int indices[6 * (vertexCount - 1) * (vertexCount - 1)];

	Vertex terrainVertices[vertexCount * vertexCount];

	unsigned int terrainIndices[vertexCount - 1][2 * vertexCount];

	float normals[(vertexCount * vertexCount) * 3];
	float textureCoords[(vertexCount * vertexCount) * 2];


	float xPos;
	float zPos;
	string texture;

	//Buffer
	unsigned int VBO, VAO;

	unsigned int diffuseTexture;

	void Generate();
	void CalculateHeights();

public:

	Shader* myShader;
	Terrain(int XGrid, int ZGrid, string tex);
	void CreateTextures();
	void CreateBuffers();
	void RandomizeColour();
	void Draw();
};

