#ifndef DIFFUSE_HPP
#define DIFFUSE_HPP

#include "vec.hpp"

Vec sample_cosine_hemisphere(float u, float v);
Vec brdf_diffuse(const Vec& albedo);
float pdf_diffuse(const Vec& wi);


#endif





