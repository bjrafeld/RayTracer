//Vector Class
class Vector;

class Vector {
    float x, y, z;
    
public:
	Vector();
    Vector(float x, float y, float z);
    Vector operator+(Vector v);
    Vector operator-(Vector v);
    Vector operator*(float scalar);
    Vector operator/(float scalar)
    Vector noramlize();
};

class Point;

//Point Class
class Point {
	float x, y, z;

public:
	Point();
	Point(float x, float y, float z);
	Point operator+(Point p);
	Point operator-(Point p);
}