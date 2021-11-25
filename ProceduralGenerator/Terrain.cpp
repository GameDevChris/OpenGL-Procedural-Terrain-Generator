#include "Terrain.h"

//const int Terrain::vertexCount;

Terrain::Terrain(int XGrid, int ZGrid)
{
	parentXPos = XGrid;
	parentZPos = ZGrid;

	xPos = XGrid - (vertexCount/2);
	zPos = ZGrid - (vertexCount/2);

	Generate();
}

void Terrain::CalculateHeights()
{
	float h1, h2, h3, h4, aver, h;

	//int seed = 13729327;
	//cout << "Input seed!" << endl;
	//cin >> seed;
	//srand(1);

	srand(time(NULL));
	h1 = (rand() % 10) / 5.0 - 1.0;
	h2 = (rand() % 10) / 5.0 - 1.0;
	h3 = (rand() % 10) / 5.0 - 1.0;
	h4 = (rand() % 10) / 5.0 - 1.0;


	heights[0][0] = h1 * terrainAmplifier;
	heights[vertexCount - 1][0] = h2 * terrainAmplifier;
	heights[vertexCount - 1][vertexCount - 1] = h3 * terrainAmplifier;
	heights[0][vertexCount - 1] = h4 * terrainAmplifier;

	//heights[0][0] = (float(rand()) / float((RAND_MAX)) * 5.0f);


	int step_size, tt, H, count;
	float rand_max;
	tt = vertexCount;
	step_size = tt - 1;
	H = 1;
	rand_max = 1;

	while (step_size > 1)
	{
		for (int x = 0; x < vertexCount - 1; x += step_size)

			for (int y = 0; y < vertexCount - 1; y += step_size)
			{
				//diamond_step(x, y, stepsize)
				h1 = heights[x][y];
				h2 = heights[x + step_size][y];
				h3 = heights[x][y + step_size];
				h4 = heights[x + step_size][y + step_size];
				aver = (h1 + h2 + h3 + h4) / 4.0;
				h = (rand() % 10) / 5.0 - 1.0;
				aver = aver + h * terrainAmplifier * rand_max;
				heights[x + step_size / 2][y + step_size / 2] = aver;
			}

		for (int x = 0; x < vertexCount - 1; x += step_size)
			for (int y = 0; y < vertexCount - 1; y += step_size)
			{
				//square_step(x, y)
				count = 0;
				h1 = heights[x][y];  count++;
				h2 = heights[x][y + step_size];  count++; //below
				if ((x - step_size / 2) >= 0) { h3 = heights[x - step_size / 2][y + step_size / 2]; count++; }
				else { h3 = 0.0; }
				if ((x + step_size / 2) < vertexCount) { h4 = heights[x + step_size / 2][y + step_size / 2]; count++; }
				else { h4 = 0.0; }
				aver = (h1 + h2 + h3 + h4) / (float)count;
				h = (rand() % 10) / 5.0 - 1.0;
				aver = aver + h * terrainAmplifier * rand_max;
				heights[x][y + step_size / 2] = aver;

				//second one
				count = 0;
				h1 = heights[x][y];  count++;
				h2 = heights[x + step_size][y];  count++; //below
				if ((y - step_size / 2) >= 0) { h3 = heights[x + step_size / 2][y - step_size / 2]; count++; }
				else { h3 = 0.0; }
				if ((y + step_size / 2) < vertexCount) { h4 = heights[x + step_size / 2][y + step_size / 2]; count++; }
				else { h4 = 0.0; }
				aver = (h1 + h2 + h3 + h4) / (float)count;
				h = (rand() % 10) / 5.0 - 1.0;
				aver = aver + h * terrainAmplifier * rand_max;
				heights[x + step_size / 2][y] = aver;

				//third one
				count = 0;
				h1 = heights[x + step_size][y];  count++;
				h2 = heights[x + step_size][y + step_size];  count++; //below
				h3 = heights[x + step_size / 2][y + step_size / 2]; count++;
				if ((x + 3 * step_size / 2) < vertexCount) { h4 = heights[x + 3 * step_size / 2][y + step_size / 2]; count++; }
				else { h4 = 0.0; }
				aver = (h1 + h2 + h3 + h4) / (float)count;
				h = (rand() % 10) / 5.0 - 1.0;
				aver = aver + h * terrainAmplifier * rand_max;
				heights[x + step_size][y + step_size / 2] = aver;

				//fourth one
				count = 0;
				h1 = heights[x][y + step_size];  count++;
				h2 = heights[x + step_size][y + step_size];  count++; //below
				h3 = heights[x + step_size / 2][y + step_size / 2]; count++;
				if ((y + 3 * step_size / 2) < vertexCount) { h4 = heights[x + step_size / 2][y + 3 * step_size / 2]; count++; }
				else { h4 = 0.0; }
				aver = (h1 + h2 + h3 + h4) / (float)count;
				h = (rand() % 10) / 5.0 - 1.0;
				aver = aver + h * terrainAmplifier * rand_max;
				heights[x + step_size / 2][y + step_size] = aver;
			}

		rand_max = rand_max * pow(2, -H);
		step_size = step_size / 2;
	}
	
}


