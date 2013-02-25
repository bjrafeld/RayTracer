#include <cmath>

#include "SupportClasses.h"

inline float sqr(float x) {return x*x;}

Vector3::Vector3() {
	this->x = 0.0;
	this->y = 0.0;
	this->x = 0.0;
}

Vector3::Vector3(float x, float y, float z) {
	this->x = x;
	this->y = y;
	this->z = z;
}

Vector3 Vector3::operator+(Vector3 v) {
	Vector3 result;
	result.x = x + v.x;
	result.y = y + v.y;
	result.z = z + v.z;
	return result;
}

Vector3 Vector3::operator-(Vector3 v) {
	Vector3 result;
	result.x = x - v.x;
	result.y = y - v.y;
	result.z = z - v.z;
	return result;
}

Vector3 Vector3::operator*(float scalar) {
	Vector3 result;
	result.x = x*scalar;
	result.y = y*scalar;
	result.z = z*scalar;
	return result;
}

Vector3 Vector3::operator/(float scalar) {
	Vector3 result;
	result.x = x/scalar;
	result.y = y/scalar;
	result.z = z/scalar;
	return result;
}

Vector3 Vector3::normalize() {
	Vector3 result;
	float magnitude = sqrt(sqr(this->x)+sqr(this->y)+sqr(this->z));
	result.x = x/magnitude;
	result.y = y/magnitude;
	result.z = z/magnitude;
	return result;
}

float Vector3::dotProduct(const Vector3 v1, const Vector3 v2) {
	return ((v1.x*v2.x) + (v1.y*v2.y) + (v1.z*v2.z));
}

Point::Point() {
	this->x = 0.0;
	this->y = 0.0;
	this->z = 0.0;
}

Point::Point(float x, float y, float z) {
	this->x = x;
	this->y = y;
	this->z = z;
}

Point Point::operator+(Point p) {
	Point result;
	result.x = x + p.x;
	result.y = y + p.y;
	result.z = z + p.z;
	return result;
}

Point Point::operator-(Point p) {
	Point result;
	result.x = x - p.x;
	result.y = y - p.y;
	result.z = z - p.z;
	return result;
}

Vector3 Vector3::pointSubtraction(Point target_point, Point initial_point) {
	Point temp;
	temp = target_point-initial_point;
	Vector3 result(temp.x, temp.y, temp.z);
	return result;
}

Normal::Normal() {
	this->x=0.0;
	this->y = 0.0;
	this->z = 0.0;
}

//Normalizes the points given to it
Normal::Normal(float x, float y, float z) {
	this->x = x;
	this->y = y;
	this->z = z;
	if (x!=0 && y!=0 && z!=0) {
		float magnitude = sqrt(sqr(this->x)+sqr(this->y)+sqr(this->z));
		this->x = this->x/magnitude;
		this->y = this->y/magnitude;
		this->z = this->z/magnitude;
	}
}

Normal Normal::normalize() {
	if(x==0 && y==0 && z==0) {
		Normal normal;
		return normal;
	} else {
		Normal result;
		float magnitude = sqrt(sqr(this->x)+sqr(this->y)+sqr(this->z));
		result.x = x/magnitude;
		result.y = y/magnitude;
		result.z = z/magnitude;
		return result;
	}
}

//Always returns a normalized Vector
Normal Normal::operator+(Normal n) {
	Normal result;
	result.x = x + n.x;
	result.y = y + n.y;
	result.z = z + n.z;
	result = result.normalize();
	return result;
}

//Always returns a normalized vector
Normal Normal::operator-(Normal n) {
	Normal result;
	result.x = x - n.x;
	result.y = y - n.y;
	result.z = z - n.z;
	result = result.normalize();
	return result;
}

Ray::Ray() {
	pos = Point();
	dir = Vector3();
	t_min = 0.0;
	t_max = 0.0;
}

Ray::Ray(Point p, Vector3 v, float t_min, float t_max) {
	this->pos = p;
	this->dir = v;
	this->t_min = t_min;
	this->t_max = t_max;
}

Color::Color() {
	r=0.0;
	g=0.0;
	b=0.0;
}

Color::Color(float r, float g, float b) {
	this->r = r;
	this->g = g;
	this->b = b;
}

