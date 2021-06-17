#include "Container.h"
#include "SFML/Graphics.hpp"
#include "GameEntities.h"
#include <bits/stdc++.h>
#include "Vector.h"

// The container class contains bullets so that multiple configs can be loaded with only this
// class needing to be overridden
Container::Container()
{

}

void Container::initialize(float offset, Vector p0){

}

std::vector<Bullet*> Container::getBullets(){
    return this->bullets;
}
