
#include "Parser.h"
#include "SupportClasses.h"
#include "RayTracer.cpp"

int main(int argc, char *argv[]) {
	//filename argument
	//obj file arg (Camera pos, object poss, lights, etc) -> obj parser
	//resolution args

	//Temporary Scene Construction
	Scene scene;
	GeometricPrimitive sphere;
	sphere.shape = new Sphere(Point(0.0, 0.0, 0.0), 1.0);
	sphere.mat = new Material(BRDF(Color(0.0, 0.0, 0.0), Color(1.0, 0.0, 1.0), Color(0.0, 0.0, 1.0), Color(0.0, 0.0, 0.0), 20.0));
	
	// Identity matrix
	vector<float> column0(4);
	column0[0] = 1.0;
	column0[1] = column0[2] = column0[3] = 0.0;
	vector<float> column1(4);
	column1[1] = 1.0;
	column1[0] = column1[2] = column1[3] = 0.0;
	vector<float> column2(4);
	column2[2] = 1.0;
	column2[0] = column2[1] = column2[3] = 0.0;
	vector<float> column3(4);
	column3[3] = 1.0;
	column3[0] = column3[1] = column3[2] = 0.0;
	vector <vector <float> > identity(4);
	identity[0] = column0;
	identity[1] = column1;
	identity[2] = column2;
	identity[3] = column3;
	Matrix m(identity);

	//Temporary Scene Construction
	sphere.objToWorld = Transformation(m);
	sphere.worldToObj = Transformation(m);

	GeometricPrimitive sphere2;
	sphere2.shape = new Sphere(Point(-0.5, 0.5, -2.0), 0.3);
	sphere2.mat = new Material(BRDF(Color(0.0, 0.0, 0.0), Color(0.0, 1.0, 1.0), Color(0.0, 0.0, 1.0), Color(0.0, 0.0, 0.0), 20.0));
	sphere2.objToWorld = Transformation(m);
	sphere2.worldToObj = Transformation(m);

	PointLight thomasJefferson = PointLight(Point(1.0, 1.0, -1.0), Color(1.0, 1.0, 1.0));
	DirectionalLight georgeWashington = DirectionalLight(Vector3(1.0, 0.0, -1.0), Color(0.5, 0.5, 0.5));
	scene.allSceneLights.push_back(&georgeWashington);
	scene.allSceneLights.push_back(&thomasJefferson);

	
	vector<GeometricPrimitive*> list;
	list.push_back(&sphere);
	list.push_back(&sphere2);
	scene.aggPrimitives = AggregatePrimitive(list);

	scene.render();
	
}