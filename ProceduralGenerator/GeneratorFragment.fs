#version 460 core
out vec4 FragColor;

struct Material 
{
    sampler2D texture_diffuse;
    sampler2D texture_specular;
    float shininess;
};

struct Light 
{
    vec3 position;
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};

in vec3 ourColor;
in vec2 TexCoord;
in vec3 FragPos;  
in vec3 Normal;

uniform vec3 viewPos; 
uniform Material material;
uniform Light light;

void main() 
{
    //ambient
    vec3 ambient = light.ambient * texture(material.texture_diffuse, TexCoord).rgb;

    //diffuse
    vec3 norm = normalize(Normal);
    vec3 lightDir = normalize(light.position - FragPos);
    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = light.diffuse * diff * texture(material.texture_diffuse, TexCoord).rgb;           
    
    //specular
    vec3 viewDir = normalize(viewPos - FragPos);
    vec3 reflectDir = reflect(-lightDir, norm);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
    vec3 specular = light.specular * spec * texture(material.texture_specular, TexCoord).rgb;

    vec3 result = (ambient + diffuse + specular);

    if(ourColor == vec3(1.0f, 0.0f, 0.0f))
    {
        result *= ourColor;
    }

    FragColor = vec4(result, 1.0);
}