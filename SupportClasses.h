#ifndef SUPPORTCLASSES_H
#define SUPPORTCLASSES_H

#include <cmath>
#include <iostream>
#include <vector>

using namespace std;

class Vector3;
class Point;
class Normal;
class Ray;
class Color;
class Sample;
class LocalGeo;
class BRDF;
class Matrix;
class Transformation;
class Shape;
class Sphere;
class Triangle;
class Intersection;
class Primitive;
class Material;
class GeometricPrimitive;
class AggregatePrimitive;

//Vector3 Class
class Vector3 {
public:
	float x, y, z;
	Vector3();
    Vector3(float x, float y, float z);
    Vector3 operator+(Vector3 v);
    Vector3 operator-(Vector3 v);
    Vector3 operator*(float scalar);
    Vector3 operator/(float scalar);
    Vector3 power(float constant);
    Vector3 normalize();
    float magnitude();
    static Vector3 pointSubtraction(Point target_point, Point initial_point);
    static float dotProduct(const Vector3 v1, const Vector3 v2);
    static Vector3 crossProduct(Vector3 v1, Vector3 v2);
};


//Point Class
class Point {
public:
	float x, y, z;
	Point();
	Point(float x, float y, float z);
	Point operator+(Point p);
	Point operator-(Point p);
};

//Normal Class
class Normal {
public:
	float x, y, z;
	Normal();
	Normal(float x, float y, float z);
	Normal operator+(Normal n);
	Normal operator-(Normal n);
    Vector3 normalToVector();
	static Normal pointSubtraction(Point target_point, Point initial_point);
private:
	Normal normalize();
};

class Ray {
public:
	Point pos;
	Vector3 dir;
	float t_min, t_max;
	Ray();
	Ray(Point p, Vector3 v, float t_min, float t_max);
	static Ray createReflectRay(LocalGeo local, Ray ray);
};

class Color {
public:
	float r, g, b;
	Color();
	Color(float r, float g, float b);
	void setColor(float r, float g, float b);
	Color operator+(Color c);
	Color operator-(Color c);
    Color operator*(Color c);
    Color operator*(float scalar);
};

class Sample {
public:
	float x, y;
	Sample();
	Sample(float x, float y);
};

class LocalGeo {
public:
	Point pos;
	Normal normal;
	LocalGeo();
	LocalGeo(Point p, Normal n);
};

class BRDF {
public:
	Color ka, kd, ks;
	float kr;
    float alphaConstant;
	BRDF();
	BRDF(Color ka, Color kd, Color ks, float kr, float alphaConstant);
};


/*
| [0][0] [1][0] [2][0] [3][0] |
| [0][1] [1][1] [2][1] [3][1] |
| [0][2] [1][2] [2][2] [3][2] |
| [0][3] [1][3] [2][3] [3][3] |
*/

class Matrix {
public:
	vector< vector <float> > mat;
	Matrix();
	Matrix(vector< vector<float> > input);
	Matrix operator*(float n);
	static Matrix createTranslationMatrix(float tx, float ty, float tz);
	static Matrix createScalarMatrix(float sx, float sy, float sz);
	static Matrix createRotationMatrix(float x, float y, float z, float angle);
	static vector<float> multVector(Matrix transform, vector<float> vect);
	float determinant(); //Only for 4x4 Matrices
	Matrix transpose();  //4x4
	Matrix inverse();	 //4x4
	static Matrix matMult(Matrix m1, Matrix m2);
	void printMatrix();
    static float twoDeterminant(vector < vector <float> > input);
    

private:  
	static Matrix createXRotation(float angle);
	static Matrix createYRotation(float angle);
	static Matrix createZRotation(float angle);  
    static float threeDeterminant(vector < vector <float> > input);
    static Matrix adjointMatrix(vector <vector <float> > input);
    static Matrix computeInverseMatrix(vector < vector <float> > input);
    static float fourDeterminant(vector < vector <float> > input);
    static Matrix transposeMatrix(vector <vector <float> > input);
    static vector<vector <float> > cofactorMatrix(vector <vector <float> > input);
};

class Transformation {
public:
	Matrix mat;
	Matrix minvt;
	Transformation();
	Transformation(vector< vector<float> > input);
	Transformation(Matrix m);
	void pushTransform(Matrix m);
	Point operator*(Point p);
	Vector3 operator*(Vector3 v);
	Normal operator*(Normal n);		//Needs to be changed
	Ray operator*(Ray r);
	LocalGeo operator*(LocalGeo l);
};


// Shape Class
class Shape {
public:
    Shape();
    // tests if a ray intersects this shape, and if so, returns the intersection point and normal in the form of a LocalGeo
    virtual bool intersect(Ray & ray, float* thit, LocalGeo* local);
    // tests if a ray intersects this shape, returns true if so
    virtual bool intersectP(Ray & ray);
    virtual void printSelf() = 0;
};

// Sphere Class
class Sphere : public Shape {
public:
    Point center;
    float radius;

    Sphere();
    Sphere(Point c, float r);
    // tests if a ray intersects this shape, and if so, returns the intersection point and normal in the form of a LocalGeo
    virtual bool intersect(Ray & ray, float* thit, LocalGeo* local);
    // tests if a ray intersects this shape, returns true if so
    virtual bool intersectP(Ray & ray);
    virtual void printSelf();
};

// Triangle Class

class Triangle : public Shape{
public:
    int vert_a_index, vert_b_index, vert_c_index;
    vector<Point*>* vertices;
    Normal normal;
    Triangle();
    Triangle(int vertexA, int vertexB, int vertexC, vector<Point*>* allVertices);

    // tests if a ray intersects this shape, and if so, returns the intersection point and normal in the form of a LocalGeo
    virtual bool intersect(Ray & ray, float* thit, LocalGeo* local);
    // tests if a ray intersects this shape, returns true if so
    virtual bool intersectP(Ray & ray);
    virtual void printSelf();
};

// Intersection
class Intersection {
public:
    Intersection();
    LocalGeo localGeo;
    Primitive* primitive;
};

// Primitive
class Primitive {
public:
    virtual bool intersect(Ray & ray, float* thit, Intersection* in) = 0;
    virtual bool intersectP(Ray & ray) = 0;
    virtual void getBRDF(LocalGeo& local, BRDF* brdf) = 0;
    virtual void printSelf() = 0;
};

// GeometricPrimitive
class GeometricPrimitive : public Primitive {
public:
    Transformation objToWorld, worldToObj;
    Shape* shape;
    Material* mat;

    GeometricPrimitive();
    GeometricPrimitive(Shape* shape, Material* m, Transformation obj, Transformation world);
    virtual bool intersect(Ray & ray, float* thit, Intersection* in);
    virtual bool intersectP(Ray & ray);
    virtual void getBRDF(LocalGeo& local, BRDF* brdf);
    virtual void printSelf();
};

// AggregatePrimitive
class AggregatePrimitive {
public:
	vector<GeometricPrimitive*> allPrimitives;
	AggregatePrimitive();
	AggregatePrimitive(vector<GeometricPrimitive*> list);
	bool intersect(Ray & ray, float *thit, Intersection* in);
	bool intersectP(Ray & r);
};

// Material
// Stores a constant material used for shading calculations
class Material {
public:
    BRDF constantBRDF;
    Material(BRDF brdf);
    void getBRDF(LocalGeo& local, BRDF* brdf);
    Material();
};

#endif
