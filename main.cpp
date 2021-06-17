// TO - DO
// Implement parameterization of shapes by creating a vertex class which can be equipped with a polynomial
// Implement polynomial clamping


#include <SFML/Graphics.hpp>
#include <bits/stdc++.h>
#include<GameEntities.h>
#include<BulletManager.h>
#include<chrono>
#include<Vector.h>

#include <SamplePreset.h>
#define WIDTH 1000
#define HEIGHT 1000

int main()
{
    sf::RenderWindow renderWindow(sf::VideoMode(WIDTH, HEIGHT), "SFML works!");
    Window window = Window(&renderWindow);

    sf::View view(sf::Vector2f(0.0f, 0.0f), sf::Vector2f(WIDTH, HEIGHT ));
    std::chrono::steady_clock::time_point start = std::chrono::steady_clock::now();

    BulletManager bulletManager;

    while (renderWindow.isOpen())
    {
        std::chrono::steady_clock::time_point current = std::chrono::steady_clock::now();
        int time = std::chrono::duration_cast<std::chrono::milliseconds>(current - start).count();

        sf::Event event;
        while (renderWindow.pollEvent(event))
        {
            switch(event.type){
                case sf::Event::Closed:
                    renderWindow.close();
                    break;
                case sf::Event::Resized:
                    break;
                case sf::Event::MouseButtonPressed:
                    if(event.mouseButton.button == sf::Mouse::Left){
                        sf::Vector2i pos = sf::Mouse::getPosition(*window.getWindow());
                        Vector s =  window.getSize();
                        bulletManager.loadContainer(new SamplePreset(), float(time) / 1000.0f, Vector(pos.x - s.x / 2, pos.y - s.y / 2));
                    }

                    break;
                default:
                    break;
            }
        }


        renderWindow.clear();
        renderWindow.setView(view);

        bulletManager.draw(window, float(time) / 1000.0f);
        bulletManager.update(float(time) / 1000.0f);



        renderWindow.display();
    }



    return 0;
}
