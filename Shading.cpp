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
	float dotProduct = Vector3::dotProduct(lray->dir.normalize(), local.normal.normalToVector());
	if(dotProduct < 0) {
		dotProduct *= -1.0;
	}
	if(brdf.kd.r > .69 && brdf.kd.g > .69 && brdf.kd.b ==1) {
		//cout<<dotProduct<<endl;
	}
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
	if((specular.r!=0 ||specular.g!=0||specular.b!=0) && dotProduct==0) {
		//cout<<"AHA!"<<endl;
	}
	return outputColor;
}	

Vector3 Shader::reflectedVector(Vector3 lightDirection, Vector3 normal) {
	float dotProduct =Vector3::dotProduct(lightDirection, normal);
	Vector3 result = normal * (2.0 * dotProduct) - lightDirection;
	return result.normalize();
}


