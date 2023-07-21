#pragma once

#include <cmath>

#include "Vector.hpp"

namespace pe {
    namespace algo {
        static float PIE = (float)3.141592;
        static float FLOAT_MIN = (float)(1e-6);

        /// <summary>
        /// Compares two floats 
        /// (https://realtimecollisiondetection.net/blog/?p=89) 
        /// </summary>
        /// <param name="x">First float</param>
        /// <param name="y">Second float</param>
        /// <param name="epsilon">Tolerance</param>
        /// <returns>Whether given floats are within tolerance</returns>
        bool compare(float& x, float& y, float epsilon);
        bool compare(float& x, float& y);

        float degreeToRadian(float degree);
        float radianToDegree(float radian);

        // returns squared distance between two points
        float distance2(const pe::Vector2f& point_a, const pe::Vector2f& point_b);
        float distance(const pe::Vector2f& point_a, const pe::Vector2f& point_b);

        /// <summary>
        /// Rotates the point
        /// </summary>
        /// <param name="">Coordinates of the point to be rotated</param>
        /// <param name="">Angle of rotation in anti-clockwise</param>
        /// <param name="">(Optional argument: defaults to 0,0) Point about which rotate</param>
        /// <returns>Rotated point</returns>
        pe::Vector2f PointRotator(pe::Vector2f& , float , pe::Vector2f );

        /// <summary>
        /// Checks circle to circle collision
        /// </summary>
        /// <param name="">radius of first circle</param>
        /// <param name="">center of first circle</param>
        /// <param name="">radius of second circle</param>
        /// <param name="">center of second circle</param>
        /// <returns>true if circles do collide; else false</returns>
        bool checkCircleCircleCollision(float , pe::Vector2f& , float , pe::Vector2f& );


        /**************************************************************/
        // POINT VS SHAPES
        /**************************************************************/


        /// <summary>
        /// Checks whether point in on the line
        /// </summary>
        /// <param name="">Coordinates of point</param>
        /// <param name="">Start coordinates of line</param>
        /// <param name="">End coordinates of line</param>
        /// <returns>True if point is on the line</returns>
        bool checkPointLineCollision(pe::Vector2f&, pe::Vector2f&, pe::Vector2f&);

        /// <summary>
        /// Checks whether point is in the circle (including on the circle)
        /// </summary>
        /// <param name="">Coordinates of point</param>
        /// <param name="">Radius of circle</param>
        /// <param name="">Center of circle</param>
        /// <returns>True if point is in the circle</returns>
        bool checkPointCircleCollision(pe::Vector2f&, float&, pe::Vector2f&);

        /// <summary>
        /// Checks whether point is in the AABB box
        /// </summary>
        /// <param name="">Coordinates of point</param>
        /// <param name="">Top-left(min) coordinate of AABB</param>
        /// <param name="">Bottom-right(max) coordinate of AABB</param>
        /// <returns>True if point is in the AABB</returns>
        bool checkPointAABBCollision(pe::Vector2f&, pe::Vector2f&, pe::Vector2f&);

        /// <summary>
        /// Checks whether point is in the OBB box
        /// </summary>
        /// <param name="point">: Coordinates of point</param>
        /// <param name="min">: Top-left(min) coordinate of box</param>
        /// <param name="max">: Bottom-right(max) coordinate of box</param>
        /// <param name="theta">: Angle of rotation</param>
        /// <param name="center">: Center coordinates of the box</param>
        /// <returns>True if point is in the box</returns>
        bool checkPointBoxCollision(pe::Vector2f& point, pe::Vector2f& min, pe::Vector2f& max, float theta, pe::Vector2f& center);


        /**************************************************************/
        // LINE VS SHAPES
        /**************************************************************/

        bool checkLineCircleCollision(pe::Vector2f& lineStart, pe::Vector2f& lineEnd, float& radius, pe::Vector2f& center);
    }
}