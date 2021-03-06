#include "Water.h"

Water::Water(int XGrid, int ZGrid)
{
	xPos = XGrid - (vertexCount / 2);
	zPos = ZGrid - (vertexCount / 2);

	Generate();
}

void Water::Generate()
{
	for (int x = 0; x < vertexCount; x++)
	{
		for (int y = 0; y < vertexCount; y++)
		{
			heights[x][y] = -30;
		}
	}

	int i = 0;
	for (int x = 0; x < vertexCount; x++)
	{
		for (int y = 0; y < vertexCount; y++)
		{
			waterVertices[i].coords.x = ((float)x * spacing) + xPos;
			waterVertices[i].coords.y = heights[x][y];
			waterVertices[i].coords.z = ((float)y * spacing) + zPos;
			waterVertices[i].coords.w = 1.0;
			
			waterVertices[i].normals.x = 0.0;
			waterVertices[i].normals.y = 0.0;
			waterVertices[i].normals.z = 0.0;


			i++;
		}
	}

	i = 0;
	for (int z = 0; z < vertexCount - 1; z++)
	{
		i = z * vertexCount;
		for (int x = 0; x < vertexCount * 2; x += 2)
		{
			waterIndices[z][x] = i;
			i++;
		}
		for (int x = 1; x < vertexCount * 2 + 1; x += 2)
		{
			waterIndices[z][x] = i;
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
			index1 = waterIndices[z][x];
			index2 = waterIndices[z][x + 1];
			index3 = waterIndices[z][x + 2];
					
			Pt1.x = waterVertices[index1].coords.x;
			Pt1.y = waterVertices[index1].coords.y;
			Pt1.z = waterVertices[index1].coords.z;
					
			Pt2.x = waterVertices[index2].coords.x;
			Pt2.y = waterVertices[index2].coords.y;
			Pt2.z = waterVertices[index2].coords.z;
				
			Pt3.x = waterVertices[index3].coords.x;
			Pt3.y = waterVertices[index3].coords.y;
			Pt3.z = waterVertices[index3].coords.z;

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

			waterVertices[index1].normals = norVec + waterVertices[index1].normals;
			waterVertices[index2].normals = norVec + waterVertices[index2].normals;
			waterVertices[index3].normals = norVec + waterVertices[index3].normals;
		}
	}


	int total;
	total = vertexCount * vertexCount;
	for (i = 0; i < (total - 1); i++)
	{
		ttVec = waterVertices[i].normals;
		norVec = normalize(ttVec);
		waterVertices[i].normals = norVec;
	}

	float fTextureS = float(vertexCount) * 0.05f;
	float fTextureT = float(vertexCount) * 0.05f;
	i = 0;
	for (int y = 0; y < vertexCount; y++)
	{
		for (int x = 0; x < vertexCount; x++)
		{
			float fScaleC = float(x) / float(vertexCount - 1);
			float fScaleR = float(y) / float(vertexCount - 1);

			waterVertices[i].texCoords = glm::vec2(fTextureS * fScaleC, fTextureT * fScaleR);

			i++;
		}
	}
}

void Water::CreateTextures()
{
	//Water
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
		std::cout << "Failed to load water texture " << std::endl;
	}

	stbi_image_free(data);


	//foam
	glGenTextures(1, &foamID);

	stbi_set_flip_vertically_on_load(false);
	int width2, height2, nrChannels2;

	unsigned char* data2 = stbi_load(foamPath.c_str(), &width2, &height2, &nrChannels2, 0);

	if (data2)
	{
		glBindTexture(GL_TEXTURE_2D, foamID);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width2, height2, 0, GL_RGB, GL_UNSIGNED_BYTE, data2);
		glGenerateMipmap(GL_TEXTURE_2D);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	}

	else
	{
		std::cout << "Failed to load foam texture " << std::endl;
	}

	stbi_image_free(data2);

	BindTexturesOnUnits();
}

void Water::CreateBuffers()
{
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);

	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(waterVertices), waterVertices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, sizeof(waterVertices[0]), 0);
	glEnableVertexAttribArray(0);

	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(waterVertices[0]), (GLvoid*)sizeof(waterVertices[0].coords));
	glEnableVertexAttribArray(1);

	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(waterVertices[0]), (GLvoid*)(sizeof(waterVertices[0].coords) + sizeof(waterVertices[0].normals)));
	glEnableVertexAttribArray(2);
}

void Water::BindTexturesOnUnits()
{
	myShader->Use();
	myShader->SetInt("waterTex", 4);

	glActiveTexture(GL_TEXTURE4);
	glBindTexture(GL_TEXTURE_2D, textureID);

	myShader->Use();
	myShader->SetInt("foamTex", 6);

	glActiveTexture(GL_TEXTURE6);
	glBindTexture(GL_TEXTURE_2D, foamID);
}

void Water::SetShaderProperties()
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

	myShader->setVec4("waveDirection", 3, 0, 1, 0);
	myShader->SetInt("waveAmount", 1);
	myShader->SetFloat("waveFrequency", 0.01);
	myShader->SetFloat("waveSpeed", 0.05);
	myShader->SetFloat("waveAmplitude", 15);
	myShader->SetFloat("crestDist", 0.1);
}

void Water::Draw()
{
	timeSinceStart = glfwGetTime();
	deltaTime = timeSinceStart - oldTimeSinceStart;
	oldTimeSinceStart = timeSinceStart;

	flowValue += deltaTime;

	waveDirValX += (deltaTime / 25)*waveDirXSign;
	
	if (!zFliping)
	{
		waveDirZCounter += (deltaTime / 10);

		if (waveDirZCounter > 10)
		{
			if (waveDirValZ == 1)
			{
				zFlipSign = -1;
			}

			else
			{
				zFlipSign = 1;
			}

			zFliping = true;
			waveDirZCounter = 0;
		}
	}

	else 
	{
		if (zFlipSign == 1) 
		{
			waveDirValZ += (deltaTime / 10);

			if (waveDirValZ > 1)
			{
				waveDirValZ = 1;
				zFliping = false;
			}

		}

		else
		{
			waveDirValZ -= (deltaTime / 10);

			if (waveDirValZ < -1)
			{
				waveDirValZ = -1;
				zFliping = false;
			}
		}
	}
	

	if (waveDirValX > 1)
	{
		waveDirXSign = -1;
	}

	if (waveDirValX < -1)
	{
		waveDirXSign = 1;
	}

	

	myShader->SetFloat("waveFlow", flowValue);
	myShader->setVec4("waveDirection", waveDirValX, 0, waveDirValZ, 0);

	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	BindTexturesOnUnits();

	glBindVertexArray(VAO);
	for (int i = 0; i < vertexCount - 1; i++)
	{
		glDrawElements(GL_TRIANGLE_STRIP, 2 * vertexCount, GL_UNSIGNED_INT, waterIndices[i]);
	}
	glBindVertexArray(0);
}
