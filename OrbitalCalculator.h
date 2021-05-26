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
    static Vector2<float> normalize(const Vector2<float> &source);

    Vector2<float> calculateForceTowardsPlanet(Planet &planet);

    void calculateVelocity(Planet &planet);

public:
    const std::vector<Planet> &getPlanets() const;

    void addPlanet(Planet planet);

private:
    float tick = 10;

    std::mutex mutex;
    std::vector<Planet> planets;
public:

    explicit OrbitalCalculator(const std::vector<Planet> &planets);

    void updatePlanetPositions();

    void updatePlanet(Planet &planet);

};


#endif //PHYSICSSIMULATIONSTUFF_ORBITALCALCULATOR_H