Color Color::operator+(Color c) {
	Color result;
	result.r = r + c.r;
	result.g = g + c.g;
	result.b = b + c.b;
	return result;
}

Color Color::operator-(Color c) {
	Color result;
	result.r = r - c.r;
	result.g = g - c.g;
	result.b = b - c.b;
	return result;
}

Sample::Sample() {
	x = 0.0;
	y = 0.0;
}

Sample::Sample(float x, float y) {
	this->x = x;
	this->y = y;
}

LocalGeo::LocalGeo() {
	pos = Point();
	normal = Normal();
}

LocalGeo::LocalGeo(Point p, Normal n) {
	pos = p;
	normal = n;
}

BRDF::BRDF() {
	this->ka = Color();
	this->kd = Color();
	this->ks = Color();
	this->kr = Color();
}

BRDF::BRDF(Color ka, Color kd, Color ks, Color kr) {
	this->ka = ka;
	this->kd = kd;
	this->ks = ks;
	this->kr = kr;
}

Matrix::Matrix(vector <vector <float> > input) {
	mat = input;
}

Matrix::Matrix() {
	vector< vector<float> >(4, vector <float>(4, 0.0));
}

Matrix Matrix::createTranslationMatrix(float tx, float ty, float tz) {
	vector <vector <float> > input(4, vector<float>(4, 0.0));
	vector<float> last(4, 1.0);
	last[0] = tx;
	last[1] = ty;
	last[2] = tz;
	input[3] = last;
	return Matrix(input);
}

Matrix Matrix::createScalarMatrix(float sx, float sy, float sz) {
	vector <vector <float> > input(4, vector<float>(4, 0.0));
	input[0][0] = sx;
	input[1][1] = sy;
	input[2][2] = sz;
	input[3][3] = 1.0;
	return Matrix(input);
}

// SHAPES
Shape::Shape() {
}

bool Shape::intersect(Ray & ray, float* thit, LocalGeo* local) {
	// Override me!
}

bool Shape::intersect(Ray & ray) {
	// Override me!
	return false;
}

Sphere::Sphere() {
}

Sphere::Sphere(Point c, float r) {
	this->center = c;
	this->radius = r;
}

bool Sphere::intersect(Ray & ray, float* thit, LocalGeo* local) {
	float A = Vector3::dotProduct(ray.dir, ray.dir);
	float B = Vector3::dotProduct( (ray.dir * 2), Vector3::pointSubtraction(ray.pos, this->center) );
	float C = Vector3::dotProduct(Vector3::pointSubtraction(ray.pos, this->center), Vector3::pointSubtraction(ray.pos, this->center)) - (this->radius * this->radius);
	float determinant = (B * B) - (4 * A * C);
	if (determinant < 0) {
		// no intersection
		return false;
	}
	float t1 = (-B + sqrt((B*B) - (4 * A * C))) / (2 * A);
	float t2 = (-B - sqrt((B*B) - (4 * A * C))) / (2 * A);
	if (t1 < t2) {
		*thit = t1;
	} else {
		*thit = t2;
	}
	local->pos = Point( (ray.pos.x + ((*thit) * ray.dir.x)), (ray.pos.y + ((*thit) * ray.dir.y)), (ray.pos.z + ((*thit) * ray.dir.z)) );
	local->normal = Normal::pointSubtraction(local->pos, this->center);
	return true;
}

bool Sphere::intersect(Ray & ray) {
	float A = Vector3::dotProduct(ray.dir, ray.dir);
	float B = Vector3::dotProduct( (ray.dir * 2), Vector3::pointSubtraction(ray.pos, this->center) );
	float C = Vector3::dotProduct(Vector3::pointSubtraction(ray.pos, this->center), Vector3::pointSubtraction(ray.pos, this->center)) - (this->radius * this->radius);
	float determinant = (B * B) - (4 * A * C);
	return (determinant >= 0);
}

Triangle::Triangle() {
	// TODO
}

bool Triangle::intersect(Ray & ray, float* thit, LocalGeo* local) {
	// TODO
	return false;
}

bool Triangle::intersect(Ray & ray) {
	// TODO
	return false;
}
