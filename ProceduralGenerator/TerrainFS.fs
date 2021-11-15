#version 460 core

out vec4 FragColor;
in vec4 RandomVec;

float rnd(float i) 
{
	return mod(4000.*sin(23464.345*i+45.345),1.);
}

void main()
{   
    FragColor = RandomVec;
}
