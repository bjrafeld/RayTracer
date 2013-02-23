//Vector Class

class Vector;

class Vector {
    float x, y, z;
    
public:
    Vector(float x, float y, float z);
    Vector operator+(Vector v);
    Vector operator-(Vector v);
    Vector operator*(Vector v);
    Vector operator/(Vector v)
    Vector noramlize();
};