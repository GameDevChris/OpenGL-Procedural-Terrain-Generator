#version 460 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 terrainNormals;

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

void main()
{
	normalExport = terrainNormals;
    normalExport = normalize(normalMat * normalExport);

	gl_Position = projection * view * vec4(aPos, 1.0);
}