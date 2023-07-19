#include "Object.hpp"

namespace pe {
    Object::Object() {
        float randomXVelocity = pe::util::Random::getRandom(-10, 10);
        float randomYVelocity = pe::util::Random::getRandom(-10, 10);
        float randomMass = pe::util::Random::getRandom(10);

        velocity = pe::Vector2f(randomXVelocity, randomYVelocity);
        mass = randomMass;
        std::cout << velocity._x << " " << velocity._y << std::endl;
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