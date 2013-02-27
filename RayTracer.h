#include "SupportClasses.h"

class RayTracer;

RayTracer {

public:
	void trace(Ray & ray, int depth, Color* color);
};