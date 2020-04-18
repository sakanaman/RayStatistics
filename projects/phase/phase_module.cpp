#include"pybind11/pybind11.h"
#include"pybind11/stl.h"
#include"phase.hpp"
#include <vector>

std::vector<float> wrap_henyey_greenstein_sample(float g, float u, float v)
{
    Vec wi_local = henyey_greenstein_sample(g,u,v);
    return {wi_local.x, 
            wi_local.y, 
            wi_local.z};
}

float wrap_henyey_greenstein_phase(float theta, float g)
{
    return henyey_greenstein_phase(theta, g);
}

namespace py = pybind11;
PYBIND11_MODULE(phase_module, m)
{
    m.doc() = "phase function test";
    m.def("henyey_greenstein_sample",&wrap_henyey_greenstein_sample);
    m.def("henyey_greenstein_phase", &wrap_henyey_greenstein_phase);
}
