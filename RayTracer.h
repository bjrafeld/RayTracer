#ifndef RAYTRACER_H
#define RAYTRACER_H


#include "FreeImage.h"
#include "Shading.h"
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
	Scene* scene;
	Shader* shader;
	RayTracer();
	RayTracer(Scene* scene);
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

class PointLight : public Light {
public:
	Point location;
	Color color;
	PointLight();
	PointLight(Point location, Color color);
	virtual void generateLightRay(LocalGeo& local, Ray* lray, Color* color);
};

class DirectionalLight : public Light {
public:
	Vector3 direction;
	Color color;
	DirectionalLight();
	DirectionalLight(Vector3 direction, Color color);
	virtual void generateLightRay(LocalGeo& local, Ray* lray, Color* color);
};

class Camera {
public:
	Camera();
	Camera(float x, float y, float z, int screenWidth, int screenHeight);
	Camera(Point p, int screenWidth, int screenHeight);
	Camera(Point pos, Point lookAt, Vector3 up, float fov, int screenWidth, int screenHeight);
	Vector3 upVector;
	Point lookAt;
	Point pos;
	float aspectRatio;
	int screenWidth, screenHeight;
	float l,r,t,b;
	Vector3 UL, UR, LL, LR;
	void generateRay(Sample & sample, Ray* ray);
};

class Film {
public:
	Film(int screenWidth, int screenHeight, string filename);
	const char* filename;
	int screenWidth, screenHeight;
	vector< vector <Color> > pixelImage;		//pixelImage[width][height]
	void commit(Sample & sample, Color & color);
	void writeImage();
};

class Scene {
public:
	RayTracer raytracer;
	Camera camera;
	//TODO get prims in the list
	AggregatePrimitive aggPrimitives;
	//TODO get lights in the list
	vector<Light*> allSceneLights;
	Point camerapos;
	int screenHeight, screenWidth;
	string filename;
	Scene();
	Scene(int screenWidth, int screenHeight, float camerax, float cameray, float cameraz, string filename);
	void render();
};

#endif