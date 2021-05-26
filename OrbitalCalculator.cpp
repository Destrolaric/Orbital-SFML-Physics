//
// Created by georg on 08.05.2021.
//


#include <mutex>
#include <cmath>
#include "OrbitalCalculator.h"
#include <iostream>

//creates threads for each planets, which will update their position dependent on gravity force on that moment;
void OrbitalCalculator::updatePlanetPositions() {
    auto *threads = new std::vector<std::thread *>();
    for (int i = 0; i< planets.size(); i++) {
        auto thread = new std::thread(&OrbitalCalculator::updatePlanet,this, std::ref(planets[i]));
        thread->join();
        threads->push_back(thread);
    }

}

Vector2<float> OrbitalCalculator::normalize(const Vector2<float> &source) {
    float length = sqrt((source.x * source.x) + (source.y * source.y));
    if (length != 0)
        return {source.x / length, source.y / length};
    else
        return source;
}

void OrbitalCalculator::updatePlanet(Planet &planet) {
    calculateVelocity(planet);
    Vector2f pos = planet.getPosition() + planet.getVelocity() * tick;
    planet.setPosition(pos);

}

void OrbitalCalculator::calculateVelocity(Planet &planet) {
    planet.setAcceleration(calculateForceTowardsPlanet(planet) / (float)planet.getMass() * tick);
    planet.setVelocity(planet.getVelocity() + planet.getAcceleration());
}

/**
 *
 * @param planets
 * @returns this
 */
OrbitalCalculator::OrbitalCalculator(const std::vector<Planet> &planets) {
    this->planets.assign(planets.cbegin(), planets.cend());
}

Vector2<float> OrbitalCalculator::calculateForceTowardsPlanet(Planet &planet) {
    Vector2<float> F;
    for (auto &i : planets) {
        if (i.getPosition() != planet.getPosition()) {
            mutex.lock();
            float bodyForce;
            bodyForce =- (0.000000000066742f * planet.getMass() * i.getMass() /
                         (pow(i.getPosition().x - planet.getPosition().x, 2) +
                          pow(i.getPosition().y - planet.getPosition().y, 2)));
            Vector2f direction = normalize(planet.getPosition() - i.getPosition());
            F += direction * bodyForce;
            mutex.unlock();
        }
    }
    return F;
}

const std::vector<Planet> &OrbitalCalculator::getPlanets() const {
    return planets;
}

void OrbitalCalculator::addPlanet(Planet planet) {
    planets.push_back(planet);
}



