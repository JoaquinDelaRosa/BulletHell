#include "BulletManager.h"
#include "SFML/Graphics.hpp"
#include "GameEntities.h"
#include<bits/stdc++.h>
#include "Vector.h"

#include "SamplePreset.h"

BulletManager::BulletManager()
{
    SamplePreset *preset = new SamplePreset();
    //this->loadContainer(preset, 0);
}

void BulletManager::loadContainer(Container* container, float time, Vector p0){
    container->initialize(time, p0);

    std::vector<Bullet*> bs = container->getBullets();
    for(Bullet* b : bs){
        this->addBullet(b, time);
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



