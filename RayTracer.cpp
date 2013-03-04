
#include "RayTracer.h"
#include <cstdlib>

RayTracer::RayTracer() {
	
}

RayTracer::RayTracer(Scene* scene) {
	this->scene = scene;
}

void RayTracer::trace(Ray & ray, int depth, Color* color) {

	float thit = 1000000.0;
	Intersection in;

	if(depth >1) {
		color->setColor(0.0, 0.0, 0.0);
		return;
	}
	if(!scene->aggPrimitives.intersectP(ray)) {
		color->setColor(0.0, 0.0, 0.0);
		return;
	} else {
		scene->aggPrimitives.intersect(ray, &thit, &in);
	}

	BRDF brdf;
	in.primitive->getBRDF(in.localGeo, &brdf);
	*color = in.primitive->getColor();
	for(unsigned int i=0; i<scene->allSceneLights.size(); i++) {
		//scene->allSceneLights[i].generateLightRay(in.local, )
		//TODO: FINISH THIS SHIT LATER
	}

}

Sampler::Sampler(int screenWidth, int screenHeight) {
	this->screenWidth = screenWidth;
	this->screenHeight = screenHeight;
	xPixel = yPixel = 0;
}

bool Sampler::getSample(Sample* sample) {
	// update this method in the future to allow for multiple sampling / anti-aliasing 
	if (yPixel >= screenHeight) {
		return false;
	}
	sample->x = xPixel;
	sample->y = yPixel;
	xPixel += 1;
	yPixel += 1;
	if (xPixel >= screenWidth) {
		xPixel = 0;
		yPixel++;
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

Camera::Camera() {
}

Camera::Camera(float x, float y, float z, int screenWidth, int screenHeight) {
	Point p(x, y, z);
	this->pos = p;
	this->screenWidth = screenWidth;
	this->screenHeight = screenHeight;
	this->l = this->b = -1.0;
	this->r = this->t = 1.0;
	this->UL = Vector3(-1.0, 1.0, -1.0);
	this->UR = Vector3(1.0, 1.0, -1.0);
	this->LL = Vector3(-1.0, -1.0, -1.0);
	this->LR = Vector3(1.0, -1.0, -1.0);
}

Camera::Camera(Point p, int screenWidth, int screenHeight) {
	this->pos = p;
	this->screenWidth = screenWidth;
	this->screenHeight = screenHeight;
	this->l = this->b = -1.0;
	this->r = this->t = 1.0;
	this->UL = Vector3(-1.0, 1.0, -1.0);
	this->UR = Vector3(1.0, 1.0, -1.0);
	this->LL = Vector3(-1.0, -1.0, -1.0);
	this->LR = Vector3(1.0, -1.0, -1.0);
}

void Camera::generateRay(Sample & sample, Ray* ray) {
	float u = l + ( ((r-l)*(sample.x + 0.5)) / screenWidth);
	float v = b + ( ((t - b)*(sample.y + 0.5)) / screenHeight);
	float w = -1;
	ray->dir = Vector3(u, v, w);
	ray->pos = this->pos;
	//Vector3 P = (((LL*v)+(UL*(1.0-v))) * u) + (((LR*v)+(UR*(1.0-v))) * (1.0-u));
	//ray->dir = P;
}

Film::Film(int screenWidth, int screenHeight, string filename) {
	this->filename = filename.c_str();
	this->screenHeight = screenHeight;
	this->screenWidth = screenWidth;
	this->pixelImage = vector <vector <Color> >(screenWidth, vector<Color>(screenHeight, Color()));
}

void Film::commit(Sample & sample, Color & color) {
	//May need to convert from [0, 1] to [0, 255]
	pixelImage[sample.x][sample.y] = color;
	color.r = 0.0;
	color.g = 0.0;
	color.b = 0.0;
}

void Film::writeImage() {
	FreeImage_Initialise();

	FIBITMAP* bitmap = FreeImage_Allocate(screenWidth, screenHeight, 24);
	RGBQUAD color;

	if(!bitmap) 
		exit(-1);

	for (int width=0; width<screenWidth; width++) {
		for(int height=0; height<screenHeight; height++) {
				color.rgbRed = pixelImage[width][height].r;
				color.rgbGreen = pixelImage[width][height].g;
				color.rgbBlue = pixelImage[width][height].b;
				FreeImage_SetPixelColor(bitmap, width, height, &color);
		}
	}

	if(FreeImage_Save(FIF_PNG, bitmap, this->filename, 0)) {
		cout << "saved" <<filename << endl;
	}

	FreeImage_DeInitialise();
}

Scene::Scene(int screenWidth, int screenHeight, float camerax, float cameray, float cameraz, string filename) {
	this->filename = filename;
	this->screenHeight = screenHeight;
	this->screenWidth = screenWidth;
	this->camerapos = Point(camerax, cameray, cameraz);
	this->raytracer = RayTracer(this);
	this->camera = Camera(this->camerapos, screenWidth, screenHeight);
}

void Scene::render() {
	Sampler sampler(screenWidth, screenHeight);
	Sample sample;
	Ray ray;
	Color color;
	Film film(screenWidth, screenHeight, filename);
	while(sampler.getSample(&sample)) {
		camera.generateRay(sample, &ray);
		raytracer.trace(ray, 0, &color);
		film.commit(sample, color);
	}
	film.writeImage();
}

int main(int argc, char *argv[]) {
	//filename argument
	//obj file arg (Camera pos, object poss, lights, etc) -> obj parser
	//resolution args
	string arg = argv[1];
	int width = atoi(argv[2]);
	int height = atoi(argv[3]);
	Scene scene(width, height, 0.0, 0.0, 0.0, arg);

	//Temporary Scene Construction
	GeometricPrimitive sphere;
	sphere.shape = new Sphere(Point(0.0, 0.0, -2.0), 1.0);
	sphere.mat = new Material(BRDF());
	sphere.color = Color(1.0, 0.0, 0.0);
	
	vector<float> column0(4);
	column0[0] = 1.0;
	column0[1] = column0[2] = column0[3] = 0.0;
	vector<float> column1(4);
	column1[1] = 1.0;
	column1[0] = column1[2] = column1[3] = 0.0;
	vector<float> column2(4);
	column2[2] = 1.0;
	column2[0] = column2[1] = column2[3] = 0.0;
	vector<float> column3(4);
	column3[3] = 1.0;
	column3[0] = column3[1] = column3[2] = 0.0;
	vector <vector <float> > identity(4);
	identity[0] = column0;
	identity[1] = column1;
	identity[2] = column2;
	identity[3] = column3;


	Matrix m(identity);
	sphere.objToWorld = Transformation(m);
	sphere.worldToObj = Transformation(m);
	
	vector<GeometricPrimitive*> list;
	list.push_back(&sphere);
	scene.aggPrimitives = AggregatePrimitive(list);

	scene.render();
	
}