#include "Bullet.h"
#include <SFML/Graphics.hpp>
#include<bits/stdc++.h>
#include<GameEntities.h>
#include<Vector.h>

Bullet::Bullet(Vector position, Vector angle, Vector radius)
{
    this->fpos.addCoefficient(position, 0);
    this->frot.addCoefficient(angle, 0);
    this->frad.addCoefficient(radius, 0);
    this->forient.addCoefficient(Vector(1, 0), 0);   // Default orientation is 0 degrees.
}

Bullet::~Bullet()
{

}

Bullet::Bullet(const Bullet& other){
    this->shape = new sf::CircleShape(*other.shape);

    this->fpos = *new Polynomial(other.fpos);
    this->frot = *new Polynomial(other.frot);
    this->fangle = *new Polynomial(other.fangle);
    this->ffire = *new Polynomial(other.ffire);
    this->frad = *new Polynomial(other.frad);

    this->lifespan = *new float(other.lifespan);
    this->visible = *new bool(other.visible);
    this->fireShape = *new Shape(other.fireShape);
    this->childTemplate = other.childTemplate;

    this->forient = *new Polynomial(other.forient);

}

Bullet& Bullet::operator=(const Bullet& other){
    if(this == &other)    return *this;

    this->shape = new sf::CircleShape(*other.shape);

    this->fpos = *new Polynomial(other.fpos);
    this->frot = *new Polynomial(other.frot);
    this->fangle = *new Polynomial(other.fangle);
    this->ffire = *new Polynomial(other.ffire);
    this->frad = *new Polynomial(other.frad);

    this->lifespan = *new float(other.lifespan);
    this->visible = *new bool(other.visible);
    this->fireShape = *new Shape(other.fireShape);
    this->childTemplate = other.childTemplate;

    this->forient = *new Polynomial(other.forient);

    return *this;
}

void Bullet::draw(Window& window, float time){
    if(this->isOutOfBounds(window))
        return;

    if(this->visible && !this->isDeleted)
        window.draw(*(this->shape));
}

void Bullet::update(float time){
    time = time - this->birthTime;

    Vector position = this->fpos.evaluate(time);
    Vector angle = this->frot.evaluate(time);
    Vector radius = this->frad.evaluate(time);
    Vector orientation = this->forient.evaluate(time);

    Vector motion = this->getMotionVector(position, angle, radius, orientation);
    sf::Vector2f m = sf::Vector2f(motion.x, motion.y);
    this->shape->setPosition(m);
}

Vector Bullet::getMotionVector(Vector position, Vector angle, Vector radius, Vector orientation){
    position.x += radius.x * cos(angle.x);
    position.y += radius.y * sin(angle.y);

    return position;
}

std::vector<Bullet*> Bullet::makeBullets(float time){
    std::vector<Bullet*> bullets;

    if(this->timesFired > 100){
        return bullets;
    }
    if(this->childTemplate == nullptr){
        return bullets;
    }

    time = time - this->birthTime;

    float angle = this->fangle.evaluate(time).x;
    float delay = this->fdelay.evaluate(time).x;
    float fireRate = sin(this->ffire.evaluate(time).x + delay);

    if(fireRate > 0 && !hasFired){
        hasFired = true;
        this->timesFired ++;

        std::vector<Vector> vertices = this->fireShape.getVertices();

        int vsize = vertices.size();

        for(int i = 0; i < vsize ; i++){
            Bullet* b = new Bullet(*this->childTemplate);
            float rotation = angle * PI / 180;
            Vector pos;
            pos.x = (vertices[i].x * cos(vertices[i].y));
            pos.y = (vertices[i].x * sin(vertices[i].y));

            float x = pos.x, y= pos.y;
            pos.x = x * cos(rotation) - y * sin(rotation);
            pos.y = y * cos(rotation) + x * sin(rotation);

            // To modify later when a new class for shapes is added
            Vector v = Vector(this->shape->getPosition().x, this->shape->getPosition().y);
            pos = pos + v;
            float tilt = rotation + vertices[i].y;


            b->getPositionFunction()->copyFunctionToThis(this->childTemplate->getPositionFunction(), tilt);
            b->getAngleFunction()->copyFunctionToThis(this->childTemplate->getAngleFunction(), tilt);
            b->getRotationFunction()->copyFunctionToThis(this->childTemplate->getRotationFunction(), tilt);


            b->fpos.getPolynomial(0)->addCoefficient(pos, 0);
            b->getPositionFunction()->setTilt(tilt);

            b->getPositionFunction()->makeContinuous();
            bullets.push_back(b);
        }

    }
    else if(fireRate < 0 && hasFired){
        hasFired = false;
    }

    return bullets;
}

Polynomial* Bullet::getPositionFunction(){
    return &(this->fpos);
}
Polynomial* Bullet::getRotationFunction(){
    return &(this->frot);
}
Polynomial* Bullet::getRadiusFunction(){
    return &(this->frad);
}

Polynomial* Bullet::getAngleFunction(){
    return &(this->fangle);
}

Polynomial* Bullet::getFireRateFunction(){
    return &(this->ffire);
}

Polynomial* Bullet::getOrientationFunction(){
    return &(this->forient);
}

Polynomial* Bullet::getFireDelayFunction(){
    return &(this->fdelay);
}

bool Bullet::isVisible(){
    return this->visible;
}

float Bullet::getBirthTime(){
    return this->birthTime;
}

float Bullet::getLifeSpan(){
    return this->lifespan;
}

void Bullet::setLifeSpan(float ls){
    this->lifespan = ls;
}

void Bullet::setBirthTime(float bt){
    this->birthTime = bt;
}

void Bullet::setFiringShape(Shape* shape){
    this->fireShape = *shape;
}

void Bullet::setColor(sf::Color color){
    this->shape->setFillColor(color);
}

void Bullet::setChildTemplate(Bullet* b){
    this->childTemplate = b;
}


bool Bullet::checkDeletion(float time){
    return !(time <= this->birthTime + this->lifespan || this->lifespan < 0);
}

bool Bullet::isOutOfBounds(Window& window){
    Vector position = Vector(this->shape->getPosition().x, this->shape->getPosition().y);
    float radius = this->shape->getRadius();
    Vector center = window.getCenter();
    Vector vsize = window.getSize();

    bool x = position.x + radius > center.x - vsize.x / 2 && position.x - radius< center.x + vsize.x / 2;
    bool y = position.y + radius > center.y - vsize.y / 2 && position.y - radius < center.y + vsize.x / 2;

    return !(x && y);

}


