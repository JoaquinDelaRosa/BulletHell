#include "Vector.h"

Vector::Vector(float x, float y)
{
    this->x = x;
    this->y = y;
}

Vector::Vector(){
    this->x = 0;
    this->y =0;
}

Vector::~Vector()
{
    //dtor
}

Vector::Vector(const Vector& other)
{
    this->x = other.x;
    this->y = other.y;
}

Vector& Vector::operator=(const Vector& rhs)
{
    if (this == &rhs) return *this; // handle self assignment
    this->x = rhs.x;
    this->y = rhs.y;
    return *this;
}

Vector Vector::operator+(const Vector& other){
    return Vector(other.x + this->x, other.y + this->y);
}

Vector Vector::operator-(const Vector& other){
    return Vector(other.x - this->x, other.y - this->y);
}

void Vector::operator+=(const Vector& other){
    this->x += other.x;
    this->y += other.y;
}

void Vector::operator-=(const Vector& other){
    this->x -= other.x;
    this->y -= other.y;
}

Vector Vector::operator*(const float& f){
    return Vector(this->x * f, this->y * f);
}
