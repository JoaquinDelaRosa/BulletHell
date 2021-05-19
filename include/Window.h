#ifndef WINDOW_H
#define WINDOW_H
#include<SFML/Graphics.hpp>
#include<Vector.h>

class Window
{
    private: sf::RenderWindow* window;
    public:
        Window(void* window);
        virtual Vector getCenter();
        virtual Vector getSize();
        virtual void draw(const sf::Drawable& entity);

};

#endif // WINDOW_H
