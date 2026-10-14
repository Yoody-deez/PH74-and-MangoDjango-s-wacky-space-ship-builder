#pragma once
struct Vector3 {
    float x;
    float y;
    float z;

    Vector3(float xCoord = 0.0f, float yCoord = 0.0f, float zCoord = 0.0f) 
        : x(xCoord), y(yCoord), z(zCoord) {}
};