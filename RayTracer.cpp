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