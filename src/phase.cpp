#include"vec.hpp"
#include"random.hpp"

#include<cmath>

float henyey_greenstein_phase(float theta, float g)
{
    float denomi = 1 + g*g - 2*g*std::cos(theta);
    return 1/(4 * M_PI) * (1 - g*g) / std::pow(denomi, 3.0f/2.0f);
}

Vec henyey_greenstein_sample(float g, float u, float v)
{
    float s = 2*u - 1;
    float T = (1 - g*g) / (1 + g * s);
    float cosTheta = 1.0/(2.0 * g) * (1 + g*g - std::pow(T, 2.0f));
    float sinTheta = std::sqrt(1 - cosTheta*cosTheta);
    float phi = 2 * M_PI * v;

    return {sinTheta * std::cos(phi),
            sinTheta * std::sin(phi),
            cosTheta};
}