#include "SupportClasses.h"
#include "FreeImage.h"

class RayTracer;
class Sampler;
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