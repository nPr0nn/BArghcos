
#ifndef COLLISIONS
#define COLLISIONS 

#include "../libs/raylib/raylib.h"
#include "../libs/raylib/raymath.h"

// POINT/CIRCLE
static inline bool pointCircle(Vector2 point, Vector2 center, float radius) {
    // Calculate the distance between the point and the circle's center
    float distance = Vector2Distance(point, center);

    // Check if the point is inside the circle
    return distance <= radius;
}

// LINE/POINT
static inline bool linePoint(Vector2 start, Vector2 end, Vector2 point) {
    // Get distance from the point to the two ends of the line
    float d1 = Vector2Distance(point, start);
    float d2 = Vector2Distance(point, end);

    // Get the length of the line
    float lineLen = Vector2Distance(start, end);

    // Add a small buffer for floating point precision
    float buffer = 0.1f;

    // Check if the sum of the distances is approximately equal to the line length
    return (d1 + d2 >= lineLen - buffer && d1 + d2 <= lineLen + buffer);
}

// LINE/CIRCLE
static inline bool lineCircle(Vector2 start, Vector2 end, Vector2 center, float radius) {
    // Check if either end is inside the circle
    if (pointCircle(start, center, radius) || pointCircle(end, center, radius)) {
        return true;
    }

    // Vector from start to end
    Vector2 lineDir = Vector2Subtract(end, start);

    // Distance between the start point and the circle center
    Vector2 toCircle = Vector2Subtract(center, start);

    // Get the projection of the circle center onto the line
    float lineLen = Vector2Length(lineDir);
    float dot = Vector2DotProduct(toCircle, lineDir) / (lineLen * lineLen);

    // Calculate the closest point on the line to the circle's center
    Vector2 closest = Vector2Add(start, Vector2Scale(lineDir, dot));

    // Check if the closest point is actually on the line segment
    if (!linePoint(start, end, closest)) {
        return false;
    }

    // Check the distance from the closest point to the circle center
    float distanceToCenter = Vector2Distance(closest, center);

    return distanceToCenter <= radius;
}

// NORMAL OF A LINE SEGMENT
static inline Vector2 lineNormal(Vector2 start, Vector2 end) {
    // Get the direction vector of the line
    Vector2 direction = Vector2Subtract(end, start);

    // The normal is perpendicular to the direction vector
    Vector2 normal = { -direction.y, direction.x };

    // Normalize the normal vector
    return Vector2Normalize(normal);
}

#endif // !COLLISIONSj
