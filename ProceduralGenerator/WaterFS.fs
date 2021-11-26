#version 460 core
in vec3 normalExport;
out vec4 FragColor;
in vec2 texCoordsExport;
in float yValue;

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

uniform sampler2D waterTex;
uniform sampler2D foamTex;

vec4 textureMap;

void main()
{   
    if(yValue > -14)
    {
        textureMap = mix(texture(foamTex, texCoordsExport), texture(waterTex, texCoordsExport), 0.5);
        textureMap.a = 0.8;
    }


    else if(yValue > -15.5)
    {
        textureMap = mix(texture(foamTex, texCoordsExport), texture(waterTex, texCoordsExport), 0.8);
        textureMap.a = 0.8;
    }

    else
    {
        textureMap = texture(waterTex, texCoordsExport);
        textureMap.a = 0.8;
    }

    normal = normalize(normalExport);
    lightDirection = normalize(vec3(light0.coords));
    fAndBDif = max(dot(normal, lightDirection), 0.0f) * (light0.difCols *  terrainFandB.difRefl); 
    FragColor =  (vec4(vec3(min(fAndBDif, vec4(1.0))), 1.0)) * textureMap; 
  
}
