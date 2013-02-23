#include <cmath>

#include "SupportClasses.h"

inline float sqr(float x) {return x*x;}

Vector::Vector() {
	this->x = 0.0;
	this->y = 0.0;
	this->x = 0.0;
}

Vector::Vector(float x, float y, float z) {
	this->x = x;
	this->y = y;
	this->z = z;
}

Vector Vector::operator+(Vector v) {
	Vector result;
	result.x = x + v.x;
	result.y = y + v.y;
	result.z = z + v.z;
	return result;
}

Vector Vector::operator-(Vector v) {
	Vector result;
	result.x = x - v.x;
	result.y = y - v.y;
	result.z = z - v.z;
	return result;
}

Vector Vector::operator*(float scalar) {
	Vector result;
	result.x = x*scalar;
	result.y = y*scalar;
	result.z = z*scalar;
	return result;
}

Vector Vector::operator/(float scalar) {
	Vector result;
	result.x = x/scalar;
	result.y = y/scalar;
	result.z = z/scalar;
	return result;
}

Vector Vector::normalize() {
	Vector result;
	float magnitude = sqrt(sqr(this->x)+sqr(this->y)+sqr(this->z));
	result.x = x/magnitude;
	result.y = y/magnitude;
	result.z = z/magnitude;
	return result;
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

Vector Vector::pointSubtraction(Point target_point, Point initial_point) {
	Point temp;
	temp = target_point-initial_point;
	Vector result(temp.x, temp.y, temp.z);
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
	dir = Vector();
	t_min = 0.0;
	t_max = 0.0;
}

Ray::Ray(Point p, Vector v, float t_min, float t_max) {
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