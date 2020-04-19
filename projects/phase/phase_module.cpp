#include"pybind11/pybind11.h"
#include"pybind11/stl.h"
#include"phase.hpp"
#include <vector>
#include <random>
#include <iostream>
std::random_device seed_gen;
std::default_random_engine engine(seed_gen());

// 0.0以上1.0未満の値を等確率で発生させる
std::uniform_real_distribution<float> dist(0.0, 1.0);
float rnd()
{
    return dist(engine);
}

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

/////////// from edupt //////////////
const float kPI = 3.14159265358979323846;
const float kINF = 1e128;
const float kEPS = 1e-6;

struct _Ray {
	Vec org, dir;
    bool in_media;
	_Ray(const Vec &org, const Vec &dir, bool in_media) : org(org), dir(dir),in_media(in_media) {}
};

struct _Hitpoint {
	float distance;
	Vec normal;
	Vec position;

	_Hitpoint() : distance(kINF), normal({0,0,0}), position({0,0,0}) {}
};

bool intersect(const Vec& position, float radius,
               const _Ray &ray, _Hitpoint *hitpoint)
{
    const Vec p_o = position - ray.org;
    const float b = dot(p_o, ray.dir);
    const float D4 = b * b - dot(p_o, p_o) + radius * radius;

    if (D4 < 0.0)
        return false;
    
    const float sqrt_D4 = sqrt(D4);
    const float t1 = b - sqrt_D4, t2 = b + sqrt_D4;

    if (t1 < kEPS && t2 < kEPS)
        return false;

    if (t1 > kEPS) {
        hitpoint->distance = t1;
    } else {
        hitpoint->distance = t2;
    }

    hitpoint->position = ray.org + hitpoint->distance * ray.dir;
    hitpoint->normal   = normalize(hitpoint->position - position);
		return true;
}
/////////////////////////////////////

void branchlessONB(const Vec &n, Vec &b1, Vec &b2)
{
    float sign = copysignf(1.0f, n.z);
    const float a = -1.0f / (sign + n.z);
    const float b = n.x * n.y * a;
    b1 = Vec(1.0f + sign * n.x * n.x * a, sign * b, -sign * n.x);
    b2 = Vec(b, sign + n.y * n.y * a, -n.y);
}

Vec _calc_normal(const Vec& position, const Vec& centor)
{
    return normalize(position - centor);
}

bool _is_outside(const Vec& wo, const Vec& n)
{
    return dot(wo, n) > 0;
}

float _distance_sample(float sigma_e, float u)
{
    return -std::log(1 - u)/sigma_e;
}

//View vpt`s path in sphere(homogenious)
std::vector<std::vector<float>> //path list
vpt_path(float g, //HG phase function param
         float sigma_a, float sigma_s, //these unit = [m^-1]
         float radius, //unit=[m].Sphere centor = (0,0,0)
         std::vector<float> start_origin, std::vector<float> start_dir)
{
    std::vector<std::vector<float>> path_list;
    float sigma_e = sigma_a + sigma_s;
    Vec centor{0,0,0};
    Vec origin{start_origin[0], start_origin[1],start_origin[2]};
    Vec dir{start_dir[0],start_dir[1],start_dir[2]};
    _Ray ray{origin,dir,false};//assume that path start is outside sphere

    //Trace
    while(1)
    {
        if(ray.in_media)
        {
            _Hitpoint hitpoint;
            bool is_hit = intersect(centor, radius, ray, &hitpoint);
            if(is_hit)
            {
                float max_d = hitpoint.distance;
                float d = _distance_sample(sigma_e, rnd());
                if(kEPS < d && d < max_d)
                {
                    //scattering
                    Vec scatter_point = ray.org + d * ray.dir;
                    //add path
                    Vec extra_path = scatter_point - ray.org;
                    path_list.push_back({extra_path.x, extra_path.y, extra_path.z});

                    //scattering sampling
                    Vec scatter_dir_local = henyey_greenstein_sample(g, rnd(), rnd());
                    Vec local_x = {0,0,0}, local_y = {0,0,0};
                    branchlessONB(ray.dir, local_x, local_y);
                    Vec scatter_dir =  scatter_dir_local.x * local_x
                                      +scatter_dir_local.y * local_y
                                      +scatter_dir_local.z * ray.dir;
                    
                    //renew ray
                    ray.org = scatter_point;
                    ray.dir = scatter_dir;
                    //Needn't to change ray.in_media

                    continue;
                }
                else
                {
                    // reach surface
                    Vec extra_path = hitpoint.position - ray.org;
                    path_list.push_back({extra_path.x, extra_path.y, extra_path.z});
                    break;
                }
                
            }
            else
            {
                std::cout << "serious error: 1" << std::endl;
                break;
            }
            
        }
        else
        {
            _Hitpoint hitpoint;
            bool is_hit = intersect(centor, radius, ray, &hitpoint);
            if(is_hit)
            {
                _Hitpoint internal_hitpoint;
                _Ray internal_ray{hitpoint.position, ray.dir, false};
                bool is_internal_hit = intersect(centor, radius, 
                                                 internal_ray, &internal_hitpoint);
                float d = _distance_sample(sigma_e, rnd());
                float max_d = internal_hitpoint.distance;
                if(kEPS < d && d < max_d)
                {
                    //add path
                    Vec scatter_point = internal_ray.org + d * internal_ray.dir;
                    Vec extra_path = scatter_point - ray.org;
                    path_list.push_back({extra_path.x, extra_path.y, extra_path.z});

                    //calculate scattering direction
                    Vec scatter_dir_local = henyey_greenstein_sample(g, rnd(), rnd());
                    Vec local_x{0,0,0}, local_y{0,0,0};
                    branchlessONB(ray.dir, local_x, local_y);
                    Vec scatter_dir =  scatter_dir_local.x * local_x
                                      +scatter_dir_local.y * local_y
                                      +scatter_dir_local.z * ray.dir;

                    //renew ray
                    ray.org = scatter_point;
                    ray.dir = scatter_dir;
                    ray.in_media = true;

                    continue;
                }
                else
                {
                    //reach surface
                    Vec extra_path = internal_hitpoint.position - ray.org;
                    path_list.push_back({extra_path.x, extra_path.y, extra_path.z});
                    break;   
                }
            }
            else
            {
                std::cout << "first ray doesn't hit sphere" << std::endl;
                break;
            }
        }
    }

    return path_list;
}


namespace py = pybind11;
PYBIND11_MODULE(phase_module, m)
{
    m.doc() = "phase function test";
    m.def("henyey_greenstein_sample",&wrap_henyey_greenstein_sample);
    m.def("henyey_greenstein_phase", &wrap_henyey_greenstein_phase);
    m.def("vpt_path", &vpt_path);
}
