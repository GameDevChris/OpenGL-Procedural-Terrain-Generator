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
	float h1, h2, h3, h4, aver, h;
	float rand_max = 1; 

	int spacing = 2;

	float xPos;
	float zPos;

	float terrainAmplifier = 800;
	const static int vertexCount = 1025;

	float heights[vertexCount][vertexCount];
	int indices[6 * (vertexCount - 1) * (vertexCount - 1)];

	Vertex terrainVertices[vertexCount * vertexCount];

	unsigned int terrainIndices[vertexCount - 1][2 * vertexCount];

	float normals[(vertexCount * vertexCount) * 3];
	float textureCoords[(vertexCount * vertexCount) * 2];

	
	vector<string> texturePaths
	{
		"./Terrain/snow.jpg",
		"./Terrain/grass.jpg",
		"./Terrain/rock.jpg",
		"./Terrain/beach.jpg",
	};

	vector<unsigned int> textureIDs;

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

	void Generate();
	void CalculateHeights();
	void DiamondStep(int coord1, int coord2, int stepVal);
	void SquareStep(int coord1, int coord2, int stepVal);

public:
	float parentXPos;
	float parentZPos;

	Shader* myShader;
	Terrain(int XGrid, int ZGrid);
	void CreateTextures();
	void CreateBuffers();
	void BindTexturesOnUnits();
	void SetShaderProperties();
	void Draw();
};

