#include "BulletManager.h"
#include "SFML/Graphics.hpp"
#include "GameEntities.h"
#include<bits/stdc++.h>
#include "Vector.h"

BulletManager::BulletManager()
{
    float SIZE = 100;
    float V = 1;
    Shape* fshape = new Shape();

    for(int i = 0; i < V; i ++){
        float angle = (i * 1.0f) / V * (2 * PI);
        fshape->addVertex(Vector(1 * cos(angle), 1 * sin(angle)));
    }

    for(int i = 0; i < SIZE; i ++){
        float angle = (i * 1.0f) / SIZE * 360;
        angle = (angle / (180) * PI);
        Bullet *b = new Bullet(Vector(0, 0), Vector(0, 90), Vector(0, 0) );
        b->getPositionFunction()->setUpperBound(-1);
        b->getPositionFunction()->setTilt(angle);
        b->getPositionFunction()->addCoefficient(Vector(200, 200), 1);


        Polynomial* p = new Polynomial(6);
        Polynomial* q = new Polynomial(18);
        Polynomial* r = new Polynomial(24);


        p->addCoefficient(Vector(10, 100), 1);
        q->addCoefficient(Vector(-100, 0 ), 1);
        p->addWrapper(Polynomial::SineY, 100, 1);
        p->addTerm(q);


        b->getPositionFunction()->makeContinuous();

        r->addCoefficient(Vector(0, 0), 1);
        r->addCoefficient(Vector(10, 10), 2);

        Bullet* temp = new Bullet(Vector(0, 0));
        temp->getPositionFunction()->addCoefficient(Vector(100, 0), 1);
        temp->getPositionFunction()->setUpperBound(3);
        temp->getPositionFunction()->addPolynomial(new Polynomial(*p));
        temp->getRotationFunction()->addCoefficient(Vector(1,1), 1);
        temp->getPositionFunction()->addPolynomial(new Polynomial(*q));
        temp->getPositionFunction()->addPolynomial(new Polynomial(*r));
        temp->getPositionFunction()->makeContinuous();

        if(i%2 == 0){
            b->getFireRateFunction()->addCoefficient(Vector(100, 1), 1);
            b->getAngleFunction()->addCoefficient(Vector(30 , 1), 1);
            b->setColor(sf::Color::Red);
            temp->setColor(sf::Color::Red);
            b->setFiringShape(fshape);
            b->setChildTemplate(temp);
        }
        else{
            b->getFireRateFunction()->addCoefficient(Vector(100, 1), 1);
            b->getAngleFunction()->addCoefficient(Vector(30 , 1), 1);
            b->setColor(sf::Color::Blue);
            temp->setColor(sf::Color::Blue);
            b->setFiringShape(fshape);
            b->setChildTemplate(temp);
        }
        this->addBullet(b, 0);
    }
}

void BulletManager::draw(Window& window, float time){
    for(int i = 0 ; i < (long int) this->bullets.size(); i ++){
        this->bullets[i]->draw(window, time);
    }
}

void BulletManager::update(float time){
    for(int i = 0 ; i < (long int) this->bullets.size(); i ++){
        if(this->bullets[i]->checkDeletion(time)){
            Bullet* temp = this->bullets[i];
            this->bullets.erase(this->bullets.begin() + i );
            delete temp;
            i--;
            continue;
        }
        this->bullets[i]->update(time);
        std::vector<Bullet*> newBullets = this->bullets[i]->makeBullets(time);

        this->addBullet(newBullets, time);
    }
}

void BulletManager::addBullet(Bullet* b, float time, float lifespan){
    b->setBirthTime(time);
    b->setLifeSpan(lifespan);
    this->bullets.push_back(b);
}

void BulletManager::addBullet(std::vector<Bullet*> b, float time){
    for(int i = 0; i < (int) b.size(); i++){
        this->addBullet(b[i], time, b[i]->getLifeSpan());
    }
}



