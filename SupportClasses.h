#include <vector>
#include <cmath>
#include <iostream>

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
    Vector3 normalize();
    static Vector3 pointSubtraction(Point target_point, Point initial_point);
    static float dotProduct(const Vector3 v1, const Vector3 v2);
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
};

class Color {
public:
	float r, g, b;
	Color();
	Color(float r, float g, float b);
	Color operator+(Color c);
	Color operator-(Color c);
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
	Color ka, kd, ks, kr;
	BRDF();
	BRDF(Color ka, Color kd, Color ks, Color kr);
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
	static vector<float> multVector(vector < vector <float> > transform, vector<float> vect);

	//NEED TO FINISH
    static Matrix computeInverseMatrix(vector < vector <float> > input);
    static float fourDeterminant(vector < vector <float> > input);

private:    
    static float threeDeterminant(vector < vector <float> > input);
    static float twoDeterminant(vector < vector <float> > input);
    static Matrix transposeMatrix(vector <vector <float> > input);
    static Matrix adjunctMatrix(vector <vector <float> > input);
    static float cofactorTerm(vector <vector <float> > input, int i, int j);
};

class Transformation {
public:
	vector< vector <float> > mat;
	vector< vector <float> > minvt;
	Transformation();
	Transformation(vector< vector<float> > input);
	Transformation(Matrix m);
	Point operator*(Point p);
	Vector3 operator*(Vector3 v);
	Normal operator*(Normal n);
	Ray operator*(Ray r);
};


// Shape Class
class Shape {
public:
    Shape();
    // tests if a ray intersects this shape, and if so, returns the intersection point and normal in the form of a LocalGeo
    virtual bool intersect(Ray & ray, float* thit, LocalGeo* local);
    // tests if a ray intersects this shape, returns true if so
    virtual bool intersectP(Ray & ray);
};

// Sphere Class
class Sphere : Shape{
public:
    Point center;
    float radius;

    Sphere();
    Sphere(Point c, float r);
    // tests if a ray intersects this shape, and if so, returns the intersection point and normal in the form of a LocalGeo
    virtual bool intersect(Ray & ray, float* thit, LocalGeo* local);
    // tests if a ray intersects this shape, returns true if so
    virtual bool intersectP(Ray & ray);
};

// Triangle Class

class Triangle : Shape{
public:
    Triangle();

    // tests if a ray intersects this shape, and if so, returns the intersection point and normal in the form of a LocalGeo
    virtual bool intersect(Ray & ray, float* thit, LocalGeo* local);
    // tests if a ray intersects this shape, returns true if so
    virtual bool intersectP(Ray & ray);
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
};

// GeometricPrimitive
class GeometricPrimitive : Primitive {
public:
    Transformation objToWorld, worldToObj;
    Shape* shape;
    Material* mat;
    GeometricPrimitive();
    virtual bool intersect(Ray & ray, float* thit, Intersection* in);
    virtual bool intersectP(Ray & ray);
    virtual void getBRDF(LocalGeo& local, BRDF* brdf);
};

// AggregatePrimitive
// TODO

// Material
// Stores a constant material used for shading calculations
class Material {
public:
    BRDF constantBRDF;
    Material(BRDF brdf);
    void getBRDF(LocalGeo& local, BRDF* brdf);
}
