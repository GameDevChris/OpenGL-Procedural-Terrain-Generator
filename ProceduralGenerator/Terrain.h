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

	//int terrainWidth = 4;
	//int terrainHeight = 4;


	static const int chunkSize = 5;
	static const int stripCount = chunkSize - 1;

	static const int vertsPerStrip = 2 * chunkSize;

	unsigned int terrainIndexData[stripCount][vertsPerStrip];

	float terrain[chunkSize][chunkSize];

	Vertex terrainVertices[chunkSize * chunkSize];

	//float* vertices = 0;
	//int* indices = 0;

	//int total_vertices = (terrainWidth + 1) * (terrainHeight + 1);
	//
	//Ciwfvec2
	//
	//int numIndPerRow = terrainWidth * 2 + 2;
	//int numIndDegensReq = (terrainHeight - 1) * 2;
	//int total_indices = numIndPerRow * terrainHeight + numIndDegensReq;
	//
	//uint16_t* planeInd = new uint16_t[total_indices];
	//Vertex terrainVertices[vertexCount * vertexCount] = {};




	//const static int vertexCount = 5;
	//
	//float heights[vertexCount][vertexCount];
	//int indices[6 * (vertexCount - 1) * (vertexCount - 1)];
	//
	//Vertex terrainVertices[vertexCount * vertexCount] = {};
	//
	//const int stripCount = vertexCount - 1;
	//const int vertPerStrip = 2 * vertexCount;
	//unsigned int terrainIndices[vertexCount - 1][2 * vertexCount];
	//
	//
	//float vertices[(vertexCount * vertexCount) * 3];
	//
	//
	//float normals[(vertexCount * vertexCount) * 3];
	//float textureCoords[(vertexCount * vertexCount) * 2];
	

	float xPos;
	float zPos;
	string texture;

	//Buffer
	unsigned int VBO, VAO, EBO;

	unsigned int diffuseTexture;

	void Generate();
	int GetVertCount(int w, int h);
	int GetIndCount(int w, int h);

	float* GetVerts(int w, int h);
	int* GetInds(int w, int h);

public:

	Shader* myShader;
	Terrain(int XGrid, int ZGrid, string tex);
	void CreateTextures();
	void CreateBuffers();
	void RandomizeColour();
	void Draw();
};

