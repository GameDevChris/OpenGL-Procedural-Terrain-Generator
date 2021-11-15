#version 460 core
layout (location = 0) in vec3 aPos;

out vec4 RandomVec;

uniform mat4 view;
uniform mat4 projection;

uniform float RandValueX;
uniform float RandValueY;
uniform float RandValueZ;
uniform float RandValueW;

void main()
{
	RandomVec = vec4(RandValueX, RandValueY, RandValueZ, RandValueW);
	gl_Position = projection * view * vec4(aPos, 1.0);
}