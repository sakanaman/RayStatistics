#include "pybind11/pybind11.h"
#include "pybind11/stl.h"
#include "diffuse.hpp"
#include <vector>

std::vector<float> wrap_sample_diffuse(float u, float v)
{
    Vec wi = sample_cosine_hemisphere(u, v);
    return {wi.x, wi.y, wi.z};
}

std::vector<float> wrap_brdf_diffuse(std::vector<float>& albedo)
{
    Vec brdf = brdf_diffuse({albedo[0], albedo[1], albedo[2]});
    return {brdf.x, brdf.y, brdf.z};
}

float wrap_pdf_diffuse(std::vector<float>& wi)
{
    return pdf_diffuse({wi[0], wi[1], wi[2]});
}


namespace py = pybind11;
PYBIND11_MODULE(diffuse_module, m)
{
    m.doc() = "diffuse test";
    m.def("sample_diffuse", &wrap_sample_diffuse);
    m.def("brdf_diffuse", &wrap_brdf_diffuse);
    m.def("pdf_diffuse", &wrap_pdf_diffuse);
}