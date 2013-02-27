#include "RayTracer.h"

void RayTracer::trace(Ray & ray, int depth, Color* color) {
	if(depth >1) {
		color->setColor(0.0, 0.0, 0.0);
		return;
	}
}