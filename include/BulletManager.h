#ifndef BULLETMANAGER_H
#define BULLETMANAGER_H
#include<SFML/Graphics.hpp>
#include<GameEntities.h>
#include<bits/stdc++.h>

class BulletManager
{
    private:
        std::vector<Bullet*> bullets;

    public:
        BulletManager();
        void draw(Window& window, float time);
        void update(float time);
        void addBullet(Bullet* b, float time, float lifeSpan = -1);
        void addBullet(std::vector<Bullet*> b, float time);
};

#endif // BULLETMANAGER_H
