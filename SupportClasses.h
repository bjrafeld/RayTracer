//Vector Class
class Vector;

class Vector {
    float x, y, z;
    
public:
	Vector();
    Vector(float x, float y, float z);
    const Vector operator+(const Vector v);
    const Vector operator-(const Vector v);
    const Vector operator*(const float scalar);
    const Vector operator/(const float scalar)
    Vector noramlize();
};

class Point;

//Point Class
class Point {
	float x, y, z;

public:
	Point();
	Point(float x, float y, float z);
	const Point operator+(Point p);
	const Point operator-(Point p);
}


// Shape Class
class Shape;

class Shape {

public:
    Shape();
    // tests if a ray intersects this shape, and if so, returns the intersection point and normal in the form of a LocalGeo
    virtual bool intersect(Ray & ray, float* thit, LocalGeo* local);
    // tests if a ray intersects this shape, returns true if so
    virtual bool intersect(Ray & ray);
}

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
}

// Triangle Class

class Triangle;

class Triangle : Shape{

public:
    float x,y,z;
    // tests if a ray intersects this shape, and if so, returns the intersection point and normal in the form of a LocalGeo
    virtual bool intersect(Ray & ray, float* thit, LocalGeo* local);
    // tests if a ray intersects this shape, returns true if so
    virtual bool intersect(Ray & ray);
}
