#ifndef CONTAINER_H
#define CONTAINER_H

#include <SFML/Graphics.hpp>
#include <GameEntities.h>
#include<bits/stdc++.h>
#include <Vector.h>
class Container
{
    protected:
        std::vector<Bullet*> bullets;

    public:
        Container();
        virtual void initialize(float offset, Vector p0);
        std::vector<Bullet*> getBullets();
};

#endif // CONTAINER_H
