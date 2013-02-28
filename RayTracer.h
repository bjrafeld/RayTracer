#include "SupportClasses.h"

class RayTracer;
class Sampler;

class RayTracer {
public:
	void trace(Ray & ray, int depth, Color* color);
};

class Sampler {
public:
	int xPixel, yPixel, screenWidth, screenHeight;
	Sampler(int screenWidth, int screenHeight);
	bool getSample(Sample* sample);
};