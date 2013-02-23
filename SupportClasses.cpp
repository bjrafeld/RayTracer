#include <SupportClasses.h>

Vector::Vector() {
	this->x = 0.0;
	this->y = 0.0;
	this->z = 0.0;
}

Vector::Vector(float x, float y, float z) {
	this->x = x;
	this->y = y;
	this->z = z;
}

const Vector Vector::Vector operator+(const Vector& v) {
	Vector result;
	result.x = this->x + v.x;
	result.y = this->y + v.y;
	result.z = this->z + v.z;
	return result;
}

const Vector Vector::Vector operator-(const Vecto& v) {
	Vector result;
	result.x = this->x - v.x;
	result.y = this->y - v.y;
	result.z = this->z - v.z;
	return result;
}

const Vector Vector::Vector operator*(const float& scalar) {
	Vector result;
	result.x = this.x*scalar;
	result.y = this.y*scalar;
	result.z = this.z*scalar;
	return result;
}

const Vector Vector::Vector operator/(const float& scalar) {
	Vector result;
	result.x = this.x/scalar;
	result.y = this.y/scalar;
	result.z = this.z/scalar;
	return result;
}

Vector::Vector normalize() {
	Vector result;
	float magnitude = sqrt(sqr(this->x)+sqr(this->y)+sqr(this->z));
	result.x = this->x/magnitude;
	result.y = this->y/magnitude;
	result.z = this->z/magnitude;
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

const Point Point::Point operator+(const Point& p) {
	Point result;
	result.x = this->x + p.x;
	result.y = this->y + p.y;
	result.z = this->z + p.z;
	return result;
}

const Point Point::Point operator-(const Point& p) {
	Point result;
	result.x = this->x - p.x;
	result.y = this->y - p.y;
	result.z = this->z - p.z;
	return result;
}