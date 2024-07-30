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

vec3 color(const ray& r, hitable *world, int depth)
{   
    hit_record rec;
    if(world->hit(r, 0.001, MAXFLOAT, rec))
    {
        ray scattered;
        vec3 attenuation;
        if (depth < 50 && rec.mat_ptr->scatter(r, rec, attenuation, scattered))
        {
            return attenuation * color(scattered, world, depth + 1);
        }
        else
        {
            return vec3(0, 0, 0);
        }
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

    hitable *list[4];

    list[0] = new sphere(vec3(0, 0, -1), 0.5, new lambertian(vec3(0.8, 0.3, 0.3)));
    list[1] = new sphere(vec3(0, -100.5, -1), 100, new lambertian(vec3(0.8, 0.8, 0.0)));
    list[2] = new sphere(vec3(1, 0, -1), 0.5, new metal(vec3(0.8, 0.6, 0.2), 0.3));
    list[3] = new sphere(vec3(-1, 0, -1), 0.5, new metal(vec3(0.8, 0.8, 0.8), 1.0));
    hitable *world = new hitableList(list, 4);

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
                col += color(r, world, 0);

            }

            col /= float(ns);

            col = vec3(std::sqrt(col[0]), std::sqrt(col[1]), std::sqrt(col[2]));
            int ir = int (255.99 * col[0]);
            int ig = int (255.99 * col[1]);
            int ib = int (255.99 * col[2]);

            std::cout << ir << " " << ig << " " << ib << "\n";
        } 
    }

    return 0;
}