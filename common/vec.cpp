#include "vec.hpp"
#include<cmath>

Vec::Vec(const float x, const float y, const float z) : x(x), y(y), z(z){}
Vec Vec::operator+(const Vec &b) const 
{
	return {x + b.x, y + b.y, z + b.z};
}
Vec Vec::operator-(const Vec &b) const {
    return {x - b.x, y - b.y, z - b.z};
}
Vec Vec::operator*(const float b) const {
    return {x * b, y * b, z * b};
}
Vec Vec::operator/(const float b) const {
    return {x / b, y / b, z / b};
}
float Vec::length_squared() const { 
    return x*x + y*y + z*z; 
}
float Vec::length() const { 
    return sqrt(length_squared()); 
}



Vec operator*(float f, const Vec &v) { 
	return v * f; 
}
Vec normalize(const Vec &v) {
	return v * (1.0 / v.length()); 
}
Vec multiply(const Vec &v1, const Vec &v2) {
	return {v1.x * v2.x, v1.y * v2.y, v1.z * v2.z};
}
float dot(const Vec &v1, const Vec &v2) {
	return v1.x * v2.x + v1.y * v2.y + v1.z * v2.z;
}
Vec cross(const Vec &v1, const Vec &v2) {
	return 	{
				(v1.y * v2.z) - (v1.z * v2.y),
				(v1.z * v2.x) - (v1.x * v2.z),
				(v1.x * v2.y) - (v1.y * v2.x)
			};
}
