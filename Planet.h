//
// Created by georg on 08.05.2021.
//

#ifndef PHYSICSSIMULATIONSTUFF_PLANET_H
#define PHYSICSSIMULATIONSTUFF_PLANET_H

#include <SFML/Graphics.hpp>

using namespace sf;

class Planet {
public:
    bool operator==(const Planet &planet1);

    long long int getMass() const;

    Vector2<float> getCenteredPosition();

    void setPosition(const Vector2f &position);

    void setMass(long long int mass);

    const Vector2f &getPosition() const;

    Planet(float x_pos, float y_pos, float radius, long long mass, Vector2f velocity);

    void addPlanet(Planet planet);

    Planet(float x_pos, float y_pos, float radius, long long mass, Image image, Vector2f velocity);

    const CircleShape &getPlanet() const;

    Vector2f getAcceleration();

    const Vector2f &getVelocity() const;

    void setAcceleration(const Vector2f &acceleration);

    void setVelocity(const Vector2f &velocity);

private:
    Image image;
    CircleShape planet;
public:
    void setPlanet(const CircleShape &planet);

private:
    Vector2f position, velocity, acceleration;
    long long mass;
};


#endif //PHYSICSSIMULATIONSTUFF_PLANET_H
