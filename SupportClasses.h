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

class Normal {
public:
	float x, y, z;
	Normal();
	Normal(float x, float y, float z);
	Normal operator+(Normal n);
	Normal operator-(Normal n);
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

class Matrix {
public:
	vector< vector <float> > mat;
	Matrix();
	Matrix(vector< vector<float> > input);
	static Matrix createTranslationMatrix(float tx, float ty, float tz);
	static Matrix createScalarMatrix(float sx, float sy, float sz);
};


// Shape Class
class Shape;

class Shape {

public:
    Shape();
    // tests if a ray intersects this shape, and if so, returns the intersection point and normal in the form of a LocalGeo
    virtual bool intersect(Ray & ray, float* thit, LocalGeo* local);
    // tests if a ray intersects this shape, returns true if so
    virtual bool intersect(Ray & ray);
};

// Sphere Class
class Sphere;

class Sphere : Shape{

public:
    Point center;
    float radius;

    Sphere();
    Sphere(Point c, float r);
    // tests if a ray intersects this shape, and if so, returns the intersection point and normal in the form of a LocalGeo
    virtual bool intersect(Ray & ray, float* thit, LocalGeo* local);
    // tests if a ray intersects this shape, returns true if so
    virtual bool intersect(Ray & ray);
};

// Triangle Class

class Triangle;

class Triangle : Shape{

public:
    Triangle();

    // tests if a ray intersects this shape, and if so, returns the intersection point and normal in the form of a LocalGeo
    virtual bool intersect(Ray & ray, float* thit, LocalGeo* local);
    // tests if a ray intersects this shape, returns true if so
    virtual bool intersect(Ray & ray);
};
