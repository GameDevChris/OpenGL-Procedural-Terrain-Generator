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
	const static int vertexCount = 5;

	float heights[vertexCount][vertexCount];
	int indices[6 * (vertexCount - 1) * (vertexCount - 1)];

	Vertex terrainVertices[vertexCount * vertexCount] = {};

	const int stripCount = vertexCount - 1;
	const int vertPerStrip = 2 * vertexCount;
	unsigned int terrainIndices[vertexCount - 1][2 * vertexCount];


	float vertices[(vertexCount * vertexCount) * 3];
	

	float normals[(vertexCount * vertexCount) * 3];
	float textureCoords[(vertexCount * vertexCount) * 2];
	

	float xPos;
	float zPos;
	string texture;

	//Buffer
	unsigned int VBO, VAO, EBO;

	unsigned int diffuseTexture;

	void GenerateVerts();

public:

	Shader* myShader;
	Terrain(int XGrid, int ZGrid, string tex);
	void CreateTextures();
	void CreateBuffers();
	void RandomizeColour();
	void Draw();
};

