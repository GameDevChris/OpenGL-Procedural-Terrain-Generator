#version 460 core

in vec3 normalExport;
out vec4 FragColor;
in vec4 RandomVec;

struct Light
{
   vec4 ambCols;
   vec4 difCols;
   vec4 specCols;
   vec4 coords;
};
uniform Light light0;

uniform vec4 globAmb;

struct Material
{
 vec4 ambRefl;
 vec4 difRefl;
 vec4 specRefl;
 vec4 emitCols;
 float shininess;
};
uniform Material terrainFandB;
uniform vec4 overrideColour;
vec3 normal, lightDirection;
vec4 fAndBDif;

uniform Sampler2D leavesTex;
uniform Sampler2D snowTex;
uniform Sampler2D snowGrassTex;
uniform Sampler2D grassTex;
uniform Sampler2D grassRockTex;
uniform Sampler2D rockTex;
uniform Sampler2D desertTex;
uniform Sampler2D beachTex;

void main()
{   
    normal = normalize(normalExport);
    lightDirection = normalize(vec3(light0.coords));
    fAndBDif = max(dot(normal, lightDirection), 0.0f) * (light0.difCols *  terrainFandB.difRefl); 
    FragColor =  vec4(vec3(min(fAndBDif, vec4(1.0))), 1.0); 
}
