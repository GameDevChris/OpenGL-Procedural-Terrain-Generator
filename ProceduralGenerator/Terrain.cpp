#include "Terrain.h"

//const int Terrain::vertexCount;

Terrain::Terrain(int XGrid, int ZGrid, string tex)
{
	texture = tex;
	xPos = XGrid;
	zPos = ZGrid;

	Generate();
}

void Terrain::CalculateHeights()
{
	float h1, h2, h3, h4;

	int seed;

	h1 = (rand() % 10) / 5.0 - 1.0;
	h2 = (rand() % 10) / 5.0 - 1.0;
	h3 = (rand() % 10) / 5.0 - 1.0;
	h4 = (rand() % 10) / 5.0 - 1.0;


	heights[0][0] = h1 * 10.0;
	heights[vertexCount - 1][0] = h2 * 10.0;
	heights[vertexCount - 1][vertexCount - 1] = h3 * 10.0;
	heights[0][vertexCount - 1] = h4 * 10.0;
}

void Terrain::Generate()
{
	for (int x = 0; x < vertexCount; x++)
	{
		for (int y = 0; y < vertexCount; y++)
		{
			heights[x][y] = -5;
		}
	}

	CalculateHeights();

	int i = 0;
	for (int x = 0; x < vertexCount; x++)
	{
		for (int y = 0; y < vertexCount; y++)
		{
			terrainVertices[i].coords[0] = (float)x;
			terrainVertices[i].coords[1] = heights[x][y];
			terrainVertices[i].coords[2] = (float)y;
			terrainVertices[i].coords[3] = 1.0;

			terrainVertices[i].colors[0] = 0.0;
			terrainVertices[i].colors[1] = 0.0;
			terrainVertices[i].colors[2] = 0.0;
			terrainVertices[i].colors[3] = 1.0;

			i++;
		}
	}

	i = 0;
	for (int z = 0; z < vertexCount - 1; z++)
	{
		i = z * vertexCount;
		for (int x = 0; x < vertexCount * 2; x += 2)
		{
			terrainIndices[z][x] = i;
			i++;
		}
		for (int x = 1; x < vertexCount * 2 + 1; x += 2)
		{
			terrainIndices[z][x] = i;
			i++;
		}
	}

	i = 0;
	for(int x = 0; x< (vertexCount * vertexCount) * 3; x+=3)
	{
		vertices[x] = terrainVertices[i].coords[0];
		vertices[x+1] = terrainVertices[i].coords[1];
		vertices[x+2] = terrainVertices[i].coords[2];

		i++;
	}

	cout << "Finished generating" << endl;
}

void Terrain::CreateTextures()
{
	unsigned int textureID;
	glGenTextures(1, &textureID);

	stbi_set_flip_vertically_on_load(false);
	int width, height, nrChannels;
	
	cout << "Loading plane face " << endl;
	unsigned char* data = stbi_load(texture.c_str(), &width, &height, &nrChannels, 0);
	if (data)
	{
		cout << "it workie " << endl;

		glBindTexture(GL_TEXTURE_2D, diffuseTexture);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	}

	else
	{
		cout << "It no workie" << endl;
	}

	stbi_image_free(data);

	diffuseTexture = textureID;
}

void Terrain::CreateBuffers()
{
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);

	//Bind VAO & VBO
	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);

	glEnableVertexAttribArray(0);

}

void Terrain::RandomizeColour()
{
	myShader->Use();

	srand(time(NULL));
	float randomValX = rand() % 100 + 1;
	cout << "Random value X is " << randomValX << endl;
	myShader->SetFloat("RandValueX", randomValX / 100);

	srand(time(NULL));
	float randomValY = rand() % 50 + 1;
	cout << "Random value Y is " << randomValY << endl;
	myShader->SetFloat("RandValueY", randomValY / 100);

	srand(time(NULL));
	float randomValZ = rand() % 10 + 1;
	cout << "Random value Z is " << randomValZ << endl;
	myShader->SetFloat("RandValueZ", randomValZ / 100);

	srand(time(NULL));
	float randomValW = rand() % 20 + 1;
	cout << "Random value W is " << randomValW << endl;
	myShader->SetFloat("RandValueW", randomValW / 100);
}

void Terrain::Draw()
{
	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	glBindTexture(GL_TEXTURE_2D, diffuseTexture);
	glActiveTexture(GL_TEXTURE0);

	glBindVertexArray(VAO);


	for (int i = 0; i < vertexCount - 1; i++)
	{
		glDrawElements(GL_TRIANGLE_STRIP, 2 * vertexCount, GL_UNSIGNED_INT, terrainIndices[i]);
	}

	glBindVertexArray(0);
}
