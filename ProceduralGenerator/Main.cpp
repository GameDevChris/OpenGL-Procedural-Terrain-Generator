#include "Generator.h"

int main()
{
	Generator myGenerator;
	
	myGenerator.Awake();
	
	myGenerator.mainSkybox = new Skybox();
	
	Terrain* terrain = new Terrain(-500, -500);
	myGenerator.AddTerrain(terrain);

	myGenerator.Generate();
	
	myGenerator.Start();
	
	return 0;
}


