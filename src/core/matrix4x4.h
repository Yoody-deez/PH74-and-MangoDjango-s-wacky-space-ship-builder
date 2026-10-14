#pragma once

class Matrix4x4 {
public:
    float m[16];
    Matrix4x4() {}

    operator const float* () const {}

    static Matrix4x4 ortho(float left, float right, float bottom, float top, float zNear, float zFar) {}
};
