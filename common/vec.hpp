#ifndef VEC_HPP
#define VEC_HPP

struct Vec {
	float x = 0, y = 0, z = 0;
	
    Vec(const float x, const float y, const float z);
	Vec operator+(const Vec &b) const;
	Vec operator-(const Vec &b) const;
	Vec operator*(const float b) const;
	Vec operator/(const float b) const;
	float length_squared() const;
	float length() const ;
};
Vec operator*(float f, const Vec &v);
Vec normalize(const Vec &v);
Vec multiply(const Vec &v1, const Vec &v2);
float dot(const Vec &v1, const Vec &v2);
Vec cross(const Vec &v1, const Vec &v2);


#endif