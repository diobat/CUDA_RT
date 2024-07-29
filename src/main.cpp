#include <iostream>

#include "sphere.hpp"
#include "hitableList.hpp"
#include "camera.hpp"

#include <random>

float hit_sphere ( const vec3& center, float radius, const ray& r)
{
    vec3 oc = r.origin() - center;
    float a = dot(r.direction(), r.direction());
    float b = 2.0f * dot(oc, r.direction());
    float c = dot(oc, oc) - radius*radius;
    float discriminant = b*b - 4*a*c;

    if(discriminant < 0)
    {
        return -1.0f;
    }
    return (-b - sqrt(discriminant)) / (2.0f*a);
}

vec3 color(const ray& r, hitable *world)
{   
    hit_record rec;
    if(world->hit(r, 0.0, MAXFLOAT, rec))
    {
        return 0.5f * vec3(rec.normal.x() + 1, rec.normal.y() + 1, rec.normal.z() + 1);
    }
    else
    {
        vec3 unit_direction = unit_vector(r.direction());
        float t = 0.5f * (unit_direction.y() + 1.0f);
        return (1.0f - t) * vec3(1.0f, 1.0f, 1.0f) + t * vec3(0.5f, 0.7f, 1.0f);
    }
}

int main()
{
    int nx = 600;
    int ny = 300;
    int ns = 100;

    std::cout << "P3\n" << nx << " " << ny << "\n255\n";

    vec3 lower_left_corner(-2.0, -1.0, -1.0);
    vec3 horizontal(4.0, 0.0, 0.0);
    vec3 vertical(0.0, 2.0, 0.0);
    vec3 origin(0.0, 0.0, 0.0);

    hitable *list[2];

    list[0] = new sphere(vec3(0, 0, -1), 0.5);
    list[1] = new sphere(vec3(0, -100.5, -1), 100);
    hitable *world = new hitableList(list, 2);

    camera cam;

    for (int j = ny - 1 ; j >= 0 ; j--)
    {
        for (int i = 0; i < nx; i++)
        {
            vec3 col(0, 0, 0);
            for (int s = 0; s < ns; s++)
            {
                float u = float(i + ((float) rand() / RAND_MAX)) / float(nx);
                float v = float(j + ((float) rand() / RAND_MAX)) / float(ny);

                ray r = cam.get_ray(u, v);

                vec3 p = r.point_at_parameter(2.0);
                col += color(r, world);

            }

            col /= float(ns);

            int ir = int (255.99 * col[0]);
            int ig = int (255.99 * col[1]);
            int ib = int (255.99 * col[2]);

            std::cout << ir << " " << ig << " " << ib << "\n";
        } 
    }

    return 0;
}