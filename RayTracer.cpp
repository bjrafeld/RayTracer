#include "RayTracer.h"

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

bool Sampler::getSample(Sample* sample) {
	// update this method in the future to allow for multiple sampling / anti-aliasing 
	sample->x = this->xPixel;
	sample->y = this->yPixel;
	this->xPixel += 1;
	this->yPixel += 1;
	if (xPixel >= screenWidth) {
		xPixel = 0;
		yPixel++;
		if (yPixel >= screenHeight) {
			return false;
		}
	} 
	return true;
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

Camera::Camera(float x, float y, float z) {
	Point p(x, y, z);
	this->pos = p;
}

Camera::Camera(Point p) {
	this->pos = p;
}

void Camera::generateRay(Sample & sample, Ray* ray) {

}

Film::Film(int screenWidth, int screenHeight) {
	this->pixelImage = vector <vector <Color> >(screenWidth, vector<Color>(screenHeight, Color()));
}

void Film::commit(Sample & sample, Color & color) {

}

void Film::writeImage() {
	
}

Scene::Scene(int screenWidth, int screenHeight, float camerax, float cameray, float cameraz) {
	this->screenHeight = screenHeight;
	this->screenWidth = screenWidth;
	this->camerapos = Point(camerax, cameray, cameraz);
}

void Scene::render() {
	Sampler sampler(screenWidth, screenHeight);
	Sample sample;
	Ray ray;
	RayTracer raytracer;
	Color color;
	Camera camera(camerapos);
	Film film(screenWidth, screenHeight);
	while(!sampler.getSample(&sample)) {
		camera.generateRay(sample, &ray);
		raytracer.trace(ray, 0, &color);
		film.commit(sample, color);
	}
	film.writeImage();
}

int main(int argc, char *argv[]) {
}