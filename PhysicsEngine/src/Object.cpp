#include "Object.hpp"

namespace pe {
    Object::Object() {

        // Randomly initiating velocity and mass for now
        float randomXVelocity = pe::util::Random::getRandom(-10, 10);
        float randomYVelocity = pe::util::Random::getRandom(-10, 10);
        float randomMass = pe::util::Random::getRandom(1);

        velocity = pe::Vector2f(randomXVelocity, randomYVelocity);
        mass = randomMass;
        std::cout << "Object created with velocity : " << velocity._x << " " << velocity._y << std::endl;
    }

    Object::Object(Object& obj) {
        collider = obj.collider;
        transform = obj.transform;
        velocity = obj.velocity;
        force = obj.force;
        mass = obj.mass;
    }

    Object::~Object() {
        delete collider;
        delete transform;
    }
}