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

uniform mat3 normalMat;
uniform vec4 globAmb;
uniform mat4 view;
uniform mat4 projection;

out vec3 normalExport;
out vec2 texCoordsExport;

uniform vec4 waveDirection;
uniform int waveAmount;
uniform float waveFrequency;
uniform float waveSpeed;
uniform float waveAmplitude;
uniform float crestDist;
uniform float waveFlow;

void main()
{
	float dirSup = sqrt(9.81 * 2 * 3.14159265 / crestDist);
	vec4 dirAmp = (waveDirection/dirSup) * waveAmplitude;
	
	float phi = waveSpeed * 2/crestDist;
	
	vec4 updatedPos = aPos;
	
	vec4 hFormula = dirAmp*(-1) * sin((dot(waveDirection, aPos) * waveFrequency) - (phi * waveFlow));

	updatedPos.x += hFormula.x; 
	updatedPos.z += hFormula.z;
	updatedPos.y += waveAmplitude * cos((dot(waveDirection, aPos) * waveFrequency) - (phi * waveFlow));


	normalExport = terrainNormals;
    normalExport = normalize(normalMat * normalExport);
	texCoordsExport = terrainTexCoords;

	gl_Position = projection * view * updatedPos;
	
}