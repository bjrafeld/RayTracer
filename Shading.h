#ifndef SHADING_H
#define SHADING_H


#include <vector>
#include <cmath>
#include <iostream>
#include "SupportClasses.h"

using namespace std;

class Shader;

class Shader {
public:
	Shader();
	Color shading(LocalGeo local, BRDF brdf, Ray* lray, Color* lcolor, const Point camera, Vector3 rayDir);
	Vector3 reflectedVector(Vector3 lightDirection, Vector3 normal);
};

#endif