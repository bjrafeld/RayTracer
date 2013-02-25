#include "SupportClasses.h"

inline float sqr(float x) {return x * x;}

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

Normal Normal::pointSubtraction(Point target_point, Point initial_point) {
	Point temp;
	temp = target_point-initial_point;
	Normal result(temp.x, temp.y, temp.z);
	return result.normalize();
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
	this->mat = vector< vector<float> >(4, vector <float>(4, 0.0));
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

float Matrix::fourDeterminant(vector < vector <float> > input) {
	float a, b, c, d;
	float colAarr[] = {input[0][1], input[0][2], input[0][3]};
	float colBarr[] = {input[1][1], input[1][2], input[1][3]};
	float colCarr[] = {input[2][1], input[2][2], input[2][3]};
	float colDarr[] = {input[3][1], input[3][2], input[3][3]};
	vector<float> colA(colAarr, colAarr + sizeof(colAarr) / sizeof(float) );
	vector<float> colB(colBarr, colBarr + sizeof(colBarr) / sizeof(float) );
	vector<float> colC(colCarr, colCarr + sizeof(colCarr) / sizeof(float) );
	vector<float> colD(colDarr, colDarr + sizeof(colDarr) / sizeof(float) );
	vector< vector <float> > matAvect(3, vector<float>(3, 0.0));
	vector< vector <float> > matBvect(3, vector<float>(3, 0.0));
	vector< vector <float> > matCvect(3, vector<float>(3, 0.0));
	vector< vector <float> > matDvect(3, vector<float>(3, 0.0));
	matAvect[0]=colB;
	matAvect[1]=colC;
	matAvect[2]=colD;
	matBvect[0]=colA;
	matBvect[1]=colC;
	matBvect[2]=colD;
	matCvect[0]=colA;
	matCvect[1]=colB;
	matCvect[2]=colD;
	matDvect[0]=colA;
	matDvect[1]=colB;
	matDvect[2]=colC;
	a = input[0][0] * Matrix::threeDeterminant(matAvect);
	b = input[1][0] * Matrix::threeDeterminant(matBvect);
	c = input[2][0] * Matrix::threeDeterminant(matCvect);
	d = input[3][0] * Matrix::threeDeterminant(matDvect);
	return (a-b+c-d);
}

float Matrix::threeDeterminant(vector< vector <float> > input) {
	float a, b, c;
	float colAarr[] = {input[0][1], input[0][2]};
	float colBarr[] = {input[1][1], input[1][2]};
	float colCarr[] = {input[2][1], input[2][2]};
	vector<float> colA(colAarr, colAarr + sizeof(colAarr) / sizeof(float) );
	vector<float> colB(colBarr, colBarr + sizeof(colBarr) / sizeof(float) );
	vector<float> colC(colCarr, colCarr + sizeof(colCarr) / sizeof(float) );
	vector< vector <float> > matAvect(2, vector<float>(2, 0.0));
	vector< vector <float> > matBvect(2, vector<float>(2, 0.0));
	vector< vector <float> > matCvect(2, vector<float>(2, 0.0));
	matAvect[0]=colB;
	matAvect[1]=colC;
	matBvect[0]=colA;
	matBvect[1]=colC;
	matCvect[0]=colA;
	matCvect[1]=colB;
	a = input[0][0] * Matrix::twoDeterminant(matAvect);
	b = input[1][0] * Matrix::twoDeterminant(matBvect);
	c = input[2][0] * Matrix::twoDeterminant(matCvect);
	return (float)(a-b+c);
}

float Matrix::twoDeterminant(vector < vector <float> > input) {
	float ad = input[0][0] * input[1][1];
	float bc = input[0][1] * input[1][0];
	return (ad-bc);
}

Transformation::Transformation() {
	this->mat = vector< vector < float> >(4, vector <float>(4, 0.0));
	this->minvt = vector< vector <float> >(4, vector <float>(4, 0.0));
}

Transformation::Transformation(vector< vector <float> > input) {
	this->mat = input;
	//this->minvt = Matrix::inverse(input);
}