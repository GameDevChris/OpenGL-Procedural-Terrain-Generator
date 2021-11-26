#version 460 core
in vec3 normalExport;
out vec4 FragColor;

in vec2 texCoordsExport;

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

in float yValue;
float snowLevel = 250.0f; float snowTopBlendLevel = 245.0f; float snowMidBlendLevel = 235.0f; float snowBotBlendLevel = 225.0f;
float grassLevel = 100; float grassTopBlendLevel = 95; float grassMidBlendLevel = 85; float grassBotBlendLevel = 75;
float rockLevel = 0; float rockTopBlendLevel = -5; float rockMidBlendLevel = -15; float rockBotBlendLevel = -25;
float topBlendFactor = 0.3f; float midBlendFactor = 0.5f; float botBlendFactor = 0.7f;

uniform sampler2D snowTex; uniform sampler2D grassTex; uniform sampler2D rockTex; uniform sampler2D beachTex;

vec4 textureMap;

void main()
{   
    if(yValue > snowLevel){textureMap = texture(snowTex, texCoordsExport);}

    else if(yValue > snowTopBlendLevel){textureMap = mix(texture(snowTex, texCoordsExport), texture(grassTex, texCoordsExport), topBlendFactor);}

    else if(yValue > snowMidBlendLevel){textureMap = mix(texture(snowTex, texCoordsExport), texture(grassTex, texCoordsExport), midBlendFactor);}

    else if(yValue > snowBotBlendLevel){textureMap = mix(texture(snowTex, texCoordsExport), texture(grassTex, texCoordsExport), botBlendFactor);}

    else if(yValue > grassLevel){textureMap = texture(grassTex, texCoordsExport);}

    else if(yValue > grassTopBlendLevel) {textureMap = mix(texture(grassTex, texCoordsExport), texture(rockTex, texCoordsExport), topBlendFactor);}

    else if(yValue > grassMidBlendLevel){textureMap = mix(texture(grassTex, texCoordsExport), texture(rockTex, texCoordsExport), midBlendFactor);}

    else if(yValue > grassBotBlendLevel){textureMap = mix(texture(grassTex, texCoordsExport), texture(rockTex, texCoordsExport), botBlendFactor);}

    else if(yValue > rockLevel){textureMap = texture(rockTex, texCoordsExport);}

    else if(yValue > rockTopBlendLevel){textureMap = mix(texture(rockTex, texCoordsExport), texture(beachTex, texCoordsExport), topBlendFactor);}

    else if(yValue > rockMidBlendLevel){textureMap = mix(texture(rockTex, texCoordsExport), texture(beachTex, texCoordsExport), midBlendFactor);}

    else if(yValue > rockBotBlendLevel){textureMap = mix(texture(rockTex, texCoordsExport), texture(beachTex, texCoordsExport), botBlendFactor);}
    
    else{textureMap = texture(beachTex, texCoordsExport);}

    normal = normalize(normalExport);
    lightDirection = normalize(vec3(light0.coords));
    fAndBDif = max(dot(normal, lightDirection), 0.0f) * (light0.difCols *  terrainFandB.difRefl); 
    FragColor =  vec4(vec3(min(fAndBDif, vec4(1.0))), 1.0)  * textureMap; 
  
}
