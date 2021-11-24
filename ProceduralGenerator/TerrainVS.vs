#version 460 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 terrainNormals;

struct Material
{
vec4 ambRefl = vec4(1.0, 1.0, 1.0, 1.0);
vec4 difRefl = vec4(1.0, 1.0, 1.0, 1.0);
vec4 specRefl = vec4(1.0, 1.0, 1.0, 1.0);
vec4 emitCols = vec4(0.0, 0.0, 0.0, 1.0);
float shininess = 50.0f;
};

out vec4 RandomVec;

uniform mat3 normalMat;
uniform vec4 globAmb = vec4(0.2, 0.2, 0.2, 1.0);
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
    normalExport = normalize(normalMat * normalExport);

	//RandomVec = vec4(RandValueX, RandValueY, RandValueZ, RandValueW);

	gl_Position = projection * view * vec4(aPos, 1.0);
}