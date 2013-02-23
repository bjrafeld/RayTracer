//Vector Class
class Vector;

class Vector {
    float x, y, z;
    
public:
	Vector();
    Vector(float x, float y, float z);
    const Vector operator+(const Vector &v);
    const Vector operator-(const Vector &v);
    const Vector operator*(const float &scalar);
    const Vector operator/(const float &scalar)
    Vector noramlize();
};

class Point;

//Point Class
class Point {
	float x, y, z;

public:
	Point();
	Point(float x, float y, float z);
	const Point operator+(Point &p);
	const Point operator-(Point &p);
}