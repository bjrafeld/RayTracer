#include "RayTracer.h"
//#include "SupportClasses.h"

void RayTracer::trace(Ray & ray, int depth, Color* color) {
	if(depth >1) {
		color->setColor(0.0, 0.0, 0.0);
		return;
	}
}

Sampler::Sampler(int screenWidth, int screenHeight) {
	this->screenWidth = screenWidth;
	this->screenHeight = screenHeight;
	xPixel = yPixel = 0;
}

bool getSample(Sample* sample) {
	// update this method in the future to allow for multiple sampling / anti-aliasing 
	sample->x = this->xPixel;
	sample->y = this->yPixel;
	this->xPixel += 1;
	this->yPixel += 1;
}

// Lights
PointLight::PointLight() {
}

PointLight::PointLight(Point location, Color color) {
	this->location = location;
	this->color = color;
}

void PointLight::generateLightRay(LocalGeo& local, Ray* lray, Color* color) {
	lray->pos = local.pos;
	lray->dir = Vector3::pointSubtraction(this->location, local.pos);
}

DirectionalLight::DirectionalLight() {
}

DirectionalLight::DirectionalLight(Vector3 direction, Color color) {
	this->direction = direction;
	this->color = color;
}

void DirectionalLight::generateLightRay(LocalGeo& local, Ray* lray, Color* color) {
	lray->pos = local.pos;
	lray->dir = this->direction * -1.0;
}