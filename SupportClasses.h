//Vector Class


class Vector;
class Point;
class Normal;
class Ray;
class Color;
class Sample;
class LocalGeo;
class BRDF;

class Vector {
public:
	float x, y, z;
	Vector();
    Vector(float x, float y, float z);
    Vector operator+(Vector v);
    Vector operator-(Vector v);
    Vector operator*(float scalar);
    Vector operator/(float scalar);
    Vector normalize();
    static Vector pointSubtraction(Point target_point, Point initial_point);
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
	Vector dir;
	float t_min, t_max;
	Ray();
	Ray(Point p, Vector v, float t_min, float t_max);
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