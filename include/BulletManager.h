#ifndef BULLETMANAGER_H
#define BULLETMANAGER_H
#include<SFML/Graphics.hpp>
#include<Container.h>
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
        void loadContainer(Container* container, float time, Vector p0);
};

#endif // BULLETMANAGER_H
