using namespace std;//Vector Class


class Vector;
class Point;

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