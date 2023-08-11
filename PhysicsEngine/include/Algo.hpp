#pragma once

#include <cmath>

#include "Vector.hpp"
#include "Transform.hpp"
#include "collider/CircleCollider.hpp"
#include "collider/AABBCollider.hpp"
#include "collider/BoxCollider.hpp"
#include "collider/LineCollider.hpp"
#include "ray/Ray.hpp"
#include "ray/RaycastResult.hpp"
#include "manifold/CollisionManifold.hpp"

namespace pe {
    namespace algo {
        static float PIE = (float)3.141592;
        static float FLOAT_MIN = (float)(1e-6);

        /**************************************************************/
        // HELPER functions
        /**************************************************************/
        
        /// Compares two floats 
        /// (https://realtimecollisiondetection.net/blog/?p=89) 
        bool compare(float x, float y, float epsilon);
        bool compare(float x, float y);
        bool compare(Vector2f a, Vector2f b);

        float degreeToRadian(float degree);
        float radianToDegree(float radian);

        // returns squared distance between two points
        float distanceSq( pe::Vector2f& point_a,  pe::Vector2f& point_b);
        float distance( pe::Vector2f& point_a,  pe::Vector2f& point_b);

        pe::Vector2f PointRotator(pe::Vector2f , float , pe::Vector2f );

        Vector2f getInterval(pe::AABBCollider* aabb, pe::Transform* transform, pe::Vector2f axis);
        Vector2f getInterval(pe::BoxCollider* box, pe::Transform* transform, pe::Vector2f axis);

        bool overlapOnAxis(pe::AABBCollider* aabbA, pe::Transform* transformA, pe::AABBCollider* aabbB, pe::Transform* transformB, pe::Vector2f axis);
        bool overlapOnAxis(pe::AABBCollider* aabb, pe::Transform* transformA, pe::BoxCollider* box, pe::Transform* transformB, pe::Vector2f axis);
        bool overlapOnAxis(pe::BoxCollider* boxA, pe::Transform* transformA, pe::BoxCollider* boxB, pe::Transform* transformB, pe::Vector2f axis);



        /**************************************************************/
        // POINT VS SHAPES
        /**************************************************************/

        bool checkPointLineCollision(pe::Vector2f&, pe::LineCollider*);

        bool checkPointCircleCollision(pe::Vector2f&, pe::CircleCollider* , pe::Transform* );

        bool checkPointAABBCollision(pe::Vector2f&, pe::AABBCollider*, pe::Transform*);

        bool checkPointBoxCollision(pe::Vector2f& , pe::BoxCollider* ,pe::Transform*);


        /**************************************************************/
        // LINE VS SHAPES
        /**************************************************************/

        bool checkLineCircleCollision(pe::LineCollider* ,pe::CircleCollider* , pe::Transform*);

        bool checkLineAABBCollision(pe::LineCollider* , pe::AABBCollider*, pe::Transform* );

        bool checkLineBoxCollision(pe::LineCollider* , pe::BoxCollider* , pe::Transform* );


        /**************************************************************/
        // Ray VS SHAPES
        /**************************************************************/

        bool raycastCircle(pe::CircleCollider* , pe::Transform*, Ray ray, RaycastResult result);

        bool raycastAABB(pe::AABBCollider*,pe::Transform*, Ray ray, RaycastResult& result);

        bool raycastBox(pe::BoxCollider*, pe::Transform*, Ray ray, RaycastResult& result);


        /**************************************************************/
        // Circle VS SHAPES
        /**************************************************************/

        bool checkCircleCircleCollision(pe::CircleCollider* , pe::Transform* , pe::CircleCollider* , pe::Transform*);

        bool checkCircleAABBCollision(pe::CircleCollider* circle, pe::Transform* transformCircle, pe::AABBCollider* aabb, pe::Transform* transformAABB);

        bool checkCircleBoxCollision(pe::CircleCollider* circle, pe::Transform* transformCircle, pe::BoxCollider* box, pe::Transform* transformBox);



        /**************************************************************/
        // AABB VS SHAPES
        /**************************************************************/

        bool checkAABBCircleCollision(pe::AABBCollider* aabb, pe::Transform* transformAABB, pe::CircleCollider* circle, pe::Transform* transformCircle);

        bool checkAABBAABBCollision(pe::AABBCollider* aabbA, pe::Transform* transformA, pe::AABBCollider* aabbB, pe::Transform* transformB);

        bool checkAABBBoxCollision(pe::AABBCollider* aabb, pe::Transform* transformA, pe::BoxCollider* box, pe::Transform* transformB);


        /**************************************************************/
        // BOX VS SHAPES
        /**************************************************************/

        bool checkBoxCircleCollision(pe::BoxCollider* box, pe::Transform* transformBox, pe::CircleCollider* circle, pe::Transform* transformCircle);

        bool checkBoxAABBCollision(pe::BoxCollider* box, pe::Transform* transformB, pe::AABBCollider* aabb, pe::Transform* transformA);

        bool checkBoxBoxCollision(pe::BoxCollider* boxA, pe::Transform* transformA, pe::BoxCollider* boxB, pe::Transform* transformB);


        /**************************************************************/
        // CONTACT POINTS
        /**************************************************************/
        Vector2f getClosestPointOnLineSegment(Vector2f targetPoint, Vector2f pointA, Vector2f pointB);

        std::vector<pe::Vector2f> findContactPoints(CircleCollider* circleA, Transform* transformA,
                                                    CircleCollider* circleB, Transform* transformB);

        std::vector<pe::Vector2f> findContactPoints(CircleCollider* circle, Transform* transformCircle,
                                                    BoxCollider* box,       Transform* transformBox);

        std::vector<pe::Vector2f> findContactPoints(CircleCollider* circle, Transform* transformCircle,
                                                    AABBCollider* box,      Transform* transformBox);

        std::vector<pe::Vector2f> findContactPoints(BoxCollider* boxA, Transform* transformA,
                                                    BoxCollider* boxB, Transform* transformB);

        
        /**************************************************************/
        // INERTIA
        /**************************************************************/

        float getBoxInertia(float mass, float width, float height);

        float getCircleInertia(float mass, float radius);

    }
}