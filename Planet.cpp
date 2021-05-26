//
// Created by georg on 08.05.2021.
//

#include "Planet.h"

using namespace sf;

Planet::Planet(float x_pos, float y_pos, float radius, long long mass, Vector2f velocity) : position(x_pos, y_pos) {
    planet.setRadius(radius);
    planet.setPosition(x_pos, y_pos);
    planet.setFillColor(Color::Red);
    acceleration = Vector2f(0, 0);
    this->velocity = Vector2f(velocity.x / 1000, velocity.y / 1000);

    this->mass = mass;
}

Vector2f Planet::getAcceleration() {
    return acceleration;
}

Planet::Planet(float x_pos, float y_pos, float radius, long long mass, Image image, Vector2f velocity) {
    planet.setRadius(radius);
    planet.setPosition(x_pos, y_pos);
    Texture *texture = new Texture();
    texture->loadFromImage(image);
    planet.setTexture(texture);
    this->velocity = Vector2f(velocity.x / 1000, velocity.y / 1000);
    acceleration = Vector2f(0, 0);
    this->image = image;
    this->mass = mass;

}

long long Planet::getMass() const {
    return mass;
}

const Vector2f &Planet::getPosition() const {
    return planet.getPosition();
}

void Planet::setPosition(const Vector2f &position1) {
    planet.setPosition(position1);
    Planet::position = position1;
}

void Planet::setVelocity(const Vector2f &velocity) {
    Planet::velocity = velocity;
}

void Planet::setAcceleration(const Vector2f &acceleration) {
    Planet::acceleration = acceleration;
}

const Vector2f &Planet::getVelocity() const {
    return velocity;
}

const CircleShape &Planet::getPlanet() const {
    return planet;
}
