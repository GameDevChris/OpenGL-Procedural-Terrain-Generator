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
	float terrainAmplifier = 200;
	int heightDisplace = 0;
	const static int vertexCount = 1025;

	float heights[vertexCount][vertexCount];
	int indices[6 * (vertexCount - 1) * (vertexCount - 1)];

	Vertex terrainVertices[vertexCount * vertexCount];

	unsigned int terrainIndices[vertexCount - 1][2 * vertexCount];

	float normals[(vertexCount * vertexCount) * 3];
	float textureCoords[(vertexCount * vertexCount) * 2];


	float xPos;
	float zPos;
	
	vector<string> texturePaths
	{
		"./Terrain/leaves.jpg",
		"./Terrain/snow.jpg",
		"./Terrain/snowGrass.jpg",
		"./Terrain/grass.jpg",
		"./Terrain/grassRock.jpg",
		"./Terrain/rock.jpg",
		"./Terrain/desert.jpg",
		"./Terrain/beach.jpg",
	};

	
	unsigned int leavesTex;
	unsigned int snowTex;
	unsigned int snowGrassTex;
	unsigned int grassTex;
	unsigned int grassRockTex;
	unsigned int rockTex;
	unsigned int desertTex;
	unsigned int beachTex;

	//Buffer
	unsigned int VBO, VAO;

	unsigned int diffuseTexture;

	void Generate();
	void CalculateHeights();

public:

	Shader* myShader;
	Terrain(int XGrid, int ZGrid);
	void CreateTextures();
	void CreateBuffers();
	void SetShaderProperties();
	void RandomizeColour();
	void Draw();
};

