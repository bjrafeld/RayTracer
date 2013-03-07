#include "SupportClasses.h"
#include <algorithm>


inline float sqr(float x) {return x * x;}

Vector3::Vector3() {
	this->x = 0.0;
	this->y = 0.0;
	this->x = 0.0;
}

Vector3::Vector3(float x1, float y1, float z1) {
	if(x1 == 0.0f) x1=0*1;
	if(y1 == 0.0f) y1=0*1;
	if(z1 == 0.0f) z1=0*1;
	this->x = x1;
	this->y = y1;
	this->z = z1;
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
	if(result.x==0.0f) result.x = 0;
	if(result.y==0.0f) result.y = 0;
	if(result.z==0.0f) result.z = 0;
	return result;
}

float Vector3::magnitude() {
	return sqrt(sqr(this->x)+sqr(this->y)+sqr(this->z));
}

float Vector3::dotProduct(const Vector3 v1, const Vector3 v2) {
	return ((v1.x*v2.x) + (v1.y*v2.y) + (v1.z*v2.z));
}

Vector3 Vector3::crossProduct(Vector3 v1, Vector3 v2) {
	vector <vector <float> > vectorProduct(2, vector<float>(2, 0.0));
	vectorProduct[0][0] = v1.y;
	vectorProduct[1][0] = v1.z;
	vectorProduct[0][1] = v2.y;
	vectorProduct[1][1] = v2.z;
	float x = Matrix::twoDeterminant(vectorProduct);

	vectorProduct[0][0] = v1.x;
	vectorProduct[0][1] = v2.x;
	float y = -1*Matrix::twoDeterminant(vectorProduct);

	vectorProduct[1][0] = v1.y;
	vectorProduct[1][1] = v2.y;
	float z = Matrix::twoDeterminant(vectorProduct);

	return Vector3(x, y, z);
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

Vector3 Vector3::power(float constant) {
	Vector3 output;
	output.x = pow(this->x, constant);
	output.y = pow(this->y, constant);
	output.z = pow(this->z, constant);
	return output;
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

Vector3 Normal::normalToVector() {
	Vector3 output;
	output.x = x;
	output.y = y;
	output.z = z;
	return output;
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

Ray Ray::createReflectRay(LocalGeo local, Ray ray) {
	Vector3 n = local.normal.normalToVector();
	float dotProduct = Vector3::dotProduct(ray.dir.normalize(), n);
	Vector3 direction = n * (2.0 * dotProduct) - ray.dir.normalize();
	Ray result(local.pos, direction.normalize(), 0.01, 999999.99);
	return result;
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

Color Color::operator*(Color c) {
	Color result;
	result.r = r * c.r;
	result.g = g * c.g;
	result.b = b * c.b;
	return result;	
}

Color Color::operator*(float scalar) {
	Color output;
	output.r = this->r * scalar;
	output.g = this->g * scalar;
	output.b = this->b * scalar;
	return output;
}

void Color::setColor(float r, float g, float b) {
	this->r = r;
	this->g = g;
	this->b = b;
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
	this->kr = 0.0;
	this->alphaConstant = 0.0;
}

BRDF::BRDF(Color ka, Color kd, Color ks, float kr, float alphaConstant) {
	this->ka = ka;
	this->kd = kd;
	this->ks = ks;
	this->kr = kr;
	this->alphaConstant = alphaConstant;
}

Matrix::Matrix(vector <vector <float> > input) {
	mat = input;
}

Matrix::Matrix() {
	this->mat = vector< vector<float> >(4, vector <float>(4, 0.0));

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
	this->mat[0] = column0;
	this->mat[1] = column1;
	this->mat[2] = column2;
	this->mat[3] = column3;
}

Matrix Matrix::operator*(float n) {
	vector< vector <float> > m = this->mat;
	for (int i=0; i<4; i++) {
		for (int j=0; j<4; j++) {
			m[i][j] = n*m[i][j];
		}
	}
	return Matrix(m);
}

Matrix Matrix::createTranslationMatrix(float tx, float ty, float tz) {
	vector <vector <float> > input(4, vector<float>(4, 0.0));
	vector<float> last(4, 1.0);
	last[0] = tx;
	last[1] = ty;
	last[2] = tz;
	input[3] = last;
	input[0][0] = 1.0;
	input[1][1] = 1.0;
	input[2][2] = 1.0;
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

Matrix Matrix::adjointMatrix(vector <vector <float> > input) {
	vector< vector <float> > adjMat = Matrix::transposeMatrix(input).mat;
	vector< vector <float> > result(4, vector<float>(4, 0.0));
	result = Matrix::cofactorMatrix(adjMat);
	return Matrix(result);
}

vector< vector <float> > Matrix::cofactorMatrix(vector <vector <float> > input) {
	vector <vector <float> > result(4, vector<float>(4, 0.0));

	float colAarr[] = {input[0][1], input[0][2], input[0][3]};
	float colBarr[] = {input[1][1], input[1][2], input[1][3]};
	float colCarr[] = {input[2][1], input[2][2], input[2][3]};
	float colDarr[] = {input[3][1], input[3][2], input[3][3]};
	vector<float> colA(colAarr, colAarr + sizeof(colAarr) / sizeof(float) );
	vector<float> colB(colBarr, colBarr + sizeof(colBarr) / sizeof(float) );
	vector<float> colC(colCarr, colCarr + sizeof(colCarr) / sizeof(float) );
	vector<float> colD(colDarr, colDarr + sizeof(colDarr) / sizeof(float) );
	vector<vector <float> > placeholder(3, vector<float>(3, 0.0));
	placeholder[0] = colB;
	placeholder[1] = colC;
	placeholder[2] = colD;
	result[0][0] = Matrix::threeDeterminant(placeholder);
	placeholder[0] = colA;
	result[1][0] = -Matrix::threeDeterminant(placeholder);
	placeholder[1] = colB;
	result[2][0] = Matrix::threeDeterminant(placeholder);
	placeholder[2] = colC;
	result[3][0] = -Matrix::threeDeterminant(placeholder);

	colA[0] = input[0][0];
	colB[0] = input[1][0];
	colC[0] = input[2][0];
	colD[0] = input[3][0];
	placeholder[0] = colB;
	placeholder[1] = colC;
	placeholder[2] = colD;
	result[0][1] = -Matrix::threeDeterminant(placeholder);
	placeholder[0] = colA;
	result[1][1] = Matrix::threeDeterminant(placeholder);
	placeholder[1] = colB;
	result[2][1] = -Matrix::threeDeterminant(placeholder);
	placeholder[2] = colC;
	result[3][1] = Matrix::threeDeterminant(placeholder);

	colA[1] = input[0][1];
	colB[1] = input[1][1];
	colC[1] = input[2][1];
	colD[1] = input[3][1];
	placeholder[0] = colB;
	placeholder[1] = colC;
	placeholder[2] = colD;
	result[0][2] = Matrix::threeDeterminant(placeholder);
	placeholder[0] = colA;
	result[1][2] = -Matrix::threeDeterminant(placeholder);
	placeholder[1] = colB;
	result[2][2] = Matrix::threeDeterminant(placeholder);
	placeholder[2] = colC;
	result[3][2] = -Matrix::threeDeterminant(placeholder);

	colA[2] = input[0][2];
	colB[2] = input[1][2];
	colC[2] = input[2][2];
	colD[2] = input[3][2];
	placeholder[0] = colB;
	placeholder[1] = colC;
	placeholder[2] = colD;
	result[0][3] = -Matrix::threeDeterminant(placeholder);
	placeholder[0] = colA;
	result[1][3] = Matrix::threeDeterminant(placeholder);
	placeholder[1] = colB;
	result[2][3] = -Matrix::threeDeterminant(placeholder);
	placeholder[2] = colC;
	result[3][3] = Matrix::threeDeterminant(placeholder);

	return result;
}

Matrix Matrix::transposeMatrix(vector < vector <float> > input) {
	vector < vector <float> > newMat(4, vector<float>(4, 0.0));
	for(int i=0; i<4; i++) {
		for(int j=0; j<4; j++) {
			newMat[i][j]=input[j][i];
		}
	}
	return Matrix(newMat);
}

Matrix Matrix::computeInverseMatrix(vector < vector <float> > input) {
	float determinant = Matrix::fourDeterminant(input);
	if(determinant==0) {
		cout << "This should not happen, and if this is being printed" 
		<< " then something is really not working!!!" << endl;
		return Matrix();
	}
	return (Matrix::adjointMatrix(input) * (1/determinant));
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

/* Only works for 4x4 Matrices*/
float Matrix::determinant() {
	return Matrix::fourDeterminant(this->mat);
}

Matrix Matrix::transpose() {
	return Matrix::transposeMatrix(this->mat);
}

Matrix Matrix::inverse() {
	return Matrix::computeInverseMatrix(this->mat);
}

void Matrix::printMatrix() {
	cout.precision(4);
	for(int i=0; i<4; i++) {
		cout<<"| ";
		for(int j=0; j<4; j++) {
			cout<<fixed<<mat[j][i]<<" ";
		}
		cout<<"|"<<endl;
	}
}

Matrix Matrix::matMult(Matrix m1, Matrix m2) {
	vector <vector <float> > a = m1.mat;
	vector <vector <float> > b = m2.mat;
	vector <vector <float> > result(4, vector<float>(4, 0.0));
	for (int col=0; col<4; col++) {
		for (int row=0; row<4; row++) {
			for (int inner=0; inner<4; inner++) {
				result[col][row] += a[inner][row]*b[col][inner];
			}
		}
	}
	return Matrix(result);
}

Transformation::Transformation() {
	this->mat = vector< vector < float> >(4, vector <float>(4, 0.0));
	this->minvt = vector< vector <float> >(4, vector <float>(4, 0.0));
}

Transformation::Transformation(vector< vector <float> > input) {
	Matrix m(input);
	this->mat = m;
	this->minvt = m.inverse();
}

Transformation::Transformation(Matrix m) {
	this->mat=m;
	this->minvt = m.inverse();
}

vector<float> Matrix::multVector(Matrix m, vector<float> vect) {
	vector<float> resultHolder(4, 0.0);
	for (int i=0; i<4; i++) {
		float a = m.mat[0][i]*vect[0];
		float b = m.mat[1][i]*vect[1];
		float c = m.mat[2][i]*vect[2];
		float d = m.mat[3][i]*vect[3];
		resultHolder[i] = (a+b+c+d);
	}
	vector<float> result(3, 0.0);
	result[0] = resultHolder[0]/resultHolder[3];
	result[1] = resultHolder[1]/resultHolder[3];
	result[2] = resultHolder[2]/resultHolder[3];
	return result;
}

Point Transformation::operator*(Point p) {
	vector<float> mult(4, 1.0);
	mult[0] = p.x;
	mult[1] = p.y;
	mult[2] = p.z;
	vector<float> result = Matrix::multVector(mat, mult);
	Point point(result[0], result[1], result[2]);
	return point;
}

Vector3 Transformation::operator*(Vector3 v) {
	vector<float> mult(4, 1.0);
	mult[0] = v.x;
	mult[1] = v.y;
	mult[2] = v.z;
	vector<float> result = Matrix::multVector(mat, mult);
	Vector3 vect(result[0], result[1], result[2]);
	return vect;
}

Normal Transformation::operator*(Normal n) {
	//TODO
	vector<float> mult(4, 1.0);
	mult[0] = n.x;
	mult[1] = n.y;
	mult[2] = n.z;
	vector<float> result = Matrix::multVector(minvt.transpose(), mult);
	Normal normal(result[0], result[1], result[2]);
	return normal;
}

Ray Transformation::operator*(Ray r) {
	Point p = (*this) * r.pos;
	Vector3 v = (*this) * r.dir;
	return Ray(p, v, r.t_min, r.t_max);
}

LocalGeo Transformation::operator*(LocalGeo l) {
	Normal n = (*this) * l.normal;
	Point p = (*this) * l.pos;
	return LocalGeo(p, n);
}

void Transformation::pushTransform(Matrix m){
	this->mat = Matrix::matMult(m, mat);
	this->minvt = this->mat.inverse();
}

// SHAPES
Shape::Shape() {
}

bool Shape::intersect(Ray & ray, float* thit, LocalGeo* local) {
	// Override me!
	return false;
}

bool Shape::intersectP(Ray & ray) {
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

	bool t1_out = ((t1 < ray.t_min) || (t1 > ray.t_max));
	bool t2_out = ((t2 < ray.t_min) || (t2 > ray.t_max));
	//Checks to see that both t1 and t2 are out of bounds
	if(t1_out && t2_out) {
		return false;
	} else if (t1_out) {
		*thit = t2;
	} else if (t2_out) {
		*thit = t1;
	} else {

		if (t1 < t2) {
			*thit = t1;
		} else {
			*thit = t2;
		}
	}

	local->pos = Point( (ray.pos.x + ((*thit) * ray.dir.x)), (ray.pos.y + ((*thit) * ray.dir.y)), (ray.pos.z + ((*thit) * ray.dir.z)) );
	local->normal = Normal::pointSubtraction(local->pos, this->center);
	return true;
}

bool Sphere::intersectP(Ray & ray) {
	float A = Vector3::dotProduct(ray.dir, ray.dir);
	float B = Vector3::dotProduct((ray.dir * 2), Vector3::pointSubtraction(ray.pos, this->center));
	float C = Vector3::dotProduct(Vector3::pointSubtraction(ray.pos, this->center), (Vector3::pointSubtraction(ray.pos, this->center))) - (this->radius * this->radius);
	float determinant = (B * B) - (4 * A * C);
	
	float t1 = (-B + sqrt((B*B) - (4 * A * C))) / (2 * A);
	float t2 = (-B - sqrt((B*B) - (4 * A * C))) / (2 * A);

	bool t1_out = ((t1 < ray.t_min) || (t1 > ray.t_max));
	bool t2_out = ((t2 < ray.t_min) || (t2 > ray.t_max));
	if(determinant >=0) {
		if(t1_out && t2_out) {
			return false;
		}
		return true;
	}
	//Checks to see that both t1 and t2 are out of bounds
	return false;
}

void Sphere::printSelf() {
	cout << "Shape center is: " << this->center.x <<" "<<this->center.y<<" "<<this->center.z<<endl;
	cout << "Shape radius is: " << this->radius <<endl;
}

Triangle::Triangle() {
	vert_a_index = 0;
	vert_b_index = 0;
	vert_c_index = 0;
	normal = Normal();
}

Triangle::Triangle(int vertexA, int vertexB, int vertexC, vector<Point*>* allVertices) {
	this->vert_a_index = vertexA;
	this->vert_b_index = vertexB;
	this->vert_c_index = vertexC;
	this->vertices = allVertices;

	Point vert_a = *((*vertices)[vert_a_index]);
	Point vert_b = *((*vertices)[vert_b_index]);
	Point vert_c = *((*vertices)[vert_c_index]);

	Vector3 edge_a = Vector3::pointSubtraction(vert_b, vert_a);
	Vector3 edge_b = Vector3::pointSubtraction(vert_c, vert_a);
	Vector3 tri_normal = Vector3::crossProduct(edge_a, edge_b).normalize();
	normal.x = tri_normal.x;
	normal.y = tri_normal.y;
	normal.z = tri_normal.z;
}

bool Triangle::intersect(Ray & ray, float* thit, LocalGeo* local) {
	
	Point vert_a = *((*vertices)[vert_a_index]);
	Point vert_b = *((*vertices)[vert_b_index]);
	Point vert_c = *((*vertices)[vert_c_index]);
	// setup matrix variables to compute beta, gamma, t. Page 79 in the book
	float a = vert_a.x - vert_b.x;
	float b = vert_a.y - vert_b.y;
	float c = vert_a.z - vert_b.z;
	float d = vert_a.x - vert_c.x;
	float e = vert_a.y - vert_c.y;
	float f = vert_a.z - vert_c.z;
	float g = ray.dir.x;
	float h = ray.dir.y;
	float i = ray.dir.z;
	float j = vert_a.x - ray.pos.x;
	float k = vert_a.y - ray.pos.y;
	float l = vert_a.z - ray.pos.z;
	float ei_hf = ((e*i)-(h*f));
	float gf_di = ((g*f)-(d*i));
	float dh_eg = ((d*h)-(e*g));
	float ak_jb = ((a*k)-(j*b));
	float jc_al = ((j*c)-(a*l));
	float bl_kc = ((b*l)-(k*c));
	float M = (a*ei_hf) + (b*gf_di) + (c*dh_eg);

	float t = -( ((f*ak_jb)+(e*jc_al)+(d*bl_kc)) / M);
	if (t<ray.t_min || t>ray.t_max) 
		return false;

	float gamma = ( (i*ak_jb)+(h*jc_al)+(g*bl_kc) ) / M;
	if (gamma<0.0 || gamma>1.0) 
		return false;

	float beta = ( (j*ei_hf)+(k*gf_di)+(l*dh_eg) ) / M;
	if (beta<0.0 || beta>(1.0-gamma) ) 
		return false;

	(*thit) = t;
	local->pos = Point( (ray.pos.x + ((*thit) * ray.dir.x)), (ray.pos.y + ((*thit) * ray.dir.y)), (ray.pos.z + ((*thit) * ray.dir.z)) );
	local->normal = this->normal;
	return true;

}

bool Triangle::intersectP(Ray & ray) {
	Point vert_a = *((*vertices)[vert_a_index]);
	Point vert_b = *((*vertices)[vert_b_index]);
	Point vert_c = *((*vertices)[vert_c_index]);
	
	// setup matrix variables to compute beta, gamma, t. Page 79 in the book
	float a = vert_a.x - vert_b.x;
	float b = vert_a.y - vert_b.y;
	float c = vert_a.z - vert_b.z;
	float d = vert_a.x - vert_c.x;
	float e = vert_a.y - vert_c.y;
	float f = vert_a.z - vert_c.z;
	float g = ray.dir.x;
	float h = ray.dir.y;
	float i = ray.dir.z;
	float j = vert_a.x - ray.pos.x;
	float k = vert_a.y - ray.pos.y;
	float l = vert_a.z - ray.pos.z;
	float ei_hf = ((e*i)-(h*f));
	float gf_di = ((g*f)-(d*i));
	float dh_eg = ((d*h)-(e*g));
	float ak_jb = ((a*k)-(j*b));
	float jc_al = ((j*c)-(a*l));
	float bl_kc = ((b*l)-(k*c));
	float M = (a*ei_hf) + (b*gf_di) + (c*dh_eg);

	float t = -( ((f*ak_jb)+(e*jc_al)+(d*bl_kc)) / M);
	if (t<ray.t_min || t>ray.t_max) 
		return false;

	float gamma = ( (i*ak_jb)+(h*jc_al)+(g*bl_kc) ) / M;
	if (gamma<0.0 || gamma>1.0) 
		return false;

	float beta = ( (j*ei_hf)+(k*gf_di)+(l*dh_eg) ) / M;
	if (beta<0.0 || beta>(1.0-gamma) ) 
		return false;

	return true;
}

void Triangle::printSelf() {
	cout << "Triangle, motherfucker! My vertices (in index form) are: " << this->vert_a_index <<" "<<this->vert_b_index<<" "<<this->vert_c_index<<endl;
}

// Intersection
Intersection::Intersection() {
}

// Geometric Primitive
GeometricPrimitive::GeometricPrimitive() {
}

GeometricPrimitive::GeometricPrimitive(Shape* shape, Material* material, Transformation obj, Transformation world) {
	this->objToWorld = obj;
	this->worldToObj = world;
	this->mat = material;
	this->shape = shape;
}

void GeometricPrimitive::printSelf() {
	cout<<"Material.ka is: "<<mat->constantBRDF.ka.r<<" "<<mat->constantBRDF.ka.g<<" "<<mat->constantBRDF.ka.b<<endl;
	shape->printSelf();
}

bool GeometricPrimitive::intersect(Ray & ray, float* thit, Intersection* in) {
	Ray objRay = (this->worldToObj * ray);
	objRay.dir = objRay.dir.normalize();
	LocalGeo objLocal;
	if (!this->shape->intersect(objRay, thit, &objLocal)) return false;
	in->primitive = this;
	in->localGeo = this->objToWorld * objLocal;
	return true;
}

bool GeometricPrimitive::intersectP(Ray & ray) {
	Ray objRay = (this->worldToObj * ray);
	return this->shape->intersectP(objRay);
}

void GeometricPrimitive::getBRDF(LocalGeo& local, BRDF* brdf) {
	this->mat->getBRDF(local, brdf);
}

// AggregatePrimitive
AggregatePrimitive::AggregatePrimitive() {

}

AggregatePrimitive::AggregatePrimitive(vector<GeometricPrimitive*> list) {
	this->allPrimitives = list;
}

bool AggregatePrimitive::intersect(Ray & ray, float *thit, Intersection* in) {
	float *new_Hit = new float(99999.0);
	bool hitSomething = false;
	Intersection *closestIntersection = new Intersection();
	for(unsigned int i=0; i<allPrimitives.size(); i++) {
		if(allPrimitives[i]->intersect(ray, new_Hit, closestIntersection)) {
			//cout<<"Hit Something"<<endl;
			hitSomething = true;
			if((*new_Hit) < (*thit)) {
				(*thit) = (*new_Hit);
				(*in) = (*closestIntersection);
			}
		}
	}
	//Assumes that intersectP has been called -- no false returned
	delete closestIntersection;
	delete new_Hit;
	return hitSomething;
}

//Should be called before intersect to check
bool AggregatePrimitive::intersectP(Ray & ray) {
	for(unsigned int i=0; i<allPrimitives.size(); i++) {
		if (allPrimitives[i]->intersectP(ray)) {
			return true;
		}
	}
	return false;
}

// Material
Material::Material(BRDF brdf) {
	this->constantBRDF = brdf;
}

Material::Material() {
	this->constantBRDF = BRDF();
}

void Material::getBRDF(LocalGeo& local, BRDF* brdf) {
	//(*brdf) = this->constantBRDF; // possibly buggy? possibly would work? woof woof
	brdf->ka = this->constantBRDF.ka;
	brdf->kd = this->constantBRDF.kd;
	brdf->ks = this->constantBRDF.ks;
	brdf->kr = this->constantBRDF.kr;
	brdf->alphaConstant = this->constantBRDF.alphaConstant;
}
