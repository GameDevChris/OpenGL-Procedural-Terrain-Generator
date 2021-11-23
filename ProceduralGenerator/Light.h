#pragma once

struct Light
{
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