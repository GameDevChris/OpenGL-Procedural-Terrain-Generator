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

//float rnd(float i) 
//{
//	return mod(4000.*sin(23464.345*i+45.345),1.);
//}

void main()
{   
    //terrainFandB.ambRefl = vec4(1.0, 1.0, 1.0, 1.0);
    //terrainFandB.difRefl = vec4(1.0, 1.0, 1.0, 1.0);
    //terrainFandB.specRefl = vec4(1.0, 1.0, 1.0, 1.0);
    //terrainFandB.emitCols = vec4(0.0, 0.0, 0.0, 1.0);

    //light0.ambCols = vec4(0.0, 0.0, 0.0, 1.0);
    //light0.difCols = vec4(1.0, 1.0, 1.0, 1.0);
    //light0.specCols = vec4(1.0, 1.0, 1.0, 1.0);
    //light0.coords = = vec4(1.0, 10.0, 0.0, 0.0);


    //normal = normalize(normalExport);
    //lightDirection = normalize(vec3(vec4(1.0, 10.0, 0.0, 0.0)));
    //fAndBDif = max(dot(normal, lightDirection), 0.0f) * (vec4(1.0, 1.0, 1.0, 1.0) * vec4(1.0, 1.0, 1.0, 1.0)); 
    //FragColor =  vec4(vec3(min(fAndBDif, vec4(1.0))), 1.0); 

    //normal = normalize(normalExport);
    //lightDirection = normalize(vec3(vec4(1.0, 1.0, 0.0, 0.0)));
    //FragColor = max(dot(normal, lightDirection), 0.0f) * (vec4(1.0, 1.0, 1.0, 1.0) * vec4(1.0, 1.0, 1.0, 1.0));


    //lightDirection = normalize(vec3(light0.coords));
    //fAndBDif = max(dot(normal, lightDirection), 0.0f) * (light0.difCols * terrainFandB.difRefl); 
    //FragColor =  vec4(vec3(min(fAndBDif, vec4(1.0))), 1.0); 

    //FragColor = vec4(1,1,0,1);
    FragColor = overrideColour;

    //FragColor = RandomVec;
}
