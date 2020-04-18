#ifndef PHASE_HPP
#define PHASE_HPP
#include"vec.hpp"

float henyey_greenstein_phase(float theta, float g);
Vec henyey_greenstein_sample(float g, float u, float v);

#endif