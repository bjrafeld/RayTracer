
#include "Parser.h"

using namespace std;

int main(int argc, char *argv[]) {
	//filename argument
	//obj file arg (Camera pos, object poss, lights, etc) -> obj parser
	//resolution args
	
	string fileName = argv[1];
	vector<GeometricPrimitive*> list(0);
	Scene scene;
	scene.aggPrimitives = AggregatePrimitive(list);
	loadScene(fileName, &scene);
	//scene.allSceneLights[0]->printSelf();
	scene.render();
	
}