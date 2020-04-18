#include"vec.hpp"
#include"random.hpp"

#include<cmath>

Vec sample_cosine_hemisphere(float u, float v)
{
    float x = std::sqrt(u) * std::cos(2 * M_PI * v);
    float y = std::sqrt(u) * std::sin(2 * M_PI * v);
    float z = std::sqrt(1-u);

    return {x, y, z};
}
Vec brdf_diffuse(const Vec& albedo)
{
    return (albedo / M_PI);
}

float pdf_diffuse(const Vec& wi)
{
    float cosTheta = wi.z;
    return cosTheta/M_PI;
}