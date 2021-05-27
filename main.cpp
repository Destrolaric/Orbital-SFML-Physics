#include <SFML/Graphics.hpp>
#include "OrbitalCalculator.h"
#include "Planet.h"
#include <iostream>
using namespace sf;


int main() {
    auto window = new RenderWindow(VideoMode(1000, 1000), "Gravitation stuff");
    Sprite sprite;
    Text text;
    Texture texture;

    std::vector<Planet> planets;

    OrbitalCalculator orbitalCalculator(planets);
    sprite.setTexture(texture);
    while (window->isOpen()) {
        sf::Event event;
        while (window->pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window->close();
            if (event.type == sf::Event::MouseButtonReleased){
                Planet planet = Planet(event.mouseButton.x, event.mouseButton.y, 10, 99909900, Vector2f(0, 0));
                orbitalCalculator.addPlanet(planet);
            }
        }
        orbitalCalculator.updatePlanetPositions();
        window->draw(sprite);
        for (auto &planet : orbitalCalculator.getPlanets()) {

            window->draw(planet.getPlanet());
        }
        window->display();
        window->clear();
    }
    delete (window);


}
