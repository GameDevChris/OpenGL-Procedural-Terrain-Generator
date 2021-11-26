#pragma once
#include <glm.hpp>

struct Vertex
{
	glm::vec4 coords;
	glm::vec3 normals;
	glm::vec2 texCoords;
	float noise;
};