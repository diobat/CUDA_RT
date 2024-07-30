#pragma once

#include "ray.hpp"

class camera
{
    public:
        camera(vec3 lookFrom, vec3 lookAt, vec3 vup, float vfov, float aspect)
        {
            vec3 u, v, w;
            float theta = vfov*M_PI/180;
            float half_height = tan(theta/2);
            float half_width = aspect * half_height;
            
            origin = lookFrom;
            w = unit_vector(lookFrom - lookAt);
            u = unit_vector(cross(vup, w));
            v = cross(w, u);

            lower_left_corner = origin - half_width*u - half_height*v - w;
            horizontal = 2*half_width*u;
            vertical = 2*half_height*v;
        }
        ray get_ray(float u, float v) { return ray(origin, lower_left_corner + u*horizontal + v*vertical - origin); }

        vec3 origin;
        vec3 lower_left_corner;
        vec3 horizontal;
        vec3 vertical;
};

