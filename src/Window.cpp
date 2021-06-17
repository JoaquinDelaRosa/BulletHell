#include "Window.h"
#include "SFML/Graphics.hpp"
#include "Vector.h"

Window::Window(void* w)
{
    this->window = (sf::RenderWindow*) w;
}

Vector Window::getCenter(){
    float x = this->window->getView().getCenter().x;
    float y = this->window->getView().getCenter().y;

    Vector v = Vector(x, y);
    return v;
}

Vector Window::getSize(){
    float x = this->window->getView().getSize().x;
    float y = this->window->getView().getSize().y;

    Vector v = Vector(x, y);
    return v;
}

void Window::draw(const sf::Drawable& entity){
    this->window->draw(entity);
}

sf::Window* Window::getWindow(){
    return this->window;
}
