#pragma once

struct Light
{
	vec4 ambCols;
	vec4 difCols;
	vec4 specCols;
	vec4 coords;



	float xPos;
	float yPos;
	float zPos;

	Light(float x, float y, float z)
	{
		xPos = x;
		yPos = y;
		zPos = z;
	}
};