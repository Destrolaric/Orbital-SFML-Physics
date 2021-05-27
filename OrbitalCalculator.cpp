//
// Created by georg on 08.05.2021.
//


#include <mutex>
#include <cmath>
#include "OrbitalCalculator.h"
#include <iostream>
#define  G 0.000000000066742f
//creates threads for each planets, which will update their position dependent on gravity force on that moment;
void OrbitalCalculator::updatePlanetPositions() {
    auto *threads = new std::vector<std::thread *>();
    if (planets.empty()) {
        return;
    }
    for (int i = 0; i < planets.size(); i++) {
      auto thread = new std::thread(&OrbitalCalculator::updatePlanet, this, std::ref(planets[i]));
      updatePlanet(planets[i]);
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
    bool flag = false;
    calculateVelocity(planet, flag);
    if (flag) return;
    Vector2f pos = planet.getPosition() + planet.getVelocity() * tick;
    planet.setPosition(pos);

}

void OrbitalCalculator::calculateVelocity(Planet &planet, bool &flag) {
    Vector2<float> F;
    for (auto &i : planets) {
        if (&i != &planet) {

            if (isCollided(planet, i)) {
                mutex.lock();
                if (processCollision(planet, i)) {
                    mutex.unlock();
                    flag = true;
                    return; // planet is destroyed, no reason to process it anymore
                } else {
                    mutex.unlock();
                    continue; // planet is alive and now much bigger
                }
            }

            F += calculateForceTowardsPlanet(planet, i);
        }
    }
    planet.setAcceleration(F / (float) planet.getMass() * tick);
    planet.setVelocity(planet.getVelocity() + planet.getAcceleration());
}


/**
 *
 * @param planets
 * @returns this
 */
bool OrbitalCalculator::isCollided(Planet &planet, Planet &second_planet) {
    double dist = sqrt(pow(planet.getCenteredPosition().x - second_planet.getCenteredPosition().x, 2) +
                       pow(planet.getCenteredPosition().y - second_planet.getCenteredPosition().y, 2));
    double rad = second_planet.getPlanet().getRadius() + planet.getPlanet().getRadius();
    return dist <= rad;

}

OrbitalCalculator::OrbitalCalculator(const std::vector<Planet> &planets) {
    this->planets.assign(planets.cbegin(), planets.cend());
}

Vector2<float> OrbitalCalculator::calculateForceTowardsPlanet(Planet &planet, Planet &second_planet) {
    float bodyForce;
    bodyForce = (float) -(G * planet.getMass() * second_planet.getMass() /
                          (pow(second_planet.getCenteredPosition().x - planet.getCenteredPosition().x, 2) +
                           pow(second_planet.getCenteredPosition().y - planet.getCenteredPosition().y, 2)));
    Vector2f direction = normalize(planet.getCenteredPosition() - second_planet.getCenteredPosition());
    return direction * bodyForce;
}

const std::vector<Planet> &OrbitalCalculator::getPlanets() const {
    return planets;
}

void OrbitalCalculator::addPlanet(Planet planet) {
    planets.push_back(planet);
}

/**
 *
 * @param planet
 * @param second_planet
 * @return [bool] Main planet destroyed?
 */
bool OrbitalCalculator::processCollision(Planet &planet, Planet &second_planet) {
    if (second_planet.getMass() > planet.getMass()) {
        auto pVelocity =
                Vector2<float>(planet.getVelocity().x * planet.getMass() / second_planet.getMass(),
                               planet.getVelocity().y * planet.getMass() / second_planet.getMass() );
        second_planet.setVelocity(second_planet.getVelocity() + pVelocity);
        auto planetobj = second_planet.getPlanet();
        planetobj.setRadius(second_planet.getPlanet().getRadius() + planet.getPlanet().getRadius());
        second_planet.setMass(second_planet.getMass() + planet.getMass());
        second_planet.setPlanet(planetobj);
        deletePlanet(planet);
        return true;
    } else {
        auto pVelocity =
                Vector2<float>(second_planet.getVelocity().x * second_planet.getMass() / planet.getMass(),
                               second_planet.getVelocity().y * second_planet.getMass() / planet.getMass());
        planet.setVelocity(planet.getVelocity() + pVelocity);
        auto planetobj = planet.getPlanet();
        planet.setMass(second_planet.getMass() + planet.getMass());
        planetobj.setRadius(second_planet.getPlanet().getRadius() + planet.getPlanet().getRadius());
        planet.setPlanet(planetobj);
        deletePlanet(second_planet);
        return false;
    }
}

void OrbitalCalculator::deletePlanet(const Planet &planet) {
    auto position = std::find(planets.begin(), planets.end(), planet);
    if (position != planets.end())
        planets.erase(position);
}