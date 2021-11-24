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

out vec4 RandomVec;

uniform mat3 normalMat;
uniform vec4 globAmb;
uniform mat4 view;
uniform mat4 projection;

uniform float RandValueX;
uniform float RandValueY;
uniform float RandValueZ;
uniform float RandValueW;

out vec3 normalExport;

void main()
{
	normalExport = terrainNormals;
    //normalExport = normalize(normalMat * normalExport);

	normalExport = normalize(mat3(vec3(1, 1, 1), vec3(0, 0, 0), vec3(0, 0, 0)) * normalExport);

	//RandomVec = vec4(RandValueX, RandValueY, RandValueZ, RandValueW);

	gl_Position = projection * view * vec4(aPos, 1.0);
}