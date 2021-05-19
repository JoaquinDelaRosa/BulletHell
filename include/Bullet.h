#ifndef BULLET_H
#define BULLET_H
#include <SFML/Graphics.hpp>
#include <Polynomial.h>
#include <Shape.h>
#include <Window.h>
#include <Vector.h>

class Bullet
{
    private:
        sf::CircleShape* shape = new sf::CircleShape(5);
        Polynomial fpos = Polynomial();             // Position function - controls the position of the center of mass of the bullet
        Polynomial frot = Polynomial();             // Rotation function - controls the angle of the forward direction of the bullet.
        Polynomial frad = Polynomial();             // Radius function, controls how far bullet is from center of mass
        float lifespan = -1;
        float birthTime;
        Polynomial forient = Polynomial();          // Orientation pertains to the angle off from the x-axis.

        bool visible = true;
        bool isDeleted = false;

        Polynomial ffire = Polynomial();
        Polynomial fangle = Polynomial();
        Polynomial fdelay = Polynomial();


        bool hasFired = false;
        int timesFired = 0;
        // Helper functions
        Vector getMotionVector(Vector position, Vector angle, Vector radius);

        Shape fireShape = Shape();
        Bullet* childTemplate = nullptr;

    public:
        Bullet(Vector position, Vector angle = Vector(0, 0), Vector radius = Vector(0, 0));
        Bullet(const Bullet& other);
        Bullet& operator=(const Bullet& other);
        void draw(Window& window, float time);
        void update(float time);
        std::vector<Bullet*> makeBullets(float time);

        Polynomial* getPositionFunction();
        Polynomial* getRotationFunction();
        Polynomial* getRadiusFunction();
        Polynomial* getFireRateFunction();
        Polynomial* getAngleFunction();
        Polynomial* getOrientationFunction();
        Polynomial* getFireDelayFunction();


        bool isVisible();
        bool isOutOfBounds(Window& window);

        float getBirthTime();
        float getLifeSpan();

        void setBirthTime(float bt);
        void setLifeSpan(float ls);
        void setColor(sf::Color color);
        bool checkDeletion(float time);

        void setFiringShape(Shape* shape);
        void setChildTemplate(Bullet* b);

        void setPositionFunction(Polynomial* p);


        ~Bullet();



};

#endif // BULLET_H
