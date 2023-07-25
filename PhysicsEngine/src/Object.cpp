#include "Object.hpp"

namespace pe {
    Object::Object() {

        // Randomly initiating velocity and mass for now
        float randomXVelocity = pe::util::Random::getRandom(-10, 10);
        float randomYVelocity = pe::util::Random::getRandom(-10, 10);
        float randomMass = 10;

        velocity = pe::Vector2f(randomXVelocity, randomYVelocity);
        mass = randomMass;
        inverseMass = 1 / mass;
        cor = pe::util::Random::getRandom((float)0.7, (float)1);
        std::cout << "Object created with velocity : " << velocity._x << " " << velocity._y << std::endl;
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
        if (mass == 0.0f)
            inverseMass = 0.0f;
        else
            inverseMass = 1 / mass;
    }

    float Object::getMass() {
        return mass;
    }

    float Object::getInverseMass() {
        return inverseMass;
    }

    Object::~Object() {
        delete collider;
        delete transform;
    }
}