void Terrain::Generate()
{
	for (int x = 0; x < vertexCount; x++)
	{
		for (int y = 0; y < vertexCount; y++)
		{
			heights[x][y] = 0;
		}
	}

	CalculateHeights();

	int i = 0;
	for (int x = 0; x < vertexCount; x++)
	{
		for (int y = 0; y < vertexCount; y++)
		{
			terrainVertices[i].coords.x = ((float)x * spacing) + xPos;
			terrainVertices[i].coords.y = heights[x][y];
			terrainVertices[i].coords.z = ((float)y * spacing) + zPos;
			terrainVertices[i].coords.w = 1.0;
			 
			terrainVertices[i].normals.x = 0.0;
			terrainVertices[i].normals.y = 0.0;
			terrainVertices[i].normals.z = 0.0;


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


	///compute normal vectors for each vertices
	int index1, index2, index3;
	float dot_value;
	glm::vec3 Pt1, Pt2, Pt3, ttVec, edgeVec1, edgeVec2, norVec, upvec;
	upvec.x = 0.0; upvec.y = 1.0; upvec.z = 0.0;
	for (int z = 0; z < vertexCount - 1; z++)
	{
		for (int x = 0; x < (vertexCount * 2 - 2); x++)
		{
			index1 = terrainIndices[z][x];
			index2 = terrainIndices[z][x + 1];
			index3 = terrainIndices[z][x + 2];

			Pt1.x = terrainVertices[index1].coords.x;
			Pt1.y = terrainVertices[index1].coords.y;
			Pt1.z = terrainVertices[index1].coords.z;

			Pt2.x = terrainVertices[index2].coords.x;
			Pt2.y = terrainVertices[index2].coords.y;
			Pt2.z = terrainVertices[index2].coords.z;

			Pt3.x = terrainVertices[index3].coords.x;
			Pt3.y = terrainVertices[index3].coords.y;
			Pt3.z = terrainVertices[index3].coords.z;

			edgeVec1 = Pt2 - Pt1;
			edgeVec2 = Pt3 - Pt1;
			if (x % 2 == 1)
				ttVec = cross(edgeVec2, edgeVec1);
			else
				ttVec = cross(edgeVec1, edgeVec2);

			dot_value = dot(ttVec, upvec);
			if (dot_value < 0.0000001)
				norVec = -ttVec;
			else
				norVec = ttVec;

			terrainVertices[index1].normals = norVec + terrainVertices[index1].normals;
			terrainVertices[index2].normals = norVec + terrainVertices[index2].normals;
			terrainVertices[index3].normals = norVec + terrainVertices[index3].normals;
		}
	}


	int total;
	total = vertexCount * vertexCount;
	for (i = 0; i < (total - 1); i++)
	{
		ttVec = terrainVertices[i].normals;
		norVec = normalize(ttVec);
		terrainVertices[i].normals = norVec;
	}

	float fTextureS = float(vertexCount) * 0.2f;
	float fTextureT = float(vertexCount) * 0.2f;
	i = 0;
	for (int y = 0; y < vertexCount; y++)
	{
		for (int x = 0; x < vertexCount; x++) 
		{
			float fScaleC = float(x) / float(vertexCount - 1);
			float fScaleR = float(y) / float(vertexCount - 1);

			terrainVertices[i].texCoords = glm::vec2(fTextureS * fScaleC, fTextureT * fScaleR);

			i++;
		}
	}


	cout << "Finished generating" << endl;
}

void Terrain::CreateTextures()
{
	for (int i = 0; i < texturePaths.size(); i++)
	{
		unsigned int textureID;
		glGenTextures(1, &textureID);

		stbi_set_flip_vertically_on_load(false);
		int width, height, nrChannels;

		unsigned char* data = stbi_load(texturePaths[i].c_str(), &width, &height, &nrChannels, 0);

		if (data)
		{
			cout << "Generated texture with path " << texturePaths[i].c_str() << endl;

			glBindTexture(GL_TEXTURE_2D, textureID);
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
			glGenerateMipmap(GL_TEXTURE_2D);

			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		}

		else
		{
			cout << "Failed to load texture " << i << endl;
		}

		stbi_image_free(data);

		textureIDs.push_back(textureID);
	}

	BindTexturesOnUnits();
}

void Terrain::CreateBuffers()
{
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);

	//Bind VAO & VBO
	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(terrainVertices), terrainVertices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, sizeof(terrainVertices[0]), 0);
	glEnableVertexAttribArray(0);

	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(terrainVertices[0]), (GLvoid*)sizeof(terrainVertices[0].coords));
	glEnableVertexAttribArray(1);

	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(terrainVertices[0]), (GLvoid*)(sizeof(terrainVertices[0].coords) + sizeof(terrainVertices[0].normals)));
	glEnableVertexAttribArray(2);

}

