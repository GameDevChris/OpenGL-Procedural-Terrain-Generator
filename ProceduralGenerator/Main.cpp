#include "Generator.h"

int main()
{
	Generator myGenerator;
	
	cout << "Stressed noises" << endl;
	
	//Initializing generator
	myGenerator.Awake();
	
	myGenerator.mainSkybox = new Skybox();
	
	Terrain firstTerrain(0, 0, "floor.png");
	//Terrain secondTerrain(1, 0, "floor.png");
	
	myGenerator.Grid.push_back(&firstTerrain);
	//myGenerator.Grid.push_back(&secondTerrain);
	
	//Generating objects
	myGenerator.Generate();
	
	//Starting engine
	myGenerator.Start();
	
	return 0;
}


