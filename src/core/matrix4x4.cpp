#include "matrix4x4.h"

Matrix4x4::Matrix4x4() {
		std::memset(m, 0, sizeof(m));
		m[0] = 1.0f;
		m[5] = 1.0f;
		m[10] = 1.0f;
		m[15] = 1.0f;
}

Matrix4x4::operator const float* () const {
		return m;
}

Matrix4x4 Matrix4x4::ortho(float left, float right, float bottom, float top, float zNear, float zFar) {
		Matrix4x4 result;

		result.m[0] = 2.0f / (right - left);
		result.m[5] = 2.0f / (top - bottom);
		result.m[10] = -2.0f / (zFar - zNear);

		result.m[12] = -(right + left) / (right - left);
		result.m[13] = -(top + bottom) / (top - bottom);
		result.m[14] = -(zFar + zNear) / (zFar - zNear);
		result.m[15] = 1.0f;

		return result;
}