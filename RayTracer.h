#include "SupportClasses.h"

class RayTracer;
class Sampler;
class Light;
class PointLight;
class DirectionalLight;

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

class Light {
public:
	virtual void generateLightRay(LocalGeo& local, Ray* lray, Color* color) = 0;
};

class PointLight : Light {
public:
	Point location;
	Color color;
	PointLight();
	PointLight(Point location, Color color);
	virtual void generateLightRay(LocalGeo& local, Ray* lray, Color* color);
};

class DirectionalLight : Light {
public:
	Vector3 direction;
	Color color;
	DirectionalLight();
	DirectionalLight(Vector3 direction, Color color);
	virtual void generateLightRay(LocalGeo& local, Ray* lray, Color* color);
};