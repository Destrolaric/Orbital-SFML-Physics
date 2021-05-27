//
// Created by georg on 08.05.2021.
//

#ifndef PHYSICSSIMULATIONSTUFF_ORBITALCALCULATOR_H
#define PHYSICSSIMULATIONSTUFF_ORBITALCALCULATOR_H

#include <SFML/Graphics.hpp>
#include <vector>
#include <thread>
#include "Planet.h"
#include <atomic>
#include <mutex>

using namespace sf;

class OrbitalCalculator {
private:

    float tick = 10;
    std::mutex mutex;
    std::vector<Planet> planets;

    static Vector2<float> normalize(const Vector2<float> &source);


    void calculateVelocity(Planet &planet, bool &flag);

    bool processCollision(Planet &planet, Planet &second_planet);

public:
    const std::vector<Planet> &getPlanets() const;
    void deletePlanet(const Planet& planet);
    void addPlanet(Planet planet);

    explicit OrbitalCalculator(const std::vector<Planet> &planets);

    void updatePlanetPositions();

    void updatePlanet(Planet &planet);

    bool isCollided(Planet &planet, Planet &second_planet);

    static Vector2<float> calculateForceTowardsPlanet(Planet &planet, Planet &second_planet);
};


#endif //PHYSICSSIMULATIONSTUFF_ORBITALCALCULATOR_H
