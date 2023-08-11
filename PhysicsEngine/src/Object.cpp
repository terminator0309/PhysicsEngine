#include "Object.hpp"

namespace pe {
    Object::Object() {

        // Randomly initiating velocity and mass for now
        float randomXVelocity = pe::util::Random::getRandom(-2, 2);
        float randomYVelocity = pe::util::Random::getRandom(-2, 2);
        float randomMass = 10;

        velocity = pe::Vector2f(randomXVelocity, randomYVelocity);
        mass = randomMass;
        inverseMass = 1 / mass;
        //cor = pe::util::Random::getRandom((float)0.7, (float)1);
        cor = 0.2f;
        isStatic = false;
        angularVelocity = 0;
    }

    Object::Object(Object& obj) {
        collider = obj.collider;
        transform = obj.transform;
        velocity = obj.velocity;
        force = obj.force;
        mass = obj.mass;
    }

    void Object::setMass(float mass) {
        this->mass = mass;
        if (mass == 0.0f) {
            isStatic = true;
            inverseMass = 0.0f;
            angularVelocity = 0;
        }
        else
            inverseMass = 1 / mass;
    }

    float Object::getMass() {
        return mass;
    }

    float Object::getInverseMass() {
        return inverseMass;
    }

    void Object::setInertia(float inertia) {
        this->inertia = inertia;
        if (inertia == 0.0f) {
            inverseInertia = 0.0f;
        }
        else
            inverseInertia = 1 / inertia;
    }

    float Object::getInertia() {
        return inertia;
    }

    float Object::getInverseInertia() {
        return inverseInertia;
    }

    bool Object::getStatic() {
        return isStatic;
    }

    Vector2f Object::getPosition() {
        return transform->position;
    }
    void Object::setPosition(Vector2f position) {
        transform->position = position;
    }
    float Object::getRotation() {
        return transform->rotation;
    }
    void Object::setRotation(float rotation) {
        transform->rotation = rotation;
    }

    Object::~Object() {
        delete collider;
        delete transform;
    }
}