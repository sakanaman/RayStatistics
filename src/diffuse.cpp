#include"vec.hpp"
#include"random.hpp"

#include<cmath>

Vec sample_cosine_hemisphere(float u, float v)
{
    float z = v;
    float r = std::sqrt(1 - z * z);

    
    float x = r * std::cos(2 * M_PI * u);
    float y = r * std::sin(2 * M_PI * u);

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