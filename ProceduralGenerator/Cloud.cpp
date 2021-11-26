#include "Cloud.h"

Cloud::Cloud(int XGrid, int ZGrid)
{
	xPos = XGrid - (vertexCount / 2);
	zPos = ZGrid - (vertexCount / 2);

	Generate();
}

void Cloud::Generate()
{
	for (int x = 0; x < vertexCount; x++)
	{
		for (int y = 0; y < vertexCount; y++)
		{
			heights[x][y] = 800;
		}
	}

	int i = 0;
	for (int x = 0; x < vertexCount; x++)
	{
		for (int y = 0; y < vertexCount; y++)
		{
			cloudVertices[i].coords.x = ((float)x * spacing) + xPos;
			cloudVertices[i].coords.y = heights[x][y];
			cloudVertices[i].coords.z = ((float)y * spacing) + zPos;
			cloudVertices[i].coords.w = 1.0;
			
			cloudVertices[i].normals.x = 0.0;
			cloudVertices[i].normals.y = 0.0;
			cloudVertices[i].normals.z = 0.0;

			srand(time(NULL));
			float randomVal = (rand() % 10) / 5.0 - 1.0;
			noise.SetSeed(randomVal);
			cloudVertices[i].noise = noise.GetNoise(cloudVertices[i].coords.x, cloudVertices[i].coords.y, cloudVertices[i].coords.z);

			i++;
		}
	}

	i = 0;
	for (int z = 0; z < vertexCount - 1; z++)
	{
		i = z * vertexCount;
		for (int x = 0; x < vertexCount * 2; x += 2)
		{
			cloudIndices[z][x] = i;
			i++;
		}
		for (int x = 1; x < vertexCount * 2 + 1; x += 2)
		{
			cloudIndices[z][x] = i;
			i++;
		}
	}
	 
	int index1, index2, index3;
	float dot_value;
	glm::vec3 Pt1, Pt2, Pt3, ttVec, edgeVec1, edgeVec2, norVec, upvec;
	upvec.x = 0.0; upvec.y = 1.0; upvec.z = 0.0;
	for (int z = 0; z < vertexCount - 1; z++)
	{
		for (int x = 0; x < (vertexCount * 2 - 2); x++)
		{
			index1 = cloudIndices[z][x];
			index2 = cloudIndices[z][x + 1];
			index3 = cloudIndices[z][x + 2];

			Pt1.x = cloudVertices[index1].coords.x;
			Pt1.y = cloudVertices[index1].coords.y;
			Pt1.z = cloudVertices[index1].coords.z;
					
			Pt2.x = cloudVertices[index2].coords.x;
			Pt2.y = cloudVertices[index2].coords.y;
			Pt2.z = cloudVertices[index2].coords.z;
				
			Pt3.x = cloudVertices[index3].coords.x;
			Pt3.y = cloudVertices[index3].coords.y;
			Pt3.z = cloudVertices[index3].coords.z;

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

			cloudVertices[index1].normals = norVec + cloudVertices[index1].normals;
			cloudVertices[index2].normals = norVec + cloudVertices[index2].normals;
			cloudVertices[index3].normals = norVec + cloudVertices[index3].normals;
		}
	}


	int total;
	total = vertexCount * vertexCount;
	for (i = 0; i < (total - 1); i++)
	{
		ttVec = cloudVertices[i].normals;
		norVec = normalize(ttVec);
		cloudVertices[i].normals = norVec;
	}

	float fTextureS = float(vertexCount) * 0.01f;
	float fTextureT = float(vertexCount) * 0.01f;
	i = 0;
	for (int y = 0; y < vertexCount; y++)
	{
		for (int x = 0; x < vertexCount; x++)
		{
			float fScaleC = float(x) / float(vertexCount - 1);
			float fScaleR = float(y) / float(vertexCount - 1);

			cloudVertices[i].texCoords = glm::vec2(fTextureS * fScaleC, fTextureT * fScaleR);

			i++;
		}
	}
}

void Cloud::CreateTextures()
{
	glGenTextures(1, &textureID);

	stbi_set_flip_vertically_on_load(false);
	int width, height, nrChannels;

	unsigned char* data = stbi_load(texturePath.c_str(), &width, &height, &nrChannels, 0);

	if (data)
	{
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
		std::cout << "Failed to load cloud texture " << std::endl;
	}

	stbi_image_free(data);

	BindTexturesOnUnits();
}

void Cloud::CreateBuffers()
{
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);

	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(cloudVertices), cloudVertices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, sizeof(cloudVertices[0]), 0);
	glEnableVertexAttribArray(0);

	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(cloudVertices[0]), (GLvoid*)sizeof(cloudVertices[0].coords));
	glEnableVertexAttribArray(1);

	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(cloudVertices[0]), (GLvoid*)(sizeof(cloudVertices[0].coords) + sizeof(cloudVertices[0].normals)));
	glEnableVertexAttribArray(2);

	glVertexAttribPointer(3, 1, GL_FLOAT, GL_FALSE, sizeof(cloudVertices[0]), (GLvoid*)(sizeof(cloudVertices[0].coords) + sizeof(cloudVertices[0].normals) + sizeof(cloudVertices[0].texCoords)));
	glEnableVertexAttribArray(3);
}

void Cloud::BindTexturesOnUnits()
{
	myShader->Use();
	myShader->SetInt("cloudTex", 5);

	glActiveTexture(GL_TEXTURE5);
	glBindTexture(GL_TEXTURE_2D, textureID);
}

void Cloud::SetShaderProperties()
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

void Cloud::Draw()
{
	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	BindTexturesOnUnits();

	glBindVertexArray(VAO);
	for (int i = 0; i < vertexCount - 1; i++)
	{
		glDrawElements(GL_TRIANGLE_STRIP, 2 * vertexCount, GL_UNSIGNED_INT, cloudIndices[i]);
	}
	glBindVertexArray(0);
}
