#version 460 core
layout (location = 0) in vec4 aPos;
layout (location = 1) in vec3 terrainNormals;
layout (location = 2) in vec2 terrainTexCoords;
layout (location = 3) in float noiseValue;

struct Material
{
vec4 ambRefl;
vec4 difRefl;
vec4 specRefl;
vec4 emitCols;
float shininess;
};

uniform mat3 normalMat;
uniform vec4 globAmb;
uniform mat4 view;
uniform mat4 projection;

out vec3 normalExport;
out vec2 texCoordsExport;
out float noise;

void main()
{
	noise = noiseValue;
	normalExport = terrainNormals;
    normalExport = normalize(normalMat * normalExport);
	texCoordsExport = terrainTexCoords;

	gl_Position = projection * view * aPos;
	
}