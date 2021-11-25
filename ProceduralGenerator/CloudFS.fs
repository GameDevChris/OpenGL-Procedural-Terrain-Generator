#version 460 core
in vec3 normalExport;
out vec4 FragColor;
in vec2 texCoordsExport;
in float noise;

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

uniform sampler2D cloudTex;
vec4 textureMap;

void main()
{   
    textureMap = texture(cloudTex, texCoordsExport);

    if(noise > 0)
    {
        textureMap.a = 1.0;
    }

    else
    {
        textureMap.a = 0.0;
    }
    

    normal = normalize(normalExport);
    lightDirection = normalize(vec3(light0.coords));
    fAndBDif = max(dot(normal, lightDirection), 0.0f) * (light0.difCols *  terrainFandB.difRefl); 
    FragColor =  (vec4(vec3(min(fAndBDif, vec4(1.0))), 1.0)) * textureMap; 
  
}
