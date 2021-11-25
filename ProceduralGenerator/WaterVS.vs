#version 460 core
layout (location = 0) in vec4 aPos;
layout (location = 1) in vec3 terrainNormals;
layout (location = 2) in vec2 terrainTexCoords;

struct Material
{
vec4 ambRefl;
vec4 difRefl;
vec4 specRefl;
vec4 emitCols;
float shininess;
};

uniform float waveFlow;
uniform mat3 normalMat;
uniform vec4 globAmb;
uniform mat4 view;
uniform mat4 projection;

out vec3 normalExport;
out vec2 texCoordsExport;

void main()
{
	vec4 updatedPos = aPos;

	updatedPos.y += 1.0f * (sin(aPos.x + waveFlow) + cos(aPos.z + waveFlow)) + 1.0f;

	normalExport = terrainNormals;
    normalExport = normalize(normalMat * normalExport);
	texCoordsExport = terrainTexCoords;

	gl_Position = projection * view * updatedPos;
	
}