void Terrain::BindTexturesOnUnits()
{
	myShader->Use();
	myShader->SetInt("snowTex", 0);
	myShader->SetInt("grassTex", 1);
	myShader->SetInt("rockTex", 2);
	myShader->SetInt("beachTex", 3);


	
	for (int i = 0; i < textureIDs.size(); i++)
	{
		glActiveTexture(GL_TEXTURE0 + i);
		glBindTexture(GL_TEXTURE_2D, textureIDs[i]);
	}
}

void Terrain::SetShaderProperties()
{
	myShader->setVec4("terrainFandB.ambRefl", 1.0, 1.0, 1.0, 1.0);
	myShader->setVec4("terrainFandB.difRefl", 1.0, 1.0, 1.0, 1.0);
	myShader->setVec4("terrainFandB.specRefl", 1.0, 1.0, 1.0, 1.0);
	myShader->setVec4("terrainFandB.emitCols", 0.0, 0.0, 0.0, 1.0);
	myShader->SetFloat("terrainFandB.shininess", 50.0f);

	myShader->setVec4("light0.ambCols", 0.0, 0.0, 0.0, 1.0);
	myShader->setVec4("light0.difCols", 1.0, 1.0, 1.0, 1.0);
	myShader->setVec4("light0.specCols", 1.0, 1.0, 1.0, 1.0);
	myShader->setVec4("light0.coords", 1.0, 1.0, 0.0, 0.0);

	myShader->setVec4("globAmb", 0.2, 0.2, 0.2, 1.0);

	myShader->setVec4("overrideColour", 1, 1, 0, 1);
}



void Terrain::Draw()
{
	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	BindTexturesOnUnits();

	glBindVertexArray(VAO);
	for (int i = 0; i < vertexCount - 1; i++)
	{
		glDrawElements(GL_TRIANGLE_STRIP, 2 * vertexCount, GL_UNSIGNED_INT, terrainIndices[i]);
	}
	glBindVertexArray(0);
}
