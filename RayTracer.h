#include "SupportClasses.h"

class RayTracer;
class Sampler;
class Light;
class PointLight;
class DirectionalLight;
class Film;
class Scene;
class Camera;

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

class Camera {
public:
	Camera(float x, float y, float z);
	Camera(Point p);
	Point pos;
	void generateRay(Sample & sample, Ray* ray);
};

class Film {
public:
	Film(int screenWidth, int screenHeight);
	vector< vector <Color> > pixelImage;		//pixelImage[height][row]
	void commit(Sample & sample, Color & color);
	void writeImage();
};

class Scene {
public:
	Point camerapos;
	int screenHeight, screenWidth;
	Scene(int screenWidth, int screenHeight, float camerax, float cameray, float cameraz);
	void render();
};