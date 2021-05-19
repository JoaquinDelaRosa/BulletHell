#include "Shape.h"
#include<bits/stdc++.h>
#include<Vector.h>
#include<SFML/Graphics.hpp>

Shape::Shape()
{

}

Shape::~Shape()
{
    //dtor
}

Shape::Shape(const Shape& other)
{
    this->vertices = other.vertices;

}

Shape& Shape::operator=(const Shape& rhs)
{
    if (this == &rhs) return *this; // handle self assignment
        this->vertices = rhs.vertices;
    return *this;
}

void Shape::addVertex(Vector v){
    float x = v.x;
    float y = v.y;

    // Convert into polar coordinates
    v.x = sqrt(x * x + y * y);
    v.y = atan2(y, x);                  // In radians
    this->vertices.push_back(v);
}

void Shape::removeVertex(Vector v){
    int vertexCount = this->vertices.size();
    for(int i = 0; i < vertexCount; i ++){
        if(vertices[i].x == v.x && vertices[i].y == v.y){
            this->vertices.erase(this->vertices.begin() + i);
            return;
        }
    }
}



std::vector<Vector> Shape::getVertices(){
    return this->vertices;
}
