
#ifndef COLLISIONS
#define COLLISIONS 

#include "../libs/raylib/raylib.h"
#include "../libs/raylib/raymath.h"

static inline float GetRandomFloat(float min, float max) {
    return min + ((float)rand() / (float)RAND_MAX) * (max - min);
}

static inline Vector2 RandomPointOnLine(Vector2 p1, Vector2 p2) {
  float t = 0;

  while(t < 0.3 || t > 0.7){
    t = (float)rand() / (float)RAND_MAX; 
  }
 
    Vector2 randomPoint = Vector2Add(p1, Vector2Scale(Vector2Subtract(p2, p1), t));
    return randomPoint;
}

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

static inline bool pointInPolygon(Vector2 point, Vector2 *polygon, int vertexCount) {
    bool inside = false;

    // Loop through each edge of the polygon
    for (int i = 0, j = vertexCount - 1; i < vertexCount; j = i++) {
        // Get the vertices of the polygon edge
        Vector2 vi = polygon[i];
        Vector2 vj = polygon[j];

        // Check if the point is between the y-values of the vertices and the point's x is to the left of the edge
        if (((vi.y > point.y) != (vj.y > point.y)) &&
            (point.x < (vj.x - vi.x) * (point.y - vi.y) / (vj.y - vi.y) + vi.x)) {
            inside = !inside;  // Toggle inside/outside status
        }
    }

    return inside;
}


static inline bool circleLineCollision(Vector2 circleCenter, float radius, Vector2 lineStart, Vector2 lineEnd, Vector2 *collisionPoint) {
    // Vector from line start to line end
    Vector2 lineDir = Vector2Subtract(lineEnd, lineStart);

    // Vector from line start to circle center
    Vector2 toCircle = Vector2Subtract(circleCenter, lineStart);

    // Get the projection of the circle center onto the line
    float lineLength = Vector2Length(lineDir);
    float dot = Vector2DotProduct(toCircle, lineDir) / (lineLength * lineLength);

    // Clamp the projection value to ensure the point lies on the line segment
    dot = Clamp(dot, 0.0f, 1.0f);

    // Find the closest point on the line
    *collisionPoint = Vector2Add(lineStart, Vector2Scale(lineDir, dot));

    // Check the distance from the closest point to the circle center
    float distanceToCircle = Vector2Distance(*collisionPoint, circleCenter);

    // Collision occurs if the distance is less than or equal to the radius
    return distanceToCircle <= radius;
}

static inline bool sweptCircleLineCollision(Vector2 circleStart, Vector2 circleEnd, float radius, Vector2 lineStart, Vector2 lineEnd, Vector2 *collisionPoint, float *t) {
    Vector2 velocity = Vector2Subtract(circleEnd, circleStart);

    // Early out if the player is not moving
    if (Vector2Length(velocity) == 0) return false;

    // Check for initial overlap with the line
    if (circleLineCollision(circleStart, radius, lineStart, lineEnd, collisionPoint)) {
        *t = 0.0f;
        return true;
    }

    // Expand the line by the circle's radius (as if the line is thickened)
    Vector2 lineDir = Vector2Subtract(lineEnd, lineStart);
    Vector2 perpLineDir = Vector2Normalize((Vector2){-lineDir.y, lineDir.x});  // Perpendicular to the line

    // Shift the line to create a thickened line for CCD
    Vector2 shiftedLineStart = Vector2Add(lineStart, Vector2Scale(perpLineDir, radius));
    Vector2 shiftedLineEnd = Vector2Add(lineEnd, Vector2Scale(perpLineDir, radius));

    // Use parametric line-circle intersection to find the first point of contact
    float lineLength = Vector2Length(lineDir);
    Vector2 toCircle = Vector2Subtract(circleStart, shiftedLineStart);

    float dot = Vector2DotProduct(toCircle, lineDir) / (lineLength * lineLength);
    dot = Clamp(dot, 0.0f, 1.0f);  // Clamp to the line segment

    Vector2 closestPoint = Vector2Add(shiftedLineStart, Vector2Scale(lineDir, dot));
    float distance = Vector2Distance(closestPoint, circleStart);

    if (distance <= radius) {
        *collisionPoint = closestPoint;
        *t = distance / Vector2Length(velocity);  // Time to collision
        return true;
    }
    return false;
}

// Resolve the collision using reflection and moving the player
static inline void resolveCollision(Vector2 *circleCenter, Vector2 *velocity, Vector2 lineStart, Vector2 lineEnd, Vector2 collisionPoint) {
    // Get the normal of the line (perpendicular)
    Vector2 lineDir = Vector2Subtract(lineStart, lineEnd);
  
    Vector2 normal = Vector2Normalize((Vector2){-lineDir.y, lineDir.x});

    // Reflect the velocity
    float dot = Vector2DotProduct(*velocity, normal);
    *velocity = Vector2Subtract(*velocity, Vector2Scale(normal, 1.0f * dot));

    // Move the circle out of collision (optional, depending on how deep it's in)
    Vector2 toCollisionPoint = Vector2Subtract(*circleCenter, collisionPoint);
    *circleCenter = Vector2Add(*circleCenter, Vector2Scale(normal, Vector2Length(toCollisionPoint)));
}

#endif // !COLLISIONSj
