#include <cstdlib>
#include <algorithm>
#include <cmath>

#include "Shading.h"

Shader::Shader() {

}

Color Shader::shading(LocalGeo local, BRDF brdf, Ray* lray, Color* lcolor, const Point camera, Vector3 rayDir) {
	Color outputColor;
	// diffuse
	Color diffuse;
	float dotProduct = max(Vector3::dotProduct(lray->dir.normalize(), local.normal.normalToVector()), 0.0f);
	diffuse = (brdf.kd * dotProduct) * (*lcolor);
	outputColor = outputColor + diffuse;
	//specular
	Color specular;
	Vector3 reflectedVector = this->reflectedVector(lray->dir.normalize(), local.normal.normalToVector());
	//Vector3 viewer = Vector3::pointSubtraction(camera, Point());
	//Vector3 viewer = Vector3::pointSubtraction(camera, local.pos); //woof woof
	//VIEWER IS NEGATIVE CAMERA RAY
	//Camera Direction
	Vector3 viewer = rayDir * -1;
	float reflectedDotProduct = max(Vector3::dotProduct(reflectedVector, viewer), 0.0f);
	specular = (brdf.ks * pow(reflectedDotProduct, brdf.alphaConstant)) *(*lcolor);
	outputColor = outputColor + specular;

	outputColor.r = min(outputColor.r, 1.0f);
	outputColor.g = min(outputColor.g, 1.0f);
	outputColor.b = min(outputColor.b, 1.0f);
	return outputColor;
}	

Vector3 Shader::reflectedVector(Vector3 lightDirection, Vector3 normal) {
	float dotProduct =Vector3::dotProduct(lightDirection, normal);
	Vector3 result = normal * (2.0 * dotProduct) - lightDirection;
	return result.normalize();
}


