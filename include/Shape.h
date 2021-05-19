#ifndef SHAPE_H
#define SHAPE_H
#include<bits/stdc++.h>
#include<SFML/Graphics.hpp>
#include<Vector.h>

class Shape
{
    protected:
        std::vector<Vector> vertices = std::vector<Vector>();

    public:
        Shape();
        virtual ~Shape();
        Shape(const Shape& other);
        Shape& operator=(const Shape& other);

        void addVertex(Vector v);
        void removeVertex(Vector v);
        std::vector<Vector> getVertices();
};

#endif // SHAPE_H
