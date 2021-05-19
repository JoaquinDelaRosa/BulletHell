#ifndef VECTOR_H
#define VECTOR_H

class Vector
{
    public:
        float x;
        float y;

        Vector(float x, float y);
        Vector();
        virtual ~Vector();
        Vector(const Vector& other);
        Vector& operator=(const Vector& other);
        Vector operator+(const Vector& other);
        Vector operator-(const Vector& other);
        void operator+=(const Vector& other);
        void operator-=(const Vector& other);
        Vector operator*(const float& f);
};

#endif // VECTOR_H
