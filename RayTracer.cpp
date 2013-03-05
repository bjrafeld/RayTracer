
/*POSSIBLE FUCK-UPS

- Flipped pixel indices (orientation could be upside-down)
- Check for color flips (FreeImage uses mod255)
- issues with t_min in light rays 
- Need to account for camera direction (Specular shading)
- When computing specular component in Shader viewer vector could possibly be wrong (now constant at camera.pos-origin)
*/

#include "RayTracer.h"
#include <cstdlib>

RayTracer::RayTracer() {

}

RayTracer::RayTracer(Scene* scene) {
	this->scene = scene;
	this->shader = new Shader();
}

void RayTracer::trace(Ray & ray, int depth, Color* color) {

	float thit = 1000000.0;
	Intersection in;

	if(depth >1) {
		color->setColor(0.0, 0.0, 0.0);
		return;
	}
	if(!scene->aggPrimitives.intersect(ray, &thit, &in)) {
		color->setColor(0.0, 0.0, 0.0);
		//cout<<"Not intersecting anything\n"<<endl;
		return;
	} 

	BRDF brdf;
	in.primitive->getBRDF(in.localGeo, &brdf);

	Color totalColor;
	for(unsigned int i=0; i<scene->allSceneLights.size(); i++) {
		
		Ray lray;
		lray.t_min = thit + 0.0001;	// ordering here is important
		lray.t_max = 9999999.0;	// t_max will be set differently for point lights
		Color lcolor;
		scene->allSceneLights[i]->generateLightRay(in.localGeo, &lray, &lcolor);

		// TODO - check if light is blocked or not before calling shading method
		totalColor = totalColor + shader->shading(in.localGeo, brdf, &lray, &lcolor, scene->camera.pos);
	}

	totalColor.r = min(totalColor.r, 1.0f);
	totalColor.g = min(totalColor.g, 1.0f);
	totalColor.b = min(totalColor.b, 1.0f);

	color->setColor(totalColor.r, totalColor.g, totalColor.b);

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
	color->r = this->color.r;
	color->g = this->color.g;
	color->b = this->color.b;
	lray->t_max = lray->t_min + lray->dir.magnitude();
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
	color->r = this->color.r;
	color->g = this->color.g;
	color->b = this->color.b;
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

	// needs to be changed for non-origin camera positions woof woof
	float u = l + ( ((r-l)*(sample.x + 0.5)) / screenWidth);
	float v = b + ( ((t - b)*(sample.y + 0.5)) / screenHeight);
	float w = -1;
	ray->dir = Vector3(u, v, w);
	ray->pos = this->pos;
	ray->t_min = 1.0;
	ray->t_max = 999999.0;
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
	color.r = color.r*255.0;
	color.g = color.g*255.0;
	color.b = color.b*255.0;

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
		cout << "saved " << filename << endl;
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
		//cout<<"Sample.x = "<<sample.x<<" Sample.y = "<<sample.y<<endl;
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
	sphere.shape = new Sphere(Point(0.0, 0.0, 0.0), 1.0);
	sphere.mat = new Material(BRDF(Color(0.0, 0.0, 0.0), Color(1.0, 0.0, 1.0), Color(0.0, 0.0, 1.0), Color(0.0, 0.0, 0.0), 20.0));
	sphere.color = Color(1.0, 0.0, 0.0);
	
	// Identity matrix
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

	//Temporary Scene Construction
	GeometricPrimitive sphere;
	sphere.shape = new Sphere(Point(0.0, 0.0, -3.0), 1.0);
	sphere.mat = new Material(BRDF(Color(0.0, 0.0, 0.0), Color(1.0, 0.0, 1.0), Color(0.0, 0.0, 1.0), Color(0.0, 0.0, 0.0), 20.0));
	sphere.objToWorld = Transformation(m);
	sphere.worldToObj = Transformation(m);

	GeometricPrimitive sphere2;
	sphere2.shape = new Sphere(Point(-0.5, 0.5, -2.0), 0.3);
	sphere2.mat = new Material(BRDF(Color(0.0, 0.0, 0.0), Color(0.0, 1.0, 1.0), Color(0.0, 0.0, 1.0), Color(0.0, 0.0, 0.0), 20.0));
	sphere2.objToWorld = Transformation(m);
	sphere2.worldToObj = Transformation(m);

	PointLight thomasJefferson = PointLight(Point(1.0, 1.0, -1.0), Color(1.0, 1.0, 1.0));
	DirectionalLight georgeWashington = DirectionalLight(Vector3(1.0, 0.0, -1.0), Color(0.5, 0.5, 0.5));
	scene.allSceneLights.push_back(&georgeWashington);
	scene.allSceneLights.push_back(&thomasJefferson);

	
	vector<GeometricPrimitive*> list;
	list.push_back(&sphere);
	list.push_back(&sphere2);
	scene.aggPrimitives = AggregatePrimitive(list);

	scene.render();
	
}